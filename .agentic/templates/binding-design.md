# Binding mapping design

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | binding-api-designer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Target profile
Language/runtime/platform versions, existing package baseline, native ABI revision,
intended capabilities. Language ID is not constrained to a fixed registry.

## Capability and ABI mapping
| Capability/API operation | Public ABI symbol/version | Mapping concept | Intended idiom | Supported/unsupported/deferred | Evidence adapter |
| --- | --- | --- | --- | --- | --- |

## Mapping rules
Buffers/lengths; text encoding and NULs; signedness/ranges; errors; opaque handles;
borrow/copy/retain/release; callback lifetime; thread/reentrancy/runtime constraints;
async scheduling and cancellation; feature detection and missing native capabilities.

## Packaging contract
Native discovery/bundling, runtime/platform support, local verification and limitations.
Publishing is a separate action.

## Unsafe mappings and decisions
Questions routed to protocol-api-designer; representation differences versus semantic
differences; approved decisions; independent BINDING_DESIGN reviewer.

