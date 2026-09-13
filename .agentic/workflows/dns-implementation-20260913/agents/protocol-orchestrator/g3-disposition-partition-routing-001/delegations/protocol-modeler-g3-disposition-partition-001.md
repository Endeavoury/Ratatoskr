# Delegation — protocol-modeler / g3-disposition-partition-001

| Field | Value |
| --- | --- |
| Workflow / target / stage | `dns-implementation-20260913` / `protocol/dns` / modeling (G3) |
| Root task / project | `dns-implementation-20260913` / `Ratatoskr` |
| Parent role / child role | `protocol-orchestrator` / `protocol-modeler` leaf |
| Assignment ID | `g3-disposition-partition-001` |
| Repository root and command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline | `fa2cf017b2505c0aacae3cacbe65714a960a8e9c` on `hermes/dns-implementation-20260913`; origin `https://github.com/Endeavoury/Ratatoskr.git` |
| Child artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/` |
| Requested runtime | `gpt-5.6-terra` / `medium` |
| Observed runtime before dispatch | `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry unknown |
| Attempts / escalation | One bounded delivery attempt. If missing/contradictory upstream semantic truth, create a blocking modeler handoff; do not invent policy or retry across model tiers. |

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-modeler/SKILL.md`
3. `docs/agentic/ARCHITECTURE.md`, `ARTIFACTS.md`, `HANDOFFS.md`, `REVIEW_GATES.md`, `DIRECTORIES.md`, `MODEL_POLICY.md`
4. This packet and `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/reviews/g3-corrective-model-review.md`
6. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/handoffs/g3-corrective-to-modeler-disposition-partition.md`
7. `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/protocol-model.yaml` at `46dfcfe543c7591db963c606802cd7f0d147d35d`, and its completion/handoff records as relevant.
8. `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g2-model-001/protocol-model.yaml` and `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` at approved recorded revisions, especially `DNS-REQ-019`, `DNS-REQ-023`, `DNS-REQ-024`, and `DNS-REQ-025`.

## Goal

Create a **new candidate** semantic model in your assigned workspace that resolves the open `DNS-HO-API-G3-CORRECTIVE-001-DISPOSITION-PARTITION` handoff. Do not edit previous modeler output. For each completed, correlated TCP frame in the approved profile, define exactly one mutually exclusive or explicitly ordered observable disposition: publish; terminal malformed; terminal resource-limit; or terminal unsupported-extension. Resolve the overlap between accepted-profile malformed, excluded OPT/EDNS, and resource-limit classifications. A nonmatching frame alone may remain pending/ignored.

Preserve terminal no-result and cleanup effects, `DNS-REQ-019/023/024/025` traceability, and language/ABI/parser independence. Do not select numerical policy, change approved analysis, add API/ABI/parser details, alter review verdicts, or route later stages.

## Exact allowed writes

Only these paths are writable:

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/decisions/`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/handoffs/`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/completion-report.md`
- Only the `## Resolution (destination role)` section of `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-corrective-review-001/handoffs/g3-corrective-to-modeler-disposition-partition.md`

Everything else is read-only and forbidden: workflow state, reviews, source, headers, tests, vectors, bindings, docs, request, manifest, prior modeler workspaces, and handoff closure. Do not modify `master` or unrelated files. Do not delegate.

## Required checks and delivery

Before writing, verify the absolute wrapper is an executable regular file and inspect it:
`/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`.

Use that wrapper only, from the stated repository working directory, for branch/origin/HEAD/diff-boundary verification, commit, push, and remote readback:
`/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-modeler -- <git arguments>`.

Verify YAML syntax/model invariants and `git diff --check`; record actual commands/results. Verify branch is `hermes/dns-implementation-20260913`, origin is the stated URL, and inspect the diff boundary. Commit only the allowed leaf files and permitted handoff Resolution with the wrapper. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`. Then remote-readback with the wrapper/allowed Git and record the matching SHA. Never raw-Git substitute, merge, or push master.

## Acceptance and report

Report `READY_FOR_REVIEW` only after local and remote delivery verification. Write complete modeler artifacts and a completion report with actual runtime requested/actual, checks, commit, remote SHA, exact files, assumptions/limitations, and a handoff to a **fresh independent G3 protocol-api-designer reviewer**. Do not dispatch that reviewer.

If a quota/rate limit occurs, stop immediately without shared workflow-state changes and report the exact error. If the inputs contradict or prerequisite evidence is missing, stop with a modeler-owned blocking handoff. Return your concise outcome to this orchestrator.