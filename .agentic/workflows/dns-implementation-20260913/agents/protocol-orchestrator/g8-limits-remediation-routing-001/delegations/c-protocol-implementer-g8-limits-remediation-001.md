# Delegated task

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g8-limits-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | local routing artifact; HEAD/origin `9275f66dba3c19440da28ca86bd53777490b3e59` before dispatch |
| Source artifacts | G8 review/handoff at `git:90a02df18522b6c311e236dc03c82583971c7511`; reviewed candidate `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee` |
| Assumptions | Existing public `ratos_dns_limits` fields are the approved contract; no ABI/design change is needed unless inspection proves otherwise. |
| Open questions | Whether existing test assets can evidence every required class is for the independent G7 reviewer/test engineer; do not create or alter tests. |
| Limitations | No absolute executable `git-agent` wrapper was found in `/home/hermes/.local/bin`, `/home/hermes/bin`, `/usr/local/bin`, `/usr/bin`, or `/opt`; no raw-Git commit/push is authorized. |

ACTIVE ROLE: c-protocol-implementer

ROLE: c-protocol-implementer

GOAL: Correct only DNS-G8-001: enforce the already-configured DNS resource limits with finite effective defaults and terminal no-result resource-limit behavior.

SCOPE: Native C implementation remediation only. Do not alter approved requirements, model, API design, canonical vectors, public ABI, test truth, G7/G8 reviews, workflow state, G9 scope, or other roles' artifacts. If an API contract change is required, stop and return a narrow handoff to `protocol-api-designer`; do not make that change.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, c-protocol-implementer row.
- Requested provider/model ID: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: `openai-codex/gpt-5.6-terra`; effort unknown.
- Verification source: parent session metadata; do not infer a configuration change from this packet.
- Context target: 8,000–16,000 task-specific tokens after complete required reading.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction; then record a bounded blocker/handoff.
- Escalation trigger and next model/effort: intricate resource-limit/lifetime or arithmetic defect → Sol/high in a separately configured session; no model switch is implied here.
- Stop/checkpoint condition: missing approved contract, required ABI/design change, conflicting writer, unavailable wrapper for requested delivery, or completed bounded output.

## Target and working directories

- Target: `protocol/dns`, DNS-G8-001 only.
- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/`.
- Workspace owner: this fresh c-protocol-implementer leaf only.
- Shared-file writer / ordering: this leaf is the sole authorized writer for the listed production files; no concurrent writer is authorized. Independent G7 then G8 reviews are mandatory after a new candidate and are not delegated now.

## Workflow / stage / assignment

- Workflow: `dns-implementation-20260913`.
- Current failed gate: G8 `CHANGES_REQUESTED`, finding `DNS-G8-001`.
- Assignment: `g8-limits-remediation-001`.
- Shared state (read-only): `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/c-protocol-implementer/SKILL.md`
3. `docs/agentic/HANDOFFS.md`
4. `docs/agentic/ARTIFACTS.md`
5. `docs/agentic/SECURITY_MODEL.md`
6. `docs/agentic/REVIEW_GATES.md`
7. `docs/agentic/DIRECTORIES.md`
8. `docs/agentic/MODEL_POLICY.md`
9. `docs/contributing.md` and `docs/abi.md`
10. This packet and the current workflow state.

## Required immutable inputs

- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/reviews/g8-security-review.md` at `git:90a02df18522b6c311e236dc03c82583971c7511`, disposition `CHANGES_REQUESTED`.
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/security-review.md` at `git:90a02df18522b6c311e236dc03c82583971c7511`.
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/handoffs/dns-g8-001-configured-limits-enforcement.md` at `git:90a02df18522b6c311e236dc03c82583971c7511`, status `NEEDS_UPSTREAM_CHANGE`.
- Reviewed corrective candidate `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee`; `src/protocols/dns/dns_client.c` digest `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88`.
- G6 and G7 approval records named in workflow-state. The prior G7 approval applies only to the cited candidate and must not be reused as approval of this remediation.

## Files allowed to change

### Production

