# Delegated task — fresh G7 DNS-G8-001 limits remediation review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g7-g8-limits-rereview-001-delegation` |
| Root task / project | `ratatoskr-dns-implementation-20260913` / `Ratatoskr` |
| Workflow / stage | `dns-implementation-20260913` / G7 `native_verification` |
| Target / owner | `protocol/dns` / `protocol-orchestrator` |
| Assigned role / leaf ID | `protocol-test-engineer` / `g7-g8-limits-rereview-001` |
| Status | `IN_PROGRESS` |
| Candidate revision | `git:a8d98b75e9c450734808d5a672a2023e83589fb0` |
| Artifact-delivery revision | `git:a424049521c97969c32ef37f026c63803224b146` |

ACTIVE ROLE: protocol-test-engineer

ROLE: Fresh independent `protocol-test-engineer` G7 reviewer in hierarchy `workspace-orchestrator → protocol-orchestrator → protocol-test-engineer`.

GOAL: Establish an independent technical G7 disposition for the DNS-G8-001 configured-limits remediation candidate. Inspect required evidence and run viable real validation; do not repair or author production/test/canonical truth.

SCOPE: G7 only. Do not start, route, approve, or prepare G8, G9, or later stages. You must be independent of `c-protocol-implementer/g8-limits-remediation-001`, `protocol-test-engineer/g7-native-verification-001`, and `protocol-test-engineer/g7-remediation-rereview-002`. Record that independence in your reports.

## Model and attempts

- Policy/default: `docs/agentic/MODEL_POLICY.md`, protocol-test-engineer row: `gpt-5.6-terra`, `medium`.
- Requested route/effort: `openai-codex/gpt-5.6-terra`, medium.
- Observed route before dispatch: parent session `openai-codex/gpt-5.6-terra`; effort and child usage telemetry unknown unless runtime exposes them. Record requested versus actual and attempt count honestly.
- Attempt policy: one independent evidence pass; no corrective authoring. Any defect, stale input, test failure, unavailable validation prerequisite, quota/rate-limit error, or path conflict is a bounded disposition/handoff, not a repair.
- Stop condition: On an actual quota/rate-limit error, stop immediately with no state change. Do not delegate further.

## Root, workspace, and ownership

- Absolute repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Absolute control workspace: `/home/hermes/hermes-workspace/.hermes-control`.
- Your unique artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-g8-limits-rereview-001/`.
- Parent routing workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g7-g8-limits-rereview-routing-001/`.
- The parent alone writes `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
- You are the sole writer of your exact workspace. Preserve unrelated untracked workspaces.

## Read first

1. `AGENTS.md`; `.hermes/skills/protocol-test-engineer/SKILL.md`.
2. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md,SECURITY_MODEL.md}` and `docs/contributing.md`.
3. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
4. Required candidate inputs:
   - `agents/c-protocol-implementer/g8-limits-remediation-001/{implementation-report.md,completion-report.md,handoffs/dns-g8-001-remediation-to-protocol-orchestrator.md}`;
   - `agents/security-reviewer/g8-security-review-001/handoffs/dns-g8-001-configured-limits-enforcement.md`;
   - prior G7 reports/handoffs only as stale context, never as approval of this candidate;
   - approved G1–G6 analysis/model/API/vector records referenced by current state and relevant existing G7 evidence.

## Required verification and acceptance

1. Verify `a8d98b75e9c450734808d5a672a2023e83589fb0` is the precise review candidate and `a424049521c97969c32ef37f026c63803224b146` delivers its required author artifacts. Record branch, candidate, and actual origin readback.
2. Independently inspect the five authorized remediation paths and the existing native/G7 test evidence read-only. Assess the G8 handoff acceptance subjects: finite defaults and configured UDP, TCP-frame, total-RR, name-expansion, compression-pointer, typed-field, outstanding-request, and connection limits; terminal request resource-limit/no-result behavior. Do not convert this into G8 review or make a security verdict.
3. Run viable real validation relevant to the candidate, including feasible strict compilation and existing DNS/G7 regression builds/runs. Attempt the documented CMake/CTest workflow only if `cmake` is available. Record commands, revision, results, and limitations; in particular record absent `cmake` rather than claiming CMake/CTest passed.
4. Produce an independent `test-report.md` containing exact inputs, reviewer identity/independence, evidence, actual execution, limitations, and exactly one G7 disposition: `APPROVED`, `CHANGES_REQUESTED`, `REJECTED`, or `BLOCKED`. Return code defects to `c-protocol-implementer`, expectation disputes to vector-designer/analyst, and harness defects to a separate independent test-engineer assignment.
5. Produce `completion-report.md` using the standard fields and an optional formal handoff only when needed. Do not update state and do not self-approve any artifact you author.

## Exact write boundary

Allowed writes, and no others:

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-g8-limits-rereview-001/README.md`
- `.../test-report.md`
- `.../handoffs/` only for a required formal finding/blocker handoff
- `.../completion-report.md`

Read-only / forbidden: `src/`, `include/`, `tests/`, canonical vectors, analysis/model/API/design, all prior agent workspaces, root `request.md`, `manifest.yaml`, `workflow-state.yaml`, reviews, and every other repository path. Do not modify production, tests, canonical vectors, or previous artifacts.

## Delivery and return

Before committing or pushing, independently verify the regular executable wrapper at `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`. Use no raw Git commit/push: only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- <git arguments>`. Commit only the completed allowed leaf artifacts after validation and only if no quota/rate-limit condition occurred. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never merge or push master, then read back `origin/hermes/dns-implementation-20260913` with the wrapper. If wrapper validation/delivery fails, record the exact blocker and do not claim remote delivery.

HANDOFF TARGET: `protocol-orchestrator`, through your test/completion reports and any formal handoff in your workspace. A future fresh G8 re-review is outside this assignment and must not be routed by you.
