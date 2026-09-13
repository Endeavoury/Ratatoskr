# Architecture and repository baseline

## Target architecture

```text
Protocol definitions, requirements, models and canonical vectors
                            |
                            v
                 Native C implementation
                            |
                            v
                     Stable native ABI
                            |
        +--------+------+---+----+--------+--------+-------+
        Java     C++   Rust     .NET    Python     Go    Swift ...
```

The maintenance target is N native protocol implementations + M binding
implementations. Bindings still need exposure/mapping work for new capabilities,
but never N × M independent codecs or state machines. CLI and bindings are peer ABI
consumers. A binding must not call internal headers or shell out to the CLI.

## Inspected repository

Snapshot inspected 2026-09-13; recheck paths and capabilities for each work item.

| Area | Existing location and convention |
| --- | --- |
| Native runtime | `src/core/`; private `core_internal.h` |
| Protocol module | `src/protocols/dns/`; private `dns_internal.h`, separate builder/parser/client/transports |
| Public API | `include/ratatoskr/`; `ratos_*` symbols, opaque ownership, fixed-width ABI fields |
| CLI | `cli/commands/`, including command registration; presentation only |
| Bindings | `bindings/{c,cpp,dotnet,java,kotlin,python,rust,go,swift,node,php,ruby,dart,lua}/` |
| Native verification | `tests/core/`, `tests/dns/`, `tests/integration/`, `tests/fixtures/dns/` |
| Fuzzing | `fuzz/dns/` |
| Build | C11, CMake 3.20+, per-component CMake files, CTest, `dev`/`release`/`sanitize` presets |
| Packaging | `packaging/`, `cmake/`, binding-local manifests; existing release tools in `tools/` |
| CI | `.github/workflows/ci.yml`, `bindings.yml`, `package.yml` |
| Existing documentation | `docs/architecture.md`, `repository-layout.md`, `abi.md`, `contributing.md`, protocol and binding guides |
| Legacy compatibility | `DNS.Client*` directories and managed compatibility surface; not a second authority for new protocols |

The binding list describes directories, not guaranteed feature parity. Determine
actual capabilities from code, ABI and execution evidence. At inspection there was
no project-local `AGENTS.md`, `CLAUDE.md`, or Hermes framework. The parent workspace
had general Git/build conventions. The earlier validation plan was already an
uncommitted documentation change and has been preserved.

## Vocabulary

| Concept | Meaning and boundary |
| --- | --- |
| Protocol | Rules for peers, messages, semantics, roles and interaction |
| Codec | Encoding/decoding portion of a protocol; not the whole protocol |
| Transport | Delivery/framing/session mechanism used by a protocol |
| State machine | Valid states and transitions driven by messages, local actions, timers and failures |
| Binding | Language adapter over supported public native functionality |
| ABI | Binary calling, type, lifetime, error and version contract across the native boundary |
| Test vector | Canonical inputs/events and expected outcomes linked to requirements |
| Conformance | Evidence that implementation/exposure meets a defined requirement profile |
| Extension | Optional or versioned behavior with dependencies and negotiation/unknown-value rules |

DNS includes a codec; UDP and TCP are transports. TLS can serve as a secure transport
layer and is itself a security protocol. DoH composes DNS and HTTP behavior; DoQ
involves DNS and QUIC. These are examples, not schema enums or assumed work targets.

Model dependencies using stable component IDs, required capabilities, versions,
edge purposes, and negotiation rules. Distinguish implementation dependencies from
runtime peer interactions. Orchestrate prerequisites in dependency order; identify
cycles and resolve the decomposition explicitly rather than scheduling a deadlock.
Composition needs its own framing, errors, state, security, and interoperability
analysis; reusing a codec does not prove the composition correct.

## Stateful and incremental capabilities

Never assume a complete-buffer `parse` API is sufficient. Analysis/model/design and
vectors can describe stream consumption, need-more-input, connections, sessions,
handshakes, multiplexed stream IDs, timers, retransmission, shutdown and cancellation.
Record client/server roles, concurrent activity, ordering, input consumption, output
events, deadlines, state after errors, and resource budgets. Use logical time in
canonical event sequences. A timeout is an event, not necessarily a response packet.

Models use semantic domains, ranges and lifetimes, not Java classes, Rust structs,
C# records, or private C layouts. Native API design later chooses ABI representation;
binding design maps that ABI without changing protocol meaning.

## Instruction architecture

`AGENTS.md` supplies concise common context. `docs/agentic/` supplies shared contracts.
`.hermes/skills/` supplies one focused identity per role. `.agentic/templates/` and
`.agentic/schemas/` define durable work records. `.agentic/workflows/` is the proposed
home of future instantiated work, not a queue or runtime. Git preserves history.
