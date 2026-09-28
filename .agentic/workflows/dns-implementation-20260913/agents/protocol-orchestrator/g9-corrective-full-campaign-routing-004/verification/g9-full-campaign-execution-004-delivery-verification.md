# G9 full-campaign execution 004 delivery verification

| Check | Result |
| --- | --- |
| Leaf identity | Fresh nested `fuzz-engineer` leaf `deleg_95c1c5fc/task-0` |
| Leaf delivery / origin readback | `edfde9410eb78ac9dd816136e57651d5e863c330` / same |
| Baseline ancestry | Routing commit `b82ea8499600c3ef7ab1e51fa297b477b1f17c1c` is the tested revision; leaf delivery is present at the fetched target ref |
| Delivery boundary | Exactly the five assigned fuzz-engineer workspace files; no source, harness, tracked corpus, CMake, test, API, workflow-state, or other workspace file |
| Diff integrity | `git diff --check b82ea84..edfde94` passed |
| Campaign result | Packet clean (0, 91.1975008812733s); name clean (0, 91.17736798198894s); record returned 71 after 10.101190892979503s with libFuzzer out-of-memory under unchanged `-rss_limit_mb=1024` |
| Disposition | `BLOCKED`; no retry, correction, G9 approval, security-review routing, or later role |

The leaf used the specified LLVM19 configure/build, first-colon `seeds.txt` conversion, fresh corpus per target, and exact bounded target arguments. It delivered all five required artifacts. The record resource failure is preserved as factual G9 blocking evidence; it is not a diagnosis or authorization for a fix.
