# Delegated task

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-security-review-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | protocol/dns |
| Owner role | protocol-orchestrator |
| Status | IN_PROGRESS |
| Revision | routing baseline `e8040f62880b2411049c9e8e97b5f8db7699459f` |
| Source artifacts | Exact paths/revisions below |
| Assumptions | G7 remains approved at the stated corrective subject unless fresh review evidence proves otherwise. |
| Open questions | None at routing; reviewer must record any evidence gap. |
| Limitations | This delegation does not configure the child model or authorize remediation, fuzzing, G9, or later stages. |

ACTIVE ROLE: security-reviewer

ROLE: security-reviewer

GOAL: Independently perform the designated G8 security review of the approved native DNS delivery and record one evidence-backed G8 disposition.

SCOPE: Security review only. Assess the G7 evidence, security/threat model, implementation diff/revision, approved analysis/model/API/vectors, and native test evidence for hostile-input and network behavior. Do not implement, revise canonical truth/tests, run fuzzing as G9, or route any subsequent stage.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, security-reviewer row.
- Requested provider/model ID: `gpt-5.6-sol`.
- Requested reasoning effort: `high`.
- Observed runtime provider/model/effort: unknown at routing; parent runtime is `gpt-5.6-terra`, and packet text does not configure a child.
- Verification source: no child runtime metadata exposed before dispatch.
- Context target: 8,000–16,000 task-specific tokens; required reading remains complete.
- Completion summary target: 200–400 words plus artifact paths.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction only if a review-record defect is found; do not retry missing input or an upstream technical defect.
- Escalation trigger and next model/effort: unresolved adversarial interaction across components → `gpt-6-astra`/high only after documented Sol failure; otherwise hand off/block.
- Stop/checkpoint condition: missing/stale prerequisite, conflicting write boundary, unavailable independent identity, actual hard cap, or a completed G8 record.

## Target

Protocol `dns`; workflow stage `security`; gate `G8`; dependency `native_verification`/G7 is APPROVED. G9/fuzzing and every later stage remain NOT_STARTED and are outside this assignment.

## Repository and workspaces

- Repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/`
- Workspace owner: a fresh independent `security-reviewer` leaf assigned to `g8-security-review-001`; it must declare it did not author the reviewed implementation, G7 reviewer artifacts, or any remediation/fix.
- Shared source directories: none.
- Shared-file writer / ordering: only protocol-orchestrator updates `workflow-state.yaml`; reviewer writes only its workspace.
- Existing-path exception: none.

## Workflow / assignment

`dns-implementation-20260913` / `security` / `g8-security-review-001`; shared state is `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` and is read-only.

## Read first

- `AGENTS.md`
- `.hermes/skills/security-reviewer/SKILL.md`
- `docs/agentic/SECURITY_MODEL.md`
- `docs/agentic/HANDOFFS.md`
- `docs/agentic/REVIEW_GATES.md` (G8 and G9 boundary)
- `docs/agentic/DIRECTORIES.md`
- `docs/agentic/MODEL_POLICY.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- This delegation packet

## Required immutable inputs

- G7 corrective subject: `4b801fbdf782c4aca4c6427ad930a48cb5e029ee`; corrective source digest `6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88`.
- G7 approval record: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/test-report.md` at git `1424debe5395a1650a05d2933ba01234c589e535`, sha256 `a9b0504305333ec073bbce88b94fcc19ec2438f08e02685d4ea933e0d34a3236`.
- G7 reviewer completion: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/completion-report.md` at git `1424debe5395a1650a05d2933ba01234c589e535`, sha256 `cdbf4f4c50427a328491d3c8f230b73eb39309bbe938928407eb2d3b56e2a77f`.
- Original G7 findings/test evidence: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-native-verification-001/test-report.md` and `handoffs/dns-g7-001-local-label-validation.md`.
- G6 implementation evidence: `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/implementation-report.md` and completion report; G6 readiness evidence: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g6-implementation-routing-001/verification/g6-implementation-readiness-verification.md`.
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md`, git `3b20866323491799ac4d3c29d8b9151da1472bfe`, sha256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Approved model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml`, git `f26745472178649a60f2cb079937d1bbe3f13c0b`, sha256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- Approved API: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md`, git `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, sha256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`.
- Approved vectors: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/vector-set.json`, git `b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, sha256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`.
- Threat model: `docs/agentic/SECURITY_MODEL.md`.
- Read-only implementation and tests at the corrective subject: `include/ratatoskr/dns.h`, `src/core/`, `src/protocols/dns/`, `tests/dns/`, `tests/integration/`, `tests/fixtures/dns/`, `CMakeLists.txt`, and `tests/CMakeLists.txt`.
- Routing baseline / remote tracking ref before this assignment: `e8040f62880b2411049c9e8e97b5f8db7699459f` for both local HEAD and `origin/hermes/dns-implementation-20260913`.

## Allowed changes

Only these new reviewer-owned paths:

- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/security-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/reviews/g8-security-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/handoffs/` (only a formal handoff when needed)
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/completion-report.md`

## Read-only / forbidden paths

- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`; request, manifest, all existing agent workspaces, and all upstream evidence.
- All production source/headers, tests, vectors, fuzzers, bindings, docs, build files, and CI.
- No changes outside the five concrete reviewer outputs above.
- Do not commit, push, merge, or invoke a new specialist. If Git inspection is needed, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role security-reviewer -- <git args>`.

## Expected outputs

- `security-review.md`: adversarial review with assets/attackers/entrypoints/trust boundaries, assessed classes, exact subject/evidence revisions, findings (or explicit none), severity/rationale, owner, blocker status, remediation/re-review criteria, residual risk and limitations.
- `reviews/g8-security-review.md`: designated G8 record with reviewer identity/independence declaration, exact input revisions, evidence checks, and exactly one disposition: APPROVED, CHANGES_REQUESTED, REJECTED, or BLOCKED.
- `completion-report.md`: standard fields, actual route/usage or unknown, output revisions, and next role or return route.
- Formal handoff only when a blocking finding or missing input needs a responsible owner.

## Acceptance / disposition rules

- A G8 APPROVED disposition requires no unresolved blocking finding and explicit residual risks within scope.
- Do not self-approve any implementation/fix. A code defect returns to `c-protocol-implementer`; API safety returns to `protocol-api-designer`; semantic interpretation returns to `protocol-analyst` (and researcher if source authority is missing).
- Any unresolved mandatory evidence, uncertain risk disposition, or inability to establish independence is BLOCKED rather than approval.
- CHANGES_REQUESTED/REJECTED must identify finding IDs, exact evidence/revisions, owner, required remediation, and fresh independent G8 re-review requirement.
- No-op is permitted only as a documented review finding of no new artifacts beyond the required records; it is not a G8 approval without all required assessment evidence.

## Reporting target

Return the completed artifacts and exact G8 disposition to `protocol-orchestrator` through this workflow. Do not update shared state. The orchestrator alone verifies delivery and records a state change only if this leaf actually completes.

## Delegation allowance

No further delegation.

## Context contract

You have fresh context. Read the role and all required contracts, announce `ACTIVE ROLE: security-reviewer`, verify prerequisite approvals and boundaries, and do not perform another role's work. Do not route G9 or any later stage.
