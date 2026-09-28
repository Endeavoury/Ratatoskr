# G9 DNS fuzz execution plan

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-002-plan` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target | `protocol/dns` |
| Owner role | `fuzz-engineer/g9-fuzz-execution-002` |
| Status | `BLOCKED` — corpus-preparation prerequisite failed before configure/build/campaign; no retry authorized |
| Revision | Dispatch baseline `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3`; local execution HEAD to be recorded in results |
| Source artifacts | Delegation; approved G8 review `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`; LLVM 19 preflight `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`; tracked seed descriptions `fuzz/dns/corpus/{README.md,seeds.txt}` |
| Assumptions | G7/G8 approvals remain valid; the fixed tracked sources are unchanged from dispatch; pre-existing untracked files are unrelated and untouched. |
| Open questions | None. |
| Limitations | Local, fixed-seed, 90-second-per-target libFuzzer campaign only; no network, corpus evolution retention, coverage threshold, or conformance claim. |

## Scope and target mapping

Only the existing targets below will be configured, built, and run sequentially. No harness, CMake, corpus, production, header, test, vector, workflow-state, or documentation file will be changed.

| Target | Reachable entrypoint / adversarial surface | Invariants exercised |
| --- | --- | --- |
| `ratos_fuzz_dns_packet` | `ratos_dns_parse_response` over arbitrary DNS response bytes, with the input’s first two bytes used as the response ID | No sanitizer-detected memory/undefined-behavior failure; malformed/truncated packet handling returns or destroys safely. |
| `ratos_fuzz_dns_name` | `ratos_dns_parse_response` over a fixed DNS header plus mutated name bytes | No sanitizer-detected failure across labels, compression-like bytes, truncation, and bounded copied input. |
| `ratos_fuzz_dns_record` | `ratos_dns_parse_response` over a fixed question plus a synthesized mutated answer record | No sanitizer-detected failure across record type/class/count/RDLENGTH/payload combinations and bounded copies. |

## Build and campaign envelope

Execution working directory is `/home/hermes/hermes-workspace/projects/Ratatoskr`; the disposable build directory is `/tmp/ratatoskr-g9-fuzz-execution-002`. CMake will use `/usr/bin/clang-19` and `/usr/bin/clang++-19`, `RATOS_BUILD_FUZZERS=ON`, `RATOS_BUILD_TESTS=OFF`, and the repository-defined libFuzzer AddressSanitizer/UBSan target settings. Build only the three listed targets with `--parallel 2`.

The ephemeral corpus directory will be decoded solely from tracked `fuzz/dns/corpus/seeds.txt`: the explicit zero-length seed, a 65,535-byte all-zero maximum-size seed, and the seven labelled hexadecimal descriptions. The results record the exact decoder command and SHA-256 digest of both source files.

Each target receives that same corpus and exactly `-max_total_time=90 -rss_limit_mb=1024 -timeout=10`, under a 120-second OS wall-clock `timeout` guard. Targets run one at a time. The campaign stops immediately on configure/build/prerequisite failure, timeout/fuzzer nonzero result, or sanitizer diagnostic; no retry or native fix is allowed. A clean run requires all three targets to exit zero without an AddressSanitizer, UndefinedBehaviorSanitizer, libFuzzer crash, or timeout diagnostic. Results will retain command output tails and elapsed dispositions in the owned result artifact only.
