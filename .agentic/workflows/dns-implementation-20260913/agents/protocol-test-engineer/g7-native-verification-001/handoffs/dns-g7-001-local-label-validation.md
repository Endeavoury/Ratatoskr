# Handoff request — DNS-G7-001 local label validation

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g7-native-verification-001-dns-g7-001-handoff` |
| Workflow / stage | `dns-implementation-20260913` / `native_verification` |
| Source role / assignment | `protocol-test-engineer` / `g7-native-verification-001` |
| Destination role | `c-protocol-implementer` |
| Target | `protocol/dns` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Blocking | true |
| Source revisions | subject `eaa191ba25fde6b4224e0cacccee92adbdfd5701`; routing baseline `3b2803d0a1c92c1d73e36fa1e258305b5f06d4d8`; vectors `b7d05411cacfeb07be9f6bfbc36f705efdd002c5` |

## Reason and evidence

`DNS-REQ-002` and `DNS-VEC-003` require local rejection of a presentation DNS name containing one 64-octet label, without I/O or retained request context. At the submitted G6 implementation, `ratos_dns_request_start` only rejects empty names and names with total `strlen(name) > 255`. It accepts a 64-octet label and returns an owned request.

`tests/dns/dns_g7_native_verification_tests.c` reproduces the required local observable. Its manually linked execution failed at the assertion that `ratos_dns_request_start` return `RATOS_ERROR_INVALID_ARGUMENT`; process exit was 134. The test source and its registration are permitted G7 evidence, not canonical truth.

## Requested action

In a separately authorized implementation assignment, correct the native request-start validation without altering approved vectors, analysis, model, API design, workflow state, or this test's expectation. Preserve the existing synchronous API.

## Acceptance criteria

1. The G7 regression passes: a 64-octet label returns `RATOS_ERROR_INVALID_ARGUMENT` and leaves `out_request == NULL`.
2. Validation occurs before request/context creation and does not weaken the DNS-REQ-002 name boundaries.
3. Existing native DNS tests still pass under the feasible manual C11 build.
4. The implementer provides a new submitted implementation report and delivery revision; an independent G7 re-review verifies both the implementation and this authored harness. No self-approval.

## Resolution

Pending destination role action.
