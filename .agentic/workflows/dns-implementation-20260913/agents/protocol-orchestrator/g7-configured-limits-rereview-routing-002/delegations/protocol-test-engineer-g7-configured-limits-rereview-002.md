# Delegated task — fresh independent G7 configured-limits re-review 002

| Metadata | Value |
| --- | --- |
| Workflow / root task / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| Assignment ID | `g7-configured-limits-rereview-002` |
| Stage / gate | `native_verification` / G7 |
| Hierarchy | `workspace-orchestrator → protocol-orchestrator → protocol-test-engineer (leaf)` |
| Exact candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Repository root and command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace owned by leaf | `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-002/` |
| Handoff target | `protocol-orchestrator` only |

ACTIVE ROLE: `protocol-test-engineer`

## Goal and independence

Perform exactly one fresh independent G7 review of the exact DNS-G8-001 corrective candidate. You are independent of `c-protocol-implementer/g8-configured-limits-remediation-002` and all earlier relevant G7 reviewers: `g7-native-verification-001`, `g7-remediation-rereview-002`, `g7-g8-limits-rereview-001`, `g7-limits-rereview-001`, and `g7-accounting-native-verification-001`. Declare that independence and your fresh session identity in every review/completion record. Do not treat prior approvals as approval of this candidate.

## Required route and stop rule

This direct one-shot invocation is explicitly requested with provider `openai-codex`, model `gpt-5.6-terra`, reasoning `medium`. Record actual route from the invocation evidence; it must match. One bounded review only, no fallback or further delegation. If the actual route/effort cannot be evidenced, an input is absent, a quota/rate failure occurs, or a boundary conflict is found: stop immediately, write only a leaf `BLOCKED` report/review/completion in your workspace, and modify neither tests nor shared state. On quota/rate failure, stop immediately without retry.

## Read first

1. `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`
2. `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/protocol-test-engineer/SKILL.md`
3. `docs/agentic/{ARTIFACTS,HANDOFFS,DIRECTORIES,MODEL_POLICY,REVIEW_GATES,SECURITY_MODEL}.md` and `docs/contributing.md`
4. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`
5. This packet and the required inputs below.

## Required read-only inputs

- `origin/hermes/dns-implementation-20260913` and exact candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; use `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- <git args>` for every Git read/write.
- `agents/c-protocol-implementer/g8-configured-limits-remediation-002/{implementation-report.md,completion-report.md,handoffs/dns-g8-001-configured-limits-remediation-to-protocol-orchestrator.md}`.
- `agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`.
- Current state’s G1–G6 approvals and G7/G8 `CHANGES_REQUESTED` rationale. Historical G7/G8 evidence is context only.

## Allowed writes

Only your unique workspace: `README.md`, `test-report.md`, `reviews/g7-configured-limits-rereview.md`, `handoffs/`, and `completion-report.md`.

Only if strict inspection establishes necessity, you may additionally create the specifically scoped test files `tests/dns/dns_g7_configured_limits_rereview_tests.c`, `tests/integration/dns_g7_configured_limits_rereview_test.py`, `tests/fixtures/dns/g7-configured-limits-rereview-fixtures.json`, and scoped registration in `tests/CMakeLists.txt`. Explain necessity before writing them. Do not change existing tests.

## Forbidden writes

No production source/header, public ABI, vectors, approved design/truth, existing reviewer/source artifacts, workflow-root files, docs, fuzz, bindings, CLI, build files except the stated scoped test registration, or any G8/G9/later artifact/route. Preserve unrelated work. Never merge, rebase, reset, clean, stash, force-push, or touch master.

## Required G7 assessment and evidence

Before technical judgment, verify exact candidate/remote ref/ancestry and inspect candidate diff/boundary. Independently assess: record-owner `read_name` resource propagation; rejection of traversal configuration above 128; resource-first effective pointer and total-RR boundaries; oversized/truncated synchronous UDP rejection before fallback/parsing; preservation of accounting/lifetime, exact-once cleanup, no-result behavior, and public ABI behavior from `c38a7fa`.

Run and report only checks actually executed. Fresh evidence must cover record-owner name expansion/pointer exhaustion over UDP and TCP, effective-default RR/pointer boundaries, over-hard traversal configuration rejection, and an actually oversized synchronous UDP datagram. State exactly what CMake/CTest, dynamic socket, Windows, parser-boundary, sanitizer, or platform evidence is unavailable. If a defect appears, do not fix it: create a handoff to the appropriate owner.

## Outputs and acceptance

Create `test-report.md`, `reviews/g7-configured-limits-rereview.md`, any needed handoff, and `completion-report.md` with exact candidate, commands/results, requirement trace, limitations, requested/actual runtime, independence, and a technical disposition of only `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED`. Do not route or claim G8/G9/later. Commit and push only your allowed artifacts with the wrapper as role `protocol-test-engineer` to `HEAD:refs/heads/hermes/dns-implementation-20260913`, then wrapper-read that exact remote ref. Report the delivery commit.
