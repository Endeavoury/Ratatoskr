# G9 full campaign execution 004

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-004-workspace` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-full-campaign-execution-004` |
| Status | `BLOCKED` |
| Tested revision | `git:b82ea8499600c3ef7ab1e51fa297b477b1f17c1c` |

## Scope

One local-only LLVM19 campaign over the existing `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` targets. Repository writes are limited to the five assigned files in this workspace. Build, copied corpus, converter, wrapper, and full logs are under `/tmp/ratatoskr-g9-full-campaign-execution-004*`.

## Preconditions

- Repository root, origin, and branch: `/home/hermes/hermes-workspace/projects/Ratatoskr`; `https://github.com/Endeavoury/Ratatoskr.git`; `hermes/dns-implementation-20260913`.
- Local HEAD and fetched `origin/hermes/dns-implementation-20260913`: `b82ea8499600c3ef7ab1e51fa297b477b1f17c1c`.
- Committed dispatch packet `464702783c7174212644a4d6416a72958c057cae` is an ancestor of both local HEAD and fetched origin.
- G7 and G8 records are `APPROVED`; workflow G9 was `IN_PROGRESS`, not approved. No live target worker was found (the only matching process was the preflight command itself).
- Required source and harness SHA-256 values matched the packet; versioned Clang 19.1.7, CMake 3.31.6, Ninja 1.12.1, GNU timeout 9.7, and matching LLVM19 fuzzer/ASan/UBSan archives were present.
- Pre-existing untracked artifacts were preserved; tracked worktree was clean before assigned writes.

## Outcome

Packet and name completed cleanly. Record returned 71 with an explicit libFuzzer out-of-memory diagnostic under the mandatory 1024 MiB RSS budget. Campaign stopped immediately; this workspace does not approve G9 or route security review.

See `fuzz-plan.md`, `fuzz-results.md`, the handoff, and `completion-report.md` for evidence and disposition.
