# G8 DNS configured-limits security re-review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-configured-limits-security-rereview-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured limits and synchronous UDP admission |
| Owner role | `security-reviewer/g8-configured-limits-security-rereview-001` |
| Status | `APPROVED` |
| Candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` (parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`) |
| G7 evidence | Reviewer delivery `git:510b5a131bcb3272caeb7eb1821444b35644cfcd`; remote reflection `git:7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`; scoped disposition `APPROVED` |
| Prior G8 evidence | `DNS-G8-001` and `DNS-G8-002` in reviewer delivery `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |
| Assumptions | Same-context mutation and destruction are externally serialized; distinct contexts are concurrently usable. |
| Open questions | None for this G8 disposition. |
| Limitations | Linux execution only; Windows oversize handling was inspected but not compiled or run. CMake/CTest, ThreadSanitizer, G9 fuzzing, and a dedicated dynamic name-expansion exhaustion probe were not available or not in scope. |

## Runtime identity, scope, and independence

ACTIVE ROLE: `security-reviewer`.

Before substantive review, the live parent process command line exposed:

`hermes chat -Q --oneshot --provider openai-codex --model gpt-5.6-sol --reasoning high --in /home/hermes/hermes-workspace/projects/Ratatoskr --query-file .../g8-configured-limits-security-rereview-routing-001/dispatch-query.md`

The actual route is therefore explicitly `openai-codex/gpt-5.6-sol/high`. Environment variables were empty and persistent profile defaults are not treated as the invocation route. Token, cache, cost, and reasoning-token telemetry were not exposed and remain unknown.

This is one fresh independent review of exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`. This reviewer did not author the candidate, its evidence, the G7 evidence, prior G8 records, approved analysis/model/API/vectors, or workflow state. The only writes are this assigned reviewer workspace. No delegation was made.

Reviewed immutable inputs include the delegation packet; repository governance and security model; current workflow state; approved G1-G6 analysis/model/API/vector records; accounting design; prior G8 findings; candidate implementation artifacts; exact candidate diff/source; and fresh G7 review/report/completion.

## Threat scope

Assets are process memory and availability, configured parsing and transport budgets, response/result atomicity, per-context outstanding/TCP capacity, caller-owned request/result lifetime, and isolation between contexts. Attackers include a malicious or on-path DNS peer able to send correlated malformed UDP datagrams or TCP frames and an untrusted caller selecting documented limit values.

Entrypoints assessed are synchronous `ratos_dns_query`, incremental UDP/TCP receive, DNS limit configuration, parser name/count/RDLENGTH handling, fallback admission, terminal cleanup, result transfer, request destruction, and context destruction. Trust boundaries are caller configuration and buffers, socket datagram/frame metadata, parser offsets/counts/compression pointers, allocation/copy operations, and context/request ownership.

## Candidate identity and checks

