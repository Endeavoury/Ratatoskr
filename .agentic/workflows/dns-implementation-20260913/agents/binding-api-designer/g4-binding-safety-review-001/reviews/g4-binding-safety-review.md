# G4 binding-safety review — DNS native API candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g4-binding-safety-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `binding-api-designer` (designated independent G4 binding-safety reviewer) |
| Status | `CHANGES_REQUESTED` |
| Revision | Reviewer record at repository HEAD `c2ab2aa30496edf70163b46b9572c0b155488eb4`; created in the assigned reviewer workspace only. |
| Source artifacts | Candidate and completion at Git `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a`; approved G3 review at Git `865fa190ee19e041c5ddfab8279b49829baaa240`; ABI baseline at Git `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`. |
| Assumptions | Review is limited to the proposed UDP-first, one-request native surface. No language binding target is selected or reviewed. |
| Open questions | The candidate must resolve the binding-visible scalar/struct contracts identified below before safe mapping can be approved. |
| Limitations | Artifact and header-baseline review only. No ABI/header, implementation, vector, binding, documentation, workflow-state, or compatibility review was performed. |

## Gate identity

- **Gate / applicability:** G4 / applicable; this is the binding-safety half only. A separate compatibility-reviewer disposition remains mandatory and unperformed.
- **Workflow stage:** `native_api_design`.
- **Candidate author:** `protocol-api-designer / g4-api-design-001` (`deleg_8857e307/task-0`, as recorded by workflow state); candidate author identity in delivery commit: `protocol-api-designer <protocol-api-designer@roygerritse.nl>`.
- **Reviewer identity:** `binding-api-designer / g4-binding-safety-review-001`, fresh leaf reviewer in this session.
- **Independence declaration:** I did not author or edit `g4-api-design-001`, its API candidate, its completion report, the approved G3 review, or any native design truth. I wrote only the assigned reviewer artifacts. I did not perform compatibility review, vector design, implementation, or remediation.
- **Review date:** 2026-09-14.
- **Reviewer model/runtime evidence:** requested `gpt-5.6-terra` / medium; observed runtime `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry unknown.

## Exact input evidence

| Input | Required revision | Observed verification |
| --- | --- | --- |
| API candidate | `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a` | Current path equals that Git revision; SHA-256 `4e8c33beecf48a2a55d83183de7dd100c934fa874661a97ae7e25f67277d597d`; Git blob `72789f0e9270a4b42a40fb4bf3f532734bb7edea`. |
| Candidate completion report | `1b3fe06b3b4c5b7ffa0db0df0199dd45ac0dad2a` | Current path equals that Git revision; SHA-256 `5c94f5bb6456eb68faaf84878da51b8aa02a3023d6cad3e271c1b9eb17f76771`; Git blob `058a6864ee0be2e15476cd0c5f0a747b423004b3`. |
| Approved G3 review | `865fa190ee19e041c5ddfab8279b49829baaa240` | Read as approved semantic prerequisite; it records the approved `f267454...` model and review boundary. |
| ABI baseline | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | Current `include/ratatoskr/` and `docs/abi.md` equal the stated baseline. `docs/abi.md` SHA-256 `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b`; per-header digests were recorded during review. |

## Evidence and checks

| Binding-safety criterion | Evidence | Observed result | Limitation |
| --- | --- | --- | --- |
| Opaque ownership and destruction | Candidate §§2–3, APIs 002 and 007–009; ABI baseline ownership contract | **Pass.** `ratos_dns_request` and `ratos_dns_result` are opaque; successful start/take ownership, borrowed result views, NULL-tolerant destroy, and no `free` are representable in FFI wrappers. Nonzero DNS RCODE remains a completed owned result rather than a foreign exception/error. | The resulting header is not yet available for compile-time binding validation. |
| Pointer, length, and output validity | Candidate §§2–4 | **Changes requested — F-BIND-001.** The proposal says inputs are borrowed and outputs initialized, but does not define the concrete public layouts and scalar representations of `ratos_dns_event`, `ratos_dns_endpoint`, `ratos_dns_request_state`, `ratos_dns_transport_failure`, or the DNS error-class output/accessor it relies on. In particular, `event` is described as an enum and as an object with scalar fields, while neither its type/layout nor the valid fields on each return path are specified. A binding cannot allocate, initialize, inspect, or preserve ABI-safe layout for these required values. | This finding does not prescribe a replacement layout. |
| Text and input representability | Candidate APIs 002–004 and §3 | **Changes requested — F-BIND-002.** `name` is a `const char *`, but the candidate gives no explicit C-string/NUL or text encoding contract, whereas the new endpoint is said to carry address-byte pointer inputs without a defined public layout. A language adapter cannot determine how to marshal name text or endpoint address/length storage safely and consistently. | Existing synchronous DNS naming behavior is baseline context, not an implicit specification for a new API. |
| Events and errors | Candidate §§3–4 and §8; baseline `ratos_error` | **Changes requested — F-BIND-001.** Event/error operation results are not fully representable until their fixed-width types, fields, initialization, and observation rules are declared. The candidate correctly avoids treating a valid RCODE as `ratos_error`, but refers to a distinct DNS error-class accessor/event field without naming its operation or contract. | Compatibility impact of any added `ratos_error` is intentionally left to the required compatibility review and was not assessed here. |
| Callback, threading, cancellation, and reentrancy | Candidate §6 and API 006/009 | **Pass with explicit adapter constraint.** No callback removes foreign-runtime callback lifetime and thread-attachment hazards. Single-driver ownership and explicit rejection of races are representable if bindings serialize mutable operations and do not expose concurrent cancel/destroy as supported. | Thread safety of shared `ratos_context` remains unspecified pending separate documentation/contract evidence; bindings must not claim it. |
| Incremental TCP consumption | Candidate API 004 and §5 | **Pass conceptually.** `bytes_len` plus required `out_consumed`, explicit prefix/frame limit, and preserved suffix enable an adapter to retain and resubmit unconsumed bytes without wire parsing. | F-BIND-001 still prevents an adapter from reading the required event/state result safely. |
| Capability and deferred-feature signaling | Candidate §1 and §8 | **Pass conceptually.** Fixed-width `uint64_t` capability discovery and unsupported returns distinguish optional behavior and explicitly defer callbacks, EDNS, TCP reuse/pipelining, retries, and bindings. | The same missing error/event definitions prevent complete runtime classification mapping. |
| No independent wire parsing | Candidate APIs 003–004, §5; `AGENTS.md`; `BINDING_LIFECYCLE.md` | **Pass conceptually.** Bindings can feed native datagrams/bytes, use native consumption/event/state, and obtain native results; the candidate does not require a binding parser or a language-specific DNS oracle. | No binding or vector adapter is in scope for execution. |

## Findings and required return

- **F-BIND-001 (blocking):** Specify each new binding-visible event/state/failure/error-class type and operation at the native API-design level: ABI-safe fixed-width representation, concrete public struct fields (if any), `struct_size`/reserved-field rules where applicable, required initialization, and which fields are valid for every documented return/event path. Include the named operation/accessor that exposes the DNS error class. This is required for FFI allocation, initialization, decoding, and safe error handling.
- **F-BIND-002 (blocking):** Specify the new `name` text/C-string contract and the full endpoint/address byte layout and pointer/length validity rules, including nullability and lifetime, sufficiently for a binding to marshal without guessing or independently parsing protocol data.

**Disposition: `CHANGES_REQUESTED`.** The candidate has a sound opaque-lifetime, callback-free, incremental-consumption, capability-signaling direction, but F-BIND-001 and F-BIND-002 leave mandatory boundary types and text/endpoint marshaling unrepresentable for bindings. Return through `protocol-orchestrator` to `protocol-api-designer`; re-review requires a revised candidate at a new immutable delivery revision addressing both findings. This record is not a G4 pass and does not decide ABI compatibility.
