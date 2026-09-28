# Handoff: G8 accounting design candidate to protocol orchestrator

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-design-to-protocol-orchestrator` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` internal request accounting |
| Owner role | `protocol-api-designer/g8-accounting-design-001` |
| Status | `READY_FOR_REVIEW` |
| Revision | Delivered with the assignment candidate; exact commit reported on return. |
| Source artifacts | `../api-design.md`; `../decisions/context-destroy-live-requests.md`; G8 delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; blocker delivery `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`. |
| Assumptions | Existing public API remains unchanged. |
| Open questions | None for the design author; independent dispositions are pending. |
| Limitations | No implementation, test, gate approval, or workflow-state update was performed. |

## Routing

- ID / workflow / stage: `DNS-G8-ACCOUNTING-DESIGN-001` / `dns-implementation-20260913` / corrective native API design.
- Source role and assignment: `protocol-api-designer/g8-accounting-design-001`.
- Destination role: `protocol-orchestrator`.
- Target protocol/component: DNS request/context ownership and per-context caps.
- Reason: return an implementation-ready candidate resolving the authority gap for `DNS-G8-002`.
- Blocking: true for renewed implementation routing.
- Status: `READY_FOR_REVIEW`.

## Source artifacts and evidence

`api-design.md` maps start, UDP-to-TCP, completion, failure, cancellation, take-result, request destruction, and context destruction to explicit context-owned state. It forbids process-global mutable request tracking and limits the proposed implementation to four private source/header files. `decisions/context-destroy-live-requests.md` resolves caller-handle behavior when a context is destroyed.

All immutable commits named by the packet were verified as ancestors of the exact origin delivery branch before writing. The candidate changes no production/public header/test/vector/review/workflow-root file.

## Requested action

Obtain fresh independent `binding-api-designer` lifetime/representability review and fresh independent `compatibility-reviewer` ABI/ownership review of this exact candidate. If both approve, renew G6 with an exact four-file accounting implementation scope and a fresh c-protocol-implementer assignment. After implementation, require fresh independent G7 and then G8; do not close `DNS-G8-002` from this authoring handoff.

## Acceptance criteria

- Independent reviews address post-context-destroy request/result use, opaque ownership, and ABI-1 compatibility against this exact revision.
- Orchestrator records whether G4 evidence remains applicable and renews G6 only with exact private paths.
- Any implementation contains no process-global mutable tracker and follows exact-once per-context accounting.
- Fresh independent G7 verifies lifecycle/caps/distinct-context concurrency; fresh independent G8 verifies `DNS-G8-002` and the complete candidate.

## Resolution (destination role)

Pending independent review and orchestrator synthesis.

## Closure (orchestrator after verification)

Pending.
