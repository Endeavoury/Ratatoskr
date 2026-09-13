# Binding lifecycle

“Add a Swift binding” or “Add a Python binding” selects ADD_BINDING. The orchestrator
first inspects `bindings/<language>/`: in this repository both example directories
already exist. Distinguish creation, completion, extension, and audit without
overwriting an existing package. The language ID is open-ended.

The native ABI and approved protocol artifacts are inputs. Adding one binding must
not require redesigning every protocol or discovering protocol semantics afresh.

| Stage | Owner | Output / review |
| --- | --- | --- |
| Request and baseline | protocol-orchestrator | Binding manifest, supported platforms/versions, native revision, G0 |
| Mapping design | binding-api-designer | Buffer/string/error/handle/callback/async/threading mapping, capability table, BINDING_DESIGN review |
| Implementation | binding-implementer | Idiomatic FFI/lifetime wrappers within approved ABI |
| Protocol registry exposure | binding-implementer | Capability-to-public-surface mapping with unsupported features explicit |
| Canonical vector adaptation | binding-implementer | Mechanical byte/argument adapters; no changed expectations |
| Packaging verification | binding-implementer | Local package build/load/native-library discovery evidence; G10 |
| Conformance | conformance-reviewer | Same native semantics across declared surfaces/platforms; G11 |
| Documentation | documentation-writer | Install/use/ownership/errors/async/limitations; G13 |
| Compatibility | compatibility-reviewer | Public API, native compatibility, supported runtime/version impact; G12 |
| Final audit | final-reviewer | All applicable evidence current; G14 |

Packaging is prepared before G10 so conformance can use the intended packaged
artifact. If packaging changes after conformance, rerun affected evidence. Publishing
is a separate authorized release action, not part of local packaging acceptance.

The orchestrator owns each transition, registers inputs by revision, and delegates
one binding target per disjoint write scope. Mapping review is by an independent
binding-api-designer; ABI doubts involve protocol-api-designer. Native gates may be
reused only with sufficient approved evidence for the capabilities being exposed.
Missing evidence creates a linked upstream handoff; it does not block unrelated
mapping investigation or authorize native redesign by the binding implementer.

Mapping is conceptual before it becomes language declarations: ranges/signedness,
encoding and embedded NULs, borrowed versus copied buffers, retain/release, exceptions
versus returned errors, callback lifetimes, runtime thread restrictions, cancellation,
and worker scheduling over a synchronous native API all need explicit treatment.
Async wrappers must not claim native cancellation that the ABI does not provide.

Conformance compares normalized meaning, errors, ordering and lifecycle, not identical
class names or formatting idioms. Canonical protocol bytes stay authoritative. When
the public ABI has no raw parser entrypoint, reuse native vector evidence and test
the binding through supported calls/local exchanges; do not expose internals or add
a binding parser to make a vector harness convenient.

Unsafe/unrepresentable mapping → binding-api-designer → protocol-api-designer if
needed. Wrapper defect → binding-implementer. Native behavior disagreement →
protocol-test-engineer/analyst via the orchestrator. No binding role may rewrite
analysis or canonical vectors.
