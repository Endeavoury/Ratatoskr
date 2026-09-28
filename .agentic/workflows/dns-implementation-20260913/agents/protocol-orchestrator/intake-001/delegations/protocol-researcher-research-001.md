# Delegated task — DNS specification discovery

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-delegation-research-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-orchestrator |
| Status | IN_PROGRESS |
| Revision | Git `42b0611efa90e4b62f06d07cca64044ae9f090a7`; packet written at workflow intake |
| Source artifacts | `request.md`, `manifest.yaml`, `workflow-state.yaml`, `g0-intake.md`, all at this workflow |
| Assumptions | Existing implementation/docs are discovery leads, not specification authority. |
| Open questions | Binding scope is deferred; no binding work is assigned. |
| Limitations | No G1 approval exists; researcher must not self-approve. |

ACTIVE ROLE: protocol-researcher

ROLE: protocol-researcher (leaf assignment; no further delegation)

GOAL: Produce an evidence-backed DNS specification inventory for the recorded native unicast stub/client scope, with official sources, update/obsolescence and errata dispositions, registry references, explicit exclusions/deferred areas, and an analyst-ready handoff.

SCOPE: Discovery only. Do not interpret unsupported wire/state behavior, design APIs/vectors, implement or test DNS, alter scope, or approve G1. Existing implementation must only be used as read-only discovery evidence.

## Model and reasoning
- Policy: `docs/agentic/MODEL_POLICY.md`, protocol-researcher row.
- Requested provider/model ID: `gpt-5.6-luna`.
- Requested reasoning effort: `low`.
- Observed runtime provider/model/effort: `openai-codex / gpt-5.6-terra / unknown`; session metadata observed by orchestrator; the packet does not switch runtime configuration.
- Verification source: Hermes session metadata supplied to orchestrator.
- Context target: 8,000–16,000 task-specific tokens while reading required sources completely.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction on default settings; then record bounded handoff rather than repeat.
- Escalation: if update/errata graph is large or sources are missed, `gpt-5.6-terra` / `medium` in a separately configured compatible session; do not claim an in-prompt switch.
- Stop/checkpoint: missing/inaccessible authoritative evidence, unresolved source authority, a boundary conflict, or completed inventory/handoff.

## Target and working directories
- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/`.
- Workspace owner: protocol-researcher, assignment `research-001`, delegated leaf agent identity recorded by the delegation runtime.
- Shared source directories: none; all repository code and existing artifacts are read-only.
- Shared-file writer/ordering: protocol-orchestrator is the sole writer of workflow state; no shared source writer is assigned.
- Existing-path exception: none.

## Workflow / stage / assignment
`dns-implementation-20260913` / `research` / `research-001`; shared state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.

## Read first
- `AGENTS.md`
- `.hermes/skills/protocol-researcher/SKILL.md`
- `docs/agentic/HANDOFFS.md`, `ARTIFACTS.md`, `DIRECTORIES.md`, `MODEL_POLICY.md`, `PROTOCOL_LIFECYCLE.md`, and `REVIEW_GATES.md` (G1)
- `.agentic/workflows/dns-implementation-20260913/request.md`, `manifest.yaml`, `workflow-state.yaml`
- `docs/protocol-validation-plan.md` and `docs/dns-rfc-compliance.md` as non-authoritative discovery leads

## Required input artifacts
- Baseline Git revision `42b0611efa90e4b62f06d07cca64044ae9f090a7`.
- Workflow request, manifest, state and G0 record above; G0 only is approved.
- Read-only DNS surface: `src/protocols/dns/`, `include/ratatoskr/dns.h`, `cli/commands/dns.c`, `tests/dns/dns_tests.c`, `tests/integration/dns_fixture_test.py`, `fuzz/dns/`, `docs/dns.md`, `docs/dns-rfc-compliance.md`, `docs/protocol-validation-plan.md`.

## Files allowed to change
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/specification-inventory.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/decisions/` source-authority decisions only
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/handoffs/research-to-analyst-g1.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-researcher/research-001/completion-report.md`

## Read-only / forbidden
All source, tests, fuzzing, headers, CLI, bindings, documentation, workflow-root artifacts, other assignments, Git/config/credentials and external publication are read-only or out of scope. Do not delegate further.

## Expected outputs and acceptance
- A `specification-inventory.md` that records official source title/URL/status/sections/checked date/source revision where available; Updates/Obsoletes/successor, errata and registry dispositions; discovered/visited closure; applicability for the stated scope; exclusions/deferred areas; and open source-authority questions without interpreting them.
- Optional source decision records only when a decision is required to classify authority.
- `handoffs/research-to-analyst-g1.md` with `READY_FOR_REVIEW`, requesting independent protocol-analyst G1 review; it must reference inventory revision and acceptance criteria.
- `completion-report.md` with the standard fields and actual checks/limitations.
- No implementation changes; report `READY_FOR_REVIEW`, not approved.

HANDOFF TARGET: protocol-analyst for independent G1 review through the handoff path above; protocol-orchestrator updates state only after verification.

STOP CONDITIONS: Stop and hand off to protocol-orchestrator if source authority cannot be verified, product scope changes, prerequisites conflict, or permissions would require a non-listed path. Stop normally once the inventory and G1 handoff are complete.

DELEGATION ALLOWANCE: None. This is a leaf. Do not spawn, subcontract, or otherwise delegate.

CONTEXT CONTRACT: You have fresh context. Announce `ACTIVE ROLE: protocol-researcher`, verify scope and G0 inputs, retain all role boundaries, and do not update shared workflow state.
