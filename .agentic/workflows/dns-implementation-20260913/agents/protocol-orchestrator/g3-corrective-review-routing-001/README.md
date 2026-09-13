# DNS G3 corrective-review routing

| Field | Value |
| --- | --- |
| Assignment | `g3-corrective-review-routing-001` |
| Active role | `protocol-orchestrator` |
| Workflow / stage | `dns-implementation-20260913` / G3 corrective review |
| Target | `protocol/dns` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g3-corrective-review-routing-001/` |
| Delivered correction revision | `46dfcfe543c7591db963c606802cd7f0d147d35d` |
| Remote readback | `46dfcfe543c7591db963c606802cd7f0d147d35d refs/heads/hermes/dns-implementation-20260913` |

## Scope

This routing record delivers the previously local G3 model correction and assigns exactly one fresh independent `protocol-api-designer` G3 reviewer. The correction remains `READY_FOR_REVIEW`; G3 and modeling remain `CHANGES_REQUESTED` until that reviewer records a disposition. G4 and all later stages are outside this assignment.

## Delivery evidence

The coordinator independently verified `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is a regular executable file (mode `700`), inspected its thin role-controlled Git exec, verified the repository root/origin/branch/baseline and `git diff --check`, then committed `46dfcfe543c7591db963c606802cd7f0d147d35d` (`Deliver G3 corrective model artifacts`). The wrapper pushed only `HEAD:refs/heads/hermes/dns-implementation-20260913`; exact remote readback matched that revision.

## Assigned reviewer boundary

The reviewer workspace is `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/`. It is a fresh delegation identity, distinct from prior `protocol-api-designer/g3-api-001`, and may write only its README, `reviews/g3-corrective-model-review.md`, permitted handoff records/resolution, and completion report. It may not author API design, modify shared state, route G4, or modify technical truth.
