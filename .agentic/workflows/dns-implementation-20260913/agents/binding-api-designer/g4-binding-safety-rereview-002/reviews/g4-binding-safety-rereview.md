# G4 binding-safety re-review — DNS remediation candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g4-binding-safety-rereview-002` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `binding-api-designer` (fresh independent reviewer) |
| Status | `APPROVED` — scoped solely to F-BIND-001 and F-BIND-002 |
| Candidate | Remediation `api-design.md` at Git `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814` |
| Limitation | This is not overall G4 approval and does not assess compatibility. A separate independent compatibility review remains mandatory and unperformed. |

## Scope, identity, and independence

- **Gate context:** G4 native API design; this record covers only the binding-safety remediation of `F-BIND-001` and `F-BIND-002`.
- **Reviewer:** `binding-api-designer / g4-binding-safety-rereview-002`, a fresh independent leaf session.
- **Independence declaration:** I did not author or edit the original API candidate (`protocol-api-designer/g4-api-design-001`), the remediation candidate (`protocol-api-designer/g4-binding-safety-remediation-001`), or the first binding-safety review (`binding-api-designer/g4-binding-safety-review-001`). I wrote only this assigned workspace. I performed no compatibility review, overall G4 decision, header/API realization, implementation, test, binding, documentation, vector, or workflow-state work.
- **Actual model telemetry:** requested `gpt-5.6-terra` / medium; exposed route `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry `unknown`.

## Immutable input verification

All revision-bound inputs were wrapper-read, rather than read from the mutable worktree.

| Input | Immutable revision | SHA-256 verified |
| --- | --- | --- |
| Remediation API candidate | `262c445a1b519b3baaa04f71fbcd59074c1baab0` | `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814` |
| Remediation completion report | `262c445a1b519b3baaa04f71fbcd59074c1baab0` | `6de8c06709d92d5b99eac797e6c7b974e05f5f75630f6342fd13a639231bb55e` |
| Corrected first review | `6126fa3f076614f69864186d9e9aa8223c3c024f` | `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4` |
| Corrected first return handoff | `6126fa3f076614f69864186d9e9aa8223c3c024f` | `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353` |
| ABI baseline `docs/abi.md` | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b` |
| ABI baseline `include/ratatoskr/dns.h` | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | `d8d316792368150c6157001c4f5efa7b0420c5cac6ff95d81387cf942ca34ff5` |
| ABI baseline `include/ratatoskr/error.h` | same | `52dbf424d8eb10a657bc5c1cc4f74d355acbd0ec93058882d9f7974fdacc3643` |
| ABI baseline `include/ratatoskr/context.h` | same | `af9a41beaf8260a38667847cf8d795deca94e668c77d59a05940a2b866c6b559` |
| ABI baseline `include/ratatoskr/export.h` | same | `8bf3e01bb4c02dbc5bfa14db29abbd7a4d05809056d0efa35556503f610dfdee` |
| ABI baseline `include/ratatoskr/ratatoskr.h` | same | `248d18e2a901b415544b5ae0eda63b76bd2dd25ba9ccbaa4312345bc3ba51e6d` |
| ABI baseline `include/ratatoskr/version.h` | same | `151b91f4f7353467e63bb255052aaa8773faa937f287e2930ae30f377efa270a` |

## Criterion review

| Finding | Candidate evidence | Binding-safety assessment | Scoped disposition |
| --- | --- | --- | --- |
| `F-BIND-001`: fixed-width representations; concrete layout, initialization, reserved/versioning/validity rules; named accessors | Candidate §2 defines `uint32_t` typedefs and stable constants for request state, event kind, transport failure, and DNS error class; §2.1 gives their concrete values; §2.2 gives complete `ratos_dns_event` field order and `ratos_dns_event_init`; §2 and §2.2 require `struct_size`, zero reserved fields, append-only evolution, and initialized outputs; §3 APIs 008–010 name and contract state/error-class/transport-failure accessors; §4 gives operation-by-operation event/output validity. | The candidate now gives an FFI adapter fixed-width categorical representations, an allocatable and initialized event layout, deterministic reserved-field and extension behavior, and named accessors for the required observable state/error values. Its validity matrix removes the prior ambiguity about which event fields can be decoded on each return path. This resolves the first review's blocking requirements without requiring bindings to infer a native layout. | `APPROVED` |
| `F-BIND-002`: `name` text/NUL/lifetime; endpoint binary address pointer/length/nullability/lifetime | Candidate §2.3 gives full `ratos_dns_endpoint` field order, family values, exact IPv4/IPv6 lengths, network-byte-order address bytes, host-order port, initializer defaults, nullability, invalid combinations, and receive-call borrowing duration. Candidate §3/API-DNS-002 and “Name text contract” define `name` as required non-NULL, borrowed for the call, UTF-8, NUL-terminated C text with first-NUL termination and no representable embedded NUL; they define validation and failure effects. | The candidate now permits a binding to construct an endpoint with exact pointer/length/family rules and retain its backing byte storage through the only permitted borrow window. It also permits deterministic name marshaling: UTF-8 C-string bytes, no embedded NUL, no pointer retention after return. No binding-side DNS parser or inferred text convention is required. | `APPROVED` |

## Disposition and limits

**Scoped disposition: `APPROVED`.** The remediation candidate resolves both `F-BIND-001` and `F-BIND-002` for this fresh independent binding-safety re-review.

This scoped approval does **not** grant overall G4 approval, decide ABI/source/binding compatibility, or authorize any later stage. Compatibility review is separately mandatory and unperformed. The protocol-orchestrator alone may interpret this reviewer record together with the required independent compatibility evidence.

## Checks and evidence

- Read `AGENTS.md`, the corrected delegation packet, the binding-api-designer role skill, required agentic contracts, workflow state, original packet, and historical blocked record before writing.
- Wrapper-only Git discovery confirmed repository root, origin, target branch, local baseline `2e4cc51521f3d1b2b1c0f395fc90704487629fb4`, and preserved unrelated untracked `g4-binding-safety-rereview-001`.
- Wrapper `show` reads and SHA-256 calculations verified every revision-bound input listed above before this assessment.
- No build or test was appropriate: the scope is immutable API-artifact review only and prohibits code/header/test/binding changes.
