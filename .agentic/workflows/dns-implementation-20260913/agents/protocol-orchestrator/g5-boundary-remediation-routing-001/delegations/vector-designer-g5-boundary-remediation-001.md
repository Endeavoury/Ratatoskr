# Delegated task

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-vector-designer-g5-boundary-remediation-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | Routing packet delivery pending wrapper-mediated commit |
| Source artifacts | Exact paths and revisions below. |
| Assumptions | None. |
| Open questions | None. |
| Limitations | One bounded corrective authoring route only; G5 synthesis, reviewer routing, G6 and later work are forbidden. |

ACTIVE ROLE: vector-designer

ROLE: vector-designer
GOAL: Produce one new, canonical, mechanically consumable DNS-REQ-002 local-request boundary remediation vector set that resolves `DNS-G5-COV-004` without modifying the existing candidate.
SCOPE: Corrective vector authoring only. Root task ID `dns-implementation-20260913`; project ID `Ratatoskr`; hierarchy `workspace-orchestrator -> protocol-orchestrator -> vector-designer (leaf)`.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, vector-designer row.
- Requested provider/model: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: unknown until exposed by the child; do not infer from this packet.
- Context target: 8,000–16,000 task-specific tokens while completing all required reading.
- Completion target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one evidence-driven correction only; then stop with a blocker/handoff.
- Escalation: bit-level ambiguity -> Sol/high only in a compatible configured session; missing truth -> handoff, not escalation.
- Stop: missing or conflicting upstream truth, write-boundary conflict, repeated validation failure, or completed READY_FOR_REVIEW output.

## Repository and working directories

- Absolute repository root and command CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Unique child workspace: `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/`.
- Shared source directories: none.
- Shared-file writer/ordering: the parent protocol-orchestrator is the sole workflow-state writer; child writes only the concrete files below.
- Git wrapper: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`; use `--role vector-designer` for every Git operation, including status/diff/check/commit/push/readback. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; never merge or push master. Preserve unrelated untracked historical workspaces.

## Workflow / stage / assignment

Workflow `dns-implementation-20260913`; stage `vectors`, gate `G5`; assignment `g5-boundary-remediation-001`; shared state `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` is read-only.

## Read first

- `AGENTS.md`
- `.hermes/skills/vector-designer/SKILL.md`
- `docs/agentic/{HANDOFFS,DIRECTORIES,ARTIFACTS,REVIEW_GATES,MODEL_POLICY}.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- This packet.

## Required inputs (read-only)

- Corrected candidate `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-remediation-001/vector-set.json` at `git:a8e631b338df393ddfd3ea9648f333303726d87b`, `sha256:0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`.
- Byte/coverage review `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g5-remediation-byte-coverage-review-002/reviews/g5-remediation-vector-byte-coverage-review.md` at remote `git:43979c78c33247cf990002ec1392606f24bc7427` (blocking `DNS-G5-COV-004`).
- Interpretation review `.agentic/workflows/dns-implementation-20260913/agents/protocol-analyst/g5-remediation-interpretation-review-002/reviews/g5-remediation-vector-interpretation-review.md` at remote `git:525ba264e97e579c5a2720db8706bb286d85d343` (approved scoped interpretation).
- Approved analysis `agents/protocol-analyst/analysis-001/protocol-analysis.md` at `git:5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
- Approved model `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at `git:f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- Approved API `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` at `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`.

## Allowed writes

- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/vector-set.json`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/decisions/`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/handoffs/`
- `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/completion-report.md`

All other paths are forbidden, including the existing vector candidate, all reviewer artifacts, workflow state, request/manifest, production code, tests, fuzzing, bindings, docs, and all G6/later records.

## Required output and acceptance

Create a new complete vector set in the child workspace. It must:

1. Preserve current corrective VEC-014, VEC-017, and VEC-019 through VEC-023 semantics/bytes/expectations from the immutable prior candidate, without editing that candidate.
2. Provide canonical mechanically consumable local-request boundary vectors mapping all DNS-REQ-002 values `0/1/63/64/255/256`.
3. For accepted boundary inputs, provide exact local input representation plus exact emitted DNS bytes, decoded lengths, framing, and expected success/state/cleanup behavior.
4. For rejected boundary inputs, provide exact local input representation plus rejected exact local input/no-I/O/cleanup outcome.
5. Use no production parser/builder/harness as oracle; validate JSON, hex, declared lengths, allowed-path diff, and `git diff --check`.
6. Write a standard READY_FOR_REVIEW completion report and a handoff to `protocol-orchestrator` requesting only later administrative evidence handling. Do not claim G5 approval and do not route reviewers/G6/later work.

If any required boundary behavior is ambiguous, create a formal blocking handoff to `protocol-analyst`, leave the output status BLOCKED, and stop. If a quota/rate error occurs, stop immediately without state changes or additional artifacts and report the exact error.

DELEGATION ALLOWANCE: none; this leaf must not delegate.
