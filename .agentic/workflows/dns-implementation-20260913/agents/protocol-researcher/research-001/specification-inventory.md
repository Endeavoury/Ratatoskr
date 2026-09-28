# DNS specification inventory — native unicast stub/client

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-specification-inventory-research-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-researcher |
| Status | READY_FOR_REVIEW |
| Revision | Baseline Git `42b0611efa90e4b62f06d07cca64044ae9f090a7`; inventory checked 2026-09-13 |
| Source artifacts | `request.md`, `manifest.yaml`, `workflow-state.yaml`, `g0-intake.md`, delegation `protocol-researcher-research-001.md`, all at baseline/workflow intake |
| Assumptions | Scope is the recorded native DNS unicast stub/client query construction and response parsing, UDP with TCP fallback, and public C result/ownership surface. Existing code/docs are discovery leads only. |
| Open questions | The analyst must determine effective behavior for out-of-scope extension material encountered in a response and whether API-supported query types include ANY or other special QTYPEs. Binding scope remains a maintainer decision (`DNS-SCOPE-001`). |
| Limitations | This is source discovery, not requirements analysis, API design, vectors, implementation evidence, or G1 approval. RFC Editor/IANA pages are live registries/errata indexes; snapshot dates and URLs are recorded below. |

## Scope and source-authority method

**ACTIVE ROLE: protocol-researcher.** G0 is present and administrative-only: `g0-intake.md` records the native unicast stub/client focus and that G1 is not approved. The authoritative hierarchy used here is: (1) RFC Editor publication and RFC information/errata pages for RFC status, update/obsolescence and errata; (2) IANA DNS Parameters registry for currently assigned wire values; (3) IETF RFC text for relevant sections. Repository sources were read only to discover the bounded product surface; they are not normative authority.

Checked date for all external pages: **2026-09-13**. “Publication revision” means the immutable RFC publication named by number; individual RFCs do not expose a source commit. Registry snapshot is the page’s displayed **Last Updated 2026-08-28**. An erratum is not treated as an automatic replacement: only its stated RFC Editor status is recorded.

## Scope classification

| Inventory area | Disposition | Why it is in this inventory |
| --- | --- | --- |
| Standard QUERY request/response message, domain names, RR envelope, UDP exchange | Applicable source family | Directly supports native query construction and response parsing. |
| TCP DNS framing and use after UDP truncation | Applicable source family | Explicitly included native transport scope. |
| Response correlation and forged-response resistance | Applicable security source | A stub/client receives untrusted network responses. Applicability of individual rules remains for G1 analyst review. |
| Unknown RR envelope/raw RDATA | Applicable source family | Product discovery shows unknown result retention; source establishes a forward-compatibility authority. |
| Current DNS numeric assignments | Applicable registry | Parser/query surface contains types, classes, opcodes, RCODEs and header flags; values are IANA-governed. |
| EDNS(0), EDE, DNSSEC records/validation, cache policy, encrypted transports, mDNS/DNS-SD, authoritative/recursive service, transfers/updates | Deferred or excluded as classified below | Explicit G0 exclusions/deferred scope; still recorded because formal base-spec updates and registry entries can otherwise be mistaken for silently supported behavior. |

## Official source inventory

