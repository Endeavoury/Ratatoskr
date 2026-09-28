# G9 record-resource strategy/harness triage

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-triage-001-plan` |
| Workflow / stage | `dns-implementation-20260913` / G9 fuzzing |
| Owner | `fuzz-engineer/g9-record-resource-triage-001` |
| Status | `BLOCKED` |
| Inspection baseline | local `HEAD` `2162d33d8b2db5ace97cff25ada0cd89322aa5d4` |
| Historical campaign revision | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Mandatory budget | `-rss_limit_mb=1024` (preserved; not executed or changed) |

## Inspection scope

Read-only inspection covered `fuzz/dns/fuzz_dns_record.c`, its packet/name peers, `fuzz/CMakeLists.txt`, and `fuzz/dns/corpus/{README.md,seeds.txt}`; preserved campaign plan, results, and prior handoff; the current toolchain preflight; and the record-resource design assessment. No corpus decoding, fuzzer launch, build, `ctest`, retry, flag change, or source edit occurred.

## Observed facts

1. The historical record run returned 71 after `21.236172719858587` seconds with `ru_maxrss` `1,675,884 KiB`; libFuzzer reported `out-of-memory (used: 1636Mb; limit: 1024Mb)`. Packet and name returned 0 with no sanitizer, crash, timeout, or resource marker. The record OOM artifact digest was `23b56d8f1807e20c6a37be929283eaf0ed81d38cd5c7e9609d49b05840996a38`; it was removed.
2. `fuzz_dns_record.c` creates a fresh context/result per input, synthesizes a DNS response with one answer, sets RR type from the first two input bytes, and sets RDLENGTH to the copied fuzz payload length. Its local packet is capped at 65,535 bytes and payload is capped at `65535 - 31 - 10 = 65494` bytes.
3. The corpus explicitly includes a 65,535-octet `maximum-size` seed. The corpus README states that maximum packet boundaries are intended coverage. The record harness's maximum RDATA therefore exercises a stated boundary rather than an accidental unconstrained host allocation.
4. Packet fuzzing can also pass input up to the fuzzer-provided size to `ratos_dns_parse_response`; it was clean. Name fuzzing is locally capped at 1007 bytes. All targets use the same fuzzer/address/undefined sanitizer options and link target.

## Assessment

**Observed:** the record-specific structured grammar reaches a parser path that exceeded the mandatory RSS budget.

**Not established:** that the record harness leaks, retains state, over-allocates independently, or is otherwise defective; nor which native allocation/lifetime/algorithmic path caused RSS growth. The single historical OOM artifact is unavailable, and no execution or instrumentation authority exists in this assignment. The packet/record difference is a useful localization signal only, not proof: their inputs and reached parser paths differ.

Limiting RDATA, removing the maximum boundary seed, weakening the invariant, or raising the 1024 MiB limit would suppress required hostile-input/boundary coverage and is forbidden. No fuzz-only remediation is evidenced; `fuzz/dns/fuzz_dns_record.c` remains unchanged.

## Bounded future prerequisite

The protocol orchestrator must first retain `BLOCKED`, obtain the unresolved maintainer/product numeric resource-policy decision (or documented determination that no policy revision is required), and obtain revision-bound authority for a narrow root-cause investigation. A future authorized owner must distinguish harness retention from native parser/resource behavior with retained evidence. Only if that evidence proves a fuzz-only defect may a separate fuzz-engineer assignment change the single record harness, followed by a separately authorized fresh campaign under unchanged `-rss_limit_mb=1024`.
