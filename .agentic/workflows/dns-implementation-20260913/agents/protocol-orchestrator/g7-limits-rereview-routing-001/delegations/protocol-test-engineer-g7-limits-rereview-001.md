# Delegation: fresh independent G7 limits review

| Field | Value |
| --- | --- |
| Template version | 1 |
| Delegation ID | `dns-implementation-20260913-protocol-test-engineer-g7-limits-rereview-001` |
| Root task / project / workflow | `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913` |
| Stage / gate | `native_verification` / fresh independent `G7` review only |
| Hierarchy | `workspace-orchestrator → protocol-orchestrator → protocol-test-engineer` (leaf; no subdelegation) |
| Assignee / identity | `protocol-test-engineer/g7-limits-rereview-001`, a new unique reviewer identity |
| Repository root and command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/` |
| Requested model / effort | `openai-codex/gpt-5.6-terra` / `medium` |
| Actual route / effort | Unknown until runtime exposes it; report honestly, do not claim requested settings were applied |
| Attempt policy | One bounded independent review pass; no broad retry |

## Goal

Independently review the delivered DNS-G7-LIMITS-001 remediation at candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` and produce the designated G7 review evidence. This is neither a G8 security review nor an approval/routing of G8, G9, or any later stage.

Declare in the review record and completion report that this assignment is fresh and independent of `c-protocol-implementer/g7-limits-remediation-001` and all prior G7 review authors, including `protocol-test-engineer/g7-native-verification-001`, `protocol-test-engineer/g7-remediation-rereview-002`, and `protocol-test-engineer/g7-g8-limits-rereview-001`. Do not author production code, tests, vectors, canonical truth, or shared workflow state.

## Read first

1. `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`
2. `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/protocol-test-engineer/SKILL.md`
3. `/home/hermes/hermes-workspace/projects/Ratatoskr/docs/agentic/{ARTIFACTS.md,SECURITY_MODEL.md,REVIEW_GATES.md,DIRECTORIES.md,HANDOFFS.md,MODEL_POLICY.md}` and `docs/contributing.md`
4. This packet at `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g7-limits-rereview-routing-001/delegations/protocol-test-engineer-g7-limits-rereview-001.md`
5. Current `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`

## Exact inputs (read-only)

- Delivered source candidate: `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` (must be checked as an ancestor of the current delivery line).
- Delivered artifacts / exact origin readback at assignment routing: `git:3bb81004050ca860ce8d9572f4e834847daf5b96`.
- Remediation artifacts:
  - `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-limits-remediation-001/implementation-report.md`
  - `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-limits-remediation-001/completion-report.md`
  - `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-limits-remediation-001/handoffs/dns-g7-limits-001-remediation-to-protocol-orchestrator.md`
- Prior G7 finding context, not approval: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-g8-limits-rereview-001/{test-report.md,completion-report.md,handoffs/dns-g7-limits-001-resource-classification.md}` at delivery `git:15d3fc3de3eb733aac7f04d07ba7da02ffe809bd`.
- Production subject: `src/protocols/dns/dns_parser.c` at candidate revision; all production source/headers are read-only.
- Approved G1-G6 and canonical inputs remain exactly those referenced by the current workflow state.

## Allowed writes

Only these paths:

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/test-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/reviews/g7-limits-rereview.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/handoffs/` (only if a finding/blocker requires the formal return)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/completion-report.md`
- Destination **Resolution section only** of `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-limits-remediation-001/handoffs/dns-g7-limits-001-remediation-to-protocol-orchestrator.md`.

Everything else is forbidden: all production code, headers, tests, vectors, fixtures, build files, upstream truth, all shared workflow state, other role workspaces except the stated Resolution section, G8/G9/later artifacts, master, and external publication.

## Required review checks and acceptance

1. Verify the candidate and artifact delivery commits exist, candidate ancestry to the current delivery line, and `origin/hermes/dns-implementation-20260913` using **only** `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- <git arguments>` for every Git readback, commit, and push. Never raw-Git commit/push/readback. Do not merge or push master; if committing, push exactly `HEAD:refs/heads/hermes/dns-implementation-20260913` and exact-read that origin ref afterward.
2. Verify required remediation artifacts exist, report `READY_FOR_REVIEW`, and delivery/candidate diffs obey their declared boundary. Preserve pre-existing modified workflow state and historical untracked agent directories.
3. Perform an independent G7 review against candidate `7a0875e…`; do not rely on the implementer claim. Verify **both** configured resource-limit cases: `max_name_expansion_bytes` exhaustion and `max_compression_pointer_traversals` exhaustion.
4. For each case, establish whether the path preserves resource-limit classification/terminal behavior and **no-result behavior** (no takeable result), using actual reproducible evidence where environment capability permits. Record commands, revision, environment, results, and any limitations honestly. Do not claim unexecuted checks passed.
5. Write `test-report.md` and `reviews/g7-limits-rereview.md` with exact input revisions, fresh-independence declaration, G7-only disposition (`APPROVED`, `CHANGES_REQUESTED`, or `BLOCKED`), evidence, findings, and return owner if needed. Write a completion report in the required template fields. The reviewer decides the technical disposition; do not self-update state.

## Git delivery and reporting

Before delivery, use the required wrapper for `diff --check`, status/readback, commit, push, and exact origin readback. Commit only your allowed artifacts and permitted Resolution section under the `protocol-test-engineer` wrapper identity. Report the candidate revision, resulting delivery commit, exact origin readback, changed paths, actual model/effort if exposed (else unknown), checks/results, G7-only disposition, and blockers.

Return the full summary to `protocol-orchestrator`; do not route any other role/stage. A completion message is not state advancement.

## Stop conditions

- If any prerequisite, candidate/delivery integrity, independence condition, or required artifact is missing/conflicting: make no out-of-scope change; write only permitted blocker artifacts if possible and report `BLOCKED` to the orchestrator.
- If an actual quota or rate-limit error occurs: stop immediately; do not change state or retry broadly; report the exact blocker.
- If the evidence identifies a code defect, return it only to `c-protocol-implementer` through a formal handoff; do not fix it.
- If G7 is approved, stop after recording G7-only evidence. Do not initiate, imply, or approve G8/G9/later work.
