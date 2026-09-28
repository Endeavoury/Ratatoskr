# Delegated task — C-COMP-001 remediation

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-delegation-g4-compatibility-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | Routing baseline `0cb6e27b265c38e42d09d61c0883f1a086df8835` |
| Source artifacts | Compatibility delivery at `0cb6e27b265c38e42d09d61c0883f1a086df8835`; immutable subject candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` |
| Assumptions | G3 remains approved; G4 remains `CHANGES_REQUESTED`; no numeric policy is implied. |
| Open questions | Numeric defaults/limits must be handed to maintainer through this orchestrator if no existing policy answers them. |
| Limitations | Design-only response; no realization or gate approval. |

ACTIVE ROLE: protocol-api-designer

ROLE: protocol-api-designer / g4-compatibility-remediation-001

GOAL: Produce one fresh, immutable, design-only DNS API candidate resolving compatibility finding `C-COMP-001`.

SCOPE: Correct only the blocking public C design defects identified by the independent compatibility delivery. Do not author a review or advance any gate. Do not implement headers/code, vectors, bindings, tests, fuzzing, docs, or public API realization.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-api-designer row.
- Requested: `gpt-5.6-sol` / medium.
- Observed parent runtime: `openai-codex` / `gpt-5.6-terra`; effort unknown. A prompt does not configure the child; record actual child values if exposed, otherwise unknown.
- Context target: 8,000–16,000 tokens with complete required reading.
- Summary target: 200–400 words plus artifact paths.
- User hard cap: none.
- Attempt policy: one bounded design attempt; do not retry through another role.
- Escalation: complex ownership/ABI evolution could justify Sol/high only in a separately configured session; missing policy must hand off, not be invented.
- Stop: missing/stale input, conflicting path authority, numeric-policy gap, quota/rate limit, or completed READY_FOR_REVIEW delivery.

## Target and workspace

- Repository and command directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/`.
- You are a fresh leaf and may not delegate.
- Shared-state writer: protocol-orchestrator only.
- You may edit the compatibility handoff `Resolution` section only, after creating your candidate; do not close the handoff.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-api-designer/SKILL.md`
3. `docs/agentic/HANDOFFS.md`, `DIRECTORIES.md`, `ARTIFACTS.md`, `REVIEW_GATES.md`, `MODEL_POLICY.md`, `ARCHITECTURE.md`, `PROTOCOL_LIFECYCLE.md`
4. `docs/abi.md` and `docs/repository-layout.md`
5. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
6. This packet and compatibility delivery:
   - `agents/compatibility-reviewer/g4-compatibility-review-001/compatibility-report.md`
   - `agents/compatibility-reviewer/g4-compatibility-review-001/reviews/g12-g4-compatibility-support-review.md`
   - `agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/g4-compatibility-to-api-designer-c-comp-001.md`
   - `agents/compatibility-reviewer/g4-compatibility-review-001/completion-report.md`
7. Immutable candidate `agents/protocol-api-designer/g4-binding-safety-remediation-001/api-design.md` at `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`; G3 model and analysis at state-recorded revisions; `include/ratatoskr/` and `docs/abi.md` at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.

## Allowed writes

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/README.md`
- `.../api-design.md`
- `.../decisions/` (only if a concrete design decision is needed)
- `.../handoffs/` (only if a policy/upstream blocker is found)
- `.../completion-report.md`
- `agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/g4-compatibility-to-api-designer-c-comp-001.md` — `Resolution` section only.

All other paths are read-only, especially workflow state, all existing agent workspaces except the named Resolution section, production source, public headers, tests, fuzzers, bindings, and docs.

## Required candidate content and acceptance

1. Use non-conflicting C ordinary identifiers for the request-state typedef and accessor; show every corrected affected signature.
2. Fully define `ratos_dns_request_options` and `ratos_dns_limits`: public field order/types, mandatory `struct_size` prefix, initialization, reserved input/output rules, append-only evolution, ownership/nullability/copy semantics, defaults and validation, and ABI implications.
3. Preserve ABI-1 baseline symbols, result ownership, and synchronous DNS behavior. Remain callback-free and compatible with the approved synchronous DNS model.
4. Do not invent numeric defaults or resource policy. If existing inputs do not determine values, state symbolic/default-source behavior and create a maintainer handoff rather than selecting values.
5. Add traceable `C-COMP-001` resolution text and candidate revision/hash in the allowed handoff Resolution, with `READY_FOR_REVIEW`; do not mark it complete.
6. Write a standard `READY_FOR_REVIEW` completion report with exact inputs, actual checks, model/runtime evidence, limitations, and next requirement: fresh independent compatibility re-review.
7. Before commit: use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- <git arguments>`; verify branch, staged allowed paths, and `git diff --check`. Commit and push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then wrapper-read that exact remote ref. Preserve the pre-existing untracked binding re-review-001 workspace.

HANDOFF TARGET: Return candidate and the allowed handoff-resolution to protocol-orchestrator. A fresh independent compatibility review is required later but is explicitly not routed by you or this assignment.

STOP CONDITIONS: On missing/stale prerequisite, authority conflict, quota/rate error, or unavailable Git wrapper, do not change shared workflow state; write only an owned blocker/completion record if permitted and return it. Do not claim G4 approval.