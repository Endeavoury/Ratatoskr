# Delegated task — prepared, not dispatched

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-configured-limits-rereview-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Root task ID | `dns-implementation-20260913` |
| Project ID | `Ratatoskr` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `protocol-orchestrator` |
| Intended leaf role | `protocol-test-engineer` |
| Hierarchy | `workspace-orchestrator → protocol-orchestrator → protocol-test-engineer (leaf)` |
| Status | `BLOCKED` — packet ready; no leaf dispatch |
| Candidate revision | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |

ACTIVE ROLE: `protocol-test-engineer`

ROLE: `protocol-test-engineer`, a fresh independent G7 reviewer. You must be independent of `c-protocol-implementer/g8-configured-limits-remediation-002` and all prior relevant G7 reviewer assignments, including `g7-native-verification-001`, `g7-remediation-rereview-002`, `g7-g8-limits-rereview-001`, `g7-limits-rereview-001`, and `g7-accounting-native-verification-001`.

GOAL: Independently review exact pushed candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` for G7. Establish a technical disposition only from your own reviewer evidence; do not assume prior G7 approval applies to this corrective candidate.

SCOPE: Review-only G7 native implementation/test evidence. Do not implement production code, alter canonical truth, alter prior reviews, alter gate status, or route any later stage. You may author new scoped test evidence only if necessary after inspection under the explicit paths below.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, `protocol-test-engineer` row.
- Requested route: provider `openai-codex`, model `gpt-5.6-terra`, reasoning `medium`.
- Required pre-dispatch actual route: verified `openai-codex/gpt-5.6-terra`, effort `medium`.
- Observed before dispatch attempt: model/provider verified as `openai-codex/gpt-5.6-terra`; effort is unknown/unset because no `agent.reasoning_effort` is configured.
- Verification source: active runtime metadata plus `/home/hermes/.hermes/profiles/workspace/config.yaml`.
- Attempt policy: one bounded independent review; no model fallback. Stop and write a BLOCKED report if the effective model or medium effort is not verified, required input is missing, or a quota/rate-limit occurs.
- Escalation: Sol/high only for a documented nondeterministic state/transport or hard oracle/harness problem; do not silently escalate.

## Repository and working directories

- Absolute repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Required command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Git wrapper for any role commit/push/readback: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`, syntax `--role protocol-test-engineer -- <git args>`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/`.
- The leaf owns only its unique workspace. There is no shared writer by default.

## Read first

- `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/protocol-test-engineer/SKILL.md`
- `docs/agentic/{ARTIFACTS.md,HANDOFFS.md,DIRECTORIES.md,MODEL_POLICY.md,REVIEW_GATES.md,SECURITY_MODEL.md}`
- `docs/contributing.md`
- `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`

## Required inputs (read-only)

- Candidate branch remote ref `origin/hermes/dns-implementation-20260913` at exact `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`.
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-002/{implementation-report.md,completion-report.md,handoffs/dns-g8-001-configured-limits-remediation-to-protocol-orchestrator.md}`.
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`.
- Prior G7/G8 records only as historical context; they are not approval for `1a371fe`.
- Approved prerequisites and G7 rationale from current workflow state: G1–G6, G5 vectors, and G7 requirements.

## Allowed writes

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/test-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/reviews/g7-configured-limits-rereview.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/handoffs/`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-001/completion-report.md`
- Only if inspection strictly establishes necessity: `tests/dns/dns_g7_configured_limits_rereview_tests.c`, `tests/integration/dns_g7_configured_limits_rereview_test.py`, `tests/fixtures/dns/g7-configured-limits-rereview-fixtures.json`, and scoped registration in `tests/CMakeLists.txt`.

## Forbidden writes

- All production source and headers, including `src/protocols/dns/` and `include/`.
- Workflow root `workflow-state.yaml`, request, manifest, gate status, and all prior role artifacts/reviews/handoffs.
- Canonical vectors, approved analysis/model/API, docs, fuzz, bindings, CLI, build files other than the narrowly allowed test registration.
- Any G8/G9/later-stage artifact or route.
- All paths outside the explicit allowed list; preserve unrelated modified/untracked artifacts.

## Expected outputs

- `test-report.md`: exact candidate/revision, independent inspection, execution commands/results, requirement/vector trace, limitations, and disposition.
- `reviews/g7-configured-limits-rereview.md`: independent G7 disposition with exact input revisions and reviewer identity.
- A handoff only if a discrepancy/blocker needs the owning role; otherwise state no handoff required.
- `completion-report.md` using the required role fields and actual model/effort/usage evidence.

## Acceptance criteria

- Verify the exact candidate and remote ref before technical work.
- Independently assess record-owner resource propagation; >128 traversal configuration rejection; resource-first effective pointer and RR boundaries; and oversized/truncated synchronous UDP rejection before fallback/parsing.
- Assess that context accounting/lifetime, exact-once cleanup, no-result behavior, and public ABI behavior from the accounting candidate remain intact.
- Execute and report only checks actually run. Faithfully record CMake/CTest, dynamic socket, Windows, boundary-probe, sanitizer, or platform limitations.
- If defects arise, do not fix them: route them to `c-protocol-implementer`, vector-designer, or analyst as applicable.
- Do not claim G8/G9/later gates passed or route them.

## Handoff and stopping

- Report to `protocol-orchestrator` in the leaf completion report and any leaf handoff.
- No further delegation is permitted.
- On a model/effort mismatch, quota/rate-limit, missing candidate/input, or boundary conflict: stop immediately, create the allowed leaf BLOCKED report, and do not modify tests or shared state.
