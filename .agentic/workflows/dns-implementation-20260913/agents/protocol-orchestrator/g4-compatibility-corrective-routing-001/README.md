# G4 compatibility corrective routing

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Assignment | `g4-compatibility-corrective-routing-001` |
| Active role | `protocol-orchestrator` |
| Scope | One design-only corrective response to compatibility finding `C-COMP-001` |
| Command directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline before routing | `0cb6e27b265c38e42d09d61c0883f1a086df8835` |

No production, header, test, vector, binding, fuzzing, documentation, or review work is authorized. The only routed child is a fresh `protocol-api-designer` leaf in `g4-compatibility-remediation-001`. G4 remains `CHANGES_REQUESTED`; `native_api_design` remains `IN_PROGRESS` pending verified child delivery and a separately assigned fresh compatibility re-review.

The pre-existing untracked `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-rereview-001/` is unrelated and preserved.