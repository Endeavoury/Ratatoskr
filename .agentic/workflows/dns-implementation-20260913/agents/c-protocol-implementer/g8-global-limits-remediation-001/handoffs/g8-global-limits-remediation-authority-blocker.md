# Handoff: G8 global-limits remediation authority blocker

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-global-limits-remediation-authority-blocker` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `c-protocol-implementer/g8-global-limits-remediation-001` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Revision | Checked `git:b26757b196793785082f5a3eea9ae2f512e57795` |
| Source artifacts | G8 review delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; `DNS-G8-001`; `DNS-G8-002`; approved G7 delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d` |
| Assumptions | None. |
| Open questions | Authorization for context-owned request accounting and destruction safety. |
| Limitations | No production change was made. |

## Routing

- ID / workflow / stage: `DNS-G8-001` and `DNS-G8-002` / `dns-implementation-20260913` / corrective native implementation.
- Source role and assignment: `c-protocol-implementer/g8-global-limits-remediation-001`.
- Destination role: `protocol-orchestrator`.
- Target protocol/component: native DNS request accounting and configured limits.
- Reason: the packet forbids the required context ownership realization.
- Blocking: true.
- Status: `NEEDS_UPSTREAM_CHANGE`.

## Source artifacts

The current implementation's global `context_requests` list in `src/protocols/dns/dns_client.c` violates the approved separate-context concurrency rule. `src/core/core_internal.h` contains the full internal `ratos_context` layout and has no field for per-context DNS request accounting. Both that header and `src/core/context.c` are forbidden by the packet. The authorized DNS-only files cannot safely attach ownership to a context or establish context-outlives-request destruction semantics.

## Specific problem or question

Can the project authorize a context-owned DNS request-accounting structure, its initialization/destruction lifecycle, and the necessary internal core-file write scope? Without it, removing the global list loses enforced per-context caps; retaining/replacing it with another global scheme conflicts with the no-global-state/concurrency contract and packet prohibition on speculative lifetime design.

## Requested action

Route the ownership question to the responsible API/design and core implementation authority. Produce an approved design revision that specifies the context-owned accounting representation, start/terminal/cancel/destroy updates, context-destruction behavior with live requests, and the exact writable core/internal paths. Then issue a new bounded implementation packet and renewed review routing.

## Acceptance criteria

- Approved authority and exact write scope permit context-owned accounting without public ABI changes unless separately approved.
- The design specifies context-outlives-request or safe context teardown, and preserves per-context outstanding/connection caps through UDP-to-TCP transition, completion, failure, cancellation, take-result, and request destruction.
- A new implementation packet permits only the needed paths and requires fresh independent G7 then G8 review.

## Resolution (destination role)

Pending.

## Closure (orchestrator after verification)

Pending.