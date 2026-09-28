# Handoff: DNS-G8-001 configured-limits enforcement

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-001-configured-limits-enforcement` |
| Workflow / stage | `dns-implementation-20260913` / G8 security |
| Owner role | `security-reviewer` |
| Status | `NEEDS_UPSTREAM_CHANGE` |

## Routing

- **Source:** `security-reviewer/g8-security-review-001`
- **Destination:** `c-protocol-implementer`
- **Target:** `protocol/dns`
- **Blocking:** true
- **Reason:** implementation defect, DNS-G8-001.

## Evidence

At `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee`, `ratos_dns_context_set_dns_limits` copies all public fields but only UDP/TCP limits are used downstream. The parser retains hard-coded count/packet bounds and never receives/enforces configured total-RR, name-expansion, compression-pointer, or typed-field budgets; request/connection caps are likewise absent. This conflicts with `DNS-REQ-024`, model `INV-BOUNDED-PARSING`, and API design §4. Detailed line-level evidence is in `../security-review.md`.

## Requested action

Implement the contractual finite effective defaults and configured limit enforcement before allocation/iteration/copy/traversal, with terminal resource-limit/no-result behavior. Preserve approved canonical requirements; do not modify this review, workflow state, or G9 scope. If public contract changes are necessary, return that narrower question to `protocol-api-designer` first.

## Acceptance criteria

1. New implementation revision enforces each accepted limit or has an approved API-design revision removing an unsupported field.
2. Native tests demonstrate UDP and TCP limit failures are terminal resource-limit outcomes with no partial result and no escape past the selected budget.
3. An independent G7 review verifies the implementation/tests; then a fresh independent G8 re-review verifies DNS-G8-001 remediation.

## Resolution (destination role)

**READY_FOR_REVIEW.** The c-protocol-implementer produced the DNS-G8-001 candidate and trace at `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/implementation-report.md` and handoff `handoffs/dns-g8-001-remediation-to-protocol-orchestrator.md`. The candidate enforces finite effective defaults and the configured UDP, TCP-frame, RR-count, name-expansion, compression-traversal, typed-field, outstanding-request, and connection limits in the authorized private DNS implementation paths; request-path resource excess fails terminally with no transferable result. `git diff --check`, strict C compilation, and the existing native DNS test executable passed; CMake/CTest remain unavailable because `cmake` is absent. Candidate delivery and fresh independent G7 then G8 review are still required; this destination resolution makes no approval claim.

## Closure (orchestrator after verification)

Pending.
