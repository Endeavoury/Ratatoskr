# Handoff: G8 accounting implementation to protocol orchestrator

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-accounting-implementation-to-protocol-orchestrator` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` context-owned request accounting |
| Owner role | `c-protocol-implementer/g8-accounting-implementation-001` |
| Status | `READY_FOR_REVIEW` |
| Revision | Wrapper-mediated delivery commit reported on return. |
| Source artifacts | `implementation-report.md`; design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; approvals `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`, `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`. |
| Assumptions | Same-context mutation is externally serialized. |
| Open questions | None. |
| Limitations | Fresh independent G7 and then G8 are required; neither was performed by this leaf. |

## Routing

- ID / workflow / stage: `DNS-G8-ACCOUNTING-IMPLEMENTATION-001` / `dns-implementation-20260913` / native implementation corrective delivery.
- Source role and assignment: `c-protocol-implementer/g8-accounting-implementation-001`.
- Destination role: `protocol-orchestrator`.
- Target protocol/component: DNS request/context ownership and per-context accounting.
- Reason: deliver the renewed-G6 four-file implementation candidate for independent review.
- Blocking: false for handoff; mandatory downstream review remains required.
- Status: `READY_FOR_REVIEW`.

## Source artifacts and evidence

Production changes are confined to `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c`. They replace the global tracker with a context list/counters, centralize flag-based slot release, detach caller-owned requests on context destruction, and reject detached mutable operations. Compilation and existing G7 native test evidence are recorded in `implementation-report.md`.

## Requested action

Verify the delivery boundary and route a fresh independent G7 review for the accounting candidate. Only after G7 approval may an independent G8 re-review assess `DNS-G8-002` and this complete candidate.

## Acceptance criteria

- Wrapper-read delivery ref and diff show only the four authorized production files and this assigned workspace.
- G7 independently exercises lifecycle/cap/detach behavior, including terminal accounting and post-context-destroy request safety.
- A later independent G8 verifies no process-global mutable tracker and closes or returns `DNS-G8-002`.

## Resolution (destination role)

Pending protocol-orchestrator routing.

## Closure (orchestrator after verification)

Pending.
