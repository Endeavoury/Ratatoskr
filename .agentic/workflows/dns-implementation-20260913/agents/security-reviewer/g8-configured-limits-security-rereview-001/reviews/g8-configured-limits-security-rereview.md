# Gate review: G8 DNS configured-limits corrective candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g8-configured-limits-security-rereview-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured limits and synchronous UDP admission |
| Owner role | `security-reviewer/g8-configured-limits-security-rereview-001` |
| Status | `APPROVED` |
| Revision | Candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`; G7 delivery `git:510b5a131bcb3272caeb7eb1821444b35644cfcd` |
| Source artifacts | Technical findings and exact execution evidence in `../security-review.md`; G7 remote reflection `git:7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`; prior G8 delivery `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |
| Assumptions | Same-context mutation/destruction is externally serialized; distinct contexts are concurrent. |
| Open questions | None for G8. |
| Limitations | Linux dynamic execution only; Windows source inspection only; no CMake/CTest, TSan, or G9 fuzzing; no dedicated dynamic name-expansion exhaustion probe. |

## Gate identity

- Gate: `G8`, applicable security review of hostile configured limits, resource disposition, synchronous UDP admission, accounting, and lifetime.
- Workflow stage: `security`.
- Candidate author: `c-protocol-implementer/g8-configured-limits-remediation-002`.
- G7 reviewer: fresh `protocol-test-engineer/g7-configured-limits-rereview-003`, disposition `APPROVED` for the exact candidate.
- G8 reviewer: fresh direct `security-reviewer/g8-configured-limits-security-rereview-001` leaf.
- Independence: this reviewer authored none of the candidate, tests, G7 evidence, prior G8 records, approved truth, or workflow state and made no delegation.
- Review date: `2026-09-26T13:56:55+02:00`.
- Actual runtime: live parent command line explicitly exposed `--provider openai-codex --model gpt-5.6-sol --reasoning high`; actual route/effort is `openai-codex/gpt-5.6-sol/high`. Usage/cost telemetry is unknown.

## Evidence and checks

| Pass criterion | Evidence | Observed result | Limitation |
| --- | --- | --- | --- |
| Exact candidate and prerequisite identity | Wrapper parent/path checks; ancestry `1a371fe → 510b5a1 → 7720bfe`; exact G7 record | PASS | Remote branch advances beyond the prerequisite commits, as expected |
| Authorized candidate boundary and public ABI | Candidate diff and `git diff --check` | PASS: exactly four private DNS files; no public header/API/layout or core accounting change | None |
| Record-owner configured-limit errors survive UDP/TCP | Exact `read_records` control flow; scoped normal and ASan/UBSan runs | PASS: exact `read_name` error is preserved; pointer excess is terminal RESOURCE_LIMIT/no-result over UDP and TCP | Name-expansion branch verified statically, not by a dedicated probe |
| Configured/default pointer limit is enforceable | `ratos_dns_effective_limits`, `read_name`; scoped boundary test | PASS: 129 is rejected as configuration; 128 boundary is enforceable and excess is resource-first | None |
| Total-RR count is resource-first and pre-allocation | Parser count arithmetic/order; scoped 4,097-RR header test | PASS: effective/default excess returns resource error before allocation/iteration | None |
| Oversized synchronous UDP is rejected before parse/fallback | POSIX `recvmsg`/`MSG_TRUNC`; Windows `WSAEMSGSIZE`; Linux loopback test | PASS on Linux: actual 30-byte datagram versus 29-byte limit returns resource error/no result | Windows not compiled or run |
| Terminal cleanup and DNS-G8-002 accounting remain safe | Candidate delta boundary; request failure/release/detach control flow; scoped tests | PASS: zero counters, no takeable result, exact-once slot release, safe detached handle | Same-context concurrent mutation remains unsupported |
| Malformed lengths, offsets, copies, and allocations remain bounded | Exact parser/TCP/UDP source; strict compile and sanitizer run | PASS for reviewed paths; no new blocking issue established | G9 fuzzing not in scope |
| No unresolved blocking G8 finding remains | `../security-review.md` | PASS: DNS-G8-001 resolved; DNS-G8-002 preserved | Recorded residual limitations remain nonblocking |

## Findings and failure route

- `DNS-G8-001`: **RESOLVED** for candidate `1a371fe`.
- `DNS-G8-002`: **RESOLVED/PRESERVED** for candidate `1a371fe`.
- New blocking findings: none.
- Failure route: none; no implementation/design/API return handoff is required.
- Return target: `protocol-orchestrator` only, for verification and state reflection. This leaf does not route G9 or later work.

## Disposition

**G8: APPROVED** for exact candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`.

The candidate closes configured-limit error propagation and ordering, rejects unenforceable traversal configuration, prevents oversized synchronous UDP datagrams from being accepted as truncated prefixes, and preserves the already-correct context-owned accounting/lifecycle contract. No unresolved blocking G8 finding remains within the approved profile and recorded limitations.
