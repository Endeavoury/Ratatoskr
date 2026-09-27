# G9 DNS fuzz results — execution 005

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-005-results` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-fuzz-execution-005` |
| Status | `BLOCKED` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch HEAD | `bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15` |
| Packet commit | `bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15` (ancestor of HEAD) |
| Campaign-source baseline | `400e818790bf6a8e7f13b7b86cfaf837a11066fc` (ancestor of HEAD) |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / unknown (telemetry not exposed) |

## Preconditions and integrity

`git diff --quiet` succeeded before campaign writes; all pre-existing untracked paths were preserved. The packet and campaign-source ancestor checks both succeeded. Fixed SHA-256 inputs matched the delegation exactly:

```text
8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07  fuzz/dns/corpus/seeds.txt
5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551  fuzz/dns/corpus/README.md
abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263  fuzz/dns/fuzz_dns_packet.c
f30ad35561305843882bb79a43af5a2ecf392fb74d7ca8b8c769dc59bbc3c4b0  fuzz/dns/fuzz_dns_name.c
2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c  fuzz/dns/fuzz_dns_record.c
5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5  fuzz/CMakeLists.txt
```

Tool versions: CMake 3.31.6; Ninja 1.12.1; `/usr/bin/clang-19` and `/usr/bin/clang++-19` Debian Clang 19.1.7; GNU `timeout` 9.7. The existing CMake target options specify `-fsanitize=fuzzer,address,undefined`.

## Derived corpus

A strict first-colon Python conversion ran solely under `/tmp/ratatoskr-g9-fuzz-execution-005/corpus`. It produced 10 named inputs: `zero-length` (0), `maximum-size` (65535), `valid-a` (45), `valid-aaaa` (57), `valid-mx` (50), `valid-txt` (47), `valid-ptr` (65), `truncated` (29), `pointer-loop` (18), and `invalid-rdlength` (41) bytes: 65,887 bytes total. The exact converter rejected the packet-specified invalid forms and accepted only the special values specified in `seeds.txt`.

During the first libFuzzer run, its normal corpus minimization/expansion changed only this derived `/tmp` corpus. Consequently the name target loaded 292 derived files (1–65,535 bytes; 687,325 bytes), still only under `/tmp`.

## Configure and build

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-fuzz-execution-005 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-fuzz-execution-005 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Configure succeeded with Clang 19.1.7. Build succeeded: all 17 Ninja steps completed and each of the three named target executables was linked in `/tmp/ratatoskr-g9-fuzz-execution-005/fuzz/`.

## Serial campaign evidence

| Target | Exact invocation | Elapsed | Exit | Result |
| --- | --- | ---: | ---: | --- |
| `ratos_fuzz_dns_packet` | `timeout 120s /tmp/ratatoskr-g9-fuzz-execution-005/fuzz/ratos_fuzz_dns_packet /tmp/ratatoskr-g9-fuzz-execution-005/corpus -max_total_time=90 -rss_limit_mb=1024 -timeout=10` | 91 s | 0 | Clean: completed 572,748 runs in 91 seconds; final `DONE`; no sanitizer/crash/timeout/RSS diagnostic. Final coverage `cov: 780`, `ft: 3156`, corpus `253/474Kb`, RSS 329 MB. |
| `ratos_fuzz_dns_name` | `timeout 120s /tmp/ratatoskr-g9-fuzz-execution-005/fuzz/ratos_fuzz_dns_name /tmp/ratatoskr-g9-fuzz-execution-005/corpus -max_total_time=90 -rss_limit_mb=1024 -timeout=10` | <1 s | 1 | **Crash: not clean.** Initial derived corpus execution reported UBSan index 1024 out of bounds at `fuzz/dns/fuzz_dns_name.c:12:32`, then ASan `stack-buffer-overflow`, write of size 1 in `LLVMFuzzerTestOneInput`; crash input saved under `/tmp`. |
| `ratos_fuzz_dns_record` | Not run | — | — | Not run: mandatory immediate stop after the name-target sanitizer crash; no retry. |

Relevant sanitizer evidence for `ratos_fuzz_dns_name`:

```text
fuzz/dns/fuzz_dns_name.c:12:32: runtime error: index 1024 out of bounds for type 'uint8_t[1024]'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior fuzz/dns/fuzz_dns_name.c:12:32
ERROR: AddressSanitizer: stack-buffer-overflow
WRITE of size 1 ... in LLVMFuzzerTestOneInput
[32, 1056) 'packet' <== Memory access at offset 1056 overflows this variable
```

libFuzzer emitted `crash-7d5929dc5a1559f575eda5f7bbe6f49ae0fbe721`. It was immediately copied to `/tmp/ratatoskr-g9-fuzz-execution-005/name-crash-7d5929dc5a1559f575eda5f7bbe6f49ae0fbe721` (1,133 bytes; SHA-256 `f311b05d472cc851617730ec235289edb0b18777d06325477a601eff164ea01a`) and the generated repository-root copy was removed; no repository corpus or source input remains changed.

## Disposition and limitations

This is not G9 evidence suitable for approval. The packet target was clean only; the name harness has an ASan/UBSan failure and record was deliberately not run. No source or harness remediation was authorized or attempted. All detailed build/run logs and the preserved crash input remain under `/tmp/ratatoskr-g9-fuzz-execution-005`.
