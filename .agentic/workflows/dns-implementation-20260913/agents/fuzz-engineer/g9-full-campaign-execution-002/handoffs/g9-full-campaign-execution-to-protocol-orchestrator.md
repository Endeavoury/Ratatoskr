# Handoff: G9 full campaign resource-limit failure

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-002-handoff` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `fuzz-engineer/g9-full-campaign-execution-002` |
| Status | `BLOCKED` |
| Revision | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Source artifacts | `fuzz-plan.md`; `fuzz-results.md`; ephemeral `/tmp/ratatoskr-g9-full-campaign-execution-002/record-run.json` |
| Assumptions | The declared 1024 MiB libFuzzer RSS limit is mandatory and must not be changed by this assignment. |
| Open questions | Root cause and remediation owner, protocol-orchestrator; blocking. |
| Limitations | This author does not diagnose or patch native/fuzz code and performed no retry. |

## Routing

- ID / workflow / stage: `dns-implementation-20260913-g9-full-campaign-execution-002` / `dns-implementation-20260913` / G9.
- Source role and assignment: `fuzz-engineer/g9-full-campaign-execution-002`.
- Destination role: `protocol-orchestrator`.
- Target: DNS record parser fuzz target.
- Reason: the fresh serial campaign stopped on the record target's explicit libFuzzer RSS-limit failure.
- Blocking: true.
- Status: `BLOCKED`.

## Source evidence

At tested HEAD `90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`, the prescribed LLVM19 build succeeded. Packet and name executions were clean. The first record execution used the required flags unchanged and returned 71 after 21.236172719858587 monotonic seconds; child `ru_maxrss` was 1,675,884 KiB. Captured diagnostic: `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`. The generated `oom-f1545b193bff32ed14265f7211065e43346a6de0` had SHA-256 `23b56d8f1807e20c6a37be929283eaf0ed81d38cd5c7e9609d49b05840996a38` and was removed from the repository root; complete logs remain only under `/tmp`.

## Requested action

Determine the appropriate owner and bounded corrective scope for the record-target resource growth; preserve the failed budget and evidence. A subsequent authorized campaign must be a new assignment. Do not treat this artifact as G9 approval and do not route G9 security review from this handoff.

## Acceptance criteria

A responsible owner records root cause and remediation evidence; the orchestrator supplies a new, independently scoped execution assignment if and only if appropriate. A later security reviewer independently evaluates only a clean candidate campaign.

## Resolution (destination role)

Pending protocol-orchestrator action.

## Closure (orchestrator after verification)

Pending.