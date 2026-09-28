# Delegated task — independent DNS G1 review and analysis candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-protocol-analyst-analysis-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-orchestrator |
| Status | IN_PROGRESS |
| Revision | Delivery baseline Git `051d010d889155dd26906161473f2c1fcb3af81b` |
| Source artifacts | Inputs listed below, all committed at `051d010d889155dd26906161473f2c1fcb3af81b` with recorded SHA-256 digests |
| Assumptions | The authorized scope is native unicast DNS stub/client query construction and response parsing, UDP with TCP fallback; no DNS implementation is authorized. |
| Open questions | EDNS/unsupported-extension response behavior and special query-type scope must be resolved or explicitly remain a blocking product/source handoff. |
| Limitations | This assignment may review G1 and author a G2 candidate only. It may not self-approve G2, update shared state, or broaden scope. |

ACTIVE ROLE: protocol-analyst

ROLE: protocol-analyst

GOAL: Independently review the `research-001` DNS specification inventory for G1. Only if G1 is approved, author a source-grounded DNS protocol-analysis candidate ready for independent G2 review.

SCOPE: G1 review plus the conditional G2 candidate only. Do not implement DNS; do not modify production code, headers, tests, fuzzers, CLI, docs, configuration, credentials, GitHub settings, or shared workflow state. Do not delegate further.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-analyst row.
- Requested provider/model ID: `gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: model `gpt-5.6-terra`; effort unknown (`agent.reasoning_effort` unset).
- Verification source: parent session `hermes config get model.default`; no child-specific runtime metadata is available in this packet.
- Context target: 8,000–16,000 task-specific tokens; required reading and authoritative sources may not be omitted.
- Completion summary target: 200–400 words plus artifact paths and revisions.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction; then produce a bounded handoff rather than repeat.
- Escalation trigger and next model/effort: conflicting normative rules or subtle state/framing requirements → Sol/high in a separately configured session; do not silently change model.
- Stop/checkpoint condition: a missing authority, unresolved mandatory interpretation, prohibited-write need, or completed output.

## Target and directories

- Target: `protocol/dns`, native unicast stub/client only; operating-system UDP/TCP exchange is a dependency.
- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/`.
- Workspace owner: protocol-analyst / `analysis-001` / this delegated leaf identity.
- Shared source directories: none.
- Shared-file writer / ordering: protocol-orchestrator is the sole writer of `workflow-state.yaml`; this leaf must not edit it. The researcher handoff is read-only except no destination resolution is authorized by this packet; record findings in this workspace instead.
- Existing-path exception: none.

## Workflow/stage/assignment

- Workflow: `dns-implementation-20260913`, type `ADD_PROTOCOL`.
- G1 subject stage: `research`, which is `READY_FOR_REVIEW` at dispatch.
- Conditional author stage: `analysis`, assigned as `IN_PROGRESS`; its gate is G2.
- Shared state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
- Delivery branch/ref: `hermes/dns-implementation-20260913` / `refs/heads/hermes/dns-implementation-20260913`.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-analyst/SKILL.md`
3. `docs/agentic/{WORKFLOW,ROLES,HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,PROTOCOL_LIFECYCLE,MODEL_POLICY}.md`
4. `.agentic/workflows/dns-implementation-20260913/{request.md,manifest.yaml,workflow-state.yaml}`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/{specification-inventory.md,handoffs/research-to-analyst-g1.md,completion-report.md}`
6. This packet.

## Required inputs and exact revisions

All paths are repository-relative and committed at `051d010d889155dd26906161473f2c1fcb3af81b`:

- `workflow-state.yaml`, SHA-256 `5148497f11c927217abad7f53317f85b5bf730ff2ee839ecdd43660ef7581cd2`.
- `request.md`, SHA-256 `63b399c8a44abb0036dae556796cfa358391850a1376f0561fba87b013a03284`; G0 administrative approval record exists.
- `manifest.yaml`, SHA-256 `c47e4d741c53e8d08315a02d29fda2aa64b1708ef21b4b79d4da57c7e81c6cf4`.
- `agents/protocol-researcher/research-001/specification-inventory.md`, SHA-256 `9aa91abf9cb3a98c0fd3fb061f26d2c16e57ee4685c5efa729d3af7dfdef8073`; author identity is `protocol-researcher <protocol-researcher@roygerritse.nl>` in commit `051d010…`.
- `agents/protocol-researcher/research-001/handoffs/research-to-analyst-g1.md`, SHA-256 `e41ed5cc5818ef41df06511980b584eaa66b131d2c34ed08d0a69e92bada0d0b`; status `READY_FOR_REVIEW`.

