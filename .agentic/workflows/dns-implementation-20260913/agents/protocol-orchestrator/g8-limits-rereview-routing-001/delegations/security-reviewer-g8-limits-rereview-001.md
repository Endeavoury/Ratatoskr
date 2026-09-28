# Delegated task — ready but not dispatched

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-security-reviewer-g8-limits-rereview-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `BLOCKED` — runtime model/effort route unavailable; no child dispatched |
| Revision | Candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; author-artifact delivery `git:3bb81004050ca860ce8d9572f4e834847daf5b96` |
| Source artifacts | G7 approved review at `agents/protocol-test-engineer/g7-limits-rereview-001/reviews/g7-limits-rereview.md`; prior G8 review/report/handoff at `agents/security-reviewer/g8-security-review-001/`; approved upstream requirements/model/API/vectors named by the existing G8 packet and workflow state |
| Assumptions | Candidate and author delivery are ancestors of repository HEAD verified before routing. |
| Open questions | None for routing; Sol/high availability must be supplied by a separately configured session/profile. |
| Limitations | No security leaf, G8 disposition, CMake, or CTest is implied by this packet. |

ACTIVE ROLE: security-reviewer

ROLE: security-reviewer

GOAL: Perform one fresh, independent G8 re-review of the DNS-G8-001 configured-limits remediation at candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` after the approved fresh G7 review.

SCOPE: Security review only. Independently assess DNS-G8-001 against the candidate, the approved G7 review, approved upstream requirements/model/API/vectors, and the prior G8 finding. Perform bounded adversarial evidence checks. Record G8 disposition and residual risks. Do not fix code, alter tests/vectors/API, update workflow state, route G9, or claim later-stage status.

## MODEL AND REASONING

- Policy: `docs/agentic/MODEL_POLICY.md`, security-reviewer row.
- Requested provider/model ID: `openai-codex/gpt-5.6-sol`.
- Requested reasoning effort: `high`.
- Observed runtime provider/model/effort: parent/delegation route `openai-codex/gpt-5.6-terra`; `delegation.model` has no configured override; `agent.reasoning_effort` is unset.
- Verification source: `hermes config get delegation.model` (no override) and `hermes config get agent.reasoning_effort` (unset, exit 1), with current parent runtime observed as `openai-codex/gpt-5.6-terra`.
- Context target: roughly 8,000–16,000 task-specific tokens, without omitting required reading.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one bounded independent review; no retry under a cheaper/incompatible route.
- Escalation trigger and next model/effort: unresolved adversarial interaction across components → Astra/high, restricted to the finding and only after documented Sol failure.
- Stop/checkpoint condition: missing prerequisite, conflicting candidate revision, boundary violation, unavailable Sol/high route, quota/rate-limit error, or completed G8 record.

These settings are assignment metadata and not a model switch. Do not dispatch until the actual child route is independently verified as Sol/high.

## TARGET
`protocol/dns`; G8 security gate; DNS-G8-001 configured-limits enforcement remediation.

## REPOSITORY ROOT
`/home/hermes/hermes-workspace/projects/Ratatoskr`

## WORKING DIRECTORIES

- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/`.
- Workspace owner: one fresh independent `security-reviewer` leaf; record its runtime delegation/session identity in the review.
- Shared source directories: none; all source is read-only.
- Shared-file writer / ordering: only the security reviewer writes its workspace. The protocol-orchestrator alone updates shared state after verification.
- Existing-path exception: the prior G8 handoff may be read; only the protocol-orchestrator may write its Closure section after independent verification.

## WORKFLOW / STAGE / ASSIGNMENT
`dns-implementation-20260913` / `security` / `g8-limits-rereview-001`; shared state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.

## READ FIRST

- `AGENTS.md`
- `.hermes/skills/security-reviewer/SKILL.md`
- `docs/agentic/SECURITY_MODEL.md`
- `docs/agentic/HANDOFFS.md`
- `docs/agentic/REVIEW_GATES.md`
- `docs/agentic/DIRECTORIES.md`
- `docs/agentic/MODEL_POLICY.md`
- current `workflow-state.yaml`
- this packet

## REQUIRED INPUT ARTIFACTS

- Candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; author-artifact delivery `git:3bb81004050ca860ce8d9572f4e834847daf5b96`.
- Approved fresh G7 record: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/reviews/g7-limits-rereview.md` (candidate/delivery stated above; disposition APPROVED).
- Prior G8 review, security report, and DNS-G8-001 handoff: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/{reviews/g8-security-review.md,security-review.md,handoffs/dns-g8-001-configured-limits-enforcement.md}` at delivery `git:90a02df18522b6c311e236dc03c82583971c7511`.
- Approved analysis/model/API/vector records named in the existing G8 assignment and workflow state, read-only.

## FILES/DIRECTORIES ALLOWED TO CHANGE

- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/security-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/reviews/g8-limits-rereview.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/handoffs/`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/completion-report.md`

## FILES/DIRECTORIES THAT MUST REMAIN READ-ONLY

- Production source, headers, public API, tests, fuzz, bindings, docs, vectors, and build configuration.
- All prior role workspaces, including prior G7/G8 reviews and handoffs.
- `request.md`, `manifest.yaml`, and `workflow-state.yaml`.
- All paths outside the explicit allowed set.

## EXPECTED OUTPUT ARTIFACTS

- Assigned workspace README with the actual reviewer identity and actual model/effort evidence.
- `security-review.md`: threat boundaries, adversarial checks, DNS-G8-001 remediation evidence, reachable findings, severity/blocking rationale, and explicit residual risks.
- `reviews/g8-limits-rereview.md`: G8 disposition with exact inputs/revisions, independence declaration, evidence, limitations, and failure route if applicable.
- Handoff only if the disposition requires an upstream change.
- `completion-report.md` using the standard fields and honestly recording CMake/CTest availability.

## ACCEPTANCE CRITERIA

- Reviewer is a fresh identity independent from `c-protocol-implementer/g8-limits-remediation-001`, `c-protocol-implementer/g7-limits-remediation-001`, all prior G7 reviewers, and `security-reviewer/g8-security-review-001`.
- Actual child runtime is verified as `openai-codex/gpt-5.6-sol` with `high` reasoning before substantive review; otherwise stop without a reviewer disposition.
- Candidate and G7 approval revisions match this packet.
- Bounded adversarial evidence checks address hostile limits, allocation/iteration/copy/traversal, terminal no-result behavior, and relevant UDP/TCP paths.
- Reviewer writes only the assigned workspace and does not fix code.
- If APPROVED, no unresolved blocking G8 finding remains and residual risks are explicit. If CHANGES_REQUESTED, retain that disposition faithfully and identify the owner/required remediation.

## HANDOFF TARGET
`protocol-orchestrator`, through the assigned completion/report artifacts. The orchestrator may update G8/security only after independently verifying the designated reviewer record. No G9 routing is authorized by this packet.

## STOP CONDITIONS
Stop without state advancement for missing/stale approvals, non-Sol/high runtime, candidate mismatch, reviewer self-review/conflict, forbidden-path requirement, quota/rate-limit error, or any unresolved blocking finding. Do not make fixes.

## DELEGATION ALLOWANCE
No further delegation.

## CONTEXT CONTRACT
You have fresh context. Read the role and all required inputs; announce ACTIVE ROLE; verify scope, model route, independence, and revisions. Do not assume parent chat. Write the standard completion report in the assigned workspace and do not update shared workflow state.