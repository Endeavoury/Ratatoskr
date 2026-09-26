# G7 review: DNS configured-limits corrective candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-configured-limits-rereview-003-gate-review` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `protocol-test-engineer/g7-configured-limits-rereview-003` |
| Status | `APPROVED` |
| Revision | Candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; reviewer delivery pending wrapper commit/readback |
| Source artifacts | Candidate implementation report, completion, and handoff at `c-protocol-implementer/g8-configured-limits-remediation-002/`; originating G8 `DNS-G8-001` handoff; approved G1-G6 inputs in workflow state |
| Assumptions | POSIX `MSG_TRUNC` semantics exercised on Linux; Windows path inspected only. |
| Open questions | None for G7. G8 disposition is deliberately not asserted. |
| Limitations | CMake/CTest and Windows runtime validation unavailable. |

## Gate identity

- Gate ID and applicability: G7, applicable native implementation review.
- Workflow stage: `native_verification`.
- Candidate author: `c-protocol-implementer/g8-configured-limits-remediation-002`.
- Reviewer: fresh direct `protocol-test-engineer/g7-configured-limits-rereview-003`.
- Independence: reviewer did not author candidate code, candidate evidence, or prior relevant G7 review records.
- Actual runtime route: provider/model exposed by this direct CLI session as `openai-codex` / `gpt-5.6-terra`; reasoning-effort telemetry was not exposed, so actual effort is `unknown` (requested `medium`).

## Evidence and checks

| Pass criterion | Evidence | Observed result | Limitation |
| --- | --- | --- | --- |
| Candidate stays in authorized four private DNS files | `git diff-tree --name-only 1a371fe` | Exactly `dns_parser.c`, `dns_transport_udp.c`, `dns_client.c`, `dns_internal.h` | None |
| Record-owner resource errors survive both transports | `test-report.md`; scoped native test | UDP and TCP-after-TC pointer exhaustion are terminal resource limits with no result | None |
| Defaults and invalid configuration are enforceable | `test-report.md`; scoped native test | 128 cumulative traversal boundary accepted; next traversal and 4,097 RR header are resource limits; 129 configured traversal limit rejected | None |
| Oversized synchronous UDP is rejected before parse/fallback | `test-report.md`; loopback socket test | Real 30-byte datagram versus 29-byte configured limit returns `RATOS_ERROR_OUT_OF_MEMORY`, no result | Windows not run |
| Exact-once cleanup/no-result and detached-handle safety remain intact | `test-report.md`; candidate control-flow inspection | Slot counters reach zero, no result is takeable, and context destruction detaches request safely | No TSan run |
| Native checks execute and pass | `test-report.md` commands | scoped test, ASan/UBSan test, existing DNS/G7 tests, strict syntax, and diff check pass | CMake/CTest unavailable |

## Disposition

`APPROVED` for exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`.

The corrective implementation satisfies G7's configured-limit and synchronous UDP acceptance evidence. Handoff `dns-g7-configured-limits-rereview-to-protocol-orchestrator.md` asks `protocol-orchestrator` only to reflect this G7 disposition administratively and, if authorized by workflow policy, route the separate independent G8 review. This review does not approve, route, or perform G8, G9, or later work.