Independently inspect relevant official RFC Editor/RFC texts, errata/update relationships, and IANA DNS Parameters. Repository code and existing DNS documentation are discovery context only, not specification authority.

## Files allowed to change

Only these role-owned files under the assigned workspace:

- `reviews/g1-inventory-review.md` — assigned independent G1 record with exact subject revision, reviewer identity, official-source evidence, independence declaration, and APPROVED/CHANGES_REQUESTED/BLOCKED disposition.
- `protocol-analysis.md` — only if G1 is approved; requirement IDs, traceability, wire/framing/state/error/limit/security behavior, scope/exclusions, and testability.
- `decisions/` — only source-backed interpretation decisions needed for the candidate.
- `handoffs/` — a precise handoff to `protocol-researcher` if G1 fails or a mandatory source/authority gap blocks analysis; otherwise a G2 handoff to `protocol-modeler`.
- `completion-report.md` — required status, validation, commit/push evidence, and next role.

All paths outside that list are read-only. Do not edit the researcher handoff, workflow root, project-orchestrator workspace, or any implementation surface.

## Required work and acceptance criteria

1. Declare active role and verify root, origin, branch, `HEAD`, clean/owned worktree scope, and each required input revision before writing.
2. Independently evaluate G1 under `REVIEW_GATES.md`: classify normative sources, formal updates/obsolescence, relevant errata, and IANA registry authority for the exact native unicast stub/client scope; verify exclusions/deferred areas are explicit. Record exact official sources/sections checked and the reviewer identity. You are independent of the inventory author.
3. If G1 fails or is blocked: do **not** author downstream analysis as approved truth. Write a concrete source-gap handoff to `protocol-researcher` with document/section/disposition, report `CHANGES_REQUESTED` or `BLOCKED`, and leave G2 candidate absent.
4. If G1 passes: write the independent G1 record with `APPROVED` recommendation, then author `protocol-analysis.md` as a **candidate** for G2. It must include stable requirements and source mapping; DNS header/message/name/RR layouts; UDP/TCP framing and incremental-consumption behavior; request/response correlation and client state; malformed/unknown/unsupported/negative-result handling; observable limits/resource policy gaps; security-sensitive rules; extensions/exclusions; error/recovery/ownership implications; and evidence planned for model/vector/API stages. Resolve mandatory interpretation ambiguity with a source-backed decision or route it upstream; never invent behavior.
5. Write a G2 handoff to `protocol-modeler` with the candidate revision and explicit statement that G2 is unapproved and requires independent review. Do not self-approve G2.
6. Validate: placeholders removed; all cited local paths exist; source links/sections recorded; `git diff --check`; and `git diff --name-only` shows only allowed analyst workspace paths.
7. If completed output exists, commit only the analyst workspace after validation with `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-analyst -- commit -m "docs(dns): review inventory and add analysis candidate"`; before pushing, confirm branch/ref and working-tree scope; push only using `git-agent.sh --role protocol-analyst -- push origin HEAD:refs/heads/hermes/dns-implementation-20260913`; then run `git ls-remote --heads origin refs/heads/hermes/dns-implementation-20260913` and record local/remote hashes. No merge. If the wrapper prevents a valid role-scoped commit or push, record the blocker rather than bypass it.

## Handoff target and stop conditions

- On G1 failure/block: `protocol-researcher` via the analyst workspace `handoffs/`, then await orchestrator routing.
- On G1 approval and candidate completion: `protocol-modeler` for independent G2 review, via analyst workspace `handoffs/`.
- Stop on missing/stale inputs, failed G1, need for prohibited writes, unresolved mandatory source ambiguity, or after a validated role-scoped commit/push attempt and completion report.

## Delegation allowance and context contract

No further delegation. You have fresh context: do not assume parent chat history; read the specified files, obey the role boundary, and do not update shared state. This task authorizes no source implementation, test/fuzz changes, merge, credential/configuration change, or publication.
