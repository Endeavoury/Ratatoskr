# DNS-G8-001 implementation report

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g8-limits-remediation-001-implementation` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Candidate revision | Wrapper-delivered `git:a8d98b75e9c450734808d5a672a2023e83589fb0`; origin readback matched `a8d98b75e9c450734808d5a672a2023e83589fb0` |
| Source artifacts | G8 finding/handoff at `git:90a02df18522b6c311e236dc03c82583971c7511`; approved API candidate `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; reviewed corrective candidate `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee` |
| Assumptions | Caller serializes mutable context/request operations, as approved API/model specifies. A request reserves one potential TCP fallback connection while pending because reuse/pipelining are excluded. |
| Open questions | Fresh G7 and then fresh G8 must independently verify the candidate. |
| Limitations | CMake/CTest are unavailable because `cmake` is not installed; no tests were created or modified. |

## Implementation trace

- `DNS-REQ-024`, `INV-BOUNDED-PARSING`: `ratos_dns_effective_limits` canonicalizes every zero public limit to finite private defaults: UDP/TCP frame 65,535; total RRs 4,096; name expansion 65,535; compression traversals 128; typed field 65,535; outstanding requests/connections 1. It rejects invalid protocol maxima, zero effective values, undersized frame limits, record maxima above the implemented ceiling, and connection limits greater than outstanding requests.
- `max_udp_message_bytes` is passed to synchronous UDP transport before receive-buffer allocation and enforced on incremental UDP input before parsing.
- `max_tcp_frame_bytes` is passed to synchronous TCP transport and checked at TCP-prefix time before frame allocation; the incremental path has the same pre-allocation terminal check.
- `max_total_rrs` is checked from header counts before record-array allocation/iteration.
- `max_name_expansion_bytes` and `max_compression_pointer_traversals` are accumulated and checked before name expansion/copy and pointer traversal.
- `max_typed_field_bytes` is checked before RDATA allocation/copy and typed decoding.
- Pending requests are tracked privately per context. `max_outstanding_requests` and `max_connections` both cap active request contexts; one pending request reserves one potential fallback connection in the no-reuse/no-pipelining profile. Terminal states no longer count; destruction unlinks the private tracker.
- Parser and intake resource excess returns the existing internal resource result, and request paths convert it to terminal `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`; `request_fail` destroys partial frame/result state and `take_result` cannot expose a result except from COMPLETE.
- The existing internal parser entry point is retained as a default-effective-limits wrapper for read-only existing tests/fuzz callers; request and synchronous paths use the explicit limited entry point.

## Validation evidence

- `git diff --check`: passed.
- Native compilation with `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -c` passed for each changed DNS C translation unit.
- Existing `tests/dns/dns_tests.c` compiled with the DNS/core implementation and executed successfully: `Ratatoskr DNS native tests passed`.
- Requested CMake command could not run: `/usr/bin/bash: line 5: cmake: command not found`.

No G7/G8 approval is asserted by this report.
