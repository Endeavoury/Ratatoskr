#ifndef _WIN32
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/in.h>

#include "core/core_internal.h"
#include "protocols/dns/dns_internal.h"

static void put_u16(uint8_t *data, size_t *at, uint16_t value) {
    data[(*at)++] = (uint8_t)(value >> 8);
    data[(*at)++] = (uint8_t)value;
}

static size_t owner_pointer_packet(uint8_t *data, size_t capacity, uint16_t id, size_t chain_count) {
    size_t at = 0u, chain_start, i;
    assert(chain_count > 0u && chain_count <= 128u && capacity >= 512u);
    put_u16(data, &at, id); put_u16(data, &at, 0x8180u);
    put_u16(data, &at, 1u); put_u16(data, &at, 2u);
    put_u16(data, &at, 0u); put_u16(data, &at, 0u);
    data[at++] = 0u; put_u16(data, &at, RATOS_DNS_A); put_u16(data, &at, 1u);
    put_u16(data, &at, 0xc00cu); put_u16(data, &at, 65000u); put_u16(data, &at, 1u);
    memset(data + at, 0, 4u); at += 4u;
    put_u16(data, &at, (uint16_t)(chain_count * 2u));
    chain_start = at;
    put_u16(data, &at, 0xc00cu);
    for (i = 1u; i < chain_count; ++i)
        put_u16(data, &at, (uint16_t)(0xc000u | (chain_start + (i - 1u) * 2u)));
    put_u16(data, &at, (uint16_t)(0xc000u | (chain_start + (chain_count - 1u) * 2u)));
    put_u16(data, &at, RATOS_DNS_A); put_u16(data, &at, 1u);
    memset(data + at, 0, 4u); at += 4u;
    put_u16(data, &at, 4u);
    data[at++] = 192u; data[at++] = 0u; data[at++] = 2u; data[at++] = 1u;
    return at;
}

static void init_request(ratos_context **out_ctx, ratos_dns_request **out_request, ratos_dns_endpoint *peer) {
    static const uint8_t address[4] = {127u, 0u, 0u, 1u};
    ratos_dns_request_options options;
    *out_ctx = ratos_context_create();
    assert(*out_ctx != NULL);
    ratos_dns_endpoint_init(peer);
    peer->family = RATOS_DNS_ADDRESS_FAMILY_IPV4;
    peer->port = 53u;
    peer->address = address;
    peer->address_len = sizeof(address);
    ratos_dns_request_options_init(&options);
    options.upstream = peer;
    assert(ratos_dns_request_start(*out_ctx, ".", &options, out_request) == RATOS_OK);
    assert((*out_ctx)->dns_outstanding_requests == 1u);
}

static void assert_terminal_resource(ratos_context *ctx, ratos_dns_request *request) {
    ratos_dns_result *result = (ratos_dns_result *)(uintptr_t)1u;
    assert(ratos_dns_request_get_state(request) == RATOS_DNS_REQUEST_STATE_FAILED);
    assert(ratos_dns_request_error_class(request) == RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT);
    assert(ctx->dns_outstanding_requests == 0u);
    assert(ctx->dns_connections == 0u);
    assert(ratos_dns_request_take_result(request, &result) == RATOS_ERROR_INVALID_ARGUMENT);
    assert(result == NULL);
}

static void test_record_owner_pointer_limit_over_udp_and_tcp(void) {
    uint8_t packet[512];
    ratos_context *ctx;
    ratos_dns_request *request = NULL;
    ratos_dns_endpoint peer;
    ratos_dns_event event;
    size_t length;

    init_request(&ctx, &request, &peer);
    length = owner_pointer_packet(packet, sizeof(packet), request->id, 128u);
    assert(ratos_dns_request_receive_udp(request, packet, length, &peer, &event) == RATOS_ERROR_OUT_OF_MEMORY);
    assert_terminal_resource(ctx, request);
    ratos_dns_request_destroy(request);
    ratos_context_destroy(ctx);

    init_request(&ctx, &request, &peer);
    packet[0] = (uint8_t)(request->id >> 8); packet[1] = (uint8_t)request->id;
    packet[2] = 0x83u; packet[3] = 0x80u;
    packet[4] = 0u; packet[5] = 1u; packet[6] = packet[7] = packet[8] = packet[9] = packet[10] = packet[11] = 0u;
    packet[12] = 0u; packet[13] = 0u; packet[14] = 1u; packet[15] = 0u; packet[16] = 1u;
    assert(ratos_dns_request_receive_udp(request, packet, 17u, &peer, &event) == RATOS_OK);
    assert(ratos_dns_request_get_state(request) == RATOS_DNS_REQUEST_STATE_TCP_PENDING);
    length = owner_pointer_packet(packet, sizeof(packet), request->id, 128u);
    {
        uint8_t frame[514]; size_t used = 0u;
        frame[0] = (uint8_t)(length >> 8); frame[1] = (uint8_t)length;
        memcpy(frame + 2u, packet, length);
        assert(ratos_dns_request_receive_tcp(request, frame, length + 2u, &used, &event) == RATOS_ERROR_OUT_OF_MEMORY);
        assert(used == length + 2u);
    }
    assert_terminal_resource(ctx, request);
    ratos_context_destroy(ctx);
    assert(request->context == NULL);
    assert(ratos_dns_request_get_state(request) == RATOS_DNS_REQUEST_STATE_FAILED);
    ratos_dns_request_destroy(request);
}

