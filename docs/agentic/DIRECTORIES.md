# Agent working directories

Every assignment has its own directory, including reviewers and the orchestrator:

```text
.agentic/workflows/<work-id>/agents/<role>/<assignment-id>/
```

Use the exact role name from the table below. Assignment IDs distinguish concurrent
agents, different binding targets, retries with a new owner, and independent reviews
by agents using the same role. Never share an assignment directory between writers.
The orchestrator assigns the concrete path before work starts. For direct framework
maintenance, the documentation-writer records its entry scope in its own directory,
as permitted by [HANDOFFS.md](HANDOFFS.md).

Reusable starter directories for all 16 roles are in
[agent-workspaces](../../.agentic/templates/agent-workspaces/). Copy only the needed
role directory into the assigned `<assignment-id>/`, then replace its README with
concrete scope and paths. These templates are not active agents or approved work.

## Directory ownership map

In this table, every role has the workspace above with its own role name substituted.
Reports, owned truth, decisions, handoffs and completion records go in that workspace.
A `reviews/` subdirectory holds only that assignment's independently authored reviews.
Directory eligibility below must still be narrowed to exact files in the assignment;
it is not blanket write permission. See [ROLES.md](ROLES.md) for artifact ownership.

| Role / workspace segment | Workspace outputs | Eligible shared repository paths |
| --- | --- | --- |
| `protocol-orchestrator` | Delegations, administrative G0 record, coordination completion | Workflow-root `request.md`, `manifest.yaml`, `workflow-state.yaml`; handoff/index closure only |
| `protocol-researcher` | `specification-inventory.md`, source decisions | None; source and code discovery is read-only |
| `protocol-analyst` | `protocol-analysis.md`, interpretation decisions, assigned independent reviews | None |
| `protocol-modeler` | `protocol-model.yaml`, modeling decisions, assigned independent reviews | None |
| `protocol-api-designer` | `api-design.md`, design decisions, assigned independent reviews | None; public headers are read-only design inputs |
| `vector-designer` | `vector-set.json`, vector decisions | None; canonical vectors live in the assigned workspace |
| `c-protocol-implementer` | `implementation-report.md` | `src/protocols/<component>/`, `src/core/`; approved header realization in `include/ratatoskr/`; scoped component CMake registration |
| `protocol-test-engineer` | `test-report.md`, assigned independent gate reviews | `tests/<component>/`, `tests/core/`, `tests/integration/`, derived fixtures in `tests/fixtures/<component>/`; scoped test CMake registration |
| `security-reviewer` | `security-review.md`, G8/G9 records | None; implementation and fuzz evidence are read-only |
| `fuzz-engineer` | `fuzz-plan.md`, `fuzz-results.md` | `fuzz/<component>/`, derived corpus and scoped fuzz CMake registration |
| `binding-api-designer` | `binding-design.md`, mapping decisions and assigned independent reviews | None; `bindings/<language>/` and public headers are read-only design inputs |
| `binding-implementer` | `binding-report.md` | `bindings/<language>/` including local tests, examples and packaging; explicitly assigned binding CI files |
| `conformance-reviewer` | `conformance-report.md`, G11/G13 records | None; source, vectors and documentation are read-only |
| `documentation-writer` | `documentation-report.md` | Assigned `docs/`, README and binding guides; explicit framework maintenance may also edit `AGENTS.md`, `.hermes/skills/`, `.agentic/templates/`, `.agentic/schemas/` and `.agentic/README.md` |
| `compatibility-reviewer` | `compatibility-report.md`, G12 record | None; ABI, source and documentation are read-only |
| `final-reviewer` | `final-review.md`, G14 record | None; all reviewed artifacts and shared state are read-only |

## Working directory and shared source

Run commands from the repository root unless a tool requires a component/package
root. Record both command working directory and artifact workspace in the delegation.
Resolve artifact paths from the repository root, never relative to an agent's shell
working directory. Keep build output in existing build/package output directories;
use a separate build directory per concurrent build when they would otherwise clash.

Native source, headers, CLI, tests, bindings, build and packaging retain the layout in
[repository-layout.md](../repository-layout.md). Do not copy production code into
agent workspaces. A language package combines binding source, local tests and package
metadata under `bindings/<language>/`; a protocol combines its native translation
units under `src/protocols/<component>/`. Ownership of canonical expectations stays
with the vector designer even when tests or fuzzers consume derived fixtures.

Shared files require a named writer and explicit scope. Two assignments may work in
one component directory only with disjoint files; serialize overlapping edits. Native
API designers propose contracts in their workspace; native implementers realize
approved headers. Binding documentation may share a package directory with binding
implementation, but the same guide cannot have two simultaneous writers.

`cli/`, `cmake/`, `packaging/`, `tools/`, root build files and `.github/workflows/`
have no blanket owner under this map. Existing role allowances cover only specifically
delegated registration or binding CI changes. Other changes need a separately scoped
assignment with an applicable role boundary; directory proximity grants no rights.
Reviewers may read relevant shared code but write findings only in their own workspace.
A separate directory does not by itself establish reviewer independence.

## Shared state and existing work

Only the orchestrator writes workflow-root request, manifest and state, or prepares
delegation packets in its own workspace. State references the exact paths of all
specialist outputs, review records, decisions and handoffs. A handoff remains in its
origin workspace; the assigned destination may write its resolution and the
orchestrator may close it, sequentially under the existing handoff contract.

Use this layout for new assignments. Existing `artifacts/`, `bindings/`, `reviews/`,
`delegations/`, `decisions/`, `handoffs/` and `completions/` paths remain valid when
recorded in an active packet. Do not move approved artifacts or duplicate canonical
truth just to match the new layout. Any later migration must update references and
revision evidence through the orchestrator, preserving approval history.

These directories are instruction boundaries, not filesystem sandbox enforcement.
User scope, role boundaries and the concrete assignment must all permit a write.
