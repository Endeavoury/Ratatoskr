# Delegation: G9 DNS name-harness bounds remediation 002

| Field | Value |
| --- | --- |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| Role / hierarchy | `fuzz-engineer`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Assignment / stage | `g9-name-harness-bounds-remediation-002`; DNS G9 corrective fuzz-harness stage |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `d489d749a37548e1e711d11c10b53b2041281bbf`; branch `hermes/dns-implementation-20260913`; origin `https://github.com/Endeavoury/Ratatoskr.git` |
| Leaf workspace | `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/` |
| Reporting target | `protocol-orchestrator/g9-resumption-009` through the leaf completion and handoff artifacts |
| Requested / observed model | requested `openai-codex/gpt-5.6-terra`, medium; actual runtime/effort unknown before launch—record honestly |
| Attempt limit | one bounded remediation attempt; no further delegation, retry, campaign, or review routing |

## READ FIRST
1. `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`
2. `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/fuzz-engineer/SKILL.md`
3. `docs/agentic/{SECURITY_MODEL,ARTIFACTS,REVIEW_GATES,DIRECTORIES,HANDOFFS,MODEL_POLICY}.md` and `docs/contributing.md`
4. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
5. Exact inputs listed below. Treat all inputs and every path except the explicit allowed list as read-only.

## Goal and exact inputs
Perform exactly one authorized correction attempt for the historic out-of-bounds terminal writes in `fuzz/dns/fuzz_dns_name.c`, reported by:
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/handoffs/g9-fuzz-execution-to-protocol-orchestrator.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-008/verification/g9-fuzz-execution-005-delivery-verification.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-focused-review-001/reviews/g9-name-harness-focused-review.md`

Inspect live `fuzz/dns/fuzz_dns_name.c`; do not assume the historic report proves current behavior. If the five terminal writes require a cap, the only permitted correction is the minimal `copied` bound required to ensure the highest write index is at most 1023. At dispatch, the expected safe form is `sizeof(packet) - 17u`, and fix commit `2c9e9b945352642d27cf703132e8e5e525b8b5cb` is already an ancestor. If that safe form is already present and live, do not alter source: record a no-op remediation result and validate the existing correction.

## Allowed writes (exact)
- `fuzz/dns/fuzz_dns_name.c` — only the minimal bounds correction above, and only if absent or incorrect.
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/fuzz-plan.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/handoffs/g9-name-harness-bounds-remediation-to-protocol-orchestrator.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/completion-report.md`

## Forbidden
Do not modify corpus, CMake, other harnesses, production/source paths, tests, workflow state, docs, config, bindings, or any other agent artifact. Do not touch pre-existing untracked files. Do not commit/push any file outside the allowed list. No package install, network target, credential access, merge, force push, master update, security review, or full/partial G9 campaign. Do not delegate.

## Required validation and delivery
1. Preserve existing unrelated working-tree state. Verify root/origin/branch/local and fetched remote ref match the dispatch baseline before writes; otherwise BLOCKED and do not commit.
2. Record source-level bounds reasoning and run focused sanitizer validation appropriate to this correction: configure/build only `ratos_fuzz_dns_name` using existing LLVM19 toolchain in `/tmp`, then replay an isolated 1,133-byte derived input. Record exact commands, exit codes, sanitizer result, build path, and limitations. Do not run packet or record targets.
3. Write all four leaf deliverables. Status is `READY_FOR_REVIEW` only for a completed focused remediation/no-op validation; it is never G9 approval. If prerequisites, toolchain, baseline, wrapper, or validation fail, write a BLOCKED completion/handoff and do not claim delivery.
4. Before delivery inspect the staged diff and require it is limited exactly to the allowed source path only if a correction was necessary, plus the four leaf artifacts. Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git args>` to commit and push to `HEAD:refs/heads/hermes/dns-implementation-20260913`; then read back the exact remote ref. Include commit, remote readback, and changed-path evidence in the artifacts. No raw git commit/push.

## Acceptance / stop behavior
Acceptance is bounded remediation evidence and a correctly scoped delivery, not a G9 pass. Do not route, request, or perform a focused review, campaign, security review, or later stage. If blocked, preserve G9 BLOCKED and state the precise next responsible role/action. On quota/rate error, stop immediately without state changes, commits, pushes, or retries; report it to the orchestrator.