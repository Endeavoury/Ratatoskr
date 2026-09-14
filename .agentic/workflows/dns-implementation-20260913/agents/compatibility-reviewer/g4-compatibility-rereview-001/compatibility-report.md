# DNS G4 compatibility re-review — C-COMP-001

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-compatibility-report-g4-rereview-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `compatibility-reviewer` |
| Status | `APPROVED` — G4-support / G12-style compatibility disposition only |
| Candidate revision | `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c` |
| Candidate SHA-256 | `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520` |
| Baseline ABI | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` |
| Assumptions | The reviewed design is the complete corrective contract for C-COMP-001; header realization remains future work. |
| Open questions | Numeric resource defaults remain maintainer policy; the existing maintainer handoff makes this nonblocking for the symbolic design contract but blocking for a realization that claims concrete defaults. |
| Limitations | No public header/library, ABI export comparison, runtime, vector, documentation, or binding package exists to test. |

## Scope and correction

The prior independent compatibility review at delivery `0cb6e27b265c38e42d09d61c0883f1a086df8835` returned blocking `C-COMP-001`: an invalid ordinary-identifier collision between the request-state typedef and accessor, plus undefined public `ratos_dns_request_options` and `ratos_dns_limits` types. The new immutable candidate corrects exactly those compatibility defects at design level.

This report is independent compatibility support evidence for the applicable G4 native API-design gate. It supports G4 on the C-COMP-001 compatibility axis only. It neither approves overall G4 nor final workflow G12, advances no state, and authorizes no later stage.

## Compatibility assessment

| Axis | Baseline / correction comparison | Disposition |
| --- | --- | --- |
| Existing C ABI | ABI-1 permits additive exports and versioned input structs but forbids removal, rename, reordering, ownership changes, and exposed private layouts. The candidate changes no baseline header or ABI document and expressly preserves `ratos_dns_query`, `ratos_dns_query_options`, opaque result ownership, borrowed record/string/raw-data views, and existing error conventions. | Compatible additive intent; a future realized export comparison remains required. |
| C source API | The candidate retains `typedef uint32_t ratos_dns_request_state` and uses distinct accessor `ratos_dns_request_get_state`. It fully declares `ratos_dns_request_options` and `ratos_dns_limits` before their affected signatures. An isolated C11 declaration probe including the corrected types and all listed request operations passed with `cc -std=c11 -pedantic-errors -Wall -Wextra -x c -fsyntax-only -`. | C-COMP-001 source defect corrected. The probe validates declarations only, not a future complete public header. |
| ABI layout and evolution | Both new public input structs start with `uint32_t struct_size`, have normative fixed-width/pointer field order, initializer rules, reserved-zero input/output rules, mandatory-prefix rejection, no pointer retention, and append-only ABI-1 evolution. The candidate expressly rejects using reserved storage for future fields or changing existing field meaning/lifetime. | Compatible design contract for an additive ABI-1 realization. |
| Binding exposure implications | The prior scoped binding-safety re-review at `0f0eb9db033f4c26481a302df397184515dc60ad` approved F-BIND-001/F-BIND-002 only. This correction removes the remaining C-header obstacles it identified: bindings can allocate initialized options/limits with fixed-width fields, preserve pointer storage through the stated call borrow, and rely on no-retention/copy semantics. No binding target or package is selected or tested. | No C-COMP-001 binding blocker remains; not a binding implementation approval. |
| Protocol behavior | The candidate preserves the G3 UDP-first, correlated-TC-only TCP fallback and single-driver model; nonzero DNS RCODE remains a structured result, while malformed/resource-limit/unsupported-extension/transport/cancelled outcomes expose no partial result. Existing synchronous query behavior is explicitly not redirected. | Additive behavior intent consistent with model/analysis; unexecuted. |
| Migration, versioning, deprecation | No baseline API removal, deprecation, ABI-version increment, or binding migration is proposed. Under `docs/abi.md`, the additive ABI-1 path remains valid only if a later realization preserves these declarations and ownership contracts. `docs/migration-dotnet.md` stays baseline-only evidence; it neither selects a new binding nor changes the .NET migration policy. | No new migration or deprecation action is required for this design correction. |

## Evidence and limitations

- Candidate `api-design.md` was Git-read at `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; its SHA-256 matched `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`.
- Candidate completion report at delivery `0902aabe1306cf3700044d978e75d4b73d7638dc` identifies the same candidate revision/digest and `READY_FOR_REVIEW` status.
- Immutable G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b` and analysis `5615caed0b7ad0a321d6794e71b79c4195e90384` matched packet digests `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700` and `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- The candidate commit contains only its three protocol-api-designer workspace files; there is no header/source/binding/docs/state change. The baseline-to-candidate diff for `include/ratatoskr/` and `docs/abi.md` is empty.
- No binary ABI comparison, library build, runtime behavior, vectors, or binding package can be run because the assignment is a design-artifact re-review and those artifacts do not exist.

## Disposition

**APPROVED.** `C-COMP-001` is corrected in candidate `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`: the ordinary C identifier collision is removed, and the two previously omitted public versioned input contracts are complete enough to assess ABI/source/binding implications. This is a G4-support / G12-style compatibility approval only. Overall G4 still requires the protocol-orchestrator to combine all mandatory independent evidence and update shared state; this reviewer does neither.

No new handoff is required: the assigned corrective acceptance criteria are met. The existing `maintainer-resource-policy.md` remains the route for a future concrete-default decision and is outside this C-COMP-001 correction.
