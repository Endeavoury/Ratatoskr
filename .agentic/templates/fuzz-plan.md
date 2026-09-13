# Fuzz plan

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | fuzz-engineer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Target and prerequisites
Approved entrypoints, model/analysis/API/vector revisions, G7/G8 evidence and scope.

## Strategy
| Target/state surface | Seed provenance | Generation/mutation | Applicable invariant | Budget/limit | Reproduction method |
| --- | --- | --- | --- | --- | --- |

## Invariants
Select and justify no crash/undefined behavior, bounded resources, valid transitions,
semantic preservation. Round trip applies only to supported operations with specified
canonicalization/loss semantics. Include stateful event/time/stream sequences.

## Campaign design
Toolchain/sanitizers, build, corpus handling, dictionary, deterministic replay,
minimization, timeout/resource budgets and planned coverage limitations.

## Triage and acceptance
Route native defects, harness defects and interpretation disputes to owners.
A plan is not a completed campaign; reference fuzz-results.md for executed evidence.

