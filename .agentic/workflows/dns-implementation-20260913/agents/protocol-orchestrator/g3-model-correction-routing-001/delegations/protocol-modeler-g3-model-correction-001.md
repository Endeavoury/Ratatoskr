# Delegation — DNS G3 semantic-model correction

| Field | Value |
| --- | --- |
| ROLE | protocol-modeler |
| Workflow / stage | `dns-implementation-20260913` / modeling corrective return for G3 |
| Target | `protocol/dns` |
| Assignment ID | `g3-model-correction-001` |
| Repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/` |
| Requested runtime | `gpt-5.6-terra` / medium |
| Observed parent runtime | `openai-codex` / `gpt-5.6-terra`; effort and usage unknown |
| Attempt limit | One evidence-driven correction attempt only; no retry/escalation. |

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-modeler/SKILL.md`
3. `docs/agentic/{ARCHITECTURE.md,ARTIFACTS.md,REVIEW_GATES.md,HANDOFFS.md,DIRECTORIES.md,MODEL_POLICY.md}`
4. This packet.
5. Current `workflow-state.yaml`, G3 review, and G3 return handoff listed below.

## Required immutable inputs

- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/reviews/g3-model-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/handoffs/g3-to-modeler-tcp-semantics.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/protocol-model.yaml` at delivery commit `7de66fd8bc3c28dc058f3c51a6cd36c2db81424c`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/reviews/g2-analysis-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at `5615caed0b7ad0a321d6794e71b79c4195e90384`

## Authorized writes — exact list

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/protocol-model.yaml`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/decisions/` (only a correction rationale if needed)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/handoffs/` (including a fresh model-to-G3 handoff)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/completion-report.md`
- Only the `## Resolution (destination role)` section of `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-api-001/handoffs/g3-to-modeler-tcp-semantics.md`, as permitted by `HANDOFFS.md`.

Everything else is read-only: shared state; all existing specialist/reviewer artifacts beyond that resolution section; API design; production code; headers; tests; vectors; bindings; docs; request and manifest. Do not self-review G3 and do not author API design.

## Goal and acceptance criteria

Create a new language-independent semantic-model revision, derived only from the approved analysis and G3 return finding. It must:

1. Define one observable incremental TCP consumption contract for `EVT-TCP-BYTES` / `STR-TCP-DNS-FRAME`, specifying accepted caller bytes, accumulator-owned bytes, and remaining caller input for need-more and one-frame outcomes.
2. Define explicit terminal outcomes for every completed correlated TCP frame that is malformed, exceeds a resource limit, or contains structurally recognized but excluded OPT/EDNS material.
3. Keep no partial result and terminal cleanup explicit for those terminal outcomes.
4. Preserve language/ABI/parser independence; do not invent numerical policy or alter approved requirements.
5. Update requirement traceability, including `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025`.
6. Record actual runtime exactly as exposed (otherwise `unknown`), inputs/revisions, one attempt, validations, limitations, and a fresh READY_FOR_REVIEW handoff to an independent protocol-api-designer G3 review.

If an interpretation conflict is found, stop and hand off to protocol-analyst rather than decide it. Do not route or conduct the G3 review.

## Git delivery requirement and stop condition

Before any leaf work, discover and record the **absolute** `git-agent` wrapper path. Coordinator precheck found no wrapper via `PATH`, standard checked locations, or a name search under `/home/hermes`; independently confirm this. If no verified absolute wrapper exists, record a blocker in your authorized workspace and make **no** raw-Git substitute commit or push. If available, use only that wrapper to commit only the exact allowed paths and push `HEAD:refs/heads/hermes/dns-implementation-20260913`; then read back that exact remote ref. Never merge or push master. If a quota/rate-limit error occurs, stop immediately without state changes and report it plainly.

## Handoff target

Return a fresh model-to-G3 handoff and completion report to protocol-orchestrator. A future independent `protocol-api-designer` G3 review is the next role only; do not dispatch it.
