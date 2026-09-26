# DNS-G7-001 local-label remediation

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g7-local-label-remediation-001-readme` |
| Workflow / stage | `dns-implementation-20260913` / corrective return from G7 `native_verification` |
| Target | `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Routing baseline | `37a59e7cba78a2b1455d407ec70854fd8255ce9e` |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Leaf workspace | `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g7-local-label-remediation-001/` |

Scope: only `src/protocols/dns/dns_client.c` was changed. `ratos_dns_request_start` now validates presentation-name label and wire-length boundaries before `calloc` or request duplication, rejecting a 64-octet label with `RATOS_ERROR_INVALID_ARGUMENT` while retaining the caller-visible null out-request initialization. The leaf requests an independent G7 re-review; it does not approve G7.

The assigned Resolution section in the original G7 handoff is updated, and this workspace contains the implementation, completion, and independent-review-request artifacts. Delivery is local-only because no absolute executable `git-agent` wrapper was found.