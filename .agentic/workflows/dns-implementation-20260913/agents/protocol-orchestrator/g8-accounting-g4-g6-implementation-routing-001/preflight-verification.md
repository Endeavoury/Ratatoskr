# G8 accounting corrective G4/G6 verification

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` / Ratatoskr DNS |
| Role | `protocol-orchestrator` |
| Status | `APPROVED` administratively for the narrowly scoped corrective G4 synthesis and renewed G6 only |
| Verified repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / remote | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Verified HEAD and origin ref | `685242c528517ec2e704c28a1f520ed4c1b76672` |
| Requested implementation scope | `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, `src/protocols/dns/dns_client.c` only |

## Independent immutable inputs

1. Accounting design candidate: `git:4a37fc293c842b206190bad369e2a3e1ad00008c`.
   - Subject artifacts are the API design, context-destroy decision, handoff, and completion report.
   - Candidate diff is limited to the candidate workspace and the named destination handoff resolution; it adds no public ABI/API change.
   - Design SHA-256 observed from the checked worktree: `45206e6aaaaab1323af010eabe17e9ea2e19acac4c61ab5c73a8b21bd4c0b331` for `api-design.md`.
2. Fresh binding-lifetime review delivery: `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`.
   - Scoped disposition is `APPROVED`; subject is exactly `4a37fc293c842b206190bad369e2a3e1ad00008c`.
   - Declared independent reviewer identity: `binding-api-designer/g8-accounting-lifetime-review-001`, distinct from design author `protocol-api-designer/g8-accounting-design-001`.
   - Review SHA-256 observed: `a1add54587bd3ad5823e5999b92413afa802065e570eb8fdf74bf2def472044f`.
3. Fresh compatibility review-002 delivery: `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`.
   - Scoped disposition is `APPROVED`; subject is exactly `4a37fc293c842b206190bad369e2a3e1ad00008c`, baseline exactly `git:e804eb46f9aca14c4be6152e154a0b518f34c7fe`, and supporting lifetime delivery exactly `e04fefa07e72427adc7ecbab339fef96bc04b3b7`.
   - Declared fresh reviewer session `20260920_095053_0c67b1` is distinct from both the design author and binding-lifetime reviewer. The record states actual `openai-codex/gpt-5.6-sol` / `medium`.
   - Review SHA-256 observed: `de4b368529cf6dfa3e59bed86b6f4c0e3e8401ad4bb0efa0c0ba19b7ff1b9eda`.
   - Its delivery changed only its three reviewer-owned artifacts plus the named binding-lifetime handoff Resolution section. `git diff --check` is recorded as passing.

Wrapper-mediated checks confirm all three exact objects exist; design and binding-review commits are ancestors of review delivery, and review delivery is an ancestor of current verified `HEAD`/origin ref. The requested phrase “currently local HEAD and exact origin ref” is not literally true: `aa2ebfaa…` is the immutable review delivery, while both local HEAD and origin are the later documentation-only commit `685242c…` (one `completion-report.md` addition). No reviewed input was altered by that descendant.

## ABI and boundary verification

Wrapper `ls-tree` shows byte-identical baseline/subject public blobs:

- `include/ratatoskr/context.h`: `ef8b574154ff8f21ba81b3b4d3bcae5c9c2f6935`
- `include/ratatoskr/dns.h`: `6a8ea8fb6bac8e4397d72efcbff1950cb186d8ad`
- `include/ratatoskr/version.h`: `72f3097b3d9138dfce075db4c5f476866ba19a41`
- `docs/abi.md`: `b071414c8e2f8f079e3f46dc7c70ee5531a9bb71`
- `docs/migration-dotnet.md`: `dfff11cdfc2ce56d03deddf1a50d5ba2ef9492f8`

No public header, public ABI layout, symbol, calling convention, version, CMake, test, parser, transport, binding, vector, documentation, or workflow-state write is authorized to the corrective leaf. The approved design itself explicitly limits the new realization to the four private production paths above, the leaf’s own workspace, and named destination Resolution sections only.

## G4 synthesis and renewed G6

The two designated independent scoped reviews approve the same immutable design with required ownership/lifetime and ABI compatibility facts. Therefore this orchestrator administratively synthesizes corrective G4 as `APPROVED` for this design only and renews G6 as `APPROVED` for a single fresh c-protocol-implementer assignment limited to the exact four private paths.

The leaf must implement: context-owned request registry/counters; detach (never free) caller-owned requests before context storage is freed; release outstanding/TCP slots exactly once across all terminal/destruction paths; retain safe request inspection, COMPLETE take-result, and destruction after detachment. The leaf must not perform or route G7, G8, G9, bindings, docs, or any later work.

## Operational checks and limits

- Required wrapper exists and is executable: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`.
- Workspace profile confirms `delegation.max_spawn_depth: 2` and `delegation.orchestrator_enabled: true`.
- Process inspection found only this parent/session and the workspace scheduler; no live leaf/scheduler execution matching `review-002`.
- Existing modified `workflow-state.yaml` and pre-existing untracked agent workspaces are preserved. They are excluded from this routing artifact commit.
- No quota/rate error was observed.

## Next authorized action

Dispatch exactly one fresh `c-protocol-implementer/g8-accounting-implementation-001` leaf using the adjacent complete packet. Its completion may be accepted only as `READY_FOR_REVIEW`; no reviewer or later stage is authorized in this assignment.
