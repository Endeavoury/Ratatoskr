# Handoff: G9 full campaign record resource failure

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-004-handoff` |
| Workflow / stage | `dns-implementation-20260913` / G9 fuzzing |
| Source / destination | `fuzz-engineer/g9-full-campaign-execution-004` → `protocol-orchestrator/g9-corrective-full-campaign-routing-004` |
| Target | `protocol/dns` record parser fuzz target |
| Status / blocking | `BLOCKED` / true |
| Tested revision | `git:b82ea8499600c3ef7ab1e51fa297b477b1f17c1c` |

## Evidence

Required input digests, G7/G8 approvals, packet ancestry, LLVM19 toolchain, one exact configure/build, and the fixed first-colon-derived corpus were verified. Packet and name completed cleanly under the recorded budget. Record was launched once, serially, with:

```text
/usr/bin/timeout 120s /tmp/ratatoskr-g9-full-campaign-execution-004/build/fuzz/ratos_fuzz_dns_record /tmp/ratatoskr-g9-full-campaign-execution-004/corpus-record -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

It returned 71 after 10.101190892979503 monotonic seconds. Captured stderr reports `ERROR: libFuzzer: out-of-memory` and `SUMMARY: libFuzzer: out-of-memory`; wrapper child `ru_maxrss` changed from 499624 KiB to 1071852 KiB. Complete output is `/tmp/ratatoskr-g9-full-campaign-execution-004/record-run.json`.

## Requested action

Record this factual G9 blocker and determine the appropriate independently authorized corrective owner/scope. Preserve the required budget and this evidence. Any successor campaign requires a new fresh assignment.

## Acceptance criteria

A responsible owner records root cause/remediation evidence and the protocol orchestrator issues a new unambiguous campaign assignment only if authorized. Do not treat this as G9 approval or route G9 security review from this handoff.

## Resolution

Pending protocol-orchestrator action.
