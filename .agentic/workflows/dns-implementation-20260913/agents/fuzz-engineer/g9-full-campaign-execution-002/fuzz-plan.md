# G9 DNS full fuzz campaign plan

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-002-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Target | `protocol/dns` — existing packet, name, and record fuzz targets |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-full-campaign-execution-002` |
| Status | `BLOCKED` |
| Baseline | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Executed at | `2026-09-27T07:04:50+02:00` |

## Inputs and provenance

The packet is committed at `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`, which is HEAD and an ancestor of HEAD. Repository root, branch, origin, and tracked cleanliness were verified: `/home/hermes/hermes-workspace/projects/Ratatoskr`, `hermes/dns-implementation-20260913`, `https://github.com/Endeavoury/Ratatoskr.git`, and `git diff --quiet` exit 0. Pre-existing untracked paths were preserved.

Required G7 and G8 records are `APPROVED` for candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; the LLVM19 preflight confirms the three targets. Verified SHA-256 digests: seeds `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`, README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`, packet harness `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`, name harness `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`, record harness `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`, and `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

## Corpus and execution method

The fixed corpus was decoded only under `/tmp/ratatoskr-g9-full-campaign-execution-002-corpus` with `/usr/bin/python3` using first-colon partition; the decoder rejected missing colons, empty/duplicate labels, and unexpected directives; accepted literal `zero-length:` only with empty value; accepted only the specified `maximum-size` directive; and otherwise used `bytes.fromhex(value.strip())`. Output was `01-zero-length.bin` (0, `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`), `02-maximum-size.bin` (65535, `9f797b60edaf440d5831da53c35f4d4847a2f55adc64cfe887a7bcfcd9eca495`), `03-valid-a.bin` (45, `770622abdbf50d514ee038eff5c8a52360a441ac3b52e5359e7360044bb0874d`), `04-valid-aaaa.bin` (57, `ebe126c2b3d7e40b7bdfb19c2cc550a7b3b2aa059bae9a4b11c168fe773710dc`), `05-valid-mx.bin` (50, `2f36b307da97dd508deefb9c1fdee1d00ddb58c0f29cda34a8156c87cdd48a54`), `06-valid-txt.bin` (47, `542373994cb87d838c00b64b08e7b6b8fb9087bdc030434bee50021f68b0d4cb`), `07-valid-ptr.bin` (65, `4cb2e955ae4d3fb74f79d295406827ffd306d61722de57310cf006bc0df896cf`), `08-truncated.bin` (29, `51b208163f61a88671385db1d78afc775e5559feda165bc7c3c1c5f8a662f25f`), `09-pointer-loop.bin` (18, `19754f606d8caf63ab261b66ab4a4f6ebcf113bfee851e49910979d21fc0cb8f`), and `10-invalid-rdlength.bin` (41, `026c5d564611ff4db34de2671e15f8a96717129d30ccac097de7e50c9ab51edc`).

Configured and built only the assigned targets with:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-002 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-002 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Each serial launch used a Python wrapper around exactly `/usr/bin/timeout 120s <target> /tmp/ratatoskr-g9-full-campaign-execution-002-corpus -max_total_time=90 -rss_limit_mb=1024 -timeout=10`. The wrapper recorded `time.monotonic()` elapsed time, `resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss` before/after/delta in Linux KiB, command, return code, and complete stdout/stderr in `/tmp/ratatoskr-g9-full-campaign-execution-002/{packet,name,record}-run.json`. It did not invoke `/usr/bin/time`.

## Invariants and stopping policy

Applicable invariant: hostile parser inputs must not crash, trip ASan/UBSan, time out, or exceed the declared libFuzzer RSS limit. Packet then name then record were launched serially. The first nonzero result, sanitizer/crash/UB, timeout, or resource diagnostic stops the campaign without retry or remaining target. Packet and name were clean; record triggered the resource stop condition. This plan is execution evidence, not G9 approval.

## Model and limitations

Requested route: `openai-codex/gpt-5.6-terra`, medium. Actual model: `gpt-5.6-terra`; actual effort and usage telemetry: `unknown`. No network, source/CMake/test/fuzz/corpus change, workflow-state write, review dispatch, or further delegation occurred. The campaign is blocked pending orchestrator-directed defect triage; no security review is routed by this author.