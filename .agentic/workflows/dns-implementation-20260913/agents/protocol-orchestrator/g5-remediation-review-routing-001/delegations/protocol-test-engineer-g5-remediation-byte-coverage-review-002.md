# Delegated task — G5 corrected DNS exact-byte and coverage review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g5-remediation-byte-coverage-review-002-delegation` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `NOT_STARTED` |
| Baseline delivered candidate | `git:a8e631b338df393ddfd3ea9648f333303726d87b`; vector SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c` |

ACTIVE ROLE: protocol-test-engineer

ROLE: Fresh independent G5 reviewer, assignment `g5-remediation-byte-coverage-review-002`.
GOAL: Independently review the immutable corrected vector candidate for exact bytes, declared lengths, DNS UDP/TCP framing, parser consumption, expected events/errors/state/cleanup, and positive/negative/boundary coverage.
SCOPE: G5 review record only. Do not author tests or fixtures, revise vectors, resolve interpretation as vector truth, approve G5, start G6, or route later work.

## Model and reasoning
- Policy: `docs/agentic/MODEL_POLICY.md` protocol-test-engineer row: `gpt-5.6-terra`, medium; escalate to Sol/high only for nondeterministic state/transport or oracle/harness distinction.
- Requested model/effort: `openai-codex/gpt-5.6-terra` / medium. Observed runtime model/effort: record actual metadata if exposed; otherwise `unknown`.
- Context target: complete required inputs; completion summary 200–400 words plus paths. Attempt policy: one independent evidence-driven review; stop on missing immutable input, scope conflict, actual quota/rate-limit, or unresolved semantic ambiguity.

## Repository and workflow
- Absolute repository root and command CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Workflow-state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` (read-only).
- Immutable candidate: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-remediation-001/vector-set.json` at `git:a8e631b338df393ddfd3ea9648f333303726d87b`, SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`. Verify both before review.
- Read first: `AGENTS.md`; `.hermes/skills/protocol-test-engineer/SKILL.md` if it exists; `docs/agentic/ARTIFACTS.md`, `HANDOFFS.md`, `DIRECTORIES.md`, `REVIEW_GATES.md` (G5), `MODEL_POLICY.md`; workflow state; this packet; approved analysis/model/API; and corrected vector completion/handoff.

## Independence and allowed writes
- Must be a fresh session distinct from remediation author `deleg_18ffa0d9/task-0`, original author `deleg_29cd50f7/task-0`, and both prior G5 reviewers. Declare identity and independence in the review.
- Only allowed workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g5-remediation-byte-coverage-review-002/`.
- Allowed files only: `reviews/g5-remediation-vector-byte-coverage-review.md` and `completion-report.md` (a handoff only if blocker requires it, in the same workspace).
- Forbidden: all other paths, including vector-designer workspaces, workflow state, production source, headers, tests/fixtures, fuzzers, bindings, docs, request/manifest, prior artifacts, and G6+ paths.

## Acceptance criteria
- Review exact encoded bytes/declared lengths and independently check corrected `DNS-VEC-014`, `017`, and `019`–`023` plus overall coverage, with no production parser/builder oracle.
- Assess DNS UDP/TCP framing, opcode/question/endpoint correlation, authority ordering, EOF/trailing consumption, limit precedence, expected result/error/state/cleanup, and positive/negative/boundary coverage.
- Produce one G5 gate review using template fields: exact input commit/digest, author/reviewer identities, independence declaration, check evidence/limitations, and exactly one disposition: APPROVED, CHANGES_REQUESTED, REJECTED, or BLOCKED.
- Produce one completion report only.

## Delivery and reporting
- Before committing, verify branch, staged allowed paths, and `git diff --check`. Commit/push only through `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer` to `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref.
- Report to `protocol-orchestrator` with workspace paths, commit hash, exact remote readback, actual model/effort or unknown, gate disposition, and blockers.
- On quota/rate-limit: stop immediately and make no state/artifact writes. On another blocker: write only allowed review/completion records if safe, do not alter candidate/state, and report BLOCKED. No further delegation.
