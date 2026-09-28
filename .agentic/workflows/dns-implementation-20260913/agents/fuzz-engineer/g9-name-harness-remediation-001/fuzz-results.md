# G9 DNS name-harness remediation results

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-remediation-001-results` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9 corrective harness stage) |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-remediation-001` |
| Status | `READY_FOR_REVIEW` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch / pre-change local / pre-change remote | `git:f90c9bd80217cddb0e036d4dc0d8914f0cd32927` / same / same |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Source revision after remediation | `fuzz/dns/fuzz_dns_name.c` SHA-256 `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f` (pre-commit) |

## Preconditions

Repository root, origin, branch, local HEAD, and `origin/hermes/dns-implementation-20260913` matched the packet baseline `f90c9bd80217cddb0e036d4dc0d8914f0cd32927`. `git diff --quiet` passed before this assignment's write. Pre-existing untracked paths were observed and left untouched. `/usr/bin/clang-19` and `/usr/bin/clang++-19` were both usable Debian Clang 19.1.7; no unversioned compiler was used.

## Remediation

Changed only `fuzz/dns/fuzz_dns_name.c`:

```c
size_t copied = size < sizeof(packet) - 17u ? size : sizeof(packet) - 17u;
```

The five terminal writes span offsets `12 + copied` through `16 + copied`; the new maximum `copied` is 1007, making the largest write index 1023 in the 1024-byte packet.

## Configure and focused build

All commands ran from the repository root:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-name-harness-remediation-001 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-name-harness-remediation-001 --target ratos_fuzz_dns_name --parallel 2
```

Configure succeeded with Clang 19.1.7. The 13-step Ninja build completed successfully and linked `/tmp/ratatoskr-g9-name-harness-remediation-001/fuzz/ratos_fuzz_dns_name`.

## Fixed-corpus replay

A local derived file was created only at `/tmp/ratatoskr-g9-name-harness-remediation-001/corpus/reproducer-1133.bin` with `bytes(1133)`: 1,133 zero bytes, SHA-256 `c80420c3c5d20d1ce9447e14c185c5a2840ca200790f9b1532f556f5edcefe7b`. This preserves the reported reproducer *condition* (input length 1,133) without modifying the tracked corpus or relying on the historical crash payload.

```text
timeout 30s /tmp/ratatoskr-g9-name-harness-remediation-001/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-name-harness-remediation-001/corpus -runs=1 -timeout=10 -rss_limit_mb=1024
```

Result: exit 0; libFuzzer loaded the one 1,133-byte corpus file and completed 2 runs in 0 seconds (`DONE`, RSS 33 MB). The sanitizer-instrumented target emitted no UBSan, ASan, crash, timeout, or RSS-limit diagnostic.

## Scope and limitations

Only the name target was built and replayed. Packet and record targets were not run. This is bounded remediation evidence only, not a full G9 campaign, not a G9 approval, and not a security review.