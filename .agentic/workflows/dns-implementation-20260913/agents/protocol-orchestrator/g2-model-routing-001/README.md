# DNS G2 model-routing assignment

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Assignment | `g2-model-routing-001` |
| Active role | `protocol-orchestrator` |
| Scope | Route independent G2 analysis review; conditionally route a semantic-model candidate only after G2 approval. |
| Repository root / command directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Owned paths | This workspace; workflow-root `workflow-state.yaml` only for verified routing/disposition. |
| Forbidden | Specialist truth, source, tests, vectors, API design, shared request/manifest changes. |

The designated independent child is `protocol-modeler/g2-model-001`. It owns its review, any conditional model candidate, decisions/handoffs, and completion report. The orchestrator alone verifies its delivery and advances shared state.
