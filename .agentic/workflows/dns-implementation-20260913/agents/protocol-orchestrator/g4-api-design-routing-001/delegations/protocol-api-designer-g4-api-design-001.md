# Delegated task — DNS G4 native API design

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-api-designer-g4-api-design-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `READY_FOR_DISPATCH` |
| Revision | Prepared against G3 reviewer delivery `865fa190ee19e041c5ddfab8279b49829baaa240`; dispatch occurs only after G3 closure remote readback. |
| Source artifacts | Exact G3/model/analysis and ABI input revisions below. |
| Assumptions | Approved scope is the UDP-first unicast DNS stub/client profile; excluded protocol features remain excluded. |
| Open questions | Binding scope is deferred; do not invent a binding surface. |
| Limitations | This assignment authors a proposal only. It cannot approve G4 or alter public ABI/source. |

ACTIVE ROLE: protocol-api-designer

ROLE: protocol-api-designer
GOAL: Author a `READY_FOR_REVIEW` native DNS API design traceable to G3-approved semantic model and current native ABI baseline.
SCOPE: Native API/ABI design artifacts only. Cover capability/operation mapping; opaque handles and ownership/borrowing/allocation/freeing; buffer lengths; error and output-validity rules; UDP/TCP incremental transport, session, cancellation, callbacks/reentrancy/threading where applicable; resource configuration; ABI evolution/version/capability detection; representability and compatibility considerations. No header, C, test, vector, binding, documentation, config, state, or later-stage work.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-api-designer row.
- Requested provider/model ID: `gpt-5.6-sol`.
- Requested reasoning effort: medium.
- Observed parent runtime provider/model/effort: `openai-codex` / `gpt-5.6-terra` / unknown. The child must record its own exposed runtime truth or `unknown`; this prompt does not configure it.
- Verification source: parent session metadata; child runtime metadata if exposed.
- Context target: 8,000–16,000 task-specific tokens with all required input reading complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction maximum; then write a bounded handoff/escalation instead of repeated retries.
- Escalation trigger and next setting: complex ownership, streaming/callback ABI, or binary evolution may use Sol/high only if actually configured; unresolved semantics return to the owning upstream role.
- Stop/checkpoint condition: missing/stale G3 approval, any boundary conflict, unrepresentable ownership/error behavior, unresolved maintainer compatibility choice, quota/rate error, or completion at `READY_FOR_REVIEW`.

## Target and directories

- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Workflow/stage/assignment: `dns-implementation-20260913` / `native_api_design` (G4) / `g4-api-design-001`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/`.
- Workspace owner: this leaf only; no shared-file writer is assigned.
- Shared source directories: none writable. Existing headers are read-only design inputs.

## Read first

- `AGENTS.md`
- `.hermes/skills/protocol-api-designer/SKILL.md`
- `docs/agentic/{HANDOFFS,DIRECTORIES,ARTIFACTS,REVIEW_GATES,MODEL_POLICY,ARCHITECTURE}.md`
- `docs/abi.md` and `docs/repository-layout.md`
- `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml,request.md}`
- this packet and the G3 evidence below.

## Required input artifacts

- G3 independent approval: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at delivery Git `865fa190ee19e041c5ddfab8279b49829baaa240`.
- G3-approved semantic model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Closure evidence: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g4-api-design-routing-001/g3-state-closure-verification.md` at the G3 closure commit recorded by state.
- Current ABI inputs: `include/ratatoskr/` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` (tree SHA-256 `93c781c12692de0245624115d0581d276abfd077c0ca94ad3af662a2e23134cf`); `docs/abi.md` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`, SHA-256 `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b`; `docs/repository-layout.md` at Git `42b0611efa90e4b62f06d07cca64044ae9f090a7`, SHA-256 `f5f0276ed9137ba838fbc78b143eb04f52176f74efc1dfdbc1f9ad1dc4962d17`.

## Allowed changes

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/api-design.md`
- Files under that workspace’s `decisions/` and `handoffs/` only.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/completion-report.md`

All other paths are read-only, including workflow state, every upstream workspace, `include/ratatoskr/`, `src/`, `tests/`, `fuzz/`, `bindings/`, `docs/`, configuration, credentials, and every other agent workspace.

## Expected outputs and acceptance

- A complete `api-design.md` that maps approved requirements/model elements/capabilities to proposed native operations and explicitly specifies ownership, borrowing, allocation/freeing, errors/output validity, buffer/input consumption, incremental transport/session/cancellation/threading behavior, and ABI/evolution/compatibility considerations.
- Decisions/handoffs only when evidence requires them; no invented resolution of upstream or maintainer decisions.
- Standard completion report reporting `READY_FOR_REVIEW`, actual runtime/usage truth, checks performed, limitations, and a G4-review handoff target.
- Commit and push only completed allowed leaf output paths using `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- git ...`; before commit/push verify branch/ref/staged scope and `git diff --check`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref.

## Handoff and stop conditions

Handoff target: `protocol-orchestrator` for delivery verification and routing of the designated independent G4 review; do not self-approve G4 or route vector design.

Stop immediately with no further state change on a quota/rate error. Stop and write a bounded blocker/handoff for missing/stale G3 evidence, scope conflict, required public-ABI change that lacks a safe proposal, or unresolved compatibility/product decision. Do not delegate further.

CONTEXT CONTRACT: You have fresh context. Read the listed instructions and current state, announce the active role, verify prerequisites and boundaries, and do only this assignment. Do not update shared workflow state.
