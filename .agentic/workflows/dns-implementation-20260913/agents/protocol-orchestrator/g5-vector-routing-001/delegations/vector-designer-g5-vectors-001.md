# Delegated task — G5 canonical DNS vectors

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-g5-vectors-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Baseline | `fe1f99c03ad32241909935947d8d3dfa641759b0` on `hermes/dns-implementation-20260913` |

ACTIVE ROLE: vector-designer

ROLE: vector-designer

GOAL: Author the authoritative, language-independent candidate canonical DNS vector set grounded only in approved G1/G2/G3/G4 inputs, then submit a G5 handoff for independent review.

SCOPE: G5 vector authoring only. This is a candidate and must be `READY_FOR_REVIEW`; do not approve G5, update shared workflow state, or route G6/later work. Do not use production code, a parser, builder, test, or binding as an oracle. No further delegation is allowed.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, vector-designer row.
- Requested provider/model ID: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed parent route: `openai-codex/gpt-5.6-terra`; effective effort unknown. Naming this requested setting does not configure Hermes.
- Context target: 8,000–16,000 task-specific tokens; all required reading remains complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction; then return a bounded handoff/blocker.
- Escalation: bit-level ambiguity or complex temporal expectations → Sol/high only in a compatible configured session; missing truth returns upstream.
- Stop: missing/stale/contradictory approved input, byte expectations not independently justifiable, boundary conflict, or completed candidate.

## Hierarchy and locations

- Root task ID: `dns-implementation-20260913`; project ID: `Ratatoskr`.
- Hierarchy: workspace-orchestrator → protocol-orchestrator → vector-designer (leaf).
- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Workflow state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` (read-only).
- Your unique artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/`.
- Parent routing workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g5-vector-routing-001/` (read-only).
- Shared source directories: none.
- Shared-file writer/order: only protocol-orchestrator writes workflow state; return to protocol-orchestrator after authoring.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/vector-designer/SKILL.md`
3. `docs/agentic/{ARTIFACTS.md,ARCHITECTURE.md,HANDOFFS.md,DIRECTORIES.md,REVIEW_GATES.md,MODEL_POLICY.md,PROTOCOL_LIFECYCLE.md}`
4. This packet and current workflow state.
5. Approved inputs and their records below, including G4 closure verification.

## Required input artifacts and revisions

- G1 inventory approval: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/reviews/g1-inventory-review.md`.
- Approved analysis: `agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Approved G2: `agents/protocol-modeler/g2-model-001/reviews/g2-analysis-review.md`.
- Approved model/G3: `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; approval `agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md`.
- G4 candidate: `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` at `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`.
- G4 administrative closure: `agents/protocol-orchestrator/g5-vector-routing-001/g4-closure-verification.md`.
- Scope/manifest/request remain read-only: `.agentic/workflows/dns-implementation-20260913/{request.md,manifest.yaml}`.

## Allowed writes — exact and exclusive

- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/vector-set.json`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/decisions/` (only needed decision records)
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/handoffs/` (required G5 review handoff)
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/completion-report.md`

All code, headers, CMake, tests, fuzz, docs, bindings, prior role workspaces, request, manifest, workflow-state, and every path outside the five entries are read-only/forbidden.

## Acceptance criteria

1. `vector-set.json` is canonical, language-independent, schema-valid where possible, and uses exact hex bytes (or justified base64), lengths/framing, logical inputs/events, expected outputs/consumption/state/error, requirement IDs, and source provenance.
2. Coverage explicitly includes positive, malformed/negative, boundary, unknown-value/extension, and interaction/stateful cases demanded by approved semantics; TCP cases include ordered events, correlation, consumption, and terminal cleanup where applicable.
3. Byte encodings/offsets are independently checked against approved sources; no production implementation/harness/binding output is used as an oracle.
4. A handoff to protocol-orchestrator identifies the independent G5 review needed: protocol-test-engineer plus independent protocol-analyst interpretation review, with coverage/gaps and exact candidate revision/digest.
5. Completion report is `READY_FOR_REVIEW`, records actual checks and limitations, and does not claim G5 approval or G6 readiness.

## Handoff and stop behavior

Write the required handoff in your workspace to `protocol-orchestrator`; do not update workflow state. If inputs are missing, stale, contradictory, or an expectation cannot be justified, write a blocking/needs-upstream-change handoff and completion report without authoring speculative vectors. Do not delegate further.