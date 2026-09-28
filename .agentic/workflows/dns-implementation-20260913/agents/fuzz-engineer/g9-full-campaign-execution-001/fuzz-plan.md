# G9 DNS full fuzz campaign plan

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-001-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner / ACTIVE ROLE | `fuzz-engineer` |
| Status | `BLOCKED` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Packet revision / HEAD | `git:dd1c0f3987a88a4c0b0d16afbeddc1043674561d` / same |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / `openai-codex/gpt-5.6-terra`, effort telemetry unknown |

## Preconditions verified

The packet commit was derived with `git log -1 --format=%H -- <packet>` and was an ancestor of `HEAD`; `git diff --quiet` exited 0. Root, branch, and origin were `/home/hermes/hermes-workspace/projects/Ratatoskr`, `hermes/dns-implementation-20260913`, and `https://github.com/Endeavoury/Ratatoskr.git`. Pre-existing untracked paths were observed and preserved.

SHA-256 matched every packet-required input: `seeds.txt` `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet/name/record harnesses `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`, `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`, `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; and `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

Inputs read: approved G7/G8 reviews, LLVM19 toolchain preflight, focused name-harness remediation/review records, corpus README/seeds, and all three existing harnesses. LLVM19 was Debian Clang 19.1.7; CMake 3.31.6 and Ninja 1.12.1.

## Corpus and intended campaign

The first-colon decoder converted the ten labeled seed entries only under `/tmp/ratatoskr-g9-full-campaign-execution-001-corpus`; `zero-length` became empty, and `maximum-size` became 65,535 NUL bytes. The planned serial commands were each `timeout 120s <target> /tmp/ratatoskr-g9-full-campaign-execution-001-corpus -max_total_time=90 -rss_limit_mb=1024 -timeout=10`, in packet, name, record order. Any nonzero exit, sanitizer, crash, timeout, UB, or resource diagnostic required immediate stop.

## Stop disposition

The packet target launch failed before the fuzzer executable started because the added measurement wrapper `/usr/bin/time` does not exist. `timeout` exited 127 with `timeout: failed to run command ‘/usr/bin/time’: No such file or directory`. Under the packet stop rule, no remaining target was run and no retry/workaround was attempted. This plan is not G9 evidence.