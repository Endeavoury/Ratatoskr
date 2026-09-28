# G7 DNS configured-limits re-review report

| Field | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g7-g8-limits-rereview-001-test-report` |
| Workflow / stage / target | `dns-implementation-20260913` / G7 `native_verification` / `protocol/dns` |
| Reviewer role | `protocol-test-engineer/g7-g8-limits-rereview-001` |
| Technical G7 disposition | `CHANGES_REQUESTED` |
| Candidate revision | `git:a8d98b75e9c450734808d5a672a2023e83589fb0` |
| Required author-artifact delivery | `git:a424049521c97969c32ef37f026c63803224b146` |
| Actual branch / remote readback | local `hermes/dns-implementation-20260913` at `6ada36167c0f32dee39553ded3ac4d642ce1a3ef`; `origin/hermes/dns-implementation-20260913` read back as the same `6ada36167c0f32dee39553ded3ac4d642ce1a3ef` |
| Independence | Fresh reviewer distinct from `c-protocol-implementer/g8-limits-remediation-001`, `protocol-test-engineer/g7-native-verification-001`, and `protocol-test-engineer/g7-remediation-rereview-002`; no production/test/canonical-truth authoring in this assignment. |

## Input integrity and scope

`git cat-file -t` identified both required revisions as commits. Candidate `a8d98b75e9c450734808d5a672a2023e83589fb0` has parent `9275f66dba3c19440da28ca86bd53777490b3e59`; author-artifact delivery `a424049521c97969c32ef37f026c63803224b146` has candidate as its parent. Both delivery and candidate are ancestors of the checked-out/remote-readback revision above.

The candidate changed exactly the five authorized production paths plus its author artifacts and the permitted destination-handoff Resolution:

- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_internal.h`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_transport_tcp.c`

The delivery commit contains the required remediation `README.md`, `implementation-report.md`, `completion-report.md`, and `handoffs/dns-g8-001-remediation-to-protocol-orchestrator.md`. `git diff --check` passed for both candidate and author-artifact delivery diffs.

Reviewed inputs: the remediation implementation/completion reports and orchestrator handoff; security handoff `dns-g8-001-configured-limits-enforcement.md`; prior G7 reports only as stale context; and the approved G1–G6 references recorded in workflow state. The reviewed acceptance subjects were finite defaults and configured UDP, TCP-frame, total-RR, name-expansion, compression-pointer, typed-field, outstanding-request, and connection limits, plus terminal request resource-limit/no-result behavior. This is not a G8 review or security disposition.

## Implementation and existing-evidence assessment

Read-only inspection confirms the candidate canonicalizes zero limits to finite private defaults; threads UDP/TCP limits to synchronous transports before receive/frame allocation; tests total RRs before result-record allocation; checks RDLENGTH before raw RDATA allocation/copy; and tracks active request reservations for outstanding-request/connection limits. Existing `tests/dns/dns_tests.c` and `tests/dns/dns_g7_native_verification_tests.c` contain no configured-limit coverage; the latter remains the prior 64-octet-label regression only.

The parser's configured name-expansion and compression-pointer paths are not correctly propagated as resource-limit errors. `read_name` returns `RATOS_ERROR_OUT_OF_MEMORY` on either configured name-expansion or compression-pointer exhaustion, but `read_records` discards that return value in its combined condition and returns `RATOS_ERROR_PROTOCOL`; the question-name combined condition similarly reaches cleanup with its initial `RATOS_ERROR_PROTOCOL`. `request_parse` consequently classifies the terminal event as `RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE`, not `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`.

## Actual execution

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr` against the checked-out line containing candidate `a8d98b75e9c450734808d5a672a2023e83589fb0` and its artifact delivery.

| Check | Actual result |
| --- | --- |
| `git diff --check a8d98...^ a8d98...` and `git diff --check a8d98... a424...` | PASS |
| Strict C11 compilation: `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only` over core and DNS source set | PASS |
| Existing native build/run with `tests/dns/dns_tests.c` | PASS — `Ratatoskr DNS native tests passed` |
| Existing G7 regression build/run with `tests/dns/dns_g7_native_verification_tests.c` | PASS — `G7 native DNS verification tests passed` |
| Temporary outside-repository probe: configured `max_name_expansion_bytes=1`, valid matching UDP response | FAILS required classification: `receive=6 state=4 class=2 event=5 take_result=(nil)` (`6` is `RATOS_ERROR_PROTOCOL`; class `2` is `RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE`) |
| `command -v cmake`; `command -v ctest` | Both absent; no CMake configure/build/CTest result is claimed. |

The temporary probe was written and compiled under `/tmp`, not retained as a repository test or artifact. It set the response ID from the read-only private request instance solely to make the local deterministic intake reach parser limit handling. It proves terminal/no-result cleanup but disproves the required resource-limit error classification for configured name expansion. The same discarded `read_name` result affects configured compression-pointer exhaustion.

## Finding and disposition

### DNS-G7-LIMITS-001 — configured name/pointer limit becomes malformed-response terminal

**Blocking:** yes. **Return owner:** `c-protocol-implementer`.

The candidate must preserve `RATOS_ERROR_OUT_OF_MEMORY` (the internal resource result) from `read_name` through question/record parsing so `request_parse` emits terminal `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`. It currently converts configured name-expansion and compression-pointer budget exhaustion to `RATOS_ERROR_PROTOCOL` / malformed-response. This does not meet the candidate handoff requirement for terminal resource-limit/no-result behavior for every accepted configured limit class.

**G7 technical disposition: `CHANGES_REQUESTED`.** Formal return: `handoffs/dns-g7-limits-001-resource-classification.md`. This report makes no G8 finding, approval, routing, preparation, or result claim.

## Model and execution provenance

Requested route/effort: `openai-codex/gpt-5.6-terra`, medium. Actual runtime route exposed for this reviewer: `openai-codex/gpt-5.6-terra`; actual reasoning effort and usage telemetry were not exposed. Attempts: one bounded independent evidence pass, no escalation. No quota/rate-limit error occurred.
