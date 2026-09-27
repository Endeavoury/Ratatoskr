# Focused fuzz plan — name-harness bounds remediation 003

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-bounds-remediation-003-plan` |
| Workflow / stage | `dns-implementation-20260913` / G9 corrective harness evidence only |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-bounds-remediation-003` |
| Status | `READY_FOR_REVIEW` |
| Revision | baseline `2c6b0bc742d3db88cc94b9e6e354b362ee0f6055` |
| Source artifacts | Delegation packet; `g9-fuzz-execution-005/fuzz-results.md`; live `fuzz/dns/fuzz_dns_name.c` |
| Assumptions | `/usr/bin/clang-19` and `/usr/bin/clang++-19` are available. |
| Open questions | None for the bounded validation. |
| Limitations | Excludes packet/record targets and every fuzz campaign. |

## Scope

Inspect the live copied-byte cap. If it is not `sizeof(packet) - 17u`, make only that minimal harness correction. Otherwise preserve the source and validate the no-op state by building only `ratos_fuzz_dns_name` with LLVM19 sanitizers and replaying one isolated 1,133-byte input from `/tmp/ratatoskr-g9-name-harness-bounds-remediation-003`.

## Invariant and boundary reasoning

`packet` has 1,024 indices (`0..1023`). Terminal writes occur at `12 + copied` through `16 + copied`. The live cap makes `copied <= 1024 - 17 = 1007`; therefore the highest terminal write is `16 + 1007 = 1023`, and the parser length is at most `1007 + 17 = 1024`. The historic 1,133-byte input must not cause ASan/UBSan diagnostics.

## Exact validation commands

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-name-harness-bounds-remediation-003 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-name-harness-bounds-remediation-003 --target ratos_fuzz_dns_name --parallel 2
timeout 30s /tmp/ratatoskr-g9-name-harness-bounds-remediation-003/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-name-harness-bounds-remediation-003/corpus -runs=1 -timeout=10 -rss_limit_mb=1024
```
