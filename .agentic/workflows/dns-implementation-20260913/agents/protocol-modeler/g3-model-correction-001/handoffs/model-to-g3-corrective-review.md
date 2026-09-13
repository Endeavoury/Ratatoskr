# Model-to-G3 handoff — DNS TCP semantic correction

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-handoff-modeler-g3-correction-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-modeler |
| Status | READY_FOR_REVIEW |
| Revision | Local corrective candidate; final content digest is recorded in `completion-report.md`; Git delivery is blocked by absent verified `git-agent`. |
| Source artifacts | G3 review/return handoff plus approved analysis and G2 model listed below. |
| Assumptions | No numerical resource policy is selected; the existing UDP-first, TCP-after-correlated-TC profile remains unchanged. |
| Open questions | None for this correction. |
| Limitations | This handoff requests a fresh independent G3 review; it does not approve G3 or authorize G4. |

## Routing

- **ID / workflow / stage:** `DNS-HO-MODELER-001-G3-CORRECTIVE` / `dns-implementation-20260913` / modeling (G3).
- **Source role and assignment:** protocol-modeler / `g3-model-correction-001`.
- **Destination role:** independent protocol-api-designer / fresh G3 review assignment.
- **Target:** `protocol/dns`.
- **Reason:** Correct the two G3 findings without changing requirements or introducing ABI/parser semantics.
- **Blocking:** true.
- **Status:** READY_FOR_REVIEW.

## Source artifacts

- G3 review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/reviews/g3-model-review.md` at delivery commit `0fa10145698994fcdb2e3a6004cd8e6a356b96f7`.
- Return handoff: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/handoffs/g3-to-modeler-tcp-semantics.md` at delivery commit `0fa10145698994fcdb2e3a6004cd8e6a356b96f7`.
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Prior G2 model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/protocol-model.yaml` at `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, SHA-256 `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd`.
- Corrective model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/protocol-model.yaml`; local SHA-256 recorded in `completion-report.md`.

## Resolution supplied for review

1. `DOM-CONSUMPTION`, `ENT-FRAME-ACCUMULATOR`, `EVT-TCP-BYTES`, and `STR-TCP-DNS-FRAME` now specify a single observable contract: accepted leading caller bytes transfer to the accumulator; need-more accepts all supplied incomplete frame bytes and leaves no caller remainder; one-frame outcomes accept only prefix plus declared body and leave the suffix as caller input.
2. `TR-TCP-CORRELATED-MALFORMED`, `TR-TCP-CORRELATED-RESOURCE-LIMIT`, and `TR-TCP-CORRELATED-UNSUPPORTED-EXTENSION` explicitly terminate completed correlated frames with the matching error class, no result, discarded partial/frame state, and released context/buffers. Nonmatching complete frames remain pending-only; valid correlated frames publish atomically.
3. Traceability for `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025` references the corrected domains, transitions, errors, and cleanup invariant.

## Requested action

Perform one fresh independent G3 review of the corrective model after a verified wrapper delivers the authorized paths. Verify the consumption contract and every completed correlated-frame disposition against the approved analysis and return finding. Do not author API design unless G3 passes and the orchestrator separately routes G4.

## Acceptance criteria

- The reviewer finds no contradictory need-more/one-frame consumption or remaining-input semantics.
- Every completed correlated frame is either published, terminal malformed, terminal resource-limit, or terminal unsupported-extension; only a nonmatching frame is ignored while pending.
- Terminal error transitions explicitly retain no partial result and clean up context/buffers.
- G3 disposition is recorded by an independent protocol-api-designer.

## Resolution (destination role)

Reserved for the independent G3 reviewer.

## Closure (orchestrator after verification)

Reserved for protocol-orchestrator after verifying delivery and reviewer independence.
