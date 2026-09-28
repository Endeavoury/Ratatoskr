# G8 DNS security assessment

## Scope, identity, and immutable inputs

This is an independent G8 assessment by the fresh `security-reviewer` leaf `g8-security-review-001`. I did not author the DNS implementation, G7 reviewer artifacts, or any remediation/fix. Reviewed subject: `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee`, corrective `dns_client.c` digest `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88`.

Input hashes were checked directly from their specified commits and matched: analysis `3b20866323491799ac4d3c29d8b9151da1472bfe` / `5bc0…d444`; model `f26745472178649a60f2cb079937d1bbe3f13c0b` / `155e…8700`; API `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c` / `69be…b520`; vectors `b7d05411cacfeb07be9f6bfbc36f705efdd002c5` / `6950…2cd6`; and G7 report/completion `1424debe5395a1650a05d2933ba01234c589e535` / `a9b0…3236`, `cdbf…77f`.

The corrective subject is an ancestor of current delivery baseline `732473104e8590b40d2cf8e00a3b23658327ca3f`; wrapper-mediated `git diff` found no post-subject changes in the reviewed DNS/header/core/test/build paths.

## Threat model

Assets are process memory/availability, request correlation context, result ownership, configured resource budgets, and caller-selected upstream identity. Attackers include an off-path packet injector and an on-path/malicious upstream that can send malformed UDP datagrams, TCP prefixes/frames, DNS compression graphs, high counts, large RDATA, or valid-looking response floods. Entrypoints are synchronous UDP/TCP exchanges and `ratos_dns_request_receive_udp`/`receive_tcp`; trust boundaries are caller input/options, network input, parser-to-result allocation, and copied request context. DNS authenticity remains out of scope: UDP is forgeable and DNSSEC/encrypted DNS are excluded.

Assessed classes: bounds/truncation and offset arithmetic; compression loops/forward pointers; name/RDLENGTH/count parsing; typed-RDATA allocation; TCP framing; correlation; lifecycle/partial-result cleanup; local-label validation; configuration/resource exhaustion; and unsupported OPT handling.

## Finding

### DNS-G8-001 — configured parsing limits are accepted but not enforced

- **Severity:** High (remote availability/resource-exhaustion policy bypass)
- **Blocking:** Yes
- **Owner:** `c-protocol-implementer`
- **Evidence:** `DNS-REQ-024` and model invariant `INV-BOUNDED-PARSING` require configured limits before allocation/iteration. API design §4 states each zero limit selects a finite implementation default and nonzero limits bound total RRs/work, expanded names, compression traversals, typed fields, outstanding requests, and connections.
- **Reachable behavior:** `ratos_dns_context_set_dns_limits` in `src/protocols/dns/dns_client.c:169-171` copies all fields after checking only UDP/TCP maxima. `ratos_dns_request_start` copies them into the request (`:180`), but `request_parse` only consults `max_udp_message_bytes` (`:186`) and TCP intake only consults nonzero `max_tcp_frame_bytes` (`:204`). `ratos_dns_parse_response`/`read_name`/`read_records` use hard-coded `RATOS_DNS_MAX_RECORDS` and packet limits, with no configured total-RR, expansion, pointer-traversal, or typed-field checks. No source or native/integration test reference to the six ignored limit fields was found.
- **Impact/rationale:** An upstream can make a request configured with a small nonzero work/memory budget parse and allocate up to the hard-coded profile maximum (including records, raw RDATA, escaped strings, and pointer work). This defeats the advertised per-context containment boundary and violates the mandated resource-limit-before-allocation/iteration disposition. It is remotely reachable through correlated UDP or TCP DNS responses.
- **Required remediation:** Implement finite documented defaults for every zero field; reject incoherent values; thread effective limits into parsing; enforce them before each relevant allocation/iteration/copy/traversal; classify excess as terminal `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`; enforce outstanding-request/connection limits or remove unsupported API fields through the owning design path. Add independent native evidence for every enforced class. Do not change canonical requirements/vectors to mask the defect.
- **Re-review criterion:** A fresh independent G8 reviewer verifies the corrected implementation at a new revision, validates limit-triggered terminal/no-result behavior under UDP and TCP, verifies no partial allocations/result escape, and confirms the fixed input revisions remain current.

## Residual risk and limitations

No separate memory-safety defect was established in the reviewed bounded parser: it checks packet reads, RDLENGTH, pointer direction/cycles, label/name limits, and rejects OPT. G7’s 64-octet local-label correction is consistent with its evidence. However, this does not cure DNS-G8-001.

CMake/CTest and fuzzing were not run by this review; fuzzing is G9 and outside scope. This review does not prove data authenticity, concurrency safety, network availability, or behavior beyond the scoped native DNS implementation.

## Disposition

**G8: CHANGES_REQUESTED.** DNS-G8-001 is unresolved and blocking. Formal return handoff: `handoffs/dns-g8-001-configured-limits-enforcement.md`.
