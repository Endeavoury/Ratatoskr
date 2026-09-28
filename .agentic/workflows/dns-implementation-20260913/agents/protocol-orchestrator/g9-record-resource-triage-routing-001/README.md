# G9 record resource triage routing 001

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-triage-routing-001` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9 corrective strategy/harness triage) |
| Root task / project | `dns-implementation-20260913` / `Ratatoskr` |
| Owner / ACTIVE ROLE | `protocol-orchestrator/g9-record-resource-triage-routing-001` |
| Status | `IN_PROGRESS` — exactly one fuzz-engineer leaf dispatched; G9 remains BLOCKED |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline observed at dispatch | local and origin branch `hermes/dns-implementation-20260913`: `2162d33d8b2db5ace97cff25ada0cd89322aa5d4` |

## Scope decision

G9’s designated failure route is strategy/harness → fuzz-engineer and crash → c-protocol-implementer. The fresh record-target result is an RSS-limit failure only: exit 71 after 21.236172719858587 seconds, `ru_maxrss` 1,675,884 KiB, and libFuzzer `used: 1636Mb; limit: 1024Mb`; no crash, sanitizer finding, or timeout. The narrowest permitted next stage is one fuzz-engineer strategy/harness root-cause/remediation-or-blocker triage. It may not run, retry, or alter a G9 campaign and may not touch production code.

The mandatory `-rss_limit_mb=1024` budget and failure evidence are preserved. No G9 security review or later G9 review is assigned.

## Delivery limitation

The required wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is executable and responds to `--help` (exit 2 with its usage). No commit or push is authorized by this routing assignment, so no remote write/readback is claimed.
