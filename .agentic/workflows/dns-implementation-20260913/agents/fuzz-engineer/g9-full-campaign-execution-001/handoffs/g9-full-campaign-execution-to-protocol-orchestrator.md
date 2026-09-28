# Handoff: G9 full campaign execution blocker

| Field | Value |
| --- | --- |
| ID | `dns-implementation-20260913-g9-full-campaign-execution-001` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Source / destination | `fuzz-engineer` → `protocol-orchestrator` |
| Status | `BLOCKED` |
| Blocking | Yes |
| Baseline | `git:dd1c0f3987a88a4c0b0d16afbeddc1043674561d` |

## Reason and evidence

All required source/corpus digests, packet ancestry, tracked cleanliness, repository identity, LLVM19 configure/build, and first-colon corpus conversion passed. The first serial target did not start because the measurement wrapper `/usr/bin/time` was absent:

```text
timeout: failed to run command ‘/usr/bin/time’: No such file or directory
```

The packet command exited `127` at `2026-09-27T06:25:25+02:00`. This is a required nonzero-exit stop condition. No fuzz target executed; name and record were deliberately not run; no retry, workaround, minimization, or security-review routing was performed.

## Requested action and acceptance criteria

The protocol-orchestrator must record this blocked assignment and decide any future authorized fresh campaign separately. Do not treat these records as G9 fuzz evidence or route G9 security review from them. A future campaign, if separately dispatched, must start from a new packet and independently repeat all required provenance/build/run checks.

## Resolution

Unresolved; owned by `protocol-orchestrator`.