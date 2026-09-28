# DNS G8 global-limits remediation implementation report

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g8-global-limits-remediation-001-implementation` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `BLOCKED` |
| Baseline / current revision | Required subject `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; checked `HEAD` `git:b26757b196793785082f5a3eea9ae2f512e57795` |
| Source artifacts | G8 finding delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; approved G7 delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d`; G8 handoffs `DNS-G8-001`, `DNS-G8-002` |
| Assumptions | None added. |
| Open questions | Whether an internal context-owned DNS request-accounting field and context-destruction invariant may be authorized. |
| Limitations | No production change is safe within this packet's write scope. |

## Authority assessment

`DNS-G8-002` requires removal of the unsynchronized process-global request list while preserving per-context outstanding-request and connection caps. The approved API/model requires copied per-context configuration and terminal cleanup, and `docs/architecture.md` requires separate contexts to be concurrently usable with no global resolver state. However, the concrete `ratos_context` layout is defined only in `src/core/core_internal.h` as `error_message` plus `dns_limits`; it has no DNS-private request-accounting/list field. That file and `src/core/context.c` are outside this packet's exact write scope. The public request API also has no context teardown registration hook.

A context-owned counter/list therefore cannot be realized in the five authorized DNS files without inventing an unapproved global synchronization/lifetime scheme, weakening the cap contract, or modifying forbidden core ownership state. Per packet stop condition, no production source was changed.

## Validation evidence

- Read `AGENTS.md`, the active `c-protocol-implementer` skill, required contracts, current workflow state, G6 readiness record, approved analysis/model/API/vector truth, G8 review, both G8 handoffs, and approved G7 review.
- Wrapper baseline checks passed: repository root `/home/hermes/hermes-workspace/projects/Ratatoskr`; origin `https://github.com/Endeavoury/Ratatoskr.git`; branch `hermes/dns-implementation-20260913`; `HEAD` `b26757b196793785082f5a3eea9ae2f512e57795`; both required ancestry checks to `844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f` passed.
- Read-only source inspection confirms the only current tracker is `static ratos_dns_request *context_requests` in `src/protocols/dns/dns_client.c`, and the only concrete context layout is the forbidden core-internal definition above.
- No build or test was run because this assignment made no native source change.

## Required upstream disposition

See `handoffs/g8-global-limits-remediation-authority-blocker.md`. The protocol orchestrator must obtain an authorized core-context ownership/lifetime design and exact write scope before a native implementation retry. Neither G7 nor G8 is approved by this report.