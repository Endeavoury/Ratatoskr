# G9 DNS full fuzz campaign results

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-002-results` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner | `fuzz-engineer/g9-full-campaign-execution-002` |
| Status | `BLOCKED` |
| Revision tested | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Build / corpus | `/tmp/ratatoskr-g9-full-campaign-execution-002` / `/tmp/ratatoskr-g9-full-campaign-execution-002-corpus` |

## Build

The exact LLVM19 configure and three-target build commands in `fuzz-plan.md` completed exit 0. CMake reported Clang 19.1.7 and linked only `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` with repository-defined fuzzer, address, and undefined-behavior sanitizers.

## Per-target execution

All wrapper commands used `/usr/bin/timeout 120s <target> <corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10`; `ru_maxrss` units are KiB on Linux. Complete wrapper stdout/stderr is retained in the named ephemeral JSON files.

| Target | Return | Monotonic elapsed seconds | ru_maxrss before / after / delta | Sanitizer/crash | Resource | Disposition |
| --- | ---: | ---: | --- | --- | --- | --- |
| `ratos_fuzz_dns_packet` | 0 | 91.12561804009601 | 0 / 360620 / 360620 | none | none | clean |
| `ratos_fuzz_dns_name` | 0 | 91.17745899502188 | 0 / 454032 / 454032 | none | none | clean |
| `ratos_fuzz_dns_record` | 71 | 21.236172719858587 | 0 / 1675884 / 1675884 | none | libFuzzer RSS-limit failure | **BLOCKED** |

The packet and name runs completed their bounded campaign durations, returned zero, and wrapper scans found no sanitizer, crash, timeout, or resource marker. The record run stopped at the mandated first resource issue. Its complete captured stderr ends:

```text
==258527== ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)
   To change the out-of-memory limit use -rss_limit_mb=<N>
...
artifact_prefix='./'; Test unit written to ./oom-f1545b193bff32ed14265f7211065e43346a6de0
SUMMARY: libFuzzer: out-of-memory
```

The generated root artifact had SHA-256 `23b56d8f1807e20c6a37be929283eaf0ed81d38cd5c7e9609d49b05840996a38` and was removed immediately so the only repository outputs are this assignment's four authorized files; logs and captured wrapper JSON remain under `/tmp`.

## Disposition

This is one fresh campaign only. `ratos_fuzz_dns_record` exceeded the preserved `-rss_limit_mb=1024` budget; its nonzero exit and explicit out-of-memory diagnostic block G9 evidence. No retry, altered flag, additional run, security-review dispatch, or further target was performed after the failure. No crash, ASan, UBSan, or timeout was observed before the required resource stop.