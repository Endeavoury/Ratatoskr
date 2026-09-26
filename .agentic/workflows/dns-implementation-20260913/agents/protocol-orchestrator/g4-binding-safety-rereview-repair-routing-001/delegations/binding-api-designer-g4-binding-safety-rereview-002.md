# Delegation: corrected G4 binding-safety re-review

## Identity and scope

- **Root task / project / workflow:** `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913`
- **Hierarchy:** `workspace-orchestrator -> protocol-orchestrator -> binding-api-designer` (leaf; no further delegation).
- **Assignee identity:** `binding-api-designer / g4-binding-safety-rereview-002`, one fresh independent child session.
- **Repository root and command working directory:** `/home/hermes/hermes-workspace/projects/Ratatoskr`
- **Target branch:** `hermes/dns-implementation-20260913`
- **Routing baseline:** `cde744a21343b1cddf8abdd585ff2f46907bc4fb`.

**READ FIRST:** `AGENTS.md`; this packet; `.hermes/skills/binding-api-designer/SKILL.md`; `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md,BINDING_LIFECYCLE.md}`; `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`; and the original packet plus its completion and blocked leaf records at `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g4-binding-safety-rereview-routing-001/` and `../binding-api-designer/g4-binding-safety-rereview-001/`.

## Immutable read-only inputs

1. Remediation candidate `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-binding-safety-remediation-001/api-design.md` at Git `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`; also read its completion report at that revision.
2. Corrected original review `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/reviews/g4-binding-safety-review.md` at Git `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4`.
3. Corrected original return handoff `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-review-001/handoffs/g4-binding-safety-to-api-designer.md` at Git `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353`.
4. ABI baseline `include/ratatoskr/` and `docs/abi.md` at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`.

Wrapper-read every revision-bound input and calculate/check its SHA-256 before technical assessment. Do not substitute mutable worktree content. If any required input is missing, stale, or digest-mismatched, write accurate local assigned artifacts only and report `BLOCKED`; do not claim delivery.

## Permitted writes and hard boundary

Write **only** in the new unique leaf directory `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-rereview-002/`:

- `README.md`
- `reviews/g4-binding-safety-rereview.md`
- optional `handoffs/` only if disposition is `CHANGES_REQUESTED` or `BLOCKED`
- `completion-report.md`

Everything else is read-only, including `workflow-state.yaml`, production, headers, tests, bindings, documentation, vectors, all historical artifacts, and all other agent directories. No implementation or technical truth changes.

## Sole review task

Conduct exactly one fresh independent G4 **binding-safety re-review only** of the remediation candidate, limited exactly to:

- `F-BIND-001`: fixed-width representations; concrete layout, initialization, reserved/versioning/validity rules; named accessors.
- `F-BIND-002`: `name` text/NUL/lifetime plus endpoint binary address pointer/length/nullability/lifetime.

Explicitly declare independence from original API author `protocol-api-designer/g4-api-design-001`, remediation author `protocol-api-designer/g4-binding-safety-remediation-001`, and first reviewer `binding-api-designer/g4-binding-safety-review-001`. Your sole permitted disposition is `APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED` for these two criteria. Do **not** grant overall G4 approval, decide compatibility, perform compatibility review, or route any later stage. State that compatibility review is separately mandatory and unperformed.

## Delivery and completion

For every Git state command, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role binding-api-designer -- ...`; never raw Git. Preserve unrelated untracked files. Commit only your assigned artifacts and push exactly `HEAD:refs/heads/hermes/dns-implementation-20260913`. After delivery, wrapper-fetch and wrapper-read `refs/remotes/origin/hermes/dns-implementation-20260913` (or exact remote equivalent). If any wrapper/remote/integrity failure occurs, accurately record only allowed local artifacts and do not claim remote delivery. If a quota/rate-limit error occurs, stop immediately, make no state changes, and report the exact error.

Completion must name all artifact paths; local and remote SHA or blocker; exact revisions/digests; independence; criterion disposition; commands/checks; allowed-path boundary evidence; actual model/effort telemetry as exposed or `unknown`; one bounded attempt; limitations; and return to `protocol-orchestrator / g4-binding-safety-rereview-repair-routing-001`.

## Model policy

Requested setting: `gpt-5.6-terra` / medium. Actual route/effort is runtime evidence, not a prompt setting; record exposed values or `unknown`. One bounded attempt; no escalation or delegation.