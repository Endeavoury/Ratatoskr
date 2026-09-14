# Delegated task — fresh G4 compatibility re-review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-delegation-g4-compatibility-rereview-001` |
| Workflow ID / project | `dns-implementation-20260913` / `Ratatoskr` |
| Target | `protocol/dns`, corrective API-design candidate for `C-COMP-001` |
| Owner role | `protocol-orchestrator` |
| Status | `READY_FOR_DISPATCH` |
| Routing baseline | `fb766f3deb0bc0b549c612a5d59eee08d4992b3d` |
| Assumptions | None beyond immutable inputs listed below. |
| Limitations | This is a design-artifact re-review; no realized header/library, runtime, vector, or binding-package evidence exists. |

ACTIVE ROLE: `compatibility-reviewer`.

ROLE / HIERARCHY: `workspace-orchestrator -> project protocol-orchestrator -> compatibility-reviewer`.

GOAL: Independently re-review the fresh corrective native C API design candidate for `C-COMP-001` across existing C ABI, C source API, binding exposure implications, and stated protocol behavior. Produce a G4-support / G12-style disposition. Do not treat this as final workflow G12 and do not approve overall G4: overall G4 requires both mandatory independent support evidence, and only the protocol-orchestrator updates state.

REPOSITORY ROOT / COMMAND CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr` for both.

WORKFLOW / STAGE / ASSIGNMENT: `dns-implementation-20260913` / `native_api_design` G4 support re-review / `g4-compatibility-rereview-001`; shared state is `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` and is read-only to this leaf.

MODEL AND REASONING:
- Policy: `docs/agentic/MODEL_POLICY.md`, compatibility-reviewer row.
- Requested provider/model: `gpt-5.6-sol`; requested effort: `medium`.
- Observed parent runtime: `openai-codex` / `gpt-5.6-terra`; effective effort unknown. This request does not configure the child model; record actual exposed runtime honestly.
- Context target: 8,000–16,000 task-specific tokens while completing every required reading.
- Attempt policy: one evidence-driven correction only; missing/contradictory evidence or repeated quality failure becomes a handoff/blocker, not an invented conclusion.
- Escalation: ABI layout/lifetime/version-negotiation or multi-runtime break may justify `gpt-5.6-sol` / high in a compatible configured session; do not change shared configuration.

READ FIRST:
- `AGENTS.md`; this packet; `.hermes/skills/compatibility-reviewer/SKILL.md`.
- `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,DIRECTORIES.md,REVIEW_GATES.md,MODEL_POLICY.md}`.
- `docs/abi.md` and `docs/migration-dotnet.md` as relevant.
- Current `workflow-state.yaml`; candidate completion; original compatibility report/review/handoff; listed model/analysis and ABI inputs.

REQUIRED IMMUTABLE INPUTS:
1. Corrective candidate `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` at Git `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`.
2. Candidate completion at current delivery state; candidate completion identifies the same candidate revision/digest and `READY_FOR_REVIEW`.
3. Original compatibility report and G12-style support record: `agents/compatibility-reviewer/g4-compatibility-review-001/{compatibility-report.md,reviews/g12-g4-compatibility-support-review.md}` at delivery `0cb6e27b265c38e42d09d61c0883f1a086df8835`.
4. `C-COMP-001` return handoff: `agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/g4-compatibility-to-api-designer-c-comp-001.md`, including Resolution that names the corrective candidate and requires fresh re-review.
5. ABI baseline `include/ratatoskr/` and `docs/abi.md` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.
6. Model/analysis inputs recorded in state: model `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; analysis `agents/protocol-analyst/analysis-001/protocol-analysis.md` at Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
7. Scoped independent binding-safety re-review: `agents/binding-api-designer/g4-binding-safety-rereview-002/reviews/g4-binding-safety-rereview.md` at remote Git `0f0eb9db033f4c26481a302df397184515dc60ad`, SHA-256 `e5ead3b0fa6e966c50b4a3ed7e0999d4001bb4e1b497629252699673b3354bb8`.

ALLOWED WRITES — ONLY THESE LEAF PATHS:
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/compatibility-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/reviews/g12-g4-compatibility-rereview.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/handoffs/` (only a formal handoff if changes/blocker require it)
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/completion-report.md`

READ-ONLY / FORBIDDEN: every other path, including `workflow-state.yaml`, all production/header/source/test/vector/binding/fuzz/docs/request/manifest files, all other workflow-root files, all prior specialist workspaces, and unrelated untracked `agents/binding-api-designer/g4-binding-safety-rereview-001/`. Do not implement, edit the candidate, alter a handoff Resolution, perform routing/state work, commit/push unrelated files, or further delegate.

INDEPENDENCE: You must be a fresh reviewer identity independent of the corrective candidate's author, original candidate authors, original `g4-compatibility-review-001` reviewer, binding-safety reviewers, and all authors of subjects you assess. Declare this explicitly in the gate record. If independence cannot be truthfully established, stop and report `BLOCKED` without technical approval.

EXPECTED OUTPUTS / ACCEPTANCE:
- A `compatibility-report.md` comparing baseline to candidate across C ABI, C source API, binding exposure implications, protocol behavior, migration/version/deprecation implications, C-COMP-001 correction, evidence/limitations, and explicit disposition.
- `reviews/g12-g4-compatibility-rereview.md` with exact input revisions/digests, reviewer identity/independence, evidence table, and one disposition: `APPROVED`, `CHANGES_REQUESTED`, `REJECTED`, or `BLOCKED`.
- A formal handoff in this leaf workspace if changes or missing evidence require an owner action; otherwise state why no handoff is required.
- `completion-report.md` with standard fields, actual validation evidence, and runtime/model metadata.
- The review must say whether it supports G4, but must not claim final workflow G12 or approve G4. No further delegation.

REPORTING TARGET: return concise outcome to the protocol-orchestrator; write only the paths above. The orchestrator's routing completion report and `workflow-state.yaml` are the only shared reporting targets.

STOP CONDITIONS: missing immutable evidence, digest/revision mismatch, boundary conflict, inability to establish independence, quota/rate limit, or completion of the assigned review. On quota/rate limit, stop immediately, do not edit shared state, and report the exact error.