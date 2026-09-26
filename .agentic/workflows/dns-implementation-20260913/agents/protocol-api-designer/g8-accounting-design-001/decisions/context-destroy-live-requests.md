# Decision: detach live DNS requests during context destruction

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-context-destroy-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` request/context lifetime |
| Owner role | `protocol-api-designer/g8-accounting-design-001` |
| Status | `READY_FOR_REVIEW` |
| Revision | Delivered with the assignment candidate. |
| Source artifacts | `../api-design.md`; `DNS-G8-002` at `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; authority blocker at `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`. |
| Assumptions | Context/request mutation is externally serialized; request handles are caller-owned and opaque. |
| Open questions | None. |
| Limitations | Private design decision only; independent review and implementation are pending. |

## Context

The public context destroy operation returns `void`; the public request handle is separately caller-owned and has its own destroy operation. The approved G4 design did not define destruction of a context with an attached request. A global registry is unsafe, but merely moving its head into the context without defining teardown would leave dangling request context pointers.

## Decision

Context destruction walks its private request registry, terminally cancels each nonterminal request without emitting an event, releases all held slots, and detaches every handle by clearing its context/list links. It does not free caller-owned request handles. Existing terminal states are preserved; a COMPLETE request preserves its owned result for later take-result or destruction. The caller remains responsible for request destruction.

After detachment, state/error accessors, COMPLETE take-result, and request destruction remain valid. Further transport/parser mutation cannot resume. Same-context destruction concurrent with request activity remains unsupported; distinct contexts remain concurrently usable.

## Alternatives rejected

- Reject context destruction while requests exist: impossible to report through the existing `void` function and would leak or require undocumented behavior.
- Free live request handles from context destruction: violates caller ownership and creates double-free/UAF when callers later use or destroy retained handles.
- Require context to outlive requests without enforcement: leaves the exact dangling-pointer safety gap the corrective design must close.
- Add a global lock around the process-global list: retains forbidden resolver-global state, adds cross-context contention, and does not by itself settle handle ownership at context destruction.
- Add a new public close/status API: unnecessary public ABI/API expansion for a private ownership correction and outside this assignment.

## Consequences

The implementation needs a context-local registry plus exact-once accounting flags. Terminal request handles can outlive context storage safely. No public declaration or ABI generation changes, but fresh independent binding-lifetime and compatibility review is required before renewed implementation authority.
