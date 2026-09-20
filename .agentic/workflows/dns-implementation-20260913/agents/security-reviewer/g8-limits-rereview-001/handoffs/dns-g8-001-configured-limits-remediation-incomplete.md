# Handoff: DNS-G8-001 configured-limits remediation incomplete

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-001-configured-limits-remediation-incomplete` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `security-reviewer/g8-limits-rereview-001` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Revision | Reviewed candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` |
| Source artifacts | `../security-review.md`; G7 review delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d`; prior G8 delivery `git:90a02df18522b6c311e236dc03c82583971c7511` |
| Assumptions | None. |
| Open questions | None. |
| Limitations | Static control-flow review plus existing G7 evidence; no new test/probe authored. |

## Routing

- ID / workflow / stage: `DNS-G8-001` / `dns-implementation-20260913` / G8 `security`.
- Source role and assignment: `security-reviewer/g8-limits-rereview-001`.
- Destination role: `c-protocol-implementer` through `protocol-orchestrator`.
- Target protocol/component: native DNS limits enforcement.
- Reason: the configured-limits remediation is incomplete at the reviewed candidate.
- Blocking: true.
- Status: `NEEDS_UPSTREAM_CHANGE`.

## Source artifacts

`security-review.md` records exact revisions/hashes and line-level evidence. The blocking paths are record-owner name-limit error conversion in `dns_parser.c:374-376`, fixed pointer/record guards preceding configured/effective resource classification in `dns_parser.c:97-99,418-420`, acceptance of unenforceable pointer limits in `dns_client.c:75-81`, and synchronous POSIX UDP truncation without full-datagram detection in `dns_transport_udp.c:91-100`.

## Specific problem or question

`DNS-REQ-024` and the approved model/API require accepted limits to be coherent, applied before relevant work, and reported as terminal resource-limit with no partial result. Candidate `7a0875e` still converts some reached resource limits to malformed, accepts a pointer limit above the parser hard maximum, and can accept a synchronous UDP datagram larger than the configured admitted-message limit after OS truncation removes trailing bytes. The security reviewer cannot patch production code or author tests.

## Requested action

Produce a narrowly owned implementation correction that:

1. preserves resource results from every record-owner/name caller;
2. validates explicit values against actual implementation maxima and applies resource-limit disposition before overlapping hard guards;
3. detects an oversized/truncated UDP datagram before treating its prefix as a complete message;
4. retains terminal cleanup and no-result behavior on both UDP and TCP paths.

Do not alter approved requirements/vectors or prior review records.

## Acceptance criteria

- New candidate has exact source/delivery revisions and authorized-path evidence.
- Independent native evidence covers record-owner expansion/pointer exhaustion over UDP and TCP, effective-default RR/pointer boundaries, rejection of over-hard pointer configuration, and synchronous over-limit UDP datagrams.
- Each configured excess is terminal `RESOURCE_LIMIT`, performs no over-budget allocation/copy/traversal, and leaves no takeable result; over-limit UDP is never accepted as a valid truncated prefix.
- Fresh independent G7 approves the new candidate, followed by fresh independent G8 re-review.

## Resolution (destination role)

Pending.

## Closure (orchestrator after verification)

Pending.