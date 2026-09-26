# Delegation: fresh DNS G7 configured-limits re-review 003

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-configured-limits-rereview-003-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Candidate revision | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` (parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`) |
| Author | `c-protocol-implementer/g8-configured-limits-remediation-002` |
| Reviewer identity | fresh direct Hermes CLI `protocol-test-engineer` leaf; distinct from author and all prior relevant G7 reviewers |

ACTIVE ROLE: `protocol-test-engineer`

## Goal and scope

Independently perform G7 review of exact corrective candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f` only. Do not route, perform, claim, or create G8, G9, or later work. Do not modify production code. You may create narrowly scoped new test evidence only if strict inspection establishes it is necessary.

## Model and execution

- Policy/default: `docs/agentic/MODEL_POLICY.md`, protocol-test-engineer: `openai-codex` / `gpt-5.6-terra` / `medium`.
- Requested route: `openai-codex` / `gpt-5.6-terra` / `medium`.
- Actual route: verify from this direct CLI invocation if exposed; otherwise record `unknown`, never infer it from this packet.
- One bounded attempt. Stop and honestly report `BLOCKED` for unavailable required input, wrapper, build/test capability, or boundary conflict. If quota/rate error occurs, stop immediately without workflow-state changes.
- No further delegation.

## Working directories and Git

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Your unique workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-003/`.
- Required wrapper for every Git write operation: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-test-engineer -- <git args>`.
- Never raw-git write, merge, or push master. If you create a commit, use wrapper-mediated commit/push exact `HEAD:refs/heads/hermes/dns-implementation-20260913`, then wrapper `ls-remote origin refs/heads/hermes/dns-implementation-20260913`, and record exact readback.
- Preserve unrelated tracked/untracked workspaces.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/protocol-test-engineer/SKILL.md`
3. `docs/agentic/{HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,MODEL_POLICY,SECURITY_MODEL}.md`
4. `docs/contributing.md`
5. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
6. This packet: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g7-configured-limits-rereview-routing-003/delegations/protocol-test-engineer-g7-configured-limits-rereview-003.md`

## Required inputs

- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-002/{README.md,implementation-report.md,completion-report.md,handoffs/dns-g8-001-configured-limits-remediation-to-protocol-orchestrator.md}` at candidate `1a371fe`.
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`.
- Approved requirements/model/API/vector inputs referenced by workflow state.
- Candidate source changes must be exactly `src/protocols/dns/dns_parser.c`, `dns_transport_udp.c`, `dns_client.c`, and `dns_internal.h`.

## Allowed writes

- Your own `README.md`, `test-report.md`, `reviews/g7-configured-limits-rereview.md`, `handoffs/`, and `completion-report.md`.
- Only if strict inspection establishes necessity: `tests/dns/dns_g7_configured_limits_rereview_tests.c`, `tests/integration/dns_g7_configured_limits_rereview_test.py`, `tests/fixtures/dns/g7-configured-limits-rereview-fixtures.json`, and scoped registration in `tests/CMakeLists.txt`.

All production source/headers, workflow-root records, other workspaces, truth/reviews, docs/fuzz/bindings/CLI, existing tests except listed exceptions, and all other paths are read-only. Do not update workflow state. Do not modify an originating handoff resolution.

## G7 acceptance evidence

Independently verify and record:

1. record-owner name expansion/pointer exhaustion behavior over both UDP and TCP;
2. effective-default RR and pointer boundaries;
3. rejection of configuration above the 128 traversal maximum;
4. actual oversized synchronous UDP datagram handling—not merely static reasoning;
5. every terminal configured resource excess is `RESOURCE_LIMIT`, releases accounting exactly once, and has no takeable result;
6. context teardown/detached-handle accounting safety from `c38a7fa` remains intact.

Run tests you can actually run and record commands/revisions/output. Test `APPROVED` only if independently established. Otherwise issue `CHANGES_REQUESTED` to `c-protocol-implementer` with a complete handoff, or `BLOCKED` with honest limitations.

## Expected outputs and handoff

Create all required own artifacts. Your gate review must declare reviewer independence, exact input revisions, evidence, disposition, limitation, and failure route. If `CHANGES_REQUESTED`, hand off to `c-protocol-implementer`; if `APPROVED`, hand off to `protocol-orchestrator` for administrative state reflection only. Finish a standard completion report. Do not claim G8 passed or route it.
