# Preflight verification

| Check | Observed evidence | Result |
|---|---|---|
| Repository root | wrapper `rev-parse --show-toplevel` | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Origin / branch / local and remote tip | wrapper readback | `https://github.com/Endeavoury/Ratatoskr.git`; `hermes/dns-implementation-20260913`; both `a48815597e2fee88e8180f8c5f7b456bd19c59ae` |
| Wrapper | `stat` | regular executable, mode `700`: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` |
| Required candidate ancestry | wrapper `merge-base --is-ancestor 7a0875e.. 844cc88..` | verified |
| Required G7 delivery ancestry | wrapper `merge-base --is-ancestor defb3e.. 844cc88..` | verified |
| Gate/status | current `workflow-state.yaml`, G8 review | security/G8 is `CHANGES_REQUESTED`; `DNS-G8-001` and `DNS-G8-002` are blocking and owned by `c-protocol-implementer` |
| Existing worktree | wrapper status | unrelated untracked agent workspaces present; preserved and excluded from this assignment |

Routing authorization is confined to the packet in `delegations/`. The requested child route is `openai-codex/gpt-5.6-sol` with `high` effort because both concurrency/lifetime escalation triggers apply. Hermes child configuration cannot be assumed; actual model/effort must be recorded from exposed child/runtime metadata. If Sol/high is unavailable, the explicitly authorized bounded equivalent is inherited `openai-codex/gpt-5.6-terra` with actual exposed effort recorded; otherwise stop and hand back.
