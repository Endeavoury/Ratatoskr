# G9 full campaign execution 003 delivery verification

ACTIVE ROLE: `protocol-orchestrator`.

| Field | Verified value |
| --- | --- |
| Dispatch-packet delivery | `7b92dcb393881d7b98a15289bb98ce52317eba73` |
| Leaf delivery / exact fetched origin ref | `e03dd0da18ccfb9d308b7ad5bd758116b9a7b955` |
| Leaf disposition | `BLOCKED` before campaign execution |
| Workflow / G9 outcome | remains `BLOCKED` |

Receipt verification passed for delivery integrity but confirms the leaf correctly stopped under an internally inconsistent baseline condition: its packet required local HEAD and fetched origin to equal the pre-packet baseline `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4`, while the orchestrator had necessarily delivered the packet at `7b92dcb393881d7b98a15289bb98ce52317eba73`. The leaf independently observed local and fetched origin both at that packet delivery revision and made no campaign attempt.

Fetched origin readback is exactly `e03dd0da18ccfb9d308b7ad5bd758116b9a7b955`. From the packet delivery revision to the leaf delivery, `git diff --name-only` contains exactly the five assigned leaf files: `README.md`, `fuzz-plan.md`, `fuzz-results.md`, `handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`, and `completion-report.md` in `agents/fuzz-engineer/g9-full-campaign-execution-003/`. `git diff --check 7b92dcb..e03dd0` passed.

The records show toolchain/corpus prerequisites were available and input digests were checked, but no `/tmp` derived corpus, configure/build, packet/name/record target run, sanitizer observation, or resource result exists. No source, repository corpus, CMake, workflow state, or unrelated untracked path was changed by the leaf. This is not G9 campaign evidence and no G9 technical approval, security review, bindings, or later-stage route is inferred.