# Protocol verification report

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | protocol-test-engineer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Inputs and harness provenance
Approved vectors/design and native revision; adapters/generation source; independent
harness reviewer identity if the report author created harness code.

## Requirement evidence
| Requirement ID | Vector ID | Test/harness ID | Layer | Platform/build | Executed/result | Evidence |
| --- | --- | --- | --- | --- | --- | --- |

## Native review
Design conformance, bounds/ownership/state/error findings and responsible owners.

## Execution integrity
Commands/tool versions, assertion execution in build modes, deterministic event/peer
setup, timeouts and no-public-network assumptions. Record unexecuted checks.

## Discrepancies and coverage
Separate harness defect, implementation defect, expectation dispute, missing evidence;
link handoffs and affected requirements. Do not edit canonical truth.

