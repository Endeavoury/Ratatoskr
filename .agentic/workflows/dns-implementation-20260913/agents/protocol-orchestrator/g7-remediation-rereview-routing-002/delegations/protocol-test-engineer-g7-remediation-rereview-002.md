# Delegated task — DNS-G7-001 corrective re-review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-protocol-orchestrator-g7-remediation-rereview-routing-002-protocol-test-engineer-g7-remediation-rereview-002` |
| Workflow ID / stage | `dns-implementation-20260913` / G7 `native_verification` corrective re-review |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Assigned role / leaf ID | `protocol-test-engineer` / `g7-remediation-rereview-002` |
| Status | `IN_PROGRESS` |
| Candidate revision | `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee` |
| Source digest | `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88` |

ACTIVE ROLE: protocol-test-engineer

ROLE: protocol-test-engineer
GOAL: Independently re-review only the delivered DNS-G7-001 corrective candidate and the existing G7 harness. Record the designated G7 technical disposition without authoring production code, tests, canonical truth, or workflow state.
SCOPE: Scoped G7 review only. Do not route G8+, fuzz, bindings, documentation, or any other stage. This is a fresh reviewer identity, independent of c-protocol-implementer/g7-local-label-remediation-001 and protocol-test-engineer/g7-native-verification-001.

MODEL AND REASONING:
- Policy: `docs/agentic/MODEL_POLICY.md`, `protocol-test-engineer` row.
- Requested provider/model: `openai-codex` / `gpt-5.6-terra`.
- Requested effort: `medium`.
- Observed route before dispatch: parent session metadata `openai-codex` / `gpt-5.6-terra`; effort unknown. Record actual child route/usage if exposed, otherwise unknown.
- Attempt policy: one independent evidence review; any defect, stale input, failed command, or boundary conflict is a bounded G7 disposition/handoff, not a repair.
- Stop/checkpoint: actual quota/rate-limit error, missing candidate/revision, write-boundary conflict, or completed report. On quota/rate limit, stop immediately and make no state changes.

TARGET: `protocol/dns`; G7 native implementation review of DNS-G7-001.

REPOSITORY ROOT: `/home/hermes/hermes-workspace/projects/Ratatoskr`

WORKING DIRECTORIES:
- Command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/`.
- Workspace owner: fresh `protocol-test-engineer` leaf `g7-remediation-rereview-002`.
- Shared source directories: none writable; all production and test paths are review inputs only.
- Shared-file writer / ordering: only this leaf writes its exact artifact workspace. The parent alone writes workflow state.

WORKFLOW / STAGE / ASSIGNMENT: `dns-implementation-20260913` / `native_verification` / `g7-remediation-rereview-002`; shared state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` (read-only).

READ FIRST:
- `AGENTS.md`
- `.hermes/skills/protocol-test-engineer/SKILL.md`
- `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,DIRECTORIES.md,REVIEW_GATES.md,MODEL_POLICY.md}`
- `docs/contributing.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-local-label-remediation-001/{README.md,implementation-report.md,completion-report.md,handoffs/dns-g7-001-remediation-to-test-engineer.md}`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-native-verification-001/{test-report.md,handoffs/dns-g7-001-local-label-validation.md}`
- The approved G6 record and approved DNS analysis/model/API/vector references named by the existing G7 report.

REQUIRED INPUT ARTIFACTS:
- Delivered candidate `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee`, whose required source is `src/protocols/dns/dns_client.c` at `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88`.
- The c-protocol-implementer remediation report and READY_FOR_REVIEW handoff above.
- The original G7 CHANGES_REQUESTED report/handoff above, plus the existing G7 regression source `tests/dns/dns_g7_native_verification_tests.c` as read-only evidence.

FILES/DIRECTORIES ALLOWED TO CHANGE:
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/test-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/handoffs/` only if a technical discrepancy requires a formal handoff.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-remediation-rereview-002/completion-report.md`

FILES/DIRECTORIES THAT MUST REMAIN READ-ONLY:
- `src/`, `include/`, `tests/`, canonical vectors, analysis/model/API/design, original G7 artifacts/handoff, all workflow-root files including `workflow-state.yaml`, all unrelated workspaces, and every path outside the explicit allowed set.

EXPECTED OUTPUT ARTIFACTS:
- Leaf README with scope, candidate revision/digest, command cwd, and independence statement.
- `test-report.md` with independent G7 disposition, exact input revisions, inspection of the existing G7 harness, executed commands/results, and a concrete return route for any finding.
- Standard `completion-report.md`; any handoff only if required by a finding.

ACCEPTANCE CRITERIA:
1. Independently verify the candidate source matches the specified delivered commit/digest and that its correction is within the authorized DNS-G7-001 scope.
2. Inspect the existing G7 harness independently; do not modify it. Verify whether a 64-octet label returns `RATOS_ERROR_INVALID_ARGUMENT` with a null request, and whether validation precedes allocation/name duplication/ID/context attachment.
3. Execute the feasible manual C11 DNS test and G7 regression builds/runs, plus native `-fsyntax-only`, recording actual results. Do not claim CMake/CTest unless actually available and executed.
4. Record only the reviewer’s technical G7 disposition. Do not self-approve test artifacts authored by this reviewer and do not advance shared state.

HANDOFF TARGET: `protocol-orchestrator`, via this leaf’s `test-report.md`, `completion-report.md`, and any formal handoff in its own workspace.

STOP CONDITIONS: Any missing/stale revision, source digest mismatch, failed review criterion, test/harness concern, quota/rate error, or unauthorized-write requirement blocks technical approval and must be recorded without repair.

DELEGATION ALLOWANCE: No further delegation.

CONTEXT CONTRACT: You have fresh context. Read the role and all listed artifacts, verify prerequisites and boundary, and do not assume parent chat history. Do not update shared workflow state.