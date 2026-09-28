# Compatibility report — G8 accounting candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-compatibility-report-002` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` private request accounting and context-destroy lifetime design |
| Owner role | `compatibility-reviewer/g8-accounting-compatibility-review-002` |
| Status | `APPROVED` — scoped G4-supporting/G12-style disposition only |
| Subject revision | `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Baseline revision | `git:e804eb46f9aca14c4be6152e154a0b518f34c7fe` |
| Supporting review | Binding-lifetime delivery `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`, scoped `APPROVED` |
| Assumptions | The future implementation conforms exactly to the reviewed private design and preserves the declared serialization boundary. |
| Open questions | None for compatibility of the design candidate. |
| Limitations | No implementation or executable ABI artifact exists for this design-only correction; implementation conformance requires fresh G7/G8 evidence. |

## Scoped disposition

`APPROVED` for compatibility of the exact accounting/lifetime design candidate. This approval is only a corrective G4-supporting/G12-style review fact. It neither closes G4 nor approves full-workflow G12, G6 renewal, implementation, G7, G8, or any later stage.

## Immutable evidence and comparison method

All Git reads used `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role compatibility-reviewer -- <git args>`.

- Wrapper `cat-file -e` verified subject `4a37fc293c842b206190bad369e2a3e1ad00008c`, baseline `e804eb46f9aca14c4be6152e154a0b518f34c7fe`, and binding delivery `e04fefa07e72427adc7ecbab339fef96bc04b3b7`.
- Wrapper ancestry checks verified subject → binding delivery → baseline.
- Wrapper `show` read the exact subject `api-design.md`, `decisions/context-destroy-live-requests.md`, handoff, and completion, plus the binding review/completion/handoff at its delivery.
- The subject commit changes only its six authorized artifact/handoff paths and no public declaration.
- Wrapper diffs from subject parent → subject and subject → baseline are empty for `include/ratatoskr/`, `docs/abi.md`, and `docs/migration-dotnet.md`.
- Subject and baseline have identical blobs for `context.h` (`ef8b574154ff8f21ba81b3b4d3bcae5c9c2f6935`), `dns.h` (`6a8ea8fb6bac8e4397d72efcbff1950cb186d8ad`), `version.h` (`72f3097b3d9138dfce075db4c5f476866ba19a41`), `docs/abi.md` (`b071414c8e2f8f079e3f46dc7c70ee5531a9bb71`), and `docs/migration-dotnet.md` (`dfff11cdfc2ce56d03deddf1a50d5ba2ef9492f8`).
- Wrapper reads of baseline private `core_internal.h`, `context.c`, `dns_internal.h`, and `dns_client.c` confirmed the current global request list, context pointer, owned result representation, and context destroy behavior that the design corrects.

## Compatibility axes

### 1. Binary ABI: symbols, layout, and calling contracts — compatible

No exported symbol, function signature, calling convention, fixed-width constant type, public struct field/order/size, or opaque-type declaration changes. `ratos_context` and `ratos_dns_request` remain opaque. Only their private layouts gain context-local registry/counter/flag state. `RATOS_ABI_VERSION` remains 1 and product version remains 0.1.0. Because the reviewed public blobs are byte-identical, existing binaries retain the same symbol and calling contracts; no shared-library major or ABI-generation bump is required.

### 2. Source API — compatible

Existing source continues to compile against identical headers. No name, prototype, required initializer, enum value, capability bit, or option field changes. Existing callers need no source migration. The design adds no requirement to call a new function and preserves `void ratos_context_destroy(ratos_context *)` and `ratos_dns_request_destroy`.

### 3. Ownership and lifetime — compatible safety clarification

Caller ownership of request handles is preserved: context destruction detaches but does not free them, avoiding double-free and retained-handle UAF. Pending requests become CANCELLED/no-result; existing terminal state is retained; COMPLETE requests keep their independently owned result for later take-result or destruction. Request-local accessors and destruction remain valid after detachment, while transport/parser mutation cannot resume and returns the existing invalid-argument outcome. Private registry reachability is not an ownership transfer. Exact-once flags release per-context capacity on terminal transitions and avoid ownership-dependent counter retention.

This settles a previously omitted and unsafe context-destroy/live-request case without weakening any documented caller guarantee. Same-context mutation/destruction remains serialized; distinct contexts remain independently concurrent.

### 4. Binding representability and existing bindings — compatible

The separately delivered binding-lifetime review approves the same exact subject. FFI types and signatures are unchanged, and opaque private growth is unobservable. Existing repository bindings use the synchronous query/context lifecycle and do not expose a conflicting asynchronous request wrapper, so no binding source or package migration is triggered. Future request wrappers can represent a detached-but-caller-owned terminal request, optional owned COMPLETE result, and invalid post-detachment mutation without hidden ownership transfer or native-layout coupling.

### 5. Observable behavior — compatible, with documentation impact

The only newly determined observable case is destroying a context while caller-owned requests remain. Turning pending handles into CANCELLED/no-result, preserving terminal handles and COMPLETE results, and rejecting further mutation is a safe deterministic replacement for the baseline dangling-context hazard; it does not alter DNS wire bytes, parser disposition, response fields, normal synchronous query behavior, or documented success/error contracts. Capacity accounting changes are private and restore the intended per-context limits and distinct-context concurrency rather than creating a public semantic break.

Public lifecycle documentation should state the reviewed detach semantics when the implementation is documented at G13. That documentation work is not a prerequisite to this design-only scoped approval and must not claim implementation before fresh G7/G8 evidence.

### 6. Versioning and migration — no bump or code migration

The ABI-1 policy permits private opaque-layout changes and requires an ABI/shared-library major bump only for binary incompatibility. None exists here. No deprecation, compatibility shim, symbol version, package-major change, or `.NET` migration note is required. Release/user documentation should mention the safe live-request teardown behavior as a clarification/fix, not as a breaking migration. Existing `.NET` target-framework and managed-cancellation exceptions are unaffected.

## Residual conditions and downstream limits

Approval depends on implementation matching the design: per-context state only, exact-once slot flags, no process-global mutable tracker, detachment before context free, preserved COMPLETE result ownership, and invalid mutation after detachment. A deviation is implementation nonconformance and requires return to the implementer, not reinterpretation of this compatibility approval. The protocol orchestrator alone may synthesize G4 evidence and renew G6 with exact private write authority; fresh independent G7 and then G8 remain mandatory.