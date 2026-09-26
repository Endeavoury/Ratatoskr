# Handoff: DNS-G8-002 global request tracker race

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-002-global-request-tracker-race` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `security-reviewer/g8-limits-rereview-001` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Revision | Reviewed candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; tracker introduced by remediation candidate `git:a8d98b75e9c450734808d5a672a2023e83589fb0` |
| Source artifacts | `../security-review.md`; `docs/architecture.md`; approved API/model evidence |
| Assumptions | Documented separate-context concurrency remains supported. |
| Open questions | None. |
| Limitations | Direct C11 lifetime/control-flow evidence; no dynamic race probe authored. |

## Routing

- ID / workflow / stage: `DNS-G8-002` / `dns-implementation-20260913` / G8 `security`.
- Source role and assignment: `security-reviewer/g8-limits-rereview-001`.
- Destination role: `c-protocol-implementer` through `protocol-orchestrator`.
- Target protocol/component: native DNS request-limit accounting.
- Reason: the remediation introduced unsafe process-global mutable request tracking.
- Blocking: true.
- Status: `NEEDS_UPSTREAM_CHANGE`.

## Source artifacts

`docs/architecture.md:67-72` permits concurrent use of separate contexts and states that resolver state is not global. Candidate source has global `context_requests` at `src/protocols/dns/dns_client.c:193`, unsynchronized traversal at `:194-199`, insertion at `:212-216`, and unlink/free traversal at `:247`.

## Specific problem or question

Concurrent start/destroy operations on different contexts access and mutate one global singly linked list without synchronization. One thread can traverse a node while another removes and frees it; writers can also race on the head and links. This is C11 undefined behavior with list-corruption/use-after-free potential in a documented supported concurrency scenario. The security reviewer cannot implement the fix.

## Requested action

Replace the global tracker with context-owned accounting/lists or introduce a separately reviewed synchronization and lifetime design. Preserve context-outlives-request rules, per-context outstanding/connection limits, cancellation/terminal behavior, and safe destruction. Do not weaken the documented separate-context concurrency contract without the owning design/compatibility route.

## Acceptance criteria

- No unsynchronized process-global mutable request tracker remains.
- Per-context caps are correct across start, UDP-to-TCP transition, completion, failure, cancellation, take-result, and destruction.
- Distinct contexts can concurrently start and destroy requests without data races, stale traversal, list corruption, or UAF; race-detector/stress evidence is recorded where available.
- A fresh independent G7 review approves the corrective candidate and a fresh independent G8 reviewer verifies this finding.

## Resolution (destination role)

`c-protocol-implementer/g8-global-limits-remediation-001` assessed the packet at checked revision `git:b26757b196793785082f5a3eea9ae2f512e57795` and made no production-source change. The required context-owned accounting/list and context-destruction safety cannot be realized inside the five authorized DNS files: the complete `ratos_context` layout is in forbidden `src/core/core_internal.h` and contains no attachment point. A replacement global synchronization/lifetime design is not approved and would conflict with the no-global-state concurrency contract. The precise upstream authority request is `agents/c-protocol-implementer/g8-global-limits-remediation-001/handoffs/g8-global-limits-remediation-authority-blocker.md`. This handoff remains unresolved; no gate is closed.

## Closure (orchestrator after verification)

Pending.