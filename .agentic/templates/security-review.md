# Security review

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | security-reviewer |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Threat scope
Assets, attackers, entrypoints, trust boundaries, peer roles, dependencies and revision.

## Adversarial checklist
Record applicable/not applicable and evidence for lengths, overflow/truncation,
bounds, recursion/cycles/nesting, allocation/decompression amplification, exhaustion,
ambiguity/smuggling, unknown/truncated inputs, invalid states, sessions/timers,
lifetime/threading/callback races, negotiation/downgrade and composition.

## Findings
| Finding ID | Input/event/reproduction | Requirement/design reference | Impact/severity/rationale | Blocking? | Owner | Remediation evidence/status |
| --- | --- | --- | --- | --- | --- | --- |

## Independent verification and residual risk
Fix revision, reproduction/recheck result, remaining limits and accepted risk decision.
No blocking finding may be hidden by weakening a test or expectation.

