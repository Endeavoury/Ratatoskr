# Delegated task

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-engineer-g9-fuzz-evidence-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator/g9-fuzz-routing-001` |
| Status | `IN_PROGRESS` |
| Revision | Dispatch baseline `git:a4ae4e3fd94871bba4d5644b4edff891ae213047`; remote `origin/hermes/dns-implementation-20260913` matched before dispatch. |
| Source artifacts | G7/G8 records and current source/fuzz/build paths listed below. |
| Assumptions | Existing untracked files are unrelated and must remain untouched. |
| Open questions | None at dispatch. |
| Limitations | CMake/CTest availability and fuzz toolchain availability must be observed and reported, not inferred. |

ACTIVE ROLE: fuzz-engineer

ROLE: fuzz-engineer
GOAL: Produce executed DNS G9 fuzz evidence for the approved implementation, including a reproducible plan, any narrowly authorized fuzz-specific changes, campaign results, and a handoff to an independent G9 security review.
SCOPE: Execution-stage G9 fuzz evidence only. Do not alter DNS semantics, production code, headers, ordinary tests, canonical vectors, bindings, documentation, CLI, or workflow state. Do not approve G9.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested route: `openai-codex/gpt-5.6-terra`, reasoning `medium`.
- Observed inherited route: `openai-codex/gpt-5.6-terra`; reasoning-effort telemetry is not exposed, therefore `unknown`.
- Verification source: parent Hermes session metadata; do not claim the requested effort was configured.
- Context target: 8,000–16,000 tokens with all required reading complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: exactly one fuzz-engineer attempt; no retries or further delegation. If a material strategy/minimization problem persists, hand off rather than retrying.
- Escalation trigger: stateful generation/invariant design or difficult minimization would normally request Sol/high, but no escalation is authorized in this one-attempt assignment.
- Stop/checkpoint: missing approved prerequisite, unavailable required delivery wrapper, prohibited boundary conflict, reproducible crash/UB, unavailable execution toolchain, or completed evidence.

## Repository and workflow

- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-001/`.
- Workflow/stage/assignment: `dns-implementation-20260913` / `fuzzing` / `g9-fuzz-evidence-001`; state is read-only at `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
- Delivery branch: `hermes/dns-implementation-20260913` only. The verified absolute role-scoped wrapper is `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`; use it, with `--role fuzz-engineer --`, for every commit/push. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref. Never use raw Git for commit/push, merge, or push any other branch.

## Read first

- `AGENTS.md`
- `.hermes/skills/fuzz-engineer/SKILL.md`
- `docs/agentic/{HANDOFFS.md,DIRECTORIES.md,ARTIFACTS.md,REVIEW_GATES.md,SECURITY_MODEL.md,MODEL_POLICY.md}`
- `docs/contributing.md`
- `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`

## Required approved inputs

- G7 APPROVED record: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`, candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`, reviewer delivery `git:510b5a131bcb3272caeb7eb1821444b35644cfcd`.
- G8 APPROVED record: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`, candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`, reviewer delivery `git:5d81f9f26945ad9f80f5b818bf6b147f6b37bfff`.
- Approved upstream analysis/model/API/vectors as referenced by the current workflow state; consume them read-only.
- Current existing fuzz surface: `fuzz/CMakeLists.txt`, `fuzz/dns/{fuzz_dns_packet.c,fuzz_dns_name.c,fuzz_dns_record.c,corpus/README.md,corpus/seeds.txt}` at dispatch baseline.
- Current DNS source, read-only: `src/protocols/dns/{dns_parser.c,dns_packet.c,dns_builder.c,dns_client.c,dns_transport_udp.c,dns_transport_tcp.c}` at dispatch baseline.

## Allowed writes

- Your assigned workspace only: `README.md`, `fuzz-plan.md`, `fuzz-results.md`, `handoffs/g9-fuzz-evidence-to-security-reviewer.md`, `completion-report.md`, and any narrowly necessary owned decision files.
- Fuzz-specific shared paths only if inspection establishes necessity: `fuzz/dns/` (harnesses/adapters and derived corpus only) and `fuzz/CMakeLists.txt` (scoped DNS fuzz registration only).
- No other path is authorized. Preserve unrelated untracked files; do not stage them.

## Required outputs and acceptance

1. `fuzz-plan.md`: reachable entrypoints, trust boundaries, seed provenance, applicable invariants, mutation/generation/stateful approach, deterministic replay, sanitizer/build settings, command and time/resource budget.
2. Any authorized fuzz-only harness/corpus/registration changes, with exact path list and rationale.
3. `fuzz-results.md`: exact revision, commands, environment/toolchain, build and campaign budget, corpus provenance, results, coverage if exposed, findings/minimized reproductions and dispositions, and limitations. A plan is not executed evidence.
4. `handoffs/g9-fuzz-evidence-to-security-reviewer.md`: status `READY_FOR_REVIEW` only when evidence is complete; otherwise `BLOCKED`, with exact evidence and requested action. Target a fresh independent `security-reviewer` for G9; do not route that reviewer yourself.
5. `completion-report.md` using the standard template, ending `READY_FOR_REVIEW` or `BLOCKED` only.
6. Wrapper-mediated commit/push of only authorized paths and exact remote-ref readback. If the wrapper is unavailable or delivery cannot be verified, create an evidence-backed `BLOCKED` handoff/completion instead; never substitute raw Git.

Acceptance is delivery completeness and reproducibility for an independent G9 review, not self-approval or an assertion that G9 passed. Crashes/undefined behavior, untriaged failures, missing execution evidence, or prohibited changes are blocking and must be handed to the responsible owner.

HANDOFF TARGET: a fresh independent `security-reviewer` G9 assignment, via the specified handoff path; return completion to `protocol-orchestrator` for delivery/boundary/state verification only.

DELEGATION ALLOWANCE: No further delegation.
