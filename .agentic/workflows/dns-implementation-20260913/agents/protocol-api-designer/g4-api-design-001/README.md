# DNS G4 native API design workspace

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g4-api-design-001` |
| Workflow / stage | `dns-implementation-20260913` / `native_api_design` (G4) |
| Target | `protocol/dns` |
| Active role | `protocol-api-designer` |
| Status | `READY_FOR_REVIEW` candidate; not G4 approval |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Owned workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/` |
| Allowed writes | This README, `api-design.md`, `decisions/`, `handoffs/`, and `completion-report.md` only |

## Scope

This workspace proposes a native C ABI design for the approved UDP-first DNS unicast stub/client semantic model. It does not modify public headers, source, tests, vectors, bindings, documentation, configuration, workflow state, or later-stage artifacts.

## Verified inputs

- G3 approval: `agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md` at delivery `865fa190ee19e041c5ddfab8279b49829baaa240`, explicitly `APPROVED`.
- Approved model: `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- Approved analysis: `agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Closure evidence: `agents/protocol-orchestrator/g4-api-design-routing-001/g3-state-closure-verification.md` records remote G3 closure and an `APPROVED` disposition.
- Current remote delivery ref readback before authoring: `fb78a0c8fff656154f39b46108250f2383925df3 refs/heads/hermes/dns-implementation-20260913`.

The current files were byte-identical to these approved inputs. Existing ABI inputs were also byte-identical to their packet revisions.

## Handoff

`protocol-orchestrator` must verify this candidate and route the designated independent G4 review. The author does not approve G4 or route a later stage.