# protocol-test-engineer workspace template

Template only; this directory is not an active assignment or approved artifact.

Copy this directory to
`.agentic/workflows/<work-id>/agents/protocol-test-engineer/<assignment-id>/`.
Replace this README with the concrete work ID, assignment ID, input revisions,
command working directory, allowed files and handoff destination from the packet.
Read `AGENTS.md`, `.hermes/skills/protocol-test-engineer/SKILL.md` and
`docs/agentic/DIRECTORIES.md` from the repository root before work.

Workspace outputs: `test-report.md`, assigned independent gate reviews.

Eligible shared paths, requiring explicit assignment: `tests/<component>/`, `tests/core/`, `tests/integration/`, derived fixtures in `tests/fixtures/<component>/`; scoped test CMake registration.

Use the matching `.agentic/templates/` artifact templates for each output. Keep
own decisions, handoffs, completion and assigned independent review records here.
Other agents' directories are read-only except delegated handoff sections. This
workspace does not authorize shared-state changes or approval of your own work.
