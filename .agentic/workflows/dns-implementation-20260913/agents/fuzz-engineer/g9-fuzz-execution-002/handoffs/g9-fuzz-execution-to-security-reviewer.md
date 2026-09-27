# Handoff: G9 fuzz execution blocked

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-002-to-security-reviewer` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target | `protocol/dns` |
| Source role | `fuzz-engineer/g9-fuzz-execution-002` |
| Destination role | `security-reviewer` (G9 reviewer), via `protocol-orchestrator` routing |
| Status | `BLOCKED` |
| Blocking | Yes |
| Source revision | Local execution `git:f4a3d9a1dc8faca3e8cca2ce87d4af4e64f328ba`; dispatch `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3` |
| Evidence | `../fuzz-plan.md`; `../fuzz-results.md` |
| Owner for action | `protocol-orchestrator` must route a new authorized fuzz-engineer assignment; this leaf cannot retry or repair the failed prerequisite. |

## Reason and reproducible evidence

The required fixed-corpus preparation failed before configure/build/campaign. The decoder split every `seeds.txt` line on `": "`; the first tracked line is exactly `zero-length:` and has no trailing space. Python terminated with `ValueError: not enough values to unpack (expected 2, got 1)`, exit `1`. Full command, source SHA-256 values, and diagnostic are retained in `../fuzz-results.md`.

No CMake configure/build completed. `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` were not executed. No sanitizer crash occurred because no fuzzer process started. This record does not request an independent G9 assessment or G9 approval.

## Requested action and acceptance criteria

The protocol orchestrator must preserve this failed attempt and, if it elects to continue, issue a fresh bounded fuzz-engineer execution assignment with a verified corpus conversion procedure. The new assignment must independently rebuild all three existing targets and run the specified one-at-a-time bounded campaign. Only after clean campaign evidence for every target exists may a future independent security-reviewer G9 assessment be routed.

## Resolution

Unresolved. `BLOCKED`; no destination review action is requested from this handoff.
