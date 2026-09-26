# G4-supporting G8 accounting binding lifetime review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g4-g8-accounting-binding-lifetime-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` opaque request/result lifetime and ABI-1 representation |
| Reviewer role | `binding-api-designer/g8-accounting-lifetime-review-001` |
| Status | `APPROVED` — scoped binding-lifetime disposition only |
| Subject revision | `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Subject files | `agents/protocol-api-designer/g8-accounting-design-001/{api-design.md,decisions/context-destroy-live-requests.md,handoffs/accounting-design-to-protocol-orchestrator.md,completion-report.md}` at the subject revision |
| Supporting inputs | Approved model `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; prior G4 candidate `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; G8 reviewer delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; implementation blocker delivery `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`; `docs/abi.md`; public declarations under `include/ratatoskr/`. |
| Assumptions | The specified implementation realizes the private detachment/exact-once contract and keeps same-context mutation externally serialized. |
| Open questions | None for this scoped representability review. |
| Limitations | This does not approve G4, compatibility, renewed G6, implementation, G7, G8, or binding exposure. |

## Reviewer independence and immutable-input verification

Fresh session identity: `binding-api-designer/g8-accounting-lifetime-review-001`; active role declared before review. The candidate author is `protocol-api-designer/g8-accounting-design-001`, a distinct role/assignment/session. This reviewer did not author the candidate and reviewed the immutable commit rather than a worktree substitute.

Wrapper-mediated `merge-base --is-ancestor` checks succeeded for the subject and every named supporting commit against `origin/hermes/dns-implementation-20260913`: `4a37fc293c842b206190bad369e2a3e1ad00008c`, `f26745472178649a60f2cb079937d1bbe3f13c0b`, `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, `844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`, and `d46df3b86118ab0a7bda8aef6953ac26ec937164`. Wrapper reads of all four exact subject files at `4a37fc…00008c` succeeded. The subject diff adds only the candidate workspace plus a permitted resolution in the implementation blocker workspace; it changes no public declaration.

## Findings and binding-lifetime judgment

### BLR-001 — post-context-destroy handles are representable

**Disposition: PASS.** The candidate makes the critical ownership boundary explicit: context destruction detaches, but never frees, caller-owned opaque `ratos_dns_request` handles. Each detached request has `context=NULL`, clear registry linkage, and no held accounting flags. Consequently `ratos_dns_request_get_state`, `ratos_dns_request_error_class`, and `ratos_dns_request_transport_failure` can read request-local fields without dereferencing freed context storage. This is representable by FFI wrappers as a still-owned request object whose terminal inspection and destruction remain safe.

For a COMPLETE request, `ratos_dns_request_take_result` transfers its retained owned `ratos_dns_result` after context destruction. The private result layout at the reviewed revision owns its result strings, records, and record payloads; it contains no context pointer. The design preserves that result rather than converting it into context-borrowed storage. Therefore the returned result remains a normal owned opaque result whose borrowed record/string accessors are bounded by the result lifetime, not the destroyed context lifetime. Request destruction after detachment frees only request-owned storage and any untransferred result, without context access.

For UDP_PENDING/TCP_PENDING requests, teardown produces CANCELLED/no-result and releases slots. For FAILED/CANCELLED requests, terminal state/error remains inspectable and no takeable result exists. Further receive/transport mutation is explicitly non-resumable and must return the existing invalid-argument outcome; bindings must expose that as an operation failure, not retain a live transport capability.

### BLR-002 — ownership and exact-once accounting remain compatible with opaque handles

**Disposition: PASS.** The context registry is explicitly not a public ownership transfer or reference that allows context destruction to reclaim caller handles. It is a private reachability list used solely to detach safely. The candidate separates three lifetimes: caller-owned request handle; optional caller-takeable COMPLETE result; and context-owned accounting/transport association. That separation is safe to represent in bindings without finalizer races caused by native context teardown, provided bindings retain the documented same-context serialization rule.

The ownership flags make counter release independent of public request state. Start publishes only after allocation/copy/attach succeeds; terminal completion/failure/cancellation releases capacity exactly once; take-result changes neither accounting nor attachment; destruction uses the same cleanup discipline. A terminal resource-limit rejection after TCP fallback has no result but retains an inspectable/destroyable request handle. This behavior neither forces a binding to manufacture a result nor transfers ownership implicitly.

### BLR-003 — ABI-1 surface and compatibility boundary

**Disposition: PASS, scoped.** At the exact candidate commit, public `include/ratatoskr/context.h` and `include/ratatoskr/dns.h` retain opaque `ratos_context`, `ratos_dns_request`, and `ratos_dns_result` declarations, and the existing function signatures/calling conventions. The candidate diff contains no public header, exported symbol, public struct, enum, or ABI-version change. Private `ratos_context` and request layouts may change without exposing layout to callers. This aligns with `docs/abi.md`: ABI-1 must not change ownership transfer or expose private layouts.

The design does clarify a previously unsafe/unsettled destruction case. Its safe implementation preserves—not reverses—caller ownership: context destroy cannot free retained request handles; COMPLETE result ownership survives; request destruction remains required. This reviewer finds that clarification safely representable, but it is not a substitute for the separately designated compatibility review of ABI/API/behavioral compatibility.

### BLR-004 — registry lifecycle and concurrency contract

**Disposition: PASS.** Registry and counters are per-context private state. Attachment happens before handle exposure; terminal requests remain attached only for teardown reachability; request destruction unlinks; context destruction walks the local list, clears each request’s context/link, clears flags/counters, then frees the context. This avoids a dangling context pointer and forbids the prior process-global mutable tracker.

The contract is precise enough for bindings: mutable operations on one context and its attached requests must be serialized, including destruction; distinct contexts are disjoint and concurrently usable. No callback/reentrancy behavior is introduced. Bindings must not imply thread safety for simultaneous mutation/destruction of the same request/context, but may allow independent contexts to be used concurrently.

## Required downstream constraints

- A fresh independent `compatibility-reviewer` review of this exact candidate remains mandatory; this approval cannot satisfy it.
- G4 remains `CHANGES_REQUESTED` until the orchestrator synthesizes both required scoped reviews. This record does not self-approve G4.
- G6 renewal remains blocked. Only `protocol-orchestrator`, after both reviews and exact private write authority, may renew it.
- No implementation, binding implementation, G7, G8, G9, or other stage is authorized by this reviewer.

## Review disposition

`APPROVED` for the narrow question: the candidate’s opaque request/result ownership, post-`ratos_context_destroy` inspection/take-result/destruction behavior, terminal/no-result behavior, context-local exact-once accounting, and stated same-context/distinct-context concurrency boundary are safely representable over ABI-1 if implemented as specified. No failure handoff is required from this scoped review; mandatory compatibility and orchestrator synthesis remain pending.