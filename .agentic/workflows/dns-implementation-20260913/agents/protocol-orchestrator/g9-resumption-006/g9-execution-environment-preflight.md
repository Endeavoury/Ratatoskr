# G9 execution-environment resumption preflight

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resumption-006-preflight` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target / owner | `protocol/dns` / `protocol-orchestrator/g9-resumption-006` |
| Status | `BLOCKED` |
| Baseline observed | local `git:a6cac040bd4de2d07ba0c14199778e0fee525ea0` |
| Remote observed before artifact write | `refs/heads/hermes/dns-implementation-20260913` at `a6cac040bd4de2d07ba0c14199778e0fee525ea0` |
| Checked at | `2026-09-26T22:26:07+02:00` |
| Source artifacts | Workflow state; approved G7/G8 records; existing G9 plan and blocked results; resumption-005 blocker |
| Assumptions | Pre-existing untracked paths are unrelated and remain untouched. |
| Limitations | Required fuzz toolchain is absent, so no configure, build, or campaign command was attempted. |

## Scope and decision

ACTIVE ROLE: `protocol-orchestrator`.

This bounded resumption independently checked the current host capability required by the approved G9 campaign. The workflow state remains `BLOCKED` at `fuzzing`; G7 and G8 are recorded `APPROVED`. The existing G9 evidence was read only as the approved campaign definition and is not live work.

No fuzz-engineer was dispatched. The prerequisite set is not fully verified because CMake, Clang, Clang++, and llvm-config are unavailable in `PATH`; consequently matching compiler-rt libFuzzer/ASan/UBSan support and a build of all three targets cannot be demonstrated.

## Current probes

All commands ran from `/home/hermes/hermes-workspace/projects/Ratatoskr`.

```text
$ command -v cmake; cmake --version
cmake: absent
/usr/bin/bash: cmake: command not found

$ command -v clang; clang --version
clang: absent
/usr/bin/bash: clang: command not found

$ command -v clang++; clang++ --version
clang++: absent
/usr/bin/bash: clang++: command not found

$ command -v llvm-config; llvm-config --version
llvm-config: absent
/usr/bin/bash: llvm-config: command not found

$ git grep -n 'ratos_fuzz_dns_\|RATOS_BUILD_FUZZERS' -- CMakeLists.txt fuzz
CMakeLists.txt:20:if(RATOS_BUILD_FUZZERS)
fuzz/CMakeLists.txt:2:    add_executable(ratos_fuzz_dns_${fuzzer} dns/fuzz_dns_${fuzzer}.c)
fuzz/CMakeLists.txt:7:    target_compile_options(ratos_fuzz_dns_${fuzzer} PRIVATE -fsanitize=fuzzer,address,undefined)
fuzz/CMakeLists.txt:8:    target_link_options(ratos_fuzz_dns_${fuzzer} PRIVATE -fsanitize=fuzzer,address,undefined)

$ clang -print-file-name=libclang_rt.fuzzer-x86_64.a
(no output; clang unavailable)
$ clang -print-file-name=libclang_rt.asan-x86_64.a
(no output; clang unavailable)
$ clang -print-file-name=libclang_rt.ubsan_standalone-x86_64.a
(no output; clang unavailable)
```

The repository tracks all required existing target sources: `fuzz/dns/fuzz_dns_packet.c`, `fuzz/dns/fuzz_dns_name.c`, and `fuzz/dns/fuzz_dns_record.c`. Their registration cannot be configured or built without the missing CMake/Clang toolchain. The required capability `-fsanitize=fuzzer,address,undefined` is therefore unverified and unavailable on this host.

## Required next input

Provide an authorized execution host/image with CMake, `clang`, `clang++`, and matching compiler-rt support for libFuzzer, ASan, and UBSan. Independently verify that it configures and builds `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` with `-fsanitize=fuzzer,address,undefined` before dispatching exactly one fresh fuzz-engineer.

## State and boundary result

No shared workflow-state change is warranted. No fuzz-engineer or security-reviewer was routed. No production code, headers, tests, fuzz sources, docs, configurations, manifest, request, or other role workspace was modified.
