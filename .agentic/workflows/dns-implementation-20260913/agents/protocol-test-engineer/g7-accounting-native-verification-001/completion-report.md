# Specialist completion — G7 accounting native verification

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-accounting-native-verification-001-completion` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` context-owned request accounting candidate |
| Owner role | `protocol-test-engineer/g7-accounting-native-verification-001` |
| Status | `APPROVED` |
| Revision | Leaf delivery revision pending wrapper commit/push/readback. |
| Source artifacts | Candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; accounting design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; prerequisite reviews `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`, `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`. |
| Assumptions | Same-context mutation is externally serialized; separate contexts may be used concurrently. |
| Open questions | None for G7. |
| Limitations | CMake/CTest unavailable; ThreadSanitizer execution unavailable as recorded in the gate review. |

ROLE: `protocol-test-engineer/g7-accounting-native-verification-001`

STATUS: `APPROVED`

SUMMARY:
Fresh independent G7 review approves candidate `c38a7fa` for the context-owned request-accounting scope. Source review and executed exact-candidate lifecycle evidence confirm per-context accounting, exact-once terminal release, TCP admission accounting, context-destruction detachment, and safe post-detach operations.

ARTIFACTS CREATED:
- `README.md`
- `test-report.md`
- `reviews/g7-accounting-native-verification.md`
- `completion-report.md`

ARTIFACTS MODIFIED:
- None outside this owned leaf workspace.

DECISIONS MADE:
- G7 disposition: `APPROVED` for `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` only.

OPEN QUESTIONS:
- None.

BLOCKERS:
- None for the G7 disposition. CMake/CTest and ThreadSanitizer limitations are recorded and are not represented as passing evidence.

HANDOFF REQUIRED:
- `protocol-orchestrator`: consume this leaf G7 record only; do not advance shared workflow state from this leaf. Any later gate routing is outside this assignment.

RECOMMENDED NEXT ROLE:
- `protocol-orchestrator`.

WORKING DIRECTORIES:
- Repository command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Owned artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-accounting-native-verification-001/`.
- Exact candidate extraction/build: `/tmp/ratatoskr-g7-accounting-c38`.
- No repository test or production source was modified. Existing dirty `workflow-state.yaml` and unrelated untracked workspaces were preserved.

VALIDATION EVIDENCE:
- Wrapper candidate boundary/prerequisite/ancestry checks and `diff --check` passed.
- Strict C syntax compilation, existing native G7 executable, fresh lifecycle accounting executable, and ASan/UBSan lifecycle executable passed.
- ThreadSanitizer execution failed before test startup because of an environment memory-mapping failure; CMake/CTest unavailable because `cmake` is absent.

MODEL / REASONING USED:
- Requested `openai-codex/gpt-5.6-terra` / `medium`; observed route `openai-codex/gpt-5.6-terra`; effective effort `unknown`.

USAGE AND ESCALATIONS:
- One bounded attempt; no retry or escalation. Token, reasoning-token, and cost usage are not exposed and are `unknown`.
