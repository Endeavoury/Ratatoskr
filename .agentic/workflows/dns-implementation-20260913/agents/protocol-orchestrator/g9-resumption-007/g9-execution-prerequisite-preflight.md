# G9 resumption 007 — current execution-prerequisite preflight

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resumption-007-preflight` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Target / owner | `protocol/dns` / `protocol-orchestrator/g9-resumption-007` |
| Status | `BLOCKED` |
| Baseline checked | local and origin `git:f6d703bb8e7d8fbba88e722abb6e58e9c5c7b7c2` |
| Source artifacts | `workflow-state.yaml`; G7/G8 approvals; `g9-resumption-006`; `g9-resumption-013`; `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` |
| Assumptions | The mandatory G9 budget remains `-rss_limit_mb=1024`. Existing untracked paths predate this assignment and are preserved. |
| Limitations | Administrative prerequisite assessment only; no fuzz campaign, design, implementation, gate judgment, or state transition occurred. |

ACTIVE ROLE: `protocol-orchestrator`.

## Scope and repository verification

This one bounded resumption checks whether an eligible fresh G9 execution stage exists. All repository commands used `/home/hermes/hermes-workspace/projects/Ratatoskr`.

- Git root: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Origin: `https://github.com/Endeavoury/Ratatoskr.git`
- Branch: `hermes/dns-implementation-20260913`
- Local HEAD: `f6d703bb8e7d8fbba88e722abb6e58e9c5c7b7c2`
- Exact origin readback: `f6d703bb8e7d8fbba88e722abb6e58e9c5c7b7c2 refs/heads/hermes/dns-implementation-20260913`
- Working tree: only pre-existing unrelated untracked `.agentic` artifacts were present; none were reset, cleaned, staged, or changed.

`workflow-state.yaml` remains workflow/fuzzing/G9 `BLOCKED`; G7 and G8 are independently `APPROVED`. Historical `IN_PROGRESS` and `CHANGES_REQUESTED` entries were treated as historical artifacts, not live work. No live G9 fuzz-engineer execution was identified in the current state/evidence.

## Current toolchain evidence

The versioned LLVM toolchain prerequisite is now available:

- `/usr/bin/cmake`: CMake 3.31.6
- `/usr/bin/clang-19` and `/usr/bin/clang++-19`: Debian Clang 19.1.7
- `/usr/bin/ninja`: present
- Compiler resource directory: `/usr/lib/llvm-19/lib/clang/19`
- libFuzzer: `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.fuzzer-x86_64.a`
- ASan: `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.asan-x86_64.a`
- UBSan: `/usr/lib/llvm-19/lib/clang/19/lib/linux/libclang_rt.ubsan_standalone-x86_64.a`

The absent unversioned `clang`/`clang++` PATH aliases do not block the required CMake commands because the authorized workflow uses the verified absolute LLVM19 compiler paths. This clears only the former PATH/toolchain prerequisite.

## Blocking prerequisite and route decision

A fresh fuzz-engineer campaign is still ineligible. The durable handoff `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` remains `BLOCKED`, pending a maintainer/product numeric resource-policy decision. Its source evidence records the prior mandatory record-target failure: `ratos_fuzz_dns_record` exited 71 with libFuzzer `used: 1636Mb; limit: 1024Mb`, while the approved G9 campaign limit remains fixed at 1024 MiB.

No durable resolution provides the required numeric defaults/hard limits (or an explicit no-numeric-default-change decision), revision-bound corrective design candidate, exact authorized private paths, or fresh G6 authority assessment. Dispatching a new three-target campaign without those inputs would be speculative and could not satisfy G9. Therefore:

- No fuzz-engineer leaf was dispatched.
- No G9 security review, binding, or later-stage route was created.
- `workflow-state.yaml` remains unchanged and G9 remains `BLOCKED`.
- No quota or rate-limit condition occurred.

## Required unblock evidence

Maintainer/product must resolve `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` with concrete applicable limits or an explicit no-numeric-default-change decision. If a change is required, the responsible design owner must deliver a revision-bound candidate and exact private paths. The protocol orchestrator must then perform a fresh G6 authority assessment before any corrective specialist or fresh G9 fuzz-engineer dispatch.
