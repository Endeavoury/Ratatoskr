# Handoff — G9 resource-policy prerequisite remains unresolved

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-resource-policy-resumption-blocker-007` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Target | `protocol/dns` record-target resource policy |
| Owner role | `protocol-orchestrator/g9-resumption-007` |
| Status | `BLOCKED` |
| Revision | pre-delivery `git:f6d703bb8e7d8fbba88e722abb6e58e9c5c7b7c2` |
| Source artifacts | current state, current toolchain preflight, `DNS-G9-RESOURCE-POLICY-MAINTAINER-001` |
| Assumptions | `-rss_limit_mb=1024` remains mandatory and unchanged. |
| Limitations | No technical finding, corrective path, implementation, campaign, or G9 approval is asserted. |

## Routing

- ID / workflow / stage: `dns-g9-resource-policy-resumption-blocker-007` / `dns-implementation-20260913` / G9.
- Source role and assignment: `protocol-orchestrator/g9-resumption-007`.
- Destination role: `maintainer` / product owner, returned through `protocol-orchestrator`.
- Reason: the LLVM19 execution toolchain is available, but the mandatory record-target resource failure remains unresolved under the fixed 1024 MiB G9 budget.
- Blocking: true.
- Status: `BLOCKED`.

## Source evidence

1. `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md` records `ratos_fuzz_dns_record` exit 71, 1,675,884 KiB maximum RSS, and `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`.
2. `agents/protocol-orchestrator/g9-resource-policy-escalation-001/handoffs/dns-g9-resource-policy-to-maintainer-001.md` is still `BLOCKED`, with its destination resolution `Pending maintainer/product decision.`
3. `agents/protocol-orchestrator/g9-resumption-013/preflight-verification.md` records that no durable numeric decision, revision-bound corrective candidate, exact authorized private path, or fresh G6 authority assessment exists.
4. This assignment verified CMake 3.31.6, LLVM/Clang 19.1.7, Ninja, and matching compiler-rt libFuzzer/ASan/UBSan archives at `git:f6d703bb8e7d8fbba88e722abb6e58e9c5c7b7c2`; toolchain availability does not resolve the resource-policy blocker.

## Requested action

Record a durable maintainer/product resolution for `DNS-G9-RESOURCE-POLICY-MAINTAINER-001`: select applicable documented numeric defaults/hard limits, or explicitly decide that no numeric-default policy change is needed. If a design change follows, its responsible owner must deliver a revision-bound candidate and exact private paths.

## Acceptance criteria

- A durable maintainer/product decision answers the numeric-default/hard-limit question or explicitly records no numeric-default change.
- Any required candidate is owned by the responsible design role, revision-bound, and names exact private paths.
- A protocol-orchestrator independently verifies the return and records fresh G6 authority before any corrective dispatch or fresh fuzz-engineer campaign.
- G9 stays `BLOCKED` until independent G9 evidence is accepted under the unchanged 1024 MiB campaign limit.

## Resolution (destination role)

Pending maintainer/product decision.

## Closure (orchestrator after verification)

Pending.
