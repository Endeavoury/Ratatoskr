# Artifact contract

## Repository structure

```text
.hermes/skills/<role>/SKILL.md      reusable role instructions
.agentic/templates/               uninstantiated starting documents
.agentic/schemas/                 structural JSON Schemas, no runtime
.agentic/workflows/<work-id>/       future concrete work; created on request
  request.md
  workflow-state.yaml
  manifest.yaml                    protocol/component or binding manifest
  artifacts/                       specification, analysis, model, design, vectors
  bindings/<binding-id>/           mapping/exposure evidence, if relevant
  reviews/                         numbered gate records and specialist reviews
  decisions/
  handoffs/
  delegations/
  completions/
```

All artifact paths are repository-relative. A work ID is a unique stable slug, not
just a protocol name; multiple changes may target one protocol. Target IDs and
binding IDs are arbitrary strings. Do not bake protocols or languages into schemas.
The directory tree is a convention, not executable scaffolding or an implementation
registry. A work item may reference approved artifacts from another work item.

## Identity, provenance and approvals

Delegations and completions also carry model/effort selection and actual usage
evidence under [MODEL_POLICY.md](MODEL_POLICY.md). State assignments reference the
delegation path; no runtime configuration or model-specific schema is introduced.

Every instantiated artifact has schema/version or template version, artifact ID,
workflow ID, target, owner role, status, revision, source artifact references,
assumptions, unresolved questions and limitations. Markdown templates carry these
as a metadata table; machine-readable templates use fields. A source reference
identifies a repository path plus Git commit or content digest. RFC references
include document/section, official URL, checked date, update/errata disposition.

Use stable requirement IDs, model element IDs, API operation IDs, vector IDs and
finding IDs. Trace requirements → model → API/capabilities → vectors → native
evidence → binding mappings → conformance. Not every requirement is a byte test:
timing, security policy, ABI and packaging requirements need the appropriate evidence.

Approval applies to content revisions, never a mutable path alone. Gate records
include input revisions, reviewer identity, pass/fail reasoning, evidence and
failure route. Use [decision-record.md](../../.agentic/templates/decision-record.md)
for rationale and tradeoffs. Artifact authors propose decisions about their owned
truth; cross-owner decisions require the affected owners and gate review.

## Templates and owners

| Template | Primary owner / use |
| --- | --- |
| `request.md` | orchestrator; user intent, scope and authorization |
| `protocol-manifest.yaml` | orchestrator; component profile, graph, applicability |
| `binding-manifest.yaml` | orchestrator; language target, native baseline, capability coverage |
| `workflow-state.yaml` | orchestrator; resumable stage/assignment/gate state |
| `specification-inventory.md` | protocol-researcher; discovery and authority |
| `protocol-analysis.md` | protocol-analyst; effective requirements and wire/state rules |
| `protocol-model.yaml` | protocol-modeler; language-independent semantics |
| `api-design.md` | protocol-api-designer; proposed native ABI contract |
| `vector-set.json` | vector-designer; canonical bytes/events/expectations |
| `implementation-report.md` | c-protocol-implementer; implementation trace/evidence |
| `test-report.md` | protocol-test-engineer; harness trace and execution evidence |
| `security-review.md` | security-reviewer; threat analysis and findings |
| `fuzz-plan.md`, `fuzz-results.md` | fuzz-engineer; strategy and actual campaign evidence |
| `binding-design.md` | binding-api-designer; ABI-to-language mapping concepts |
| `binding-report.md` | binding-implementer; exposure, adapters, packaging evidence |
| `conformance-report.md` | conformance-reviewer; native/binding semantic agreement |
| `documentation-report.md` | documentation-writer; user-facing contract coverage |
| `compatibility-report.md` | compatibility-reviewer; ABI/API/behavior/version impact |
| `final-review.md` | final-reviewer; independent acceptance recommendation |
| `gate-review.md` | designated independent gate reviewer |
| `decision-record.md` | responsible truth owner; orchestrator indexes it |
| `handoff.md` | source creates, destination resolves, orchestrator closes |
| `delegation.md` | orchestrator; complete fresh-context assignment |
| `completion-report.md` | each specialist for its own assignment |

Templates are instructions and placeholders only. Replace every placeholder and
remove instructional example rows before approval. Empty arrays mean “not yet
specified” in templates, not proof that a concrete protocol has no requirements.

## Canonical vectors

Canonical bytes use hex by default, base64 when justified, never hand-maintained
language-specific arrays. Record exact length and whether bytes include framing.
Keep readable request/response explanations and structured expectations separate
from wire bytes. Future adapters mechanically derive native/language byte sequences
from the same approved canonical source; generated forms cannot become new truth.

Each vector specifies requirements, preconditions, actor/connection/stream IDs where
needed, ordered inputs/events, logical time, bytes or local actions, expected output,
input consumption, state and error class. Zero or multiple responses are valid
scenario shapes. Optional `expected_after` observations on each event verify
intermediate state, consumption, error and component-specific semantic fields.
Capture malformed bytes exactly without normalization. Distinguish
semantic equality from required exact encoding. Round-trip invariants apply only
when both operations exist and information loss/canonicalization is defined.

## Schema scope

`workflow-state.schema.json` checks structural state fields; YAML state is interpreted
as the JSON data model. `vector-set.schema.json` checks basic event/byte containers.
Neither verifies specification truth, reviewer independence, reference existence,
dependency acyclicity, hex byte counts, state transition legality or gate completion.
Those are mandatory review checks documented here and in REVIEW_GATES.md. No schema
validator or build dependency is installed by this framework.

## Registry meaning

The protocol manifest's capability list is planning metadata. For each future binding,
the binding design/report records public ABI capability → binding surface → vector
adapter → evidence, with explicit supported/unsupported/deferred dispositions.
This is “protocol registry exposure”; it does not require inventing a new runtime
registry or modifying every existing binding. Reuse the repository's actual
registration patterns after inspecting them.
