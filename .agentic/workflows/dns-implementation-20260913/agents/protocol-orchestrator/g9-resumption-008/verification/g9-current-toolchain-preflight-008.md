# G9 current toolchain preflight 008

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-resumption-008-toolchain-preflight` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner | `protocol-orchestrator/g9-resumption-008` |
| Status | `COMPLETE` — administrative prerequisite verification only |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Checked baseline | local HEAD and origin `refs/heads/hermes/dns-implementation-20260913` = `87c2b7a36fdedca2370113093e53633850268a9a` |
| Runtime | observed `openai-codex/gpt-5.6-terra`; reasoning effort telemetry unavailable |

## Predicate and evidence

The historical `g9-resumption-007` conclusion is superseded only as to its PATH-only compiler probe. It tested unversioned `clang`/`clang++`; that absence is not the requested predicate. This fresh probe explicitly selected both versioned drivers:

```text
/usr/bin/clang-19 --version
/usr/bin/clang++-19 --version
/usr/bin/cmake --version
/usr/bin/clang-19 -print-resource-dir
/usr/bin/clang-19 -print-file-name=libclang_rt.fuzzer-x86_64.a
/usr/bin/clang-19 -print-file-name=libclang_rt.asan-x86_64.a
/usr/bin/clang-19 -print-file-name=libclang_rt.ubsan_standalone-x86_64.a
```

Observed: Debian Clang 19.1.7 for both `/usr/bin/clang-19` and `/usr/bin/clang++-19`; CMake 3.31.6; resource directory `/usr/lib/llvm-19/lib/clang/19`; and matching fuzzer, ASan, and UBSan compiler-rt archives under that resource directory.

A disposable local-only build then configured and built all required existing DNS targets:

```text
/usr/bin/cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-resumption-008 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
/usr/bin/cmake --build /tmp/ratatoskr-g9-resumption-008 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

CMake identified Clang 19.1.7 and generated successfully. Ninja linked `fuzz/ratos_fuzz_dns_packet`, `fuzz/ratos_fuzz_dns_name`, and `fuzz/ratos_fuzz_dns_record`; all three were verified executable.

## Decision and limits

All stated dispatch prerequisites are true: CMake, explicitly selected matching LLVM19 sanitizer runtime support, and configure/build of all three existing DNS targets. The workflow can move from the obsolete toolchain `BLOCKED` posture to `IN_PROGRESS` solely to record one new bounded fuzz-engineer execution assignment. This is not G9 approval and does not erase prior resource/campaign findings; those are historical evidence, not an active leaf.

No fuzzer campaign was run in this preflight. The only authorized successor is one serial, local-only fuzz-engineer campaign. G9 security review and all later stages remain unassigned.

## Git-delivery limitation

The required absolute wrapper candidates `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`, `/usr/local/bin/git-agent`, `/usr/bin/git-agent`, `/home/hermes/.local/bin/git-agent`, and `/home/hermes/bin/git-agent` could not be verified executable in this session. No raw-git commit or push will be substituted; there is no remote readback because no push occurs.
