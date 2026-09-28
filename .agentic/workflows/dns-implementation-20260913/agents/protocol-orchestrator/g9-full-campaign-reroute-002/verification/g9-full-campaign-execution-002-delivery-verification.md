# Leaf delivery verification — G9 full campaign execution 002

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-reroute-002-leaf-verification` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner | `protocol-orchestrator/g9-full-campaign-reroute-002` |
| Status | `COMPLETE` — administrative receipt; no technical G9 approval |
| Routed baseline | `90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Leaf delivery / exact origin readback | `797617e7e2194afa6fe80398b89550a3bf0b0694` |

## Verified delivery boundary

`90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` is an ancestor of the leaf delivery. Exact delivery diff contains only the four authorized leaf outputs:

- `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-plan.md`
- `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md`
- `agents/fuzz-engineer/g9-full-campaign-execution-002/handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
- `agents/fuzz-engineer/g9-full-campaign-execution-002/completion-report.md`

`git diff --check` over that delivery range passed. Local HEAD and `origin` exact ref both read back as `797617e7e2194afa6fe80398b89550a3bf0b0694`. Pre-existing unrelated untracked paths remain present.

## Verified campaign disposition

The leaf built only the three specified existing LLVM19 targets and used the corrected portable wrapper: `/usr/bin/python3` monotonic timing plus `resource.getrusage(RUSAGE_CHILDREN)` around `/usr/bin/timeout 120s`; it did not invoke absent `/usr/bin/time`. Required corpus/provenance digests and build passed. Packet and name completed cleanly (91.12561804009601s/360620 KiB and 91.17745899502188s/454032 KiB). Record stopped once, with return 71 after 21.236172719858587s and `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`; `ru_maxrss` was 1,675,884 KiB.

This is a mandatory resource failure under the preserved `-rss_limit_mb=1024` budget. The leaf stopped without retry, additional work, or security-review dispatch and submitted a blocking handoff to this role. G9 remains `BLOCKED`; no independent G9 security reviewer is assigned or approved.