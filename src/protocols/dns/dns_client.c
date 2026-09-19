#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <winsock2.h>
#include <iphlpapi.h>
#else
#include <unistd.h>
#endif
#include "protocols/dns/dns_internal.h"

void ratos_dns_query_options_init(ratos_dns_query_options *options) {
    if (options == NULL) return;
    memset(options, 0, sizeof(*options));
    options->struct_size = (uint32_t)sizeof(*options);
    options->port = 53u; options->type = RATOS_DNS_A; options->timeout_ms = 5000u; options->recursion_desired = 1u;
}

char *ratos_dns_default_server(void) {
#ifdef _WIN32
    FIXED_INFO *info = NULL;
    ULONG length = 0u;
    if (GetNetworkParams(NULL, &length) == ERROR_BUFFER_OVERFLOW) info = (FIXED_INFO *)malloc(length);
    if (info != NULL && GetNetworkParams(info, &length) == NO_ERROR) {
        char *server = ratos_strdup(info->DnsServerList.IpAddress.String);
        free(info); return server;
    }
    free(info);
#else
    FILE *file = fopen("/etc/resolv.conf", "r");
    char line[512];
    if (file != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            char server[256];
            if (sscanf(line, " nameserver %255s", server) == 1 || sscanf(line, "nameserver %255s", server) == 1) {
                fclose(file); return ratos_strdup(server);
            }
        }
        fclose(file);
    }
#endif
    return NULL;
}

static uint16_t query_id(void) {
    uint16_t value = 0u;
#ifdef _WIN32
    unsigned int random_value = 0u;
    if (rand_s(&random_value) == 0) value = (uint16_t)random_value;
#else
    FILE *random_file = fopen("/dev/urandom", "rb");
    if (random_file != NULL) {
        if (fread(&value, sizeof(value), 1u, random_file) != 1u) value = 0u;
        fclose(random_file);
    }
#endif
    if (value == 0u) value = (uint16_t)((unsigned)time(NULL) ^ (unsigned)(uintptr_t)&value);
    return value;
}

static int response_requests_tcp(const uint8_t *data, size_t length, uint16_t expected_id) {
    uint16_t id, flags;
    if (length < 4u) return 0;
    id = (uint16_t)(((uint16_t)data[0] << 8) | data[1]);
    flags = (uint16_t)(((uint16_t)data[2] << 8) | data[3]);
    return id == expected_id && (flags & 0x8000u) != 0u && (flags & 0x0200u) != 0u
        && (flags & 0x0040u) == 0u && (flags & 0x7800u) == 0u;
}

ratos_error ratos_dns_query(ratos_context *ctx, const char *name,
    const ratos_dns_query_options *provided, ratos_dns_result **out_result) {
    ratos_dns_query_options options;
    ratos_dns_packet query = {0};
    uint8_t *wire_response = NULL;
    size_t response_length = 0u;
    char *default_server = NULL, *effective_name = NULL;
    const char *server;
    uint16_t id;
    ratos_dns_result *udp_result = NULL;
    ratos_error error;
    if (out_result != NULL) *out_result = NULL;
    if (ctx == NULL || name == NULL || name[0] == '\0' || out_result == NULL) return RATOS_ERROR_INVALID_ARGUMENT;
    ctx->error_message[0] = '\0';
    ratos_dns_query_options_init(&options);
    if (provided != NULL) {
        if (provided->struct_size < offsetof(ratos_dns_query_options, reserved) + sizeof(provided->reserved)) {
            ratos_set_error(ctx, "DNS options struct is too small for ABI version 1"); return RATOS_ERROR_INVALID_ARGUMENT;
        }
        options = *provided;
        if (options.port == 0u) options.port = 53u;
        if (options.timeout_ms == 0u) options.timeout_ms = 5000u;
        if ((uint16_t)options.type == 0u) options.type = RATOS_DNS_A;
    }
    server = options.server;
    if (server == NULL || server[0] == '\0') {
        default_server = ratos_dns_default_server(); server = default_server;
        if (server == NULL) { ratos_set_error(ctx, "No system DNS resolver was found; specify a server"); return RATOS_ERROR_NETWORK; }
    }
    id = query_id();
    error = ratos_dns_build_query(ctx, name, options.type, options.recursion_desired, id, &query, &effective_name);
    if (error != RATOS_OK) goto cleanup;
    error = ratos_dns_udp_exchange(ctx, server, options.port, options.timeout_ms, query.data, query.length, &wire_response, &response_length);
    if (error != RATOS_OK) goto cleanup;
    if (response_requests_tcp(wire_response, response_length, id)) {
        free(wire_response); wire_response = NULL;
        error = ratos_dns_tcp_exchange(ctx, server, options.port, options.timeout_ms, query.data, query.length, &wire_response, &response_length);
        if (error != RATOS_OK) goto cleanup;
        error = ratos_dns_parse_response(ctx, wire_response, response_length, id, effective_name, options.type, server, &udp_result);
        if (error != RATOS_OK) goto cleanup;
    } else {
        error = ratos_dns_parse_response(ctx, wire_response, response_length, id, effective_name, options.type, server, &udp_result);
        if (error != RATOS_OK) goto cleanup;
    }
    *out_result = udp_result; udp_result = NULL;
cleanup:
    free(query.data); free(wire_response); free(effective_name); free(default_server); ratos_dns_result_destroy(udp_result);
    return error;
}

