# G9 execution-environment resumption preflight

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resumption-006-preflight` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target / owner | `protocol/dns` / `protocol-orchestrator/g9-resumption-006` |
| Status | `COMPLETE` — administrative preflight only; G9 remains unapproved |
| Baseline observed | local and remote `git:2e0eb1d4fa2e554c7fb62d7612b731e9d89935c5` |
| Remote observed before artifact write | `refs/heads/hermes/dns-implementation-20260913` at `2e0eb1d4fa2e554c7fb62d7612b731e9d89935c5` |
| Checked at | `2026-09-27T01:47:54+02:00` |
| Source artifacts | Workflow state; approved G7/G8 records; existing G9 plan and blocked results; resumption-005 blocker |
| Assumptions | Pre-existing untracked paths are unrelated and remain untouched. |
| Limitations | No fuzz campaign was run; successful target builds establish only the execution prerequisite. |

## Scope and decision

ACTIVE ROLE: `protocol-orchestrator`.

This bounded resumption independently checked the current host capability required by the approved G9 campaign. Historical G9 evidence remains read-only history; G7 and G8 remain recorded `APPROVED`. No fuzz-engineer was dispatched and no security reviewer was routed.

The required compiler/runtime capability is present when the installed versioned executables are selected explicitly. CMake 3.31.6 generated a Ninja build with `/usr/bin/clang-19` and `/usr/bin/clang++-19`; Ninja 1.12.1 then built all three existing DNS fuzz targets. The project CMake registration supplies `-fsanitize=fuzzer,address,undefined`, so the successful links exercise matching libFuzzer, ASan, and UBSan compiler-rt availability.

## Current probes and build evidence

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`; build output is disposable at `/tmp/ratatoskr-g9-toolchain-preflight-20260927`.

```text
$ /usr/bin/clang-19 --version
Debian clang version 19.1.7 (3+b1)

$ /usr/bin/clang++-19 --version
Debian clang version 19.1.7 (3+b1)

$ /usr/bin/clang-19 -print-file-name=libclang_rt.fuzzer-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.fuzzer-x86_64.a
$ /usr/bin/clang-19 -print-file-name=libclang_rt.asan-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.asan-x86_64.a
$ /usr/bin/clang-19 -print-file-name=libclang_rt.ubsan_standalone-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.ubsan_standalone-x86_64.a

$ cmake -S . -B /tmp/ratatoskr-g9-toolchain-preflight-20260927 -G Ninja \
    -DCMAKE_C_COMPILER=/usr/bin/clang-19 \
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 \
    -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
-- The C compiler identification is Clang 19.1.7
-- Configuring done
-- Generating done

$ cmake --build /tmp/ratatoskr-g9-toolchain-preflight-20260927 \
    --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
[15/17] Linking C executable fuzz/ratos_fuzz_dns_packet
[16/17] Linking C executable fuzz/ratos_fuzz_dns_name
[17/17] Linking C executable fuzz/ratos_fuzz_dns_record
```

The resulting executable targets are `fuzz/ratos_fuzz_dns_packet`, `fuzz/ratos_fuzz_dns_name`, and `fuzz/ratos_fuzz_dns_record` under that build directory.

## Required next input

No environment-maintainer action is required. The protocol-orchestrator may create exactly one fresh, correctly scoped fuzz-engineer execution packet against the recorded approved inputs. That packet must define campaign budget, corpus/provenance, expected outputs, and an independent G9 security-review handoff after actual fuzz results exist. This preflight does not itself authorize G9 approval or a security-review route.

## Next-dispatch safety envelope

A future G9 specialist must operate within OpenAI safety rules: only the authorized local Ratatoskr repository is in scope; it may build and run only `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` with a fixed local seed corpus already tracked by the repository. No network access, remote targets, credential access, payload development, scanning, persistence, or exploitation is allowed. The packet must impose bounded runtime, memory, and disk consumption; retain only build/run logs and sanitizer diagnostics; and require an immediate stop-and-handoff for any crash or policy ambiguity. No campaign was run in this preflight.

## State and boundary result

`DNS-G9-FUZZ-TOOLCHAIN-001` is resolved because the prior unavailable-toolchain claim was caused by checking only unversioned `clang` on `PATH`. The workflow is ready to resume at fuzzing, but G9 remains `NOT_STARTED` pending fresh fuzz evidence. No production code, headers, tests, fuzz source/CMake, bindings, documentation, manifest, request, or other role workspace was modified.
