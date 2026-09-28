# G9 DNS full fuzz campaign plan — execution 003

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-003-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner | `fuzz-engineer/g9-full-campaign-execution-003` |
| Status | `BLOCKED` — precondition failure before campaign |
| Required baseline | `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4` |

## Required precondition result

After `git fetch origin hermes/dns-implementation-20260913`, the repository root and origin URL were correct and the branch was `hermes/dns-implementation-20260913`. Local HEAD and `origin/hermes/dns-implementation-20260913` both resolved to `7b92dcb393881d7b98a15289bb98ce52317eba73`, which differs from the required baseline. The packet requires all three values to equal before campaign activity. This divergence blocks execution.

## Inputs independently checked

G7/G8 are recorded `APPROVED`; G9/fuzzing is `BLOCKED`. The required tools are available: Clang/Clang++ 19.1.7, CMake 3.31.6, Ninja 1.12.1, GNU timeout 9.7, and matching LLVM19 fuzzer/ASan/UBSan runtime archives. SHA-256 inputs were: seeds `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet/name/record harnesses `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`, `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`, `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; and fuzz CMake `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

No deterministic corpus or target plan was executed because the prerequisite baseline/ref equality failed. The mandated packet → name → record commands, unchanged 1024 MiB RSS limit, and stop policy remain unexercised.
