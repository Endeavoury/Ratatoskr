# G8 DNS configured-limits security re-review

## Scope, identity, and immutable inputs

This is the fresh independent G8 review by `security-reviewer/g8-limits-rereview-001`; the runtime session ID is not exposed. I did not author the DNS implementation, either limits remediation, any G7 evidence, or prior G8 review `g8-security-review-001`.

Reviewed subject is candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`, author-artifact delivery `git:3bb81004050ca860ce8d9572f4e834847daf5b96`, and approved G7 reviewer delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d`. All three are ancestors of checked-out HEAD and `origin/hermes/dns-implementation-20260913`; the pre-review origin readback was `6f2e217eed356d09c70d320297bbf9ebd6245137`. No production/header/test/build delta exists from candidate to HEAD.

Verified content evidence includes:

- candidate `dns_parser.c`: `sha256:05f4e0ea0c92b17dd1a00bd9c53c530fac9a2034cba158c2b4019b44bde79216`;
- approved G7 record: `sha256:e8f094ccb164ab087891a51f4b05a75693804a07abf9ed22da36daf6d4dfb06e`;
- approved analysis/model/API/vectors: `sha256:5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`, `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`, `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`, and `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`;
- prior G8 delivery `git:90a02df18522b6c311e236dc03c82583971c7511`, fetched by exact object ID and confirmed ancestral; historical report/review/handoff hashes are `f373e7472ad7d6042c7033e36cb6d7014674b89b1bbf4ef7855b0a7f8331ddb8`, `8bccb9804493a3b1be314e12ca7a3c36e439138211ad087ad94010cdb9adb393`, and `42d821344746ee7c67e9bd431794341e9ec1ec81cc4397f7387f3c0776fd009c`.

## Threat model

Assets are process memory and availability, configured parsing and transport budgets, separate-context concurrency, request correlation state, terminal error classification, and atomic result ownership. Attackers include a malicious/on-path upstream able to return correlated UDP datagrams or TCP frames and an untrusted caller able to exercise the documented separate-context concurrency surface. Entrypoints are synchronous `ratos_dns_query`, incremental `ratos_dns_request_receive_udp`/`receive_tcp`, limits configuration, request start/destruction, and the hostile-input parser. Trust boundaries are caller configuration, peer and frame metadata, OS datagram delivery, parser allocation/copy/traversal, request tracking, and result publication.

Assessed classes include malformed lengths and counts, offset arithmetic, compressed-name cycles/traversal, expansion and allocation amplification, RR/RDATA iteration/copy, UDP truncation ambiguity, TCP preallocation framing, active-request exhaustion, partial-result cleanup, lifetime, and cross-context concurrency.

## Controls that are present

Candidate-equivalent source has finite zero-value defaults and validates UDP/TCP maxima, total-RR hard maximum, and connection/outstanding coherence. Incremental UDP and TCP reject configured frame excess before parsing or frame allocation. Synchronous TCP checks the length prefix before frame allocation. Configured RR count is normally checked before result/record-array allocation; name expansion and compression traversal counters are checked before copy/traversal; typed RDLENGTH is checked before raw-data allocation/copy. `request_fail` destroys frame/result state, and `take_result` is unavailable outside COMPLETE.

The fresh G7 record executed successful terminal/no-result probes for question/RDATA name-expansion and compression-pointer cases, plus strict compilation and existing native executables. This review independently reran strict C11 syntax compilation successfully. Those checks do not cover the findings below.

## Findings

### DNS-G8-001 — configured-limits remediation remains incomplete

- **Severity:** Medium.
- **Blocking:** Yes.
- **Owner:** `c-protocol-implementer`.
- **Requirements/design:** `DNS-REQ-024`; model `INV-BOUNDED-PARSING`, `INV-TCP-CORRELATED-DISPOSITION-PARTITION`; API design §4 (`max_udp_message_bytes`, RR/count work, expanded names, pointer work, coherent explicit values, terminal resource-limit/no-result).
- **Evidence and reachable paths:**
  1. `src/protocols/dns/dns_parser.c:374-376` combines record-owner `read_name` with structural reads and returns `RATOS_ERROR_PROTOCOL` for every failure. With `max_compression_pointer_traversals=1`, a valid correlated response containing two compressed record-owner names consumes one traversal on the first owner and exceeds the configured cumulative budget on the second. `read_name` returns the resource result, but `read_records` converts it to malformed; `request_parse` therefore reports `MALFORMED_RESPONSE`, not `RESOURCE_LIMIT`. The same conversion affects configured name-expansion exhaustion in a record owner. UDP and completed TCP frames share this parser. G7's retained evidence covered question/RDATA cases, not this record-owner caller.
  2. `dns_parser.c:97-99` evaluates the fixed 128-hop malformed guard before the configured traversal limit. `dns_client.c:75-81` accepts explicit `max_compression_pointer_traversals > 128` even though the parser's implementation maximum is 128. At the default/effective limit 128, the 129th valid backward-pointer traversal is classified malformed before the configured-limit branch; with an accepted value above 128, that value is never enforceable. This contradicts coherent-value validation and the required resource-first partition.
  3. `dns_parser.c:418-420` tests `RATOS_DNS_MAX_RECORDS` first and returns malformed before testing the effective configured default, which is the same 4,096 records. A 4,097-record minimal response is wire-reachable within the DNS message maximum (45,084 octets with a root question and zero-length minimal RRs) but is classified malformed rather than terminal resource-limit.
  4. `src/protocols/dns/dns_transport_udp.c:91-100` allocates exactly `max_udp_message_bytes` and uses plain `recv` with that capacity on POSIX. A larger datagram is truncated to the configured capacity without a returned full-datagram length or truncation flag. If the retained prefix is a complete correlated DNS response and the discarded suffix would otherwise be trailing bytes, the synchronous path accepts a datagram larger than the configured admitted-message limit. The incremental UDP path correctly receives an explicit full length and rejects excess; the synchronous path does not.
