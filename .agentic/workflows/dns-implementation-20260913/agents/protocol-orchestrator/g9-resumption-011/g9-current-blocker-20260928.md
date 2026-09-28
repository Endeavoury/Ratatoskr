# G9 resumption 011 — current authoritative blocker addendum

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-resumption-011-current-blocker-20260928` |
| Workflow / stage / target | `dns-implementation-20260913` / fuzzing (G9) / `protocol/dns` |
| Owner role / status | `protocol-orchestrator` / `BLOCKED` |
| Observed repository revision | `git:8f837d08947c17a25521be6a1743cfa43d4ff602` = `origin/hermes/dns-implementation-20260913` before this addendum |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Scope | One bounded resumption/routing decision; no specialist dispatch or technical-gate decision |

## Current evidence

The current shared state records workflow, fuzzing, and G9 as `BLOCKED`; assignment `fuzz-engineer/g9-full-campaign-execution-006` is complete with its factual blocking result. Its committed handoff records a serial packet/name/record campaign: packet and name completed cleanly, while `ratos_fuzz_dns_record` returned exit 71 after libFuzzer reported `out-of-memory (used: 1112Mb; limit: 1024Mb)`. This is blocking evidence only, not a G9 acceptance or a root-cause determination.

No live `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, or `ratos_fuzz_dns_record` execution was observed.

## Prerequisite and routing determination

`DNS-G9-RESOURCE-POLICY-MAINTAINER-001` remains the authoritative blocker in `workflow-state.yaml`. Its maintainer/product handoff remains unresolved: no durable numeric DNS default/hard-limit decision (or explicit no-numeric-default-change decision) is recorded. The current blocked API-design assessment authorizes no private corrective path; it requires the maintainer decision, any resulting responsible-owner revision-bound design candidate with exact private paths, and then a fresh G6 authority assessment.

Accordingly, no authorized specialist leaf exists. Do not route implementation, review, rerun, policy, G9 security review, bindings, or later-stage work. Preserve the mandatory `-rss_limit_mb=1024` limit. Shared `workflow-state.yaml` already accurately references this blocker, so it is intentionally unchanged.

## Required return

Maintainer/product owner must resolve `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` through `protocol-orchestrator`. If the decision produces a corrective change, the responsible design owner must provide a non-stale, revision-bound candidate and exact private paths before the orchestrator performs a fresh G6 authority assessment.
