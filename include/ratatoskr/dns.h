#ifndef RATATOSKR_DNS_H
#define RATATOSKR_DNS_H
#include <stddef.h>
#include <stdint.h>
#include "ratatoskr/context.h"
#include "ratatoskr/error.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t ratos_dns_type;
enum { RATOS_DNS_A=1, RATOS_DNS_NS=2, RATOS_DNS_MD=3, RATOS_DNS_MF=4, RATOS_DNS_CNAME=5, RATOS_DNS_SOA=6, RATOS_DNS_MB=7, RATOS_DNS_MG=8, RATOS_DNS_MR=9, RATOS_DNS_NULL=10, RATOS_DNS_WKS=11, RATOS_DNS_PTR=12, RATOS_DNS_HINFO=13, RATOS_DNS_MINFO=14, RATOS_DNS_MX=15, RATOS_DNS_TXT=16, RATOS_DNS_AAAA=28, RATOS_DNS_SRV=33, RATOS_DNS_NAPTR=35, RATOS_DNS_CAA=257 };
typedef uint8_t ratos_dns_section;
enum { RATOS_DNS_SECTION_ANSWER=1, RATOS_DNS_SECTION_AUTHORITY=2, RATOS_DNS_SECTION_ADDITIONAL=3 };

typedef struct ratos_dns_query_options { uint32_t struct_size; const char *server; uint16_t port; ratos_dns_type type; uint32_t timeout_ms; uint8_t recursion_desired; uint8_t reserved[7]; } ratos_dns_query_options;
typedef struct ratos_dns_result ratos_dns_result;
typedef struct ratos_dns_record ratos_dns_record;
RATOS_API void ratos_dns_query_options_init(ratos_dns_query_options *options);
RATOS_API ratos_error ratos_dns_query(ratos_context *ctx, const char *name, const ratos_dns_query_options *options, ratos_dns_result **out_result);
RATOS_API void ratos_dns_result_destroy(ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_rcode(const ratos_dns_result *result);
RATOS_API uint16_t ratos_dns_result_transaction_id(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_authoritative(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_truncated(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_recursion_desired(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_recursion_available(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_authentic_data(const ratos_dns_result *result);
RATOS_API uint8_t ratos_dns_result_checking_disabled(const ratos_dns_result *result);
RATOS_API const char *ratos_dns_result_server(const ratos_dns_result *result);
RATOS_API const char *ratos_dns_result_query_name(const ratos_dns_result *result);
RATOS_API ratos_dns_type ratos_dns_result_query_type(const ratos_dns_result *result);
RATOS_API size_t ratos_dns_result_count(const ratos_dns_result *result);
RATOS_API const ratos_dns_record *ratos_dns_result_record(const ratos_dns_result *result, size_t index);
RATOS_API ratos_dns_type ratos_dns_record_type(const ratos_dns_record *record);
RATOS_API uint16_t ratos_dns_record_type_code(const ratos_dns_record *record);
RATOS_API ratos_dns_section ratos_dns_record_section(const ratos_dns_record *record);
RATOS_API const char *ratos_dns_record_name(const ratos_dns_record *record);
RATOS_API uint32_t ratos_dns_record_ttl(const ratos_dns_record *record);
RATOS_API const uint8_t *ratos_dns_record_raw_data(const ratos_dns_record *record, size_t *length);
RATOS_API const char *ratos_dns_record_text(const ratos_dns_record *record);
RATOS_API int ratos_dns_record_uint16(const ratos_dns_record *record, size_t index, uint16_t *value);
RATOS_API int ratos_dns_record_uint32(const ratos_dns_record *record, size_t index, uint32_t *value);
RATOS_API size_t ratos_dns_record_string_count(const ratos_dns_record *record);
RATOS_API const char *ratos_dns_record_string(const ratos_dns_record *record, size_t index);
RATOS_API const char *ratos_dns_type_string(uint16_t type);
RATOS_API const char *ratos_dns_rcode_string(uint8_t rcode);

typedef uint32_t ratos_dns_request_state;
enum { RATOS_DNS_REQUEST_STATE_NEW=0u, RATOS_DNS_REQUEST_STATE_UDP_PENDING=1u, RATOS_DNS_REQUEST_STATE_TCP_PENDING=2u, RATOS_DNS_REQUEST_STATE_COMPLETE=3u, RATOS_DNS_REQUEST_STATE_FAILED=4u, RATOS_DNS_REQUEST_STATE_CANCELLED=5u };
typedef uint32_t ratos_dns_event_kind;
enum { RATOS_DNS_EVENT_NONE=0u, RATOS_DNS_EVENT_PENDING=1u, RATOS_DNS_EVENT_IGNORED_NONMATCHING=2u, RATOS_DNS_EVENT_NEED_TCP_FALLBACK=3u, RATOS_DNS_EVENT_COMPLETE=4u, RATOS_DNS_EVENT_TERMINAL_ERROR=5u, RATOS_DNS_EVENT_CANCELLED=6u };
typedef uint32_t ratos_dns_transport_failure;
enum { RATOS_DNS_TRANSPORT_FAILURE_NONE=0u, RATOS_DNS_TRANSPORT_FAILURE_TIMEOUT=1u, RATOS_DNS_TRANSPORT_FAILURE_NETWORK=2u, RATOS_DNS_TRANSPORT_FAILURE_CONNECT=3u, RATOS_DNS_TRANSPORT_FAILURE_EOF=4u };
typedef uint32_t ratos_dns_error_class;
enum { RATOS_DNS_ERROR_CLASS_NONE=0u, RATOS_DNS_ERROR_CLASS_LOCAL_VALIDATION=1u, RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE=2u, RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT=3u, RATOS_DNS_ERROR_CLASS_UNSUPPORTED_EXTENSION=4u, RATOS_DNS_ERROR_CLASS_TRANSPORT=5u, RATOS_DNS_ERROR_CLASS_CANCELLED=6u };
typedef uint16_t ratos_dns_address_family;
enum { RATOS_DNS_ADDRESS_FAMILY_UNSPEC=0u, RATOS_DNS_ADDRESS_FAMILY_IPV4=4u, RATOS_DNS_ADDRESS_FAMILY_IPV6=6u };
typedef struct ratos_dns_event { uint32_t struct_size; ratos_dns_event_kind kind; ratos_dns_request_state state; ratos_dns_transport_failure transport_failure; ratos_dns_error_class error_class; uint32_t reserved0; uint64_t reserved[2]; } ratos_dns_event;
typedef struct ratos_dns_endpoint { uint32_t struct_size; ratos_dns_address_family family; uint16_t port; const uint8_t *address; uint32_t address_len; uint32_t reserved0; uint64_t reserved[2]; } ratos_dns_endpoint;
typedef struct ratos_dns_request_options { uint32_t struct_size; const ratos_dns_endpoint *upstream; uint64_t deadline_monotonic_ns; uint8_t recursion_desired; uint8_t reserved0[7]; uint64_t reserved[2]; } ratos_dns_request_options;
typedef struct ratos_dns_limits { uint32_t struct_size; uint32_t max_udp_message_bytes; uint32_t max_tcp_frame_bytes; uint32_t max_total_rrs; uint32_t max_name_expansion_bytes; uint32_t max_compression_pointer_traversals; uint32_t max_typed_field_bytes; uint32_t max_outstanding_requests; uint32_t max_connections; uint32_t reserved0; uint64_t reserved[2]; } ratos_dns_limits;
typedef struct ratos_dns_request ratos_dns_request;
enum { RATOS_DNS_CAP_UDP_UNICAST_QUERY=1ull<<0, RATOS_DNS_CAP_TCP_AFTER_UDP_TC=1ull<<1, RATOS_DNS_CAP_INCREMENTAL_TCP_INPUT=1ull<<2, RATOS_DNS_CAP_REQUEST_CANCELLATION=1ull<<3, RATOS_DNS_CAP_RESOURCE_CONFIGURATION=1ull<<4, RATOS_DNS_CAP_OPAQUE_ORDINARY_RDATA=1ull<<5 };
RATOS_API void ratos_dns_event_init(ratos_dns_event *event);
RATOS_API void ratos_dns_endpoint_init(ratos_dns_endpoint *endpoint);
RATOS_API void ratos_dns_request_options_init(ratos_dns_request_options *options);
RATOS_API void ratos_dns_limits_init(ratos_dns_limits *limits);
RATOS_API ratos_error ratos_dns_context_set_dns_limits(ratos_context *context, const ratos_dns_limits *limits);
RATOS_API ratos_error ratos_dns_request_start(ratos_context *context, const char *name, const ratos_dns_request_options *options, ratos_dns_request **out_request);
RATOS_API ratos_error ratos_dns_request_receive_udp(ratos_dns_request *request, const uint8_t *datagram, size_t datagram_len, const ratos_dns_endpoint *peer, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_receive_tcp(ratos_dns_request *request, const uint8_t *bytes, size_t bytes_len, size_t *out_consumed, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_transport_failed(ratos_dns_request *request, ratos_dns_transport_failure why, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_cancel(ratos_dns_request *request, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_take_result(ratos_dns_request *request, ratos_dns_result **out_result);
RATOS_API ratos_dns_request_state ratos_dns_request_get_state(const ratos_dns_request *request);
RATOS_API ratos_dns_error_class ratos_dns_request_error_class(const ratos_dns_request *request);
RATOS_API ratos_dns_transport_failure ratos_dns_request_transport_failure(const ratos_dns_request *request);
RATOS_API void ratos_dns_request_destroy(ratos_dns_request *request);
RATOS_API uint64_t ratos_dns_capabilities(void);
#ifdef __cplusplus
}
#endif
#endif
