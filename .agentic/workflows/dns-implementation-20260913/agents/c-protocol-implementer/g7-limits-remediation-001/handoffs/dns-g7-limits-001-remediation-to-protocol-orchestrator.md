# Handoff: DNS-G7-LIMITS-001 remediation

| Field | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g7-limits-001-remediation-to-protocol-orchestrator` |
| Workflow / stage | `dns-implementation-20260913` / corrective native implementation |
| Target | `protocol/dns` |
| Source role | `c-protocol-implementer/g7-limits-remediation-001` |
| Destination role | `protocol-orchestrator` |
| Status | `READY_FOR_REVIEW` |
| Candidate revision | `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` |
| Source artifacts | G7 return handoff and report at `git:15d3fc3de3eb733aac7f04d07ba7da02ffe809bd`; implementation report in this workspace. |
| Assumptions | None. |
| Open questions | None. |
| Limitations | CMake/CTest unavailable; temporary targeted probes are outside the repository. |

## Routing

- ID / workflow / stage: `DNS-G7-LIMITS-001` / `dns-implementation-20260913` / corrective native implementation.
- Reason: returned blocking G7 resource-limit classification defect is corrected in a new candidate.
- Blocking: false for delivery verification; a fresh independent G7 review remains required.
- Status: `READY_FOR_REVIEW`.

## Source artifacts and evidence

`src/protocols/dns/dns_parser.c` candidate `7a0875e` separates `read_name` error handling from malformed checks. It returns the existing `RATOS_ERROR_OUT_OF_MEMORY` for configured name-expansion or pointer-traversal exhaustion through question, record-owner, and name-bearing RDATA callers. Existing `request_parse` maps that result to resource-limit terminal state/class and cannot expose a result after `request_fail`.

Strict C11 syntax, existing native DNS tests, existing G7 label regression, and two temporary incremental probes passed. The name and pointer probes each observed `receive=3 state=4 class=3 event=5` and asserted `ratos_dns_request_take_result` returns `RATOS_ERROR_INVALID_ARGUMENT` with a null output.

## Requested action

Verify delivery boundary and route a fresh independent G7 review of candidate `7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`. Do not treat this author handoff as G7 approval or route G8 work under this assignment.

## Acceptance criteria

1. Delivery revision and remote readback contain candidate plus only the authorized source/artifact/resolution paths.
2. Fresh independent G7 reviewer verifies both configured name-expansion and compression-pointer exhaustion retain resource-limit/no-result behavior.
3. No G8 disposition is claimed by this implementation handoff.

## Resolution (destination role)

`protocol-orchestrator` verified the ready delivery and routed the sole fresh independent G7 reviewer. That reviewer recorded `APPROVED` for candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` in `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-limits-rereview-001/reviews/g7-limits-rereview.md` at reviewer delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d`.

## Closure (orchestrator after verification)

`COMPLETE`: the fresh independent G7-only record verified both configured resource-limit cases and no-result behavior. This closure makes no G8/G9/later routing or disposition.
