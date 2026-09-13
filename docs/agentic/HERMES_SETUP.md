# Hermes setup

Behavior checked against official Hermes documentation on 2026-09-13. No Hermes
executable was found in the inspection environment, so discovery and delegation
have not been smoke-tested here. Commands and discovery behavior are version-sensitive;
check the installed CLI help and linked documentation when upgrading.

## Enable project skills

From this Git checkout, after reviewing the repository instructions:

```sh
cd /path/to/Ratatoskr
hermes skills trust
hermes
```

Current Hermes discovers `.hermes/skills/` at the Git project root after project
trust. Trust is developer-local configuration; this repository does not grant it
or store credentials. Project skill security scanning can quarantine a skill;
inspect the warning rather than bypassing it. See the official
[skills system](https://hermes-agent.nousresearch.com/docs/user-guide/features/skills#project-local-skills).

In the session, ask Hermes to list skills using `skills_list`; load a role with
`skill_view` or its slash command, for example:

```text
/protocol-orchestrator Add protocol <name>
/protocol-orchestrator Add a <language> binding
/protocol-analyst Analyze <component> using workflow <work-id>
```

Trusted discovered skills appear by name, including specialist slash commands.
Each skill uses standard `name` and `description` YAML frontmatter. If discovery
does not reflect newly added/trusted files, start a fresh session from the repo root
and list again; do not assume an undocumented reload command. Check project
discovery settings, quarantine notices and name collisions if roles remain absent.
See [skill loading](https://hermes-agent.nousresearch.com/docs/user-guide/features/skills).

## Project context

Launch at the root so `AGENTS.md` is available as project context. Current Hermes
loads project context at startup and discovers nested context progressively.
Hermes-specific `.hermes.md`/`HERMES.md` can have higher priority; this framework
adds neither, keeping one project rule source. Explicitly reading `AGENTS.md` is
still required in delegation packets. Context precedence and size limits can vary
with version/configuration; inspect the session if rules appear missing. See
[context files](https://hermes-agent.nousresearch.com/docs/user-guide/features/context-files)
and [prompt assembly](https://hermes-agent.nousresearch.com/docs/developer-guide/prompt-assembly).

## Delegation and resumption

Hermes exposes `delegate_task` when delegation tooling is available. Child agents
do not inherit parent conversation history; provide the complete
[delegation template](../../.agentic/templates/delegation.md) through the tool's
goal/context and explicit file paths. Use the installed tool schema, not a hardcoded
invocation format. Include repository root, skill path, role, scope, revisions and
outputs. See [delegation patterns](https://hermes-agent.nousresearch.com/docs/guides/delegation-patterns)
and [subagent delegation](https://hermes-agent.nousresearch.com/docs/user-guide/features/delegation).

If delegation tooling is unavailable, preserve the packet and state for a separate
session or human assignment. A role may be performed sequentially with an explicit
new assignment, but required independent review cannot be replaced by author
self-review. No custom runtime is needed.

On restart, ask the orchestrator to resume a specific work ID. It reads state,
approvals, decisions and handoffs, verifies revisions, then selects the next role.
Do not depend on a still-running child or remembered conversation for durability.

## Developer smoke check

Use the [model/reasoning policy](MODEL_POLICY.md) when selecting the parent and
worker models. It explains the shared `delegation.model` setting, separate sessions
for different tiers, and how to record requested versus actual effort. Skill names
do not configure per-task models. Confirm the effective route during the smoke check.

After trust, confirm all 16 roles are listed; load the orchestrator and one
specialist; ask for the active role and modification boundaries. In a planning-only
request verify that “Add protocol X” starts with research, “Add a binding” starts
with ABI mapping, and neither begins code without approved inputs and authorized
scope. This is a manual setup check, not production protocol testing.
