# G9 DNS full fuzz campaign plan — execution 004

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-004-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Target | `protocol/dns`: existing packet, name, record targets |
| Owner | `fuzz-engineer/g9-full-campaign-execution-004` |
| Status | `BLOCKED` after one campaign |
| Tested revision | `git:b82ea8499600c3ef7ab1e51fa297b477b1f17c1c` |

## Inputs and integrity

The packet commit `464702783c7174212644a4d6416a72958c057cae` is an ancestor of local HEAD and fetched `origin/hermes/dns-implementation-20260913`, both `b82ea8499600c3ef7ab1e51fa297b477b1f17c1c`. Root/origin/branch were verified as `/home/hermes/hermes-workspace/projects/Ratatoskr`, `https://github.com/Endeavoury/Ratatoskr.git`, and `hermes/dns-implementation-20260913`. G7 and G8 are `APPROVED`; G9 is not approved.

Verified SHA-256: `seeds.txt` `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet/name/record harnesses `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`, `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`, `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

## Derived corpus

`/tmp/ratatoskr-g9-full-campaign-execution-004-convert.py` used `label, separator, value = line.partition(':')`; it rejected missing, duplicate, or empty labels and unsupported directives; accepted literal `zero-length:` only with empty value; converted exactly `maximum-size: repeat 00 to 65535 octets during corpus preparation` to 65,535 NUL bytes; otherwise decoded `value.strip()` as hexadecimal. Fixed corpus: `/tmp/ratatoskr-g9-full-campaign-execution-004/corpus-fixed`, 10 files, 65,887 bytes; manifest SHA-256 `e8e9c5aa6f64de2208107ec1da50a568386c0ac119e962e5df4765e90207d63f`.

The ten seed output digests/sizes are recorded in that manifest: `01-zero-length.bin` 0 / `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`; `02-maximum-size.bin` 65535 / `9f797b60edaf440d5831da53c35f4d4847a2f55adc64cfe887a7bcfcd9eca495`; `03-valid-a.bin` 45 / `770622abdbf50d514ee038eff5c8a52360a441ac3b52e5359e7360044bb0874d`; `04-valid-aaaa.bin` 57 / `ebe126c2b3d7e40b7bdfb19c2cc550a7b3b2aa059bae9a4b11c168fe773710dc`; `05-valid-mx.bin` 50 / `2f36b307da97dd508deefb9c1fdee1d00ddb58c0f29cda34a8156c87cdd48a54`; `06-valid-txt.bin` 47 / `542373994cb87d838c00b64b08e7b6b8fb9087bdc030434bee50021f68b0d4cb`; `07-valid-ptr.bin` 65 / `4cb2e955ae4d3fb74f79d295406827ffd306d61722de57310cf006bc0df896cf`; `08-truncated.bin` 29 / `51b208163f61a88671385db1d78afc775e5559feda165bc7c3c1c5f8a662f25f`; `09-pointer-loop.bin` 18 / `19754f606d8caf63ab261b66ab4a4f6ebcf113bfee851e49910979d21fc0cb8f`; `10-invalid-rdlength.bin` 41 / `026c5d564611ff4db34de2671e15f8a96717129d30ccac097de7e50c9ab51edc`.

## Build and execution method

Configured and built only the assigned targets from the repository root:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-004/build -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-004/build --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Both commands returned zero. `/tmp/ratatoskr-g9-full-campaign-execution-004-run.py` copied the fixed corpus independently for packet, name, then record and invoked exactly `/usr/bin/timeout 120s <target> <fresh-corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10`. It captured full stdout/stderr, `time.monotonic()` elapsed time, and child `resource.RUSAGE_CHILDREN.ru_maxrss`; `/usr/bin/time` was not used. It scanned sanitizer, crash, timeout, and resource diagnostics and stopped at the first non-clean result.

## Invariant and limits

Applicable invariant: hostile parser inputs must not crash, trigger ASan/UBSan, time out, or violate the declared libFuzzer RSS limit. The fixed budget was one configure/build and one serial run per target. Packet and name were clean; record produced the stopping resource diagnostic. No retry, changed flags, source/harness/corpus/CMake/workflow-state edit, review routing, or further delegation occurred.

Requested route: `openai-codex/gpt-5.6-terra`, medium. Actual inherited route exposed: `openai-codex/gpt-5.6-terra`; effort and usage telemetry: `unknown`.
