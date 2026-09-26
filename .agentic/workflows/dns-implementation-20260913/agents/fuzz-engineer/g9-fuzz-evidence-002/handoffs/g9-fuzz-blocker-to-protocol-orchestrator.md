# G9 fuzz evidence blocker: baseline mismatch

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-engineer-g9-fuzz-evidence-002-baseline-blocker` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` parser robustness |
| Owner role | `fuzz-engineer/g9-fuzz-evidence-002` |
| Status | `BLOCKED` |
| Revision | Observed local `git:195e096034f0e475a92ab35a047012cfc3962ce4`; packet-required `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3` |
| Source artifacts | Delegation `agents/protocol-orchestrator/g9-resumption-007/delegations/fuzz-engineer-g9-fuzz-evidence-002.md`; G7 and G8 approvals named there; toolchain preflight `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md` |
| Assumptions | Pre-existing untracked paths are unrelated and were preserved. |
| Open questions | Which immutable baseline and replacement dispatch packet govern the G9 campaign? Owner: `protocol-orchestrator`. |
| Limitations | No CMake configuration, build, or fuzz execution occurred; no build/run logs or sanitizer diagnostics exist. |

## Routing
- ID / workflow / stage: `G9-FUZZ-BASELINE-001` / `dns-implementation-20260913` / `fuzzing` (G9)
- Source role and assignment: `fuzz-engineer/g9-fuzz-evidence-002`
- Destination role: `protocol-orchestrator`
- Target protocol/binding/component: `protocol/dns` parser fuzz evidence
- Reason: Required baseline check failed before the permitted campaign.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts
- Delegation packet section “Required baseline and commands” requires local `HEAD` exactly `f37171a33e62f2ad2c1440ce41295a22596c5ee3` and explicitly directs stop-and-handoff otherwise.
- Command executed from `/home/hermes/hermes-workspace/projects/Ratatoskr`:
  ```text
  git rev-parse HEAD
  ```
  Observed: `195e096034f0e475a92ab35a047012cfc3962ce4`.
- Read-only verification also confirmed branch `hermes/dns-implementation-20260913`, repository root, LLVM 19/CMake/Ninja availability, and a clean tracked diff. Existing unrelated untracked paths were not changed.

## Specific problem or question
The packet’s mandatory baseline does not match the actual local `HEAD`. The safety envelope prohibits fuzz execution after this mismatch, and this role cannot alter the dispatch packet, shared workflow state, checkout, or baseline.

## Requested action
`protocol-orchestrator` must reconcile the authoritative G9 baseline and issue a new or corrected fresh fuzz-engineer dispatch that names the exact immutable revision available for execution. Preserve this blocker and do not treat it as campaign evidence.

## Acceptance criteria
- A protocol-orchestrator artifact identifies one exact G9 campaign baseline and reconciles it with the workflow state and supplied dispatch context.
- A fresh packet passes its required local `HEAD` check before any build or execution.
- The rerouted fuzz-engineer assignment retains the existing three-target, fixed-corpus, bounded local-only safety envelope.

## Resolution (destination role)
Pending protocol-orchestrator action.

## Closure (orchestrator after verification)
Pending.
