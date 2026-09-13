# Protocol lifecycle

“Add STUN” is an example of routing, not an implementation included in this framework.
The orchestrator records an ADD_PROTOCOL request with the intended role/version and
supported surface, then creates a dependency-aware stage plan.

| Stage owner | Owned output | Transition owned by orchestrator |
| --- | --- | --- |
| protocol-researcher | Official specification inventory and discovery closure | G1 → analyst |
| protocol-analyst | Requirement, wire/framing/state/error/security analysis | G2 → modeler |
| protocol-modeler | Language-independent semantic model | G3 → native API designer |
| protocol-api-designer | Native API design, ownership and ABI evolution | G4 → vector designer |
| vector-designer | Canonical language-independent byte/event expectations | G5, then G6 → C implementer |
| c-protocol-implementer | Future scoped native implementation and trace report | → independent test engineer for G7 |
| protocol-test-engineer | Harness/evidence against approved vectors and native review | G7 → security reviewer |
| security-reviewer | Adversarial review and verified remediation disposition | G8 → fuzz engineer |
| fuzz-engineer | Strategy, future harness/campaign evidence and regressions | G9 → binding design/exposure |
| binding-api-designer | New/changed mappings, if existing approved mapping is insufficient | BINDING_DESIGN → binding implementer |
| binding-implementer | Required binding exposure/adapters and packaging evidence | G10 → conformance reviewer |
| conformance-reviewer | Cross-surface behavior evidence | G11 → documentation writer |
| documentation-writer | Usage, lifecycle, errors, limitations and migration docs | G13 → compatibility reviewer |
| compatibility-reviewer | ABI/API/behavior and versioning disposition | G12 → final reviewer |
| final-reviewer | Independent complete evidence audit | G14 → orchestrator closes state |

Roles author their outputs and report readiness; designated gate reviewers approve
them. Every return travels through a handoff with specific evidence. The orchestrator
alone changes shared state. The full research/design review completes before native
implementation is delegated. User requests for planning stop at planning artifacts.

## Changes, transports and extensions

EXTEND_PROTOCOL starts with baseline artifacts and a changed-requirements analysis.
Researcher verifies changed sources; analyst identifies affected model/API/vector
areas; the orchestrator reuses only demonstrably unaffected approvals. Do not restart
all protocols or treat existing behavior as automatically conformant.

ADD_TRANSPORT describes delivery, framing, connection lifecycle and how components
compose. ADD_PROTOCOL_EXTENSION describes capability dependencies, versioning,
negotiation, downgrade/unknown-extension behavior and backward compatibility. Each
uses the same owners/gates for affected artifacts. If a dependency is absent, create
a linked work item; do not conceal a second implementation inside a binding.

Stateful protocols require scenario vectors for incremental reads, consumed bytes,
need-more-input, peer/local events, session transitions, logical timers, retries,
multiplexing and shutdown. Limits belong in analysis and API configuration where
observable, not just defensive code. Errors must define whether a connection/session
can continue and what resources remain owned.

Bindings are selected by declared exposure scope and capability availability, not a
hardcoded language list. A release may explicitly defer a binding, but G0/G10/G11 and
public limitations must record that gap; “all bindings conform” cannot exclude an
in-scope binding silently.
