# G3 return handoff — DNS TCP completed-frame disposition partition

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `DNS-HO-API-G3-CORRECTIVE-001-DISPOSITION-PARTITION` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `CHANGES_REQUESTED` |
| Revision | Reviewer handoff; delivery revision recorded in `completion-report.md`. |
| Source artifacts | G3 corrective review of model delivery `46dfcfe543c7591db963c606802cd7f0d147d35d`. |
| Assumptions | Existing approved profile and numerical-policy boundaries remain unchanged. |
| Open questions | None. |
| Limitations | The reviewer cannot edit the model or shared workflow state. |

## Routing

- **ID / workflow / stage:** `DNS-HO-API-G3-CORRECTIVE-001-DISPOSITION-PARTITION` / `dns-implementation-20260913` / modeling (G3).
- **Source role and assignment:** `protocol-api-designer / g3-corrective-review-001`.
- **Destination role:** `protocol-modeler` only.
- **Target protocol/binding/component:** `protocol/dns`.
- **Reason:** Completed correlated TCP-frame terminal classifications in the corrective model overlap, so exactly-one disposition is not established.
- **Blocking:** true.
- **Status:** `CHANGES_REQUESTED`.

## Source artifacts

- Corrected candidate: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/protocol-model.yaml` at `46dfcfe543c7591db963c606802cd7f0d147d35d`, SHA-256 `130e354e67a517870e3d826f54f323b38dc98716c14b272f22a4adf8d6aa1b7f`.
- Corrective review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/reviews/g3-corrective-model-review.md`.
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`, especially `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025`.
- Prior G3 finding: `g3-api-001/reviews/g3-model-review.md` at `0fa10145698994fcdb2e3a6004cd8e6a356b96f7`.

## Specific problem or question

`TR-TCP-CORRELATED-MALFORMED` covers failure of an “accepted profile rule,” while `TR-TCP-CORRELATED-UNSUPPORTED-EXTENSION` covers a structurally recognized excluded OPT/EDNS frame. The model does not make these guards disjoint or define which one applies when both descriptions hold. `TR-TCP-CORRELATED-RESOURCE-LIMIT` also lacks an explicit exclusion/precedence relation to the other completed-correlated-frame classifications. This fails the prior G3 requirement that every completed correlated frame have exactly one disposition.

## Requested action

Revise only modeler-owned semantic-model and modeler supporting records. Define mutually exclusive classifications or explicit semantic precedence for completed correlated TCP frames, covering publish, malformed, resource-limit, and unsupported-extension. Do not change approved analysis, add API/ABI/parser details, select numerical policy, or route later stages.

## Acceptance criteria

- The revised model makes the four completed-correlated-frame outcomes pairwise unambiguous and exhaustive for the approved profile.
- Only nonmatching completed frames remain pending/ignored.
- Terminal classifications retain no partial result and terminal cleanup.
- `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025` remain traceable.
- A fresh independent `protocol-api-designer` G3 reviewer verifies the revised model before any G4 work.

## Resolution (destination role)

`protocol-modeler / g3-disposition-partition-001` supplies a new candidate model at `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` (SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`). `DOM-TCP-CORRELATED-DISPOSITION` and `INV-TCP-CORRELATED-DISPOSITION-PARTITION` define an ordered exhaustive classification for every completed correlated TCP frame: resource-limit first; if not resource-limit, malformed; if not malformed, unsupported-extension for an otherwise valid excluded OPT/EDNS frame; otherwise publish. The malformed guard expressly excludes the structurally valid OPT/EDNS case, while unsupported-extension requires no resource-limit and no other structural/profile failure. Each terminal transition preserves no-result publication and cleanup. Traceability retains `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025`.

Resolution status: `READY_FOR_REVIEW`. A fresh independent G3 `protocol-api-designer` review is requested by `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/handoffs/model-to-g3-disposition-partition-review.md`; it is not dispatched by this leaf.

## Closure (orchestrator after verification)

Reserved for `protocol-orchestrator` after verifying the revised delivery and routing a fresh independent G3 review.
