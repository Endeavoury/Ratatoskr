# G3 corrective review — DNS semantic-model correction

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g3-corrective-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` (designated independent G3 reviewer) |
| Status | `CHANGES_REQUESTED` |
| Revision | Reviewer record; Git delivery commit and digest are recorded in `completion-report.md`. |
| Source artifacts | Exact immutable revisions listed below. |
| Assumptions | Review is limited to the approved UDP-first unicast stub/client profile and the two corrective G3 subjects. |
| Open questions | None; the remaining defect is a modeler-owned transition-disposition partition. |
| Limitations | Artifact-only G3 review. It does not author or approve API/ABI, implementation, vectors, tests, bindings, documentation, decisions, or workflow state. |

## Gate identity

- **Gate / applicability:** G3 / applicable.
- **Workflow stage:** modeling.
- **Required input paths and exact revisions:**

| Input | Revision / digest | Verification |
| --- | --- | --- |
| Corrected model | `46dfcfe543c7591db963c606802cd7f0d147d35d`; SHA-256 `130e354e67a517870e3d826f54f323b38dc98716c14b272f22a4adf8d6aa1b7f` | Matched recorded author digest by immutable Git object. |
| Modeler corrective handoff | `46dfcfe543c7591db963c606802cd7f0d147d35d` | Read as delivered. |
| Prior G3 review | `0fa10145698994fcdb2e3a6004cd8e6a356b96f7`; SHA-256 `89b25877451bfd048155c6eeb3c859b10cfafa9cbfdca5742872f166ca0ef571` | Read as immutable prior finding. |
| Prior G3 return handoff | `0fa10145698994fcdb2e3a6004cd8e6a356b96f7` | Read as immutable return criteria. |
| Approved analysis | `5615caed0b7ad0a321d6794e71b79c4195e90384`; SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444` | Matched recorded digest. |
| G2 model / analysis approval evidence | `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`; model SHA-256 `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd` | Matched recorded digest; G2 review status is `APPROVED`. |

- **Artifact author identity:** `protocol-modeler / g3-model-correction-001`; corrective delivery committed by `protocol-orchestrator <protocol-orchestrator@roygerritse.nl>`.
- **Reviewer identity:** `protocol-api-designer / g3-corrective-review-001`; fresh independent leaf reviewer, distinct from `protocol-api-designer / g3-api-001`.
- **Independence declaration:** I did not author, edit, or resolve the G2 model, the corrective model, approved analysis, prior G3 review, prior G3 return handoff, or any resolution of those artifacts. I write only this assigned reviewer workspace and did not author API design or technical truth.
- **Review date:** 2026-09-14.
- **Reviewer model/runtime evidence:** requested `gpt-5.6-sol` / medium; actual exposed runtime `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry unknown.

## Evidence and checks

| G3 criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Single observable incremental consumption / remaining-input contract consistent with `DNS-REQ-019` | Corrected `DOM-CONSUMPTION`, `ENT-FRAME-ACCUMULATOR`, `EVT-TCP-BYTES`, `STR-TCP-DNS-FRAME`, `TR-TCP-NEED-MORE` at `46dfcfe` | The former contradiction is resolved: incomplete supplied prefix/body bytes transfer to the accumulator with no caller remainder; a completed frame accepts its prefix plus declared body and leaves suffix caller-owned. | No API or parser implementation was reviewed. |
| Completed correlated TCP frame has exactly one disposition | Corrected `TR-TCP-CORRELATED-MALFORMED`, `TR-TCP-CORRELATED-RESOURCE-LIMIT`, `TR-TCP-CORRELATED-UNSUPPORTED-EXTENSION`, `TR-TCP-PUBLISH`; prior G3 acceptance criterion; `DNS-REQ-019/023/024/025` | **Fails.** `TR-TCP-CORRELATED-MALFORMED` applies when a correlated frame fails an “accepted profile rule,” while `TR-TCP-CORRELATED-UNSUPPORTED-EXTENSION` applies to a structurally recognized excluded OPT/EDNS frame. An excluded OPT/EDNS frame can also fail the accepted-profile rule. No precedence or disjointness rule resolves this overlap. `TR-TCP-CORRELATED-RESOURCE-LIMIT` can likewise overlap a message classification unless ordering/exclusion is explicit. Therefore the model does not establish the required exactly-one disposition. | This finding concerns only the correction's transition partition, not numerical limit policy. |
| Terminal paths have no partial result and clean up context/buffers | Corrected terminal TCP transitions plus `INV-ATOMIC-PUBLICATION` and `INV-TERMINAL-CLEANUP` at `46dfcfe` | Each newly listed terminal transition explicitly discards partial/frame state, releases context/buffers, and publishes no result. | This does not cure the unresolved overlap above. |
| Language/ABI/parser independence and traceability retained | Corrected model entities/domains/transitions/traceability at `46dfcfe`; approved analysis | The correction remains semantic and language/ABI/parser independent; `DNS-REQ-019`, `023`, `024`, and `025` are traced. | G3 remains unapproved because the required disposition partition is incomplete. |

## Disposition

**CHANGES_REQUESTED.** The correction resolves the prior consumption contradiction and supplies terminal effects, but it does not make the completed-correlated-frame dispositions mutually exclusive. The ambiguity between `accepted profile rule` malformed handling, excluded OPT/EDNS handling, and potentially resource-limit handling violates the required exactly-one disposition criterion.

**Required revision:** `protocol-modeler` must revise only its owned corrective model and supporting modeler records to define a mutually exclusive partition or explicit, semantically observable precedence for completed correlated frames. The revised rules must demonstrate that each such frame reaches exactly one of publish, terminal malformed, terminal resource-limit, or terminal unsupported-extension; a nonmatching frame alone may remain pending/ignored. Preserve the existing no-result and cleanup effects and requirement traceability. A fresh independent G3 re-review is required.

**Formal return route:** `DNS-HO-API-G3-CORRECTIVE-001-DISPOSITION-PARTITION` to `protocol-modeler` only. No G4 or later stage is routed.
