# G9 DNS record-parser resource-policy/design assessment

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-api-design-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` record-parser resource growth under G9 |
| Owner role | `protocol-api-designer/g9-record-resource-assessment-001` |
| Status | `BLOCKED` |
| Revision | Local-only working-tree assessment at dispatch baseline `git:510d1a3617e0b66ed98b0980f277de689b5ae508` |
| Source artifacts | G9 execution evidence at `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`; source authority handoff at `git:8698fe9e5732f7b7b539d0130b13f4d3d730759f`; approved analysis/design and current G6 record listed below |
| Assumptions | `-rss_limit_mb=1024` is mandatory and remains unchanged. |
| Open questions | Maintainer/product resource policy has not selected concrete default limits; root cause of the observed RSS failure is not established by the supplied evidence. |
| Limitations | Assessment only: no code inspection conclusion is a root-cause finding, and no implementation/review/rerun is authorized. |

## 1. Revision-bound evidence

1. At tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`, `ratos_fuzz_dns_record` returned 71 after 21.236172719858587 seconds with `ru_maxrss` 1,675,884 KiB and libFuzzer reporting `used: 1636Mb; limit: 1024Mb`. Packet and name targets were clean. This is a mandatory G9 resource failure, not a diagnosis.
2. `fuzz/dns/fuzz_dns_record.c` invokes `ratos_dns_parse_response`. This identifies a read-only potential surface only. It does not establish a parser allocation, lifetime, or algorithmic cause.
3. Approved analysis `DNS-REQ-024` requires configured limits before allocation/iteration for frame bytes, RR/count work, name expansion, pointer traversal, typed-field/string bytes, and request/connection resources; limit excess is terminal with no partial result.
4. The approved limits contract in `g4-compatibility-remediation-001/api-design.md` declares every zero field to mean an implementation-selected documented default, never unlimited, but explicitly selects no numeric value. Its `maintainer-resource-policy.md` says a concrete default policy is blocking for realization that needs concrete defaults.
5. The current G6 record (`g8-accounting-g4-g6-implementation-routing-001/preflight-verification.md`) authorizes only `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c` for the accounting design. It expressly does not authorize `src/protocols/dns/dns_parser.c`.

## 2. Design conclusion

**Revised design/approval is required before a concrete bounded corrective candidate can be authorized.** Existing approved semantics establish the required categories and terminal behavior for bounded parsing, but do not choose the numeric default/hard-limit policy needed to determine whether a resource-policy correction is warranted or bounded. Separately, the observed G9 result does not identify which private implementation path would correct the failure.

Therefore this assessment authorizes **no candidate private path**. `src/protocols/dns/dns_parser.c` is not named as a candidate: it is merely a potential surface outside current G6, and naming it would infer a root cause and broaden authority without evidence. No other private path is warranted by the supplied evidence.

The mandatory G9 budget remains exactly `-rss_limit_mb=1024`. It is a verification constraint, not an implementation-selected DNS default, and must not be raised, weakened, or reinterpreted.

## 3. Public ABI and behavior boundary

No public ABI/API change is approved or proposed here. The existing approved resource contract remains the only relevant semantic baseline: resource-limit outcomes remain terminal and publish no partial result. Any later public API, default-policy, error-contract, ownership, or ABI effect requires separately demonstrated design authority and the applicable independent review; this assessment grants none.

## 4. Required future authority sequence

The protocol orchestrator must first obtain the unresolved maintainer/product resource-policy decision (or an explicit documented decision that no numeric-default change is needed) and have the responsible design owner produce any required revision-bound design candidate. Only then may it perform a **future fresh G6 authority assessment** against the exact candidate, exact private paths, applicable renewed approvals, and the unchanged 1024 MiB G9 requirement.

That future assessment must not treat this `BLOCKED` record as G6 renewal, implementation authority, G9 approval, or proof of root cause. It determines whether any G4/G5/G6 evidence is stale or must be renewed based on the actual candidate; no review is routed by this assessment.

## 5. Traceability

| ID | Disposition |
| --- | --- |
| `DNS-REQ-024` | Existing bounded-parsing semantics apply, but numeric defaults remain unresolved product policy. |
| `DNS-G9-RECORD-RESOURCE-AUTHORITY-001` | G9 failure is preserved as blocking evidence; no cause or corrective path inferred. |
| G6 current authority | Not extensible administratively; its four-path accounting scope excludes parser work. |
| G9 `-rss_limit_mb=1024` | Mandatory, unchanged, and not a substitute for DNS resource-policy approval. |