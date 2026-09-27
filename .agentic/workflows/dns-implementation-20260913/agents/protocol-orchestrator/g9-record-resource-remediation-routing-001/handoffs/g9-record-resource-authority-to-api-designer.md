# Handoff: G9 record-parser resource-growth authority and design assessment

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-authority-to-api-designer` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` record-parser resource growth |
| Owner role | `protocol-orchestrator/g9-record-resource-remediation-routing-001` |
| Status | `BLOCKED` |
| Revision | `git:8698fe9e5732f7b7b539d0130b13f4d3d730759f` |
| Source artifacts | G9 execution-002 failure, handoff, delivery verification, current G6 authority record, current workflow state |
| Assumptions | The `-rss_limit_mb=1024` budget is mandatory and cannot be increased. |
| Open questions | Does an approved resource-policy/design already determine a bounded private correction for the observed record-parser campaign failure? If not, what revised design/authority is required? |
| Limitations | This coordinator did not rerun fuzzing, diagnose code, amend design truth, or patch production. |

## Routing

- ID / workflow / stage: `DNS-G9-RECORD-RESOURCE-AUTHORITY-001` / `dns-implementation-20260913` / G9 blocker return.
- Source role and assignment: `protocol-orchestrator/g9-record-resource-remediation-routing-001`.
- Destination role: `protocol-api-designer`.
- Target protocol/component: DNS record parser and its approved resource policy.
- Reason: a reproducible mandatory G9 record-target RSS failure requires a corrective scope, but the current revision-bound G6 authority does not cover a new parser correction.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts

1. `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md`, tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`: LLVM 19 build passed; packet and name were clean; `ratos_fuzz_dns_record` returned 71 after 21.236172719858587 seconds with `ru_maxrss` 1,675,884 KiB and `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`.
2. `agents/fuzz-engineer/g9-full-campaign-execution-002/handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`, blocking handoff preserving the budget and requesting root-cause/owner/remediation evidence only.
3. `agents/protocol-orchestrator/g9-full-campaign-reroute-002/verification/g9-full-campaign-execution-002-delivery-verification.md`, which verified the leaf boundary and mandatory resource failure.
4. `agents/protocol-orchestrator/g8-accounting-g4-g6-implementation-routing-001/preflight-verification.md` and `workflow-state.yaml` G6 entry: current G6 is approved only for the accounting design and exact private paths `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c`; it explicitly excludes parser work.
5. `fuzz/dns/fuzz_dns_record.c` invokes `ratos_dns_parse_response`; `src/protocols/dns/dns_parser.c` is therefore implicated as a potential implementation surface but is outside current G6 authorization. This is scope evidence, not a root-cause conclusion.

## Specific problem or question

The failure evidence proves only that the required record fuzz run exceeded the fixed RSS budget. It does not identify the allocation/lifetime cause or authorize a parser change. Current G6 cannot be broadened administratively by this coordinator: approval is revision- and scope-bound, and its express four-path accounting scope excludes `src/protocols/dns/dns_parser.c`.

## Requested action

Assess the approved DNS resource-policy/design against the exact G9 evidence. Produce an owned design/decision/handoff that states one of the following without changing code: (a) an already approved design gives a concrete, bounded private corrective path and no API/semantic change; or (b) a revised design/approval is required, including the exact requirements, private paths, and any necessary renewed gates. Do not dispatch implementation, alter fuzz budget/corpus/harness/CMake, or route G7/G8/G9/later work.

## Acceptance criteria

- A `protocol-api-designer` owned, revision-bound record identifies whether the issue is within existing approved resource semantics or requires a design change.
- It names only the exact candidate private path(s) if an implementation route becomes appropriate, and records no public ABI change unless independently required and approved.
- It preserves the mandatory 1024 MiB G9 budget and supplies a formal handoff to `protocol-orchestrator` for a new G6 authority assessment.
- An independent designated review is obtained before any renewed G6 or native implementation dispatch where required by the resulting design.

## Resolution (destination role)

Pending `protocol-api-designer` assessment.

## Closure (orchestrator after verification)

Pending. G9 remains `BLOCKED`; no implementation or reviewer is authorized by this handoff.