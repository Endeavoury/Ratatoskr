# G9 corpus-preparation blocker verification and reroute preflight

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-corpus-decoder-routing-001-preflight` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner role | `protocol-orchestrator/g9-corpus-decoder-routing-001` |
| Status | `READY_TO_COMMIT` |
| Verified at | `2026-09-27T02:08:21+02:00` |
| Local / remote baseline | `git:cdc36bdf5005ebc9c0bdcc9a8c7050c396b142d4` |

## Verified blocker

The committed `fuzz-engineer/g9-fuzz-execution-002/fuzz-results.md` records a single failed corpus-preparation attempt, before CMake configuration or any target execution. Its decoder used `line.split(": ", 1)`. The current tracked `fuzz/dns/corpus/seeds.txt` begins with literal `zero-length:` (no space after the colon), producing `ValueError: not enough values to unpack`. The specialist correctly recorded `BLOCKED`; no build, run, sanitizer finding, or G9 review occurred.

## Inputs verified before routing

- Branch is `hermes/dns-implementation-20260913`; origin is `https://github.com/Endeavoury/Ratatoskr.git`; local HEAD, `origin/...`, and `git ls-remote` all equal `cdc36bdf5005ebc9c0bdcc9a8c7050c396b142d4`.
- `git diff --name-only` was empty. Existing unrelated untracked paths remain excluded and preserved.
- `fuzz/dns/corpus/seeds.txt` SHA-256: `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`.
- `fuzz/dns/corpus/README.md` SHA-256: `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`.
- Existing target sources and registration: `fuzz_dns_packet.c` `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`; `fuzz_dns_name.c` `f30ad35561305843882bb79a43af5a2ecf392fb74d7ca8b8c769dc59bbc3c4b0`; `fuzz_dns_record.c` `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.
- G7 and G8 are APPROVED in workflow state; G9 remains unapproved.

## Correction and bounded route

The sole fresh leaf is `fuzz-engineer/g9-fuzz-execution-004`. It must decode only into `/tmp`, first verify all recorded source digests, split each description at the first `:`, accept the empty `zero-length` value, generate exactly 65,535 zero bytes for the documented `maximum-size` directive, and hex-decode all other values. It must build and run exactly the existing three DNS targets serially under the stated time and memory bounds. The new packet deliberately requires its own committed routing packet to be an ancestor of execution HEAD, rather than impossible equality to a pre-commit HEAD.

No G9 security reviewer is routed by this administrative record. A distinct reviewer is conditional on three clean bounded runs and complete specialist evidence.