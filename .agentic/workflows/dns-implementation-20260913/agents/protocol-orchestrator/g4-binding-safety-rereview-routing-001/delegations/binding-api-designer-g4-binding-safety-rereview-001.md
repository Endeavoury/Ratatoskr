# Delegation: G4 binding-safety re-review

## Identity and scope

- **Root task / project / workflow:** `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913`
- **Hierarchy:** `workspace-orchestrator -> protocol-orchestrator -> binding-api-designer` (leaf)
- **Assignee identity:** `binding-api-designer / g4-binding-safety-rereview-001`, a fresh independent child session.
- **Repository root and command working directory:** `/home/hermes/hermes-workspace/projects/Ratatoskr`
- **Target branch:** `hermes/dns-implementation-20260913`
- **Delivery baseline:** routing baseline `232940996939a2316e6b55f708e0f99bb9b621a4`; remediation delivery `262c445a1b519b3baaa04f71fbcd59074c1baab0`.

Read `AGENTS.md`, this packet, `.hermes/skills/binding-api-designer/SKILL.md`, `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md}`, `docs/agentic/BINDING_LIFECYCLE.md`, the current `workflow-state.yaml`, and the listed inputs before writing.

## Exact read-only inputs

1. Remediation candidate `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/api-design.md`, commit `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`.
2. Its `completion-report.md` at the same commit.
3. Prior review and return handoff: `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/reviews/g4-binding-safety-review.md` and `handoffs/g4-binding-safety-to-api-designer.md`, reviewer revision `c2ab2aa30496edf70163b46b9572c0b155488eb4`.
4. ABI baseline `include/ratatoskr/` and `docs/abi.md` at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.

## Permitted writes and outputs

Write **only** under `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-rereview-001/`:

- `README.md`
- `reviews/g4-binding-safety-rereview.md`
- optional `handoffs/` record only if `CHANGES_REQUESTED` or `BLOCKED`
- `completion-report.md`

All other paths are read-only. Do not edit shared state, historical artifacts or handoff resolutions. Do not modify production/header/test/binding/doc/vector files.

## Review task and acceptance

Conduct a fresh independent G4 **binding-safety re-review only** of the remediation candidate against exactly these prior findings:

- `F-BIND-001`: fixed-width representations; concrete layout, initialization, reserved/versioning/validity rules; named accessors.
- `F-BIND-002`: `name` text/NUL/lifetime plus endpoint binary address pointer/length/nullability/lifetime.

Record a criterion-by-criterion G4 binding-safety re-review with cited candidate sections and exact input revisions/digests. Declare independence explicitly from (a) original API candidate author `protocol-api-designer/g4-api-design-001`, (b) remediation author `protocol-api-designer/g4-binding-safety-remediation-001`, and (c) first reviewer `binding-api-designer/g4-binding-safety-review-001`. You may decide only `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED` for this binding-safety re-review; never grant overall G4 approval or decide compatibility. State that compatibility review is separately mandatory and unperformed.

Completion must include actual model/effort or `unknown`, commands/checks, input revisions/digests, allowed-path boundary evidence, disposition, and limitations. No compatibility review, implementation, headers, tests, bindings, docs, vectors, G4 overall approval, or later-stage routing.

## Delivery discipline

Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role binding-api-designer -- ...` for all Git state commands. Commit the leaf artifacts and push exactly `HEAD:refs/heads/hermes/dns-implementation-20260913`; then wrapper-fetch and wrapper-read `refs/remotes/origin/hermes/dns-implementation-20260913` (or exact remote equivalent) to prove the remote SHA. Do not use raw Git. Preserve unrelated worktree changes. On any quota/rate-limit, stop immediately, make no shared-state change, and report the exact error. If input is stale/missing or wrapper/remote delivery fails, record only accurate allowed local artifacts and do not claim delivery.

## Handoff

Return completion summary with artifact paths, local/remote SHA or exact blocker, criterion disposition, and independence declaration to `protocol-orchestrator / g4-binding-safety-rereview-routing-001`. The orchestrator alone verifies delivery and may update shared state; it must not advance G4/native API design beyond `CHANGES_REQUESTED` or `IN_PROGRESS` until this re-review and the separately mandatory compatibility review are independently satisfied.

## Model policy

Requested policy setting: `gpt-5.6-terra` / medium. Observed child route is determined by Hermes delegation configuration; record actual exposed model/effort or `unknown`. One bounded review attempt; no escalation without evidence.