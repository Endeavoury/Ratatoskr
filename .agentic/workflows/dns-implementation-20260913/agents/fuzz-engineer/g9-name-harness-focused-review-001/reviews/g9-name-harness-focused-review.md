# G9 DNS name-harness focused independent review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-focused-review-001` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (focused remediation review) |
| Target | `fuzz/dns/fuzz_dns_name.c` |
| Reviewer identity | `fuzz-engineer/g9-name-harness-focused-review-001`, fresh reviewer independent of remediation author `deleg_9f677c42/task-0` |
| Disposition | `APPROVED` (focused remediation only) |
| Candidate / parent | `git:2c9e9b945352642d27cf703132e8e5e525b8b5cb` / `git:f90c9bd80217cddb0e036d4dc0d8914f0cd32927` |
| Candidate source SHA-256 | `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f` |
| Requested / actual model route | `openai-codex/gpt-5.6-terra`, medium / `openai-codex/gpt-5.6-terra`; actual effort telemetry unavailable |

## Independent checks

1. The candidate exists and has direct parent `f90c9bd80217cddb0e036d4dc0d8914f0cd32927`; parent ancestry passed. Remote readback was `refs/heads/hermes/dns-implementation-20260913 = d7dae4ecb33ff6c94cd5fc99e880fce2c4de42a8`. Its local tracking ref contains the candidate, and the candidate's source blob is unchanged through that ref.
2. `git diff-tree --name-only parent candidate` listed exactly five paths: `fuzz/dns/fuzz_dns_name.c` and the four prescribed remediation reports. `git diff --check parent candidate` exited 0. The source diff is solely `sizeof(packet) - 16u` to `sizeof(packet) - 17u`.
3. The cap is `1024 - 17 = 1007`; the terminal writes are at offsets `12 + copied` through `16 + copied`. Thus maximum `copied` is 1007 and maximum write index is `16 + 1007 = 1023`, within `packet[1024]`. The parser input length remains `copied + 17`, at most 1024.
4. Capability was present: `/usr/bin/clang-19` and `/usr/bin/clang++-19` report Debian Clang 19.1.7; CMake 3.31.6 and Ninja 1.12.1 were available. From the assigned repository cwd, an isolated candidate worktree in `/tmp/ratatoskr-g9-name-harness-focused-review-001-source` was configured with the explicit LLVM19 paths and `-DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF`. `cmake --build ... --target ratos_fuzz_dns_name --parallel 2` completed all 13 steps, exit 0. `fuzz/CMakeLists.txt` applies `-fsanitize=fuzzer,address,undefined` to this target.
5. I created only `/tmp/ratatoskr-g9-name-harness-focused-review-001-build/corpus/reproducer-1133.bin`: 1,133 zero bytes, SHA-256 `c80420c3c5d20d1ce9447e14c185c5a2840ca200790f9b1532f556f5edcefe7b`. `timeout 30s .../ratos_fuzz_dns_name .../corpus -runs=1 -timeout=10 -rss_limit_mb=1024` exited 0: libFuzzer loaded one 1,133-byte input and completed two runs. Output contained no ASan, UBSan, crash, timeout, or RSS-limit diagnostic.

## Scope limitation and disposition

This approves only the focused name-harness remediation. It does **not** approve G9, does not constitute a full G9 campaign or security review, and does not cover packet or record targets. G9 remains `BLOCKED` pending a fresh complete campaign and the designated independent G9 security review.
