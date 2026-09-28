# Delegated task — independent G7 native DNS verification

| Field | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g7-native-verification-001-delegation` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` after routing delivery readback and leaf dispatch |
| Baseline for this assignment | `855c897c46c053978ae72b4dab6bda356bf4168d` |
| Implementation subject | `eaa191ba25fde6b4224e0cacccee92adbdfd5701`, included in baseline |
| Child workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-native-verification-001/` |

ACTIVE ROLE: protocol-test-engineer

ROLE: protocol-test-engineer

GOAL: Independently review the submitted G6 native DNS implementation against approved inputs, determine and record honest feasible native test/build evidence, and return a G7 report to the protocol-orchestrator. Do not approve your own harness and do not claim G7 passed.

SCOPE: One independent G7 evidence/review assignment only. This is neither implementation repair nor canonical-truth work. Author narrowly scoped regression/harness tests only where necessary to establish independent G7 evidence. Do not route or begin security/G8, fuzzing, bindings, documentation, compatibility, or any later stage.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, `protocol-test-engineer` row.
- Requested provider/model ID / reasoning: `gpt-5.6-terra` / `medium`.
- Observed runtime provider/model/effort: unknown; packet text does not configure Hermes.
- Context target: 8,000–16,000 task-specific tokens; completion target: 200–400 words plus artifacts.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction; then a bounded report/handoff rather than repeated repair attempts.
- Escalate only for nondeterministic state/transport or oracle/harness distinction, via a separately configured Sol/high session; do not silently change routes.
- Stop/checkpoint: missing/stale prerequisite, unapproved truth conflict, scope/boundary conflict, unavailable required capability, quota/rate error, or a finding owned by another role.

## Repository and delivery

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch: `hermes/dns-implementation-20260913`; never merge/push `master`.
- State (read-only): `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
- Stage / assignment: `native_verification` / `g7-native-verification-001`.
- For any commit/push, exclusively use `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- <git args>`; never raw-git commit/push. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref with the same wrapper. If wrapper unavailable, write only allowed local report/handoff/completion evidence and state delivery is unpushed.

## Read first

- `AGENTS.md`
- `.hermes/skills/protocol-test-engineer/SKILL.md`
- `docs/agentic/{ARTIFACTS.md,SECURITY_MODEL.md,REVIEW_GATES.md,DIRECTORIES.md,HANDOFFS.md,MODEL_POLICY.md,WORKFLOW.md,PROTOCOL_LIFECYCLE.md}`
- `docs/contributing.md`
- This packet and `verification/g6-native-delivery-verification.md`

## Required immutable/read-only inputs

- G6 readiness: `agents/protocol-orchestrator/g6-implementation-routing-001/verification/g6-implementation-readiness-verification.md`.
- G6 packet: `agents/protocol-orchestrator/g6-implementation-routing-001/delegations/c-protocol-implementer-g6-native-implementation-001.md`.
- Implementation report/completion: `agents/c-protocol-implementer/g6-native-implementation-001/{implementation-report.md,completion-report.md}` at current baseline `855c897c46c053978ae72b4dab6bda356bf4168d`; subject delivery `eaa191ba25fde6b4224e0cacccee92adbdfd5701`.
- Approved analysis `agents/protocol-analyst/analysis-001/protocol-analysis.md` (`git:5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`).
- Approved model `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` (`git:f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`).
- Approved API `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` (`git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`).
- Approved canonical vectors `agents/vector-designer/g5-boundary-remediation-001/vector-set.json` (`git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`).
- G6 diff: `git diff eaa191ba25fde6b4224e0cacccee92adbdfd5701^..855c897c46c053978ae72b4dab6bda356bf4168d`; inspect implementation only read-only.

## Exact allowed writes

- Own workspace: `README.md`, `test-report.md`, `handoffs/` (only needed formal handoffs), and `completion-report.md`.
- Only if independently necessary after inspecting the existing test layout: `tests/dns/dns_g7_native_verification_tests.c`, `tests/integration/dns_g7_native_verification_test.py`, `tests/fixtures/dns/g7-native-verification-fixtures.json`, and the relevant entries in `tests/CMakeLists.txt` solely to register tests you created. Do not create any other test file or modify registration before inspection.

All production headers/source, workflow state, canonical vectors, analysis/model/API/design records, docs, bindings, fuzz, CLI, root/build configuration, existing tests/fixtures, and all other paths are read-only. Never modify implementation to address a finding. Preserve unrelated untracked workspaces.

## Required evidence and acceptance

- Independently inspect the subject diff and trace relevant approved requirements/API/vector cases to native observables; distinguish code review, parser/ABI/integration evidence, and unexecuted checks.
- Inspect available test/CMake configuration before creating any test or registration. If CMake is absent, do not fake CMake/CTest availability; run only feasible commands and record exact commands, results, environment, revision, case/count evidence, and limitations.
- If a new harness is authored, it remains your authored evidence and cannot self-approve its adequacy. Do not request or create a separate harness-review assignment in this stage; state this limitation faithfully.
- A defect in implementation returns `CHANGES_REQUESTED` with a formal handoff to `c-protocol-implementer`; truth ambiguity returns a handoff to vector-designer or protocol-analyst; insufficient capability returns `BLOCKED` to protocol-orchestrator. No production/test changes are required for a no-op evidence result.
- Write `test-report.md` and `completion-report.md` with exact input/delivery revisions, reviewer independence from `c-protocol-implementer/g6-native-implementation-001`, allowed-path diff evidence, commands/results, findings, status, and no technical self-approval.
- Return exactly one of `READY_FOR_REVIEW`, `CHANGES_REQUESTED`, or `BLOCKED` to `protocol-orchestrator`. `READY_FOR_REVIEW` is evidence submission, never G7 approval. Do not report G7 as passed.

HANDOFF TARGET: `protocol-orchestrator`, through your own `handoffs/` only if needed and your standard completion report.

DELEGATION ALLOWANCE: none.
