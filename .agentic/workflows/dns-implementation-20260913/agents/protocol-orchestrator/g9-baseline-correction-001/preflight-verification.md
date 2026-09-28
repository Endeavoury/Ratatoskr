# G9 dispatch baseline correction — preflight verification

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-baseline-correction-001-preflight` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner role | `protocol-orchestrator/g9-baseline-correction-001` |
| Status | `READY_TO_COMMIT` |
| Verified local revision | `f4a3d9a1dc8faca3e8cca2ce87d4af4e64f328ba` |
| Verified remote-tracking revision | `origin/hermes/dns-implementation-20260913 = f4a3d9a1dc8faca3e8cca2ce87d4af4e64f328ba` |
| Checked at | `2026-09-27T02:00:55+02:00` |

## Finding

The pending `g9-fuzz-execution-002` packet declares dispatch baseline
`f37171a33e62f2ad2c1440ce41295a22596c5ee3`, while verified current local and
remote-tracking heads are `f4a3d9a1dc8faca3e8cca2ce87d4af4e64f328ba`. Its
start-at-HEAD equality precondition therefore cannot pass. It is superseded for
routing only; no existing blocked evidence is deleted or modified.

## Recorded correction

This commit changes only the workflow state and this orchestrator verification to
supersede the mistaken pending assignment and reserve a distinct fresh assignment
`g9-fuzz-execution-003`. After this commit is pushed and its exact remote ref is
read back, its commit ID will be the sole baseline placed in the freshly created
packet. The packet will not be dispatched unless a just-before-dispatch HEAD check
equals that recorded baseline.

## Preconditions already verified

- G7 and G8 are recorded APPROVED in `workflow-state.yaml`.
- LLVM 19 preflight is recorded at
  `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`.
- The authorized Git wrapper exists and is executable.
- Existing untracked paths, including the partial `g9-fuzz-execution-002/`
  workspace, are preserved and excluded from staging.

## Gate status

G9 remains `IN_PROGRESS`, unapproved. No G9 security review or later stage is
routed by this correction.
