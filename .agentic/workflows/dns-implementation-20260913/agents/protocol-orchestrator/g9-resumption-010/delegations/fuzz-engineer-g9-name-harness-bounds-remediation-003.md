# Delegation: DNS name-harness bounds remediation 003

| Field | Value |
| --- | --- |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| Role / hierarchy | `fuzz-engineer`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Assignment / stage | `g9-name-harness-bounds-remediation-003`; G9 corrective harness evidence only |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Verified baseline / origin | `2c6b0bc742d3db88cc94b9e6e354b362ee0f6055`; `hermes/dns-implementation-20260913`; `https://github.com/Endeavoury/Ratatoskr.git` |
| Unique workspace | `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-003/` |
| Handoff target | `protocol-orchestrator/g9-resumption-010` |
| Requested / observed model | `openai-codex/gpt-5.6-terra`, medium / record actual as unknown unless runtime exposes it |
| Attempt policy | One focused attempt; no child delegation, retry, campaign, review, or later route |

## Read first
`AGENTS.md`; `.hermes/skills/fuzz-engineer/SKILL.md`; `docs/agentic/{SECURITY_MODEL,ARTIFACTS,REVIEW_GATES,DIRECTORIES,HANDOFFS,MODEL_POLICY}.md`; `docs/contributing.md`; current `workflow-state.yaml`; and these exact inputs:
- `agents/fuzz-engineer/g9-fuzz-execution-005/{completion-report.md,fuzz-results.md,handoffs/g9-fuzz-execution-to-protocol-orchestrator.md}`
- `agents/protocol-orchestrator/g9-resumption-008/verification/g9-fuzz-execution-005-delivery-verification.md`
- `agents/protocol-orchestrator/g9-resumption-009/{README.md,preflight-verification.md,completion-report.md,delegations/fuzz-engineer-g9-name-harness-bounds-remediation-002.md}`
- current `fuzz/dns/fuzz_dns_name.c`.

## Goal and boundary
Verify the delivered execution-005 blocker and perform exactly one narrow correction/no-op validation of the DNS name fuzz harness. The historic defect was terminal writes past `uint8_t packet[1024]` for an 1,133-byte input. Inspect the live source; the expected safe bound is `sizeof(packet) - 17u`. If it is present and correct, do not edit source: report a no-op and validate it. If absent/incorrect, modify only the copied bound to the minimal correction that ensures the highest terminal-write index is 1023. Never modify production code.

## Exact allowed writes
- `fuzz/dns/fuzz_dns_name.c` only if the minimal cap correction is actually required.
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-003/{README.md,fuzz-plan.md,fuzz-results.md,completion-report.md}`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-003/handoffs/g9-name-harness-bounds-remediation-to-protocol-orchestrator.md`

All other paths are forbidden/read-only: workflow state, corpus, CMake, all other fuzz harnesses, tests, production source, docs, bindings, configuration, and every other role workspace. Preserve unrelated untracked files.

## Required evidence and stop behavior
Before writes verify root, origin, branch, local and fetched remote ref equal the baseline. Build only the existing `ratos_fuzz_dns_name` target with `/usr/bin/clang-19` and `/usr/bin/clang++-19` in a unique `/tmp/ratatoskr-g9-name-harness-bounds-remediation-003` directory, then replay exactly one isolated 1,133-byte input. No network/remote targets, persistence/exploitation, corpus/CMake changes, packet/record target, partial/full campaign, security review, or later stage. Record exact commands, exit statuses, sanitizer result, source bounds reasoning, and limitations.

Create all five listed workspace deliverables (README included). Status may be `READY_FOR_REVIEW` only for completed narrow correction/no-op validation; it is never G9 approval. If any prerequisite/toolchain/baseline/validation fails, create BLOCKED results, completion, and handoff; do not claim delivery. On quota/rate error stop immediately: no state update, commit, push, retry, or alternate work.

Before delivery inspect that changed paths are exactly the allowed source only if necessary plus five leaf artifacts and run `git diff --check`. Commit and push only through `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git args>`, pushing only `HEAD:refs/heads/hermes/dns-implementation-20260913`; never merge, force-push, or update master. Read back the exact origin ref and place it in results/completion/handoff. Do not update workflow state.
