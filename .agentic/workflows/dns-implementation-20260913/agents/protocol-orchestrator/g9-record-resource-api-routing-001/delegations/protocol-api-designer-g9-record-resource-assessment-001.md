# Delegated task — G9 DNS record resource-policy/design assessment

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-api-designer-001` |
| Workflow ID / project ID | `dns-implementation-20260913` / `Ratatoskr` |
| Target | `protocol/dns`: record-parser resource growth under mandatory G9 budget |
| Parent role / hierarchy | `protocol-orchestrator` in `workspace-orchestrator → protocol-orchestrator → protocol-api-designer` |
| Assignment ID | `g9-record-resource-assessment-001` |
| Status | `NOT_STARTED` |
| Dispatch baseline | `git:510d1a3617e0b66ed98b0980f277de689b5ae508` |
| Tested evidence revision | `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` (verified ancestor of dispatch baseline) |
| Source handoff revision | `git:8698fe9e5732f7b7b539d0130b13f4d3d730759f` |

ACTIVE ROLE: protocol-api-designer

ROLE: protocol-api-designer

GOAL: Perform exactly one evidence-bound, assessment-only design-authoring task. Determine whether existing approved DNS resource semantics authorize a concrete bounded **private** corrective candidate for the observed G9 record-target RSS failure, or whether revised design/approval is required. Do not diagnose or invent a root cause.

SCOPE: G9 blocker assessment only; authoring status must be `READY_FOR_REVIEW` or `BLOCKED`, never approval. The mandatory `-rss_limit_mb=1024` budget is fixed and must not be increased, weakened, or reinterpreted.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-api-designer row.
- Requested provider/model/effort: `openai-codex/gpt-5.6-sol/medium`.
- Observed route at dispatch: `openai-codex/gpt-5.6-terra`; reasoning effort is unknown. This request does not configure Hermes; record actual observed route honestly in outputs.
- Context target: 8,000–16,000 task-specific tokens while completing all required reading.
- Attempt policy: one evidence-driven pass; missing/conflicting authority is a formal blocker/handoff, not repeated speculation.
- Stop condition: quota/rate-limit error (return immediately without state/commit/push), unavailable required input, path-boundary conflict, or completed assessment. Do not dispatch children.

## Repository and workspace

- Absolute repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Assigned unique workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g9-record-resource-assessment-001/`.
- Workspace owner: this fresh protocol-api-designer leaf only.
- Parent packet/report workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-record-resource-api-routing-001/`.
- Shared source writer: none. No source/header/test/fuzz/CMake writer is authorized.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-api-designer/SKILL.md`
3. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,DIRECTORIES.md,REVIEW_GATES.md,MODEL_POLICY.md,SECURITY_MODEL.md,ARCHITECTURE.md}`
4. `docs/abi.md` and `docs/repository-layout.md`
5. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`
6. `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-record-resource-remediation-routing-001/handoffs/g9-record-resource-authority-to-api-designer.md`

## Required evidence inputs

- Source handoff above at `git:8698fe9e5732f7b7b539d0130b13f4d3d730759f`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-full-campaign-reroute-002/verification/g9-full-campaign-execution-002-delivery-verification.md` at the current delivery history; it records the tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` result: record target exit 71 after 21.236172719858587s, `ru_maxrss` 1,675,884 KiB, libFuzzer OOM 1636 MiB versus required 1024 MiB; packet/name clean.
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/{fuzz-results.md,handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md}` at tested revision `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`.
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g8-accounting-g4-g6-implementation-routing-001/preflight-verification.md`: current G6 authority permits only `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, `src/protocols/dns/dns_client.c`; it does not authorize `src/protocols/dns/dns_parser.c`.
- Read-only code scope evidence only: `fuzz/dns/fuzz_dns_record.c` invokes `ratos_dns_parse_response`; `src/protocols/dns/dns_parser.c` is a potential surface, not proof of cause.

## Allowed writes — exact and exhaustive

1. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g9-record-resource-assessment-001/README.md`
2. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g9-record-resource-assessment-001/api-design.md`
3. Any file below the leaf workspace `decisions/` or `handoffs/`.
4. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g9-record-resource-assessment-001/completion-report.md`
5. Only the **Resolution** section of the source handoff named above.

## Read-only / forbidden

All other paths. In particular, do not modify production code or headers; `src/protocols/dns/dns_parser.c`; tests; fuzz source/corpus/CMake; workflow-state; manifest/request; bindings; docs; configuration; other specialist workspaces outside the exact source-handoff Resolution section. Do not dispatch implementation, reviewers, campaign reruns, security work, bindings, documentation, or later stages. No public ABI change unless independently required by demonstrated design authority; do not claim one is approved.

## Required outputs and acceptance

- `api-design.md` gives a revision-bound conclusion: either (a) existing approved resource semantics authorize a concrete bounded private corrective candidate, or (b) revised design/approval is needed.
- No root-cause assertion beyond evidence. Preserve 1024 MiB as mandatory.
- Name exact candidate private path(s) only if warranted; state why existing G6 does not itself authorize any parser change.
- State no public ABI change unless independently necessary and not approved here.
- Formal handoff to `protocol-orchestrator` requests a **future fresh G6 authority assessment**; it must not route implementation or review.
- Completion report has standard fields, actual model route/effort evidence or unknown, inputs/revisions, changed-path validation, status `READY_FOR_REVIEW` or `BLOCKED`, and limitations.

## Delivery and reporting

Report target: parent `protocol-orchestrator` at `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-record-resource-api-routing-001/` via your completion report and formal handoff.

If a compliant role-scoped commit/push is performed, first verify the absolute executable wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`; use only `--role protocol-api-designer -- <git args>`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never master/merge/force-push, and read back that exact origin ref. If the wrapper is unavailable, do not substitute raw Git; record local-only delivery. Preserve all 19 pre-existing untracked items.

DELEGATION ALLOWANCE: none.
