# G4 binding-safety return handoff

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-handoff-g4-binding-safety-to-api-designer-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `binding-api-designer` |
| Status | `CHANGES_REQUESTED` |
| Revision | Reviewer workspace record at repository HEAD `c2ab2aa30496edf70163b46b9572c0b155488eb4`. |
| Source artifacts | G4 candidate `api-design.md` and completion at Git `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`; binding-safety review `reviews/g4-binding-safety-review.md` in this workspace. |
| Assumptions | Native G4 candidate only; no binding target is selected. |
| Open questions | Concrete representations are unresolved by the candidate owner. |
| Limitations | No remediation, compatibility review, implementation, vectors, or binding work was performed. |

## Routing

- **ID / workflow / stage:** `DNS-G4-BINDING-SAFETY-API-CONTRACT-001` / `dns-implementation-20260913` / `native_api_design`.
- **Source role and assignment:** `binding-api-designer / g4-binding-safety-review-001`.
- **Destination role:** `protocol-api-designer`, routed by `protocol-orchestrator`.
- **Target:** `protocol/dns`.
- **Reason:** The submitted native API candidate cannot yet be safely represented by bindings because required binding-visible types and marshaling rules are incomplete.
- **Blocking:** true.
- **Status:** `CHANGES_REQUESTED`.

## Source artifacts and evidence

- Candidate `api-design.md` at `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`, SHA-256 `4e8c33beecf48a2a55d83183de7dd100c934fa874661a97ae7e25f67277d597d`.
- Baseline ABI at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; current `include/ratatoskr/` and `docs/abi.md` equality to that revision was verified.
- Findings: `F-BIND-001`, `F-BIND-002` in `reviews/g4-binding-safety-review.md`.

## Specific problem

The candidate uses `ratos_dns_event`, `ratos_dns_endpoint`, request state, transport-failure, and DNS error-class concepts as public function inputs/outputs without a complete, binding-visible ABI contract. `event` is described inconsistently as a fixed-width enum and as an object containing scalar fields. It neither defines a concrete layout nor names the error-class accessor it requires. It also fails to define the new `name` C-string/text encoding contract and exact endpoint address-byte pointer/length layout. The binding reviewer cannot invent these ABI semantics.

## Requested action

`protocol-api-designer` must revise its owned candidate only, without implementation or header realization, to resolve F-BIND-001 and F-BIND-002. The revision must define the new public type/operation contracts and input/output validity needed for safe language-neutral FFI mapping. Do not use this handoff to decide ABI compatibility; that remains with the separate compatibility reviewer.

## Acceptance criteria

1. A new immutable candidate revision explicitly identifies fixed-width types/layouts, initialization, reserved/versioning rules, and valid observable fields for every event/state/failure/error-class path.
2. It explicitly defines `name` text/NUL/lifetime rules and the endpoint address/length/nullability/lifetime contract.
3. It names and contracts the DNS error-class observation mechanism instead of relying on an unnamed field.
4. A fresh independent `binding-api-designer` review verifies both findings at the new revision; the compatibility review remains separately mandatory.

## Resolution (destination role)

Pending destination action.

## Closure (orchestrator after verification)

Pending orchestrator verification and routing; this handoff is not self-closed.
