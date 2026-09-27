# G9 DNS name-harness remediation plan

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-remediation-001-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9 corrective harness stage) |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-remediation-001` |
| Status | `READY_FOR_REVIEW` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `git:f90c9bd80217cddb0e036d4dc0d8914f0cd32927` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / actual effort unknown (telemetry unavailable) |

## Defect and minimal remediation

The prior G9 execution recorded a 1,133-byte input causing `fuzz/dns/fuzz_dns_name.c:12` to write index 1024 of `uint8_t packet[1024]`. The harness begins its synthesized DNS question at offset 12 and subsequently writes five terminal bytes at offsets `12 + copied` through `16 + copied`. Therefore `copied` must be at most `1024 - 17 = 1007`. The former cap of `sizeof(packet) - 16u` permits 1008 and writes the final byte at index 1024.

The authorized source-only remediation changes the cap to `sizeof(packet) - 17u`. It leaves the parser invocation and all packet construction semantics intact while ensuring `copied + 17u <= sizeof(packet)`.

## Focused verification plan

1. Confirm repository identity, tracked cleanliness, preserved pre-existing untracked paths, and explicit `/usr/bin/clang-19` plus `/usr/bin/clang++-19` availability.
2. Configure only `/tmp/ratatoskr-g9-name-harness-remediation-001` with the packet-specified LLVM 19 CMake command; build only `ratos_fuzz_dns_name`.
3. Derive a fixed local corpus file only under `/tmp` containing 1,133 zero bytes. It exercises the reported oversized-input condition; its provenance is this bounded local derivation, not a repository corpus change.
4. Replay the fixed corpus with the existing repository-defined `-fsanitize=fuzzer,address,undefined` target under `timeout 30s`, `-runs=1`, `-timeout=10`, and `-rss_limit_mb=1024`.
5. Treat any sanitizer, crash, timeout, nonzero exit, or build failure as blocking. Do not run packet/record targets or a full G9 campaign in this corrective assignment.

## Scope limitations

This plan validates only the authorized name-harness boundary correction. It neither replaces a fresh three-target G9 execution nor routes or approves G9 security review.