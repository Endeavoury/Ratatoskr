# Delegation — DNS G3 disposition-partition model review

| Field | Value |
| --- | --- |
| ROLE | `protocol-api-designer` (designated independent G3 reviewer) |
| Workflow / stage | `dns-implementation-20260913` / modeling (G3 disposition-partition review) |
| Target | `protocol/dns` |
| Assignment ID | `g3-disposition-review-001` |
| Repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/` |
| Requested runtime | `gpt-5.6-sol` / medium |
| Observed parent runtime | `openai-codex` / `gpt-5.6-terra`; effort and usage unknown |
| Attempt limit | One review only; no retry, escalation, or further delegation. |

ACTIVE ROLE: protocol-api-designer

## Goal and scope

Perform exactly one fresh independent G3 review of the READY_FOR_REVIEW DNS disposition-partition semantic model. Decide only `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED` for the submitted G3 candidate, using exact input revisions and an independence declaration. You must be a new delegated child identity and must not be `g3-api-001` or `g3-corrective-review-001`; declare that you did not author or edit either prior review, the candidate model, its source corrective records, or the approved analysis.

This is a technical gate review, not API design. Do not create `api-design.md`, decisions, public API/ABI, parser algorithms, source, headers, tests, vectors, bindings, documentation, request/manifest, or shared workflow state. Do not route G4 or later stages. Do not modify any source/design truth. The only permitted shared-file change is the destination `## Resolution (destination role)` section of the stated modeler handoff, if the handoff contract permits it.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-api-designer/SKILL.md`
3. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md}`
4. This packet and `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/{protocol-model.yaml,handoffs/model-to-g3-disposition-partition-review.md,completion-report.md}`
6. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/{reviews/g3-corrective-model-review.md,handoffs/g3-corrective-to-modeler-disposition-partition.md}`
7. `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md`

## Exact input revisions

- Candidate model and review handoff: Git `f26745472178649a60f2cb079937d1bbe3f13c0b`; model SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- Candidate completion evidence: Git `d742a39f8dcd1d9f5e3f1dd2035c13ac629a809f`.
- Corrective G3 reviewer record / return handoff: Git `4e8a6653146575b8e4ce57b7cd5927e5d80d8b9e`.
- Approved analysis: Git `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Routing baseline / origin ref before dispatch: `fde16d8ede7443e9a5fd93188ed2a05fda4d986f`.

## Allowed writes — exact paths

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/reviews/g3-disposition-model-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/handoffs/` only if a formal return handoff is necessary for `CHANGES_REQUESTED` or `BLOCKED`
- only `## Resolution (destination role)` in `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/handoffs/model-to-g3-disposition-partition-review.md`, if permitted
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/completion-report.md`

Everything else is read-only, including workflow state; every earlier API reviewer workspace; all modeler workspaces except the permitted resolution section; all code, headers, tests, vectors, bindings, documentation, request, and manifest.

## Required review checks

- Verify `DOM-TCP-CORRELATED-DISPOSITION` and `INV-TCP-CORRELATED-DISPOSITION-PARTITION` make the completed correlated TCP-frame outcomes ordered, mutually exclusive, and exhaustive: resource-limit, malformed, unsupported-extension, publish.
- Verify a completed nonmatching frame remains outside that domain and pending/ignored.
- Verify resource-limit takes precedence; malformed excludes structurally valid excluded OPT/EDNS; unsupported-extension follows only if neither prior disposition applies; publish is only the final otherwise-valid case.
- Verify each terminal disposition publishes no result and cleans partial records, accumulator, request context, and transport buffers.
- Verify traceability for `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025`, with no new analysis, API/ABI, parser, or numerical-policy semantics.
- Record reviewer identity, exact input revisions, evidence, the disposition, and boundary checks in review and completion artifacts.

## Required return route

- `APPROVED`: write the permitted handoff Resolution, review record, and completion report; return only to `protocol-orchestrator` for verification/state update. Do not route G4.
- `CHANGES_REQUESTED`: create a formal modeler-only handoff in your workspace; do not repair the model; return to `protocol-orchestrator`.
- `BLOCKED`: record the exact blocker in your workspace and return to `protocol-orchestrator`.

## Delivery and stop conditions

Before any commit independently verify that `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is an executable regular file and inspect it; verify branch, origin, HEAD, status, allowed-path diff, and `git diff --check`. Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- <git args>` for Git commits/pushes; never raw Git for a role commit. Commit only allowed artifacts, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never merge or push master, and read back `git ls-remote --heads origin refs/heads/hermes/dns-implementation-20260913` after delivery.

If a quota/rate-limit happens during work, stop immediately and make no shared-state changes. If wrapper discovery or delivery fails for another reason, still create local permitted artifacts where possible, accurately record `BLOCKED`, and do not manufacture remote evidence. No further delegation is allowed.
