# Handoff: DNS-G8-001 remediation to protocol orchestrator

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-001-remediation-to-protocol-orchestrator` |
| Workflow ID / stage | `dns-implementation-20260913` / G8 security remediation |
| Target | `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Source revision | Local candidate after `git:9275f66dba3c19440da28ca86bd53777490b3e59`; wrapper delivery pending |
| Source inputs | DNS-G8-001 at security delivery `git:90a02df18522b6c311e236dc03c82583971c7511`; reviewed candidate `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee` |
| Limitations | CMake/CTest unavailable (`cmake` absent); existing native test executable passed. |

## Routing

- Source: `c-protocol-implementer/g8-limits-remediation-001`
- Destination: `protocol-orchestrator`
- Reason: bounded implementation remediation for blocking DNS-G8-001 is ready for independent review.
- Blocking: true until fresh G7 and then fresh G8 complete.

## Evidence

See `implementation-report.md`. The candidate changes only:

- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_internal.h`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_transport_tcp.c`

The implementation canonicalizes finite effective limits; enforces all configured message, frame, record, name, pointer, and typed-field budgets before relevant resource use; enforces request/connection reservations; and preserves terminal resource-limit/no-result cleanup for request paths.

## Requested action

Route a fresh independent `protocol-test-engineer` G7 review first. Only after a fresh G7 result, route a fresh independent `security-reviewer` G8 re-review for DNS-G8-001. Do not reuse the prior G7/G8 approvals and do not route G9.

## Acceptance criteria

1. G7 independently verifies the new candidate and existing/authorized test evidence.
2. Fresh G8 verifies each configured limit class, UDP/TCP terminal resource-limit behavior, and no partial result escape.
3. Orchestrator verifies revision, delivery, scope boundary, and reviewer independence before state advancement.
