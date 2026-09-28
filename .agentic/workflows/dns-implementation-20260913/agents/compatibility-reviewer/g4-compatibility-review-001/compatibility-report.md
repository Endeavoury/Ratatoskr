# DNS G4 compatibility report

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-compatibility-report-g4-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `compatibility-reviewer` |
| Status | `CHANGES_REQUESTED` |
| Revision | Immutable subject candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`. |
| Source artifacts | ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b`; analysis `5615caed0b7ad0a321d6794e71b79c4195e90384`; binding evidence recorded in the companion G12-style record. |
| Assumptions | Candidate text is the complete proposed public declaration contract; header/code realization is forbidden and has not occurred. |
| Open questions | Numeric limits/defaults and binding-target choice are product policy, not resolved here. |
| Limitations | Artifact review and two isolated C syntax probes only; no header realization, ABI binary test, implementation, runtime behavior, or binding package test exists. |

## Scope and baseline

This is independent ABI/source/binding/behavior compatibility evidence supporting the mandatory G4 review only. It is **not** overall G4 approval and does not advance G5, G6, implementation, bindings, documentation, or workflow state.

ABI-1 permits additive symbols, constants, record types, and appended versioned-input fields, but forbids removal/rename/reorder, ownership/lifetime changes, or private layout exposure. The baseline exposes synchronous `ratos_dns_query` and opaque `ratos_dns_result`; no baseline `ratos_dns_request` API exists. The candidate states that synchronous `ratos_dns_query` remains unchanged and proposes new opaque request/result operations, fixed-width categories, event/endpoint structs, capabilities, options, and limits.

## Compatibility assessment

| Axis | Classification | Assessment |
| --- | --- | --- |
| Existing binary ABI | Conditionally additive | The candidate does not alter baseline headers or symbols at its immutable revision; its intended request APIs are new names and preserve existing result ownership in text. If the new declarations were complete and source-valid, adding exports could remain ABI-1-compatible. Compilation is not treated as ABI proof. |
| Proposed ABI contract | Blocking incomplete | `ratos_dns_event` and `ratos_dns_endpoint` have field order, `struct_size`, and reserved-field rules, but APIs 001/012 expose `ratos_dns_request_options` and `ratos_dns_limits` without defining either public struct/layout, initializer semantics, mandatory prefix, or evolution contract. Their ABI cannot be reviewed or bound. |
| C source API | Breaking/non-realizable | Candidate §3 declares `typedef uint32_t ratos_dns_request_state;` and API-DNS-008 declares a function with the identical ordinary C identifier. Typedef names and functions share C's ordinary identifier namespace. The proposed public C header therefore fails to compile. Isolated C11 syntax probe exited 1 with “redeclared as different kind of symbol.” A second probe for APIs 001/012 exited 1 because both omitted types are unknown. |
| Bindings | Blocked by source/API defects | Scoped re-review `0f0eb9…` approved F-BIND-001/F-BIND-002: the candidate now specifies event/endpoint and text marshaling. That scoped result cannot compensate for the unresolved options/limits definitions or the invalid C identifier collision. FFI generators and hand-authored bindings require a compilable, complete C header. No binding target is selected; `docs/migration-dotnet.md` remains baseline-only evidence. |
| Behavior | Additive intent; unverified | The stated single-driver, callback-free UDP-first/TCP-fallback behavior aligns with the G3 model and preserves valid nonzero RCODE as a result. No runtime change exists, and no implementation/vector evidence exists, so behavioral compatibility cannot be executed or accepted. Existing synchronous query behavior must remain unchanged in a later realization. |

## Migration, versioning, and deprecation implications

No existing API is proposed for removal or deprecation, and the synchronous query surface must not be retired. Per `docs/abi.md`, a corrected addition can remain `RATOS_ABI_VERSION == 1` only if it preserves all baseline ABI-1 contracts and provides complete compatible declarations. The collision and omitted types must be corrected before asserting that condition. A later implementation must document capability discovery and use normal library/product versioning for added exports; do not claim a new ABI generation unless a binary-incompatible change is actually chosen. Existing .NET compatibility policy retains legacy public types but does not authorize a new binding mapping; no migration instruction is selected here.

## Finding and scoped disposition

**C-COMP-001 (blocking):** The candidate is not a valid complete C public API. Rename either the `ratos_dns_request_state` typedef or its accessor using an unambiguous C-compatible API name, and define both `ratos_dns_request_options` and `ratos_dns_limits` fully at the design level (field order/types, `struct_size`, initialization, ownership/nullability, reserved/evolution, defaults/validation, and ABI implications). Recheck every function signature after that correction.

**Scoped disposition: `CHANGES_REQUESTED`.** Route C-COMP-001 to `protocol-api-designer` via the attached handoff. This is mandatory G12-style support evidence for G4 only; it neither approves G4 nor makes a product/version decision.
