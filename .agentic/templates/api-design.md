# Native API design

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | protocol-api-designer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Capability and operation map
| Operation ID | Model/requirement IDs | Proposed public operation | Inputs/outputs | Unsupported/feature detection |
| --- | --- | --- | --- | --- |

## Ownership and buffers
| Value/handle | Allocator/owner | Borrow/copy/mutation rule | Lifetime/release | Length/encoding | Failure output |
| --- | --- | --- | --- | --- | --- |

## Errors and stateful operations
Specify stable error categories, partial success, incremental consumption/production,
stream/session operations, lifecycle transitions, timers, cancellation and callbacks.

## Configuration, threading and reentrancy
Specify limits/defaults, concurrency guarantees, callback lifetime/thread and feature
negotiation. Distinguish synchronous ABI from future binding scheduling.

## ABI evolution
Baseline public symbols/layouts, proposed additions/changes, fixed-width/range rules,
opaque handles, struct versioning, compatibility implications and migration.

## Review questions
Binding representability, unsafe mappings, unresolved model requirements and decisions.
This document proposes the API; it does not modify public headers.

