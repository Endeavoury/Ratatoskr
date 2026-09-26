# Maintainer handoff — DNS resource policy

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-handoff-dns-resource-policy-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Source / destination | `protocol-api-designer` → maintainer via `protocol-orchestrator` |
| Status | `READY_FOR_REVIEW` |
| Blocking | Nonblocking for the symbolic API contract; blocking for any realization that needs concrete default resource values. |

## Question

Select documented default values and product resource policy for DNS maximum UDP/TCP frame bytes, total RR/count work, name expansion bytes, compression-pointer traversals, typed-field/string bytes, and outstanding requests/connections. The approved analysis/model require limits but explicitly leave numeric budgets and configurability to API/product policy.

## Evidence

- Analysis `DNS-REQ-024` and model `INV-BOUNDED-PARSING` require configured bounds and distinguish `resource_limit` from malformed input.
- The ABI baseline and the G4 inputs contain no approved numeric values for these fields.
- The design candidate therefore exposes symbolic per-field selectors with initializer-selected implementation defaults, without inventing values.

## Requested action and acceptance

The maintainer, through `protocol-orchestrator`, must either select values/documentation policy or retain symbolic implementation-selected defaults with an explicit release policy before a realized implementation claims concrete behavior. The choice must preserve ABI-1 append-only struct evolution and receive renewed affected review.

## Resolution

Pending maintainer/product decision.
