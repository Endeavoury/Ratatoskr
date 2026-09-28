# G4 binding-safety review routing

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g4-binding-review-routing-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `COMPLETE` |
| Baseline / delivery tip | `c2ab2aa30496edf70163b46b9572c0b155488eb4` |

ACTIVE ROLE: protocol-orchestrator

## Scope
Route exactly one designated independent binding-safety G4 review of the submitted native API candidate. This assignment does not author or alter technical truth, self-approve G4, route the mandatory compatibility review, or route vectors, implementation, or later stages.

## Verified prerequisites
- G3 is `APPROVED` in workflow state, with record `agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at delivery `865fa190ee19e041c5ddfab8279b49829baaa240`.
- `native_api_design` is `READY_FOR_REVIEW`; candidate `agents/protocol-api-designer/g4-api-design-001/api-design.md` and completion report were delivered at `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`.
- The binding-review workspace was absent before this routing assignment.

## Assignment boundary
The sole leaf may write only its listed review workspace artifacts. The orchestrator may write this workspace, the delegation packet, its delivery verification/completion records, and shared workflow state only after independently verifying the leaf's completed review. Compatibility review remains a separate mandatory G4 blocker regardless of the binding reviewer disposition.

## Model/runtime record
Requested leaf policy is `gpt-5.6-terra` / `medium`. Actual configured child route is not programmatically exposed by the delegation tool; the current exposed runtime is `openai-codex` / `gpt-5.6-terra`, with reasoning effort unknown. No model switch is claimed.
