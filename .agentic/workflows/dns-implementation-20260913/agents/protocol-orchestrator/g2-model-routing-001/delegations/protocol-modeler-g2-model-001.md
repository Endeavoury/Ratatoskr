# Delegated task — independent DNS G2 review and conditional semantic model

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-modeler-g2-model-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-orchestrator |
| Status | IN_PROGRESS |
| Revision | Git `d59fe8a06ad8a3d4f525c86057406f65c2b1c20d` at assignment preparation; routing commit pending |
| Source artifacts | Analysis candidate and G2 handoff at the recorded commit; G1 approval record |
| Assumptions | G1 is approved only for its recorded inventory revisions. |
| Open questions | Resource budgets and retry/server-selection policy remain API/product decisions; binding scope is deferred. |
| Limitations | G2 review is the only approval action in scope; any semantic model is a G3 candidate only. |

ACTIVE ROLE: protocol-modeler

ROLE: protocol-modeler, independent G2 reviewer and conditional model author
GOAL: Independently review the submitted DNS analysis for G2. Only if the G2 disposition is APPROVED, author a language-independent DNS semantic-model candidate marked READY_FOR_REVIEW; do not claim G3 approval.
SCOPE: Review/modeling artifacts only. No implementation, API, vectors, tests, fuzzing, docs, bindings, request/manifest/state edits, merges, or master changes.

## Model and reasoning
- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-modeler row.
- Requested provider/model ID: `gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: `gpt-5.6-terra`; effort unknown (parent runtime metadata exposes no effective effort).
- Verification source: parent Hermes session metadata; effort must not be inferred from this packet.
- Context target: 8,000–16,000 task-specific tokens, with all required reading complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction only; then stop and hand off unresolved upstream truth.
- Escalation trigger and next setting: coupled state-machine or semantic-invariant problem → Sol/high in a separately configured session; do not silently change model.
- Stop/checkpoint: failed G2, missing G1/input evidence, upstream ambiguity, or completed conditional output.

TARGET: DNS native unicast stub/client semantic profile; dependencies are selected upstream resolver and OS network stack.

REPOSITORY ROOT: `/home/hermes/hermes-workspace/projects/Ratatoskr`

## Working directories
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/`.
- Workspace owner: protocol-modeler / `g2-model-001` / independent child identity (record actual agent ID).
- Shared source directories: none.
- Shared-file writer / ordering: protocol-orchestrator is sole `workflow-state.yaml` writer; modeler writes only the concrete paths below. G2 review must be completed before creating `protocol-model.yaml`.
- Existing-path exception: none.

WORKFLOW / STAGE / ASSIGNMENT: `dns-implementation-20260913` / analysis G2 review then conditional modeling G3 candidate / `g2-model-001`; shared state `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` is read-only.

## Read first
- `AGENTS.md`
- `.hermes/skills/protocol-modeler/SKILL.md`
- `docs/agentic/ARCHITECTURE.md`
- `docs/agentic/ARTIFACTS.md`
- `docs/agentic/HANDOFFS.md`
- `docs/agentic/DIRECTORIES.md`
- `docs/agentic/REVIEW_GATES.md` (G2 and G3)
- `docs/agentic/MODEL_POLICY.md`
- `docs/agentic/PROTOCOL_LIFECYCLE.md`
- This packet.

## Required input artifacts
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` @ Git `d59fe8a06ad8a3d4f525c86057406f65c2b1c20d`; G1 status APPROVED, G2 candidate reviewable.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` @ Git `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/decisions/dns-extension-and-qtype-profile.md` @ Git `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/handoffs/analysis-to-modeler-g2.md` @ Git `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/reviews/g1-inventory-review.md` @ Git `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- G1 inventory source references named in those artifacts, read-only, for independent verification.

## Files/directories allowed to change
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/README.md` — concrete scope/read-first record.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/reviews/g2-analysis-review.md` — designated independent G2 record with exact input revision/content hashes and disposition.
- Only if G2 is APPROVED: `protocol-model.yaml`, `decisions/`, `handoffs/model-to-api-g3.md`, and `completion-report.md` within that same assignment workspace.
- If G2 is not APPROVED: no model candidate; write only G2 review, a handoff if required, and completion report within this workspace.

## Files/directories that must remain read-only
- Entire workflow root including request, manifest, state, and all other agent workspaces except reading inputs.
- Source, headers, CLI, tests, fuzz, docs, bindings, build/configuration, and all paths outside the explicit set.

## Expected output artifacts
- `reviews/g2-analysis-review.md`: G2 APPROVED / CHANGES_REQUESTED / REJECTED / BLOCKED; exact revision evidence, independent reviewer identity, criterion-by-criterion findings and return route.
- If and only if G2 APPROVED: `protocol-model.yaml`, with requirement-to-model trace, entities/domains/messages, request/context/framing/error/state lifecycle, resource/atomic-result invariants, dependencies/extensions/exclusions; status READY_FOR_REVIEW, explicitly not G3-approved.
- If and only if G2 APPROVED: `handoffs/model-to-api-g3.md`, READY_FOR_REVIEW route to protocol-api-designer after independent G3 review.
- `completion-report.md` with actual model/runtime evidence or unknown, checks, boundaries and next role.

## Acceptance criteria
1. Reviewer is demonstrably independent from analyst `analysis-001` and records identity/revision evidence.
2. G2 assesses all requirements for observable layout, framing, incremental input, correlation, state, errors, resource limits, security and extension behavior; local policy is not represented as RFC mandate.
3. No semantic model exists unless G2 is approved; G2 failure returns to protocol-analyst/researcher/orchestrator by explicit route.
4. Conditional model is language-independent and covers every approved requirement, including stateful and ownership semantics, without ABI/C/wire-parser design; it is marked READY_FOR_REVIEW and G3 remains NOT_STARTED.
5. Validate only artifact structure/traceability and changed-path boundary; do not run or modify production code.
6. Before completing, commit only your allowed artifacts using `git-agent.sh protocol-modeler ...` role identity, push `HEAD:refs/heads/hermes/dns-implementation-20260913`, and read back the remote ref. If the required helper is unavailable, do not substitute an unverified identity: record BLOCKED and report exact command/output.

HANDOFF TARGET: protocol-orchestrator via the child completion report; if G2 passes, include a READY_FOR_REVIEW G3 handoff for protocol-api-designer but do not assign it.

STOP CONDITIONS: Missing/stale G1 approval or analysis input; inability to maintain reviewer independence; analysis ambiguity requiring upstream change; no available `git-agent.sh` helper for required delivery; completed review and conditional candidate.

DELEGATION ALLOWANCE: No further delegation.

CONTEXT CONTRACT: You have fresh context. Read the role before work, announce ACTIVE ROLE, verify scope/input approvals, and obey role boundaries. Do not update shared workflow state. Do not perform another role's work. Write the standard completion report at `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/completion-report.md`.
