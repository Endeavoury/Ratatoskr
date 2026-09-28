# G8 DNS accounting security re-review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-accounting-security-rereview-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` accounting corrective candidate |
| Owner role | `security-reviewer/g8-accounting-security-rereview-001` |
| Status | `CHANGES_REQUESTED` |
| Candidate | `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` (parent `62a2dda24194020904a75e1edce9b3d74fbd70a4`) |
| G7 evidence | `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`, scoped `APPROVED` for candidate `c38a7fa` |
| Prior G8 evidence | `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`, findings `DNS-G8-001` and `DNS-G8-002` |
| Assumptions | Same-context mutation and destruction are externally serialized; distinct contexts remain concurrently usable. |
| Open questions | None; the remaining blocker has an implementation return route. |
| Limitations | No new probe or test source was authorized. This review ran static exact-revision inspection and strict syntax compilation; it relies on G7 for dynamic accounting/lifecycle evidence. CMake/CTest and usable ThreadSanitizer evidence were unavailable to G7. G9 fuzzing is not part of this assignment. |

## Scope, runtime identity, and independence

This is one fresh independent G8 re-review by `security-reviewer/g8-accounting-security-rereview-001`, Hermes session `20260920_145846_deae3c`. The live parent process command line contains `hermes chat --provider openai-codex --model gpt-5.6-sol --reasoning high`; those invocation overrides are the actual route for this session even though persistent profile defaults report Terra/unset. Actual runtime is therefore provider `openai-codex`, model `gpt-5.6-sol`, reasoning `high`. Token, reasoning-token, cache, cost, and spend telemetry are not exposed and are `unknown`.

I did not author candidate `c38a7fa`, its accounting design or implementation artifacts, any G7 evidence, or prior security-reviewer assignment `g8-limits-rereview-001`. I wrote only this assigned review workspace. The candidate and G7 delivery are distinct-role commits by `c-protocol-implementer` and `protocol-test-engineer`, respectively.

Reviewed immutable inputs:

- accounting implementation candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`, exact parent `git:62a2dda24194020904a75e1edce9b3d74fbd70a4`;
- implementation report, completion, and handoff in `agents/c-protocol-implementer/g8-accounting-implementation-001/` at `c38a7fa`;
- fresh G7 review/report/completion at delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`;
- accounting design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`;
- binding-lifetime review `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`;
- compatibility support review `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`;
- prior G8 finding delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`.

Git checks confirmed the candidate parent, candidate-to-G7 ancestry, and exact candidate delta. The production delta is exactly `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c`; the other three candidate files are its own implementation artifacts. `git diff --check 62a2dda... c38a7fa` passed. No source, public-header, or test delta exists from `c38a7fa` to the reviewed delivery HEAD. At review start, local HEAD and exact origin readback matched `git:4623cf479e93ab83ff297df38d9e11840604ed1e`.

## Threat scope

Assets are process memory and availability, configured parser/transport budgets, per-context outstanding/TCP capacity, request correlation state, terminal error/result atomicity, caller-owned request/result lifetime, and isolation between contexts. Attackers include a malicious or on-path DNS peer able to send correlated malformed UDP datagrams or TCP frames, and an untrusted caller exercising documented limits and distinct-context concurrency.

Entrypoints are `ratos_dns_query`, `ratos_dns_request_start`, `ratos_dns_request_receive_udp`, `ratos_dns_request_receive_tcp`, transport-failure/cancel/take-result/destruction operations, DNS limit configuration, and `ratos_context_destroy`. Trust boundaries are caller-supplied configuration/options and buffers; UDP datagram and TCP frame metadata; parser cursor, compression, count, and RDLENGTH processing; allocation/result publication; context-owned request accounting; and context/request teardown.

The review reassessed malformed lengths, truncation and offset arithmetic; record/count and typed-RDATA allocation; name expansion and compression work; UDP/TCP admission and amplification; terminal no-result behavior; exact-once slot release; cancellation/destruction; detached-handle safety; and distinct-context concurrency.

## Checks actually performed

1. Verified repository root, origin, branch, candidate parent, candidate/G7 ancestry, exact remote branch readback, candidate path boundary, G7 reviewer-only delivery boundary, and both relevant `git diff --check` ranges.
2. Read the exact candidate diff and full candidate versions of `dns_client.c`, `dns_parser.c`, both transports, private context/request headers, builder, and result cleanup code.
3. Read the exact prior G8 findings, accounting design, binding-lifetime review, compatibility review, implementation artifacts, and G7 gate/report/completion.
4. Compared candidate source to prior finding locations and confirmed `dns_parser.c` and `dns_transport_udp.c` are unchanged from the prior G8 subject through the accounting candidate.
5. Ran strict syntax compilation against candidate-equivalent checked-out source after confirming no candidate-to-HEAD source/header/test delta:
   `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only src/core/context.c src/protocols/dns/dns_client.c src/protocols/dns/dns_parser.c src/protocols/dns/dns_transport_udp.c src/protocols/dns/dns_transport_tcp.c` — passed.
6. Reviewed G7's executed exact-candidate lifecycle harness, ASan/UBSan run, strict compilation, existing native test, and two-thread distinct-context stress. G7 recorded all as passing except ThreadSanitizer, whose runtime failed before test execution; no TSan pass is claimed here.

## Prior-finding reassessment

### DNS-G8-001 — configured limits/resource disposition remains incomplete

