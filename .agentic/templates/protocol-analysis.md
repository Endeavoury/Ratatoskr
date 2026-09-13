# Protocol analysis

> Template only. Copy into a concrete work item, replace placeholders, and record
> actual evidence before review. This file is not an approved artifact.

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | <artifact-id> |
| Workflow ID | <work-id> |
| Target | <kind/id> |
| Owner role | protocol-analyst |
| Status | NOT_STARTED |
| Revision | <Git commit or content digest> |
| Source artifacts | <repository paths and exact revisions> |
| Assumptions | <explicit assumptions or none> |
| Open questions | <blocking/nonblocking, owner, or none> |
| Limitations | <explicit limits or none> |

## Scope and effective authority
- Applicable peer roles, versions, transports/compositions and source precedence:
- Normative rules versus implementation policy; justified SHOULD departures:

## Requirement register
| Requirement ID | Source/section/update | Normative strength | Preconditions/applicability | Required observable behavior | Evidence plan | Open question |
| --- | --- | --- | --- | --- | --- | --- |

## Messages and wire layout
Define every message/field, offset or length rule, bit layout, byte order, encoding,
framing, checksums if applicable, allowed ranges, reserved and unknown values.

## Interaction and state
Define client/server states, events, transitions/guards, stream consumption,
need-more-input, sessions, multiplexing, timers, retransmission, shutdown and errors.

## Constraints and security
Define malformed/truncated handling, failure recovery/output validity, resource
limits, amplification/cycle/nesting risks, trust boundaries and configuration policy.

## Extension and dependency behavior
Define negotiation, versioning, unknown extensions, downgrade, composition boundaries
and requirement-to-capability links.

## Coverage and interpretation decisions
List resolved decisions, unresolved mandatory questions and excluded requirements.

