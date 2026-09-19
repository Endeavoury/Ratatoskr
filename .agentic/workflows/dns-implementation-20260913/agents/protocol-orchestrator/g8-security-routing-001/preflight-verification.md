# G8 routing preflight verification

| Field | Observed value |
| --- | --- |
| Checked at | `2026-09-19T20:52:47Z` |
| Repository root / command directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Origin | `https://github.com/Endeavoury/Ratatoskr.git` |
| Branch | `hermes/dns-implementation-20260913` |
| Local HEAD before routing write | `e8040f62880b2411049c9e8e97b5f8db7699459f` |
| Origin tracking ref before routing write | `e8040f62880b2411049c9e8e97b5f8db7699459f` |
| Wrapper | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`, verified regular executable Bash script; accepts `protocol-orchestrator` |
| G7 corrective subject | `4b801fbdf782c4aca4c6427ad930a48cb5e029ee` |
| G7 state | APPROVED by the fresh independent `protocol-test-engineer/g7-remediation-rereview-002` record |
| Ready stage selected | G8/security only |

The wrapper-mediated `4b801fbdf782c4aca4c6427ad930a48cb5e029ee..HEAD` diff contains only the prior G7 re-review routing/reviewer artifacts and workflow state; no unreviewed production diff follows the corrective subject. Pre-existing unrelated untracked workflow directories were observed and are preserved.

G8 remains a review assignment. This preflight neither judges technical security nor advances G8. G9 and later stages remain NOT_STARTED.
