# DNS native API design proposal — binding-safety remediation (G4)

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-api-design-g4-binding-safety-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `READY_FOR_REVIEW` candidate; not a G4 approval or header realization |
| Revision | Immutable delivery revision and SHA-256 are recorded in `completion-report.md`. |
| Source artifacts | G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b` / SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; G3 approval `865fa190ee19e041c5ddfab8279b49829baaa240`; analysis `5615caed0b7ad0a321d6794e71b79c4195e90384` / SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; superseded G4 candidate `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a` / SHA-256 `4e8c33beecf48a2a55d83183de7dd100c934fa874661a97ae7e25f67277d597d`; binding findings at reviewer revision `c2ab2aa30496edf70163b46b9572c0b155488eb4`. |
| Assumptions | UDP-first, one unicast stub/client transaction; TCP only after correlated UDP TC; OS owns socket mechanics. |
| Open questions | Numeric resource defaults, retry/server selection, and binding-target selection remain product decisions. ABI compatibility is exclusively for the required independent compatibility review. |
| Limitations | Design only: no public header/code, implementation, test, vector, binding, documentation, workflow-state, compatibility review, or binding re-review is authored. |

## 1. Corrective design position

This is a new immutable replacement candidate for the prior G4 candidate. It retains that candidate's opaque request/result ownership, callback-free single-driver model, UDP-first TCP-fallback profile, and additive-only intent, while making every newly binding-visible state, event, transport-failure, and DNS error-class value concretely representable.

The existing synchronous `ratos_dns_query` surface remains unchanged. A later approved realization may add the proposed symbols only after independent binding-safety and compatibility review. No declaration below edits a public header.

## 2. Normative ABI-shape rules

All names below are proposed C declarations. `ratos_dns_request` and `ratos_dns_result` remain opaque owned types. Every new categorical public value is a fixed-width `uint32_t` typedef, never a C enum field. All numeric constants are stable values. A future unknown value must be preserved as an unknown value by consumers and treated conservatively; it is never silently remapped to a known value.

All new public input/output structures begin with `uint32_t struct_size`; field order is normative. Their fields use only fixed-width integers and pointers. The ABI does **not** promise a packed representation or a universal `sizeof` across C ABIs; callers must allocate their own compiled definition, initialize via the named initializer, and set `struct_size` to `sizeof(their_struct)`. Implementations read only fields wholly covered by `struct_size`, ignore an appended unknown tail, and must not read beyond it. A supplied `struct_size` smaller than the current mandatory prefix is `RATOS_ERROR_INVALID_ARGUMENT`.

Reserved fields and every reserved array element must be zero on input. Initializers set `struct_size` to the implementation's current `sizeof`, set all defined values to their documented zero/`NONE` values, and zero all reserved fields. A nonzero reserved input is invalid argument; outputs always zero reserved fields. Existing ABI-1 types are not reordered or changed. Appending fields after the documented final reserved field is the only in-ABI struct evolution route; removing/reordering/changing a field's type, meaning, ownership, or lifetime requires a new ABI generation.

### 2.1 Fixed-width categories

```c
typedef uint32_t ratos_dns_request_state;
enum {
  RATOS_DNS_REQUEST_STATE_NEW = 0u,
  RATOS_DNS_REQUEST_STATE_UDP_PENDING = 1u,
  RATOS_DNS_REQUEST_STATE_TCP_PENDING = 2u,
  RATOS_DNS_REQUEST_STATE_COMPLETE = 3u,
  RATOS_DNS_REQUEST_STATE_FAILED = 4u,
  RATOS_DNS_REQUEST_STATE_CANCELLED = 5u
};

typedef uint32_t ratos_dns_event_kind;
enum {
  RATOS_DNS_EVENT_NONE = 0u,
  RATOS_DNS_EVENT_PENDING = 1u,
  RATOS_DNS_EVENT_IGNORED_NONMATCHING = 2u,
  RATOS_DNS_EVENT_NEED_TCP_FALLBACK = 3u,
  RATOS_DNS_EVENT_COMPLETE = 4u,
  RATOS_DNS_EVENT_TERMINAL_ERROR = 5u,
  RATOS_DNS_EVENT_CANCELLED = 6u
};

typedef uint32_t ratos_dns_transport_failure;
enum {
  RATOS_DNS_TRANSPORT_FAILURE_NONE = 0u,
  RATOS_DNS_TRANSPORT_FAILURE_TIMEOUT = 1u,
  RATOS_DNS_TRANSPORT_FAILURE_NETWORK = 2u,
  RATOS_DNS_TRANSPORT_FAILURE_CONNECT = 3u,
  RATOS_DNS_TRANSPORT_FAILURE_EOF = 4u
};

