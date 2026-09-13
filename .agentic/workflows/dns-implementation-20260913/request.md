# DNS governed implementation request

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-request` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | protocol-orchestrator |
| Status | APPROVED (G0 administrative intake only) |
| Revision | Git `42b0611efa90e4b62f06d07cca64044ae9f090a7` |
| Source artifacts | User authorization via root task `ratatoskr-dns-implementation-20260913`; project-orchestrator packet; repository discovery at the baseline |
| Assumptions | Existing DNS code is a baseline to inspect, not approved specification truth. |
| Open questions | Native scope is currently the unicast stub/client surface; whether existing binding exposure is in this implementation scope requires a later product decision. |
| Limitations | No technical gate or specification inventory approval exists. |

## Intent and authority
- **User request:** Govern a DNS implementation workflow for Ratatoskr.
- **Requested outcome and workflow type:** `ADD_PROTOCOL` / DNS, with durable artifacts and role-scoped work only after applicable approvals.
- **Target/dependencies:** DNS unicast stub/client baseline in native C, public C ABI, thin CLI, existing bindings, native tests and fuzz surface. Existing code is read-only until G6.
- **Requested mode:** implementation, governed by the full applicable native protocol flow.
- **Allowed changes now:** Only this workflow root's request, manifest and state plus the orchestrator intake workspace. No source, tests, docs, build, configuration, credentials, commits, pushes, merges or publication.
- **Explicit exclusions:** No gate bypasses; no technical self-approval; no external actions.
- **Authorization reference:** Root task `ratatoskr-dns-implementation-20260913` and its project-orchestrator packet.

## Baseline and scope
- **Repository revision:** `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `master`, commit `42b0611efa90e4b62f06d07cca64044ae9f090a7`, clean before this workflow initialization.
- **Existing capability evidence:** `src/protocols/dns/`, `include/ratatoskr/dns.h`, `cli/commands/dns.c`, `tests/dns/dns_tests.c`, `tests/integration/dns_fixture_test.py`, `fuzz/dns/`, and DNS documentation/binding consumers existed at baseline.
- **Initial supported surface to research:** DNS unicast stub/client query construction and response parsing; UDP with TCP fallback; public C result/ownership API. Existing docs identify recursive resolver, authoritative service, caching, DNSSEC validation, encrypted transports, mDNS/DNS-SD and unspecified extensions as separately classified scope items.
- **Deferred decisions:** Binding exposure scope is not selected at G0. Existing bindings remain read-only; their gate applicability is false unless a later scope decision changes it.
- **Applicable gates:** G0–G9, G12–G14 are applicable to the governed native implementation flow. `BINDING_DESIGN`, G10 and G11 are currently not applicable because no binding target is authorized in this workflow scope.
- **Acceptance:** Initialize traceable workflow artifacts; obtain a `READY_FOR_REVIEW` researcher inventory; require independent G1 before routing analysis. No implementation may begin before G1–G6 are approved.
- **Blocking choices:** A product owner/maintainer must decide whether any existing binding is in scope before binding design/exposure. This does not block DNS source discovery.
