# Handoff: G9 record resource triage blocker

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `DNS-G9-RECORD-RESOURCE-TRIAGE-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` — `ratos_fuzz_dns_record` resource growth |
| Owner role | `fuzz-engineer/g9-record-resource-triage-001` |
| Status | `BLOCKED` |
| Inspection baseline | local `HEAD` `2162d33d8b2db5ace97cff25ada0cd89322aa5d4` |
| Historical evidence revision | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Source artifacts | `g9-full-campaign-execution-002/{fuzz-plan.md,fuzz-results.md,handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md}`; `g9-record-resource-assessment-001/api-design.md`; `fuzz/dns/{fuzz_dns_record.c,fuzz_dns_packet.c,fuzz_dns_name.c,corpus/README.md,corpus/seeds.txt}` |
| Assumptions | `-rss_limit_mb=1024` is mandatory and unchanged. |
| Open questions | What component owns the demonstrated RSS growth, and what numeric resource policy/authority applies? Blocking; protocol-orchestrator. |
| Limitations | Static inspection only; no campaign, retry, instrumentation, code change, workflow-state update, or G9 security-review route. |

## Routing

- ID / workflow / stage: `DNS-G9-RECORD-RESOURCE-TRIAGE-001` / `dns-implementation-20260913` / G9.
- Source role and assignment: `fuzz-engineer/g9-record-resource-triage-001`.
- Destination role: `protocol-orchestrator`.
- Target protocol/component: DNS record parser fuzz target.
- Reason: a mandatory record-target RSS failure is confirmed, but no fuzz-strategy/harness-only cause is proven.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts and evidence

At `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`, the record target returned 71 after `21.236172719858587` seconds, with `ru_maxrss` `1,675,884 KiB` and `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`. Its generated OOM artifact had SHA-256 `23b56d8f1807e20c6a37be929283eaf0ed81d38cd5c7e9609d49b05840996a38` and was removed. Packet and name targets were clean; no crash, ASan, UBSan, or timeout was observed.

Static harness inspection shows that the record target constructs a bounded (65,535-byte) one-answer DNS response, fuzzes RR type and RDATA, and caps copied RDATA at 65,494 bytes. The fixed corpus deliberately includes a 65,535-byte maximum-boundary seed. This is evidence that the harness intentionally reaches a bounded record path; it is not evidence of independent harness retention or allocation growth. The prior design assessment also states that the G9 result does not establish an allocation/lifetime cause and that numeric default resource policy remains unresolved.

## Specific problem or question

The exact source of RSS growth cannot be assigned to the fuzz strategy/harness from existing evidence. Changing the record harness to avoid large RDATA, changing corpus coverage, or raising the RSS budget would remove required boundary/resource evidence without proving a harness defect. The fuzz-engineer lacks authority to inspect/instrument or change native implementation and lacks the missing numeric resource-policy decision.

## Requested action

Keep G9 `BLOCKED`. Obtain the maintainer/product resource-policy decision (or explicit documented decision that no numeric default change is needed), then route a revision-bound, narrowly scoped root-cause investigation to the authorized owner. Preserve the historical campaign evidence and exact 1024 MiB budget. Do not route G9 security review or a new campaign from this handoff.

If that investigation proves a fuzz-only cause, authorize at most `fuzz/dns/fuzz_dns_record.c` in a new assignment and require a separate fresh campaign afterward. If it proves a native cause, route it through design/G6 authority and the appropriate implementation/review sequence.

## Acceptance criteria

1. A responsible owner records evidence separating harness behavior from native parser/resource behavior and identifies the corrective owner/path, or explicitly proves a harness-only defect.
2. Any policy/design/G6 prerequisites required by that evidence are recorded at exact revisions; the 1024 MiB G9 budget remains unchanged.
3. Only after a candidate is authorized may the orchestrator issue a separate execution assignment. A future independent security reviewer evaluates only fresh, clean campaign evidence.

## Resolution (destination role)

Pending protocol-orchestrator action.

## Closure (orchestrator after verification)

Pending. G9 must remain `BLOCKED`; this handoff is not G9 approval.
