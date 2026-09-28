# Preflight verification — DNS-G8-001 remediation 002

| Field | Value |
| --- | --- |
| Workflow / assignment | `dns-implementation-20260913` / `g8-configured-limits-remediation-002` |
| Status | `READY_TO_DISPATCH` |
| Verified at | `2026-09-20T19:14:24+02:00` |
| Baseline | `git:9afc2e8825619dccc73e8eed00a431f838dd8a47` |

## Verified inputs

- Wrapper: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`, invoked with `--role protocol-orchestrator` for every Git read and the reconciliation merge.
- Repository root, origin, branch and baseline: `/home/hermes/hermes-workspace/projects/Ratatoskr`, `https://github.com/Endeavoury/Ratatoskr.git`, `hermes/dns-implementation-20260913`, `9afc2e8`.
- Remote delivery ref was `5fe96f1`; it was fetched and merged through the wrapper. Merge commit `9afc2e8` has parents `23287a1` and `5fe96f1`; only remote `LICENSE` content was merged, and no local or remote history was overwritten.
- Current state identifies `DNS-G8-001` as the only active corrective blocker. The G8 review and handoff require the four specific fixes: resource propagation from record-owner name parsing; enforceable pointer limit; resource-first overlapping guards; synchronous UDP truncation/oversize detection.
- `DNS-G8-002` remains resolved for `c38a7fa`; the leaf must preserve its context-owned accounting and detached-handle behavior.
- All G7/G8 statuses remain `CHANGES_REQUESTED`; this packet grants no review authority.
- The proposed leaf workspace `agents/c-protocol-implementer/g8-configured-limits-remediation-002/` is new. No live `delegate_task` child exists.

## Runtime and boundary decision

The installed CLI accepts `hermes chat --query-file`, `--oneshot`, `--provider`, `--model`, and `--reasoning`. The leaf is dispatched only via the explicit direct command `hermes chat -Q --oneshot --provider openai-codex --model gpt-5.6-sol --reasoning high --query-file <dispatch-query>`. It must record actual runtime evidence, use the exact c-protocol-implementer Git wrapper for all Git reads/writes, and push only authorized paths to `HEAD:refs/heads/hermes/dns-implementation-20260913` followed by wrapper remote readback. Any quota/rate-limit result cancels this route with no state update beyond this pre-dispatch evidence.
