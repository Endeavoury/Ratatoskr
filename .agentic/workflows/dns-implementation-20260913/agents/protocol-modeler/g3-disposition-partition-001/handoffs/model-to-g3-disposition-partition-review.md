# Model-to-G3 handoff — DNS TCP disposition partition

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `DNS-HO-MODELER-G3-DISPOSITION-PARTITION-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-modeler` |
| Status | `READY_FOR_REVIEW` |
| Revision | Delivery commit and model SHA-256 are recorded in `completion-report.md`. |
| Source artifacts | Corrective G3 review/return handoff, approved analysis, and prior corrective model as listed below. |
| Assumptions | Existing approved profile and numerical-policy boundary remain unchanged. |
| Open questions | None. |
| Limitations | This requests a fresh independent G3 review; it does not approve G3 or authorize G4. |

## Routing

- **ID / workflow / stage:** `DNS-HO-MODELER-G3-DISPOSITION-PARTITION-001` / `dns-implementation-20260913` / modeling (G3).
- **Source role and assignment:** `protocol-modeler / g3-disposition-partition-001`.
- **Destination role:** fresh independent `protocol-api-designer` G3 reviewer.
- **Target:** `protocol/dns`.
- **Reason:** Review the ordered, exhaustive completed-correlated-TCP-frame disposition partition.
- **Blocking:** true.
- **Status:** `READY_FOR_REVIEW`.

## Source artifacts

- Corrective review and return handoff: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/reviews/g3-corrective-model-review.md` and `handoffs/g3-corrective-to-modeler-disposition-partition.md`, delivered at `4e8a6653146575b8e4ce57b7cd5927e5d80d8b9e`.
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- G2 model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/protocol-model.yaml` at `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, SHA-256 `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd`.
- Prior corrective model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/protocol-model.yaml` at `46dfcfe543c7591db963c606802cd7f0d147d35d`, SHA-256 `130e354e67a517870e3d826f54f323b38dc98716c14b272f22a4adf8d6aa1b7f`.

## Resolution supplied for review

1. `DOM-TCP-CORRELATED-DISPOSITION` makes the only completed-correlated-frame outcomes resource-limit, malformed, unsupported-extension, and publish; nonmatching frames are explicitly outside that domain.
2. `INV-TCP-CORRELATED-DISPOSITION-PARTITION` establishes observable precedence: resource-limit first, then malformed, then unsupported-extension, then publish. Each later test is evaluated only when earlier tests do not apply, making the four outcomes exhaustive and unambiguous without selecting any numerical limit.
3. The malformed guard excludes the structurally valid excluded OPT/EDNS case; unsupported-extension requires no resource-limit and otherwise-valid structure. Every terminal transition retains no-result publication and cleanup; `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025` trace to the new domain/invariant and transitions.

## Requested action

Perform one fresh independent G3 review of `protocol-model.yaml` after verifying this delivery. Verify that the stated precedence prevents overlap among the four completed correlated TCP-frame outcomes, preserves terminal cleanup/no-result effects, and does not add analysis, API/ABI, parser, or numerical-policy semantics. Do not author API design unless G3 passes and the orchestrator separately routes G4.

## Acceptance criteria

- Every completed correlated TCP frame has exactly one ordered disposition: terminal resource-limit, terminal malformed, terminal unsupported-extension, or publish.
- A completed nonmatching frame alone remains pending/ignored.
- A structurally valid excluded OPT/EDNS frame cannot be malformed or resource-limit under the same completed-frame classification; an exceeded configured resource limit takes the resource-limit disposition first.
- All terminal outcomes publish no result and clean up partial state, frame accumulator, request context, and transport buffers.
- `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025` remain traceable.
- The G3 disposition is written by a fresh independent `protocol-api-designer` reviewer.

## Resolution (destination role)

`protocol-api-designer / g3-disposition-review-001` independently reviewed the candidate model at Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`, and records **APPROVED**. `DOM-TCP-CORRELATED-DISPOSITION` and `INV-TCP-CORRELATED-DISPOSITION-PARTITION` establish resource-limit, malformed, unsupported-extension, then publish as an ordered exhaustive partition for completed correlated TCP frames. The nonmatching transition remains pending/ignored; malformed excludes structurally valid excluded OPT/EDNS; resource-limit takes precedence; terminal outcomes publish no result and clean partial records, accumulator, request context, and transport buffers. `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025` remain traceable. See `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md`.

Resolution status: `APPROVED`. Return only to `protocol-orchestrator` for delivery verification and state update; this resolution neither updates state nor routes G4 or any later stage.

## Closure (orchestrator after verification)

`protocol-orchestrator / g3-disposition-review-routing-001` verified the designated independent reviewer record and delivery `865fa190ee19e041c5ddfab8279b49829baaa240`, including reviewer identity/boundary, model Git `f26745472178649a60f2cb079937d1bbe3f13c0b`, model SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`, approved-analysis digest, delivery diff boundary, and exact origin readback. The reviewer approved G3; the orchestrator records this handoff `COMPLETE`, advances modeling/G3 to `APPROVED`, and removes `DNS-G3-MODEL-TCP-BLOCK`. This closure does not approve G4. See `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g4-api-design-routing-001/g3-state-closure-verification.md`.