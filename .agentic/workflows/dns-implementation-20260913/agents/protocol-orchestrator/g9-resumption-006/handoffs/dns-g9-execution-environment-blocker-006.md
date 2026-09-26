# G9 execution-environment blocker handoff

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `DNS-G9-EXECUTION-ENVIRONMENT-006` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator/g9-resumption-006` |
| Status | `BLOCKED` |
| Revision | baseline `git:a6cac040bd4de2d07ba0c14199778e0fee525ea0`; delivery commit pending |
| Source artifacts | `g9-execution-environment-preflight.md`; workflow state; existing approved G9 campaign plan |
| Assumptions | None. |
| Open questions | Which authorized host/image can provide the required toolchain? Owner: workspace-orchestrator / maintainer. |
| Limitations | This host has no CMake, Clang, Clang++, or llvm-config in `PATH`. |

## Routing

- ID / workflow / stage: `DNS-G9-EXECUTION-ENVIRONMENT-006` / `dns-implementation-20260913` / G9 fuzzing.
- Source role and assignment: `protocol-orchestrator/g9-resumption-006`.
- Destination role: `workspace-orchestrator` / maintainer.
- Target protocol/binding/component: `protocol/dns`.
- Reason: the applicable G9 campaign needs a CMake + Clang compiler-rt libFuzzer/ASan/UBSan environment; current independent probes do not satisfy it.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-006/g9-execution-environment-preflight.md` at baseline `git:a6cac040bd4de2d07ba0c14199778e0fee525ea0`.
- `fuzz/CMakeLists.txt` at that baseline declares `ratos_fuzz_dns_${fuzzer}` using `-fsanitize=fuzzer,address,undefined`.
- Existing sources are `fuzz/dns/fuzz_dns_packet.c`, `fuzz/dns/fuzz_dns_name.c`, and `fuzz/dns/fuzz_dns_record.c`.

## Specific problem or question

CMake, `clang`, `clang++`, and `llvm-config` are absent from `PATH`. The selected compiler cannot be used to locate matching compiler-rt libFuzzer, ASan, or UBSan runtimes; therefore the required fuzz build and three-target verification cannot be performed.

## Requested action

Provision or authorize an execution-capable Linux host/image. Return host/image identity and current probe evidence showing CMake, Clang/Clang++, and matching compiler-rt support. The protocol-orchestrator must then independently configure and build all three existing DNS fuzz targets before delegating one fresh `fuzz-engineer/g9-fuzz-evidence-002` leaf. Do not route G9 security review at this stage.

## Acceptance criteria

1. `cmake --version`, `clang --version`, and `clang++ --version` succeed on the selected host.
2. Clang compiles and links with `-fsanitize=fuzzer,address,undefined` using matching compiler-rt runtimes.
3. CMake configures and builds `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` from the assigned revision.
4. The evidence is independently recorded before exactly one fresh fuzz-engineer dispatch.

## Resolution (destination role)

Pending. Record host/image identity, executable paths and successful prerequisite evidence; mark resolution `READY_FOR_REVIEW`. This resolution is not G9 approval.

## Closure (orchestrator after verification)

Pending. G9 remains `BLOCKED`; workflow state remains unchanged until qualifying evidence exists and a fresh fuzz-engineer has completed its scoped work.
