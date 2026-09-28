# DNS internal request-accounting design — G8 correction

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-design-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` internal ownership and accounting |
| Owner role | `protocol-api-designer/g8-accounting-design-001` |
| Status | `READY_FOR_REVIEW` candidate; not approval or implementation authority |
| Revision | Delivered by the assignment commit; exact Git revision is reported to `protocol-orchestrator`. |
| Source artifacts | G8 review/handoff `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; implementation blocker `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`; model `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; G4 design `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; candidate source `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`. |
| Assumptions | Existing callback-free single-driver request API; mutable use of one context and all requests attached to it is externally serialized; separate contexts remain concurrently usable. |
| Open questions | None blocking this candidate. Numeric limit policy and DNS-G8-001 defects remain outside this accounting correction. |
| Limitations | Design only. No source, header, test, vector, fuzzer, workflow-state, or review artifact changed. |

## 1. Disposition and invariants

This supplement resolves the design-authority gap behind `DNS-G8-002`. The process-global `context_requests` list is forbidden. All mutable tracking and counters are owned by one `ratos_context`; operations on distinct contexts therefore touch disjoint accounting state and require no process-global lock.

The implementation must preserve these invariants:

1. `context->dns_outstanding_requests` equals the number of attached requests that hold an outstanding slot.
2. `context->dns_connections` equals the number of attached requests that hold a TCP-connection slot. A UDP-pending request does not consume a connection slot.
3. Each request records its slot ownership explicitly. A slot is acquired and released at most once; cleanup is idempotent.
4. Every caller-owned request handle remains linked to its context until request destruction or context destruction, even after a terminal transition. This registry exists for safe context teardown; terminal requests do not retain accounting slots.
5. A request with `context == NULL` is detached and cannot perform further transport/parser work. It remains a valid caller-owned opaque handle until `ratos_dns_request_destroy`.
6. No terminal failure or cancellation has a takeable result. COMPLETE alone may retain one owned result until take-result or request destruction.
7. No unsynchronized process-global mutable resolver/request state exists.

These are private implementation invariants. They do not expose layout, add a symbol, or alter a public structure.

## 2. Context-owned representation

A later implementation must make the following private layout changes.

### `src/core/core_internal.h`

Extend private `struct ratos_context` with:

- `ratos_dns_request *dns_requests`: head of this context's intrusive list of all caller-owned DNS request handles still attached to the context;
- `size_t dns_outstanding_requests`: currently held outstanding slots;
- `size_t dns_connections`: currently held TCP-connection slots.

`ratos_dns_request` is already a public opaque forward declaration in `ratatoskr/dns.h`, so this does not expose or duplicate its layout. Zero initialization is the valid empty state.

### `src/protocols/dns/dns_internal.h`

Retain the private request's context pointer and replace the global-list-specific link with context-local intrusive-list state:

- `next_context_request` for the per-context list;
- one boolean-sized private flag for outstanding-slot ownership;
- one boolean-sized private flag for TCP-connection-slot ownership.

No public header field is added. The flags are authoritative for exact-once release; request state alone must not be used as a release guard because cleanup can be reached through multiple failure/destruction paths.

### `src/protocols/dns/dns_client.c`

Remove `static ratos_dns_request *context_requests` and `active_requests_for_context`. Add private helpers with the following responsibilities:

- attach a newly constructed request to `request->context->dns_requests`;
- acquire/release an outstanding slot;
- acquire/release a TCP connection slot;
- release all held slots on a terminal transition;
- unlink one request from its owning context;
- detach all requests during context destruction.

A singly linked context-local list is sufficient because same-context mutation is serialized. Unlink may scan only that context's list. Helpers must tolerate a detached request and must never underflow a counter.

### `src/core/context.c`

Before freeing a non-NULL context, invoke the DNS private teardown operation that detaches its request registry as specified in §4. Context creation requires no allocation beyond the existing zeroed context; both counters and the list start at zero/NULL. Existing DNS-limit initialization remains.

The implementation may name private fields/helpers differently, but the ownership, exact-once flags, states, and file boundary above are normative.

## 3. Accounting transition table

