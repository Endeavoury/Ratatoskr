# Decision — DNS G9 record resource authority

| Metadata | Value |
| --- | --- |
| Artifact ID | `DNS-G9-RECORD-RESOURCE-DESIGN-001` |
| Workflow / target | `dns-implementation-20260913` / DNS record-target resource failure |
| Owner | `protocol-api-designer/g9-record-resource-assessment-001` |
| Status | `BLOCKED` |
| Revision | Local-only working-tree decision at dispatch baseline `git:510d1a3617e0b66ed98b0980f277de689b5ae508` |
| Inputs | G9 result at tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`; authority handoff `git:8698fe9e5732f7b7b539d0130b13f4d3d730759f`; `DNS-REQ-024`; approved limits contract; current G6 preflight |

## Decision

Do not authorize a concrete private corrective candidate. Existing resource semantics require bounded parsing but leave numeric defaults to an unresolved maintainer/product decision, while the G9 RSS evidence does not determine a causal private code path. `src/protocols/dns/dns_parser.c` is therefore not an authorized candidate merely because the record fuzzer reaches `ratos_dns_parse_response`.

## Rationale

- The record run exceeded the fixed 1024 MiB budget; that proves a mandatory verification failure only.
- `DNS-REQ-024` requires limits and terminal no-partial-result behavior, but it does not select concrete resource values.
- The approved limits design and its maintainer handoff explicitly retain numeric defaults as unresolved policy and block realization requiring concrete values.
- Current G6 is revision- and path-bound to four accounting files and excludes parser work.

## Consequences

- G9 remains `BLOCKED`.
- No public ABI/API change is approved.
- No implementation path, review, rerun, or security action follows from this decision.
- The orchestrator must obtain the missing resource-policy/design authority and then conduct a future fresh G6 authority assessment for any actual candidate.