# G9 resumption 011 preflight verification

ACTIVE ROLE: `protocol-orchestrator`.

- Verified Git root `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `hermes/dns-implementation-20260913`, local HEAD and `origin/hermes/dns-implementation-20260913` both `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4`.
- `git status --porcelain=v1` shows only pre-existing unrelated untracked `.agentic` paths before this workspace; they are preserved and excluded from staging.
- Runtime `delegate_task` list reports zero live children. Process inspection found no live `fuzz_dns_*`, Clang, CMake, Ninja, Make, or specialist campaign execution; persistent Hermes gateway/dashboard/kernel processes are not specialist executions.
- State is `workflow/fuzzing/G9 = BLOCKED`, while G7 and G8 are `APPROVED`. The latest completed `g9-resumption-010` only verified focused name-harness replay; it explicitly left the complete three-target campaign and G9 security review absent.
- Historical full campaign `g9-full-campaign-execution-002` is blocked by the record target’s mandatory 1024 MiB RSS-limit failure; its results are historical evidence only. Historical `execution-005` name stack overflow is superseded for routing purposes by resumption-010’s safe-cap replay; it is not current campaign evidence.
- Current prerequisites exist: `fuzz/dns/corpus/seeds.txt`, `fuzz/dns/corpus/README.md`, `fuzz/dns/fuzz_dns_packet.c`, `fuzz/dns/fuzz_dns_name.c`, and `fuzz/dns/fuzz_dns_record.c`; no `fuzz/dns/seeds/` directory exists. `/usr/bin/clang-19` reports Debian Clang 19.1.7, and CMake reports 3.31.6. `g9-resumption-006` records matching compiler-rt fuzzer/ASan/UBSan libraries and a successful three-target LLVM19 build.
- Nested delegation is authorized by the assigned configuration (`orchestrator_enabled=true`, `max_spawn_depth=2`). The only permitted commit/push wrapper is `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-orchestrator`; no merge, force push, or master update is authorized.

Decision: route exactly one fresh fuzz-engineer leaf for a complete bounded serial campaign. No G9 security review, bindings, or later stage is routed. Shared workflow state will not be changed until verified leaf receipt.