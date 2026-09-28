# Delegated task

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-record-resource-triage-001-delegation` |
| Root task / workflow / project | `dns-implementation-20260913` / `dns-implementation-20260913` / `Ratatoskr` |
| Target | `protocol/dns`, `ratos_fuzz_dns_record` resource-growth triage |
| Owner role | `protocol-orchestrator/g9-record-resource-triage-routing-001` |
| Status | `IN_PROGRESS` — corrective triage only; G9 remains `BLOCKED` |
| Hierarchy | `workspace-orchestrator → protocol-orchestrator → fuzz-engineer` (leaf; no delegation) |
| Dispatch baseline | local and origin `hermes/dns-implementation-20260913` = `2162d33d8b2db5ace97cff25ada0cd89322aa5d4` |
| Prior campaign evidence | tested `git:90eca1f73f448c86ef455a37cddaa6c9cbbbd12e`; evidence remains immutable |
| Assumptions | Mandatory `-rss_limit_mb=1024` is unchanged; no crash, sanitizer, or timeout was observed. |
| Limitations | This packet grants neither production-code authority nor G9 approval/review authority. |

ACTIVE ROLE: fuzz-engineer

ROLE: fuzz-engineer (single leaf specialist)

GOAL: Inspect the existing record fuzz strategy/harness and the preserved failure evidence. Produce a bounded, evidence-based root-cause/remediation handoff if the cause can be localized to fuzz strategy/harness, otherwise a blocker handoff that states what evidence/authority is missing. Do not diagnose native production code as fact without evidence.

SCOPE: G9 corrective strategy/harness triage only. This is not an execution assignment. Preserve the 1024 MiB RSS budget and all historical campaign facts. Do not run a campaign, retry any target, alter flags/budget, route security review, edit workflow state, or claim G9 approval.

## MODEL AND REASONING

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested provider/model ID: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed dispatch runtime provider/model/effort: `openai-codex/gpt-5.6-terra`; effort telemetry unavailable.
- Verification source: current Hermes runtime metadata and `g9-current-toolchain-preflight-008.md`.
- Context target: 8,000–16,000 tokens; required reading remains complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one bounded inspection/analysis only; no campaign attempts.
- Escalation trigger and next setting: stateful-generation or difficult minimization evidence would ordinarily justify Sol/high, but do not escalate or repeat in this assignment; return a blocker/handoff.
- Stop/checkpoint condition: missing proof of a fuzz-strategy/harness cause, any need for native code/design/maintainer policy, or completion of a bounded handoff.

## TARGET AND DIRECTORIES

- Repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Leaf artifact workspace (leaf owns it exclusively): `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/`
- Report target: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-record-resource-triage-routing-001/` via the leaf handoff and completion paths below.
- Shared-source ordering: no concurrent writer is assigned. A fuzz-path change is permitted only after inspection and only if your written evidence supports a strategy/harness remediation; production source is never permitted.

## READ FIRST

1. `AGENTS.md`
2. `.hermes/skills/fuzz-engineer/SKILL.md`
3. `docs/agentic/HANDOFFS.md`, `docs/agentic/DIRECTORIES.md`, `docs/agentic/ARTIFACTS.md`, `docs/agentic/REVIEW_GATES.md` (G9), `docs/agentic/SECURITY_MODEL.md`, `docs/contributing.md`
4. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-008/verification/g9-current-toolchain-preflight-008.md`
6. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-plan.md`
7. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md`
8. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
9. `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g9-record-resource-assessment-001/api-design.md` (read-only authority boundary)
10. `fuzz/dns/fuzz_dns_record.c`, `fuzz/dns/fuzz_dns_packet.c`, `fuzz/dns/fuzz_dns_name.c`, `fuzz/CMakeLists.txt`, and `fuzz/dns/corpus/` (read before any scoped change).

## REQUIRED INPUTS / BASELINE

- Current workflow state remains `BLOCKED` at G9. Treat all prior untracked `.agentic` artifacts as pre-existing and preserve them.
- The record campaign built under LLVM19, then returned 71 at 21.236172719858587 seconds with `ru_maxrss` 1,675,884 KiB and `ERROR: libFuzzer: out-of-memory (used: 1636Mb; limit: 1024Mb)`.
- Packet and name target runs were clean; no crash, ASan, UBSan, or timeout was observed. The record OOM artifact digest was `23b56d8f1807e20c6a37be929283eaf0ed81d38cd5c7e9609d49b05840996a38` and the ephemeral artifact was removed.
- Existing design assessment is BLOCKED: it does not authorize production/parser changes or establish an allocation/lifetime cause. It explicitly preserves the mandatory 1024 MiB cap.

## FILES/DIRECTORIES ALLOWED TO CHANGE

1. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/README.md`
2. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/fuzz-plan.md` — triage/root-cause or remediation proposal only; not a new campaign plan.
3. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/handoffs/g9-record-resource-triage-to-protocol-orchestrator.md` — required root-cause/remediation or blocker handoff.
4. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/completion-report.md` — required standard completion report.
5. `fuzz/dns/fuzz_dns_record.c` — only if inspection supplies evidence for a fuzz-strategy/harness-only correction; document the exact rationale and do not execute it. No other `fuzz/` path is authorized.

## READ-ONLY / FORBIDDEN

- `workflow-state.yaml`, request, manifest, every prior agent workspace, all gate records, canonical vectors, analysis/model/API artifacts, production `src/`, public `include/`, tests, bindings, docs, root CMake, `.github/`, and all paths outside the explicit allowed list.
- Do not modify `fuzz/CMakeLists.txt`, corpus files, packet/name fuzzers, CMake flags, toolchain selection, `-rss_limit_mb=1024`, timeout values, seeds, or previous campaign artifacts.
- Do not run any fuzz executable, `ctest`, altered/retry campaign, or G9 security review; do not call another delegate; do not use git commit/push.

## EXPECTED OUTPUTS / ACCEPTANCE

- A root-cause/remediation or blocker handoff at the required leaf handoff path, with exact evidence references, an explicit distinction between observed fact and hypothesis, preserved budget/failure facts, bounded permitted next owner/action, and `BLOCKED` or `READY_FOR_REVIEW` status as warranted. It must not claim G9 passed.
- A triage `fuzz-plan.md` documenting inspected strategy/harness scope and any strictly fuzz-only remediation, or why none is authorized.
- Standard completion report recording all modified paths, checks actually performed, no campaign run, no state update, no security review route, and remaining blocker.
- If a strategy/harness-only correction is evidenced, it must be limited to the single authorized record fuzzer path and still hand off for a future separately authorized execution; it may not be treated as campaign evidence.
- If the cause is not proven to be strategy/harness, write no shared fuzz change and hand off the blocker to the protocol-orchestrator. The orchestrator will not update G9 to approved from this work.

## HANDOFF / STOP CONDITIONS

Handoff target: `protocol-orchestrator`, required path `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-record-resource-triage-001/handoffs/g9-record-resource-triage-to-protocol-orchestrator.md`.

Stop immediately and write the blocker handoff if a native-code cause, semantic/design authority, numeric resource policy, or a new execution is required. Do not make a speculative harness change. No-op is valid only with the required blocker handoff and completion report. No further delegation is allowed.

CONTEXT CONTRACT: You have fresh context. Announce the active role, verify the packet and input approvals, preserve unrelated untracked work, and do not update shared workflow state.