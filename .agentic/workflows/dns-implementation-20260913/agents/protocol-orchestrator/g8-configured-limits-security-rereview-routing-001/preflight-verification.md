# G8 configured-limits security re-review preflight

| Field | Value |
| --- | --- |
| Workflow / owner | `dns-implementation-20260913` / `protocol-orchestrator` |
| Checked at | `2026-09-26T13:45:16+02:00` |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Wrapper | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-orchestrator -- …` |

## Wrapper and repository identity

The verified absolute wrapper is regular executable mode `700`, owner/group `hermes:hermes`. Its role allowlist includes both `protocol-orchestrator` and `security-reviewer`; it executes Git with the selected role identity. Wrapper-mediated reads returned:

- repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- origin: `https://github.com/Endeavoury/Ratatoskr.git`
- branch: `hermes/dns-implementation-20260913`
- local HEAD: `2f1f6c8bc2462420e1c4c903474150294980fa08`
- exact remote ref: `2f1f6c8bc2462420e1c4c903474150294980fa08 refs/heads/hermes/dns-implementation-20260913`

## Candidate and gate readiness

`git merge-base --is-ancestor 1a371fe8083e72304740d983dcb7f9f6033b6b7f HEAD` exited `0`. Wrapper `diff-tree --name-only` shows exactly:

1. `src/protocols/dns/dns_client.c`
2. `src/protocols/dns/dns_internal.h`
3. `src/protocols/dns/dns_parser.c`
4. `src/protocols/dns/dns_transport_udp.c`

The fresh independent G7 record at `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` is `APPROVED` for this candidate. The state’s G7 input revisions record candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`, reviewer delivery `510b5a131bcb3272caeb7eb1821444b35644cfcd`, and remote reflection `7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`. G8 remains `CHANGES_REQUESTED` for DNS-G8-001; this routing makes no technical judgment.

## Runtime route invocation

The installed Hermes CLI exposes explicit `--provider`, `--model`, and `--reasoning` flags. The only leaf is invoked with `--provider openai-codex --model gpt-5.6-sol --reasoning high`; packet acceptance requires the leaf’s actual runtime evidence, not the command text alone. The parent config is Terra and has no configured reasoning effort, so nested delegation is not used.