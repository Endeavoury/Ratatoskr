# G4 native API-design routing

| Field | Value |
| --- | --- |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Active role | `protocol-orchestrator` |
| Routing assignment | `g4-api-design-routing-001` |
| Leaf assignment / workspace | `protocol-api-designer / g4-api-design-001`; `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-api-design-001/` |
| Repository root / command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Delivery branch | `hermes/dns-implementation-20260913` only |
| Required packet | `delegations/protocol-api-designer-g4-api-design-001.md` |

## Preconditions

- G3/modeling is independently approved for model `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`, by reviewer delivery `865fa190ee19e041c5ddfab8279b49829baaa240`.
- This routing record and its packet are committed/pushed only as durable preparation. The sole G4 leaf is not dispatched until the G3 closure commit has an exact origin readback.
- G4 remains unapproved. The leaf may author only its workspace and must return `READY_FOR_REVIEW`; it may not modify headers or implementation, update state, self-approve G4, delegate, or route later work.

## Runtime policy

Requested leaf route: `gpt-5.6-sol` / medium. Parent runtime exposed `openai-codex` / `gpt-5.6-terra`; effective child route/effort and usage are unknown until the child reports them. No Hermes configuration is changed.
