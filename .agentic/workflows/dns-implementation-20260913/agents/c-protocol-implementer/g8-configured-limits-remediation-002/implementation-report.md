# DNS-G8-001 configured-limits corrective implementation report

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-configured-limits-remediation-002-implementation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `c-protocol-implementer/g8-configured-limits-remediation-002` |
| Status | `READY_FOR_REVIEW` |
| Candidate revision | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` (parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`) |
| Source artifacts | Accounting candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; G7 delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`; G8 delivery `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0`; originating handoff `agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md` |
| Assumptions | Approved same-context serialization remains unchanged; POSIX supplies `recvmsg`/`MSG_TRUNC`, and Winsock reports an oversized connectionless receive as `WSAEMSGSIZE`. |
| Open questions | None in implementation scope; fresh independent G7 and then G8 review are required. |
| Limitations | CMake/CTest are unavailable. No repository tests were authored or modified. No dynamic socket-truncation reproduction, Windows cross-compile, fresh parser-boundary probe, or ThreadSanitizer run is claimed. |

## Approved input baseline

The packet baseline `git:9afc2e8825619dccc73e8eed00a431f838dd8a47` was verified as an ancestor of start HEAD `git:509114307b862e8e339ded3eea5d483ea861d2d4`. Start root, origin, branch, HEAD, status, and ancestry were read through the required `git-agent.sh --role c-protocol-implementer` wrapper. The checked-out production files had no delta from reviewed accounting candidate `c38a7fa`. Unrelated untracked content was preserved.

Actual runtime route was verified from the live process command line: `hermes chat -Q --oneshot --provider openai-codex --model gpt-5.6-sol --reasoning high .../g8-configured-limits-remediation-routing-003/dispatch-query.md`. Provider/model/reasoning were therefore `openai-codex` / `gpt-5.6-sol` / `high`. The one-shot process did not expose a Hermes session identifier or token/cost telemetry.

## Complete call-graph inspection

Before editing, inspection covered all current `read_name` callers in `dns_parser.c`: question parsing; record-owner parsing in `read_records`; and NS/MD/MF/CNAME/MB/MG/MR/PTR, MX, MINFO, SRV, SOA, and NAPTR RDATA parsing in `parse_record_text`. RDATA callers already return the exact `read_name` error; question parsing already carries it through cleanup. Only record-owner parsing collapsed it into `RATOS_ERROR_PROTOCOL`.

Inspection also covered both parser entry points, their synchronous and incremental callers, effective-limit canonicalization/configuration, UDP receive/fallback selection, TCP receive framing, request terminal classification, exact-once slot release, context detachment, result cleanup, and all repository callers in native tests and fuzz entry points.

## Traceability

| Finding / requirement | Native realization | Result |
| --- | --- | --- |
| `DNS-G8-001.1`, `DNS-REQ-024`, `INV-BOUNDED-PARSING`: preserve every `read_name` resource result | `dns_parser.c::read_records` now stores and returns the record-owner `read_name` result before fixed-field parsing. | Name expansion, traversal exhaustion, and allocation failure remain `RATOS_ERROR_OUT_OF_MEMORY`; request paths continue mapping that to terminal `RESOURCE_LIMIT`/no-result. |
| `DNS-G8-001.2`: accepted traversal settings must be enforceable | `dns_internal.h` names the 128-traversal implementation maximum; the default uses it. `dns_client.c::ratos_dns_effective_limits` rejects explicit/effective values above it. `read_name` performs the configured cumulative check before its overlapping local hard guard. | Values above 128 return `RATOS_ERROR_INVALID_ARGUMENT`; the effective/default 128 boundary reaches resource disposition before the defensive malformed guard. |
| `DNS-G8-001.3`: configured/effective total-RR check precedes hard malformed guard | `dns_parser.c::ratos_dns_parse_response_limited` checks `limits->max_total_rrs` before `RATOS_DNS_MAX_RECORDS`. | A 4,097-record header at the effective default is a resource excess (`RATOS_ERROR_OUT_OF_MEMORY`), not malformed. |
| `DNS-G8-001.4`: synchronous UDP cannot accept an oversized truncated prefix | POSIX `dns_transport_udp.c` uses capacity-bounded `recvmsg` and rejects `MSG_TRUNC`; Windows rejects `SOCKET_ERROR`/`WSAEMSGSIZE`. Both paths free/close/finish before returning `RATOS_ERROR_OUT_OF_MEMORY`. | An oversized datagram is not returned to fallback detection or the parser; no truncated correlated prefix can be accepted. |
| Preserve `DNS-G8-002` accounting/lifetime behavior and public ABI | Candidate touches no public header or core file and does not alter request accounting, release, detach, cleanup, or result-publication control flow. | Context-owned registry/counters, exact-once release flags, terminal no-result cleanup, context destruction, and detached-handle behavior remain intact. |

## Change and ownership summary

Candidate `1a371fe` changes exactly the four authorized private DNS files. It adds no public symbol, public layout, dependency, test, build registration, or workflow-state change. POSIX receives at most the configured capacity and uses socket metadata to identify truncation; Windows uses the platform's connectionless oversize error. All oversize exits dispose of the temporary buffer and socket runtime before returning the existing internal resource error.

## Evidence

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`.

| Check / command | Tool/platform | Revision | Executed? | Result |
| --- | --- | --- | --- | --- |
| Required-wrapper root/origin/branch/HEAD/status plus `merge-base --is-ancestor 9afc2e8... HEAD` | wrapper / Linux | start HEAD `5091143` | Yes | Root/origin/branch matched the packet; ancestor check exited 0; unrelated untracked paths preserved. |
| Repository call-graph search and full reads of all four allowed files | repository tools | pre-candidate `5091143` | Yes | All `read_name`, parser-limit, request classification, and synchronous UDP call paths inspected before editing. |
| `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only` on the complete native core/DNS source set | GCC 14.2.0 / Linux | candidate-equivalent worktree | Yes | PASS, no output. |
| Manual compile/run of `tests/dns/dns_tests.c` with the complete native core/DNS source set | GCC 14.2.0 / Linux | candidate-equivalent worktree | Yes | PASS: `Ratatoskr DNS native tests passed`. |
| Manual compile/run of `tests/dns/dns_g7_native_verification_tests.c` with the complete native core/DNS source set | GCC 14.2.0 / Linux | candidate-equivalent worktree | Yes | PASS: `G7 native DNS verification tests passed`. |
| Both existing native executables rebuilt with `-fsanitize=address,undefined -fno-omit-frame-pointer`; `ASAN_OPTIONS=detect_leaks=1` | GCC 14.2.0 ASan/UBSan / Linux | candidate-equivalent worktree | Yes | PASS with the same success messages and no sanitizer diagnostics. |
| Required-wrapper `git diff --check` before candidate commit | wrapper | candidate worktree | Yes | PASS, no output. |
| `command -v cmake; command -v ctest` | shell | environment | Yes | Neither tool was found; CMake configure/build and CTest were not executed. |
| `command -v x86_64-w64-mingw32-gcc` | shell | environment | Yes | Not found; no Windows cross-compile is claimed. |

The checks are implementation evidence only. They do not constitute G7 or G8 approval, and the existing tests do not provide the fresh parser-boundary/socket evidence required from independent review.

## Handoff

`handoffs/dns-g8-001-configured-limits-remediation-to-protocol-orchestrator.md` requests fresh independent G7 review of exact candidate `1a371fe`, followed only after approval by fresh independent G8 verification. No other routing or gate action is performed here.
