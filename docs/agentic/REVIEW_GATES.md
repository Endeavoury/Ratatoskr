# Review gates

Gates are evidence contracts. The orchestrator checks presence, scope, independence
and disposition; the designated reviewer judges technical correctness. Authors never
approve their own artifacts. A reviewer may share a role name with an author only
in a separate assignment/agent identity; record authors and reviewers. If independent
review cannot be obtained, record BLOCKED rather than self-approving.

Independence concerns the subject being approved, not the review record the reviewer
writes. A security reviewer can record its independent judgment of implementation;
it cannot approve implementation or a fuzz harness it authored. G0 is administrative
request intake against the user's scope, not self-approval of technical truth.

Every gate uses [gate-review.md](../../.agentic/templates/gate-review.md) with exact
input revisions. A changed input invalidates affected approvals. Missing evidence,
unresolved mandatory questions, or wrong-role modifications fail the gate.

| Gate | Required artifacts | Responsible reviewer | Pass condition | Failure and return route |
| --- | --- | --- | --- | --- |
| G0 Request accepted | request, manifest, state plan, scope/authorization | orchestrator; maintainer resolves missing product choices | Target, workflow, deliverables, dependencies, applicable gates and change boundaries explicit | Ambiguous/conflicting scope → requester; incomplete records → orchestrator |
| G1 Specification inventory approved | inventory, discovery closure and source provenance | protocol-analyst, independent of inventory author | Normative sources, updates, errata and registries classified; exclusions justified | Missing/unverified source or authority → protocol-researcher |
| G2 Analysis approved | analysis, requirement IDs, G1 inputs | protocol-modeler with researcher source clarification if needed | Layout, state, errors, limits, extensions and effective rules testable; ambiguities resolved | Unsupported interpretation/missing behavior → protocol-analyst; missing source → researcher |
| G3 Model approved | semantic model and requirement map | protocol-api-designer | Language-independent entities/events/states cover requirements and stateful needs | Semantic loss/language coupling → protocol-modeler |
| G4 Native API design approved | API design, model, ABI baseline | binding-api-designer; compatibility-reviewer for ABI impact | Ownership/errors/buffers/streaming/features safely exposable; evolution explicit | Unsafe/incomplete contract → protocol-api-designer |
| G5 Canonical vectors approved | vector set, analysis/model/API references | protocol-test-engineer plus independent protocol-analyst interpretation review | Expected bytes/events independently grounded; positive/negative/boundary coverage; no production oracle | Wrong/missing expectation → vector-designer; disputed semantics → analyst |
| G6 Ready for implementation | G1–G5 records, scope, dependencies, approved revisions | orchestrator | Required design gates passed; dependencies available; exact implementation paths authorized | Any missing/stale approval → owning upstream role; no implementation starts |
| G7 Native implementation reviewed | implementation report/diff, test report, canonical trace, build evidence | protocol-test-engineer, independent of implementation author | Approved design implemented; independent native review and required tests execute and pass | Code defect → c-protocol-implementer; harness defect → independent test-engineer assignment; expectation dispute → vector-designer/analyst |
| G8 Security passed | security review, G7 evidence, threat model, remediation evidence | security-reviewer independent of fixes | No unresolved blocking findings; residual risks explicitly accepted within scope | Interpretation → analyst; API safety → API designer; code defect → implementer |
| G9 Fuzz evidence accepted | fuzz plan, results, corpus provenance, crash dispositions | security-reviewer independent of fuzz work | Applicable invariants exercised with recorded build/budget; blocking failures resolved | Strategy/harness → fuzz-engineer; crash → implementer; semantics → analyst/vector-designer |
| G10 Binding exposure completed | approved binding design, binding report, capability map, adapter and local packaging evidence | binding-api-designer independent of binding implementation | Required ABI capabilities safely exposed; adapters preserve canonical truth; package checks recorded | Mapping defect → binding-api-designer assignment; wrapper/packaging defect → binding-implementer |
| G11 Conformance passed | conformance report, native/vector and all in-scope binding evidence | conformance-reviewer | Equivalent protocol semantics across declared surfaces; differences justified as representation only | Native defect → implementer; mapping/wrapper defect → binding roles; expectation dispute → vector-designer |
| G12 Compatibility passed | compatibility report, baseline/diff, version/migration proposal, docs | compatibility-reviewer | ABI/source/binding/behavior compatibility impact explicit and accepted; deprecation/version policy followed | API contract → relevant designer; code deviation → implementer; product/version choice → maintainer |
| G13 Documentation completed | user docs, documentation report, design/conformance inputs | conformance-reviewer independent of docs author | Public behavior, lifecycle, errors, examples, limits and compatibility notes match evidence | Missing/inaccurate docs → documentation-writer; contract contradiction → artifact owner |
| G14 Final acceptance | final review, all applicable gate records, traceability, closed handoffs | final-reviewer independent of implementation | Mandatory artifacts current; gates approved; no unresolved handoffs; limitations and boundaries verified | Return to specific failed gate owner; never rubber-stamp completion |

G13 intentionally executes before G12 in the main workflow; IDs are identifiers,
not sequence numbers. G14 requires both. Reviewers can request specialist evidence
without becoming its author. Final-reviewer writes the final acceptance report;
orchestrator records the disposition and closes state only if acceptance passes.

Review assignments consume READY_FOR_REVIEW candidates for the gate they are
assigned; the candidate's own gate is not an entry prerequisite for its reviewer.
All earlier applicable approvals remain required. This applies to G1 inventory
review, BINDING_DESIGN mapping review, and every other author-to-reviewer handoff.

## Applicability and approval policy

At G0 list all gates with applicability and rationale. A review-only workflow may
require just G0, its scoped report review, and G14 scoped closure; it cannot claim
unexecuted implementation gates passed. ADD_BINDING reuses approved native G1–G9
evidence by revision/reference and adds mapping review before implementation, G10,
G11, G13, G12 and G14. Use a `BINDING_DESIGN` gate record reviewed by an independent
binding-api-designer (and protocol-api-designer for ABI questions).

A deferred feature is not a verified feature. Nonapplicable gates retain an approved
scope rationale with `applicable: false`; never label an unrun applicable check as
passing. G9 requires results for implementation work, not just a fuzz plan. Truly
inapplicable fuzzing requires a security-reviewer rationale and orchestrator scope
record. Shared-library versions, supported platforms, feature omissions and residual
security risks need maintainer decisions when existing policy/user scope does not
already settle them. Routine evidence review does not require repeated human approval.

Approval is local engineering acceptance, not permission to merge, publish packages,
deploy, or message external parties. This framework introduces no automatic CI gates
and no GitHub protection settings; future authorized work may integrate evidence
with the existing CI workflows.
