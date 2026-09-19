# G5 canonical DNS vectors — `g5-vectors-001`

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g5-vectors-001` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Active role | `vector-designer` |
| Status | `READY_FOR_REVIEW` candidate |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Owned workspace | `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-001/` |

## Scope

This workspace owns only language-independent G5 candidate vectors. It does not approve G5, change workflow state, authorize G6, or contain implementation, test, binding, or production artifacts.

## Candidate

`vector-set.json` contains 18 canonical cases spanning exact query construction; root and label boundaries; local rejection; positive UDP A, unknown-RR, and NXDOMAIN responses; structural malformed bytes; OPT handling; correlation isolation; UDP TC to incremental TCP; zero-length/coalesced/limit TCP frames; deadline and cancellation cleanup.

Byte provenance is case-local and is grounded in the approved analysis/model/API revisions plus RFC 1035, RFC 7766, RFC 9619, RFC 3597, and RFC 6891. No implementation, parser, builder, test, or binding was used as an oracle.

## Review request

The required handoff is `handoffs/g5-vectors-to-protocol-orchestrator.md`. G5 needs the designated independent protocol-test-engineer review and an independent protocol-analyst interpretation review.