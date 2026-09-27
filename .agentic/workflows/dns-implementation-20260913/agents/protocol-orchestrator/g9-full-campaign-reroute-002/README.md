# G9 full-campaign reroute 002

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-reroute-002` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| ACTIVE ROLE / hierarchy | `protocol-orchestrator`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Scope | Exactly one fresh bounded full DNS fuzz campaign; no G9 security review, binding, documentation, or later-stage routing. |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `git:cb0918853f8d795c9abe07241a87b03fc90cb229` (local HEAD and origin ref verified) |
| Leaf assignment / workspace | `g9-full-campaign-execution-002` / `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/` |
| Requested / observed route | requested `openai-codex/gpt-5.6-terra`, medium; effective runtime `gpt-5.6-terra`; effort telemetry unavailable/unknown. |

The sole prior full campaign (`g9-full-campaign-execution-001`) built the three existing targets but stopped before target launch because `/usr/bin/time` is absent. This reroute replaces only that unavailable measurement wrapper with a Python monotonic-clock and `resource.getrusage(RUSAGE_CHILDREN)` measurement wrapper. `/usr/bin/timeout` and `/usr/bin/python3` were verified available; `/usr/bin/time` remains absent.

No technical G9 approval is asserted. The leaf must return `READY_FOR_REVIEW` only if all three bounded serial targets are clean; a future independent G9 security review remains unassigned and must not be dispatched here.