# G7 gate review — DNS accounting native verification

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-accounting-native-verification-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` context-owned request accounting candidate |
| Owner role | `protocol-test-engineer/g7-accounting-native-verification-001` |
| Status | `APPROVED` |
| Revision | Candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; leaf delivery revision pending wrapper commit/push/readback. |
| Source artifacts | Candidate parent `git:62a2dda24194020904a75e1edce9b3d74fbd70a4`; accounting design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; binding-lifetime review `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`; compatibility review `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`; implementation artifacts under `agents/c-protocol-implementer/g8-accounting-implementation-001/`. |
| Assumptions | Same-context mutation is externally serialized; distinct contexts may be used concurrently. |
| Open questions | None for G7 scope. |
| Limitations | CMake/CTest was unavailable (`cmake` absent). ThreadSanitizer compiled but could not execute in this environment (`FATAL: ThreadSanitizer: unexpected memory mapping`); this is not treated as passing race-detector evidence. |

## Gate identity

- Gate ID and applicability: `G7`, applicable native implementation review.
- Workflow stage: `native_verification`.
- Required input paths/revisions: packet `protocol-orchestrator/g7-accounting-native-verification-routing-001/delegations/protocol-test-engineer-g7-accounting-native-verification-001.md`; candidate and prerequisites above.
- Artifact author: `c-protocol-implementer/g8-accounting-implementation-001` at candidate `c38a7fa`.
- Reviewer: fresh `protocol-test-engineer/g7-accounting-native-verification-001` leaf, observed route `openai-codex/gpt-5.6-terra`, reasoning effort `unknown`.
- Independence: this reviewer is separate from the candidate author, `c-protocol-implementer/g8-accounting-implementation-001`, and did not reuse a prior G7 disposition.
- Review date: `2026-09-20T14:30:41+02:00`.

## Evidence and checks

| Pass criterion | Evidence | Observed result | Limitation |
| --- | --- | --- | --- |
| Candidate/prerequisites and delivery boundary are valid | Wrapper `diff --name-status 62a2dda... c38a7fa`, `show`, ancestry and prerequisite revision checks | Candidate has the three required implementation artifacts plus exactly `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c`; `c38a7fa` is an ancestor of reviewed routing HEAD; all three prerequisite revisions resolve. | Candidate artifact metadata has no immutable delivery revision, so commit `c38a7faf937571de5f0eb64885b8e5c61e5b9175` is used. |
| No whitespace/boundary defect | Wrapper `git diff --check 62a2dda... c38a7fa`; direct candidate diff review | Passed; no whitespace error. Private context registry/counters replace the global list; request flags centralize exact-once releases. | Static source review only for this row. |
| Per-context accounting, TCP admission, terminal release, cap reuse | Fresh ephemeral harness compiled from wrapper-extracted exact candidate in `/tmp/ratatoskr-g7-accounting-c38` | Passed: two requests consume two outstanding slots; first correlated TC response acquires the only TCP slot; second TC response fails `RESOURCE_LIMIT` and releases only its outstanding slot; counters/flags match expected values. | Harness was review evidence only and was not added to the repository. |
| Context destruction and detached-handle safety | Same fresh harness | Passed: pending TCP request is cancelled/detached; existing FAILED request is preserved/detached; post-detach cancel/receive reject without context dereference; COMPLETE request remains takeable after context destruction. | Same-context concurrent destruction remains explicitly unsupported by design. |
| Distinct-context isolation | Same harness, two pthread workers × 1,000 start/destroy cycles on separate contexts | Passed under normal execution; no assertion failure or crash. | ThreadSanitizer runtime cannot run in this environment. |
| Native compile and existing G7 test | `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only ...`; existing `tests/dns/dns_g7_native_verification_tests.c` linked against all candidate native sources | Both passed; existing test output: `G7 native DNS verification tests passed`. | Existing test covers a DNS name boundary, not accounting behavior. |
| Memory/undefined behavior for lifecycle evidence | Fresh harness built with `-fsanitize=address,undefined`, `ASAN_OPTIONS=detect_leaks=1` | Passed; output: `accounting G7 lifecycle review passed`. | ASan/UBSan only; not a CMake/CTest or ThreadSanitizer run. |

## Disposition

**APPROVED.** Candidate `c38a7fa` implements the approved private accounting design at its authorized four production paths: context-local registry/counters, explicit outstanding/TCP ownership flags, TCP admission after correlated UDP truncation, centralized exact-once release across terminal paths, and safe context teardown with caller-owned detached handles. Independently executed lifecycle evidence covered the required accounting and teardown behaviors, including post-detach operations and COMPLETE take-result.

This approves G7 only for `c38a7fa`. It does not approve G8/security, fuzzing, bindings, documentation, compatibility, final review, workflow-state advancement, or any later candidate. The orchestrator remains responsible for state handling and any subsequent routing.
