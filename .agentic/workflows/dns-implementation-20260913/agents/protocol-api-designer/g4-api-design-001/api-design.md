# DNS native API design proposal (G4)

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-api-design-g4-api-design-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `READY_FOR_REVIEW` candidate; not approved ABI |
| Revision | Working candidate; Git delivery revision is recorded in `completion-report.md` |
| Source artifacts | G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b` / SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; analysis `5615caed0b7ad0a321d6794e71b79c4195e90384` / SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`; G3 approval delivery `865fa190ee19e041c5ddfab8279b49829baaa240`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` |
| Assumptions | UDP-first, one unicast stub/client transaction; TCP only after correlated UDP TC; OS owns socket mechanics. |
| Open questions | Numeric resource defaults, retry/server selection, and a future binding exposure remain product decisions. |
| Limitations | Proposal only. No public header/API, implementation, vector, test, binding, documentation, configuration, or workflow state is changed. |

## 1. Design position

The existing synchronous `ratos_dns_query` remains ABI 1 and is not redefined. This proposal adds an **opt-in additive asynchronous transaction surface** for the approved model. It expresses one outstanding query per `ratos_dns_request`; it does not promise TCP-first, TCP reuse, pipelining, retries, server rotation, callbacks, or EDNS.

The API must use opaque types, `ratos_*` names, fixed-width scalar fields, `struct_size`-guarded option/config structs, and additive symbols. A later approved implementation may expose the listed symbols in ABI 1 only as additive exports; any incompatible field/order/lifetime change requires a new ABI generation and shared-library major version.

### Capability bits

`ratos_dns_capabilities()` returns a `uint64_t` bitset. Unknown bits are ignored by callers. This candidate defines:

- `RATOS_DNS_CAP_UDP_UNICAST_QUERY`: standard single UDP query.
- `RATOS_DNS_CAP_TCP_AFTER_UDP_TC`: TCP fallback only after correlated UDP TC.
- `RATOS_DNS_CAP_INCREMENTAL_TCP_INPUT`: byte-at-a-time-to-frame incremental consume/report operation.
- `RATOS_DNS_CAP_REQUEST_CANCELLATION`: explicit terminal cancellation.
- `RATOS_DNS_CAP_RESOURCE_CONFIGURATION`: limits struct accepted.
- `RATOS_DNS_CAP_OPAQUE_ORDINARY_RDATA`: unknown ordinary RR raw RDATA retained.

No bit means unsupported; unsupported optional operations return `RATOS_ERROR_UNSUPPORTED` with no output ownership transfer. No bits are proposed for EDNS/OPT, extended RCODE, DNSSEC validation, encrypted DNS, TCP-first, reuse, pipelining, retries, server selection, callbacks, or bindings.

## 2. Proposed types and operations

Names below are proposed header declarations, not edits.

| ID | Proposed operation | Model/requirement mapping | Contract |
| --- | --- | --- | --- |
| API-DNS-001 | `ratos_dns_request_options_init(ratos_dns_request_options *o)` | ENT-QUERY-INTENT; DNS-REQ-001–005 | Required initializer. Sets `struct_size`, zeros reserved fields, and selects no hidden callback. Caller-owned `o` is writable only for call duration. |
| API-DNS-002 | `ratos_dns_request_start(ratos_context *ctx, const char *name, const ratos_dns_request_options *o, ratos_dns_request **out)` | TR-VALIDATE-AND-BUILD, TR-SEND-UDP; DNS-REQ-001–005, 017, 022 | Validates before I/O, creates owned request, emits exactly one UDP datagram through the selected OS transport adapter, then returns pending. It does not synchronously publish a result. |
| API-DNS-003 | `ratos_dns_request_receive_udp(ratos_dns_request *r, const uint8_t *datagram, size_t datagram_len, const ratos_dns_endpoint *peer, ratos_dns_event *event)` | EVT-UDP-DATAGRAM; TR-IGNORE-NONMATCHING-UDP, TR-UDP-MALFORMED, TR-UDP-TC-FALLBACK, TR-UDP-PUBLISH | One complete datagram only. The byte range is borrowed for the call. Reports ignored/pending, TCP-fallback-needed, complete, or terminal failure. |
| API-DNS-004 | `ratos_dns_request_receive_tcp(ratos_dns_request *r, const uint8_t *bytes, size_t bytes_len, size_t *out_consumed, ratos_dns_event *event)` | DOM-CONSUMPTION; EVT-TCP-BYTES; TR-TCP-* | Incrementally accepts at most one prefix-plus-frame. `out_consumed` precisely reports accepted leading bytes; suffix remains caller-owned. No DNS decode before a full frame. |
| API-DNS-005 | `ratos_dns_request_transport_failed(ratos_dns_request *r, ratos_dns_transport_failure why, ratos_dns_event *event)` | EVT-DEADLINE-OR-NETWORK-FAILURE; TR-TERMINAL-ERROR | Records deadline/network/connect/EOF terminal failure, releases request-owned transport state, publishes no result. |
| API-DNS-006 | `ratos_dns_request_cancel(ratos_dns_request *r)` | EVT-CANCEL; TR-CANCEL | Idempotent terminal action. Releases request context and buffers, transfers no result, and performs no callback. |
| API-DNS-007 | `ratos_dns_request_take_result(ratos_dns_request *r, ratos_dns_result **out_result)` | ENT-OWNED-RESULT; INV-ATOMIC-PUBLICATION | Legal only after COMPLETE. Moves the sole owned result to caller and clears request ownership. |
| API-DNS-008 | `ratos_dns_request_state(const ratos_dns_request *r)` and `ratos_dns_request_last_error(const ratos_dns_request *r)` | ST-*; ERR-* | Read-only state/error observation. Terminal status is stable until destruction. |
| API-DNS-009 | `ratos_dns_request_destroy(ratos_dns_request *r)` | INV-TERMINAL-CLEANUP | Accepts NULL. Cancels a nonterminal request as destruction cleanup; destroys any untaken result. |
| API-DNS-010 | `ratos_dns_limits_init(ratos_dns_limits *l)` and `ratos_dns_context_set_dns_limits(ratos_context *ctx, const ratos_dns_limits *l)` | INV-BOUNDED-PARSING; DNS-REQ-024 | Configures future requests only. Limits are copied, never borrowed after return. |
| API-DNS-011 | `ratos_dns_capabilities(void)` | EXT-*; DNS-REQ-021, 025–027 | Runtime feature discovery for optional/additive behavior. |

`ratos_dns_endpoint` is a fixed-layout versioned input struct (address bytes, address family, port, `struct_size`, reserved fields), not an opaque platform socket address. It lets callers provide/verify peer and local endpoint facts without exposing socket handles or platform ABI layouts. Address byte pointer inputs are explicitly length-delimited; NUL termination is never inferred for binary input.

## 3. Ownership, borrowing, allocation, and outputs

| Object / output | Owner and validity | Failure / destruction rule |
| --- | --- | --- |
| `ratos_context` | Caller-owned existing opaque context. | Existing context rules apply; a context must outlive every request created from it. |
| `ratos_dns_request` | Owned by caller after successful `start`; no copying or `free`. | `destroy(NULL)` is allowed. Destroy cancels and frees all retained transport/frame state and any untaken result. |
| `ratos_dns_result` | Request owns it after COMPLETE; `take_result` transfers sole ownership to caller. Existing `ratos_dns_result_destroy` frees it. | On every error/cancel/ignored/pending event, `*out_result` is NULL and no partial result is exposed. |
| record/name/string/raw-RDATA views | Borrowed immutable views from an owned result, as in existing ABI. | Valid only until result destruction; never retained by request after transfer. Raw RDATA accessor continues to return pointer plus explicit `size_t` length. |
| `name`, input datagram/frame bytes, endpoint address bytes, options | Borrowed only for their corresponding call; no pointer retention. | Invalid pointer/length pair returns invalid argument before state change where possible. `NULL` byte pointer is valid only with zero length. |
| `out`, `event`, `out_consumed` | Caller storage; required non-NULL where listed. | Before each call, implementation initializes outputs: result NULL, consumed 0, event `RATOS_DNS_EVENT_NONE`. On error, only documented scalar event/error fields may be observed. |
| limits/options | Caller initializes with init helper; implementation copies accepted fields and ignores appended unknown tail bytes using `struct_size`. | Reserved input bytes must be zero; nonzero returns invalid argument. |

Allocator failure is `RATOS_ERROR_OUT_OF_MEMORY`; the request becomes terminal FAILED only when a started request cannot preserve semantic state. No partial record/result is observable. A synchronous existing `ratos_dns_query` result follows unchanged baseline ownership.

## 4. Event, error, and output-validity contract

`ratos_dns_event` is a fixed-width enum: `NONE`, `PENDING`, `IGNORED_NONMATCHING`, `NEED_TCP_FALLBACK`, `COMPLETE`, `TERMINAL_ERROR`, `CANCELLED`. `event` contains only scalar status/classification fields and never borrowed payload pointers.

| Situation | Return / event | Request state | Valid outputs |
| --- | --- | --- | --- |
| Invalid local name/type/options/endpoint before start | `RATOS_ERROR_INVALID_ARGUMENT` or `RATOS_ERROR_UNSUPPORTED` | no request created | `*out == NULL`; no I/O. |
| Valid start | `RATOS_OK`, `PENDING` | UDP_PENDING | owned request only; no result. |
| Nonmatching UDP/TCP frame | `RATOS_OK`, `IGNORED_NONMATCHING` | unchanged pending | consumed per transport rule; no result/error terminalization. |
| Incomplete TCP prefix/body | `RATOS_OK`, `PENDING` | TCP_PENDING | `out_consumed` equals all accepted incomplete bytes; no result. |
| Correlated UDP TC | `RATOS_OK`, `NEED_TCP_FALLBACK` | TCP_PENDING | partial UDP content is discarded; no result. Transport adapter may begin exactly one TCP fallback. |
| Complete correlated structural response, including nonzero base RCODE | `RATOS_OK`, `COMPLETE` | COMPLETE | result is held by request; caller uses `take_result`. Base RCODE and AA/TC/RD/RA/AD/CD are result metadata. |
| Correlated malformed input | `RATOS_ERROR_PROTOCOL`, `TERMINAL_ERROR` | FAILED | `out_consumed` only as specified; no partial result. |
| Resource limit | `RATOS_ERROR_OUT_OF_MEMORY` only for allocator exhaustion; otherwise `RATOS_ERROR_PROTOCOL` plus DNS error class `RESOURCE_LIMIT` | FAILED | no partial result. Exact stable error-code addition requires compatibility review; do not overload success. |
| Structurally valid OPT/EDNS | `RATOS_ERROR_UNSUPPORTED`, `TERMINAL_ERROR` | FAILED | DNS error class `UNSUPPORTED_EXTENSION`; no result and no four-bit RCODE downgrade. |
| Deadline/network/connect/EOF | `RATOS_ERROR_TIMEOUT` or `RATOS_ERROR_NETWORK`, `TERMINAL_ERROR` | FAILED | no result. |
| Cancel | `RATOS_OK`, later state CANCELLED | CANCELLED | no result. Repeated cancel/destroy is safe. |

The baseline `RATOS_ERROR_DNS` is not used to turn a valid DNS nonzero RCODE into an API failure: a full correlated response is `RATOS_OK`/COMPLETE and exposes `ratos_dns_result_rcode`. This preserves the ABI contract and authority/additional records for NXDOMAIN, SERVFAIL, or REFUSED.

## 5. Incremental transport and session behavior

- `start` is UDP-first only. The implementation/adapter owns socket mechanics and a request’s selected peer/local endpoint/deadline correlation facts; this ABI does not expose sockets.
- `receive_udp` consumes the complete supplied datagram conceptually. A nonmatching datagram is ignored and cannot poison another request. A matching terminal disposition releases context/buffers.
- After correlated UDP TC, the API reports `NEED_TCP_FALLBACK`; it does not publish truncated content. TCP starts with the preserved request identity.
- `receive_tcp` is only valid in TCP_PENDING. It accepts the shortest leading sequence needed to complete the prefix/body, never more than one frame. On incomplete input, it consumes all supplied bytes that belong to that incomplete frame. On completed frame it consumes exactly prefix+declared body; a coalesced suffix remains caller-owned. Zero frame length, limit exceedance, or EOF midframe is terminal.
- For a completed correlated TCP frame, classification is exactly: resource limit, malformed, unsupported OPT/EDNS, then publish. Each terminal failure drops partial records, frame accumulator, request context, and transport buffers. A completed nonmatching frame is discarded and leaves the request pending.
- No TCP connection reuse/pipelining or multi-request dispatcher is represented. Adding either requires a new model/design review because correlation and cancellation become shared-session behavior.

## 6. Cancellation, callbacks, reentrancy, and threading

This candidate deliberately proposes **no callbacks**. Completion is observed through explicit feed/transport-failure calls and state/event inspection, avoiding an ABI-owned callback lifetime, reentrancy, or foreign-runtime thread attachment problem.

A request is single-driver: callers must not concurrently invoke any mutable request operation (`receive_*`, `transport_failed`, `cancel`, `take_result`, `destroy`) on the same request. Const observation is permitted only when no mutable operation is concurrently active. Different requests may run concurrently when their shared context is documented thread-safe; until that context guarantee is separately established, context use is externally serialized. An implementation must not invoke user code while holding request/context state. Calling `destroy` or `cancel` from another thread racing a feed operation is unsupported rather than best-effort.

## 7. Resource configuration

`ratos_dns_limits` is a `struct_size`-versioned fixed-width input with fields for maximum UDP bytes, TCP frame bytes, total RR work, expanded-name bytes, pointer traversals, typed-field/string bytes, outstanding requests, and TCP connections. Zero means “library default”; a nonzero protocol frame maximum above 65535 is rejected. The init helper supplies current defaults, and a later documentation/compatibility stage must publish their numeric values and supported ranges. This proposal does not invent them.

Limits are checked before read, allocation, indexing, pointer dereference, iteration, or copy. A limit applies to a request snapshot at start, so changing context limits cannot mutate an outstanding transaction. Exceeding a configured limit is a terminal no-result outcome distinct from malformed input and allocator exhaustion.

## 8. ABI evolution and compatibility

1. Preserve existing `ratos_dns_query_options`, `ratos_dns_query`, result/record accessors, result ownership, and current ABI 1 behavior.
2. Add only new symbols and named constants in ABI 1. Use opaque request types and append-only `struct_size` input structs. Do not expose private parser, socket, allocator, or record layouts.
3. `ratos_dns_capabilities()` is the forward-compatible detector. Callers must treat absent/unknown capability bits and unknown event/error-class values conservatively.
4. New semantic error classifications should be a separate fixed-width DNS error-class accessor/event field, not a reorder of `ratos_error`. If an added stable `ratos_error` enum value is judged unsafe for existing binding code generation, retain the baseline return error and use the classification accessor; compatibility reviewer decides before header realization.
5. Adding EDNS, extended RCODE, typed RDATA, retries, TCP reuse/pipelining, callbacks, encrypted transports, or binding surfaces needs capability bits, scope/source/model revision, API review, vectors, and compatibility review. No ABI promise is made by this candidate.

## 9. Traceability summary

- Query validation/build and fixed-width options: DNS-REQ-001–005 → API-DNS-001/002.
- Structural parsing, names, RRs, correlation, metadata, no partial results: DNS-REQ-006–016 → API-DNS-003/004/007/008 plus ownership/event rules.
- UDP, TCP fallback, incremental consumption, cancellation/lifecycle: DNS-REQ-017–023 → API-DNS-002–009 and sections 4–6.
- Limits and excluded OPT/EDNS: DNS-REQ-024–025 → API-DNS-010/011 and sections 4, 7, 8.
- Excluded opcode/security scope: DNS-REQ-026–027 → capability exclusions and result/error separation.

## 10. G4 review focus

The designated independent binding-api-designer and compatibility-reviewer should verify that: opaque request/result ownership and pointer validity are representable; no callback/thread-affinity hazard is hidden; every feed/error path initializes outputs and states consumption; a valid nonzero RCODE remains inspectable; limit/default/version semantics are explicit; existing ABI 1 is preserved; and additive capability detection safely describes every excluded/deferred feature.