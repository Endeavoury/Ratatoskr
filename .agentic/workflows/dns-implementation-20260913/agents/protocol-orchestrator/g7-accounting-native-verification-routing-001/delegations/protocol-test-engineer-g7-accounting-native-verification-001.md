# Delegated task — G7 accounting native verification

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-accounting-native-verification-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` G8 accounting corrective candidate |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` after dispatch only |
| Revision | Routing delivery commit pending wrapper-mediated commit/push/readback |
| Source artifacts | Candidate `git:c38a7fa`; prerequisite approvals `git:4a37fc293c842b206190bad369e2a3e1ad00008c`, `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`, `git:aa2ebfaa8379d74a539ef95caf02d925f799d229` |
| Assumptions | Same-context mutation is externally serialized; separate contexts may be used concurrently. |
| Limitations | CMake/CTest/sanitizers are not available in the delivered author evidence; do not represent unavailable checks as passing. |

ACTIVE ROLE: `protocol-test-engineer`

ROLE: `protocol-test-engineer`

GOAL: Independently perform exactly one bounded G7 review of the delivered DNS context-owned request accounting candidate. Establish and report a G7 disposition with evidence, or record `BLOCKED` with concrete cause. Do not self-approve or route later work.

SCOPE: Native implementation review and verification evidence for candidate `c38a7fa` only. Review is independent of `c-protocol-implementer/g8-accounting-implementation-001` and every prior G7 reviewer/assignment. No G8, fuzzing, bindings, docs, compatibility, final review, implementation, design, or remediation work is authorized.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, `protocol-test-engineer` row.
- Requested: `openai-codex/gpt-5.6-terra` / `medium`.
- Observed route before dispatch: `openai-codex/gpt-5.6-terra`; effective reasoning effort is not exposed (`unknown`).
- One bounded attempt. If runtime/tooling/quota prevents independent work, write `BLOCKED` artifacts and stop; do not fabricate approval. No escalation is authorized in this packet.
- Usage/cost values are `unknown` unless exposed by runtime.

## Repository and workspace

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Leaf artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-accounting-native-verification-001/`.
- Leaf owns only its new workspace. Test source exception is allowed only after inspection establishes necessity, only for these exact files: `tests/dns/dns_g7_accounting_native_verification_tests.c`, `tests/integration/dns_g7_accounting_native_verification_test.py`, `tests/fixtures/dns/g7-accounting-native-verification-fixtures.json`, and scoped registration in `tests/CMakeLists.txt`.
- All production source/headers, approved designs/vectors, workflow-root state, existing tests, fuzzing, bindings, documentation, build configuration except the scoped test registration exception, and all other agent workspaces are read-only.
- Do not modify the candidate handoff. Do not update shared workflow state. Do not delegate further.

## Read first

- `AGENTS.md`
- `.hermes/skills/protocol-test-engineer/SKILL.md`
- `docs/agentic/{HANDOFFS,DIRECTORIES,ARTIFACTS,REVIEW_GATES,MODEL_POLICY,SECURITY_MODEL}.md`
- `docs/contributing.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- This packet and `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g7-accounting-native-verification-routing-001/preflight-verification.md`

## Required inputs

- Candidate production delivery: `git:c38a7fa`, with exactly `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c` changed relative to parent `62a2dda24194020904a75e1edce9b3d74fbd70a4`.
- Candidate artifacts: `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-accounting-implementation-001/{implementation-report.md,completion-report.md,handoffs/g8-accounting-implementation-to-protocol-orchestrator.md}`.
- Design/review prerequisites: `git:4a37fc293c842b206190bad369e2a3e1ad00008c`, `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`, and `git:aa2ebfaa8379d74a539ef95caf02d925f799d229` as recorded by the prior preflight.

## Required outputs

Write only in the assigned workspace:

- `README.md` with concrete active-role/scope/independence declaration;
- `test-report.md` with independent G7 disposition, exact candidate revision, commands/environment, evidence, and limitations;
- `reviews/g7-accounting-native-verification.md` as designated G7 gate record;
- `handoffs/` only if a discrepancy or blocker requires routing;
- `completion-report.md` using the standard required fields.

## Acceptance criteria

- Verify prerequisites and candidate revision independently before judging it.
- Report an honest G7 `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED` disposition; only the orchestrator advances shared state.
- Independently examine accounting/lifetime coverage relevant to the approved design, including per-context accounting, exact-once terminal handling, TCP admission accounting, context destruction detachment, and safe post-detach request operations; do not alter production truth to resolve findings.
- Record checks actually executed and distinguish unavailable tooling from passing evidence.
- Preserve the authorized write boundary and return control to `protocol-orchestrator`.

HANDOFF TARGET: `protocol-orchestrator`, via the leaf completion report and any necessary leaf-owned handoff.

STOP CONDITIONS: Missing/stale prerequisites, candidate boundary conflict, inability to obtain independent review evidence, runtime/tooling/quota limitation, or completion of the one G7 review. On quota/rate limit, stop immediately and record `BLOCKED` without shared-state changes.
