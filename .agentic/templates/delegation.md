# Delegated task

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | protocol-orchestrator |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

ACTIVE ROLE: <role>

ROLE: <same role>
GOAL: <concrete outcome>
SCOPE: <planning/review/implementation; explicit constraints>

MODEL AND REASONING:

- Policy: docs/agentic/MODEL_POLICY.md, row for <active-role>.
- Requested provider/model ID: <configured route and explicit model ID>.
- Requested reasoning effort: <supported effort>.
- Observed runtime provider/model/effort: <verified values or unknown>.
- Verification source: <session/provider metadata; never inferred from this prompt>.
- Context target: <soft target; required reading must remain complete>.
- Completion summary target: <normally 200–400 words plus artifact links>.
- User hard token/spend cap: <explicit cap or none supplied>.
- Attempt policy: <one evidence-driven correction, then bounded escalation>.
- Escalation trigger and next model/effort: <role-specific condition and setting>.
- Stop/checkpoint condition: <repeated failure, missing evidence, or actual hard cap>.

These are assignment metadata, not automatic Hermes configuration. Model changes
require a compatible configured session; do not silently use an incompatible worker.

TARGET:
<kind and ID; protocol, binding or component; dependency IDs>

REPOSITORY ROOT:
<absolute checkout path>

WORKFLOW / STAGE / ASSIGNMENT:
<IDs and workflow-state path>

READ FIRST:

- AGENTS.md
- .hermes/skills/<role>/SKILL.md
- docs/agentic/HANDOFFS.md
- docs/agentic/MODEL_POLICY.md
- <relevant lifecycle and gate contract>

REQUIRED INPUT ARTIFACTS:

- <repository-relative path, exact revision, approval record>

FILES/DIRECTORIES ALLOWED TO CHANGE:

- <concrete path and specific purpose; no broad wildcard authority>

FILES/DIRECTORIES THAT MUST REMAIN READ-ONLY:

- <upstream truth, vectors, implementation or other relevant protected paths>
- All paths outside the explicit allowed set.

EXPECTED OUTPUT ARTIFACTS:

- <path, artifact type, required content and revision evidence>

ACCEPTANCE CRITERIA:

- <observable criterion and reviewer/gate>

HANDOFF TARGET:
<role and unique handoff output path>

STOP CONDITIONS:
<missing prerequisites, boundary conflict, upstream ambiguity, completed output>

DELEGATION ALLOWANCE:
No further delegation unless explicitly enabled here with disjoint scopes.

CONTEXT CONTRACT:
You have fresh context. Do not assume parent chat history. Read the role before
work, announce ACTIVE ROLE, verify scope/input approvals, and obey role boundaries.
Do not perform another role's work. Write the standard completion report at
<assigned completion path>; do not update shared workflow state.
