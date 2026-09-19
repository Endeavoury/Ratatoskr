# Handoff: DNS-G7-LIMITS-001 resource-limit classification

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-limits-001-resource-classification` |
| Workflow / stage | `dns-implementation-20260913` / G7 `native_verification` |
| Target | `protocol/dns` |
| Source role | `protocol-test-engineer/g7-g8-limits-rereview-001` |
| Destination role | `c-protocol-implementer` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Candidate | `git:a8d98b75e9c450734808d5a672a2023e83589fb0` |

## Routing

- Reason: blocking G7 code defect in configured name-expansion and compression-pointer limit classification.
- Blocking: true.
- Independence: fresh G7 reviewer distinct from the candidate author and prior G7 reviewers; no production or test authoring here.

## Evidence

`src/protocols/dns/dns_parser.c` makes `read_name` return `RATOS_ERROR_OUT_OF_MEMORY` for configured `max_name_expansion_bytes` or `max_compression_pointer_traversals` exhaustion. The surrounding question/record combined error conditions discard that resource result and return/retain `RATOS_ERROR_PROTOCOL`. `src/protocols/dns/dns_client.c` therefore emits a terminal `RATOS_DNS_ERROR_CLASS_MALFORMED_RESPONSE` rather than `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`.

A deterministic temporary probe against the candidate configured `max_name_expansion_bytes=1`, started a valid request, and supplied a matching minimal response. Actual output: `receive=6 state=4 class=2 event=5 take_result=(nil)`. The terminal/no-result behavior occurred, but `6` is `RATOS_ERROR_PROTOCOL` and `2` is malformed-response, not the required resource result/class. The same propagation path applies to compression-pointer exhaustion.

## Requested action

In the five authorized DNS implementation paths only, preserve the resource result from `read_name` through parser callers so request intake classifies configured name-expansion and compression-pointer exhaustion as terminal `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`. Do not change canonical truth, prior review records, workflow state, or G8+ scope.

## Acceptance criteria

1. A new candidate returns the existing internal resource result for both configured name-expansion and compression-pointer exhaustion rather than converting either to protocol/malformed response.
2. Incremental request intake yields terminal error event/state with `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT` and `ratos_dns_request_take_result(...)=RATOS_ERROR_INVALID_ARGUMENT` with null result for both cases.
3. Fresh independent G7 review verifies the new revision and existing/appropriate evidence before any future G8 action.

## Resolution (destination role)

Pending.

## Closure (orchestrator after verification)

Pending.
