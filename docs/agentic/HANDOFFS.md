# Delegation and handoffs

## Fresh-context delegation

Every child must be able to work from the delegation packet and repository alone.
Use [delegation.md](../../.agentic/templates/delegation.md). Include ROLE, GOAL,
SCOPE, target protocol/binding/component, repository root, workflow/stage IDs,
required input paths and revisions, allowed changes, read-only paths, expected
outputs, acceptance criteria, handoff target, and stop conditions. Include the exact
`.hermes/skills/<role>/SKILL.md` path in READ FIRST, together with `AGENTS.md` and the
relevant shared contracts. Pass the packet's content or an explicit instruction to
read its path; “continue what we discussed” is not sufficient.

Include requested and observed model/reasoning settings, context/summary targets,
attempt limits and the escalation trigger from [MODEL_POLICY.md](MODEL_POLICY.md).
Report unavailable settings honestly; they are runtime configuration, not role
instructions that a child can enact by naming a model.

For a direct user request there is no parent packet yet: the orchestrator records
the explicit user scope as the entry assignment before delegating. A directly invoked
specialist checks available prerequisites and records its own bounded entry scope,
then returns workflow coordination to the orchestrator. Missing state is expected
for new work; it is not evidence of approval. Explicit framework-only maintenance
can use the user request as its documentation-writer assignment without creating a
fictional protocol workflow or claiming any implementation gates passed.

At entry the specialist declares `ACTIVE ROLE: <role>`, checks its packet against
the skill, and verifies prerequisites. Missing scope or contradictory permissions
block writes. Allowed changes are the intersection of the role's ownership,
the packet's concrete paths and user authorization. All other artifacts are
read-only or out of scope. An allowed directory is not permission to change every
file inside it. Future implementation roles are definitions, not blanket authorization.

The child owns its output and a unique completion/handoff record, not the parent's
state file. It may not switch hats to fix an upstream input. If a separate role is
needed, request delegation by the parent. A fresh reviewer assignment may use the
same named skill as an author but must be a different agent/session identity that
did not author the artifact being approved. Record that identity in gate evidence.

## Handoff records

Use [handoff.md](../../.agentic/templates/handoff.md) for both blocking returns and
nonblocking questions. Required fields: ID, workflow/stage, source/destination roles,
target, reason, source artifact revisions, specific question and reproduction/evidence,
requested action, blocking flag, acceptance criteria, status and resolution.

The originator creates a READY_FOR_REVIEW handoff in its assigned unique path; the
orchestrator records it in state and routes it. The destination writes the resolution
section and links changed artifacts/decisions, setting READY_FOR_REVIEW. The
originator or designated independent reviewer checks acceptance; the orchestrator
marks the handoff COMPLETE and unblocks the stage. Do not delete the history.
For an unresolved question set BLOCKED or NEEDS_UPSTREAM_CHANGE as appropriate.

Nonblocking findings may be closed as explicitly deferred only with an owner,
tracking reference, rationale and accepted scope decision. They must not disguise
failed mandatory requirements. Final acceptance has no unresolved handoffs.

## Backtracking examples

| Finding | Return route and required action |
| --- | --- |
| Implementation disagrees with bytes | protocol-test-engineer checks harness/adapter; vector-designer checks canonical expectation; analyst resolves specification interpretation if ambiguous |
| Vector is correct; implementation is wrong | c-protocol-implementer fixes implementation; expectations remain unchanged |
| Specification discovery is incomplete | protocol-researcher adds official sources; analyst and downstream owners reassess |
| Model cannot express a required transition | protocol-modeler revises model after analyst clarifies semantics |
| Binding cannot safely represent ABI lifetime | binding-api-designer, then protocol-api-designer if ABI change is needed; never copy the protocol into the binding |
| Security finding concerns interpretation | protocol-analyst; discovery question to researcher |
| Security finding concerns exposed ownership | protocol-api-designer, then implementer after approved design |
| Security finding concerns bounds/overflow | c-protocol-implementer, with independent security re-review |
| Two bindings disagree | conformance-reviewer localizes against native evidence, then binding-api-designer or binding-implementer |
| API change breaks compatibility | relevant API designer proposes migration/versioning; compatibility-reviewer rechecks |

Changes to approved truth require owner revision, a decision record and renewed
approval. The orchestrator invalidates affected dependent approvals; it must not
edit those artifacts itself to move the workflow forward.

## Completion report

Every specialist writes [completion-report.md](../../.agentic/templates/completion-report.md)
and ends its response with the same fields: ROLE, STATUS, SUMMARY, ARTIFACTS CREATED,
ARTIFACTS MODIFIED, DECISIONS MADE, OPEN QUESTIONS, BLOCKERS, HANDOFF REQUIRED,
RECOMMENDED NEXT ROLE. Include paths/revisions, validation evidence and limitations.
Report missing execution capability as a limitation, never a passing check.

An author finishing work reports READY_FOR_REVIEW. A reviewer reports its gate
disposition and supporting record. Only the orchestrator determines whether the
workflow can advance or close.