| Path | Required accounting and ownership behavior |
| --- | --- |
| Start: validation/allocation failure | Do not attach, acquire, or expose a request. `*out_request` remains NULL. |
| Start: outstanding cap already reached | Return the existing resource-exhaustion result used by the approved API realization; no request and no counter change. |
| Start: success | Construct/copy all request-owned data first. Then, while the same context is exclusively driven, acquire one outstanding slot, set its flag, attach to that context's list, set UDP_PENDING, and expose the handle. If any pre-exposure step fails, roll back all state. UDP start does not consume a connection slot. |
| Correlated UDP `TC=1` transition | Before entering TCP_PENDING or emitting NEED_TCP_FALLBACK, acquire one connection slot. If `dns_connections == request->limits.max_connections`, terminally fail as RESOURCE_LIMIT, publish no result, release the outstanding slot, and remain attached only for safe handle/context teardown. Otherwise set the connection flag/counter and enter TCP_PENDING. |
| Ignored/nonmatching UDP/TCP input or incomplete TCP input | No accounting change. |
| Successful completion | Publish the result atomically, enter COMPLETE, then release every held connection/outstanding slot exactly once. Keep the request handle attached until destruction/context teardown. |
| Parser, framing, resource, unsupported-extension, deadline, network, connect, or EOF failure | Destroy partial frame/result state, enter FAILED with the existing precise error class, publish no result, and release every held slot exactly once. Keep the handle attached. |
| Cancellation from a nonterminal state | Destroy frame and any unpublished partial result, enter CANCELLED with CANCELLED class, publish no result, and release every held slot exactly once. Keep the handle attached. Repeated cancellation is idempotent and changes no counter. |
| Take-result | Valid only from COMPLETE with a retained result. Transfer result ownership and set the request result pointer NULL. Counters were already released on completion, so take-result changes no accounting or list membership. |
| Request destruction while attached and nonterminal | Perform cancellation-equivalent cleanup without callback/event publication, release held slots, unlink from that context, clear `context`, then free request-owned storage and the handle. |
| Request destruction while attached and terminal | No slot release unless a defensive held flag reveals an invariant violation; unlink, clear `context`, destroy any untransferred result/storage, and free. |
| Request destruction after context teardown | `context` is NULL and flags are clear. Free request-owned storage/result and the handle without touching context memory. |

All slot release must be centralized. Completion, `request_fail`, cancellation, request destruction, and context teardown call the same private exact-once release helper rather than open-coding counter changes.

## 4. Context destruction with live requests

`ratos_context_destroy` remains a `void` destroy function, so it cannot reject destruction or report a new error. Requiring the caller to keep the context alive without enforcement would leave the current reachable UAF. The compatible safe behavior is therefore:

1. Same-context serialization applies: destroying a context concurrently with an operation on that context or any attached request is unsupported. Distinct-context operations remain supported concurrently.
2. Walk only `ctx->dns_requests`. For each attached request, save its next link before mutation.
3. If the request is UDP_PENDING or TCP_PENDING, perform cancellation-equivalent internal cleanup: destroy frame/partial result, set CANCELLED and CANCELLED error class, clear transport failure, and release held connection/outstanding slots. No callback exists and no event is emitted.
4. If the request is COMPLETE, FAILED, or CANCELLED, preserve its terminal state. A COMPLETE request keeps its already owned result so the caller may still take or destroy it after context destruction. Terminal requests must hold no accounting slots.
5. For every request, set `context=NULL` and `next_context_request=NULL`. Finally set the context list/counters to empty/zero and free the context.
6. The detached handle remains owned by its caller. State/error accessors and COMPLETE take-result remain valid. Mutable receive/transport operations cannot resume and return `RATOS_ERROR_INVALID_ARGUMENT` under their existing state/argument contract. `ratos_dns_request_destroy` remains required and safe.

This rule preserves caller ownership of opaque requests, avoids silently freeing a handle still held by the caller, avoids dangling context pointers, and needs no new public error or symbol. Decision record: `decisions/context-destroy-live-requests.md`.

## 5. Concurrency and reentrancy contract

- Distinct contexts: context lists and counters are disjoint. Request start, terminal transition, cancellation, take-result, and destruction on one context may execute concurrently with operations on another context. No global DNS tracker, mutex, or atomic shared head is permitted.
- Same context: callers serialize every mutable context operation and every mutable operation on requests attached to that context, including limits changes, starts, receive/transport events, cancellation, request destruction, synchronous query use, and context destruction. The implementation need not add a same-context mutex.
- Same request: remains callback-free and single-driver. Concurrent mutation or mutation concurrent with destruction is unsupported.
- Reentrancy: these paths invoke no user callback. Internal helpers must not call a public request operation while list/counter mutation is in progress.
- Lifetime: while attached, the context holds only a registry reference, not public ownership of the request handle. Context destruction detaches but does not free handles. Request destruction removes the final caller-owned handle.

