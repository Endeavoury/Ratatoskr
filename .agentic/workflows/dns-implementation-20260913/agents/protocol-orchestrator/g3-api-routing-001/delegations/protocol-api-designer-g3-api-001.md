# Delegated task — independent DNS G3 semantic-model review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-delegation-api-designer-g3-api-001` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | protocol-orchestrator |
| Status | READY_FOR_ASSIGNMENT |
| Baseline / delivery revision | `42b0611efa90e4b62f06d07cca64044ae9f090a7` / `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c` |
| Assumptions | G2 evidence below is valid; G3 reviewer identity is fresh and independent of `protocol-modeler/g2-model-001` and `protocol-analyst/analysis-001`. |
| Limitations | This is G3 review only; no G4 advancement, header/source/test/vector/binding change, or G6 work. |

ACTIVE ROLE: protocol-api-designer

ROLE: protocol-api-designer, independent G3 reviewer (`g3-api-001`)

GOAL: Independently assess the submitted DNS semantic model against approved G2 analysis and record an evidence-backed G3 disposition. Only if the review disposition is APPROVED, author a conditional native API design candidate; that candidate is READY_FOR_REVIEW for G4 only and does not advance shared state.

SCOPE: Review/design artifacts only. Do not update workflow state or approve G4. Do not implement C, alter public headers, source, tests, vectors, fuzzing, docs, bindings, request, manifest, or any other assignment workspace.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-api-designer row.
- Requested model / effort: `gpt-5.6-sol` / `medium`.
- Observed parent/runtime configuration: `delegation.orchestrator_enabled=true`, `delegation.max_spawn_depth=2`; effective `delegation.model` and `agent.reasoning_effort` were unset. Actual child provider/model/effort are unknown unless exposed by runtime; record them honestly.
- Verification source: existing orchestration preflight supplied with this assignment; a prompt does not configure Hermes.
- Context target: 8,000–16,000 task-specific tokens while reading all required contracts fully.
- Completion target: 200–400 words plus artifact links.
- User hard cap: none.
- Attempt policy: one bounded evidence-driven correction; then return a BLOCKED or CHANGES_REQUESTED handoff rather than retrying without new evidence.
- Escalation: Sol/high only for a documented complex ownership/streaming/ABI issue; unavailable settings remain a routing limitation, not permission to self-configure.
- Stop: missing/stale prerequisite, boundary conflict, unresolved semantic loss, or completed review record.

## Repository and workspace

- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Assignment workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/`.
- Workspace owner: protocol-api-designer / `g3-api-001`; fresh delegated child identity must be recorded in review evidence.
- Shared source directories and shared writer: none. Only protocol-orchestrator writes `workflow-state.yaml`.

## Read first

- `AGENTS.md`
- `.hermes/skills/protocol-api-designer/SKILL.md`
- `docs/agentic/ARCHITECTURE.md`, `ARTIFACTS.md`, `HANDOFFS.md`, `DIRECTORIES.md`, `MODEL_POLICY.md`, `REVIEW_GATES.md`
- `docs/abi.md`, `docs/repository-layout.md`
- This delegation packet and current `workflow-state.yaml`

## Required immutable inputs

- G2 approval: `agents/protocol-modeler/g2-model-001/reviews/g2-analysis-review.md`, delivery `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, blob `bbe2703fc2ca309cd5f0948d973a6027d5f21d96`, SHA-256 `10eb209f071fb2c7f976590be4f732a59bd72120082b576a13b5805e87e12989`.
- Semantic candidate: `agents/protocol-modeler/g2-model-001/protocol-model.yaml`, delivery `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, blob `07d2096667cd6c150ba37bf6c19976ef75f30272`, SHA-256 `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd`.
- G3 handoff: `agents/protocol-modeler/g2-model-001/handoffs/model-to-api-g3.md`, delivery `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, blob `106b035b107357c0df524c65e318a9c0d5491024`, SHA-256 `6c4736c86e44382ff039bd19782f2d5b798ed49264155197f3a3187e3e705b60`.
- Approved analysis and decision: `agents/protocol-analyst/analysis-001/protocol-analysis.md` and `decisions/dns-extension-and-qtype-profile.md`, Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444` and `38746ca8f26735bae37643ae2ffc17ec652ee89c9b027fcbf5dfca4d81b082c9`.
- Current shared state and G2 state-verification: `workflow-state.yaml`; `agents/protocol-orchestrator/g3-api-routing-001/g2-state-verification.md`.

## Exact allowed writes

- `agents/protocol-api-designer/g3-api-001/README.md`
- `agents/protocol-api-designer/g3-api-001/reviews/g3-model-review.md`
- If and only if G3 review is APPROVED: `agents/protocol-api-designer/g3-api-001/api-design.md`, `decisions/`, `handoffs/`, and `completion-report.md`.
- If G3 is not approved: do not create `api-design.md`; create only the assigned review record and a completion report/handoff inside this workspace that preserves the blocking/return route.

All other paths are read-only, including every shared workflow file and all source/API/header/test/vector/binding paths.

## Expected outputs and acceptance

1. `reviews/g3-model-review.md` uses the gate-review contract; records fresh reviewer identity, independent-author declaration, exact immutable inputs, G3 disposition, evidence, and return route.
2. It checks `DNS-REQ-001` through `DNS-REQ-027`, semantic domains, state/events, incremental TCP consumption, correlation, TC fallback, terminal cleanup, ownership/result atomicity, errors, limits, exclusions, and absence of language/ABI/parser coupling.
3. If APPROVED, `api-design.md` is a conditional G4 candidate only: explicit ownership, borrowed/owned lifetimes, errors, buffers, incremental/session semantics, cancellation/threading, capability/version evolution, and compatibility constraints. No public header is changed.
4. README, decisions/handoff where needed, and `completion-report.md` exist and state no shared/prod changes. Completion status is READY_FOR_REVIEW when G3 approves; otherwise it accurately records BLOCKED/CHANGES_REQUESTED and exact responsible return role.
5. Verify the final diff is limited to this assignment workspace. Commit only completed leaf artifacts with `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- <git args>`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, read back `git ls-remote origin refs/heads/hermes/dns-implementation-20260913`, and leave the worktree clean.

HANDOFF TARGET: protocol-orchestrator / `g3-api-routing-001` with exact output paths, commit, remote ref, disposition, and blocker/next-role evidence. The leaf must not alter shared state.

DELEGATION ALLOWANCE: none. No further delegation.
