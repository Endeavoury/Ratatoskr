# Fuzz plan — G9 full DNS campaign execution 006

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-006-fuzz-plan` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role / status | `fuzz-engineer` / `BLOCKED` |
| Revision | `git:87c2b7a36fdedca2370113093e53633850268a9a`; this is an uncommitted assigned workspace artifact |
| Inputs | Delegation `g9-resumption-008/delegations/fuzz-engineer-g9-full-campaign-execution-006.md`; preflight `g9-resumption-008/verification/g9-current-toolchain-preflight-008.md`; G7 and G8 records named below |
| Assumptions | Local Linux execution only; no network or external target; G9 acceptance remains an independent security-reviewer responsibility. |
| Limitations | Fixed 90-second per-target fuzz budgets sample behavior only and do not establish conformance or absence of vulnerabilities. |

## Verified prerequisites

Repository root was `/home/hermes/hermes-workspace/projects/Ratatoskr`; branch `hermes/dns-implementation-20260913`; local `HEAD` and `origin/hermes/dns-implementation-20260913` both resolved to `87c2b7a36fdedca2370113093e53633850268a9a`. No live packet/name/record campaign process and no pre-existing `/tmp/ratatoskr-g9-full-campaign-execution-006` directory existed before execution. Existing unrelated working-tree modifications and untracked paths were observed and preserved.

Workflow state recorded G7 `APPROVED` at `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` and G8 `APPROVED` at `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`, both for candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`. G9 was `IN_PROGRESS` and unapproved; no G9 review was assigned.

Observed tools: `/usr/bin/clang-19` and `/usr/bin/clang++-19` Debian 19.1.7; `/usr/bin/cmake` 3.31.6; Ninja 1.12.1; GNU timeout 9.7. LLVM19 matching runtime archives were present at `/usr/lib/llvm-19/lib/clang/19/lib/linux/`: `libclang_rt.fuzzer-x86_64.a`, `libclang_rt.asan-x86_64.a`, and `libclang_rt.ubsan_standalone-x86_64.a`.

## Input integrity and corpus provenance

| Input | SHA-256 |
| --- | --- |
| `fuzz/dns/corpus/seeds.txt` | `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07` |
| `fuzz/dns/corpus/README.md` | `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551` |
| `fuzz/dns/fuzz_dns_packet.c` | `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263` |
| `fuzz/dns/fuzz_dns_name.c` | `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f` |
| `fuzz/dns/fuzz_dns_record.c` | `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c` |
| `fuzz/CMakeLists.txt` | `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5` |

The local converter parsed each nonempty line at its first colon, trimmed presentation whitespace after the separator, accepted only `zero-length:` as empty bytes and the documented `maximum-size:` directive as 65,535 zero bytes, and hex-decoded every other value. It rejected malformed labels/directives/hex. Ten files totaling 65,887 bytes were derived, and each target received a fresh copied corpus. Each corpus had combined SHA-256 `d7ad8905a24eb825806ae1003707e4388544551e0c5b2856fe354c39c8e51f42`.

## Target strategy and invariants

| Target | Existing entrypoint / strategy | Exercised hostile cases | Required invariant |
| --- | --- | --- | --- |
| `ratos_fuzz_dns_packet` | `ratos_dns_parse_response` over arbitrary packet bytes; expected ID from input bytes 0–1 | Valid records, truncation, pointer loops, invalid RDLENGTH, zero and maximum-size inputs, mutations | No sanitizer diagnostic, crash, target timeout, RSS failure, or nonzero exit. |
| `ratos_fuzz_dns_name` | DNS response with mutated question-name region | Malformed labels/compression-like values, zero and maximum-size inputs, mutations | Same no-failure invariant. |
| `ratos_fuzz_dns_record` | DNS response with mutated RR type/class/TTL/RDLENGTH/payload region | Record-length and payload stress, valid/malformed seeds, zero and maximum-size inputs, mutations | Same no-failure invariant, including required RSS bound. |

## Executed build and campaign commands

```text
/usr/bin/cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-006/build -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
/usr/bin/cmake --build /tmp/ratatoskr-g9-full-campaign-execution-006/build --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
/usr/bin/timeout 120s /tmp/ratatoskr-g9-full-campaign-execution-006/build/fuzz/ratos_fuzz_dns_packet /tmp/ratatoskr-g9-full-campaign-execution-006/corpus-packet -max_total_time=90 -rss_limit_mb=1024 -timeout=10
/usr/bin/timeout 120s /tmp/ratatoskr-g9-full-campaign-execution-006/build/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-full-campaign-execution-006/corpus-name -max_total_time=90 -rss_limit_mb=1024 -timeout=10
/usr/bin/timeout 120s /tmp/ratatoskr-g9-full-campaign-execution-006/build/fuzz/ratos_fuzz_dns_record /tmp/ratatoskr-g9-full-campaign-execution-006/corpus-record -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

Targets ran serially in packet/name/record order. The record result failed the required resource predicate; no rerun, changed limit, source repair, or security review is authorized.