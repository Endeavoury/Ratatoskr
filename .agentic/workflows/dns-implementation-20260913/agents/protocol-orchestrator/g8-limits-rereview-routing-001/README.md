# G8 limits re-review routing

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g8-limits-rereview-routing-001` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `BLOCKED` |
| Revision | routing preflight at `2026-09-20T02:13:25Z`; repository `git:c3114911fd087700ead2979a16aa8ecd111559ba` |

ACTIVE ROLE: protocol-orchestrator

## Scope
Route exactly one fresh independent G8 security re-review of DNS-G8-001 only when the security-reviewer model policy route is actually available. Do not route G9 or later work and do not modify implementation, tests, vectors, APIs, or prior review truth.

## Preflight result
The security-reviewer policy requires `gpt-5.6-sol` with `high` reasoning. Runtime/configuration observation shows the parent/delegation route is `openai-codex/gpt-5.6-terra`; `delegation.model` has no configured override and `agent.reasoning_effort` is unset (`hermes config get agent.reasoning_effort` exited 1). Under MODEL_POLICY.md, an unset delegation model inherits the parent and a prompt cannot switch the child. The required Sol/high route is therefore unavailable in this session.

No security-reviewer leaf was dispatched. The complete durable packet in `delegations/security-reviewer-g8-limits-rereview-001.md` is ready for a separately configured Sol/high session. G8/security remain `CHANGES_REQUESTED`; G9 and later remain unstarted.

## Git delivery requirement
This routing-only record must be committed and pushed through `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-orchestrator -- ...` to `HEAD:refs/heads/hermes/dns-implementation-20260913`, followed by exact readback of `origin/hermes/dns-implementation-20260913`.