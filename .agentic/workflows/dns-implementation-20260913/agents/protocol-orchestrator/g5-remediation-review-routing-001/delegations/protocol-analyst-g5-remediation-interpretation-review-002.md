# Delegated task — G5 corrected DNS interpretation review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-analyst-g5-remediation-interpretation-review-002-delegation` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `NOT_STARTED` |
| Baseline delivered candidate | `git:a8e631b338df393ddfd3ea9648f333303726d87b`; vector SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c` |

ACTIVE ROLE: protocol-analyst

ROLE: Fresh independent G5 reviewer, assignment `g5-remediation-interpretation-review-002`.
GOAL: Independently assess whether the immutable corrected DNS canonical vectors express approved DNS analysis/model/API interpretation, including all remediated semantics.
SCOPE: G5 interpretation review record only. Do not edit analysis/model/API/vector truth, approve G5, start G6, or route later work.

## Model and reasoning
- Policy: `docs/agentic/MODEL_POLICY.md` protocol-analyst row: `gpt-5.6-terra`, medium; escalate to Sol/high only for conflicting normative rules or subtle state/framing requirements.
- Requested model/effort: `openai-codex/gpt-5.6-terra` / medium. Observed runtime model/effort: record actual metadata if exposed; otherwise `unknown`.
- Context target: complete required inputs; completion summary 200–400 words plus paths. Attempt policy: one independent evidence-driven review; stop on missing immutable input, scope conflict, actual quota/rate-limit, or unresolved interpretation ambiguity.

## Repository and workflow
- Absolute repository root and command CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Workflow-state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` (read-only).
- Immutable candidate: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-remediation-001/vector-set.json` at `git:a8e631b338df393ddfd3ea9648f333303726d87b`, SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`. Verify both before review.
- Read first: `AGENTS.md`; `.hermes/skills/protocol-analyst/SKILL.md` if it exists; `docs/agentic/ARTIFACTS.md`, `ARCHITECTURE.md`, `HANDOFFS.md`, `DIRECTORIES.md`, `REVIEW_GATES.md` (G5), `MODEL_POLICY.md`; workflow state; this packet; approved analysis/model/API; corrected vector completion/handoff; normative inventory as needed.

## Independence and allowed writes
- Must be a fresh session distinct from remediation author `deleg_18ffa0d9/task-0`, original author `deleg_29cd50f7/task-0`, and both prior G5 reviewers. Declare identity and independence in the review.
- Only allowed workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/g5-remediation-interpretation-review-002/`.
- Allowed files only: `reviews/g5-remediation-vector-interpretation-review.md` and `completion-report.md` (a handoff only if blocker requires it, in the same workspace).
- Forbidden: all other paths, including vector-designer workspaces, workflow state, production source, headers, tests/fixtures, fuzzers, bindings, docs, request/manifest, prior artifacts, and G6+ paths.

## Acceptance criteria
- Independently assess remediated `DNS-VEC-014`, `017`, and `019`–`023` against approved requirements, model and API without treating prior review conclusions as a substitute for reasoning.
- Check UDP-first/TC fallback traceability (DNS-REQ-021), non-QUERY opcode disposition (DNS-REQ-026), correlation ignores/deadline preservation, authority parsing/order, TCP truncated-frame terminal cleanup, exact end consumption, resource-limit precedence narrowing, and explicit DNS-REQ-027 downstream treatment.
- Produce one G5 gate review with exact input commit/digest, author/reviewer identities, independence declaration, evidence/limitations, and exactly one disposition.
- Produce one completion report only.

## Delivery and reporting
- Before committing, verify branch, staged allowed paths, and `git diff --check`. Commit/push only through `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-analyst` to `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref.
- Report to `protocol-orchestrator` with workspace paths, commit hash, exact remote readback, actual model/effort or unknown, gate disposition, and blockers.
- On quota/rate-limit: stop immediately and make no state/artifact writes. On another blocker: write only allowed review/completion records if safe, do not alter candidate/state, and report BLOCKED. No further delegation.
