# Binding exposure report

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | binding-implementer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Approved baseline
Mapping gate, native ABI/capability/vector revisions and package paths.

## Exposure and adapters
| Capability | Native symbol | Binding entrypoint | Canonical case/adapter | Result | Unsupported reason |
| --- | --- | --- | --- | --- | --- |

## Implementation evidence
FFI/lifetime/errors/ranges/text; callback/thread/async contract; no wire implementation.

## Local packaging and verification
Build/load/install/native-discovery commands, runtime/platform, artifact revision,
execution results and limitations. Link binding-local tests and adapter provenance.

## Handoffs
Mapping/native gaps, conformance request and G10 evidence. No publication claim.

