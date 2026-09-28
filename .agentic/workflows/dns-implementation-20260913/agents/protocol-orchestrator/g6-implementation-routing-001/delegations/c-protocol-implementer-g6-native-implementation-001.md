# Delegated task — native DNS implementation

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g6-native-implementation-001-delegation` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` after remote routing delivery and leaf dispatch |
| Baseline | `e1290c91bd446afba7b08190fb87edfc4d5d8ca9` before routing delivery |
| Assignment workspace | `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/` |

ACTIVE ROLE: c-protocol-implementer

ROLE: c-protocol-implementer

GOAL: Implement the approved native DNS profile and additive request/limits API in C, then submit implementation evidence as `READY_FOR_REVIEW`. Do not approve your own work.

SCOPE: User-authorized native implementation only, after G6 administrative approval for the current approved G1–G5 inputs. This is one authoring assignment; it does not include test authoring, vector/design changes, review, G7, security, fuzzing, bindings, docs, CLI work, or any later stage.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, `c-protocol-implementer` row.
- Requested provider/model ID: `gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: unknown; no runtime metadata was exposed to the orchestrator and this packet does not configure Hermes.
- Context target: 8,000–16,000 task-specific tokens; required reading remains complete.
- Completion target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction; then report a bounded handoff/blocker rather than repeat unbounded repairs.
- Escalation: concurrent state, arithmetic/lifetime defect, or intricate incremental state may require a separately configured Sol/high session; do not silently change model or route.
- Stop/checkpoint: missing/stale approval, API/model/vector contradiction, required unapproved ABI change, write-boundary conflict, quota/rate error, or build defect not resolvable within the assigned scope.

## Repository and workflow

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Workflow state: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` (read-only).
- Stage / assignment: `native_implementation` / `g6-native-implementation-001`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/`.
- Delivery branch: `hermes/dns-implementation-20260913`; never merge or push `master`.
- For any commit/push, exclusively use `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role c-protocol-implementer -- <git args>` and read back `HEAD:refs/heads/hermes/dns-implementation-20260913` after each push. Never raw-git commit/push. If wrapper is unusable, create only a permitted blocker/completion artifact and do not claim delivery.

## Read first

- `AGENTS.md`
- `.hermes/skills/c-protocol-implementer/SKILL.md`
- `docs/agentic/{ARTIFACTS.md,SECURITY_MODEL.md,REVIEW_GATES.md,DIRECTORIES.md,HANDOFFS.md,MODEL_POLICY.md}`
- `docs/contributing.md`
- `docs/abi.md`
- G6 record: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g6-implementation-routing-001/verification/g6-implementation-readiness-verification.md`
- Approved analysis: `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/analysis-001/protocol-analysis.md` (`git:5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`)
- Approved model: `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` (`git:f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`)
- Approved API: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` (`git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`)
- Approved vectors: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/vector-set.json` (`git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`)

## Files allowed to change

Only these exact files, plus the exact own-workspace outputs listed below:

- `include/ratatoskr/dns.h` — realize only the approved additive public request/endpoint/limits declarations and documented ABI contract; preserve existing synchronous declarations and ABI-1 compatibility.
- `src/core/core_internal.h` and `src/core/context.c` — only necessary context-owned DNS limits realization and cleanup required by the approved API.
- `src/protocols/dns/dns_internal.h`
- `src/protocols/dns/dns_builder.c`
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_packet.c`
- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_transport_tcp.c`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/CMakeLists.txt` only if a necessary DNS component source registration is required by the realization.
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/implementation-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/handoffs/` (only an actually needed formal handoff)
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g6-native-implementation-001/completion-report.md`

All other paths are read-only, including all workflow state except your own workspace, approved analysis/model/API/vectors and gate records, `tests/`, `fuzz/`, `bindings/`, `docs/`, `cli/`, root/other CMake files, and all files outside the list above. Do not create or edit tests, vectors, designs, shared state, bindings, fuzzers, docs, or new unlisted source/header files.

## Required implementation constraints

- Implement only approved capabilities: selected ordinary QUERY behavior, hostile-input parsing, full correlation context, UDP-first with TCP only after correlated TC, one TCP frame per parse step with exact consumption, terminal cleanup/no partial results, limits, and excluded OPT/EDNS disposition.
- Preserve existing `ratos_dns_query` synchronous behavior and current ownership/error contracts. Do not invent numeric defaults, retry/server selection, TCP reuse/pipelining, EDNS, DNSSEC, encrypted transport, binding features, or a new ABI contract beyond the approved API.
- Treat input as hostile: checked arithmetic and bounds before every read/allocation/index/copy, bounded pointers/counts/name expansion, owned/borrowed lifetimes, and no undefined behavior.
- Use the approved vector set as canonical read-only behavior. Do not alter it to suit code.
- Run applicable existing native build/CTest checks from `docs/contributing.md` when feasible and record exact commands/results; tests themselves remain read-only. Document any unavailable/failed checks honestly.

## Expected outputs and acceptance

- `implementation-report.md`: maps implemented functions to approved requirements/API/vectors, lists exact changed files, baseline and delivery revision, build/check evidence, limitations, and a proposed handoff to independent `protocol-test-engineer` G7 review. Status must be `READY_FOR_REVIEW` only when your implementation work is complete.
- Standard `completion-report.md`: include role, status, artifacts, decisions, blockers, handoff, directories, validation evidence, and requested vs actual model/runtime (actual unknown unless exposed).
- Code diff remains entirely within the explicit allowed list, builds under the applicable existing workflow, and makes no technical self-approval. G7 is not started by this assignment.

HANDOFF TARGET: `protocol-orchestrator`, with a formal request for independently assigned `protocol-test-engineer` G7 review only after your authoring report is `READY_FOR_REVIEW` and delivery is verified.

DELEGATION ALLOWANCE: no further delegation.
