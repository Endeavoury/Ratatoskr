# DNS G9 fuzz plan

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-plan-001` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target / owner | `protocol/dns` / `fuzz-engineer/g9-fuzz-evidence-001` |
| Status | `BLOCKED` — execution toolchain unavailable |
| Input revision | `git:5bac8c1e9771ac9281b6b696da98efe718efc27f` |
| Prerequisites | G7 and G8 approved for candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Actual route | `openai-codex/gpt-5.6-terra`; reasoning telemetry `unknown` (requested `medium`) |

## Reachable hostile-input surfaces

1. `ratos_dns_parse_response` via `ratos_fuzz_dns_packet`: arbitrary response bytes, expected transaction ID derived from bytes 0–1.
2. `ratos_dns_parse_response` via `ratos_fuzz_dns_name`: constructed response header/question with mutable DNS-name encoding.
3. `ratos_dns_parse_response` via `ratos_fuzz_dns_record`: constructed A-record response with mutable type and RDATA.

These harnesses exercise the parser, DNS name expansion/compression traversal, section/record decoding, typed RDATA allocation/formatting, result cleanup, and default configured limits. UDP/TCP network exchanges and incremental request events are not reachable from the existing fuzz targets and are not claimed exercised.

## Trust boundaries and invariants

Untrusted DNS wire bytes cross the parser boundary. Applicable invariants are: no ASan/UBSan/libFuzzer-detected crash or undefined behavior; no out-of-bounds/invalid free/leak report under the recorded sanitizer configuration; parser termination under bounded inputs; result destruction remains safe after every parser disposition; and resource-limit/malformed inputs may return errors but must not crash. Semantic round-trip is not claimed because these targets invoke parsing only.

## Seed provenance and mutation approach

Source provenance is `fuzz/dns/corpus/seeds.txt` at the input revision, documented by `fuzz/dns/corpus/README.md`: empty, maximum-size preparation instruction, valid A/AAAA/MX/TXT/PTR, truncated, pointer-loop, and invalid-RDLENGTH cases. Decode each labeled hexadecimal value (excluding the descriptive maximum-size line) into an ephemeral binary corpus directory; generate the maximum-size all-zero seed there. Run libFuzzer byte-level mutation from that corpus against all three targets. The name and record harnesses supply valid surrounding structure to drive their focused mutable fields.

## Reproducible build and campaign

From repository root on Linux with CMake, Ninja or Make, and Clang with compiler-rt libFuzzer/ASan/UBSan:

```sh
rm -rf build-g9-fuzz corpus-g9-dns
python3 - <<'PY'
from pathlib import Path
out = Path('corpus-g9-dns'); out.mkdir()
for line in Path('fuzz/dns/corpus/seeds.txt').read_text().splitlines():
    label, value = line.split(': ', 1)
    if label == 'maximum-size':
        (out / label).write_bytes(bytes(65535))
    elif label != 'zero-length':
        (out / label).write_bytes(bytes.fromhex(value))
    else:
        (out / label).write_bytes(b'')
PY
CC=clang cmake -S . -B build-g9-fuzz -DCMAKE_BUILD_TYPE=Debug -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build build-g9-fuzz --parallel
for target in packet name record; do
  "./build-g9-fuzz/fuzz/ratos_fuzz_dns_${target}" corpus-g9-dns -seed=20260926 -runs=100000 -max_len=65535 -timeout=10 -rss_limit_mb=2048 -print_final_stats=1
done
```

Budget: three deterministic 100,000-run campaigns, each bounded to 10 seconds per input and 2 GiB RSS. Preserve libFuzzer crash artifacts and rerun each as `target artifact -runs=1 -seed=20260926`; route a sanitizer crash/UB to `c-protocol-implementer`, or a harness/strategy deficiency to this role. Record elapsed time, final coverage/corpora counters when emitted, and all reproductions in the results artifact.

## Limitation and stop condition

The current environment has neither `cmake` nor `clang`/libFuzzer, so this execution plan was not run. G9 remains blocked pending a fresh execution-capable fuzz-engineer assignment or an environment that satisfies the commands above.