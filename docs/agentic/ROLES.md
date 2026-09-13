# Role ownership matrix

Each role's model/reasoning default and escalation trigger are centralized in
[MODEL_POLICY.md](MODEL_POLICY.md). Model choice never changes the boundaries below.

Each name links to the role's operational skill. **OWNER** means responsibility for
that artifact's truth; **MAY MODIFY** means narrowly delegated supporting changes;
**READ ONLY** means evidence the role consumes, never changes to obtain a pass.
**NO ACCESS / OUT OF SCOPE** means no task reason to inspect or modify that area,
not an enforced filesystem permission.

All roles are out of scope for unrelated projects/workflows, secrets, user trust
configuration and external publication unless separately authorized. Everything not
explicitly owned/allowed is read-only when relevant, otherwise out of scope. Reviewer
access to implementation is read-only. Reviewers do not repair their own findings.

| Role | OWNER | MAY MODIFY (only when delegated) | READ ONLY | NO ACCESS / OUT OF SCOPE |
| --- | --- | --- | --- | --- |
| [protocol-orchestrator](../../.hermes/skills/protocol-orchestrator/SKILL.md) | Requests, manifests, workflow state, delegations | Handoff closure/index records | All specialist outputs and gate findings | Unrelated targets, secrets and external actions |
| [protocol-researcher](../../.hermes/skills/protocol-researcher/SKILL.md) | Specification inventory | Own source decisions | Scope, existing analysis and relevant code for discovery | Unrelated targets, secrets and external actions |
| [protocol-analyst](../../.hermes/skills/protocol-analyst/SKILL.md) | Requirements/analysis | Own interpretation decisions | Inventory, model, design, vectors | Unrelated targets, secrets and external actions |
| [protocol-modeler](../../.hermes/skills/protocol-modeler/SKILL.md) | Semantic model/IR | Own modeling decisions | Inventory, analysis, API/vector feedback | Unrelated targets, secrets and external actions |
| [protocol-api-designer](../../.hermes/skills/protocol-api-designer/SKILL.md) | Native API design | Own design decisions | Model, headers, ABI baseline, binding concerns | Unrelated targets, secrets and external actions |
| [vector-designer](../../.hermes/skills/vector-designer/SKILL.md) | Canonical vectors and expectations | Own vector decisions | Sources, analysis, model, API, implementation discrepancies | Unrelated targets, secrets and external actions |
| [c-protocol-implementer](../../.hermes/skills/c-protocol-implementer/SKILL.md) | Native implementation, report | Approved header realization and scoped build registration | Upstream truth, vectors, tests, bindings | Unrelated targets, secrets and external actions |
| [protocol-test-engineer](../../.hermes/skills/protocol-test-engineer/SKILL.md) | Native/shared harness, test report | Scoped test build registration; independent implementation review records | Native code, canonical vectors, designs | Unrelated targets, secrets and external actions |
| [security-reviewer](../../.hermes/skills/security-reviewer/SKILL.md) | Security findings/review | Assigned G8/G9 records and finding verification | All relevant code, truth, tests and fuzz evidence | Unrelated targets, secrets and external actions |
| [fuzz-engineer](../../.hermes/skills/fuzz-engineer/SKILL.md) | Fuzz strategy/harness/results | Scoped fuzz registration and derived corpus | Native code, canonical vectors, model/API | Unrelated targets, secrets and external actions |
| [binding-api-designer](../../.hermes/skills/binding-api-designer/SKILL.md) | Binding mapping/design | Assigned mapping/native exposure reviews | Public ABI, native truth, binding implementation | Unrelated targets, secrets and external actions |
| [binding-implementer](../../.hermes/skills/binding-implementer/SKILL.md) | Target binding, report | Binding-local adapters/tests/packaging and scoped CI | C/public headers, canonical truth, other bindings | Unrelated targets, secrets and external actions |
| [conformance-reviewer](../../.hermes/skills/conformance-reviewer/SKILL.md) | Conformance report | Assigned G11/G13 review records | Native/binding evidence, truth, docs | Unrelated targets, secrets and external actions |
| [documentation-writer](../../.hermes/skills/documentation-writer/SKILL.md) | User/developer docs | Explicitly scoped framework skills/templates/context | Technical truth, implementation, live workflow state | Unrelated targets, secrets and external actions |
| [compatibility-reviewer](../../.hermes/skills/compatibility-reviewer/SKILL.md) | Compatibility report | Assigned G12 review record | Baseline/candidate ABI/API/code and docs | Unrelated targets, secrets and external actions |
| [final-reviewer](../../.hermes/skills/final-reviewer/SKILL.md) | Final acceptance report | Assigned G14 review record | All workflow artifacts, gates and diff | Unrelated targets, secrets and external actions |

All specialists may write their own uniquely assigned completion, decision and
handoff records. Only the orchestrator edits shared state; the destination owner may
resolve a handoff and the orchestrator closes it after verification. Gate records are
owned by designated independent reviewers, not automatically by artifact authors.

The vector designer owns expected case outcomes **within approved analyst semantics**.
The analyst owns interpretation; the researcher owns source authority. A vector
designer cannot override analysis, and a test engineer cannot override vectors.
Designers own proposals; implementers realize accepted designs without changing the
contract. Native ABI changes require native API design review even when discovered
during binding work.

For G7 a test engineer who authored a harness needs a separate reviewer assignment
for that harness. For mapping review, use a fresh binding-api-designer assignment
independent of the design author. Final and security review must be independent of
the implementation being reviewed. The orchestrator records reviewer identities
and must not turn a role switch in the same authoring context into self-approval.

The documentation-writer may maintain this framework only for an explicit framework
request. Ordinary documentation work cannot rewrite role boundaries or gates.
Modification rights remain the intersection of role, delegation paths and user scope.
