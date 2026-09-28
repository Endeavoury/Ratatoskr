# G7 DNS-G8-001 limits re-review routing

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g7-g8-limits-rereview-routing-001` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` — routing only |
| Baseline / current HEAD | `git:6ada36167c0f32dee39553ded3ac4d642ce1a3ef` |
| Candidate / artifact delivery | `git:a8d98b75e9c450734808d5a672a2023e83589fb0` / `git:a424049521c97969c32ef37f026c63803224b146` |

ACTIVE ROLE: protocol-orchestrator

## Administrative routing record

The ready corrective stage is a fresh, independent G7 review of the DNS-G8-001 configured-limits remediation. The candidate and its artifact-delivery commit both resolve locally and are ancestors of current HEAD. Pre-routing Git verification recorded repository root `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `hermes/dns-implementation-20260913`, HEAD `6ada36167c0f32dee39553ded3ac4d642ce1a3ef`, and zero ahead/behind divergence against `origin/hermes/dns-implementation-20260913`. Pre-existing untracked workspaces remain outside this assignment.

The candidate author is `c-protocol-implementer/g8-limits-remediation-001`. The new reviewer must be a fresh `protocol-test-engineer` leaf independent of that author and of `protocol-test-engineer/g7-native-verification-001` and `protocol-test-engineer/g7-remediation-rereview-002`. No prior G7 approval applies to `a8d98b75e9c450734808d5a672a2023e83589fb0`; G8 remains `CHANGES_REQUESTED`. This assignment neither routes nor approves G8, G9, or later work.

The complete leaf packet is `delegations/protocol-test-engineer-g7-g8-limits-rereview-001.md`. Shared state records the assignment as `IN_PROGRESS`; only the leaf may establish a G7 technical disposition in its own reports. The orchestrator makes no technical judgment here.

## Boundary

Allowed orchestrator writes are this unique directory and `workflow-state.yaml`. All production source, tests, canonical vectors, reviews, prior artifacts, request, and manifest are read-only. The leaf may write only its unique assigned workspace; all production and test paths are read-only review evidence. It may commit only completed allowed leaf artifacts after validation, exclusively through `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- ...`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, and read back that exact origin ref.

## Next owner

`protocol-test-engineer/g7-g8-limits-rereview-001` is the sole delegated leaf. Its result returns to `protocol-orchestrator`; a fresh G8 re-review is explicitly out of scope for this routing assignment.
