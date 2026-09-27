# G9 DNS name-harness bounds remediation results 002

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-bounds-remediation-002-results` |
| Workflow / stage | `dns-implementation-20260913` / G9 corrective name-harness validation |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-bounds-remediation-002` |
| Status | `READY_FOR_REVIEW` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch / pre-validation local / fetched remote | `git:d489d749a37548e1e711d11c10b53b2041281bbf` / same / same |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / `openai-codex/gpt-5.6-terra`, effort telemetry unavailable |

## Preconditions

The following all succeeded before artifact writes: repository root was `/home/hermes/hermes-workspace/projects/Ratatoskr`; origin was `https://github.com/Endeavoury/Ratatoskr.git`; branch was `hermes/dns-implementation-20260913`; `HEAD` and `refs/remotes/origin/hermes/dns-implementation-20260913` were both `d489d749a37548e1e711d11c10b53b2041281bbf`; and the dispatch baseline was an ancestor of both. Existing unrelated untracked paths were observed and preserved.

The historical correction commit `2c9e9b945352642d27cf703132e8e5e525b8b5cb` is an ancestor of live `HEAD`. Live `fuzz/dns/fuzz_dns_name.c` has the safe `sizeof(packet) - 17u` cap, so this is a no-op source remediation.

## Bounds reasoning

`packet` is `uint8_t packet[1024]`. The five terminal writes use offsets `12 + copied` through `16 + copied`. With `copied <= 1024 - 17 = 1007`, the maximum offset is `16 + 1007 = 1023`, in bounds. The parse length `copied + 17` is at most 1024.

## Focused sanitizer configure/build

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`.

```text
/usr/bin/clang-19 --version
/usr/bin/clang++-19 --version
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-name-harness-bounds-remediation-002 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-name-harness-bounds-remediation-002 --target ratos_fuzz_dns_name --parallel 2
```

`/usr/bin/clang-19` and `/usr/bin/clang++-19` reported Debian Clang 19.1.7; CMake was 3.31.6 and Ninja 1.12.1. Configure exited 0. The 13-step build exited 0 and linked `/tmp/ratatoskr-g9-name-harness-bounds-remediation-002/fuzz/ratos_fuzz_dns_name`. The existing target's sanitizer configuration is the repository fuzz configuration (`fuzzer,address,undefined`).

## Isolated reproducer replay

Created only `/tmp/ratatoskr-g9-name-harness-bounds-remediation-002/corpus/reproducer-1133.bin`: 1,133 zero bytes, SHA-256 `c80420c3c5d20d1ce9447e14c185c5a2840ca200790f9b1532f556f5edcefe7b`.

```text
timeout 30s /tmp/ratatoskr-g9-name-harness-bounds-remediation-002/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-name-harness-bounds-remediation-002/corpus -runs=1 -timeout=10 -rss_limit_mb=1024
```

Replay exited 0. libFuzzer found one 1,133-byte corpus input and completed two runs in zero seconds (`DONE`, RSS 33 MB). Output contained no ASan, UBSan, crash, timeout, or RSS-limit diagnostic.

## Delivery evidence

Initial leaf delivery commit: `a5703fccd511c42267b223c4e0b43fe40318a20d`. Exact remote readback after its push: `refs/heads/hermes/dns-implementation-20260913 = a5703fccd511c42267b223c4e0b43fe40318a20d`. `git diff-tree --name-only` for that commit listed exactly the four assigned leaf artifacts: this file, `fuzz-plan.md`, the named handoff, and `completion-report.md`; it listed no source path. `git diff --check` for that delivery exited 0.

## Scope and limitations

No repository source changed; packet and record targets were not built or run. No fuzz campaign, focused review, security review, or later stage was run. This is focused no-op remediation validation only and is not G9 approval.
