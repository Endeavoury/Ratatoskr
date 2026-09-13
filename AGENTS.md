# Ratatoskr project context

Ratatoskr is a networking SDK with a portable C11 core, a stable C ABI, language
bindings, and the thin `ratos` CLI. Protocol implementation belongs in native C.
Bindings expose that implementation through FFI and idiomatic lifetime/error handling;
they must not independently implement wire formats or parse CLI output.

Protocols and binding languages are independent extension axes: maintain **N protocol
implementations + M bindings**, not N × M independent protocol implementations.

## Repository map

- `src/core/`: common runtime; `src/protocols/<protocol>/`: private protocol modules.
- `include/ratatoskr/`: public C ABI; headers below `src/` are internal.
- `bindings/<language>/`: bindings, their tests, and package metadata.
- `cli/`: thin consumer; `tests/`: native/ABI/integration fixtures; `fuzz/`: fuzz work.
- CMake/CTest build the native core; `.github/workflows/` covers CI and packaging.
- Read `docs/architecture.md`, `docs/repository-layout.md`, and `docs/abi.md` for
  existing contracts. DNS is the first module, not a framework default.

## Agent directories

Every assignment uses `.agentic/workflows/<work-id>/agents/<role>/<assignment-id>/`
for its artifacts. Read [the directory ownership map](docs/agentic/DIRECTORIES.md)
and your skill's working-directory section before writing. Source remains in the
component directories above; shared files need a single explicitly assigned writer.
Reusable directories for every role are in `.agentic/templates/agent-workspaces/`.

## Agent workflow

Read [docs/agentic/README.md](docs/agentic/README.md). Specialist roles live in
`.hermes/skills/<role>/SKILL.md`. The `protocol-orchestrator` routes protocol,
transport, extension, binding, and review requests to the narrowest specialist.

Before making changes, identify `ACTIVE ROLE: <role>`, read that skill, and establish
the request's scope and allowed paths. For framework documentation maintenance use
`documentation-writer`. Do not silently adopt another role's responsibilities.
Modification rights are the intersection of user scope, role boundaries, and the
delegation packet; a skill is not authorization to implement or publish anything.

Work is artifact-driven: use `.agentic/workflows/<work-id>/` for concrete requests,
state, decisions, handoffs, and evidence. Templates in `.agentic/templates/` are not
approved work. Resume from repository artifacts, not chat memory. The orchestrator
alone advances shared workflow state after recorded review gates.

Use `docs/agentic/MODEL_POLICY.md` for per-role OpenAI model/reasoning defaults and
token discipline. Record requested and actual settings in delegation/completion
artifacts; a role prompt does not configure Hermes's model. Preserve review quality.

Delegate with explicit role, inputs, outputs, paths, acceptance criteria, and handoff
target. Failures return to the responsible artifact owner; never change upstream
truth or weaken vectors/tests just to make a downstream stage pass. Reviewers must
be independent of the artifacts they approve. See `docs/agentic/REVIEW_GATES.md`.

Preserve unrelated changes. Keep public names prefixed `ratos_`, ownership explicit,
and protocol behavior out of bindings. Follow `docs/contributing.md` for validation
appropriate to the requested changes. Documentation-only work must not introduce
production code, tests, fuzzers, dependencies, or public API changes.
