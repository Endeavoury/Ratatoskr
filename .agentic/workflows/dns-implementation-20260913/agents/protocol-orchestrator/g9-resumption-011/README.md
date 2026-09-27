# G9 resumption 011 — full DNS fuzz campaign routing

| Field | Value |
| --- | --- |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| ACTIVE ROLE / hierarchy | `protocol-orchestrator`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Scope | Exactly one fresh, bounded, serial three-target G9 fuzz campaign: packet, name, record. No G9 security review, bindings, or later-stage routing. |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4` = `origin/hermes/dns-implementation-20260913` |
| Assignment | `fuzz-engineer/g9-full-campaign-execution-003` |
| Requested leaf model / effort | `openai-codex/gpt-5.6-terra` / `medium`; runtime telemetry must be recorded as unknown if unavailable. |

This routing stage follows G8 approval and the completed focused name-harness validation at `g9-resumption-010`; it does not treat either as G9 acceptance. The current toolchain exposes LLVM/Clang 19.1.7, CMake 3.31.6, Ninja, and the repository-defined three sanitizer targets. The assigned leaf must create a deterministic derived corpus only under a new `/tmp/ratatoskr-g9-full-campaign-execution-003*` path and run all three targets serially with the preserved `-rss_limit_mb=1024` budget. It must stop after the first sanitizer/crash/timeout/RSS failure, preserve evidence, make no source/CMake/canonical-vector change, and return a blocker handoff rather than fixing or self-reviewing. G9 remains `BLOCKED` pending verified leaf receipt and later independent G9 security review.