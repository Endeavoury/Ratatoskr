# G9 DNS name-harness bounds remediation results 003

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-bounds-remediation-003-results` |
| Workflow / stage | `dns-implementation-20260913` / G9 corrective name-harness validation |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-bounds-remediation-003` |
| Status | `READY_FOR_REVIEW` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline / pre-write local / fetched origin ref | `2c6b0bc742d3db88cc94b9e6e354b362ee0f6055` / same / same |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / `openai-codex/gpt-5.6-terra`, effort unknown |
| Delivery commit / readback | Reported in the leaf handoff and final delivery summary after wrapper-only push. |

## Preconditions and scope

Before writes, repository root, origin, branch, local `HEAD`, and fetched `origin/hermes/dns-implementation-20260913` each matched the required baseline. Unrelated pre-existing untracked paths, including the parent `g9-resumption-010/` routing artifacts, were preserved and excluded from staging. The wrapper existed and LLVM19/CMake/Ninja were available.

Live `fuzz/dns/fuzz_dns_name.c` already has `size < sizeof(packet) - 17u ? size : sizeof(packet) - 17u`; its source blob SHA-256 was unchanged from the baseline (`b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`). This was therefore a source no-op.

## Bounds reasoning

`uint8_t packet[1024]` provides indices 0 through 1023. With `copied <= 1024 - 17 = 1007`, the five terminal stores at offsets 12 through 16 relative to `copied` end at `16 + 1007 = 1023`; `copied + 17` is at most 1024. Thus the known 1,133-byte trigger is safely truncated before terminal writes.

## Focused LLVM19 sanitizer validation

Tool versions: `/usr/bin/clang-19` and `/usr/bin/clang++-19`: Debian Clang 19.1.7; CMake 3.31.6; Ninja 1.12.1. Existing `fuzz/CMakeLists.txt` configures `-fsanitize=fuzzer,address,undefined`.

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-name-harness-bounds-remediation-003 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
# exit 0
cmake --build /tmp/ratatoskr-g9-name-harness-bounds-remediation-003 --target ratos_fuzz_dns_name --parallel 2
# exit 0; 13 Ninja steps; linked fuzz/ratos_fuzz_dns_name
timeout 30s /tmp/ratatoskr-g9-name-harness-bounds-remediation-003/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-name-harness-bounds-remediation-003/corpus -runs=1 -timeout=10 -rss_limit_mb=1024
# exit 0
```

The isolated reproducer is 1,133 zero bytes at `/tmp/ratatoskr-g9-name-harness-bounds-remediation-003/corpus/reproducer-1133.bin`, SHA-256 `c80420c3c5d20d1ce9447e14c185c5a2840ca200790f9b1532f556f5edcefe7b`. libFuzzer loaded one file and completed two runs in zero seconds: `DONE`, coverage 192, features 193, RSS 33 MB. No ASan, UBSan, crash, timeout, or RSS-limit diagnostic occurred.

## Limitations

No packet or record target was built/run. No campaign, corpus mutation, CMake/source change, G9 review, security review, or later workflow route occurred. This focused no-op validation is not G9 approval.