- `src/protocols/dns/dns_client.c` — validate/canonicalize effective limits, pass them through request/synchronous DNS paths, and retain terminal resource-limit/no-result behavior.
- `src/protocols/dns/dns_parser.c` — enforce effective total-RR, name-expansion, compression-pointer traversal, and typed-field budgets before allocation/iteration/copy/traversal; preserve cleanup semantics.
- `src/protocols/dns/dns_internal.h` — only private declarations/signatures/limit-carrying state necessary for the above two files.
- `src/protocols/dns/dns_transport_udp.c` — only if necessary to apply the configured UDP receive budget before allocation/receive.
- `src/protocols/dns/dns_transport_tcp.c` — only if necessary to apply the configured TCP frame/connection budget before allocation/receive.

### Leaf artifacts

- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/implementation-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/handoffs/dns-g8-001-remediation-to-protocol-orchestrator.md`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-limits-remediation-001/completion-report.md`
- The **Resolution section only** of `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-security-review-001/handoffs/dns-g8-001-configured-limits-enforcement.md`; set it to `READY_FOR_REVIEW` only after the new candidate/report evidence exists. Do not edit any other section.

### Explicit test boundary

- Tests are read-only in this assignment: `tests/dns/dns_g7_native_verification_tests.c`, `tests/integration/dns_g7_native_verification_test.py`, `tests/fixtures/dns/g7-native-verification-fixtures.json`, `tests/CMakeLists.txt`, and all other `tests/` paths.
- You may run existing authorized build/check commands and report exact outcomes. You may not create, modify, weaken, or register tests. A fresh independent `protocol-test-engineer` G7 assignment must supply/review test evidence after this candidate; it is not authority for this leaf to write test artifacts.

## Required behavior and acceptance criteria

1. For every zero-valued public DNS limit field, establish and use a finite effective default; reject incoherent values without changing public contract.
2. Enforce `max_udp_message_bytes`, `max_tcp_frame_bytes`, `max_total_rrs`, `max_name_expansion_bytes`, `max_compression_pointer_traversals`, and `max_typed_field_bytes` before corresponding allocation, iteration, copy, or traversal.
3. Enforce `max_outstanding_requests` and `max_connections`, or stop with a narrow API-design handoff if their approved semantics cannot be realized without a contract decision.
4. Limit excess on request UDP/TCP paths must become terminal `RATOS_DNS_ERROR_CLASS_RESOURCE_LIMIT`, destroy/free partial result/frame state, and expose no result through `ratos_dns_request_take_result`.
5. Do not change public headers, canonical truth, G7/G8 findings/reviews, workflow state, or G9 scope.
6. Produce a new candidate revision, implementation trace, and completion report with exact validation output and limitations.
7. Handoff is `READY_FOR_REVIEW` to protocol-orchestrator, which must route a **fresh independent G7 review first, then a fresh independent G8 re-review**. Neither gate is approved by this work; prior G7/G8 approvals are stale for the new candidate.

## Read-only / forbidden

- `include/ratatoskr/dns.h`, `src/core/`, `src/protocols/dns/dns_builder.c`, `src/protocols/dns/CMakeLists.txt`, all tests, fuzzing, bindings, CLI, docs, build configuration, and all artifacts not named above.
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`.
- All G7/G8 review records and all other roles’ outputs, except the named destination Resolution section.
- All paths outside the explicit allowed set.

## Delivery and handoff

- Do not use raw `git commit` or raw `git push`.
- Before any commit/push, discover an **absolute executable** `git-agent` wrapper. Only that wrapper may commit/push, and only to `HEAD:refs/heads/hermes/dns-implementation-20260913`; then read back `origin/hermes/dns-implementation-20260913`.
- No wrapper was found in the parent preflight. If still absent, record the exact absolute-path discovery result in your report and handoff; leave delivery local-only and do not claim remote delivery.
- Never merge and never push `master`.
- Do not delegate further.

## Stop conditions

Stop and return to protocol-orchestrator if input revisions do not match, an API-design decision is required, a needed path is outside this packet, test authorship is required, the wrapper is unavailable for a requested delivery, or an independent gate is needed. Do not self-approve.
