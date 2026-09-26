# DNS interpretation decision — extension and QTYPE profile

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-decision-extension-qtype-profile` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-analyst |
| Status | READY_FOR_REVIEW |
| Revision | Working-tree candidate; committed revision recorded in `completion-report.md` |
| Source artifacts | G0 request/manifest; G1-approved inventory SHA-256 `9aa91abf9cb3a98c0fd3fb061f26d2c16e57ee4685c5efa729d3af7dfdef8073`; RFC 1035 §§3.2.3, 4.1; RFC 3597 §§2–5; RFC 6891 §§3, 6; IANA DNS Parameters registry |
| Assumptions | Native client scope remains standard unicast QUERY only and does not add an EDNS API. |
| Open questions | G2 may request a maintainer scope decision if compatibility evidence requires accepting OPT responses rather than the conservative profile below. |
| Limitations | This records requirements interpretation for a candidate only; it neither expands product scope nor approves G2. |

## Question
How must a bounded non-EDNS native client react to an OPT pseudo-RR or unsupported/meta QTYPE without silently claiming EDNS or special-query support?

## Decision
1. The profile sends only `OPCODE=0` standard QUERY messages with exactly one question. It accepts only ordinary supported QTYPE values selected by the native public profile; `QTYPE=255` (ANY), RFC 1035 meta-QTYPEs, and unassigned/reserved type values are **unsupported local operations**, not opaque requests. No packet is sent for them.
2. The response parser preserves an otherwise syntactically valid RR of unknown *ordinary* TYPE as opaque RDATA, as RFC 3597 requires. This does not imply semantic support for querying or interpreting that TYPE.
3. The profile does not send OPT and does not implement EDNS version/payload/option/extended-RCODE semantics. A received OPT (TYPE 41) is an unsupported extension response: finish structural validation safely, expose no successful DNS result, and return a distinct local `unsupported_extension`/protocol failure. Do not discard an extended RCODE or misreport only its low four bits as success.

## Rationale and source disposition
RFC 1035 defines standard queries and QTYPEs; RFC 9619 constrains this profile's QUERY count. RFC 3597 requires transparent handling only for an RR of unknown type and explicitly excludes known QTYPE/meta-type cases from that definition. RFC 6891 defines OPT as an EDNS pseudo-RR and places extended RCODE and option semantics in the OPT fields. The G0 manifest excludes EDNS, while the current native ABI documents no EDNS operation. Therefore accepting OPT while ignoring its semantics would falsely claim an unimplemented feature. Conservative rejection is a **local profile policy**, not a claim that RFC 6891 requires all clients to reject OPT.

## Observable effects and downstream impact
- Vectors need local rejection cases for ANY/meta/unassigned requests and for syntactically valid responses containing OPT, including one whose extended RCODE would change the effective result.
- The model/API must distinguish malformed wire data from a well-formed unsupported extension and must not expose a partial successful result.
- A later EDNS scope change supersedes this decision, requires refreshed source analysis (RFC 6891 and relevant option RFCs), a new API/model/vector review, and invalidates affected G2+ evidence.
