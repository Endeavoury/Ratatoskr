# Handoff — DNS G9 resource-policy decision required

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` |
| Workflow ID / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Target | `protocol/dns` record-target resource growth |
| Owner role | `protocol-orchestrator/g9-resource-policy-escalation-001` |
| Status | `BLOCKED` |
| Revision | Local-only artifact at observed baseline `git:510d1a3617e0b66ed98b0980f277de689b5ae508` |
| Source artifacts | Listed below, including the verified API-designer assessment and G9 execution evidence |
| Assumptions | `-rss_limit_mb=1024` is mandatory and remains unchanged. G7 and G8 are independently `APPROVED`. |
| Open questions | Maintainer/product must select the concrete DNS resource default/hard-limit policy, or explicitly decide that no numeric-default change is needed. |
| Limitations | Coordination only: no root cause, private corrective path, implementation, review, fuzz rerun, or technical gate result is asserted. |

## Routing

- ID / workflow / stage: `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` / `dns-implementation-20260913` / G9 blocker return.
- Source role and assignment: `protocol-orchestrator/g9-resource-policy-escalation-001`.
- Destination owner: maintainer/product owner, returned through `protocol-orchestrator`.
- Target protocol/component: DNS record-target parser resource policy.
- Reason: a mandatory G9 resource failure exists, while the approved resource contract deliberately leaves numeric defaults unresolved and no evidence identifies a concrete private corrective path.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts

1. `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md` at tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`: `ratos_fuzz_dns_record` returned 71 after 21.236172719858587 seconds, with `ru_maxrss` 1,675,884 KiB and libFuzzer reporting `used: 1636Mb; limit: 1024Mb`.
2. `agents/protocol-api-designer/g9-record-resource-assessment-001/api-design.md`, decision, and return handoff at observed baseline `git:510d1a3617e0b66ed98b0980f277de689b5ae508`: assessment is `BLOCKED`, authorizes no private path, and preserves the fixed G9 budget.
3. `agents/protocol-api-designer/g4-compatibility-remediation-001/handoffs/maintainer-resource-policy.md`: symbolic contract explicitly leaves documented DNS resource values/release policy to maintainer/product input.
4. `agents/protocol-orchestrator/g8-accounting-g4-g6-implementation-routing-001/preflight-verification.md`: current G6 is revision- and path-bound and excludes parser work.
5. `workflow-state.yaml`: G7 and G8 are `APPROVED`; workflow, fuzzing, and G9 are `BLOCKED`.

## Specific problem or question

What documented DNS default/hard-limit policy applies to UDP/TCP frame bytes, RR/count work, name expansion bytes, compression-pointer traversals, typed-field/string bytes, and outstanding requests/connections? If the maintainer/product decision is that no numeric-default change is needed for this issue, record that decision explicitly.

The protocol orchestrator cannot select product policy. The G9 result proves the mandatory budget failure only; it does not establish an allocation/lifetime root cause or authorize a private path. Current G6 cannot be expanded administratively.

## Requested action

Record a maintainer/product resource-policy decision that either:

1. selects the applicable documented concrete defaults/hard limits and any release-policy constraints; or
2. explicitly determines that no numeric-default policy change is needed for the observed G9 issue.

Return the decision to `protocol-orchestrator`. If it creates a design change, the responsible design owner must produce a revision-bound candidate and identify exact private paths. The orchestrator must then perform a future fresh G6 authority assessment against that actual candidate, applicable renewed approvals, and the unchanged `-rss_limit_mb=1024` requirement.

Do not treat this handoff as authorization for implementation, review, fuzz rerun, security work, bindings, documentation, configuration, public ABI change, or a G9 pass.

## Acceptance criteria

- A durable maintainer/product decision answers the numeric-default/hard-limit question or explicitly records that no numeric-default change is needed.
- Any resulting design candidate is owned by the responsible design role, revision-bound, and identifies exact private paths without inferring them from the RSS result alone.
- The protocol orchestrator verifies the returned artifact before any state transition and performs a fresh G6 authority assessment before any corrective implementation dispatch.
- G9 remains `BLOCKED` until independently accepted G9 evidence exists under the unchanged 1024 MiB limit.

## Resolution (destination owner)

Pending maintainer/product decision.

## Closure (orchestrator after verification)

Pending.