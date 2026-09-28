# G4 compatibility re-review routing

| Field | Value |
| --- | --- |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Role / assignment | `protocol-orchestrator / g4-compatibility-rereview-routing-001` |
| Status | `IN_PROGRESS` — one routing stage only |
| Baseline | `fb766f3deb0bc0b549c612a5d59eee08d4992b3d` |
| Candidate | `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520` |

ACTIVE ROLE: `protocol-orchestrator`.

Scope: route exactly one fresh, independent `compatibility-reviewer` leaf to re-review the corrective C API design for `C-COMP-001`. This assignment is mandatory G4 support evidence and produces a G12-style disposition only; it cannot approve overall G4 or route G5/G6/later stages.

Owned writes are this unique workspace and workflow-root `workflow-state.yaml` only after leaf dispatch acceptance. The sole leaf owns only `.agentic/workflows/dns-implementation-20260913/agents/compatibility-reviewer/g4-compatibility-rereview-001/{README.md,compatibility-report.md,reviews/g12-g4-compatibility-rereview.md,handoffs/,completion-report.md}`. All other paths, including production, headers, tests, vectors, bindings, docs, request, manifest, every existing specialist workspace, and unrelated untracked `agents/binding-api-designer/g4-binding-safety-rereview-001/`, remain read-only.

`native_api_design` remains `IN_PROGRESS` and G4 remains `CHANGES_REQUESTED` until designated independent evidence is recorded and evaluated by the orchestrator. No technical review is performed in this routing workspace.