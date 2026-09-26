# Handoff request — DNS-G7-001 remediation re-review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g7-local-label-remediation-001-dns-g7-001-remediation-to-test-engineer` |
| Workflow ID / stage | `dns-implementation-20260913` / corrective return to G7 `native_verification` |
| Target | `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Revision | Local working tree; `src/protocols/dns/dns_client.c` `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88` |
| Source artifacts | Original G7 handoff, G7 test report, DNS-REQ-002, DNS-VEC-003 |
| Assumptions | G6 approval remains current for this strictly local correction. |
| Open questions | None. |
| Limitations | CMake/CTest unavailable on PATH; no delivery commit/push because no executable absolute `git-agent` wrapper was found. |

## Routing
- ID / workflow / stage: `DNS-G7-001` / `dns-implementation-20260913` / `native_verification`.
- Source role and assignment: `c-protocol-implementer` / `g7-local-label-remediation-001`.
- Destination role: `protocol-test-engineer` in a fresh independent G7 re-review assignment.
- Target protocol/binding/component: `protocol/dns`.
- Reason: remediate the prior independent finding that request start accepted a 64-octet local label.
- Blocking: true until independent re-review.
- Status: `READY_FOR_REVIEW`.

## Source artifacts
- `src/protocols/dns/dns_client.c`, local content `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-native-verification-001/handoffs/dns-g7-001-local-label-validation.md`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-native-verification-001/test-report.md`.
- Requirements/evidence: `DNS-G7-001`, `DNS-REQ-002`, `DNS-VEC-003`.
- Manual C11 executions passed: existing native DNS tests and `tests/dns/dns_g7_native_verification_tests.c`; native source set also passed `-fsyntax-only`.

## Specific problem or question
The prior G7 regression showed `ratos_dns_request_start` created a request for a presentation DNS name containing one 64-octet label. The production correction is complete, but this implementation author cannot independently review or approve G7.

## Requested action
Independently inspect the local correction and the existing G7 harness, then perform the fresh G7 re-review without modifying production code, canonical truth, or workflow state.

## Acceptance criteria
1. The 64-octet label produces `RATOS_ERROR_INVALID_ARGUMENT` and `out_request == NULL`.
2. Validation occurs before `calloc`, name duplication, ID generation, or request context attachment.
3. The existing manual C11 DNS native executable and G7 regression executable pass, and the native source set passes `-fsyntax-only` where feasible.
4. The reviewer records an independent G7 disposition; this handoff is not self-approved by its author.

## Resolution (destination role)
Pending independent G7 re-review.

## Closure (orchestrator after verification)
Pending orchestrator verification of the independent review and delivery state.