| ID | Official source and status | Relevant sections / source revision | Update, successor and errata disposition | Scope disposition |
| --- | --- | --- | --- | --- |
| DNS-SRC-001 | [RFC 1034 — *Domain names - concepts and facilities*](https://www.rfc-editor.org/rfc/rfc1034.html), STD 13, Nov. 1987 | §§3.1–3.3, 3.6, 4.3.1, 5.3.1; publication RFC 1034 | Obsoletes RFCs 882/883/973. RFC Editor errata page checked: 10 verified (including technical EID 4740 in server algorithm) and 8 held; server/zone errata are not silently applied to client scope. Later documents update selected portions; listed in closure. | Applicable conceptual/name and stub-resolver context; authoritative-server/recursive algorithms excluded. |
| DNS-SRC-002 | [RFC 1035 — *Domain names - implementation and specification*](https://www.rfc-editor.org/rfc/rfc1035.html), STD 13, Nov. 1987 | §§2.3.4, 3.1–3.3, 4.1–4.2.2, 7.2; publication RFC 1035 | Obsoletes RFCs 882/883/973. RFC Editor errata index checked: 12 verified, 16 held for document update; verified/held items must be evaluated section-by-section by analyst, not adopted wholesale. Formal update descendants are enumerated in closure. | Foundational applicable wire/message/name/UDP/TCP source, subject to applicable successors. |
| DNS-SRC-003 | [RFC 1123 — *Requirements for Internet Hosts -- Application and Support*](https://www.rfc-editor.org/rfc/rfc1123.html), STD 3, Oct. 1989 | §6.1.3.1–§6.1.3.2 (resolver configuration/transport requirements); publication RFC 1123 | Updated in its DNS/TCP portions by RFC 2181 and RFC 7766. | Applicable only to the host/stub resolver portions identified; retry/server-selection policy needs analyst scoping. |
| DNS-SRC-004 | [RFC 2181 — *Clarifications to the DNS Specification*](https://www.rfc-editor.org/rfc/rfc2181.html), Standards Track, Jul. 1997 | §§5, 8, 9, 10, 11; publication RFC 2181 | Updates RFCs 1034/1035/1123. RFC Editor errata page: one technical EID 6446, **Rejected**; no replacement text applies. Later updates include RFC 4343, RFC 5452, RFC 8767 and DNSSEC documents. | Applicable clarification family for message/name/RR parsing where its section applies; cache/server-only text excluded. |
| DNS-SRC-005 | [RFC 4343 — *DNS Case Insensitivity Clarification*](https://www.rfc-editor.org/rfc/rfc4343.html), Standards Track, Jan. 2006 | §§2–4, especially §3 and §4; publication RFC 4343 | Updates RFCs 1034/1035/2181; no successor found in visited closure. | Applicable to DNS name comparison/presentation; analyst must map to response correlation/API representation. |
| DNS-SRC-006 | [RFC 3597 — *Handling of Unknown DNS Resource Record (RR) Types*](https://www.rfc-editor.org/rfc/rfc3597.html), Standards Track, Sep. 2003 | §§2–5; publication RFC 3597 | Updated by RFC 6895 (IANA considerations). | Applicable to unknown RR type envelope/raw RDATA handling. Master-file text-format rules are not automatically API requirements. |
| DNS-SRC-007 | [RFC 5452 — *Measures for Making DNS More Resilient against Forged Answers*](https://www.rfc-editor.org/rfc/rfc5452.html), Standards Track, Jan. 2009 | §§4, 5, 6, 9, 10; publication RFC 5452 | Updates RFC 2181; no obsoleting successor found in visited closure. | Applicable security discovery input for a client accepting UDP replies. Exact applicability of source-address/port and concurrency rules is analyst work. |
| DNS-SRC-008 | [RFC 7766 — *DNS Transport over TCP*](https://www.rfc-editor.org/rfc/rfc7766.html), Standards Track, Mar. 2016 | §§4–8, especially §8 length field; publication RFC 7766 | Obsoletes RFC 5966; updates RFCs 1035/1123. RFC Editor errata page checked: **no matching errata**. | Applicable TCP framing/transport successor. Connection reuse/pipelining policy is not inferred here. |
| DNS-SRC-009 | [RFC 9619 — *In the DNS, QDCOUNT Is (Usually) One*](https://www.rfc-editor.org/rfc/rfc9619.html), Standards Track, Jul. 2024 | §§3–5 and Appendix A; publication RFC 9619 | Updates RFC 1035. RFC Editor errata page: verified technical EID 8426 corrects only “QDCODE” to “QDCOUNT” in §1. | Applicable to OPCODE=0 query/response message parsing/construction; its stated exceptions and unsupported opcode scope remain analyst questions. |
| DNS-SRC-010 | [RFC 3425 — *Obsoleting IQUERY*](https://www.rfc-editor.org/rfc/rfc3425.html), Standards Track, Nov. 2002 | §§1–3; publication RFC 3425 | Updates RFC 1035; declares IQUERY obsolete. | Applicable exclusion: a standard QUERY-only client must not treat RFC 1035 IQUERY as supported. |
| DNS-SRC-011 | [RFC 6895 — *DNS IANA Considerations*](https://www.rfc-editor.org/rfc/rfc6895.html), BCP 42, Apr. 2013 | §§2–3 and registry references; publication RFC 6895 | Obsoletes RFC 6195; updates RFCs 1183/2845/2930/3597. | Applicable registry-policy context; current values come from IANA, not hard-coded from this RFC. |
| DNS-SRC-012 | [IANA DNS Parameters](https://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml), official live registry | DNS CLASSes, RR TYPEs, OpCodes, RCODEs, Label Types, EDNS option codes, DNS Header Flags; page last updated 2026-08-28 | Registry references RFCs 1035, 6895 and 9108 among others. It is a current assignment snapshot, not a protocol-behavior specification. | Applicable registry reference for exposed/parsed numeric fields; EDNS/DSO subregistries are deferred with their features. |
| DNS-SRC-013 | [RFC 9499 — *DNS Terminology*](https://www.rfc-editor.org/rfc/rfc9499.html), BCP 219, Mar. 2024 | §§1–2 and relevant glossary entries; publication RFC 9499 | Obsoletes RFC 8499; updates RFC 2308 terminology. RFC page links an errata index; terminology remains supporting authority rather than wire behavior. | Applicable vocabulary aid only; it creates no wire/API requirements in this inventory. |
| DNS-SRC-014 | [RFC 6891 — *Extension Mechanisms for DNS (EDNS(0))*](https://www.rfc-editor.org/rfc/rfc6891.html), STD 75, Apr. 2013 | §§3, 6–9; publication RFC 6891 | Obsoletes RFCs 2671/2673. Errata: EID 3604 verified editorial registry-name correction; EID 8348 held technical (OPT CLASS wording); EID 6982 rejected. | Deferred: G0 excludes EDNS. It remains a mandatory discovery lead if any future scope sends/parses OPT or relies on extended RCODE/payload negotiation. |
| DNS-SRC-015 | [RFC 8914 — *Extended DNS Errors*](https://www.rfc-editor.org/rfc/rfc8914.html), Standards Track, Oct. 2020 | §§1–4; publication RFC 8914 | Uses an RFC 6891 EDNS option; no successor found in visited closure. | Deferred with EDNS; not silently included merely because an EDE can appear in a response. |
| DNS-SRC-016 | [RFC 2308 — *Negative Caching of DNS Queries (DNS NCACHE)*](https://www.rfc-editor.org/rfc/rfc2308.html), Standards Track, Mar. 1998 | §§1–7; publication RFC 2308 | Updates RFCs 1034/1035; terminology portions updated by RFC 9499. | Excluded/deferred: G0 excludes caching. Parsing a negative response is distinguishable from caching it; analyst must not infer cache behavior. |
| DNS-SRC-017 | [RFC 8767 — *Serving Stale Data to Improve DNS Resiliency*](https://www.rfc-editor.org/rfc/rfc8767.html), Standards Track | §§1–6; publication RFC 8767 | Updates TTL definitions in RFCs 1034/1035 and RFC 2181 for recursive cache serve-stale behavior. | Excluded/deferred: caching/recursive resolver behavior. Its TTL update must not be generalized to non-cache parser behavior without analyst review. |

## Update/obsolescence closure

The RFC Editor’s RFC 1035 relationship index was traversed as a discovery queue. The following closure records every update/obsolescence lead encountered in the bounded native-client audit; grouping means the documents share the same scope disposition, not that their behavior is identical.

| Closure group | Visited sources and disposition |
| --- | --- |
| Foundational direct successors retained above | RFCs 1123, 2181, 2308, 3425, 3597, 4343, 5452, 6891, 7766, 8767 and 9619 are individually inventoried above. RFC 5966 was visited and classified **superseded** by RFC 7766. RFCs 2671 and 2673 were visited as EDNS predecessors and classified **superseded** by RFC 6891. RFC 8499 was visited as terminology predecessor and classified **superseded** by RFC 9499. |
| Query/opcode and server-operation extensions | RFCs 1995 (IXFR), 1996 (NOTIFY), 2136 (Dynamic UPDATE), 3425 (IQUERY), 5936 (AXFR), 8490 (DSO): **excluded** — no transfer, notification, update, IQUERY or DSO role is authorized. RFC 3425 is retained above because it directly excludes a legacy RFC 1035 opcode. |
| RR-type or data-format additions | RFCs 1101, 1183, 1348, 1876, 2137, 3658, 6604 and 8482: **deferred/out of current supported record scope**. They are feature/RR-specific updates, not evidence that this client supports the feature. RFC 3597 is retained because it governs unknown RR handling. Future supported typed records require their own source closure. |
| DNSSEC/security-key extensions | RFCs 2065, 2535, 2845, 4033, 4034 and 4035: **excluded/deferred** — DNSSEC validation and authenticated DNS transactions are out of G0 scope. RFC 2065 and RFC 2535 are obsolete historical DNSSEC predecessors; RFCs 4033–4035 are their standards-track replacement family. |
| Cache/recursive behavior | RFCs 2308 and 8767: **excluded/deferred**, individually inventoried above. RFC 5452 is retained as a security discovery input, but it does not authorize recursive-resolver scope. |
| Non-normative or role-external dependencies | UDP (RFC 768), TCP (RFC 793), resolver configuration, platform network APIs, retry policy and resource budgets: **dependency leads, not DNS source authority**. The manifest names the operating-system network stack dependency; product limits/policy must be surfaced by later analysis/API stages. |

Discovery closure result: no unclassified source remains in this queue. This is closure relative to the recorded unicast stub/client scope and the 2026-09-13 audit date, not a claim to inventory every DNS RFC or every IANA assignment.

## Registry disposition

The visited IANA page is the registry authority for current assignments, with a displayed snapshot date of 2026-08-28. Analyst review should reference the registry (and its listed RFC) for values rather than treat a local enum or historical compatibility matrix as authoritative.

| Registry | Disposition |
| --- | --- |
| DNS CLASSes, RR TYPEs, OpCodes, RCODEs, DNS Label Types, DNS Header Flags | Applicable lookup registries for classic DNS message/query/response parsing. Current assignment does not itself imply feature support. |
| DNS EDNS0 Option Codes, EDNS Header Flags, EDNS Version Number, Extended DNS Error Codes | Deferred with EDNS/EDE; recorded to prevent accidental interpretation as base-message fields. |
| DSO and DNS-over-QUIC related registries | Excluded/deferred with DSO and encrypted/QUIC transport scope. |

## Errata disposition summary

Errata pages were visited for RFCs 1034, 1035, 6891, 7766 and 9619; the RFC 2181 errata status was verified from the RFC Editor index. No errata disposition has been converted to an effective requirement here. RFC 9619 EID 8426 is verified technical but corrects terminology in its introduction; RFC 6891’s verified EID 3604 is editorial. RFC 1034/1035 contain both verified and held items across broad, mostly non-client sections, so the analyst must inspect any candidate section’s inline errata before deriving requirements. RFC 7766 has no matching errata. Rejected errata are not applied; held/reported items remain review inputs, not normative replacement text.

## Explicit exclusions and deferred areas

- Recursive resolution, authoritative service, delegation processing, caching (including negative and serve-stale), and resolver policy are excluded at G0.
- DNSSEC validation, trust anchors, DNSSEC algorithm policy, TSIG, and automated key management are excluded.
- EDNS(0), EDE, DNS Cookies, Client Subnet, padding, and EDNS payload negotiation are deferred; their presence must not be silently accepted as feature support without a scope decision and refreshed discovery.
- DNS over TLS/HTTPS/QUIC/DTLS, mDNS/DNS-SD, AXFR/IXFR, NOTIFY, UPDATE, DSO and encrypted-resolver discovery are excluded.
- Binding behavior remains outside current workflow scope pending maintainer decision `DNS-SCOPE-001`.

## Analyst handoff questions

1. For RFC 1035 sections affected by the sources above, identify the effective rule only after checking the exact successor section and applicable inline errata; do not infer behavior from the existing implementation.
2. Resolve how the selected public client role handles a received OPT/unknown option, extended RCODE, or unsupported opcode without expanding EDNS/DSO scope. This inventory classifies authority but does not decide behavior.
3. Resolve scope for query types exposed by the native API (including whether ANY/meta-QTYPE behavior is in scope) before treating feature-specific RR RFCs as mandatory.
4. Separate parsing/display of a negative DNS response from negative caching and recursive-resolution policy.

## Evidence and checks

- Read and verified G0/request/manifest/workflow-state and required role/shared contracts.
- Verified repository baseline and origin: `master`, `42b0611efa90e4b62f06d07cca64044ae9f090a7`, origin `https://github.com/Endeavoury/Ratatoskr.git`; workflow artifacts were pre-existing untracked intake state.
- Read the authorized DNS source/doc surface only as discovery evidence. `docs/dns.md` confirms UDP-first/TCP-fallback and explicit exclusion of EDNS/encrypted DNS/mDNS/update/AXFR; it is not cited as normative authority.
- Visited the official RFC Editor and IANA URLs above, including errata and update/obsolescence leads. No source-authority decision record was needed because the RFC Editor/IANA hierarchy is unambiguous for this inventory.
