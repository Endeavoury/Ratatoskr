# Delegated task — G4 binding-safety remediation

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-g4-binding-safety-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | Dispatch baseline `6126fa3f076614f69864186d9e9aa8223c3c024f` |
| Source artifacts | Exact paths and revisions listed below |
| Assumptions | G3 remains approved; only the recorded G4 binding-safety findings require author remediation. |
| Open questions | ABI compatibility remains solely for a later independent compatibility reviewer. |
| Limitations | This is documentation/design work only; no header or implementation realization is authorized. |

ACTIVE ROLE: protocol-api-designer

ROLE: protocol-api-designer

GOAL: Author one new immutable G4 native API-design candidate that resolves binding-safety findings `F-BIND-001` and `F-BIND-002`, without authoring any review, compatibility conclusion, header, source, test, vector, or binding work.

SCOPE: Corrective native API-design authoring only. Read the prior candidate as read-only evidence. Create a new candidate in the assigned new workspace and write only the `Resolution` section of the origin binding-safety handoff. Do not route or perform fresh binding re-review, compatibility review, vectors, or any later stage.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-api-designer row.
- Requested provider/model ID: `gpt-5.6-sol`.
- Requested reasoning effort: `medium`.
- Observed child runtime provider/model/effort: unknown at dispatch. Parent session observation is `openai-codex` / `gpt-5.6-terra`; it is not evidence of the child route.
- Verification source: child completion report must record runtime metadata only if exposed; prompt model naming does not configure runtime.
- Context target: 8,000–16,000 task-specific tokens while reading all required sources in full.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one bounded evidence-driven correction attempt; if the same acceptance defect remains, record a concise blocker/handoff and escalate the unresolved bounded API-design problem instead of retrying indefinitely.
- Escalation trigger and next setting: unresolved complex ownership, streaming/callback ABI, or binary-evolution problem after the bounded correction; `gpt-5.6-sol` / `high` in a separately compatible configured session.
- Stop/checkpoint: missing or contradictory approved inputs; a quota/rate-limit error; or inability to meet the allowed-write boundary.

These are assignment metadata, not Hermes configuration. Do not claim the requested model was active merely because it appears in this packet.

## Target and directories

- Target: `protocol/dns`, workflow `dns-implementation-20260913`, stage `native_api_design`, gate G4, assignment `g4-binding-safety-remediation-001`.
- Absolute repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/`.
- Workspace owner: this leaf assignment only.
- Shared source directories: none.
- Shared-file writer/order: only this leaf may update the `Resolution` section of the origin handoff after its candidate is authored; protocol-orchestrator alone updates `workflow-state.yaml` after delivery verification.
- Existing-path exception: origin handoff `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/handoffs/g4-binding-safety-to-api-designer.md`, `Resolution` section only.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-api-designer/SKILL.md`
3. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md}`
4. `docs/abi.md` and `docs/repository-layout.md`
5. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
6. This packet and the origin binding-safety handoff/review.

## Required immutable inputs

- G3 approved semantic model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- G3 approval record: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at Git `865fa190ee19e041c5ddfab8279b49829baaa240`.
- Analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- ABI baseline: `include/ratatoskr/` and `docs/abi.md` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.
- Prior candidate, read-only evidence: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/api-design.md` at Git `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`, SHA-256 `4e8c33beecf48a2a55d83183de7dd100c934fa874661a97ae7e25f67277d597d`.
- Mandatory return handoff: `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/handoffs/g4-binding-safety-to-api-designer.md`.
- Binding-safety review: `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/reviews/g4-binding-safety-review.md`.

## Allowed changes

Only these paths may change:

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/api-design.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/decisions/` (only needed records)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/handoffs/` (only needed records)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/completion-report.md`
- Only the `## Resolution (destination role)` section of `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/handoffs/g4-binding-safety-to-api-designer.md`.

Everything else is read-only, including `workflow-state.yaml`, all source, headers, tests, bindings, vectors, docs, request, manifest, reviews, and every other specialist artifact. Do not modify `master`, merge, or create implementation/header realizations.

## Expected outputs and acceptance

1. A new `api-design.md` immutable candidate with exact input revision/digest provenance that resolves both findings at design level:
   - Concrete fixed-width public type/layout contracts for all exposed event/state/transport-failure/error-class values; explicit fields, field validity on each documented return/event path, initialization, and `struct_size`/reserved/versioning/evolution rules where applicable.
   - A named DNS error-class accessor/operation with its input/output and validity contract.
   - Explicit `name` C-string/text encoding, NUL, nullability and lifetime rules.
   - Explicit endpoint address pointer/length representation, nullability, lifetime, and validity rules.
   - No public header/code realization.
2. `README.md`, any necessary decision/handoff records, and `completion-report.md` with `STATUS: READY_FOR_REVIEW`, exact artifact digests/revisions, checks actually run, runtime metadata/unknown, and the bounded attempt record.
3. The origin handoff’s Resolution section names the new candidate path/revision, states how F-BIND-001/F-BIND-002 were addressed, and sets destination status `READY_FOR_REVIEW`; do not alter other handoff text.

A new candidate is not a G4 approval. Fresh independent binding-safety re-review and separate compatibility review remain mandatory but are explicitly not authorized here.

## Delivery and stop conditions

Before committing/pushing, independently inspect and verify regular executable wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`; use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- <git arguments>` for delivery. Verify branch `hermes/dns-implementation-20260913`, origin `https://github.com/Endeavoury/Ratatoskr.git`, exact allowed-path diff, and `git diff --check`. Commit only allowed outputs and the permitted origin-handoff Resolution section. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back `origin/hermes/dns-implementation-20260913` and record the exact matching commit.

If any quota/rate-limit error occurs, stop immediately and make no state changes; report only the concise quota blocker. If inputs are missing/stale, wrapper delivery fails, boundaries cannot be met, or the findings cannot be resolved without an upstream decision, do not broaden scope or delegate; write a truthful authorized blocker record and return it. No further delegation is allowed.

HANDOFF TARGET: protocol-orchestrator for delivery verification only. Do not request, route, or perform review work.
