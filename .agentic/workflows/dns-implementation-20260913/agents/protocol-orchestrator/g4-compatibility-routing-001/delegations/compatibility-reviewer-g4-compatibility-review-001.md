# Delegated task — mandatory G4 compatibility support review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-g4-compatibility-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` once this packet is delivered to the single fresh leaf |
| Revision | Routing commit pending delivery; immutable inputs below govern technical review. |
| Assumptions | G3 approval and the remediation candidate evidence remain valid only at the listed immutable revisions. |
| Limitations | This early G12-style evidence is mandatory G4 support only. It cannot approve overall G4 or advance vectors/G5, G6, implementation, bindings, documentation, final review, or any later stage. |

ACTIVE ROLE: compatibility-reviewer

ROLE: compatibility-reviewer, fresh independent leaf

GOAL: Independently assess ABI, source API, binding, and protocol-behavior compatibility impact of the corrected DNS native API-design candidate against the immutable ABI baseline and specified upstream evidence. Write G12-style compatibility evidence as mandatory G4 support, with a clear scoped disposition and proper return route for defects. Do not claim overall G4 authority.

SCOPE: Review-only. Assess the proposed additive native API contract at the exact candidate revision; classify compatibility implications, affected consumers, migration/version/deprecation requirements, and evidence limitations. Do not implement or repair anything, authorize header realization, or decide product policy absent existing policy. A defect must route to the proper owner: native API/design contract to `protocol-api-designer`; implementation deviation to `c-protocol-implementer`; unresolved version/product policy to maintainer via `protocol-orchestrator`.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, compatibility-reviewer row.
- Requested provider/model ID: `gpt-5.6-sol`.
- Requested reasoning effort: medium.
- Observed parent route before delegation: `openai-codex` / `gpt-5.6-terra`; effective effort and usage unknown.
- Actual child route: record only runtime-exposed provider/model/effort telemetry; do not infer it from this packet or claim this request configured Hermes.
- Verification source: child runtime/session metadata if exposed, otherwise `unknown`.
- Context target: 8,000–16,000 task-specific tokens while completing all required reading.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: exactly one bounded review attempt. Do not retry or spawn any child.
- Escalation trigger: ABI layout, lifetime, version negotiation, or multi-runtime break; requested next setting would be Sol/high only in a separately configured session, not by silent in-task escalation.
- Stop/checkpoint: missing/stale/conflicting immutable evidence, boundary conflict, quota/rate-limit error, or any unresolved required product decision. On quota/rate-limit, stop immediately with no child state/commit changes and report exact error.

## Repository and working directories

- Repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/`.
- Workspace owner and reviewer identity: `compatibility-reviewer / g4-compatibility-review-001`, a fresh leaf identity distinct from the candidate authors and all prior G4 binding reviewers. Declare this identity and independence in the G12-style record.
- Shared source directories: none; all ABI/API/code/docs inputs are read-only.
- Shared-file writer / ordering: only `protocol-orchestrator` updates workflow state. Do not modify it.
- Existing-path exception: preserve the unrelated untracked `agents/binding-api-designer/g4-binding-safety-rereview-001/` exactly; it is read-only and outside the review.

## Workflow / stage / assignment

Workflow `dns-implementation-20260913`; stage `native_api_design`; assignment `g4-compatibility-review-001`; shared state `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`. G4 is currently `CHANGES_REQUESTED`, native API design is `IN_PROGRESS`, and G5/G6 remain `NOT_STARTED`.

## Read first

- `AGENTS.md`
- `.hermes/skills/compatibility-reviewer/SKILL.md`
- `docs/agentic/REVIEW_GATES.md` (G4 support boundary and G12 requirements)
- `docs/agentic/ARTIFACTS.md`
- `docs/agentic/HANDOFFS.md`
- `docs/agentic/DIRECTORIES.md`
- `docs/agentic/MODEL_POLICY.md`
- `docs/abi.md` and `docs/migration-dotnet.md` when relevant
- this packet and current workflow state

## Required immutable input artifacts

1. Corrected candidate: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/api-design.md` at Git `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`.
2. Candidate completion: same path workspace `completion-report.md` at Git `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6de8c06709d92d5b99eac797e6c7b974e05f5f75630f6342fd13a639231bb55e`.
3. ABI baseline: `include/ratatoskr/` and `docs/abi.md` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; at minimum verify `docs/abi.md` SHA-256 `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b` and `include/ratatoskr/dns.h` SHA-256 `d8d316792368150c6157001c4f5efa7b0420c5cac6ff95d81387cf942ca34ff5`.
4. Original G4 binding review: `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/reviews/g4-binding-safety-review.md` at Git `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4`.
5. Original return handoff: corresponding `handoffs/g4-binding-safety-to-api-designer.md` at Git `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353`.
6. Scoped fresh binding re-review: `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-rereview-002/reviews/g4-binding-safety-rereview.md` at remote Git `0f0eb9db033f4c26481a302df397184515dc60ad`, SHA-256 `e5ead3b0fa6e966c50b4a3ed7e0999d4001bb4e1b497629252699673b3354bb8`.
7. G3 model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; G3 approval `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at Git `865fa190ee19e041c5ddfab8279b49829baaa240`.
8. G3 analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.

Use the role-controlled wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` for all Git state/immutable reads and delivery, with `--role compatibility-reviewer -- <git arguments>`. Confirm it is a regular executable first. Never substitute raw Git.

