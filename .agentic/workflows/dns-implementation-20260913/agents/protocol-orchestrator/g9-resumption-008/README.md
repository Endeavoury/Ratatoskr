# G9 resumption 008 — dispatch reconciliation

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-resumption-008` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Owner | `protocol-orchestrator` |
| Status | `COMPLETE` for routing reconciliation; G9 remains unapproved pending leaf evidence |
| Reconciled campaign-source baseline | `git:400e818790bf6a8e7f13b7b86cfaf837a11066fc` |
| Required delivery branch | `hermes/dns-implementation-20260913` |

ACTIVE ROLE: `protocol-orchestrator`.

This workspace resolves `G9-FUZZ-BASELINE-001`. The exact campaign-source baseline is the pre-dispatch verified branch tip `400e818790bf6a8e7f13b7b86cfaf837a11066fc`. The leaf must not require `HEAD ==` that pre-dispatch commit. Instead, it must require both that this committed packet is an ancestor of its execution HEAD and that the campaign-source baseline is an ancestor of its execution HEAD, then verify the fixed input digests. This remains valid after this routing commit and the leaf's own evidence-delivery commit.

Only the fresh leaf `fuzz-engineer/g9-fuzz-execution-005` is authorized. It may write exactly its four assigned artifacts, build and execute only the three existing local DNS fuzz targets using an ephemeral `/tmp` build and derived copy of the fixed repository corpus, and must otherwise remain local-only. No G9 security review or later stage is authorized by this workspace.

Historical G9 `IN_PROGRESS`, `CHANGES_REQUESTED`, `BLOCKED`, and `SUPERSEDED` records are completed history, not live work. Pre-existing untracked paths are unrelated and must be preserved.
