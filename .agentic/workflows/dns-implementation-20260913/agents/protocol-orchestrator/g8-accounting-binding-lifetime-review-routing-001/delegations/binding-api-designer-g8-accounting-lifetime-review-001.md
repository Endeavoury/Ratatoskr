# Delegation: G8 accounting-design binding lifetime/representability review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-binding-lifetime-review-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` private request/context accounting design |
| Owner role | `protocol-orchestrator/g8-accounting-binding-lifetime-review-routing-001` |
| Status | `IN_PROGRESS` |
| Revision | Routing baseline `git:e138c4b35d55ccff19f1eb9abd49291adf465c0d`; exact subject `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Source artifacts | Exact candidate paths and contracts below |
| Assumptions | G4 remains `CHANGES_REQUESTED`; this review is required evidence only, not G4 approval. |
| Open questions | Technical disposition is owned by this fresh independent reviewer. |
| Limitations | No source/header/test/vector/fuzzer/ABI/workflow-state or other-stage action is authorized. |

ACTIVE ROLE: `binding-api-designer`

## Identity and hierarchy

- **ROLE:** `binding-api-designer` (fresh independent leaf)
- **Hierarchy:** `workspace-orchestrator → protocol-orchestrator → binding-api-designer`
- **Root task / project / workflow:** `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913`
- **Assignment:** `g8-accounting-lifetime-review-001`
- **Stage:** one scoped G4-supporting review of the G8 accounting design. Do not route or perform compatibility review, implementation, G6 renewal, G7/G8, G9, binding implementation, or any other stage.
- **Repository root and command cwd:** `/home/hermes/hermes-workspace/projects/Ratatoskr`

## Read first

Read, in full, before writing: `AGENTS.md`; this packet; `.hermes/skills/binding-api-designer/SKILL.md`; `docs/agentic/HANDOFFS.md`; `docs/agentic/DIRECTORIES.md`; `docs/agentic/ARTIFACTS.md`; `docs/agentic/REVIEW_GATES.md`; `docs/agentic/BINDING_LIFECYCLE.md`; `docs/agentic/MODEL_POLICY.md`; `docs/abi.md`; and `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.

Announce `ACTIVE ROLE: binding-api-designer`, verify the scope and input ancestry, and record a fresh-session independence declaration. You must be distinct from `protocol-api-designer/g8-accounting-design-001` and must not reuse or present yourself as that candidate author.

## Exact immutable review subject and inputs

Review exactly candidate commit `4a37fc293c842b206190bad369e2a3e1ad00008c`, not a newer substituted candidate:

1. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/api-design.md`
2. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/decisions/context-destroy-live-requests.md`
3. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/handoffs/accounting-design-to-protocol-orchestrator.md`
4. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/completion-report.md`

Also inspect, read-only: `docs/abi.md`; public DNS declarations under `include/ratatoskr/`; approved model `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; prior G4 candidate `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; G8 reviewer delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; and implementation blocker delivery `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`.

Before writing, verify each named commit is an ancestor of `origin/hermes/dns-implementation-20260913`, and record that the four exact subject files are present at candidate `4a37fc293c842b206190bad369e2a3e1ad00008c`.

## Review goal and required checks

Independently judge only whether the candidate is safely representable over ABI-1 and preserves opaque caller ownership/lifetime. Address all of:

- post-`ratos_context_destroy` usability of request state/error accessors, `COMPLETE` take-result, and request destruction;
- opaque request/result ownership, including whether retaining caller-owned handles and COMPLETE results after context destruction is representable without a dangling context dependency;
- terminal/no-result behavior and exact-once accounting's observable ownership implications;
- ABI-1 representability and compatibility: no public layout/symbol/calling-convention/ownership transfer change, or identify a concrete incompatibility;
- the context-owned registry/counter lifecycle and same-context serialization versus distinct-context concurrency contract;
- whether an independent compatibility review remains required and whether G6 renewal must remain blocked.

Do not invent language bindings, alter native semantics, implement code, or self-approve G4. If unsafe/unrepresentable, record `CHANGES_REQUESTED` or `BLOCKED` with a specific return handoff to `protocol-orchestrator` / `protocol-api-designer` as appropriate. If acceptable, record a scoped `APPROVED` review disposition only; the orchestrator later synthesizes evidence and compatibility remains separately mandatory.

## Exact allowed writes

Create and own only this new unique leaf workspace:

- `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g8-accounting-lifetime-review-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g8-accounting-lifetime-review-001/reviews/g4-g8-accounting-binding-lifetime-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g8-accounting-lifetime-review-001/handoffs/g8-accounting-binding-lifetime-to-protocol-orchestrator.md`
- `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g8-accounting-lifetime-review-001/completion-report.md`

All other paths are read-only, including all workflow-root records, all candidate-author artifacts, all existing reviewer artifacts, public headers, source, tests, vectors, fuzzers, bindings, docs, and every pre-existing untracked workspace.

## Expected outputs and acceptance criteria

- A review record with exact subject commit and file paths, reviewer identity, independence declaration, all required focus areas, evidence/reasoning, disposition, and failure route if not approved.
- A handoff to `protocol-orchestrator` stating the technical disposition, exact reviewed candidate, remaining mandatory compatibility review, and that no G6 renewal/implementation is authorized by this leaf.
- A completion report using the standard fields, actual validation, limitations, runtime model/effort evidence if exposed, and no invented test/build evidence.
- The final committed diff is restricted to the four allowed leaf files; `git diff --check` passes.

## Model and attempt policy

- **Policy:** `binding-api-designer` row in `docs/agentic/MODEL_POLICY.md`.
- **Requested route:** `openai-codex/gpt-5.6-terra`, reasoning `medium`.
- **Observed runtime:** inherited `gpt-5.6-terra`; effective reasoning unknown unless runtime metadata exposes it. Record actual metadata, do not infer.
- **Attempt policy:** one evidence-driven review pass; if unresolved unsafe ABI representation remains, return a concrete finding/handoff rather than retrying or escalating into another role.
- **Quota/rate-limit rule:** on an actual quota/rate-limit error, stop immediately without state changes or further writes and report the exact blocker.

## Git, reporting, and stop conditions

Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role binding-api-designer -- <git-subcommand and arguments>` for all Git operations (for example, `-- status --short`, not `-- git status --short`). Before commit, verify origin, branch `hermes/dns-implementation-20260913`, exact staged allowed-path diff, and `diff --check`. Commit the leaf artifacts and push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; then read back that exact origin ref through the wrapper and report the commit/ref.

Return results to `protocol-orchestrator`. Do not update `workflow-state.yaml`, close gates, dispatch anyone, or push to merge/master. Stop and return `BLOCKED` if input ancestry is absent, the candidate cannot be read at the exact revision, the allowed boundary conflicts, or a quota/rate-limit error occurs. No further delegation is permitted.