- The required wrapper confirmed repository `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `hermes/dns-implementation-20260913`, and candidate parent `509114307b862e8e339ded3eea5d483ea861d2d4`.
- Candidate `1a371fe` changes exactly `dns_client.c`, `dns_internal.h`, `dns_parser.c`, and `dns_transport_udp.c`; no public header, core accounting file, test, vector, build, design, state, or later-stage file is in the candidate delta.
- Wrapper `git diff --check 5091143... 1a371fe...` passed.
- Candidate, G7 delivery `510b5a1`, and remote reflection `7720bfe` passed the required ancestry checks.
- The reviewed worktree versions of all candidate files, `dns_transport_tcp.c`, `core_internal.h`, and `context.c` matched exact candidate `1a371fe`.
- Independent execution against candidate-equivalent source passed:
  - strict C11 `-Wall -Wextra -Werror -fsyntax-only` for complete native core/DNS sources;
  - `dns_g7_configured_limits_rereview_tests.c` normal run;
  - the same configured-limit executable with ASan/UBSan and leak detection;
  - existing `dns_tests.c` native suite;
  - existing `dns_g7_native_verification_tests.c` suite.
- Observed success messages were `G7 configured-limits re-review tests passed` twice, `Ratatoskr DNS native tests passed`, and `G7 native DNS verification tests passed`; no sanitizer diagnostic was emitted.
- `cmake`, `ctest`, and `x86_64-w64-mingw32-gcc` were absent. No Windows runtime/compile result is claimed.

## Finding reassessment

### DNS-G8-001 — configured limits and synchronous UDP admission

- Prior severity: Medium.
- Blocking at prior candidate: Yes.
- Current disposition: **RESOLVED for candidate `1a371fe`.**

1. **Record-owner resource propagation:** `dns_parser.c::read_records` now stores and returns the exact result of `read_name` before fixed-field decoding. Thus cumulative expansion or compression exhaustion and allocation failure remain `RATOS_ERROR_OUT_OF_MEMORY`; incremental UDP and completed TCP paths map this to terminal `RESOURCE_LIMIT`, destroy unpublished state, release both slot types exactly once, and expose no result. The scoped executable directly covers record-owner pointer exhaustion over UDP and TCP-after-truncation. Dedicated dynamic name-expansion exhaustion was not present, but exact control flow uses the same returned error without a separate collapsing branch.
2. **Compression traversal enforceability and ordering:** private maximum `RATOS_DNS_MAX_COMPRESSION_POINTER_TRAVERSALS` is 128; effective-limit validation rejects values above 128. For a valid pointer, the cumulative configured check occurs before the defensive local hard guard, so the 129th traversal at the effective/default boundary is classified as resource exhaustion rather than malformed. Pointer bounds/forward-pointer checks remain malformed and occur before budget accounting, which preserves structural rejection without consuming traversal work.
3. **Total RR ordering and arithmetic:** `an`, `ns`, and `ar` are promoted into `size_t`; their maximum aggregate is bounded without overflow on supported targets. The configured/effective `max_total_rrs` check now precedes the 4,096 implementation guard. Since effective configuration cannot exceed 4,096, a 4,097-RR header at the default is a resource limit before allocation or record iteration.
4. **Synchronous UDP admission:** POSIX now receives into exactly the configured capacity with `recvmsg` and rejects `MSG_TRUNC` before bytes reach TCP-fallback detection or parsing. Windows rejects `SOCKET_ERROR` with `WSAEMSGSIZE` on the same path. Both oversize branches free the buffer, close the socket, release address/runtime resources, set a resource-limit diagnostic, and return `RATOS_ERROR_OUT_OF_MEMORY`. The Linux loopback test sent a real 30-byte datagram against a 29-byte limit and observed resource failure with no result.
5. **Allocation/copy/traversal boundaries:** packet and frame maxima remain 65,535; typed RDATA length is checked against message remainder and configured field limit before allocation/copy; parser name offsets are bounded before dereference; partial results are destroyed on every error path. No new integer wrap, out-of-bounds, over-budget allocation, or truncated-prefix acceptance path was established.

### DNS-G8-002 — accounting, lifecycle, and detached handles

- Prior severity: High.
- Current disposition: **PRESERVED/RESOLVED for candidate `1a371fe`.**

The candidate does not modify core context ownership, request registry/counters, request slot flags, detachment, result transfer, cancellation, or destruction. Its parser resource errors flow through existing `request_fail`, which destroys unpublished frame/result state and idempotently releases held outstanding/TCP slots. The scoped UDP and TCP excess tests observed FAILED/RESOURCE_LIMIT, zero context counters, and no takeable result. Context destruction still cancels pending requests, preserves terminal/COMPLETE request-local state, clears accounting/link/context fields, and leaves caller-owned handles safe for terminal inspection, result take where applicable, and destruction. Distinct contexts retain disjoint mutable state; concurrent same-context mutation remains outside the contract.

## Residual risks and nonblocking limitations

- The Windows `WSAEMSGSIZE` branch is supported by direct source/API-semantic inspection only; no MinGW compiler or Windows runtime was available.
- Dynamic evidence covers record-owner pointer exhaustion, default pointer/RR boundaries, invalid over-hard configuration, and actual POSIX UDP truncation. Name-expansion exhaustion propagation is established by exact shared control flow, not a dedicated dynamic probe.
- No usable ThreadSanitizer result, CMake/CTest run, or G9 fuzz evidence is claimed. Same-context serialization remains required.
- Plain DNS authenticity, DNSSEC, encrypted transport, caching, retry policy, EDNS, and process-wide quotas remain outside the approved profile and this re-review.

None of these limitations creates an unresolved blocking G8 finding for the exact candidate.

## Disposition

**G8: APPROVED** for exact candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`.

`DNS-G8-001` is resolved and `DNS-G8-002` remains resolved/preserved. No new blocking security finding was established. No failure handoff is required. This reviewer does not update workflow state, route G9, merge, or perform any later-stage action; the result returns only to `protocol-orchestrator` for independent verification and administrative reflection.