- **Severity:** Medium.
- **Blocking:** Yes.
- **Owner:** `c-protocol-implementer`, routed through `protocol-orchestrator`.
- **Requirements/design:** `DNS-REQ-024`; `INV-BOUNDED-PARSING`; `INV-TCP-CORRELATED-DISPOSITION-PARTITION`; API design requirement that accepted nonzero limits be coherent and excess become terminal `RESOURCE_LIMIT` with no partial result.
- **Disposition:** **UNRESOLVED.** Candidate `c38a7fa` does not modify `dns_parser.c` or `dns_transport_udp.c`; all four prior reachable defects remain at the exact candidate:
  1. `src/protocols/dns/dns_parser.c:374-376` discards the error returned by record-owner `read_name` and returns `RATOS_ERROR_PROTOCOL`. Cumulative configured name-expansion or compression-traversal exhaustion while reading a record owner is therefore exposed as malformed instead of resource-limit on both UDP and completed TCP parsing paths.
  2. `dns_parser.c:97-99` applies the fixed 128-hop malformed guard before the configured traversal check, while `src/protocols/dns/dns_client.c:75-80` accepts a nonzero traversal limit above 128. The default/effective boundary can be classified malformed first, and accepted values above 128 are unenforceable.
  3. `dns_parser.c:418-420` applies the 4,096-record hard malformed guard before the configured/effective resource check. At the effective default of 4,096, a wire-reachable 4,097-record response is classified malformed rather than resource-limit.
  4. `src/protocols/dns/dns_transport_udp.c:91-100` allocates exactly `max_udp_message_bytes` and uses `recv` without truncation/full-datagram detection. On POSIX and Windows, a larger datagram may be truncated to an otherwise complete correlated DNS prefix and accepted, defeating the configured synchronous UDP admission boundary. The incremental UDP API correctly receives an explicit full length; the synchronous path does not.
- **Impact/rationale:** These paths preserve memory bounds in the reviewed cases, but they defeat mandatory configured-budget disposition and, for synchronous UDP, permit acceptance of an actually over-limit attacker-controlled datagram. The result/no-result partition is security-relevant and required by approved analysis/model/API; G8 cannot pass while these reachable paths remain.
- **Required action:** Preserve resource errors from every `read_name` caller; reject or cap unenforceable explicit values; order configured/effective resource checks before overlapping hard malformed guards; and detect oversized/truncated synchronous UDP datagrams before parsing. Add fresh independent UDP/TCP evidence for record-owner expansion/pointer exhaustion, default RR/pointer boundaries, invalid over-hard configuration, and synchronous over-limit UDP datagrams. Each excess must be terminal `RESOURCE_LIMIT` with no takeable result.
- **Re-review criterion:** A new authorized implementation candidate, fresh independent G7 approval covering these paths, and fresh independent G8 verification with no unresolved blocking finding.

Formal return handoff: `handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`.

### DNS-G8-002 — global request tracking and cross-context lifecycle

- **Severity:** Prior High.
- **Blocking:** No at candidate `c38a7fa`.
- **Disposition:** **RESOLVED for this candidate.** The process-global request list is removed. `ratos_context` owns `dns_requests`, `dns_outstanding_requests`, and `dns_connections`; requests carry explicit outstanding/TCP slot flags. Start acquires the outstanding slot before exposure, correlated UDP `TC=1` acquires TCP capacity before entering `TCP_PENDING`, and completion/failure/cancellation/destruction release held slots idempotently. Context destruction walks only its own list, cancels pending requests, preserves terminal state and COMPLETE results, releases slots, clears links/context pointers, and then frees context storage.
- **Concurrency/lifetime judgment:** Distinct contexts mutate disjoint lists/counters and no unsynchronized global request tracker remains. Under the approved externally serialized same-context contract, request/context destruction does not race with operations on that same context. Detached state/error accessors, COMPLETE take-result, and request destruction use request-owned storage; receive/transport/cancel reject detached handles before context dereference. G7's exact-candidate harness covered cap refusal/reuse, terminal release, pending/failed/COMPLETE detach behavior, post-detach rejection, COMPLETE take-result, and 1,000 start/destroy cycles in each of two distinct-context threads. TSan was unavailable, so the closure is based on direct ownership/control-flow review plus normal/ASan/UBSan G7 evidence, not race-detector proof.

## Other adversarial classes and residual risk

- **Malformed lengths and allocation:** Packet reads use remaining-length checks; RDLENGTH is bounded before raw allocation/copy; TCP length is checked before frame allocation; partial results are destroyed on failure. No new memory-safety blocker was established in those paths. DNS-G8-001 remains the blocking configured-budget classification/admission gap.
- **Amplification/session exhaustion:** Per-context outstanding and TCP counters now bound incremental requests and release capacity on every terminal path. UDP requests do not consume TCP capacity until correlated truncation. The synchronous API remains externally serialized per context. Network retries, caching, and process-wide quotas are outside the approved profile.
- **Terminal no-result behavior:** `request_fail` destroys frame/result state and releases slots; cancellation and context teardown clean pending state; only COMPLETE retains/takes a result. G7 directly exercised these accounting/lifetime paths. DNS-G8-001 still misclassifies some terminal outcomes but did not reveal partial result publication.
- **UDP/TCP admission:** Incremental input checks explicit sizes and TCP framing before allocation. TCP fallback admission is context-local and exact-once. Synchronous UDP full-datagram truncation detection remains unresolved under DNS-G8-001.
- **Authentication and later evidence:** Plain DNS authenticity, DNSSEC, encrypted transports, retry policy, EDNS, and G9 fuzzing are outside this assignment. No-crash evidence is not treated as proof. TSan, CMake/CTest, dynamic socket-truncation reproduction, and fresh parser-boundary probes were not executed by this leaf.

## Disposition

**G8: CHANGES_REQUESTED.** `DNS-G8-002` is resolved for candidate `c38a7fa`, but `DNS-G8-001` remains a reachable blocking finding unchanged from the prior G8 subject. G8 therefore does not pass. This reviewer does not update workflow state, route G9, or route any other stage.