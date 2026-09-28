# Blocking handoff: G9 fuzz execution 005

| Field | Value |
| --- | --- |
| ID | `dns-implementation-20260913-g9-fuzz-execution-005-blocker` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Source / destination | `fuzz-engineer/g9-fuzz-execution-005` → `protocol-orchestrator` |
| Target | DNS fuzz campaign evidence |
| Status | `BLOCKED` |
| Blocking | Yes |
| Source revision | dispatch/packet `git:bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15`; campaign baseline ancestor `git:400e818790bf6a8e7f13b7b86cfaf837a11066fc` |

## Reason and evidence

The required serial campaign stopped at `ratos_fuzz_dns_name` with UBSan and ASan evidence in the existing fuzz harness: `fuzz/dns/fuzz_dns_name.c:12:32` writes index 1024 of `uint8_t packet[1024]`, producing an AddressSanitizer stack-buffer-overflow. The initial fixed corpus was strictly converted only under `/tmp`; after the clean packet run it had libFuzzer-derived entries, and the name target loaded 292 entries before crashing during seed-corpus execution.

`ratos_fuzz_dns_packet` completed cleanly in 91 seconds (572,748 runs; final RSS 329 MB) under the required flags. The name target exited 1 in less than one second. `ratos_fuzz_dns_record` was not run and will not be run in this attempt, per immediate-stop policy. The crash input is retained only at `/tmp/ratatoskr-g9-fuzz-execution-005/name-crash-7d5929dc5a1559f575eda5f7bbe6f49ae0fbe721`, SHA-256 `f311b05d472cc851617730ec235289edb0b18777d06325477a601eff164ea01a`.

## Owner and requested action

The failing path is the pre-existing name fuzz harness; its role owner is `fuzz-engineer`, but this execution packet authorizes no harness/source change. `protocol-orchestrator` must verify this evidence and, if still desired, issue a separately scoped remediation assignment. Do **not** route G9 security review, approve G9, or route later work from this blocked result.

## Acceptance criteria for resolution

A future authorized owner must correct the harness boundary, independently validate the correction, and receive a fresh bounded execution assignment with new evidence for all three targets. This assignment is complete as a blocker report; it requests no review now.

## Resolution

Unresolved. Only `protocol-orchestrator` may record the coordination outcome.
