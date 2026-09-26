# Handoff: DNS-G8-001 configured-limits corrective candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-001-configured-limits-remediation-002-to-protocol-orchestrator` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` configured parser limits and synchronous UDP admission |
| Owner role | `c-protocol-implementer/g8-configured-limits-remediation-002` |
| Status | `READY_FOR_REVIEW` |
| Revision | Candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; artifact delivery commit reported by wrapper readback |
| Source artifacts | G8 handoff `agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`; accounting candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; G8 delivery `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |
| Assumptions | Approved same-context serialization and existing private resource-error mapping remain unchanged. |
| Open questions | None for implementation; independent reviewers must establish gate disposition. |
| Limitations | No CMake/CTest, dynamic socket-truncation reproduction, Windows cross-compile, fresh parser-boundary probe, or ThreadSanitizer evidence is claimed. |

## Routing

- ID / workflow / stage: `DNS-G8-001` / `dns-implementation-20260913` / `native_implementation` remediation.
- Source role and assignment: `c-protocol-implementer/g8-configured-limits-remediation-002`.
- Destination role: `protocol-orchestrator`.
- Target component: native DNS parser limit disposition and synchronous UDP admission.
- Reason: submit one corrective candidate for fresh independent G7 review and, only after G7 approval, fresh independent G8 review.
- Blocking: true until the required independent reviews resolve the finding.
- Status: `READY_FOR_REVIEW`.

## Source artifacts

The candidate is `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`, parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`. It modifies exactly:

- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_internal.h`

The implementation report records complete call-graph inspection, strict compilation, existing native/G7 runs, ASan/UBSan runs, diff checking, and explicit limitations. No public ABI, core, test, build, approved-truth, review, or workflow-state file changed.

## Specific problem or question

Determine independently whether candidate `1a371fe` fully resolves `DNS-G8-001`: exact record-owner resource propagation; rejection of traversal limits above 128; resource-first effective pointer and RR boundaries; and rejection of oversized synchronous UDP datagrams before fallback detection/parsing. Confirm that `DNS-G8-002` accounting, terminal cleanup/no-result, context destruction, and detached handles remain intact.

## Requested action

The protocol orchestrator should route a fresh independent G7 reviewer against exact candidate `1a371fe`. If and only if G7 approves, route a fresh independent G8 reviewer. Do not route G9 or claim either gate from this author handoff.

## Acceptance criteria

- Candidate and artifact-delivery commits are remote ancestors and remain within authorized paths.
- Fresh native evidence covers record-owner expansion/pointer exhaustion over UDP and TCP, effective-default RR and pointer boundaries, rejection of over-hard traversal configuration, and an actually oversized synchronous UDP datagram.
- Every configured excess is terminal `RESOURCE_LIMIT`, releases accounting exactly once, and leaves no takeable result; an oversized datagram is never accepted as a truncated correlated prefix.
- Accounting/lifecycle and public ABI behavior from `c38a7fa` remains unchanged.
- A fresh independent G7 reviewer records its disposition, followed by a fresh independent G8 reviewer if G7 approves.

## Resolution (destination role)

Pending protocol-orchestrator verification and independent routing.

## Closure (orchestrator after verification)

`protocol-orchestrator/g7-configured-limits-rereview-routing-003` verified the exact
candidate, reviewer delivery ancestry, permitted output boundary, required reviewer
artifacts, `git diff --check`, and wrapper remote readback
`git:7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`. Fresh independent
`protocol-test-engineer/g7-configured-limits-rereview-003` recorded G7 `APPROVED` for
candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`; G7 state is administratively
reflected. This closure does not approve, route, or perform G8, G9, or later work.
G8 remains `CHANGES_REQUESTED` pending a separately authorized independent review.
