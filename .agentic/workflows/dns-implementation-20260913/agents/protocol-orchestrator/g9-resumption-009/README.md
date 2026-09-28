# G9 resumption 009 — authorized name-harness bounds remediation

| Field | Value |
| --- | --- |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| ACTIVE ROLE / hierarchy | `protocol-orchestrator`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Scope | One bounded corrective fuzz-harness remediation attempt only; no G9 campaign, G9 security review, or other route. |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `d489d749a37548e1e711d11c10b53b2041281bbf` (local HEAD and fetched `origin/hermes/dns-implementation-20260913`) |
| Assignment | `fuzz-engineer/g9-name-harness-bounds-remediation-002` |
| Leaf workspace | `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-bounds-remediation-002/` |
| Requested / actual orchestration route | `openai-codex/gpt-5.6-terra` / low; runtime model shown by this session is `gpt-5.6-terra`, reasoning telemetry unknown |
| Requested leaf route | `openai-codex/gpt-5.6-terra`, medium; actual child route/effort must be recorded honestly by the child |

The newest prior campaign blocker reports a 1,133-byte name input causing UBSan/ASan overflow at `fuzz/dns/fuzz_dns_name.c:12:32`. Current baseline source already contains the prior `sizeof(packet) - 17u` cap and commit `2c9e9b945352642d27cf703132e8e5e525b8b5cb` is an ancestor of the dispatch baseline. That historical status is not treated as live work or sufficient fresh evidence. The sole leaf must independently inspect and remediate only if the minimal cap correction is absent; if it is already present, it must perform a no-op corrective attempt, validate it, and report the no-op fact without changing any source.

The only authority is the complete leaf packet in `delegations/fuzz-engineer-g9-name-harness-bounds-remediation-002.md`. G9 remains BLOCKED regardless of a successful focused remediation; fresh complete campaign evidence and later independent G9 security review are deliberately not routed here.