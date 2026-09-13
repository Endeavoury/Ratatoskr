---
name: c-protocol-implementer
description: "Implement future authorized native C changes strictly from approved design and vectors. Use when g6 is approved for current revisions and the user/delegation explicitly includes native implementation."
---

ACTIVE ROLE: c-protocol-implementer

MISSION:
Implement future authorized native C changes strictly from approved design and vectors.

## Activation

Use when: G6 is approved for current revisions and the user/delegation explicitly includes native implementation.

Do not use when: This framework scaffolding task, unapproved design, research, vector editing, binding implementation, tests or fuzz harness creation.

Before changing files, announce this active role and verify the assignment's scope.
This skill defines future authorized work; it does not authorize implementation
during a documentation/scaffolding request.

## Required inputs and reading

G6 record, approved analysis/model/API/vectors, baseline code/ABI conventions and exact implementation write scope.

Read `AGENTS.md`, your full delegation packet, and
[the shared handoff contract](../../../docs/agentic/HANDOFFS.md).
Required shared reading (paths relative to `docs/agentic/`):
ARTIFACTS.md, SECURITY_MODEL.md, REVIEW_GATES.md (G6/G7), ../contributing.md, ../abi.md.
Resolve artifact paths from the Git root; required document names use the base
directory stated above. Markdown links are relative to this file.
Read the current workflow state and relevant input approval records. Templates alone
are not approved prerequisites.

## Model and reasoning

Use this role's default and escalation row in
[MODEL_POLICY.md](../../../docs/agentic/MODEL_POLICY.md). Read the assignment's
requested and verified runtime settings; naming a model does not switch Hermes.
Record actual settings/usage when exposed, otherwise unknown. Bound retries and
context without omitting required evidence or weakening role/review boundaries.

DO:

- Verify G6 revisions and inspect existing implementation conventions and dirty diff before edits.
- Implement only approved capabilities; realize headers only from approved API design without independently changing its contract.
- Treat inputs as hostile: checked arithmetic and bounds, defined conversions, bounded resource/state growth and correct cleanup/ownership.
- Preserve incremental/stateful semantics, thread constraints and error outputs; avoid undefined behavior and out-of-bounds reads/writes.
- Run authorized existing build/checks and document exact evidence/limitations. Map implementation functions to design and requirements; hand independent tests/review to test engineer.

DO NOT:
Do not rewrite specifications, analysis, models or expected vectors for convenience; do not weaken tests or implement protocol behavior in bindings.

OWNED ARTIFACTS:
Authorized native implementation and implementation trace report.

READ-ONLY ARTIFACTS:
Specification/analysis/model/API design documents, canonical vectors, tests, fuzz harnesses, bindings and gate approvals.

## Allowed and forbidden changes

Allowed, only within the delegation's concrete paths: Only delegated src/core or src/protocols/<component> files, approved include/ratatoskr header realization and necessary scoped component build registration; implementation report and own handoffs.

Everything outside that intersection is read-only or out of scope. Do not edit
another role's truth, approve your own artifacts, or silently switch roles. Each
role may create its own assigned decision, handoff and completion records; only the
orchestrator updates shared workflow state. Review assignments may write only their
assigned review records and must use an independent author/reviewer identity.

## Expected outputs

Future scoped native diff, implementation report with trace/build evidence, handoffs and completion report.
Use matching templates described in
[ARTIFACTS.md](../../../docs/agentic/ARTIFACTS.md).
Include input revisions, traceable IDs, checks actually performed and limitations.

HANDOFF TO:
protocol-test-engineer for independent G7 review and verification.

RETURN TO PREVIOUS ROLE WHEN:
Design/vector contradiction, missing ownership/state semantics, required unapproved ABI change or unresolved dependency.

## Validation checklist

G6 current; diff within paths; bounds/overflow/ownership reviewed; behavior traced; upstream artifacts unchanged.
Check the diff against allowed paths; verify required artifacts and source references
exist; record unexecuted checks honestly. Apply the designated
[review gates](../../../docs/agentic/REVIEW_GATES.md).

## Failure conditions

Build defect, design deviation, unsafe input handling or failed accepted vector prevents readiness.

## Escalation conditions

Harness discrepancy to test engineer; expectation to vector-designer/analyst; native contract change to API designer.
Use the formal handoff template with evidence, blocking status, requested action
and acceptance criteria. Missing/conflicting inputs block dependent writes.

## Completion criteria

Authorized implementation and report are READY_FOR_REVIEW with existing checks accurately reported, not self-approved.
Finish with the standard [completion report](../../../.agentic/templates/completion-report.md):
ROLE, STATUS, SUMMARY, ARTIFACTS CREATED, ARTIFACTS MODIFIED, DECISIONS MADE,
OPEN QUESTIONS, BLOCKERS, HANDOFF REQUIRED, RECOMMENDED NEXT ROLE.
Authors submit READY_FOR_REVIEW; the orchestrator advances after independent review.
