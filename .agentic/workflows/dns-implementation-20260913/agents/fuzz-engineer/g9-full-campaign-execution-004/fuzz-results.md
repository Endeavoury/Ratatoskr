# G9 DNS full fuzz campaign results — execution 004

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-004-results` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner | `fuzz-engineer/g9-full-campaign-execution-004` |
| Status | `BLOCKED` |
| Revision tested | `git:b82ea8499600c3ef7ab1e51fa297b477b1f17c1c` |
| Build / corpus / logs | `/tmp/ratatoskr-g9-full-campaign-execution-004/build`; `/tmp/ratatoskr-g9-full-campaign-execution-004/corpus-fixed`; `/tmp/ratatoskr-g9-full-campaign-execution-004/{packet,name,record}-run.json` |

## Build

The exact LLVM19 CMake configure command and exact three-target build command in `fuzz-plan.md` completed with exit 0. CMake identified Clang 19.1.7 and Ninja linked `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` with repository-defined `-fsanitize=fuzzer,address,undefined` options.

## Serial target results

Each target received a fresh copy of the 10-file fixed corpus. `ru_maxrss` is Linux KiB and is cumulative maximum child RSS, so the name and record before/after readings may retain the preceding child maximum. Full captured output is retained only under `/tmp`.

| Target | Return | Monotonic elapsed seconds | ru_maxrss before / after / delta KiB | Sanitizer/crash | Resource/timeout | Disposition |
| --- | ---: | ---: | --- | --- | --- | --- |
| `ratos_fuzz_dns_packet` | 0 | 91.1975008812733 | 0 / 499624 / 499624 | none | none | clean |
| `ratos_fuzz_dns_name` | 0 | 91.17736798198894 | 499624 / 499624 / 0 | none | none | clean |
| `ratos_fuzz_dns_record` | 71 | 10.101190892979503 | 499624 / 1071852 / 572228 | none | libFuzzer out-of-memory | **BLOCKED** |

The record log contains `ERROR: libFuzzer: out-of-memory` and `SUMMARY: libFuzzer: out-of-memory` under the mandatory `-rss_limit_mb=1024` budget. No ASan, UBSan, crash, or external timeout diagnostic was observed before the mandated resource stop. The record target was the third and final assigned target; no extra target or retry was launched.

## Disposition

This single bounded campaign is blocked by the record target's nonzero resource failure. It is not G9 approval and does not justify a G9 security-review dispatch. No code diagnosis or repair was performed.
