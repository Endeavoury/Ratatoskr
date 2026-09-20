# Handoff: DNS-G8-001 configured-limits remediation still incomplete

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-001-configured-limits-remediation-still-incomplete` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parsing/UDP limits |
| Owner role | `security-reviewer/g8-accounting-security-rereview-001` |
| Status | `NEEDS_UPSTREAM_CHANGE` |
| Revision | Reviewed candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` |
| Source artifacts | `../security-review.md`; prior finding delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; G7 accounting delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd` |
| Assumptions | None beyond approved same-context serialization. |
| Open questions | None. |
| Limitations | Static exact-revision/control-flow evidence; no new test/probe source or dynamic socket reproduction was authorized. |

## Routing

- ID / workflow / stage: `DNS-G8-001` / `dns-implementation-20260913` / G8 `security`.
- Source role and assignment: `security-reviewer/g8-accounting-security-rereview-001`.
- Destination role: `c-protocol-implementer` through `protocol-orchestrator`.
- Target protocol/component: native DNS configured parser limits and synchronous UDP admission.
- Reason: accounting candidate `c38a7fa` resolves DNS-G8-002 but leaves every prior DNS-G8-001 path unchanged.
- Blocking: true.
- Status: `NEEDS_UPSTREAM_CHANGE`.

## Source artifacts

Exact reviewed candidate: `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; parent `git:62a2dda24194020904a75e1edce9b3d74fbd70a4`; G7 delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`. Prior G8 finding: `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`.

Candidate `c38a7fa` changes only private accounting/context files and its own artifacts. `src/protocols/dns/dns_parser.c` and `src/protocols/dns/dns_transport_udp.c` are unchanged from the prior finding subject. Exact candidate evidence:

- `dns_parser.c:374-376` converts record-owner `read_name` resource exhaustion to `RATOS_ERROR_PROTOCOL`;
- `dns_parser.c:97-99` checks the fixed 128-hop malformed guard before the configured traversal budget;
- `dns_client.c:75-80` accepts `max_compression_pointer_traversals > 128`;
- `dns_parser.c:418-420` applies the 4,096-record malformed guard before the configured/effective resource limit;
- `dns_transport_udp.c:91-100` uses capacity-sized `recv` without full-datagram/truncation detection.

These violate `DNS-REQ-024`, `INV-BOUNDED-PARSING`, and the ordered resource-limit disposition. The accounting G7 review explicitly scoped its approval to accounting/lifecycle behavior and does not provide closure evidence for these paths.

## Specific problem or question

A malicious upstream can reach configured name/pointer/count excess paths that are classified malformed rather than resource-limit, while explicit pointer limits above the actual hard maximum are accepted but unenforceable. The synchronous socket path can also accept a datagram larger than `max_udp_message_bytes` when the OS truncates it to a complete correlated DNS prefix. These are mandatory configured-boundary and disposition defects. A security reviewer cannot patch implementation or author the required native tests.

## Requested action

Produce one narrowly authorized native implementation correction that:

1. preserves `RATOS_ERROR_OUT_OF_MEMORY`/resource disposition from every `read_name` caller, including record owners;
2. rejects or coherently caps explicit traversal limits above the implementation maximum;
3. applies configured/effective resource checks before overlapping hard malformed guards at pointer and total-RR boundaries;
4. detects oversized/truncated synchronous UDP datagrams before parsing or acceptance on supported platforms; and
5. retains terminal cleanup, exact-once accounting, and no-result behavior from candidate `c38a7fa`.

Do not alter approved requirements, model, vectors, prior reviews, or workflow state to mask the defect.

## Acceptance criteria

- A new exact candidate and authorized-path delivery are recorded.
- Fresh native evidence covers record-owner name-expansion and pointer exhaustion over UDP and TCP; effective-default RR and pointer boundaries; rejection of over-hard pointer configuration; and synchronous UDP datagrams larger than the configured admitted size.
- Every configured excess becomes terminal `RESOURCE_LIMIT`, performs no over-budget allocation/copy/traversal, releases accounting exactly once, and leaves no takeable result. An oversized datagram is never accepted as a valid truncated prefix.
- The DNS-G8-002 context-owned accounting and detached-handle safety behavior remains intact.
- A fresh independent G7 reviewer approves the new candidate, followed by a fresh independent G8 reviewer with no unresolved blocking finding.

## Resolution (destination role)

Pending.

## Closure (orchestrator after verification)

Pending.