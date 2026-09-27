# Handoff: G9 name-harness remediation

| Field | Value |
| --- | --- |
| ID | `dns-implementation-20260913-g9-name-harness-remediation-001` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9 corrective harness stage) |
| Source / destination | `fuzz-engineer/g9-name-harness-remediation-001` → `protocol-orchestrator` |
| Target | `fuzz/dns/fuzz_dns_name.c` bound-safe harness remediation |
| Status | `READY_FOR_REVIEW` |
| Blocking | No for focused remediation review; G9 remains blocked pending fresh broader evidence |
| Source baseline | `git:f90c9bd80217cddb0e036d4dc0d8914f0cd32927` |

## Evidence and result

The authorized minimal fix changes the input copy cap from `sizeof(packet) - 16u` to `sizeof(packet) - 17u`. This limits `copied` to 1007, so the existing terminal writes through `16 + copied` remain within the 1024-byte packet. The focused LLVM 19 sanitizer build succeeded, and replay of a derived fixed 1,133-byte input exited 0 with no ASan/UBSan diagnostic.

See `fuzz-plan.md` and `fuzz-results.md` in this assignment workspace for exact commands, input SHA-256, build output, and scope limits.

## Requested action and acceptance criteria

Route only an independently assigned focused fuzz verification/review of this remediation. Accept the candidate only after the reviewer verifies the cap arithmetic, allowed-path boundary, exact build/replay evidence, and absence of sanitizer diagnostics. If accepted, the protocol orchestrator may separately decide whether to dispatch fresh bounded three-target G9 execution.

Do not route a G9 security review from this handoff. This assignment does not approve G9, and packet/record targets plus the full G9 campaign were not run.

## Resolution

Unresolved; owned by `protocol-orchestrator`.