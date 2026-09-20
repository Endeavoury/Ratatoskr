# Gate review: G8 DNS accounting corrective candidate

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g8-accounting-security-rereview-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` accounting corrective candidate |
| Owner role | `security-reviewer/g8-accounting-security-rereview-001` |
| Status | `CHANGES_REQUESTED` |
| Revision | Candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; G7 delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd` |
| Source artifacts | Exact inputs and findings in `../security-review.md` |
| Assumptions | Same-context mutation/destruction is externally serialized; distinct contexts remain concurrent. |
| Open questions | None; one blocking implementation return route remains. |
| Limitations | Static exact-revision review and strict compilation; dynamic accounting evidence reviewed from G7; no usable TSan, CMake/CTest, G9 fuzzing, new probes, or dynamic socket-truncation reproduction. |

## Gate identity

- Gate ID and applicability: `G8`, applicable hostile-input, resource, concurrency, and lifetime review.
- Workflow stage: `security`.
- Required inputs: candidate `c38a7faf937571de5f0eb64885b8e5c61e5b9175`, parent `62a2dda24194020904a75e1edce9b3d74fbd70a4`, G7 delivery `8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`, prior G8 delivery `844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`, accounting design `4a37fc293c842b206190bad369e2a3e1ad00008c`, binding-lifetime review `e04fefa07e72427adc7ecbab339fef96bc04b3b7`, and compatibility review `aa2ebfaa8379d74a539ef95caf02d925f799d229`.
- Candidate author: `c-protocol-implementer/g8-accounting-implementation-001`.
- G7 reviewer: fresh `protocol-test-engineer/g7-accounting-native-verification-001`, delivery `8c1383e...`, disposition `APPROVED` for `c38a7fa` only.
- Reviewer: fresh `security-reviewer/g8-accounting-security-rereview-001`, Hermes session `20260920_145846_deae3c`.
- Independence declaration: this reviewer authored none of the candidate, design, prerequisite reviews, G7 evidence, prior G8 findings, tests, or workflow state and wrote only this assigned reviewer workspace.
- Review date: `2026-09-20T15:04:44+02:00`.
- Actual model/effort and runtime evidence: live parent command line explicitly contains `--provider openai-codex --model gpt-5.6-sol --reasoning high`; current session ID is `20260920_145846_deae3c`. Actual route is `openai-codex/gpt-5.6-sol`, reasoning `high`. Persistent profile Terra/unset values are overridden for this invocation. Usage/cost telemetry is `unknown`.

## Evidence and checks

| Pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Candidate and G7 evidence match exactly | Candidate parent/path check; ancestry to G7 `8c1383e...`; packet verification | PASS: G7 reviews exact candidate `c38a7fa`; required candidate and reviewer commits resolve and are ancestral | G7 scope is accounting/lifecycle and does not close prior parser/UDP finding DNS-G8-001 |
| Authorized candidate boundary and source integrity | `git diff --name-only` and `git diff --check 62a2dda... c38a7fa`; candidate-to-HEAD scoped diff | PASS: four authorized production paths plus three candidate workspace artifacts; no post-candidate source/header/test delta | Unrelated pre-existing untracked workspaces preserved |
| Malformed lengths/allocation remain bounded | Exact candidate parser, builder, TCP transport, result cleanup | PASS for checked memory bounds: cursor/RDLENGTH/frame checks and partial-result cleanup are present | Not a proof for all hostile inputs; G9 not run |
| Configured limits and resource disposition are complete | `../security-review.md`, `dns_parser.c:97-99,374-376,418-420`, `dns_client.c:75-80`, `dns_transport_udp.c:91-100` | **FAIL:** DNS-G8-001 remains unchanged and reachable | No new dynamic boundary probes were authorized |
| Outstanding/TCP admission and terminal no-result accounting | Candidate `dns_client.c`; exact-candidate G7 lifecycle harness and ASan/UBSan evidence | PASS: start/fallback admission, cap reuse, terminal cleanup, and no-result behavior passed | ThreadSanitizer runtime unavailable |
| Global tracking/cross-context lifecycle is safe | Candidate private context/request fields and detach path; G7 two-thread distinct-context stress | PASS: no process-global request list; disjoint per-context state; safe detach under same-context serialization | Normal/ASan/UBSan evidence, not TSan proof |
| Teardown and detached handles are safe | `context.c`, `dns_client.c`; G7 pending/failed/COMPLETE detach and post-detach checks | PASS: pending cancellation, terminal preservation, COMPLETE take-result, invalid detached mutation, and safe destroy | Concurrent same-context destroy/use is explicitly unsupported |
| Candidate compiles under strict C11 warnings | Reviewer command recorded in `../security-review.md` | PASS | Syntax compilation only; CMake/CTest unavailable to G7 |
| No unresolved blocking security finding remains | `../security-review.md`; handoff `../handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md` | **FAIL:** blocking DNS-G8-001 remains | G9 intentionally not routed or assessed |

## Disposition

**CHANGES_REQUESTED.** Candidate `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` resolves prior high-severity `DNS-G8-002` by replacing global tracking with context-owned accounting and safe detachment. It does not modify the parser or synchronous UDP transport, so prior blocking `DNS-G8-001` remains unresolved across record-owner resource-error propagation, hard/configured guard ordering, acceptance of unenforceable traversal values, and oversized synchronous UDP datagram detection.

Responsible owner: `c-protocol-implementer` through `protocol-orchestrator`. Required action and re-review criteria are in `../handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`. A new authorized implementation revision, fresh independent G7 evidence, and fresh independent G8 review are required. This record does not change workflow state and does not route G9 or any other stage.