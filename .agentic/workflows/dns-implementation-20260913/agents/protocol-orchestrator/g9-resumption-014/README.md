# G9 resumption 014 — policy-authority blocker

| Field | Value |
| --- | --- |
| Workflow / stage | `dns-implementation-20260913` / DNS fuzzing (G9) |
| Active role | `protocol-orchestrator` |
| Scope | One bounded resumption determination only; no specialist dispatch. |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline verified | `git:b40825c9bdf1e94c21c82d36b375b42850022cc0` locally and at `origin/hermes/dns-implementation-20260913` |
| Shared-state change | None; existing workflow/G9 status remains `BLOCKED`. |

The fresh `g9-full-campaign-execution-004` record-target run failed with exit 71 and libFuzzer out-of-memory under the mandatory `-rss_limit_mb=1024` cap. This source evidence does not establish a cause or authorize a corrective path. The durable handoff `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` remains `BLOCKED`, with `Pending maintainer/product decision.`

No project-specialist corrective stage is eligible until the maintainer/product owner provides the required numeric resource-policy decision (or explicit no-numeric-default-change decision) and, if change follows, the responsible design owner supplies a revision-bound candidate and exact private paths for a fresh G6 authority assessment. No G9 security reviewer is routed.
