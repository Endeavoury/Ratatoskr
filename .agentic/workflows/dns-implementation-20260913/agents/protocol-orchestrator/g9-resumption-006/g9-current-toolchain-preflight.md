# G9 current toolchain preflight

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resumption-006-current-toolchain-preflight` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target / owner | `protocol/dns` / `protocol-orchestrator/g9-resumption-006` |
| Status | `BLOCKED` |
| Checked at | `2026-09-27T01:44:38+02:00` |
| Baseline | Local HEAD and origin target `git:f32bb2d32cf6ea29be8daaa6084bbf88d17d2fca` |
| Source artifacts | Current workflow state; delivered G9 fuzz evidence; G9 blocker-routing verification; historical resumption records |
| Assumptions | Pre-existing untracked artifacts are unrelated and remain untouched. |
| Open questions | Environment maintainer must provide Clang/compiler-rt execution capability. |
| Limitations | No configured/buildable libFuzzer target or campaign exists on this host. |

## Scope

ACTIVE ROLE: `protocol-orchestrator`.

This is one administrative resumption stage. Historical `IN_PROGRESS`, `CHANGES_REQUESTED`, and `BLOCKED` artifacts were treated as completed history, not active assignments. No package installation, configuration, build, fuzzer execution, or specialist delegation was attempted.

## Repository and wrapper verification

The verified absolute wrapper is `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`, mode `-rwx------`, owner/group `hermes:hermes`. Wrapper-mediated read-only probes reported repository root `/home/hermes/hermes-workspace/projects/Ratatoskr`, branch `hermes/dns-implementation-20260913`, local HEAD `f32bb2d32cf6ea29be8daaa6084bbf88d17d2fca`, origin `https://github.com/Endeavoury/Ratatoskr.git`, and target remote ref `f32bb2d32cf6ea29be8daaa6084bbf88d17d2fca`.

## Actual preflight commands and results

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`:

```text
$ cmake --version | head -n 1
cmake version 3.31.6

$ ctest --version | head -n 1
ctest version 3.31.6

$ ninja --version
1.12.1

$ command -v clang
(no output; exit status indicated absent)

$ clang --version | head -n 1
/usr/bin/bash: line 23: clang: command not found

$ command -v clang-16; command -v clang-17; command -v clang-18
(no output; all absent)

$ command -v llvm-profdata; command -v llvm-cov
(no output; both absent)

$ clang -print-file-name=libclang_rt.fuzzer-x86_64.a
/usr/bin/bash: line 27: clang: command not found

$ clang -print-file-name=libclang_rt.asan-x86_64.a
/usr/bin/bash: line 28: clang: command not found

$ clang -print-file-name=libclang_rt.ubsan_standalone-x86_64.a
/usr/bin/bash: line 29: clang: command not found
```

## Decision

The required environment is incomplete. CMake/CTest and Ninja are now present, which materially changes the historical blocker evidence, but no `clang` executable or matching compiler-rt libFuzzer/ASan/UBSan runtime is available. The existing G9 plan requires Clang targets built with `-fsanitize=fuzzer,address,undefined`; GCC is not substituted. No fresh fuzz-engineer packet or leaf was created, and no G9 security reviewer was routed.

## Required next input

The environment maintainer must make Clang/Clang++ and matching compiler-rt libFuzzer, ASan, and UBSan available in `PATH` on an authorized Linux execution environment. A later protocol-orchestrator resumption must re-check the complete environment, create exactly one fresh fuzz-engineer execution packet only if complete, and route a fresh independent G9 security review only after executed fuzz evidence exists.
