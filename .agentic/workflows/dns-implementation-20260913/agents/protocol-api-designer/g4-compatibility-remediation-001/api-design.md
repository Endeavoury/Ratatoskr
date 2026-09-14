# DNS native API design — compatibility remediation (G4)

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-api-design-g4-compatibility-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `READY_FOR_REVIEW` candidate; neither header realization nor G4 approval |
| Revision | This candidate's Git delivery revision and SHA-256 are recorded by the companion completion report after wrapper-mediated delivery. |
| Source artifacts | Compatibility delivery `0cb6e27b265c38e42d09d61c0883f1a086df8835`; superseded immutable candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0` / SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b`; analysis `5615caed0b7ad0a321d6794e71b79c4195e90384`. |
| Assumptions | One callback-free, single-driver unicast DNS request; UDP first and TCP only after correlated UDP TC; OS owns socket mechanics. |
| Open questions | Numeric resource defaults remain maintainer product policy in `handoffs/maintainer-resource-policy.md`. |
| Limitations | Design only: no headers/code, vectors, tests, bindings, documentation, implementation, review, or workflow-state change. |

## 1. Corrective disposition

This replacement candidate resolves `C-COMP-001` without changing ABI-1 baseline declarations. It replaces the invalid accessor name `ratos_dns_request_state` with **`ratos_dns_request_get_state`**; the fixed-width typedef remains `ratos_dns_request_state`. These ordinary C identifiers are distinct. It also fully defines the two previously omitted public versioned input structures, their initialization, copying, validation, and evolution rules.

Existing `ratos_dns_query`, `ratos_dns_query_options`, `ratos_dns_result`, result ownership, borrowed result views, error conventions, and synchronous DNS behavior are unchanged. The proposed request API is additive only and remains callback-free. A later approved header realization may add symbols but must not alter, remove, reorder, or rename baseline ABI-1 declarations.

## 2. Common ABI rules

All proposed public structs have `uint32_t struct_size` as their first mandatory field and use only fixed-width scalar fields and pointers. They are not packed and no cross-compiler universal `sizeof` is promised. Callers allocate their own compiled struct, call the relevant initializer before use, and pass `struct_size == sizeof(their compiled struct)`.

An implementation reads only fields fully covered by `struct_size`, ignores an unknown appended tail, and never reads beyond it. A size smaller than the documented mandatory prefix is `RATOS_ERROR_INVALID_ARGUMENT`. Reserved scalars and arrays must be zero on input; nonzero reserved input is invalid argument; output reserved fields are always zero. New ABI-1 fields may only be appended after the current final field. Removing, reordering, changing the type/meaning/lifetime of an existing field, or consuming reserved space changes the ABI contract and requires a new ABI generation.

Input pointer ownership is never transferred: valid input structures and their pointed-to values are borrowed for the duration of the called function only. The library copies accepted scalar configuration and never retains an options/limits/name/endpoint pointer. A NULL struct pointer is not an implicit default; where an options or limits parameter is required, NULL is `RATOS_ERROR_INVALID_ARGUMENT`.

## 3. Complete request-options contract

```c
typedef struct ratos_dns_request_options {
    uint32_t struct_size;
    const ratos_dns_endpoint *upstream;
    uint64_t deadline_monotonic_ns;
    uint8_t recursion_desired;
    uint8_t reserved0[7];
    uint64_t reserved[2];
} ratos_dns_request_options;

RATOS_API void ratos_dns_request_options_init(ratos_dns_request_options *options);
```

Field order above is normative. `upstream` is required at request start: it points to a complete initialized `ratos_dns_endpoint`, including caller-owned binary address bytes, and is borrowed only through `ratos_dns_request_start`; neither pointer nor address storage is retained. `deadline_monotonic_ns` is a caller-provided absolute monotonic-clock deadline; `0` means the implementation-selected default deadline source rather than a numeric duration. `recursion_desired` accepts only `0` or `1`; `1` requests RD and `0` omits RD. The initializer requires non-NULL storage and sets current `struct_size`, `upstream=NULL`, `deadline_monotonic_ns=0`, `recursion_desired=1`, and all reserved bytes/words to zero.

`start` rejects NULL options, undersized `struct_size`, NULL/invalid upstream, nonzero reserved data, non-boolean recursion value, or a deadline that is already expired according to the implementation's documented monotonic-clock comparison. On rejection it sends no packet, creates no request, and leaves `*out_request==NULL`. On acceptance it copies all defined values needed for the request and does not retain any caller pointer.

`ratos_dns_endpoint` remains as specified by the prior candidate: `struct_size`, fixed-width family, host-order `uint16_t port`, `const uint8_t *address`, `uint32_t address_len`, reserved zero fields. IPv4 requires four bytes and IPv6 sixteen bytes in network byte order. It is initialized by `ratos_dns_endpoint_init`; the endpoint and bytes are borrowed only for the call that consumes them.

## 4. Complete limits contract

```c
typedef struct ratos_dns_limits {
    uint32_t struct_size;
    uint32_t max_udp_message_bytes;
    uint32_t max_tcp_frame_bytes;
    uint32_t max_total_rrs;
    uint32_t max_name_expansion_bytes;
    uint32_t max_compression_pointer_traversals;
    uint32_t max_typed_field_bytes;
    uint32_t max_outstanding_requests;
    uint32_t max_connections;
    uint32_t reserved0;
    uint64_t reserved[2];
} ratos_dns_limits;

RATOS_API void ratos_dns_limits_init(ratos_dns_limits *limits);
RATOS_API ratos_error ratos_dns_context_set_dns_limits(
    ratos_context *context, const ratos_dns_limits *limits);
```

