# Handoff: G9 campaign baseline/ref divergence

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-003-handoff` |
| Workflow / stage | `dns-implementation-20260913` / G9 fuzzing |
| Source / destination | `fuzz-engineer/g9-full-campaign-execution-003` → `protocol-orchestrator/g9-resumption-011` |
| Target | `protocol/dns` |
| Status | `BLOCKED` |
| Blocking | true |

## Finding and evidence

The packet requires local HEAD, fetched `origin/hermes/dns-implementation-20260913`, and baseline to all equal `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4` before campaign work. After fetch, local HEAD and origin ref both equal `7b92dcb393881d7b98a15289bb98ce52317eba73`. This is a baseline/ref divergence. Repository root, origin URL, branch, G7/G8 approval state, toolchain availability, and six input SHA-256 values were otherwise checked and recorded in this workspace.

## Action taken

Stopped before corpus derivation, configure/build, and all three target launches. No `/tmp` campaign evidence exists because the stop occurred before campaign activity. No source, repository corpus, CMake, workflow state, or unrelated untracked path was modified.

## Requested action and acceptance

`protocol-orchestrator/g9-resumption-011` must reconcile the packet’s required baseline with the delivered branch/ref and issue a new unambiguous bounded assignment if execution remains authorized. Do not treat this handoff as G9 evidence, route a G9 security review, or infer target cleanliness. A successor must independently repeat integrity checks and run a new campaign only when its baseline/ref conditions hold.

## Resolution

Pending destination action.
