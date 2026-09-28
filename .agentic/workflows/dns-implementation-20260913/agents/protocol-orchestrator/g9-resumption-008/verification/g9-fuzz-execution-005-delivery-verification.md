# G9 fuzz execution 005 delivery verification

| Field | Verified value |
| --- | --- |
| Routing commit | `bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15` |
| Leaf delivery commit | `419992875eac88839a29efca0b06552bd02ae326` |
| Parent | `bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15` |
| Exact remote ref readback | `refs/heads/hermes/dns-implementation-20260913 = 419992875eac88839a29efca0b06552bd02ae326` |
| Leaf disposition | `BLOCKED` |
| G9 security review | Not routed |

ACTIVE ROLE: `protocol-orchestrator`.

The four required leaf outputs exist. The verified delivery diff from the routing commit adds exactly the four assigned `fuzz-engineer/g9-fuzz-execution-005` artifacts and no shared source, corpus, CMake, test, state, documentation, or other workspace path. `git diff --check` passed. The child verified its packet and campaign-source ancestor conditions, fixed corpus/harness/CMake digests, and built all three existing LLVM19 targets.

Campaign evidence is blocking: `ratos_fuzz_dns_packet` was clean (91 seconds, 572,748 runs), while `ratos_fuzz_dns_name` immediately reported UBSan index 1024 out-of-bounds at `fuzz/dns/fuzz_dns_name.c:12:32` and ASan stack-buffer-overflow. The mandatory stop policy correctly prevented execution of `ratos_fuzz_dns_record`. The crash input is retained only under `/tmp`, and no repository source or corpus was modified. This is not approvable G9 evidence; the leaf handoff correctly requests no G9 security review.
