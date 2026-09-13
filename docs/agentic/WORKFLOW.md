# Workflow and routing contract

## Entry routing

The orchestrator inspects the user request, repository revision, existing state,
artifact approvals, and target/dependency graph. It chooses the narrowest specialist
whose prerequisites are satisfied. A direct skill invocation still checks those
prerequisites; it cannot manufacture an approval.

Select the model and reasoning from [MODEL_POLICY.md](MODEL_POLICY.md), verify the
effective Hermes route, and record both in the delegation packet. Escalate a bounded
quality problem; missing upstream truth still follows the normal handoff route.

| Request | Workflow | Entry role / route |
| --- | --- | --- |
| Add protocol X | `ADD_PROTOCOL` | orchestrator → protocol-researcher |
| Analyze protocol X | scoped `REVIEW_PROTOCOL` | protocol-analyst after inventory approval; otherwise researcher |
| Create vectors for X | scoped `REVIEW_PROTOCOL` | vector-designer after approved analysis/model/API |
| Implement approved protocol X | existing implementation workflow | c-protocol-implementer only after G6 |
| Extend protocol X | `EXTEND_PROTOCOL` | researcher/analyst for changed requirements and impact |
| Add transport X | `ADD_TRANSPORT` | researcher → analyst; dependency/composition scope |
| Add protocol extension X | `ADD_PROTOCOL_EXTENSION` | researcher → analyst; extension profile |
| Review protocol X | `REVIEW_PROTOCOL` | orchestrator selects scoped evidence/review specialists |
| Review protocol security | `SECURITY_REVIEW` | security-reviewer |
| Add a language binding | `ADD_BINDING` | binding-api-designer → binding-implementer |
| Why do two bindings differ? | `CONFORMANCE_REVIEW` | conformance-reviewer |
| Will this break ABI? | scoped `REVIEW_PROTOCOL` | compatibility-reviewer |

Workflow types are routing labels. Protocol, transport, extension and language IDs
are free strings, not a fixed list. Analysis-only requests end with reviewed analysis;
review-only requests end with a report and handoffs, not unrequested fixes.

## Full protocol flow

```text
REQUEST → protocol-researcher → protocol-analyst → protocol-modeler
→ protocol-api-designer → vector-designer → implementation-ready gate (G6)
→ c-protocol-implementer → protocol-test-engineer → security-reviewer
→ fuzz-engineer → binding-implementer → conformance-reviewer
→ documentation-writer → compatibility-reviewer → final-reviewer
```

The orchestrator owns each transition. Production/design consumers require approved
inputs; review assignments consume submitted candidates to establish their gate.
A completion message alone is never an approval. Before binding implementation, insert
`binding-api-designer` for any new or changed ABI mapping; reuse an approved mapping
only if its capability and revision coverage are still valid. Binding design also
participates in native API review. See [gates](REVIEW_GATES.md) for review ownership.

Gate IDs are stable labels, not numeric execution order: G13 (documentation) precedes
G12 (compatibility) in this flow; G14 follows both. Security and compatibility concerns
may be raised early even though their final evidence gates occur later.

## Binding flow

```text
REQUEST → binding-api-designer → mapping approval
→ binding-implementer (FFI, registry exposure, vector adapters, packaging)
→ conformance-reviewer → documentation-writer
→ compatibility-reviewer → final-reviewer
```

Use approved native capability/ABI/vector artifacts as prerequisites. An existing
protocol does not have to be redesigned to add a language. Missing native evidence
becomes a linked upstream task, not permission to duplicate protocol logic.
See [binding lifecycle](BINDING_LIFECYCLE.md).

## Durable state and status

Use [workflow-state.yaml](../../.agentic/templates/workflow-state.yaml) and its
[schema](../../.agentic/schemas/workflow-state.schema.json). The orchestrator is the
single writer of state. Specialists write their assigned artifacts, handoffs and
completion reports, including intended next steps; reviewers write gate records.

| Status | Meaning |
| --- | --- |
| `NOT_STARTED` | Not yet assigned or executed |
| `IN_PROGRESS` | Assigned work with recorded role and scope |
| `BLOCKED` | Required input, capability or decision unavailable |
| `NEEDS_UPSTREAM_CHANGE` | A blocking handoff identifies the responsible earlier owner |
| `READY_FOR_REVIEW` | Author complete; evidence submitted, not approved |
| `CHANGES_REQUESTED` | Reviewer identified remediable defects |
| `APPROVED` | Independent reviewer accepted the specified artifact revisions |
| `REJECTED` | Current proposal declined; replacement needs a new decision/revision |
| `SUPERSEDED` | Replaced evidence/state retained for history |
| `COMPLETE` | Workflow or assigned task closed after its required acceptance |

Normal stage progression: NOT_STARTED → IN_PROGRESS → READY_FOR_REVIEW → APPROVED.
Failures branch to BLOCKED, NEEDS_UPSTREAM_CHANGE, or CHANGES_REQUESTED and return to
IN_PROGRESS after resolution. REJECTED/SUPERSEDED records stay historical. Workflow
COMPLETE requires G14 or the scoped final gate specified at G0; it is not an alias
for “agent stopped.” Specialists report READY_FOR_REVIEW, not self-approval.

In the state template, `native_implementation` has no separate gate: it reaches
READY_FOR_REVIEW, which permits `native_verification` to start as a review consumer.
G7 approves both implementation and verification evidence; the orchestrator then
marks both stages APPROVED. Other stages advance through their assigned gate.
For any gate, the assigned reviewer can read its READY_FOR_REVIEW candidate before
that gate passes; it must still check earlier prerequisite approvals.

`scope_mode` is an execution boundary. A planning request stops at its requested
design/planning deliverables and scoped final review; remove later execution stages
from the active plan or record them as future work. A review request cannot dispatch
remediation implementation. The full template graph is illustrative, not authority
to run every stage. Record actual user-authorized mode at G0.

## Resumption and concurrent work

1. Read `AGENTS.md`, this contract, and all relevant workflow states. If no state
   exists, instantiate templates; if multiple targets match, resolve target intent.
2. Verify the recorded baseline and input revisions against files/Git. Preserve
   unrelated uncommitted edits. Never infer approval from a filename or chat summary.
3. Read unresolved handoffs, decisions and gate records. Identify stale descendants
   of any changed artifact and invalidate their approvals before proceeding.
4. Select a ready stage whose prerequisites are approved, or a review assignment
   whose candidate is READY_FOR_REVIEW as described above. Record
   role, assignment ID, unique workspace from [DIRECTORIES.md](DIRECTORIES.md),
   command working directory, allowed paths and input revisions in a delegation packet.
5. Review outputs, boundary adherence, and independent gate findings before updating
   state. Record evidence references and the next stage even if the session ends.

The dependency graph permits independent binding targets or review evidence work in
parallel after common inputs are approved. Assign disjoint write paths and separate
review records; only the parent updates state. `active_role` is the coordinator's
current focus; the `assignments` list records all concurrent specialists. Do not have
two agents edit one artifact, approve their own work, or advance from provisional
inputs. Subagents must not delegate further without an explicit delegation allowance.

When upstream content changes, mark affected approvals SUPERSEDED, record why, route
owners to refresh dependent artifacts, and rerun affected gates. Unaffected evidence
may be reused only with recorded revision/impact justification. An instruction or
template change does not automatically rewrite active workflow contracts.