- **Impact/rationale:** Traversal/count/record-owner exhaustion stops work and publishes no result, but mandatory security classification is lost and accepted explicit limits can be incoherent. The synchronous UDP path can accept an over-limit datagram by truncating away attacker-controlled trailing bytes, defeating both the configured admission boundary and strict exact-message consumption. These are reachable policy and ambiguity failures, so DNS-G8-001 is not closed.
- **Required remediation:** Preserve resource results from every `read_name` caller; validate or remove unenforceable explicit maxima; apply configured/effective resource disposition before overlapping hard malformed guards; and receive UDP in a way that detects full datagram length/truncation before acceptance. Add independent UDP and TCP evidence for record-owner expansion/pointer exhaustion, effective-default RR/pointer boundaries, invalid over-hard configurations, and synchronous over-limit UDP datagrams. All failures must remain terminal with no takeable result.
- **Re-review criterion:** A new candidate and fresh independent G7/G8 evidence demonstrate the above paths and no regression to already passing allocation/copy/traversal checks.

Formal handoff: `handoffs/dns-g8-001-configured-limits-remediation-incomplete.md`.

### DNS-G8-002 — global request tracker violates separate-context concurrency

- **Severity:** High.
- **Blocking:** Yes.
- **Owner:** `c-protocol-implementer`.
- **Requirements/design:** `docs/architecture.md:67-72` states separate contexts may run concurrently and no resolver state is global; `docs/agentic/SECURITY_MODEL.md` requires lifetime/threading review; API ownership permits distinct requests/contexts while only same-context mutable use is externally serialized.
- **Evidence and reachable sequence:** The remediation introduced process-global `static ratos_dns_request *context_requests` at `src/protocols/dns/dns_client.c:193`. `active_requests_for_context` traverses it without synchronization (`:194-199`), request start prepends to it (`:212-216`), and request destruction walks and unlinks from it (`:247`). Two supported callers operating on separate contexts can concurrently start/destroy requests. One thread can traverse a node while another unlinks and frees it, or two writers can race on the head/link fields. Under C11 this is a data race with undefined behavior and creates reachable list corruption/use-after-free/process-failure risk.
- **Impact/rationale:** The defect crosses context isolation and can corrupt memory in a documented concurrent-use scenario. A network peer can influence request terminal timing, but no malicious peer is needed; ordinary concurrent SDK use is sufficient.
- **Required remediation:** Eliminate process-global mutable resolver tracking or provide a reviewed synchronization/lifetime design that preserves separate-context concurrency. Prefer context-owned accounting with context-outlives-request enforcement. Verify start, terminal transition, cancellation, destruction, and concurrent distinct-context operations with race-detection/stress evidence.
- **Re-review criterion:** A new implementation revision has no unsynchronized global request list and independent evidence shows correct per-context caps and destruction under documented concurrent use.

Formal handoff: `handoffs/dns-g8-002-global-request-tracker-race.md`.

## Residual risks and limitations

No additional memory-safety defect was established in bounded packet reads, RDLENGTH checks, TCP prefix/body allocation, or partial-result destruction during this bounded re-review. Plain DNS authenticity, DNSSEC/encrypted transport, retry policy, EDNS, and G9 fuzzing remain outside this assignment. `cmake` and `ctest` are not installed, so CMake/CTest were not run. No new test/probe source was authored; existing G7 execution evidence was reviewed, and strict candidate-equivalent C11 syntax compilation passed. Dynamic UDP-truncation and concurrency reproductions were not executed, so the findings rely on direct control-flow/lifetime evidence and documented platform/API semantics.

## Disposition

**G8: CHANGES_REQUESTED.** DNS-G8-001 remains incompletely remediated, and remediation introduced blocking high-severity DNS-G8-002. G9 must not be routed from this assignment.