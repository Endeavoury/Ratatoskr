# G9 current toolchain preflight

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resumption-006-current-toolchain-preflight` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target / owner | `protocol/dns` / `protocol-orchestrator/g9-resumption-006` |
| Status | `COMPLETE` — administrative preflight only; G9 itself is not approved |
| Checked at | `2026-09-27T01:47:54+02:00` |
| Baseline | Local HEAD and origin target `git:2e0eb1d4fa2e554c7fb62d7612b731e9d89935c5` |
| Source artifacts | Current workflow state; delivered G9 fuzz evidence; G9 blocker-routing verification; historical resumption records |
| Assumptions | Pre-existing untracked artifacts are unrelated and remain untouched. |
| Open questions | None for toolchain availability; a fresh fuzz-engineer still needs an authorized execution assignment. |
| Limitations | This preflight builds existing harness targets only; it does not execute a fuzz campaign or establish G9 evidence. |

## Scope

ACTIVE ROLE: `protocol-orchestrator`.

This is one administrative resumption stage. Historical `IN_PROGRESS`, `CHANGES_REQUESTED`, and `BLOCKED` artifacts were treated as completed history, not active assignments. No package installation, production/test/fuzz-source change, fuzzer execution, or specialist delegation was performed.

## Repository and toolchain verification

The repository root is `/home/hermes/hermes-workspace/projects/Ratatoskr`, on branch `hermes/dns-implementation-20260913`. Immediately before the check, both local HEAD and `origin/hermes/dns-implementation-20260913` resolved to `git:2e0eb1d4fa2e554c7fb62d7612b731e9d89935c5`.

`/usr/bin/clang-19` and `/usr/bin/clang++-19` report Debian Clang 19.1.7. The C compiler resolved each matching runtime and verified it as a regular file:

- `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.fuzzer-x86_64.a`
- `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.asan-x86_64.a`
- `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.ubsan_standalone-x86_64.a`

## Actual configure/build commands and results

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`; the disposable build directory was `/tmp/ratatoskr-g9-toolchain-preflight-20260927`.

```text
$ /usr/bin/clang-19 --version | head -n 3
Debian clang version 19.1.7 (3+b1)
Target: x86_64-pc-linux-gnu
Thread model: posix

$ /usr/bin/clang++-19 --version | head -n 3
Debian clang version 19.1.7 (3+b1)
Target: x86_64-pc-linux-gnu
Thread model: posix

$ /usr/bin/clang-19 -print-file-name=libclang_rt.fuzzer-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.fuzzer-x86_64.a
$ /usr/bin/clang-19 -print-file-name=libclang_rt.asan-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.asan-x86_64.a
$ /usr/bin/clang-19 -print-file-name=libclang_rt.ubsan_standalone-x86_64.a
/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.ubsan_standalone-x86_64.a

$ cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr \
    -B /tmp/ratatoskr-g9-toolchain-preflight-20260927 -G Ninja \
    -DCMAKE_C_COMPILER=/usr/bin/clang-19 \
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 \
    -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
-- The C compiler identification is Clang 19.1.7
-- Configuring done
-- Generating done
-- Build files have been written to: /tmp/ratatoskr-g9-toolchain-preflight-20260927

$ cmake --build /tmp/ratatoskr-g9-toolchain-preflight-20260927 \
    --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
[15/17] Linking C executable fuzz/ratos_fuzz_dns_packet
[16/17] Linking C executable fuzz/ratos_fuzz_dns_name
[17/17] Linking C executable fuzz/ratos_fuzz_dns_record
```

All three target files were verified executable:

- `/tmp/ratatoskr-g9-toolchain-preflight-20260927/fuzz/ratos_fuzz_dns_packet`
- `/tmp/ratatoskr-g9-toolchain-preflight-20260927/fuzz/ratos_fuzz_dns_name`
- `/tmp/ratatoskr-g9-toolchain-preflight-20260927/fuzz/ratos_fuzz_dns_record`

## Decision

The former conclusion was false: unversioned `clang` is absent from `PATH`, but the installed versioned LLVM 19 toolchain is usable when explicitly passed to CMake and has the required matching compiler-rt libraries. The existing configured targets build successfully with their repository-defined `-fsanitize=fuzzer,address,undefined` options.

The toolchain blocker is cleared. This is not G9 approval: no fresh fuzz plan/results, campaign budget, corpus provenance, crash disposition, or independent G9 security review exists. The next permitted action is one correctly scoped fresh fuzz-engineer dispatch by the protocol-orchestrator.

## Next-dispatch safety envelope

Any future G9 fuzz-engineer packet must remain within OpenAI safety rules and explicitly limit execution to the authorized local Ratatoskr repository. It may build and run only the three existing DNS parser quality-test targets (`ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`) against a fixed local seed corpus already in the repository. It must use no network access, remote targets, credential access, payload development, scanning, persistence, or exploitation; set bounded runtime, memory, and disk limits; and collect only build/run logs and sanitizer diagnostics. The assignee must stop and hand off on any crash or policy ambiguity. No campaign was run by this preflight.
