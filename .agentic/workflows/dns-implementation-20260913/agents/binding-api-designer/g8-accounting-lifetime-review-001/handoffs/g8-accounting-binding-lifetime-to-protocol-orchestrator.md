# Handoff: G8 accounting binding-lifetime disposition

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-binding-lifetime-to-protocol-orchestrator-001` |
| Workflow ID | `dns-implementation-20260913` |
| Stage | G4-supporting corrective native API design review |
| Source | `binding-api-designer/g8-accounting-lifetime-review-001` |
| Destination | `protocol-orchestrator` |
| Target | DNS request/context ownership and private accounting |
| Status | `READY_FOR_REVIEW` |
| Subject revision | `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Blocking | Yes — for renewed G6/implementation routing; no blocking defect is found by this reviewer |
| Source evidence | `../reviews/g4-g8-accounting-binding-lifetime-review.md`; exact candidate files at `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Limitations | Does not close a gate or authorize any later workflow stage. |

## Technical disposition

`APPROVED` narrowly for ABI-1 representability and opaque caller ownership/lifetime. The candidate safely specifies detached caller-owned requests after `ratos_context_destroy`; request-local state/error accessors, COMPLETE take-result, and request destruction remain usable without a dangling context dependency. COMPLETE results remain owned independent of context; terminal/no-result behavior does not force an ownership transfer; private context-local registry/counters and exact-once flags preserve the stated same-context serialization and distinct-context concurrency boundary.

## Requested action

1. Obtain the separately mandatory fresh independent `compatibility-reviewer` disposition for the same exact candidate.
2. Do not mark G4 approved from this leaf alone. Synthesize only after both scoped independent reviews are current and verified.
3. Keep G6 renewal and implementation blocked until that synthesis provides exact private write authority. This leaf authorizes neither implementation nor binding work.
4. If G6 is later renewed and implementation occurs, require the candidate-specified fresh G7 then G8 evidence; no G7/G8 disposition is made here.

## Acceptance criteria for orchestration

- Confirm this review and the compatibility review name exactly `git:4a37fc293c842b206190bad369e2a3e1ad00008c` as subject.
- Preserve ABI-1/public ownership boundaries: no public layout, symbol, calling convention, or ownership-transfer change.
- Renew G6 only through the orchestrator and only with the four private accounting paths explicitly named by the design.

## Resolution (destination)

Pending protocol-orchestrator verification and separately mandatory compatibility review.