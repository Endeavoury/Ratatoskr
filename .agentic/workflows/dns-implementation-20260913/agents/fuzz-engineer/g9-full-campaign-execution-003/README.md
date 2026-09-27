# G9 full DNS fuzz campaign execution 003

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-003` |
| Workflow / stage / target | `dns-implementation-20260913` / fuzzing (G9) / `protocol/dns` |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-full-campaign-execution-003` |
| Status | `BLOCKED` |
| Required baseline | `git:0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4` |
| Observed local HEAD / origin ref | `git:7b92dcb393881d7b98a15289bb98ce52317eba73` / `git:7b92dcb393881d7b98a15289bb98ce52317eba73` |

## Scope and outcome

The committed packet required all local and fetched target refs to equal the stated baseline before any campaign write or target launch. Both observed refs instead equal the later delivery revision above, not the required baseline. Per the packet stop rule, this workspace records the baseline/ref divergence only. No `/tmp/ratatoskr-g9-full-campaign-execution-003*` directory was created; no corpus conversion, CMake configure/build, fuzz target execution, source/CMake/corpus change, workflow-state change, review, or remediation occurred.

The pre-existing unrelated untracked paths observed before this workspace were preserved. G7 and G8 are `APPROVED`; workflow/fuzzing/G9 remains `BLOCKED`.

## Model telemetry

Requested: `openai-codex/gpt-5.6-terra`, medium. Observed runtime: `openai-codex/gpt-5.6-terra`; reasoning effort and usage telemetry: unknown.