static void test_effective_boundaries_and_invalid_pointer_configuration(void) {
    ratos_context *ctx = ratos_context_create();
    ratos_dns_limits limits;
    uint8_t packet[512] = {0};
    ratos_dns_result *result = NULL;
    assert(ctx != NULL);
    ratos_dns_limits_init(&limits);
    limits.max_compression_pointer_traversals = 129u;
    assert(ratos_dns_context_set_dns_limits(ctx, &limits) == RATOS_ERROR_INVALID_ARGUMENT);
    limits.max_compression_pointer_traversals = 0u;
    limits.max_total_rrs = 0u;
    assert(ratos_dns_context_set_dns_limits(ctx, &limits) == RATOS_OK);
    packet[0] = 0x12u; packet[1] = 0x34u; packet[2] = 0x81u; packet[3] = 0x80u;
    packet[4] = 0u; packet[5] = 1u; packet[6] = 0x10u; packet[7] = 0x01u;
    packet[12] = 0u; packet[13] = 0u; packet[14] = 1u; packet[15] = 0u; packet[16] = 1u;
    assert(ratos_dns_parse_response(ctx, packet, 17u, 0x1234u, ".", RATOS_DNS_A, "fixture", &result) == RATOS_ERROR_OUT_OF_MEMORY);
    assert(result == NULL);
    assert(ratos_dns_parse_response(ctx, packet, owner_pointer_packet(packet, sizeof(packet), 0x1234u, 126u), 0x1234u, ".", RATOS_DNS_A, "fixture", &result) == RATOS_OK);
    assert(result != NULL && ratos_dns_result_count(result) == 2u);
    ratos_dns_result_destroy(result);
    ratos_context_destroy(ctx);
}

static void test_oversized_synchronous_udp_datagram(void) {
    int pipefd[2];
    pid_t child;
    uint16_t port;
    ratos_context *ctx;
    ratos_dns_query_options options;
    ratos_dns_limits limits;
    ratos_dns_result *result = (ratos_dns_result *)(uintptr_t)1u;
    int status;
    assert(pipe(pipefd) == 0);
    child = fork();
    assert(child >= 0);
    if (child == 0) {
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        struct sockaddr_in address, client;
        socklen_t client_length = sizeof(client);
        uint8_t query[512], response[30] = {0};
        ssize_t received;
        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET; address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); address.sin_port = 0;
        assert(fd >= 0 && bind(fd, (struct sockaddr *)&address, sizeof(address)) == 0);
        assert(getsockname(fd, (struct sockaddr *)&address, &client_length) == 0);
        port = ntohs(address.sin_port);
        assert(write(pipefd[1], &port, sizeof(port)) == (ssize_t)sizeof(port));
        received = recvfrom(fd, query, sizeof(query), 0, (struct sockaddr *)&client, &client_length);
        assert(received > 0);
        assert(sendto(fd, response, sizeof(response), 0, (struct sockaddr *)&client, client_length) == (ssize_t)sizeof(response));
        close(fd); close(pipefd[1]); _exit(0);
    }
    close(pipefd[1]);
    assert(read(pipefd[0], &port, sizeof(port)) == (ssize_t)sizeof(port));
    close(pipefd[0]);
    ctx = ratos_context_create(); assert(ctx != NULL);
    ratos_dns_limits_init(&limits); limits.max_udp_message_bytes = 29u;
    assert(ratos_dns_context_set_dns_limits(ctx, &limits) == RATOS_OK);
    ratos_dns_query_options_init(&options); options.server = "127.0.0.1"; options.port = port; options.timeout_ms = 1000u;
    assert(ratos_dns_query(ctx, "example.com", &options, &result) == RATOS_ERROR_OUT_OF_MEMORY);
    assert(result == NULL);
    ratos_context_destroy(ctx);
    assert(waitpid(child, &status, 0) == child && WIFEXITED(status) && WEXITSTATUS(status) == 0);
}

int main(void) {
    test_record_owner_pointer_limit_over_udp_and_tcp();
    test_effective_boundaries_and_invalid_pointer_configuration();
    test_oversized_synchronous_udp_datagram();
    puts("G7 configured-limits re-review tests passed");
    return 0;
}
#else
int main(void) { return 0; }
#endif
