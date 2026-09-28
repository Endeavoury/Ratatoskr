# G7 configured-limits rereview routing 001

| Metadata | Value |
| --- | --- |
| Artifact ID | `g7-configured-limits-rereview-routing-001` |
| Workflow ID | `dns-implementation-20260913` |
| Owner role | `protocol-orchestrator` |
| Status | `BLOCKED` |
| Candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / remote readback | `hermes/dns-implementation-20260913` / `origin/hermes/dns-implementation-20260913 = 1a371fe8083e72304740d983dcb7f9f6033b6b7f` |

## Scope

Route exactly one fresh, independent `protocol-test-engineer` G7 review of the submitted DNS-G8-001 corrective candidate. This routing cannot dispatch because the required reviewer route has not been verified at the policy-required medium reasoning effort.

## Verified preconditions

- The checkout is a Git worktree at the stated repository root; the wrapper is executable mode `700`.
- Origin is `https://github.com/Endeavoury/Ratatoskr.git` and both `HEAD` and the required remote branch read back at the exact candidate SHA.
- Candidate completion, implementation report, return handoff, and originating G8 handoff all report `READY_FOR_REVIEW`/require fresh independent G7 before any G8 re-review.
- `delegation.orchestrator_enabled=true` and `delegation.max_spawn_depth=2` are configured.

## Blocker

The required G7 reviewer policy is `openai-codex/gpt-5.6-terra` with `medium` reasoning. The active configuration/runtime verifies provider/model `openai-codex/gpt-5.6-terra`, but `agent.reasoning_effort` is absent and the child effort cannot be verified before dispatch. Per model policy, naming medium in a prompt does not configure the child. No leaf was delegated, no gate passed, and G8/G9/later stages were not routed.

See `delegations/protocol-test-engineer-g7-configured-limits-rereview-001.md` for the complete ready-to-dispatch packet and `completion-report.md` for the durable BLOCKED record.