static int endpoint_valid(const ratos_dns_endpoint *e) {
    size_t n;
    if (e == NULL || e->struct_size < sizeof(*e) || e->reserved0 != 0u || e->reserved[0] != 0u || e->reserved[1] != 0u) return 0;
    n = e->family == RATOS_DNS_ADDRESS_FAMILY_IPV4 ? 4u : e->family == RATOS_DNS_ADDRESS_FAMILY_IPV6 ? 16u : 0u;
    return n != 0u && e->address != NULL && e->address_len == n;
}
static int request_name_valid(const char *name) {
    const unsigned char *cursor = (const unsigned char *)name;
    size_t wire_length = 1u, label_length = 0u;
    if (strcmp(name, ".") == 0) return 1;
    while (*cursor != 0u) {
        if (*cursor == (unsigned char)'.') {
            if (label_length == 0u) return 0;
            wire_length += label_length + 1u;
            ++cursor;
            if (*cursor == 0u) break;
            label_length = 0u;
            continue;
        }
        if (*cursor == (unsigned char)'\\') {
            ++cursor;
            if (*cursor == 0u) return 0;
            if (cursor[0] >= '0' && cursor[0] <= '9' && cursor[1] >= '0' && cursor[1] <= '9'
                && cursor[2] >= '0' && cursor[2] <= '9') {
                unsigned value = (unsigned)(cursor[0] - '0') * 100u + (unsigned)(cursor[1] - '0') * 10u + (unsigned)(cursor[2] - '0');
                if (value > 255u) return 0;
                cursor += 3;
            } else ++cursor;
        } else ++cursor;
        if (label_length >= 63u || wire_length + label_length + 2u > 255u) return 0;
        ++label_length;
    }
    if (label_length != 0u) wire_length += label_length + 1u;
    return wire_length <= 255u;
}
static void request_event(ratos_dns_request *r, ratos_dns_event *e, ratos_dns_event_kind kind) {
    ratos_dns_event_init(e); e->kind = kind; if (r != NULL) { e->state = r->state; e->error_class = r->error_class; e->transport_failure = r->transport_failure; }
}
static void request_fail(ratos_dns_request *r, ratos_dns_error_class cls, ratos_dns_transport_failure why) {
    free(r->frame); r->frame = NULL; r->frame_length = r->frame_used = r->prefix_used = 0u;
    ratos_dns_result_destroy(r->result); r->result = NULL;
    r->state = RATOS_DNS_REQUEST_STATE_FAILED; r->error_class = cls; r->transport_failure = why;
}
void ratos_dns_event_init(ratos_dns_event *e) { if (e != NULL) { memset(e, 0, sizeof(*e)); e->struct_size = (uint32_t)sizeof(*e); e->state = RATOS_DNS_REQUEST_STATE_NEW; } }
void ratos_dns_endpoint_init(ratos_dns_endpoint *e) { if (e != NULL) { memset(e, 0, sizeof(*e)); e->struct_size = (uint32_t)sizeof(*e); } }
void ratos_dns_request_options_init(ratos_dns_request_options *o) { if (o != NULL) { memset(o, 0, sizeof(*o)); o->struct_size = (uint32_t)sizeof(*o); o->recursion_desired = 1u; } }
void ratos_dns_limits_init(ratos_dns_limits *l) { if (l != NULL) { memset(l, 0, sizeof(*l)); l->struct_size = (uint32_t)sizeof(*l); } }
ratos_error ratos_dns_context_set_dns_limits(ratos_context *ctx, const ratos_dns_limits *l) {
    if (ctx == NULL || l == NULL || l->struct_size < sizeof(*l) || l->reserved0 != 0u || l->reserved[0] != 0u || l->reserved[1] != 0u || l->max_udp_message_bytes > RATOS_DNS_MAX_PACKET || l->max_tcp_frame_bytes > RATOS_DNS_MAX_PACKET) return RATOS_ERROR_INVALID_ARGUMENT;
    ctx->dns_limits = *l; return RATOS_OK;
}
ratos_error ratos_dns_request_start(ratos_context *ctx, const char *name, const ratos_dns_request_options *o, ratos_dns_request **out) {
    ratos_dns_request *r; size_t n;
    if (out != NULL) *out = NULL;
    if (ctx == NULL || name == NULL || o == NULL || out == NULL || o->struct_size < sizeof(*o) || o->recursion_desired > 1u || o->reserved[0] || o->reserved[1] || o->reserved0[0] || o->reserved0[1] || o->reserved0[2] || o->reserved0[3] || o->reserved0[4] || o->reserved0[5] || o->reserved0[6] || !endpoint_valid(o->upstream)) return RATOS_ERROR_INVALID_ARGUMENT;
    n = strlen(name); if (n == 0u || n > 255u || !request_name_valid(name)) return RATOS_ERROR_INVALID_ARGUMENT;
    r = (ratos_dns_request *)calloc(1u, sizeof(*r)); if (r == NULL) return RATOS_ERROR_OUT_OF_MEMORY;
    r->name = ratos_strdup(name); if (r->name == NULL) { free(r); return RATOS_ERROR_OUT_OF_MEMORY; }
    r->context = ctx; r->id = query_id(); r->type = RATOS_DNS_A; r->recursion_desired = o->recursion_desired; r->limits = ctx->dns_limits; r->state = RATOS_DNS_REQUEST_STATE_UDP_PENDING;
    r->upstream = *o->upstream; memcpy(r->upstream_address, o->upstream->address, o->upstream->address_len); r->upstream.address = r->upstream_address; *out = r; return RATOS_OK;
}
static int matching_peer(const ratos_dns_request *r, const ratos_dns_endpoint *p) { return endpoint_valid(p) && p->family == r->upstream.family && p->port == r->upstream.port && p->address_len == r->upstream.address_len && memcmp(p->address, r->upstream.address, p->address_len) == 0; }
static ratos_error request_parse(ratos_dns_request *r, const uint8_t *b, size_t n, ratos_dns_event *e) {
    ratos_error x; ratos_dns_result *result = NULL;
    if (n > (r->limits.max_udp_message_bytes ? r->limits.max_udp_message_bytes : RATOS_DNS_MAX_PACKET)) { request_fail(r, RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT, 0u); request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR); return RATOS_ERROR_PROTOCOL; }
    x = ratos_dns_parse_response(r->context,b,n,r->id,r->name,r->type,"request",&result);
    if (x != RATOS_OK) { request_fail(r, x == RATOS_ERROR_UNSUPPORTED ? RATOS_DNS_ERROR_CLASS_UNSUPPORTED_EXTENSION : RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE,0u); request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR); return x; }
    if (result->truncated && r->state == RATOS_DNS_REQUEST_STATE_UDP_PENDING) { ratos_dns_result_destroy(result); r->state=RATOS_DNS_REQUEST_STATE_TCP_PENDING; request_event(r,e,RATOS_DNS_EVENT_NEED_TCP_FALLBACK); return RATOS_OK; }
    r->result=result; r->state=RATOS_DNS_REQUEST_STATE_COMPLETE; request_event(r,e,RATOS_DNS_EVENT_COMPLETE); return RATOS_OK;
}
ratos_error ratos_dns_request_receive_udp(ratos_dns_request *r,const uint8_t *b,size_t n,const ratos_dns_endpoint *p,ratos_dns_event *e) {
    if (e != NULL) ratos_dns_event_init(e);
    if (r == NULL || e == NULL || (b == NULL && n != 0u) || !endpoint_valid(p)) return RATOS_ERROR_INVALID_ARGUMENT;
    if (r->state != RATOS_DNS_REQUEST_STATE_UDP_PENDING) { request_event(r,e,RATOS_DNS_EVENT_NONE); return RATOS_ERROR_INVALID_ARGUMENT; }
    if (!matching_peer(r,p) || n < 2u || (((uint16_t)b[0]<<8|b[1]) != r->id) || (n >= 4u && (b[2]&0x78u)!=0u)) { request_event(r,e,RATOS_DNS_EVENT_IGNORED_NONMATCHING); return RATOS_OK; }
    return request_parse(r,b,n,e);
}
ratos_error ratos_dns_request_receive_tcp(ratos_dns_request *r,const uint8_t *b,size_t n,size_t *used,ratos_dns_event *e) {
    size_t take; if (used != NULL) *used=0u; if (e != NULL) ratos_dns_event_init(e); if (r==NULL||used==NULL||e==NULL||(b==NULL&&n!=0u)) return RATOS_ERROR_INVALID_ARGUMENT;
    if (r->state != RATOS_DNS_REQUEST_STATE_TCP_PENDING) { request_event(r,e,RATOS_DNS_EVENT_NONE); return RATOS_ERROR_INVALID_ARGUMENT; }
    while (r->prefix_used < 2u && *used < n) r->prefix[r->prefix_used++] = b[(*used)++];
    if (r->prefix_used < 2u) { request_event(r,e,RATOS_DNS_EVENT_PENDING); return RATOS_OK; }
    if (r->frame == NULL) { r->frame_length=((size_t)r->prefix[0]<<8)|r->prefix[1]; if (r->frame_length==0u) { request_fail(r,RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE,0u); request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR); return RATOS_ERROR_PROTOCOL; } if (r->limits.max_tcp_frame_bytes && r->frame_length > r->limits.max_tcp_frame_bytes) { request_fail(r,RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT,0u); request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR); return RATOS_ERROR_PROTOCOL; } r->frame=(uint8_t*)malloc(r->frame_length); if(!r->frame){request_fail(r,RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT,0u);request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR);return RATOS_ERROR_OUT_OF_MEMORY;} }
    take=r->frame_length-r->frame_used; if(take>n-*used) take=n-*used; memcpy(r->frame+r->frame_used,b+*used,take); r->frame_used+=take; *used+=take;
    if(r->frame_used<r->frame_length){request_event(r,e,RATOS_DNS_EVENT_PENDING);return RATOS_OK;} b=r->frame; n=r->frame_length; r->frame=NULL; r->frame_used=0u; { ratos_error x = request_parse(r,b,n,e); free((void *)b); return x; }
}
ratos_error ratos_dns_request_transport_failed(ratos_dns_request *r,ratos_dns_transport_failure why,ratos_dns_event *e) { if(e!=NULL)ratos_dns_event_init(e); if(r==NULL||e==NULL||why<RATOS_DNS_TRANSPORT_FAILURE_TIMEOUT||why>RATOS_DNS_TRANSPORT_FAILURE_EOF)return RATOS_ERROR_INVALID_ARGUMENT; request_fail(r,RATOS_DNS_ERROR_CLASS_TRANSPORT,why);request_event(r,e,RATOS_DNS_EVENT_TERMINAL_ERROR);return why==RATOS_DNS_TRANSPORT_FAILURE_TIMEOUT?RATOS_ERROR_TIMEOUT:RATOS_ERROR_NETWORK; }
ratos_error ratos_dns_request_cancel(ratos_dns_request *r,ratos_dns_event *e) { if(e!=NULL)ratos_dns_event_init(e);if(r==NULL||e==NULL)return RATOS_ERROR_INVALID_ARGUMENT;if(r->state!=RATOS_DNS_REQUEST_STATE_CANCELLED){free(r->frame);r->frame=NULL;r->state=RATOS_DNS_REQUEST_STATE_CANCELLED;r->error_class=RATOS_DNS_ERROR_CLASS_CANCELLED;}request_event(r,e,RATOS_DNS_EVENT_CANCELLED);return RATOS_OK; }
ratos_error ratos_dns_request_take_result(ratos_dns_request *r,ratos_dns_result **out) {if(out!=NULL)*out=NULL;if(r==NULL||out==NULL||r->state!=RATOS_DNS_REQUEST_STATE_COMPLETE||r->result==NULL)return RATOS_ERROR_INVALID_ARGUMENT;*out=r->result;r->result=NULL;return RATOS_OK;}
ratos_dns_request_state ratos_dns_request_get_state(const ratos_dns_request *r){return r?r->state:RATOS_DNS_REQUEST_STATE_NEW;} ratos_dns_error_class ratos_dns_request_error_class(const ratos_dns_request *r){return r?r->error_class:RATOS_DNS_ERROR_CLASS_NONE;} ratos_dns_transport_failure ratos_dns_request_transport_failure(const ratos_dns_request *r){return r?r->transport_failure:RATOS_DNS_TRANSPORT_FAILURE_NONE;}
void ratos_dns_request_destroy(ratos_dns_request *r){if(r!=NULL){free(r->name);free(r->frame);ratos_dns_result_destroy(r->result);free(r);}} uint64_t ratos_dns_capabilities(void){return RATOS_DNS_CAP_UDP_UNICAST_QUERY|RATOS_DNS_CAP_TCP_AFTER_UDP_TC|RATOS_DNS_CAP_INCREMENTAL_TCP_INPUT|RATOS_DNS_CAP_REQUEST_CANCELLATION|RATOS_DNS_CAP_RESOURCE_CONFIGURATION|RATOS_DNS_CAP_OPAQUE_ORDINARY_RDATA;}
