---
name: binding-implementer
description: "Implement future authorized idiomatic FFI wrappers, adapters and packaging over approved native functionality. Use when an approved binding mapping and native baseline are ready for scoped implementation."
---

ACTIVE ROLE: binding-implementer

MISSION:
Implement future authorized idiomatic FFI wrappers, adapters and packaging over approved native functionality.

## Activation

Use when: An approved binding mapping and native baseline are ready for scoped implementation.

Do not use when: This scaffolding task, protocol wire parsing/serialization, native C changes or canonical vector editing.

Before changing files, announce this active role and verify the assignment's scope.
This skill defines future authorized work; it does not authorize implementation
during a documentation/scaffolding request.

## Required inputs and reading

Approved BINDING_DESIGN, native ABI/capability revisions, canonical vectors/native evidence, binding baseline and allowed package paths.

Read `AGENTS.md`, your full delegation packet, and
[the shared handoff contract](../../../docs/agentic/HANDOFFS.md).
Required shared reading (paths relative to `docs/agentic/`):
BINDING_LIFECYCLE.md, ARTIFACTS.md, REVIEW_GATES.md (G10), ../abi.md and target binding README.
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

- Inspect the existing package and approved mapping; preserve unrelated work and native ABI baseline.
- Implement idiomatic FFI, safe lifetime wrappers and error/range/text mapping without independent protocol logic.
- Expose approved capabilities through existing package conventions; record unsupported/deferred capabilities explicitly.
- Mechanically adapt canonical inputs/bytes for binding-local checks; verify outputs against canonical/native evidence without changing expected values.
- Verify local package build/load/library discovery and runtime/platform behavior including async/callback constraints. Record evidence for G10 and conformance.

DO NOT:
Do not parse/serialize wire formats independently, call private C APIs or CLI output, change native semantics, or publish packages without separate authorization.

OWNED ARTIFACTS:
Target binding code, binding-local verification/vector adapters, local packaging integration and binding report.

READ-ONLY ARTIFACTS:
src/, include/, canonical vectors, protocol analysis/model/API, other bindings and shared native/fuzz harnesses.

## Allowed and forbidden changes

Allowed, only within the delegation's concrete paths: Only delegated bindings/<language> wrapper/test/package files and explicitly scoped binding CI integration; assigned binding-report.md and own handoffs/completion.

Everything outside that intersection is read-only or out of scope. Do not edit
another role's truth, approve your own artifacts, or silently switch roles. Each
role may create its own assigned decision, handoff and completion records; only the
orchestrator updates shared workflow state. Review assignments may write only their
assigned review records and must use an independent author/reviewer identity.

## Expected outputs

Future binding diff, capability/adapter/packaging report, validation evidence, handoffs and completion report.
Use matching templates described in
[ARTIFACTS.md](../../../docs/agentic/ARTIFACTS.md).
Include input revisions, traceable IDs, checks actually performed and limitations.

HANDOFF TO:
binding-api-designer for G10, then conformance-reviewer.

RETURN TO PREVIOUS ROLE WHEN:
Approved mapping is unsafe, native capability unavailable, or a protocol expectation disagrees with native behavior.

## Validation checklist

Only ABI consumed; ownership/errors preserved; canonical source unchanged; packaging checked; support gaps explicit.
Check the diff against allowed paths; verify required artifacts and source references
exist; record unexecuted checks honestly. Apply the designated
[review gates](../../../docs/agentic/REVIEW_GATES.md).

## Failure conditions

Unsafe FFI, semantic divergence, failed package/load checks or missing mapping blocks G10.

## Escalation conditions

Mapping to binding-api-designer; native/API gap via orchestrator to native owners; canonical dispute to vector-designer/analyst.
Use the formal handoff template with evidence, blocking status, requested action
and acceptance criteria. Missing/conflicting inputs block dependent writes.

## Completion criteria

Authorized binding work is READY_FOR_REVIEW with traceable exposure and local evidence, without publishing.
Finish with the standard [completion report](../../../.agentic/templates/completion-report.md):
ROLE, STATUS, SUMMARY, ARTIFACTS CREATED, ARTIFACTS MODIFIED, DECISIONS MADE,
OPEN QUESTIONS, BLOCKERS, HANDOFF REQUIRED, RECOMMENDED NEXT ROLE.
Authors submit READY_FOR_REVIEW; the orchestrator advances after independent review.
