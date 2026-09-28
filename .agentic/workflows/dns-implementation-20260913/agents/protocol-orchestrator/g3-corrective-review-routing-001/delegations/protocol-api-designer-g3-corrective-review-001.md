# Delegation — DNS G3 corrective semantic-model review

| Field | Value |
| --- | --- |
| ROLE | protocol-api-designer (designated independent G3 reviewer) |
| Workflow / stage | `dns-implementation-20260913` / modeling (G3 corrective review) |
| Target | `protocol/dns` |
| Assignment ID | `g3-corrective-review-001` |
| Repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/` |
| Requested runtime | `gpt-5.6-sol` / medium |
| Observed parent runtime | `openai-codex` / `gpt-5.6-terra`; effort and usage unknown |
| Attempt limit | One independent review; no retry/escalation. |

ACTIVE ROLE: protocol-api-designer

## Goal and scope

Perform the sole fresh independent G3 review of the delivered corrected DNS semantic model at commit `46dfcfe543c7591db963c606802cd7f0d147d35d`. Validate only whether the correction resolves the recorded TCP consumption and completed correlated-frame disposition findings against the approved analysis. Record `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED` with exact input revisions and an independence declaration.

This is a gate review, not API design. Do not author `api-design.md`, public API/ABI, code, tests, vectors, bindings, docs, decisions, or shared workflow state. Do not route G4 or any later stage. Do not approve a different artifact or alter model/analysis truth.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-api-designer/SKILL.md`
3. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md}`
4. This delegation packet and current `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/reviews/g3-model-review.md`
6. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/handoffs/g3-to-modeler-tcp-semantics.md`
7. `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/{protocol-model.yaml,handoffs/model-to-g3-corrective-review.md,completion-report.md}`
8. Approved analysis at `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` (delivery `5615caed0b7ad0a321d6794e71b79c4195e90384`) and G2 evidence at delivery `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`.

## Exact inputs and delivery evidence

- Delivered correction commit: `46dfcfe543c7591db963c606802cd7f0d147d35d`.
- Remote ref readback before assignment: `46dfcfe543c7591db963c606802cd7f0d147d35d refs/heads/hermes/dns-implementation-20260913`.
- Corrected model SHA-256 recorded by author: `130e354e67a517870e3d826f54f323b38dc98716c14b272f22a4adf8d6aa1b7f`.
- Prior G3 review/return handoff delivery: `0fa10145698994fcdb2e3a6004cd8e6a356b96f7`.
- Approved analysis delivery: `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- G2 model/review delivery: `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`.

## Allowed writes — exact paths

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/reviews/g3-corrective-model-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/handoffs/` — only a formal return handoff if the disposition is `CHANGES_REQUESTED` or `BLOCKED`.
- Only `## Resolution (destination role)` in `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/handoffs/model-to-g3-corrective-review.md`, if resolution is permitted by `HANDOFFS.md`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/completion-report.md`

All other paths are read-only, including shared workflow state, prior reviewer workspace, modeler correction truth, source, headers, tests, vectors, API design, bindings, docs, request, and manifest. Do not change files beyond this list.

## Review acceptance criteria

- Verify a single observable `EVT-TCP-BYTES` / `STR-TCP-DNS-FRAME` consumption and remaining-input contract consistent with `DNS-REQ-019`.
- Verify each completed correlated TCP frame is exactly one of publish, terminal malformed, terminal resource-limit, or terminal unsupported-extension; nonmatching frames alone may remain pending/ignored.
- Verify terminal paths publish no partial result and release context/buffers.
- Verify the corrective artifact retains language/ABI/parser independence and exact requirement traceability.
- State exact input revisions, reviewer identity, and an explicit declaration that this fresh reviewer did not author/edit the G2 model, correction, approved analysis, prior G3 review, or their resolutions.

## Required disposition and return route

- If `CHANGES_REQUESTED`, create a formal handoff to `protocol-modeler` only. Do not repair the model and do not route G4.
- If `APPROVED`, resolve the modeler handoff destination section if contract permits, write the review/completion record, and return only to `protocol-orchestrator` for verification/state update. Do not route G4.
- If `BLOCKED`, state exact blocker and return to `protocol-orchestrator`; do not assume a pass.

## Delivery and stop conditions

Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer --` for Git. Before committing, independently verify the wrapper is an executable regular file, inspect it, verify branch/origin/HEAD/diff boundaries, and run `git diff --check`. Commit only your allowed artifacts, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back `git ls-remote --heads origin refs/heads/hermes/dns-implementation-20260913`. Never merge or push master.

If a quota/rate-limit error occurs at dispatch or during work, stop immediately, make no shared-state changes, and report only the limit. If delivery fails for another reason, do not claim review delivery; record `BLOCKED` only within your own allowed workspace if possible and return to the orchestrator. No further delegation is permitted.
