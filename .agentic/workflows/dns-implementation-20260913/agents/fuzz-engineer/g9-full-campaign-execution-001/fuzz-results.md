# G9 DNS full fuzz campaign results

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-001-results` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner / ACTIVE ROLE | `fuzz-engineer` |
| Status | `BLOCKED` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline | `git:dd1c0f3987a88a4c0b0d16afbeddc1043674561d` |
| Build / corpus directories | `/tmp/ratatoskr-g9-full-campaign-execution-001` / `/tmp/ratatoskr-g9-full-campaign-execution-001-corpus` |

## Corpus conversion provenance

Decoder command: the recorded Python 3 first-colon decoder in the terminal transcript read `fuzz/dns/corpus/seeds.txt`, rejected missing/empty/duplicate labels and invalid directives, accepted only literal `zero-length:` and the exact `maximum-size` directive, and wrote only `/tmp/ratatoskr-g9-full-campaign-execution-001-corpus/{01..10}-*.bin` plus `manifest.json`.

| Label | File | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| zero-length | `01-zero-length.bin` | 0 | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` |
| maximum-size | `02-maximum-size.bin` | 65535 | `9f797b60edaf440d5831da53c35f4d4847a2f55adc64cfe887a7bcfcd9eca495` |
| valid-a | `03-valid-a.bin` | 45 | `770622abdbf50d514ee038eff5c8a52360a441ac3b52e5359e7360044bb0874d` |
| valid-aaaa | `04-valid-aaaa.bin` | 57 | `ebe126c2b3d7e40b7bdfb19c2cc550a7b3b2aa059bae9a4b11c168fe773710dc` |
| valid-mx | `05-valid-mx.bin` | 50 | `2f36b307da97dd508deefb9c1fdee1d00ddb58c0f29cda34a8156c87cdd48a54` |
| valid-txt | `06-valid-txt.bin` | 47 | `542373994cb87d838c00b64b08e7b6b8fb9087bdc030434bee50021f68b0d4cb` |
| valid-ptr | `07-valid-ptr.bin` | 65 | `4cb2e955ae4d3fb74f79d295406827ffd306d61722de57310cf006bc0df896cf` |
| truncated | `08-truncated.bin` | 29 | `51b208163f61a88671385db1d78afc775e5559feda165bc7c3c1c5f8a662f25f` |
| pointer-loop | `09-pointer-loop.bin` | 18 | `19754f606d8caf63ab261b66ab4a4f6ebcf113bfee851e49910979d21fc0cb8f` |
| invalid-rdlength | `10-invalid-rdlength.bin` | 41 | `026c5d564611ff4db34de2671e15f8a96717129d30ccac097de7e50c9ab51edc` |

## LLVM19 build

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-001 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-001 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Configure succeeded with Clang 19.1.7. Ninja completed all 17 steps and linked all three requested targets. `fuzz/CMakeLists.txt` applies `-fsanitize=fuzzer,address,undefined`.

## Serial execution and stop

The first required target was attempted at `2026-09-27T06:25:25+02:00` with the required 120-second timeout and libFuzzer flags, but with an added `/usr/bin/time` measurement wrapper:

```text
timeout 120s /usr/bin/time -v -o /tmp/ratatoskr-g9-full-campaign-execution-001/packet.time /tmp/ratatoskr-g9-full-campaign-execution-001/fuzz/ratos_fuzz_dns_packet /tmp/ratatoskr-g9-full-campaign-execution-001-corpus -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

Complete stdout/stderr diagnostic:

```text
timeout: failed to run command ‘/usr/bin/time’: No such file or directory
```

The command exited `127`; no target process ran, so elapsed time, target RSS, libFuzzer diagnostics, sanitizer disposition, crash disposition, and failure input SHA-256 are unavailable. This is a nonzero campaign stop condition. Per packet, no minimization/replay, no retry/workaround, and no name or record target run occurred. G9 has no clean campaign result.