## Allowed changes

Only these paths in the assigned leaf workspace:

- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/compatibility-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/reviews/g12-g4-compatibility-support-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/decisions/` (only if needed for the reviewer’s own compatibility rationale)
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/` (only if a finding requires routing)
- `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-review-001/completion-report.md`

All other repository paths, including workflow state, candidate/author artifacts, public headers, code, tests, bindings, docs, vectors, and the orchestrator workspace, are read-only. No delegation allowance.

## Expected outputs

- `README.md`: concrete scope, immutable inputs, and identity/boundary record.
- `compatibility-report.md`: independent ABI/source/binding/behavior comparison; classifications; affected consumers; migration, versioning, and deprecation implications; limitations; and a scoped disposition. It must state this is G12-style compatibility evidence supporting mandatory G4 review only, not overall G4 approval.
- `reviews/g12-g4-compatibility-support-review.md`: G12-style gate record containing exact input revisions/digests, candidate author identities, this fresh reviewer identity, independence declaration, actual model telemetry, checks, and disposition.
- Optional handoff(s): a formal owner-specific return only for a concrete defect/policy blocker.
- `completion-report.md`: standard required fields, truthful model/usage telemetry, one-attempt result, and exact delivery evidence.

## Acceptance criteria

- Independently assesses ABI, source API, binding, and behavior axes against the immutable baseline/candidate; compilation alone is not treated as ABI proof.
- Makes version/deprecation/migration implications explicit, without silently accepting a break or selecting unresolved product policy.
- Records exact revisions/digests, reviewer identity and independence from `protocol-api-designer/g4-api-design-001`, `protocol-api-designer/g4-binding-safety-remediation-001`, `binding-api-designer/g4-binding-safety-review-001`, and `binding-api-designer/g4-binding-safety-rereview-002`.
- Does not claim overall G4 authority or update G4/G5/G6/state; defects route only to their proper owner.
- Uses the wrapper for any Git commit/push, pushes only `HEAD:refs/heads/hermes/dns-implementation-20260913`, and wrapper-fetches/reads back that exact remote ref after each commit/push.
- Preserves the unrelated historical untracked directory exactly.

## Handoff target

Return only to `protocol-orchestrator / g4-compatibility-routing-001` through the child completion report and any owner-specific handoff. The orchestrator alone verifies delivery and records state; it must not convert your scoped disposition into overall G4 approval without all required gate evidence.

## Stop conditions

Stop and produce only permitted blocker/completion records when an immutable input is missing, stale, mismatched, or contradictory; when reviewer independence cannot be declared; when a required policy decision is absent; when wrapper capability fails; or on quota/rate-limit. Do not modify state, approvals, technical artifacts, or later stages.
