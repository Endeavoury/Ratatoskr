# DNS-G8-001 configured-limits remediation 002

| Metadata | Value |
| --- | --- |
| Workflow / stage / assignment | `dns-implementation-20260913` / `native_implementation` / `g8-configured-limits-remediation-002` |
| Active role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-002/` |
| Baseline | `git:9afc2e8825619dccc73e8eed00a431f838dd8a47` |
| Candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Handoff target | `protocol-orchestrator` for fresh independent G7 then G8 routing |

## Scope

Resolve blocking finding `DNS-G8-001` only: preserve `read_name` resource disposition, make compression traversal configuration enforceable, order configured/effective resource checks ahead of overlapping hard guards, and reject truncated synchronous UDP datagrams before parsing. Preserve the context-owned accounting, exact-once release, terminal cleanup/no-result, context destruction, and detached-handle behavior established by `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`.

## Authorized writes

Production files only:

- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_internal.h`

Owned workspace files are this README, `implementation-report.md`, `handoffs/`, and `completion-report.md`. The only other-role exception is the `## Resolution (destination role)` section of the originating DNS-G8-001 handoff.

All tests, public headers, core source, build files, workflow state, approved truth, reviews, vectors, and other workspaces remain read-only. No G7, G8, G9, or later gate disposition is claimed.