## 6. Limits and terminal/no-result behavior

`max_outstanding_requests` and `max_connections` are per-context effective limits copied into each request at start, as already approved. A successful start consumes one outstanding slot. Only TCP fallback consumes one connection slot. Thus UDP work is not incorrectly limited by the TCP-connection budget, and UDP-to-TCP admission is checked at the transition where a connection is needed.

A cap refusal before request creation exposes no handle. A connection-cap refusal after correlated TC is a terminal RESOURCE_LIMIT outcome, publishes no result, releases the request's outstanding slot, and leaves the caller-owned terminal handle available for error inspection/destruction. Completion releases capacity before take-result so result ownership cannot pin request/connection capacity. Failure, cancellation, and destruction cannot leak or double-release capacity.

This supplement does not change the ordered parser disposition partition or resolve separate `DNS-G8-001` parser/UDP-admission defects.

## 7. API/ABI and evidence impact

### Public compatibility

The approved G4 public declarations and ABI-1 layouts are unchanged. `ratos_context` and `ratos_dns_request` remain opaque; only private layouts and private helpers change. No symbol, public struct, enum value, ownership transfer, calling convention, or ABI generation changes. The context-destroy rule completes an omitted safety case while preserving caller ownership of request handles.

### Existing evidence

- G4: public ABI compatibility evidence remains applicable to the unchanged declarations, but it did not approve this internal context-destruction/accounting supplement. Before implementation, a fresh independent `binding-api-designer` must review request/result usability after context destruction and a fresh independent `compatibility-reviewer` must confirm no public ABI or incompatible ownership change.
- G5: canonical wire/event vectors are not stale because no DNS wire behavior, parser disposition, or public event shape changes. Additional lifecycle/concurrency tests are implementation evidence, not new canonical protocol truth.
- G6: the prior implementation-readiness authorization is stale for this correction because its candidate and writable paths did not include the supplemental design or `src/core/core_internal.h` and `src/core/context.c`. Only `protocol-orchestrator` may renew G6 after the independent reviews.
- G7: the approval for `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` does not cover a future implementation. A fresh independent G7 must test/account for this candidate.
- G8: remains CHANGES_REQUESTED. A fresh independent G8 must verify `DNS-G8-002` and the complete corrective candidate after fresh G7.

## 8. Minimum review and implementation route

Before implementation routing:

1. fresh independent `binding-api-designer` review of opaque-handle representability and post-context-destroy lifetime;
2. fresh independent `compatibility-reviewer` scoped confirmation that the private correction preserves ABI-1 and existing public ownership; and
3. `protocol-orchestrator` synthesis/renewed G6 authority for the exact candidate and paths.

If approved, the narrow accounting implementation write scope is exactly:

- `src/core/core_internal.h`;
- `src/core/context.c`;
- `src/protocols/dns/dns_internal.h`;
- `src/protocols/dns/dns_client.c`;
- one new, uniquely assigned c-protocol-implementer workspace for its implementation report, handoff, and completion report; and
- only explicitly named destination-handoff Resolution sections.

No public header, parser, transport, test, vector, fuzzer, build, documentation, prior review, or workflow-root write is authorized by this design. If the orchestrator combines `DNS-G8-001` remediation, it must separately enumerate that finding's already-identified implementation paths; this design does not silently authorize them.

Fresh independent G7 must cover at least: start cap/rollback; UDP-to-TCP connection admission; all terminal releases; take-result non-accounting; destruction in every state; context destruction with pending and COMPLETE requests; repeated cleanup; cap reuse; and concurrent start/destroy stress on distinct contexts, with race-detector evidence where available. Only after G7 approval may a fresh independent G8 verify absence of global mutable tracking, per-context cap correctness, teardown safety, and `DNS-G8-002` closure.

## 9. Traceability to DNS-G8-002 acceptance paths

| Acceptance path | Design section |
| --- | --- |
| No unsynchronized process-global tracker | §§1–2, 5 |
| Start accounting | §3 start rows |
| UDP-to-TCP transition | §§3, 6 |
| Completion/failure/cancellation | §3 terminal rows |
| Take-result | §3 take-result row |
| Request destruction | §3 destruction rows |
| Context destruction with live request | §4 |
| Distinct-context concurrency | §5 |
| Per-context outstanding/connection caps | §§1, 6 |
| Terminal/no-result behavior | §§3, 6 |
| Fresh G7 then G8 | §§7–8 |
