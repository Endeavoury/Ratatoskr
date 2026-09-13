# Agentic engineering manual

This directory defines how Hermes specialists will develop Ratatoskr through
reviewable repository artifacts. Hermes supplies the runtime; this framework adds
instructions, role boundaries, templates, and review contracts, not an executable
workflow engine. Creating these files does not execute any implementation stage.

Roles separate specification truth, design, implementation, and independent review.
Artifacts preserve evidence and decisions across fresh sessions. A passing build
does not authorize an agent to rewrite a specification or expected vector.

## Start here

1. Follow [Hermes setup](HERMES_SETUP.md), launch from the repository root, and load
   `protocol-orchestrator` for a new multi-stage request.
2. For “Add protocol STUN”, the orchestrator records an `ADD_PROTOCOL` request and
   delegates specification discovery first. For “Add a Swift binding”, it records
   `ADD_BINDING` and starts with the existing ABI and binding design.
3. The orchestrator copies relevant [templates](../../.agentic/templates/) into a
   uniquely named `.agentic/workflows/<work-id>/`, fills the request/state, and assigns
   a specialist using a complete [delegation packet](../../.agentic/templates/delegation.md).
4. The specialist reads its `.hermes/skills/<role>/SKILL.md`, announces its identity,
   checks inputs, changes only assigned artifacts, and produces a completion report.
5. An independent reviewer records the gate result. The orchestrator advances the
   state or routes a formal handoff to the owner of the failing input.

Narrow requests can start at a later role only when its prerequisites already exist
and are approved for the current revision. Reviews produce findings; they do not
silently become implementation tasks. A new session inventories workflow states;
it never guesses which of several active targets the user intended.

## Manual map

| Document | Contract |
| --- | --- |
| [Architecture](ARCHITECTURE.md) | Repository findings, extension axes, state and composition |
| [Workflow](WORKFLOW.md) | Routing, dependencies, state transitions, resumption |
| [Roles](ROLES.md) | Ownership and modification matrix |
| [Model and reasoning policy](MODEL_POLICY.md) | OpenAI defaults per role, token discipline and escalation |
| [Handoffs](HANDOFFS.md) | Delegation, completion, escalation and backtracking |
| [Artifacts](ARTIFACTS.md) | Artifact paths, identities, templates and schemas |
| [Protocol lifecycle](PROTOCOL_LIFECYCLE.md) | New and changed native capabilities |
| [Binding lifecycle](BINDING_LIFECYCLE.md) | New language exposure without protocol redesign |
| [Security model](SECURITY_MODEL.md) | Adversarial review and instruction boundaries |
| [Review gates](REVIEW_GATES.md) | Evidence, independent approval, failure routing |
| [Hermes setup](HERMES_SETUP.md) | Discovery, trust, skills and fresh-context delegation |

The earlier [DNS validation plan](../protocol-validation-plan.md) is a scoped example,
not the framework's schema, role contract, or an approved specification inventory.
Existing implementation and legacy documentation require verification before reuse.
