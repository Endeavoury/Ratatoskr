# Delegation: G8 global limits remediation

## Identity and hierarchy

- **ROLE:** `c-protocol-implementer` (leaf)
- **Hierarchy:** `workspace-orchestrator → protocol-orchestrator → c-protocol-implementer`
- **Root task / project / workflow:** `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913`
- **Stage:** corrective native implementation responding to blocking G8 findings `DNS-G8-001` and `DNS-G8-002`; this is not a G7/G8/G9 review or gate closure.
- **Repository root and command cwd:** `/home/hermes/hermes-workspace/projects/Ratatoskr`
- **READ FIRST:** `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`; exact role skill `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/c-protocol-implementer/SKILL.md`; `docs/agentic/{ARTIFACTS.md,SECURITY_MODEL.md,REVIEW_GATES.md,HANDOFFS.md,DIRECTORIES.md,MODEL_POLICY.md}`; this packet; current workflow state.

## Immutable baseline and mandatory inputs

Work from the required subject baseline candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`. Before edits verify it and the approved G7 delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d` are ancestors of the G8 security delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; do not substitute a newer candidate as authority.

Mandatory inputs:
1. `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/security-review.md`
2. `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/reviews/g8-limits-rereview.md`
3. `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-incomplete.md`
4. `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-limits-rereview-001/handoffs/dns-g8-002-global-request-tracker-race.md`
5. approved G7 review: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/reviews/g7-limits-rereview.md`
6. current `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` and all approved upstream truth it references.

## Exact write scope

Create and own only this unique artifact workspace:
`.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-global-limits-remediation-001/`

Allowed artifact files: `README.md`, `implementation-report.md`, `handoffs/`, `completion-report.md`.

Allowed shared-source files **only**:
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_internal.h`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_transport_tcp.c`

You may write **Resolution sections only** in both mandatory G8 handoffs listed above. Everything else is forbidden/read-only, including public headers, all tests, vectors, docs, workflow state, designs/reviews, request/manifest, build files, and every other path. No ABI, contract, vector, or test edits.

## Required correction

Implement both findings narrowly and consistently with approved truth:

1. Eliminate the unsynchronized global mutable request tracker. Use a safe context-owned solution only if current approved design/code authorizes it; preserve documented supported separate-context concurrency, per-context resource/connection caps, request lifetime, cancellation/terminal behavior, take-result, UDP-to-TCP transition, and destruction safety. Do not introduce an unsupported global synchronization/lifetime design or weaken the concurrency contract.
2. Complete configured-limit remediation: correctly propagate record-owner resource outcomes; make limit precedence/validation coherent and effective (including hard maximums); preserve safe per-context caps; and synchronously detect UDP over-limit/truncation before a truncated prefix can be accepted as a complete datagram. Retain terminal cleanup/no-result behavior on UDP and TCP excess.

If existing approved design/code does not sufficiently authorize a safe context-owned solution, stop without speculative contract invention and return a blocking handoff to `protocol-orchestrator` explaining the exact missing authority.

## Acceptance and evidence

- No unsynchronized process-global mutable request tracker remains.
- Both G8 handoffs receive a scoped Resolution section citing exact changed paths/revision and outcome; do not close them.
- Resource-limit results/no-result behavior are maintained for record-owner/name expansion, pointer/RR limits, UDP/TCP terminal paths, and effective defaults/validated explicit limits.
- Synchronous UDP oversize/truncation is detected before parsing a truncated prefix.
- Diff is limited exactly to the authorized source files, own artifact workspace, and two permitted Resolution sections.
- Run feasible existing validation only; report exact commands/results and unavailable checks/limits. Do not write tests and do not self-approve.
- Finish `READY_FOR_REVIEW` only with standard completion fields: ROLE, STATUS, SUMMARY, ARTIFACTS CREATED, ARTIFACTS MODIFIED, DECISIONS MADE, OPEN QUESTIONS, BLOCKERS, HANDOFF REQUIRED, RECOMMENDED NEXT ROLE. Report to `protocol-orchestrator`.

## Git and model requirements

For every Git operation use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role c-protocol-implementer -- <git arguments>`; never raw Git. Before commit verify origin, branch `hermes/dns-implementation-20260913`, exact allowed-path staged diff, and `diff --check`. Commit/push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; read back that exact remote ref with the wrapper after push. Preserve unrelated untracked workspaces. On any quota/rate error, stop immediately with no further state changes and report it.

Requested route: `openai-codex/gpt-5.6-sol`, effort `high` (concurrency/lifetime escalation). Actual child route is not assumed: record exposed actual model/effort/usage. If Sol/high is unavailable, use only the explicitly authorized bounded inherited `openai-codex/gpt-5.6-terra`, recording actual exposed effort; one evidence-driven implementation pass only. On repeated unresolved defect, blocker, or unavailable authority, hand back—no retry ladder.

## No-op/blocker behavior

Do not modify production source if prerequisites, authority, or safe implementation basis are missing. Still create the owned report/completion and a precise handoff if permitted, report `BLOCKED`/`NEEDS_UPSTREAM_CHANGE`, preserve G8 `CHANGES_REQUESTED`, and return control to `protocol-orchestrator`.
