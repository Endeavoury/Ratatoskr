# G9 resumption 010 — DNS name-harness corrective verification

| Field | Value |
| --- | --- |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| ACTIVE ROLE / hierarchy | `protocol-orchestrator`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Scope | Exactly one bounded corrective fuzz-harness attempt. No G9 campaign, G9 security review, or later-stage routing. |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `2c6b0bc742d3db88cc94b9e6e354b362ee0f6055` = `origin/hermes/dns-implementation-20260913` |
| Assignment | `fuzz-engineer/g9-name-harness-bounds-remediation-003` |
| Requested leaf model / effort | `openai-codex/gpt-5.6-terra` / `medium`; actual runtime telemetry must be recorded as unknown if unavailable. |

The verified execution-005 evidence is a blocked sanitizer failure at `fuzz/dns/fuzz_dns_name.c:12`. Current source already has the bounded-copy form `sizeof(packet) - 17u`; earlier remediation evidence is historical only. The new leaf must independently inspect current source and execute one focused no-op validation if it remains safe, or make only the same minimal bounds correction if it does not. G9 stays BLOCKED regardless of this leaf outcome.
