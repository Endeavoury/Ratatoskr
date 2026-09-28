# Completion report: G8 accounting-design routing

## ROLE

`protocol-orchestrator/g8-accounting-design-routing-001`

## STATUS

`COMPLETE` for the single design-routing stage. The returned design candidate is `READY_FOR_REVIEW`; no technical gate advanced.

## SUMMARY

Verified no live specialist execution, then routed exactly one independent `protocol-api-designer` leaf at Sol/medium. The leaf delivered a private DNS request-accounting design at `git:4a37fc293c842b206190bad369e2a3e1ad00008c`, which equals the exact remote delivery ref. Its six-file delta is confined to the assigned design workspace and the permitted Resolution section of the implementation authority blocker. It proposes context-owned request registry/counters, exact-once capacity release, safe context teardown with caller-owned handles, and a later four-private-file implementation scope. It did not alter production code, public headers, tests, vectors, fuzzing, prior reviews, or workflow-root files.

The candidate requires fresh independent binding-lifetime and compatibility reviews. Accordingly, native API design is `READY_FOR_REVIEW`; G4 and G6 are `CHANGES_REQUESTED`/stale for the new corrective candidate. G7/G8 remain unapproved for any later implementation and G9/later stages remain unstarted.

## ARTIFACTS CREATED

- `README.md`
- `delegations/protocol-api-designer-g8-accounting-design-001.md`
- `completion-report.md`

## ARTIFACTS MODIFIED

- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` — routing/status only.

## DECISIONS MADE

- Routed the G8-002 ownership/lifetime gap to `protocol-api-designer` before any further implementation.
- Recorded the new design candidate as requiring fresh scoped binding-lifetime and compatibility review; no inherited G4/G6 approval covers its private core-path expansion.

## OPEN QUESTIONS

None for routing. Independent review must determine whether the candidate safely preserves opaque-handle ownership and ABI compatibility.

## BLOCKERS

`DNS-G8-001` and `DNS-G8-002` remain unresolved. Implementation is blocked pending the designated independent reviews and renewed G6 authority.

## HANDOFF REQUIRED

`protocol-orchestrator` must next route the designated independent design review(s), without dispatching implementation first.

## RECOMMENDED NEXT ROLE

`binding-api-designer` for the scoped independent lifetime/representability review, followed separately by `compatibility-reviewer`.

## VERIFIED EVIDENCE

- Wrapper remote readback: local and `origin/hermes/dns-implementation-20260913` both `4a37fc293c842b206190bad369e2a3e1ad00008c`.
- `git diff --check 2fee7ea..4a37fc2`: passed.
- Exact leaf delta contains only the six permitted paths; unrelated pre-existing untracked workspaces remain untracked and untouched.
- Leaf recorded its Sol runtime route and no build/test/race run because those actions were outside its design-only scope.