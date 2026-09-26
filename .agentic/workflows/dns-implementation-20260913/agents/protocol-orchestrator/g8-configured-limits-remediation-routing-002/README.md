# DNS-G8-001 configured-limits remediation routing 002

| Field | Value |
| --- | --- |
| Workflow / stage | `dns-implementation-20260913` / corrective `native_implementation` |
| Active role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` pending the sole fresh implementation leaf's runtime-route check |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Local baseline | `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |
| Exact origin ref at preflight | `git:5fe96f16812e1c98ca4b1f68c120a72a3d54d00b` |
| Leaf workspace | `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-001/` |

## Scope

Route exactly one fresh `c-protocol-implementer` leaf for blocking `DNS-G8-001` using `delegations/c-protocol-implementer-g8-configured-limits-remediation-001.md`. The leaf may use only the four named private DNS source files, its fresh workspace artifacts, and the destination-only Resolution section of the named G8 handoff. It must not start or approve G7/G8 or later work.

## Preflight evidence

- Required role skill and contracts, current state, G8 review, finding handoff, G7 approval, and routing packet were read.
- Wrapper is executable at `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`; all repository Git inspection used it.
- Local HEAD is the required `1d33a8155dc6bcd3be16689d8aa134044b4449b0`; origin remains the historical `5fe96f16812e1c98ca4b1f68c120a72a3d54d00b`; existing unrelated dirty/untracked work is preserved.
- No live delegated child exists. The target leaf workspace is absent, so it is fresh.
- `c38a7fa`, G7 delivery `8c1383e`, and G8 delivery `1d33a8` resolve locally and are ancestors of local HEAD. G8 technical truth remains `CHANGES_REQUESTED`: DNS-G8-002 resolved only for `c38a7fa`; DNS-G8-001 remains blocking.
- Runtime preflight shows parent `openai-codex/gpt-5.6-terra` and no configured `delegation.model` or `agent.reasoning_effort`. The leaf must verify its own effective route is exactly `openai-codex/gpt-5.6-sol` with `high` reasoning before substantive work; otherwise it returns `BLOCKED` without repository writes.

## Authority boundary

Only this orchestrator writes `workflow-state.yaml`. The leaf is an author only and may submit `READY_FOR_REVIEW`; independent G7 and G8 remain pending after any candidate. This assignment routes no review.