typedef uint32_t ratos_dns_error_class;
enum {
  RATOS_DNS_ERROR_CLASS_NONE = 0u,
  RATOS_DNS_ERROR_CLASS_LOCAL_VALIDATION = 1u,
  RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE = 2u,
  RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT = 3u,
  RATOS_DNS_ERROR_CLASS_UNSUPPORTED_EXTENSION = 4u,
  RATOS_DNS_ERROR_CLASS_TRANSPORT = 5u,
  RATOS_DNS_ERROR_CLASS_CANCELLED = 6u
};
```

`NONE` means no terminal error classification, not an unknown value. `LOCAL_VALIDATION` is observable only from a failed start (which creates no request); request-level accessors cannot be called for it. `TRANSPORT` is paired with a non-`NONE` transport failure. `CANCELLED` is terminal but not a `ratos_error` failure.

### 2.2 Event layout and initialization

```c
typedef struct ratos_dns_event {
  uint32_t struct_size;
  ratos_dns_event_kind kind;
  ratos_dns_request_state state;
  ratos_dns_transport_failure transport_failure;
  ratos_dns_error_class error_class;
  uint32_t reserved0;
  uint64_t reserved[2];
} ratos_dns_event;

RATOS_API void ratos_dns_event_init(ratos_dns_event *event);
```

The event contains no borrowed pointer, payload, result, DNS bytes, platform socket address, or hidden allocation. `ratos_dns_event_init` requires non-NULL caller storage and sets `kind=NONE`, `state=NEW`, `transport_failure=NONE`, `error_class=NONE`, and all reserved fields to zero. Every operation accepting `ratos_dns_event *event` requires non-NULL storage. Before validating any other argument or mutating request state, it overwrites the caller object as this initializer does. Therefore a returned event is always initialized, including a `ratos_error` return.

### 2.3 Endpoint layout and initialization

```c
typedef uint16_t ratos_dns_address_family;
enum {
  RATOS_DNS_ADDRESS_FAMILY_UNSPEC = 0u,
  RATOS_DNS_ADDRESS_FAMILY_IPV4 = 4u,
  RATOS_DNS_ADDRESS_FAMILY_IPV6 = 6u
};

typedef struct ratos_dns_endpoint {
  uint32_t struct_size;
  ratos_dns_address_family family;
  uint16_t port;
  const uint8_t *address;
  uint32_t address_len;
  uint32_t reserved0;
  uint64_t reserved[2];
} ratos_dns_endpoint;

