# Handoff — G9 record resource-policy/design assessment

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-api-designer-handoff-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` record-parser resource growth |
| Owner role | `protocol-api-designer/g9-record-resource-assessment-001` |
| Status | `BLOCKED` |
| Revision | Local-only working-tree handoff at dispatch baseline `git:510d1a3617e0b66ed98b0980f277de689b5ae508` |
| Source artifacts | `api-design.md`; `decisions/dns-g9-record-resource-authority.md`; G9 failure at tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e` |
| Assumptions | `-rss_limit_mb=1024` remains mandatory. |
| Open questions | Concrete default/hard-limit policy and any resulting revision-bound corrective design candidate remain unavailable. |
| Limitations | No root cause, implementation path, implementation, review, or campaign result is asserted. |

## Routing

- ID / workflow / stage: `DNS-G9-RECORD-RESOURCE-AUTHORITY-002` / `dns-implementation-20260913` / G9 blocker return.
- Source role and assignment: `protocol-api-designer/g9-record-resource-assessment-001`.
- Destination role: `protocol-orchestrator`.
- Target protocol/component: DNS record-target resource-policy authority.
- Reason: current approved semantics do not select the concrete default/hard-limit policy needed for a bounded resource-policy correction, and G9 evidence does not identify a causal private path.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts

- `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md` at tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`: record target exited 71 with 1,675,884 KiB `ru_maxrss` and an explicit 1636 MiB versus 1024 MiB libFuzzer failure.
- `agents/protocol-analyst/analysis-001/protocol-analysis.md`, `DNS-REQ-024`: configured bounds and terminal resource-limit semantics are required.
- `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` and `handoffs/maintainer-resource-policy.md`: numeric defaults were deliberately not selected and remain a maintainer/product policy prerequisite for realization requiring concrete values.
- `agents/protocol-orchestrator/g8-accounting-g4-g6-implementation-routing-001/preflight-verification.md`: current G6 authorizes only four accounting paths and excludes parser work.

## Specific problem or question

A mandatory G9 RSS failure exists, but it is not causal evidence for a parser change or any other exact private path. The existing approved resource model is symbolic with unresolved numeric defaults. This role cannot choose product policy, broaden G6, or diagnose native code.

## Requested action

After obtaining the missing maintainer/product resource-policy decision and any resulting responsible-owner design revision, conduct a **future fresh G6 authority assessment** for the exact candidate only. That assessment must verify the candidate’s revision, exact private paths, applicable renewed approvals/gates, and preservation of `-rss_limit_mb=1024`.

Do not route implementation, independent review, fuzz rerun, security work, bindings, documentation, configuration, or later-stage work from this handoff.

## Acceptance criteria

- A recorded resource-policy decision identifies whether concrete default/hard-limit behavior changes are required.
- If a design candidate results, it is revision-bound and names exact private paths without inferring them from the G9 result alone.
- The protocol orchestrator completes a future fresh G6 authority assessment rather than extending current G6 administratively.
- G9 remains `BLOCKED` until separately authorized mandatory evidence is satisfied under the unchanged 1024 MiB budget.

## Resolution (destination role)

Pending protocol-orchestrator action.

## Closure (orchestrator after verification)

Pending.