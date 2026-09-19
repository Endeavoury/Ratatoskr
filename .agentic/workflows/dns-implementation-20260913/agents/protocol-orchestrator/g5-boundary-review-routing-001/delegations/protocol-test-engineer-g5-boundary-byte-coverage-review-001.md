# Delegated task

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g5-boundary-byte-coverage-review-001-delegation` |
| Workflow / stage | `dns-implementation-20260913` / vectors (G5) |
| Target / owner | `protocol/dns` / `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Candidate revision | `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`; SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6` |

ACTIVE ROLE: protocol-test-engineer

ROLE: protocol-test-engineer, fresh independent G5 reviewer.
GOAL: Independently review this exact immutable candidate for G5 exact bytes, declared lengths, boundary coverage and mechanically consumable outcomes. Record only your technical disposition; do not repair or synthesize.
SCOPE: Review-only. Required designated G5 byte/coverage review. Earlier G5 reviews apply to a different candidate and must not be reused as an approval.

## Model and reasoning
- Policy/default: `gpt-5.6-terra`, medium.
- Requested route: `openai-codex/gpt-5.6-terra`, medium; observed parent route `openai-codex/gpt-5.6-terra`; child effort/usage telemetry unknown unless exposed.
- Context target: 8k–16k; summary target 200–400 words.
- Attempt policy: one evidence-driven review pass; no corrective authoring. Stop on missing input, scope conflict, quota/rate-limit error, or completion.

## Repository and paths
- Root and command CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- AGENTS: `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`.
- Specialist skill: `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/protocol-test-engineer/SKILL.md`.
- Your artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g5-boundary-byte-coverage-review-001/`.
- You are a leaf. No further delegation.
- For any commit/push, use only executable `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- ...`; never raw-git commit/push. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never master; read back that exact remote ref.

## Read first
1. `AGENTS.md`; your skill; `docs/agentic/HANDOFFS.md`, `ARTIFACTS.md`, `DIRECTORIES.md`, `MODEL_POLICY.md`, `REVIEW_GATES.md` (G5), `PROTOCOL_LIFECYCLE.md`.
2. Workflow state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
3. Candidate: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/vector-set.json` and its handoff/completion.
4. Approved analysis/model/API referenced in the candidate. Prior finding record `DNS-G5-COV-004` is context only, not a substitute review.

## Allowed writes
Only these paths: your `README.md`; `reviews/g5-boundary-vector-byte-coverage-review.md`; optional `handoffs/`; `completion-report.md` in your workspace. All other paths, including candidate, state, production, tests, prior reviews and other workspaces, are read-only.

## Required checks and acceptance
- Verify candidate path, delivery revision, SHA-256, JSON validity, 29-case count, DNS-VEC-024..029 presence, and no author/reviewer identity overlap.
- Independently inspect exact local UTF-8 input, QNAME bytes, emitted DNS bytes/diagnostic would-be QNAME, declared hex lengths, outcomes/no-I/O/cleanup, and coverage of semantic boundaries 0/1/63/64/255/256.
- Check candidate delivery and your own delivery diffs against allowed paths and run `git diff --check` for your delivery.
- Use no production implementation or test harness as an oracle. State limitations honestly.
- Write a complete gate-review record with exact inputs, reviewer identity, independence declaration, evidence table, and exactly one disposition: APPROVED, CHANGES_REQUESTED, REJECTED, or BLOCKED. If corrective work is needed, identify the responsible owner and re-review criteria but create no corrective route.
- Write completion report. Commit/push only your assigned workspace and read back exact remote ref.

HANDOFF: protocol-orchestrator; report only the individual G5 byte/coverage disposition and remote delivery evidence. Do not update workflow state, approve G5 overall, route work, G6, or later stages.
