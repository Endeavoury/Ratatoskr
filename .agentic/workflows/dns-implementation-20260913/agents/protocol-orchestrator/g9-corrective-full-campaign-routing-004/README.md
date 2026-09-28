# G9 corrective full-campaign routing 004

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-corrective-full-campaign-routing-004` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner | `protocol-orchestrator/g9-corrective-full-campaign-routing-004` |
| Status | `IN_PROGRESS` — one fresh leaf dispatched after routing delivery |
| Baseline observed | `git:464702783c7174212644a4d6416a72958c057cae` |
| Repository / branch | `/home/hermes/hermes-workspace/projects/Ratatoskr` / `hermes/dns-implementation-20260913` |

ACTIVE ROLE: `protocol-orchestrator`.

## Scope

This is exactly one corrective G9 execution route. It authorizes one fresh `fuzz-engineer/g9-full-campaign-execution-004` leaf to run the existing local DNS packet, name, and record fuzz targets under the recorded bounded campaign. It does not authorize source, harness, CMake, corpus, API, test, review, binding, documentation, or security-review work.

## Pre-dispatch facts

- Local HEAD and `origin/hermes/dns-implementation-20260913` both resolved to `464702783c7174212644a4d6416a72958c057cae`; origin is `https://github.com/Endeavoury/Ratatoskr.git`.
- G7 and G8 are `APPROVED`; workflow/fuzzing/G9 were `BLOCKED` before this fresh dispatch.
- No live DNS fuzzer or G9 fuzz-engineer process was observed. Historical G9 records, including prior blocked executions, are evidence only, not live workers.
- LLVM 19 preflight establishes `/usr/bin/clang-19` and `/usr/bin/clang++-19` with matching libFuzzer/ASan/UBSan runtimes. Current fixed corpus and three existing harness/CMake SHA-256 values match the approved packet inputs.
- The requested corrective stage explicitly supersedes the former colon-space decoder failure: the leaf must split each seed line at its first colon and must accept `zero-length:`.

## Boundaries and next step

The orchestrator owns only this workspace and the minimal fresh-dispatch state reflection. The leaf owns only its new workspace and `/tmp` evidence. A clean leaf result is `READY_FOR_REVIEW`, never G9 approval; the next permitted role only after verified clean results is an independent `security-reviewer` for G9. Any toolchain, provenance, build, sanitizer, timeout, nonzero, or RSS failure remains factual `BLOCKED` evidence with no retry or fix.
