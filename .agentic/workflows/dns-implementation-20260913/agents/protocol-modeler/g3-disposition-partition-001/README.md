# DNS G3 disposition-partition correction

| Field | Value |
| --- | --- |
| Assignment | `g3-disposition-partition-001` |
| Active role | `protocol-modeler` |
| Workflow / stage | `dns-implementation-20260913` / modeling corrective return for G3 |
| Target | `protocol/dns` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/` |
| Requested runtime | `gpt-5.6-terra` / medium |
| Actual exposed runtime | `openai-codex` / `gpt-5.6-terra`; reasoning effort and usage unknown |
| Attempt count | One bounded delivery attempt |

## Scope

This assignment resolves only `DNS-HO-API-G3-CORRECTIVE-001-DISPOSITION-PARTITION`. It defines an ordered, exhaustive observable disposition for every completed TCP frame correlated to the outstanding request. It does not alter approved analysis, numerical resource policy, API/ABI/parser design, reviews, workflow state, source, tests, vectors, bindings, docs, request, or manifest.

## Semantic correction

`DOM-TCP-CORRELATED-DISPOSITION` and `INV-TCP-CORRELATED-DISPOSITION-PARTITION` make classification ordered and exhaustive: resource-limit first; if not resource-limit, malformed; if not malformed, unsupported-extension for an otherwise valid excluded OPT/EDNS frame; otherwise publish. A nonmatching completed frame remains pending/ignored. Every terminal disposition retains the existing no-result, partial-state discard, context/buffer cleanup, and `DNS-REQ-019/023/024/025` traceability.

## Delivery boundary

Writable output is limited to this assignment workspace and the destination `## Resolution (destination role)` section of the specified reviewer handoff. A fresh independent G3 reviewer is requested but not dispatched.