RATOS_API void ratos_dns_endpoint_init(ratos_dns_endpoint *endpoint);
```

The initializer sets `family=UNSPEC`, `port=0`, `address=NULL`, `address_len=0`, and all reserved fields to zero. This initialized empty endpoint is not a usable peer for receive correlation. A usable endpoint has `family=IPV4` with exactly four address octets or `family=IPV6` with exactly sixteen address octets; `address` is non-NULL and points to those exact binary octets in network byte order; `port` is the host-order numeric UDP/TCP port. `address_len` must be exactly 4 or 16 for its family. No other family, length, or nonzero reserved value is accepted in this candidate.

`address` is binary data, never C text: no NUL terminator is implied, required, added, or inspected. The endpoint structure and its address storage are borrowed only for the duration of `ratos_dns_request_receive_udp`; neither pointer is retained after return. A NULL address is valid only with `address_len==0` in an initialized empty endpoint, which is invalid where a usable peer endpoint is required. The receive operation rejects NULL `peer`, an empty endpoint, and every invalid pointer/length/family combination with `RATOS_ERROR_INVALID_ARGUMENT` before consuming the supplied datagram or changing request state.

## 3. Operations, input ownership, and outputs

| ID | Proposed operation | Contract |
| --- | --- | --- |
| API-DNS-001 | `void ratos_dns_request_options_init(ratos_dns_request_options *o)` | Required initializer for the new request-options struct; it sets `struct_size`, defined defaults, and reserved zeros. The options struct is copied on accepted start and is not retained. |
| API-DNS-002 | `ratos_error ratos_dns_request_start(ratos_context *ctx, const char *name, const ratos_dns_request_options *o, ratos_dns_request **out_request)` | Validates before I/O. `out_request` is required and is set to NULL before any validation. On `RATOS_OK`, it returns one owned request in UDP_PENDING. On every non-OK return it remains NULL and no request/result ownership transfers. |
| API-DNS-003 | `ratos_error ratos_dns_request_receive_udp(ratos_dns_request *r, const uint8_t *datagram, size_t datagram_len, const ratos_dns_endpoint *peer, ratos_dns_event *event)` | One complete UDP datagram. The byte range and endpoint/address bytes are borrowed only for the call. `datagram==NULL` is valid only with `datagram_len==0`; a zero-length datagram is then a malformed correlated input only after valid request/peer checks. |
| API-DNS-004 | `ratos_error ratos_dns_request_receive_tcp(ratos_dns_request *r, const uint8_t *bytes, size_t bytes_len, size_t *out_consumed, ratos_dns_event *event)` | Only in TCP_PENDING. `out_consumed` and `event` are required, set to 0 and initialized before validation. `bytes==NULL` is valid only with `bytes_len==0`. It accepts at most one prefix-plus-frame and reports exactly the accepted leading count; an unaccepted suffix remains caller-owned. |
| API-DNS-005 | `ratos_error ratos_dns_request_transport_failed(ratos_dns_request *r, ratos_dns_transport_failure why, ratos_dns_event *event)` | `why` must be TIMEOUT, NETWORK, CONNECT, or EOF (not NONE/unknown). It terminally records transport failure, releases request transport state, and transfers no result. |
| API-DNS-006 | `ratos_error ratos_dns_request_cancel(ratos_dns_request *r, ratos_dns_event *event)` | `event` is required and initialized. First cancellation transitions a nonterminal request to CANCELLED; repeated cancellation returns `RATOS_OK` with CANCELLED state/event and does not transfer a result. |
| API-DNS-007 | `ratos_error ratos_dns_request_take_result(ratos_dns_request *r, ratos_dns_result **out_result)` | `out_result` is required and set NULL before validation. Only COMPLETE with an untaken result returns `RATOS_OK` and transfers the sole owned result. All other paths leave it NULL. |
| API-DNS-008 | `ratos_dns_request_state ratos_dns_request_state(const ratos_dns_request *r)` | Non-NULL request input. Returns the fixed-width current state; terminal state is stable until destruction. |
| API-DNS-009 | `ratos_dns_error_class ratos_dns_request_error_class(const ratos_dns_request *r)` | **Named DNS error-class accessor.** Non-NULL request input. Returns NONE while NEW/UDP_PENDING/TCP_PENDING/COMPLETE; returns the terminal class in FAILED/CANCELLED. It returns TRANSPORT only for a transport terminal path and CANCELLED only for cancellation. It never represents a valid DNS RCODE. |
| API-DNS-010 | `ratos_dns_transport_failure ratos_dns_request_transport_failure(const ratos_dns_request *r)` | Non-NULL request input. Returns the recorded reason only when `error_class==TRANSPORT`; otherwise returns NONE. |
| API-DNS-011 | `void ratos_dns_request_destroy(ratos_dns_request *r)` | Accepts NULL. It cancels a nonterminal request, destroys any untaken result, and releases request/frame state. |
| API-DNS-012 | `void ratos_dns_limits_init(ratos_dns_limits *l)` and `ratos_error ratos_dns_context_set_dns_limits(ratos_context *ctx, const ratos_dns_limits *l)` | Limits are a versioned fixed-width input struct, initialized then copied for future requests. No limits pointer is retained. |
| API-DNS-013 | `uint64_t ratos_dns_capabilities(void)` | Fixed-width capability bitset; unknown bits are ignored. |

### Name text contract

`name` in `start` is required, non-NULL, and borrowed for that call only. It is a NUL-terminated C string in UTF-8 encoding. The first NUL terminates the value; embedded NUL octets cannot be represented and are not accepted as part of a name. The library neither retains the pointer nor writes through it. The string must be syntactically valid presentation input for the selected DNS-name conversion and must produce the approved DNS label-octet name constraints; invalid UTF-8, invalid presentation syntax, or a name that cannot satisfy those DNS constraints returns `RATOS_ERROR_INVALID_ARGUMENT`, leaves `*out_request==NULL`, sends no packet, and exposes no request-level error class. This text conversion is local API marshaling, not wire parsing in a binding.

Existing result string accessors retain their baseline borrowed immutable C-string contracts. This candidate does not alter their encoding policy.

## 4. Event and field-validity matrix

For every successful feed/cancel/transport operation, `event.struct_size` is the current struct size and both reserved fields are zero. Fields not marked with a specific value below have the initialized value: `transport_failure=NONE` and `error_class=NONE`.

| Operation outcome | `ratos_error` | `event.kind` | `event.state` | `event.transport_failure` | `event.error_class` | Other output validity |
| --- | --- | --- | --- | --- | --- | --- |
| Argument/state validation fails in receive/feed/cancel operation | `RATOS_ERROR_INVALID_ARGUMENT` or `RATOS_ERROR_UNSUPPORTED` | NONE | unchanged current state if `r` is valid; NEW if no request can be observed | NONE | NONE | TCP `*out_consumed=0`; no bytes accepted; no result transfer. |
| Valid `start` | `RATOS_OK` | not applicable | request is UDP_PENDING | n/a | n/a | `*out_request` is owned; no result. |
| Nonmatching UDP datagram or completed TCP frame | `RATOS_OK` | IGNORED_NONMATCHING | unchanged pending state | NONE | NONE | UDP accepts its complete datagram; TCP count is exact completed frame bytes; no result. |
| TCP incomplete prefix/body | `RATOS_OK` | PENDING | TCP_PENDING | NONE | NONE | `*out_consumed` is every supplied byte belonging to incomplete frame; no DNS result. |
| Correlated UDP TC | `RATOS_OK` | NEED_TCP_FALLBACK | TCP_PENDING | NONE | NONE | UDP partial content discarded; no result. |
| Complete correlated valid response, including nonzero base RCODE | `RATOS_OK` | COMPLETE | COMPLETE | NONE | NONE | Result remains request-owned until take-result. RCODE is read only through existing result accessor after take-result. |
| Correlated malformed UDP/TCP input or zero TCP frame | `RATOS_ERROR_PROTOCOL` | TERMINAL_ERROR | FAILED | NONE | MALFORMED_RESPONSE | No partial result. TCP count is only accepted prefix/body bytes required to establish terminal framing/parse failure. |
| Correlated configured resource limit | `RATOS_ERROR_PROTOCOL` (or existing `RATOS_ERROR_OUT_OF_MEMORY` only for allocator exhaustion) | TERMINAL_ERROR | FAILED | NONE | RESOURCE_LIMIT | No partial result. |
| Structurally valid excluded OPT/EDNS material | `RATOS_ERROR_UNSUPPORTED` | TERMINAL_ERROR | FAILED | NONE | UNSUPPORTED_EXTENSION | No partial result and no four-bit-RCODE downgrade. |
| Valid transport-failed call | `RATOS_ERROR_TIMEOUT` for TIMEOUT; `RATOS_ERROR_NETWORK` for NETWORK/CONNECT/EOF | TERMINAL_ERROR | FAILED | supplied reason | TRANSPORT | No partial result. |
| First or repeated valid cancel | `RATOS_OK` | CANCELLED | CANCELLED | NONE | CANCELLED | No result transfer. |

No valid DNS nonzero RCODE changes `ratos_error`, `event.error_class`, or `ratos_dns_request_error_class`: it is a complete structured result and remains observable by `ratos_dns_result_rcode` after `take_result`.

## 5. Ownership, lifecycle, and transport

A successful start returns an owned request; callers destroy it only with `ratos_dns_request_destroy`, never `free`. A COMPLETE request owns the result until `take_result`; taking moves ownership to the caller, which uses existing `ratos_dns_result_destroy`. Record, name, raw-RDATA, and existing result-string views are borrowed immutable result views and expire at result destruction. All terminal errors, ignored/pending events, cancellation, and destroyed untaken requests transfer no partial result.

The API has no callbacks. A request is single-driver: concurrent mutable calls (`receive_*`, `transport_failed`, `cancel`, `take_result`, `destroy`) on the same request are unsupported. Const accessors are permitted only when no mutable request call is active. Shared-context concurrency is not promised; callers serialize it unless a later documented context guarantee says otherwise. No user code is invoked by this surface.

UDP is one datagram per call. TCP input is accepted according to the approved model: at most one prefix-plus-frame, with a coalesced suffix caller-owned. Following correlated UDP TC, exactly one TCP fallback preserves query identity. Resource-limit, malformed, unsupported-extension, transport, cancellation, and complete paths release request transport/frame state according to their terminal outcome. No TCP-first, reuse, pipelining, retry, server rotation, EDNS, callback, or binding behavior is promised.

## 6. Evolution and review boundary

Capability discovery remains `uint64_t`; unknown bits are ignored. New type constants are additive and fixed-width. A later implementation must use only the declared append-only struct evolution scheme and must preserve all existing ABI-1 symbols, ownership, and result behavior. This candidate deliberately makes no ABI compatibility conclusion and does not authorize header realization.

The required next technical evidence is a fresh independent binding-safety review of this candidate against F-BIND-001 and F-BIND-002. An independent compatibility review remains mandatory and unperformed. Neither review is authored here.

## 7. Traceability

- Fixed-width event/state/failure/error-class and named accessor: DNS-REQ-017–025; model `ST-*`, `EVT-*`, `ERR-*`, and terminal-cleanup/atomic-publication invariants; resolves F-BIND-001.
- Event field-validity and output initialization: DNS-REQ-017–025 and model consumption/disposition rules; resolves F-BIND-001.
- UTF-8 C-string name and endpoint binary pointer/length/family/lifetime contract: DNS-REQ-002, DNS-REQ-004, DNS-REQ-013, DNS-REQ-017; resolves F-BIND-002.
- Opaque ownership, no callbacks, incremental TCP consumption, and valid nonzero RCODE result: DNS-REQ-015, DNS-REQ-018–023 and baseline ABI ownership/error rules.
