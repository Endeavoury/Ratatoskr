# Preflight verification — G7 configured-limits re-review 002

| Field | Observed evidence |
| --- | --- |
| Workflow / stage | `dns-implementation-20260913` / G7 native verification |
| Candidate | `1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Repository root / cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch | `hermes/dns-implementation-20260913` |
| Origin | `https://github.com/Endeavoury/Ratatoskr.git` |
| Local HEAD / remote-tracking ref | both `a4fff37070604df1d01e03e302d545cbec2647c1` |
| Candidate ancestry | wrapper `merge-base --is-ancestor candidate HEAD` exited 0 |
| Wrapper | executable at `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` |
| Existing state | G7 and G8 are `CHANGES_REQUESTED`; candidate author assignment is `READY_FOR_REVIEW`; historical rereview-001 is `BLOCKED` solely for unknown effort |
| Specialist availability | process listing showed dashboard/gateway/interactive Hermes processes and this cron worker, but no identified live protocol-test-engineer delegation or direct one-shot execution for assignment `g7-configured-limits-rereview-002` |
| Independent subject | New direct one-shot session will be independent from remediation author and all named prior G7 reviewers |
| Required runtime | direct CLI command will explicitly specify `--provider openai-codex --model gpt-5.6-terra --reasoning medium`; CLI help confirms `--reasoning` overrides the session setting |

Inputs checked: candidate implementation report, completion report, author return handoff, originating DNS-G8-001 handoff, workflow state, AGENTS, role skills, and required agentic contracts.

Decision: the routing packet may be committed and pushed before exactly one fresh leaf dispatch. This is administrative readiness only; no G7 technical disposition is asserted.
