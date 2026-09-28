# Delegated task

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-analyst-g5-boundary-interpretation-review-001-delegation` |
| Workflow / stage | `dns-implementation-20260913` / vectors (G5) |
| Target / owner | `protocol/dns` / `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Candidate revision | `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`; SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6` |

ACTIVE ROLE: protocol-analyst

ROLE: protocol-analyst, fresh independent G5 reviewer.
GOAL: Independently review the exact candidate's semantic/interpretation correctness against approved DNS analysis/model/API and authoritative sources already recorded by those artifacts. Record only your individual disposition; do not author vector truth or synthesize G5.
SCOPE: Review-only, designated G5 interpretation review. Earlier G5 interpretation approval applied to a different immutable candidate and must not be reused.

## Model and reasoning
- Policy/default: `gpt-5.6-terra`, medium.
- Requested route: `openai-codex/gpt-5.6-terra`, medium; observed parent route `openai-codex/gpt-5.6-terra`; child effort/usage telemetry unknown unless exposed.
- Context target: 8k–16k; summary target 200–400 words.
- Attempt policy: one evidence-driven review pass; no corrective authoring. Stop on missing input, scope conflict, quota/rate-limit error, or completion.

## Repository and paths
- Root and command CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- AGENTS: `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`.
- Specialist skill: `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/protocol-analyst/SKILL.md`.
- Your artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/g5-boundary-interpretation-review-001/`.
- You are a leaf. No further delegation.
- For any commit/push, use only executable `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-analyst -- ...`; never raw-git commit/push. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never master; read back that exact remote ref.

## Read first
1. `AGENTS.md`; your skill; `docs/agentic/HANDOFFS.md`, `ARTIFACTS.md`, `DIRECTORIES.md`, `MODEL_POLICY.md`, `REVIEW_GATES.md` (G5), `PROTOCOL_LIFECYCLE.md`.
2. Workflow state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
3. Candidate plus handoff/completion: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/`.
4. Approved analysis `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md`, approved model `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml`, and approved API `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md`.

## Allowed writes
Only your `README.md`; `reviews/g5-boundary-vector-interpretation-review.md`; optional `handoffs/`; `completion-report.md` in your workspace. All other paths, including canonical candidate, state, production, tests, earlier reviews and other workspaces, are read-only.

## Required checks and acceptance
- Verify candidate path/revision/SHA-256, JSON validity, 29 cases, DNS-VEC-024..029, and fresh independence from candidate author and the other reviewer.
- Independently judge whether 0/1/63/64/255/256 name boundaries, accepted/rejected dispositions, ERR-LOCAL-VALIDATION/no-I/O/terminal cleanup, QNAME semantics, framing and provenance agree with approved analysis/model/API and cited RFC intent.
- Check delivery/diff boundary and your own delivery `git diff --check`; do not use production implementation as a semantic oracle.
- Write complete gate-review record with exact inputs, identity, independence, evidence and one individual disposition. If changes are needed, route only in the record to responsible owner with re-review criteria; create no corrective assignment.
- Write completion report. Commit/push only your own assigned workspace and read back exact remote ref.

HANDOFF: protocol-orchestrator; report only individual interpretation disposition and remote delivery evidence. Do not alter state or vector truth, synthesize G5, route corrective work, G6 or later stages.
