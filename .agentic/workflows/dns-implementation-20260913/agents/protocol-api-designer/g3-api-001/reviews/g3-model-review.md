# G3 review — DNS semantic-model candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g3-review-api-designer-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-api-designer |
| Status | CHANGES_REQUESTED |
| Revision | Authored review; delivery commit and content digest are recorded in `completion-report.md`. |
| Source artifacts | Exact immutable inputs below. |
| Assumptions | Bounded standard unicast stub/client: selected upstream resolver, OS-owned sockets, UDP first, TCP only after correlated UDP TC. |
| Open questions | Numerical limits and retry/server-selection/connection-reuse policy remain explicit API/product decisions; they are not the requested change. |
| Limitations | This is an artifact-only G3 review. It does not approve G3/G4 or authorize API, header, implementation, vector, test, binding, documentation, or workflow-state changes. |

## Gate identity

- **Gate / applicability:** G3 / applicable.
- **Workflow stage:** modeling.
- **Required immutable inputs:**

| Input | Commit | Blob | SHA-256 | Result |
| --- | --- | --- | --- | --- |
| G2 approval record | `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c` | `bbe2703fc2ca309cd5f0948d973a6027d5f21d96` | `10eb209f071fb2c7f976590be4f732a59bd72120082b576a13b5805e87e12989` | matched working file |
| Semantic model candidate | `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c` | `07d2096667cd6c150ba37bf6c19976ef75f30272` | `a94af3e8889a6f86470385cecf3084fb8c4d8db8d712e539f5cbb7241851e1cd` | matched working file |
| Model-to-G3 handoff | `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c` | `106b035b107357c0df524c65e318a9c0d5491024` | `6c4736c86e44382ff039bd19782f2d5b798ed49264155197f3a3187e3e705b60` | matched working file |
| Approved analysis | `5615caed0b7ad0a321d6794e71b79c4195e90384` | `244b6aac760c7a67aac909d905e9215c0766e88f` | `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444` | matched working file |
| Extension/QTYPE decision | `5615caed0b7ad0a321d6794e71b79c4195e90384` | `c6fa17aa6bccdc2702bf2f16a54b97e132d97b1e` | `38746ca8f26735bae37643ae2ffc17ec652ee89c9b027fcbf5dfca4d81b082c9` | matched working file |

- **Artifact author identities:** protocol-modeler / `g2-model-001` / Hermes child `20260913_195235_e7a80b`; approved analysis author protocol-analyst / `analysis-001` / recorded workflow agent `deleg_52a8fb54/task-0`.
- **Reviewer identity:** protocol-api-designer / `g3-api-001` / fresh delegated child for this review; Git delivery identity `protocol-api-designer <protocol-api-designer@roygerritse.nl>`.
- **Independence declaration:** This reviewer did not author, edit, or resolve `protocol-modeler/g2-model-001`, `protocol-analyst/analysis-001`, their decisions/handoffs, or G2. The review writes only this assignment workspace.
- **Review date:** 2026-09-13.
- **Reviewer model/runtime evidence:** requested `gpt-5.6-sol` / medium. Actual inherited runtime exposed to this reviewer: `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry unavailable. This routing mismatch is recorded, not treated as a review exemption.

## Evidence and checks

| G3 pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Requirement traceability and semantic domains | Model `traceability` plus `DOM-DNS-U16/U32/NAME/OPAQUE-BYTES/TRANSPORT/PEER-CONTEXT/CONSUMPTION`; analysis `DNS-REQ-001`–`DNS-REQ-027` at the verified revisions | Each requirement has at least one model-element reference. Query/header/name/RR domains, bounded opaque RDATA, correlation peer context, and excluded EDNS/transport policy are language-independent. | Traceability alone does not cure conflicting transition semantics below. |
| Request, response, correlation, and profile exclusions | `ENT-*`, `MSG-*`, `TR-VALIDATE-AND-BUILD`, `TR-IGNORE-NONMATCHING-UDP`, `TR-UDP-*`, `EXT-*`; requirements 001–018, 021, 025–027 | One-question QUERY, selected ordinary QTYPE, local rejection, full transaction context, case-insensitive ASCII matching, TC fallback, atomic result, base RCODE metadata, OPT rejection, and residual unauthenticated-UDP boundary are represented without ABI/parser-layout coupling. | TCP malformed input remains incomplete. |
| States, lifecycle, terminal cleanup, and result ownership | `ST-*`, `ENT-OWNED-RESULT`, `INV-ATOMIC-PUBLICATION`, `INV-TERMINAL-CLEANUP`; requirements 004, 017–018, 022–024 | UDP and cancellation/deadline paths explicitly release context/buffers and publish zero-or-one owned result. No language-specific ownership type or public ABI layout is introduced. | A complete correlated malformed TCP frame has no corresponding terminal transition. |
| Incremental TCP framing and consumption | `ENT-FRAME-ACCUMULATOR`, `MSG-TCP-FRAME`, `STR-TCP-DNS-FRAME`, `DOM-CONSUMPTION`, `TR-TCP-NEED-MORE`; requirements 019–020 | Prefix/body framing, zero-length failure, EOF, and one-frame-per-step intent are modeled. However `DOM-CONSUMPTION` says need-more-input has **no consumption**, while `TR-TCP-NEED-MORE` says to consume available frame bytes. The analysis requires incremental consumption of available prefix/body bytes. | Required correction: choose and define one externally observable consumption contract consistent with DNS-REQ-019, including buffered bytes and remaining caller input. |
| Correlated malformed TCP behavior | `TR-TCP-INVALID-FRAME`, `TR-TCP-IGNORE-NONMATCHING`, `TR-TCP-PUBLISH`; requirements 019, 023 | Frame-length and EOF failures are terminal; nonmatching completed frame is ignored; valid correlated frame publishes. No transition covers a **completed, correlated** TCP frame that fails DNS header/structural/name/count/RDLENGTH/exact-consumption/reserved-bit/OPT rules. It is neither valid publish nor nonmatching nor framing failure. | Required correction: add explicit terminal malformed/unsupported-extension/resource-limit transitions and preserve atomic no-result cleanup; then recheck corresponding requirement references. |
| Language/ABI/parser independence | Entire model and analysis at verified revisions | The candidate uses semantic entities, domains, events, and effects rather than C layouts, handles, ownership functions, or parser algorithm APIs. | A corrected model must retain this boundary. |

## Disposition

**CHANGES_REQUESTED.** G3 cannot approve a model that leaves a required TCP terminal outcome unspecified and gives contradictory semantic input-consumption behavior. These are model corrections, not API-design choices.

**Return route:** `DNS-HO-API-001-G3-TCP` to **protocol-modeler / g2-model-001**. The modeler must revise only its owned semantic model (and any required modeler decision/handoff/completion records), provide immutable revision evidence, and request a fresh independent G3 re-review. The re-review must show: (1) a single observable incremental TCP consumption definition consistent with DNS-REQ-019, and (2) explicit terminal handling for every completed correlated TCP frame that is malformed, exceeds a resource limit, or contains a structurally recognized unsupported OPT/EDNS extension, with no partial result and terminal cleanup. The protocol-analyst is the return role only if the modeler discovers an interpretation conflict; the orchestrator resolves product policy only if the change requires new policy.

No `api-design.md` was created because the G3 disposition is not APPROVED.
