# DNS G7 configured-limits re-review test report

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-configured-limits-rereview-003-test-report` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `protocol-test-engineer/g7-configured-limits-rereview-003` |
| Status | `APPROVED` |
| Candidate revision | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` (parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`) |
| Source artifacts | G8 remediation implementation/completion/handoff; originating `DNS-G8-001` handoff; approved analysis `git:5615cae`, model `git:f267454`, API `git:e3c63fd`, and G5 vector candidate `git:b7d0541` |
| Assumptions | Linux POSIX `recvmsg` reports truncated datagrams with `MSG_TRUNC`; supported by this executed environment. |
| Open questions | Fresh independent G8 review remains required and is outside this assignment. |
| Limitations | `cmake` and `ctest` are unavailable; CMake/CTest and Windows `WSAEMSGSIZE` behavior were not executed. |

## Reviewer independence and scope

This is a fresh direct `protocol-test-engineer` assignment, distinct from `c-protocol-implementer/g8-configured-limits-remediation-002` and prior relevant G7 reviewers. I did not author candidate production code or prior relevant review artifacts. The candidate diff is exactly `dns_parser.c`, `dns_transport_udp.c`, `dns_client.c`, and `dns_internal.h`; working-tree inspection found no production delta beyond that candidate.

## Requirement evidence

| Requirement | Independent evidence | Result |
| --- | --- | --- |
| Record-owner expansion/pointer exhaustion over UDP and TCP | New scoped native test constructs a record-owner pointer chain exceeding the effective default, drives both `ratos_dns_request_receive_udp` and TCP-after-TC framing, and asserts `RATOS_ERROR_OUT_OF_MEMORY`, `RESOURCE_LIMIT`, no result, and released slots. | Pass |
| Effective-default pointer and RR boundaries | Same test accepts exactly 128 cumulative pointer traversals (including the first record owner), rejects the next traversal as resource limit, and parses a 4,097-RR header as `RATOS_ERROR_OUT_OF_MEMORY` before malformed count handling. | Pass |
| Over-hard traversal configuration | Same test sets 129 traversals and verifies `ratos_dns_context_set_dns_limits` returns `RATOS_ERROR_INVALID_ARGUMENT`. | Pass |
| Actual oversized synchronous UDP admission | Same test forks a loopback UDP peer, receives the real client query, returns a 30-byte datagram against a configured 29-byte limit, and verifies synchronous `ratos_dns_query` returns `RATOS_ERROR_OUT_OF_MEMORY` with no result. This exercised POSIX `recvmsg`/`MSG_TRUNC`, not static reasoning. | Pass |
| Terminal cleanup/accounting/no result | Resource-limit tests assert FAILED/RESOURCE_LIMIT, zero outstanding and TCP connection counters, failed `take_result` with `NULL` output, and context teardown detaches the handle safely. | Pass |
| `c38a7fa` lifecycle safety | Candidate does not alter context-owned request registry/counters, request release, detachment, cleanup, or result ownership paths. Executed terminal and context-destruction assertions retain their behavior. | Pass |

## Commands and output

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr` against a worktree containing candidate `1a371fe`.

| Command | Result |
| --- | --- |
| `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc tests/dns/dns_g7_configured_limits_rereview_tests.c src/core/*.c src/protocols/dns/*.c -o /tmp/ratatoskr-g7-configured-limits && /tmp/ratatoskr-g7-configured-limits` | Pass: `G7 configured-limits re-review tests passed` |
| Same command with `-fsanitize=address,undefined -fno-omit-frame-pointer` and `ASAN_OPTIONS=detect_leaks=1` | Pass: same success output; no sanitizer diagnostics |
| Manual strict build/run of `tests/dns/dns_tests.c` | Pass: `Ratatoskr DNS native tests passed` |
| Manual strict build/run of `tests/dns/dns_g7_native_verification_tests.c` | Pass: `G7 native DNS verification tests passed` |
| `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only src/core/*.c src/protocols/dns/*.c` | Pass, no output |
| `git diff --check` | Pass, no output |
| `command -v cmake; command -v ctest` | Neither executable found; CMake/CTest not run |

## Conclusion

The scoped test was necessary because existing tests did not exercise actual synchronous socket truncation or all required configured-limit boundaries. Candidate `1a371fe` satisfies the G7 acceptance evidence on this Linux environment. G7 disposition: `APPROVED`. Fresh G8 review remains a separate required gate.
