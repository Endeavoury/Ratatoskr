# G3 return handoff — DNS TCP semantic completeness

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-handoff-api-001-to-modeler-g3-tcp` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-api-designer |
| Status | CHANGES_REQUESTED |
| Revision | Authored handoff; delivery commit and content digest are recorded in `completion-report.md`. |
| Source artifacts | G3 review and immutable G2 model input identified below. |
| Assumptions | The approved scope remains UDP-first standard unicast DNS with TCP fallback only after correlated UDP TC. |
| Open questions | None needed to resolve the two model gaps; existing numerical policy questions remain owned by API/product scope. |
| Limitations | The source reviewer cannot edit the protocol-modeler workspace or shared state. |

## Routing

- **ID / workflow / stage:** `DNS-HO-API-001-G3-TCP` / `dns-implementation-20260913` / modeling (G3).
- **Source role and assignment:** protocol-api-designer / `g3-api-001`.
- **Destination role:** protocol-modeler / `g2-model-001` (or a newly assigned modeler revision workspace).
- **Target:** `protocol/dns`.
- **Reason:** The G3 review found two semantic-model omissions affecting required TCP framing and error outcomes.
- **Blocking:** true.
- **Status:** CHANGES_REQUESTED.

## Source artifacts

- Review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/reviews/g3-model-review.md`.
- Model under review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/protocol-model.yaml` at `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`, blob `07d2096667cd6c150ba37bf6c19976ef75f30272`, SHA-256 `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd`.
- Approved interpretation: analysis `DNS-REQ-019` and `DNS-REQ-023` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.

## Specific problem

1. `DOM-CONSUMPTION` defines `need-more-input` as no consumption, but `TR-TCP-NEED-MORE` says available frame bytes are consumed. DNS-REQ-019 requires an incremental prefix/body consumption contract. The model must make its observable input consumption and accumulator ownership unambiguous.
2. For a completed TCP frame that is correlated but whose DNS message is malformed, exceeds a configured parsing limit, or contains recognized-but-excluded OPT/EDNS material, the model has no transition. `TR-TCP-INVALID-FRAME` only covers prefix length/limit and EOF; `TR-TCP-IGNORE-NONMATCHING` is not applicable; `TR-TCP-PUBLISH` requires structural validity. DNS-REQ-019, DNS-REQ-023, DNS-REQ-024, and DNS-REQ-025 require an explicit safe terminal outcome.

## Requested action

Revise the model in the modeler-owned workspace without introducing native API, ABI, or parser-algorithm coupling:

1. Define one consumption model for `EVT-TCP-BYTES`/`STR-TCP-DNS-FRAME`: what is accepted from the caller, what remains unconsumed after need-more-input and after one emitted frame, and what bytes are owned by the frame accumulator.
2. Add explicit transitions/error classes for completed correlated TCP frames that fail structural parse, hit resource limits, or encounter a supported-to-recognize but excluded OPT/EDNS extension. Each must discard partial content, release context/buffers, publish no result, and reach the appropriate terminal state.
3. Update requirement traceability and model-level handoff/completion evidence. If any requirement interpretation must change, return to protocol-analyst / `analysis-001`; do not decide it locally.

## Acceptance criteria

- A new immutable model revision maps DNS-REQ-019, 023, 024, and 025 to unambiguous TCP transitions/effects.
- Need-more-input and one-frame outcomes have nonconflicting consumption/remaining-input semantics.
- Every completed correlated TCP frame has a defined disposition: publish, terminal malformed/resource/unsupported-extension, or (only if correlation fails) ignore while pending.
- Atomic publication and terminal cleanup remain explicit.
- An independent protocol-api-designer G3 review verifies the revised model before any G4 candidate is authored.

## Resolution (destination role)

Reserved for the modeler. Set READY_FOR_REVIEW only after recording revised paths and exact immutable revisions.

## Closure (orchestrator after verification)

Reserved for protocol-orchestrator after verifying the modeler resolution and routing a fresh independent G3 review.
