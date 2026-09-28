# ADR — fixed-width binding-visible DNS transaction contract

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g4-binding-safety-layout-decision-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `PROPOSED` within the submitted G4 candidate |
| Candidate | `../api-design.md`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814` |

## Decision

Represent all new request state, event kind, transport-failure, and DNS error-class values as named `uint32_t` typedefs with stable numeric constants. Represent event and endpoint values as caller-owned, `struct_size`-versioned public structs with only fixed-width scalars and pointers. Use a named request error-class accessor rather than an unnamed event-only classification.

## Rationale

Language bindings need a concrete allocation, initialization, decoding, and evolution contract. Fixed-width categories avoid compiler-sized enum layout ambiguity; an event struct gives every feed path a single initialized output shape; the endpoint struct gives binary address bytes an explicit pointer/length/family/lifetime contract. This resolves F-BIND-001 and F-BIND-002 without realizing an ABI in headers.

## Consequences and boundary

The candidate requires future independent binding-safety and compatibility review before any header realization. It does not determine ABI compatibility, numeric resource defaults, or a binding target, and it adds no implementation behavior beyond the approved semantic model.
