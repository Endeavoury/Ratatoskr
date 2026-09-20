# DNS-G7-LIMITS-001 implementation report

| Field | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g7-limits-remediation-001-implementation-report` |
| Workflow / stage / target | `dns-implementation-20260913` / corrective native implementation / `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Candidate revision | `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` |
| Source artifacts | G7 report and DNS-G7-LIMITS-001 handoff at `git:15d3fc3de3eb733aac7f04d07ba7da02ffe809bd`; prior remediation candidate `git:a8d98b75e9c450734808d5a672a2023e83589fb0`. |
| Assumptions | None. |
| Open questions | None for this bounded implementation; independent G7 review is required. |
| Limitations | `cmake` and `ctest` are unavailable in this environment; no CMake/CTest run is claimed. The two limit probes were temporary `/tmp` programs and were not retained as repository tests. |

## Change trace

`read_name` already returns `RATOS_ERROR_OUT_OF_MEMORY` for both configured `max_name_expansion_bytes` and `max_compression_pointer_traversals` exhaustion. Candidate `7a0875e` preserves that return through every parser caller that previously combined `read_name` with malformed-input checks:

- question parsing in `ratos_dns_parse_response_limited` now assigns and checks the `read_name` result before the question fields;
- `read_records` already returned its local error, so it passes the record-owner resource result unchanged;
- DNS name-bearing RDATA parsing (single-name, MX, MINFO, SRV, SOA, and NAPTR) now returns the captured `read_name` result after cleanup instead of converting it to `RATOS_ERROR_PROTOCOL`.

`request_parse` already maps `RATOS_ERROR_OUT_OF_MEMORY` to `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`, calls `request_fail`, emits a terminal error event, and destroys/noes any result. No client/transport/header modification was necessary.

## Validation evidence

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr` against candidate `7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`.

| Check | Result |
| --- | --- |
| `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only` over the core and DNS C source set | PASS |
| Existing `tests/dns/dns_tests.c` compile/run against the core and DNS source set | PASS — `Ratatoskr DNS native tests passed` |
| Existing `tests/dns/dns_g7_native_verification_tests.c` compile/run against the core and DNS source set | PASS — `G7 native DNS verification tests passed` |
| Temporary `/tmp` configured-name-expansion incremental probe | PASS — `receive=3 state=4 class=3 event=5`; verified terminal event, failed state, `RATOS_ERROR_OUT_OF_MEMORY`, resource-limit class, and null/no takeable result. |
| Temporary `/tmp` configured-compression-pointer incremental probe | PASS — same output and assertions; the response uses a record-owner pointer then CNAME RDATA pointer to exhaust a limit of one traversal. |
| `git diff --check` before candidate commit | PASS |

The temporary probes deliberately used private request state only to set a matching transaction ID, remained outside the repository, and do not constitute changed tests. `cmake` and `ctest` are absent, so the documented configure/build/CTest workflow was not runnable.

## Boundary verification

Candidate commit `7a0875e` changes only `src/protocols/dns/dns_parser.c`. It contains no ABI, header, test, vector, workflow-state, review, or G8+ edit. The delivery artifact commit is limited to this assignment workspace plus the destination handoff's Resolution section.

## Model and execution provenance

Requested `openai-codex/gpt-5.6-terra` / medium. Actual exposed route: `openai-codex/gpt-5.6-terra`; reasoning effort and usage telemetry were not exposed. One bounded implementation/evidence pass; no quota/rate-limit error and no escalation.
