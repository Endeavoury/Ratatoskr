# G4 compatibility return handoff — C-COMP-001

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-handoff-g4-compatibility-c-comp-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `compatibility-reviewer` |
| Status | `CHANGES_REQUESTED` |
| Revision | Subject candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`. |
| Source artifacts | Compatibility report and G12-style support review in this workspace; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`. |
| Assumptions | Public native API design remains the protocol-api-designer's owned truth. |
| Open questions | Numeric resource policy remains with maintainer via protocol-orchestrator if the designer cannot state existing policy. |
| Limitations | No remediation, header realization, implementation, binding, or state update is performed here. |

## Routing

- **ID / stage:** `C-COMP-001` / `native_api_design`.
- **Source:** `compatibility-reviewer / g4-compatibility-review-001`.
- **Destination:** `protocol-api-designer`, routed by `protocol-orchestrator`.
- **Blocking:** true.
- **Reason:** Proposed public C API cannot compile and has incomplete public input types, preventing ABI/source/binding compatibility approval.

## Evidence

1. Candidate §2 defines `typedef uint32_t ratos_dns_request_state;`; API-DNS-008 uses `ratos_dns_request_state ratos_dns_request_state(const ratos_dns_request *r)`. A C11 syntax probe of those declarations exits 1: `ratos_dns_request_state redeclared as different kind of symbol`.
2. APIs 001/002 name `ratos_dns_request_options`; APIs 012 names `ratos_dns_limits`; the candidate contains no declarations/layouts for either type. A C11 syntax probe of those proposed declarations exits 1 with unknown-type errors for both names.
3. ABI-1 policy permits additive symbols only while preserving a valid compatible C ABI; a declaration that cannot compile or cannot describe its public structs is not eligible for that conclusion.

## Requested action and acceptance criteria

The `protocol-api-designer` must issue a new immutable design candidate, without header/code realization, that:

1. uses nonconflicting C identifiers for the request-state typedef and accessor;
2. defines request-options and limits layouts and initializers completely, including field order/types, `struct_size` mandatory prefix, reserved input/output behavior, append-only evolution, nullability/lifetime/copy semantics, defaults and validation;
3. preserves the existing ABI-1 symbols, ownership, and synchronous DNS behavior; and
4. supplies a corrected candidate for fresh independent compatibility review. If numeric defaults require a policy choice not already recorded, return that choice to maintainer through `protocol-orchestrator` rather than inventing it.

## Resolution

`protocol-api-designer / g4-compatibility-remediation-001` supplied replacement candidate `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` at Git revision `e3c63fd`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`, with status `READY_FOR_REVIEW`.

It resolves the ordinary-identifier collision by retaining `typedef uint32_t ratos_dns_request_state;` and renaming the accessor to `ratos_dns_request_get_state(const ratos_dns_request *request)`. It completely defines `ratos_dns_request_options` and `ratos_dns_limits`: normative fixed-width field order/types; mandatory `struct_size`; initializer behavior; reserved input/output zero rules; append-only evolution; borrowed input and copy/no-retention semantics; validation; symbolic implementation-selected default-source behavior; and ABI-1 additive implications. It preserves baseline symbols, result ownership, synchronous `ratos_dns_query` behavior, and the callback-free UDP-first/TCP-fallback model.

No numeric resource defaults were invented. `agents/protocol-api-designer/g4-compatibility-remediation-001/handoffs/maintainer-resource-policy.md` records the required maintainer decision through `protocol-orchestrator`. Fresh independent compatibility re-review is required; this destination resolution does not close the handoff or approve G4.

## Closure

Pending orchestrator verification; this handoff is not self-closed.
