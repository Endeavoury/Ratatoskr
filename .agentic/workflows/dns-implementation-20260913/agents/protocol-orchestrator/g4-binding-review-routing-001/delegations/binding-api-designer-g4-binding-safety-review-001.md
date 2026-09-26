# G4 binding-safety independent review delegation

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-binding-api-designer-g4-binding-safety-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | `git:c2ab2aa30496edf70163b46b9572c0b155488eb4` |

ACTIVE ROLE: binding-api-designer

ROLE: binding-api-designer, designated independent G4 binding-safety reviewer.
GOAL: Independently assess only the binding-safety portion of the READY_FOR_REVIEW DNS native API candidate and record one G4 review disposition: `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED`.
SCOPE: Review-only. Do not author binding design, native API/model/ABI truth, implementation, vectors, tests, bindings, documentation, or workflow state. Do not route compatibility review or any later stage. You are independent of `protocol-api-designer/g4-api-design-001` and must state that you did not author or edit its candidate.

MODEL AND REASONING:
- Policy: `docs/agentic/MODEL_POLICY.md`, binding-api-designer row.
- Requested: `gpt-5.6-terra` / `medium`.
- Observed runtime: record actual provider/model/effort only if exposed; current parent evidence is `openai-codex` / `gpt-5.6-terra`, effort unknown. A prompt does not switch model.
- Attempt policy: one complete evidence review; no speculative retries.
- Stop/checkpoint: quota/rate error means stop immediately with no state changes and return the error without writing artifacts. Missing/stale inputs or unsafe/unrepresentable behavior require a bounded handoff and `BLOCKED` or `CHANGES_REQUESTED` as applicable.

REPOSITORY ROOT AND COMMAND CWD:
`/home/hermes/hermes-workspace/projects/Ratatoskr`

WORKSPACE:
`.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/`

READ FIRST:
- `AGENTS.md`
- `.hermes/skills/binding-api-designer/SKILL.md`
- `docs/agentic/{HANDOFFS,DIRECTORIES,ARTIFACTS,REVIEW_GATES,BINDING_LIFECYCLE,MODEL_POLICY}.md`
- `.agentic/workflows/dns-implementation-20260913/{request.md,manifest.yaml,workflow-state.yaml}`
- this delegation packet

REQUIRED INPUTS (READ-ONLY):
- Candidate: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/api-design.md` at delivery `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`.
- Candidate completion report at that same delivery.
- Approved G3 review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at `865fa190ee19e041c5ddfab8279b49829baaa240`.
- ABI baseline: `include/ratatoskr/` and `docs/abi.md` at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.

ALLOWED WRITES ONLY:
- `README.md`
- `reviews/g4-binding-safety-review.md`
- `handoffs/` (only if required by your disposition)
- `completion-report.md`
inside your assigned workspace. All other paths are read-only. Do not use Git commit/push; return delivery to this orchestrator.

REQUIRED REVIEW EVIDENCE:
Assess opaque ownership/destruction; pointer/length/output validity; event/error representation; callback/threading and cancellation safety; incremental TCP consumption; capability/deferred-feature signaling; and representability without independent wire parsing. Record exact input revisions/digests where obtainable, reviewer identity/independence, observed evidence, limitations, finding IDs where needed, disposition and return route. Do not propose a replacement design or implementation.

ACCEPTANCE:
A completed reviewer-only record exists at `reviews/g4-binding-safety-review.md`, has an allowed disposition and boundary-respecting evidence, and the standard completion report names the mandatory still-unperformed compatibility review. Your review alone cannot pass G4.

HANDOFF TARGET:
`protocol-orchestrator`, using your completion report and any necessary bounded handoff. No further delegation is allowed.