Field order is normative. The limits respectively bound admitted UDP message bytes, a TCP frame body, cumulative RR/count work, expanded DNS-name bytes, compression-pointer traversal work, typed-field/string bytes, concurrent DNS requests, and DNS connections. A field value of `0` means “use the implementation-selected documented default for this field”; it never means unlimited. The initializer requires non-NULL storage, writes current `struct_size`, writes `0` to every configurable limit to select that default source, and zeroes reserved fields.

No numeric value is selected by this design: analysis/model declare numeric budgets to be product policy, not protocol law. The later realization must document selected defaults and enforce protocol maxima (including no TCP frame above the DNS 65,535-octet wire maximum). The maintainer handoff records that unresolved policy. Explicit nonzero values are valid only when they are internally coherent for the selected profile and do not exceed a documented implementation hard maximum; otherwise `set_dns_limits` returns `RATOS_ERROR_INVALID_ARGUMENT`. An accepted limits struct is copied and no pointer is retained. It governs requests started after successful setting; a request already started keeps its copied effective limits. A failed set leaves the context's existing configured limits unchanged.

`context` and `limits` are required. The operation validates all fields, `struct_size`, and reserved zeros before changing configuration. Concurrent use of the same context is not promised; callers serialize `set_dns_limits` with starts and other mutable context operations. Resource exhaustion during a request reports the existing terminal resource-limit design outcome; it transfers no partial result.

## 5. Corrected affected signatures and full proposed operations

The following declarations are the complete affected signature set for this correction; API-DNS-008 is intentionally renamed and APIs 001/002/012 now reference fully defined types.

```c
RATOS_API void ratos_dns_request_options_init(ratos_dns_request_options *options);
RATOS_API ratos_error ratos_dns_request_start(
    ratos_context *context, const char *name,
    const ratos_dns_request_options *options,
    ratos_dns_request **out_request);
RATOS_API ratos_dns_request_state ratos_dns_request_get_state(
    const ratos_dns_request *request);
RATOS_API void ratos_dns_limits_init(ratos_dns_limits *limits);
RATOS_API ratos_error ratos_dns_context_set_dns_limits(
    ratos_context *context, const ratos_dns_limits *limits);
```

For completeness, all remaining proposed request operations retain their prior names and contracts:

```c
RATOS_API ratos_error ratos_dns_request_receive_udp(
    ratos_dns_request *request, const uint8_t *datagram, size_t datagram_len,
    const ratos_dns_endpoint *peer, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_receive_tcp(
    ratos_dns_request *request, const uint8_t *bytes, size_t bytes_len,
    size_t *out_consumed, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_transport_failed(
    ratos_dns_request *request, ratos_dns_transport_failure why,
    ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_cancel(
    ratos_dns_request *request, ratos_dns_event *event);
RATOS_API ratos_error ratos_dns_request_take_result(
    ratos_dns_request *request, ratos_dns_result **out_result);
RATOS_API ratos_dns_error_class ratos_dns_request_error_class(
    const ratos_dns_request *request);
RATOS_API ratos_dns_transport_failure ratos_dns_request_transport_failure(
    const ratos_dns_request *request);
RATOS_API void ratos_dns_request_destroy(ratos_dns_request *request);
RATOS_API uint64_t ratos_dns_capabilities(void);
```

`start` requires a non-NULL UTF-8 NUL-terminated `name`, borrows it for the call, initializes `*out_request=NULL` before validation, returns one owned request only on `RATOS_OK`, and sends no I/O on local validation failure. Request accessors require non-NULL request input. Destroy accepts NULL. `take_result` initializes `*out_result=NULL` and transfers the sole owned result only from COMPLETE; callers destroy it through existing `ratos_dns_result_destroy`. Result records, strings, and raw bytes retain baseline borrowed immutable lifetime.

## 6. Behavior, lifecycle, and compatibility

The request is single-driver and has no callbacks: concurrent mutable calls on one request are unsupported; callers serialize mutable use of a context unless a later contract promises otherwise. UDP receives one complete datagram per call. Only a correlated UDP response with TC transitions to TCP_PENDING. TCP accepts at most one length-prefixed frame per call and reports exact consumed leading bytes; caller-owned suffix remains unconsumed. Valid nonzero DNS RCODE remains a complete structured `ratos_dns_result`, not a transport/parser error. Malformed, resource-limit, unsupported-extension, transport, and cancellation terminal paths expose no partial result.

This is ABI-1 additive intent only. Existing synchronous `ratos_dns_query` behavior remains intact and is not redirected through the new request API by this design. No deprecation, migration, ABI-version increment, binding target, retry/server-selection policy, or numeric resource policy is selected. Fresh independent compatibility review must evaluate the new immutable candidate; this author does not approve it.

## 7. Traceability

- `C-COMP-001`: distinct ordinary identifiers and complete public options/limits layouts.
- `DNS-REQ-004`, `DNS-REQ-017`–`024`: request lifecycle, endpoint/deadline, TCP consumption, terminal cleanup, and limits.
- ABI baseline: opaque ownership, `struct_size` evolution, additive ABI-1 symbols, and unchanged synchronous query/result contracts.
