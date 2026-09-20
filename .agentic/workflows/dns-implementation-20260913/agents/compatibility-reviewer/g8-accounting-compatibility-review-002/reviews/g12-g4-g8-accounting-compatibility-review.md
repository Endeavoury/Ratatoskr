# G12-style G4-supporting G8 accounting compatibility review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g12-g4-g8-accounting-compatibility-review-002` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` private request accounting and context-destroy lifetime design |
| Owner role | `compatibility-reviewer/g8-accounting-compatibility-review-002` |
| Status | `APPROVED` — scoped review only |
| Subject revision | `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Baseline revision | `git:e804eb46f9aca14c4be6152e154a0b518f34c7fe` |
| Supporting delivery | `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7` |
| Assumptions | Future implementation realizes the reviewed private contract exactly. |
| Open questions | None for this scoped gate fact. |
| Limitations | Not overall G4 or full G12 approval; no G6, implementation, G7, G8, or later-stage authorization. |

## Gate identity

- Gate ID and applicability: G12-style compatibility evidence supporting corrective G4 review only.
- Workflow stage: corrective native API design review.
- Required inputs: exact candidate design/decision/handoff/completion at `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; ABI/API baseline at `git:e804eb46f9aca14c4be6152e154a0b518f34c7fe`; binding-lifetime review/completion/handoff at `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`.
- Artifact author: `protocol-api-designer/g8-accounting-design-001`, Hermes session `20260920_085757_8e1f9b` as recorded in workflow state.
- Binding-lifetime reviewer: `binding-api-designer/g8-accounting-lifetime-review-001`, `deleg_8efb9cd3/task-0` as recorded in workflow state.
- Prior blocked reviewer: `compatibility-reviewer/g8-accounting-compatibility-review-001`, distinct and not reused for technical judgment.
- Reviewer: fresh `compatibility-reviewer/g8-accounting-compatibility-review-002`, Hermes session `20260920_095053_0c67b1`.
- Independence: this reviewer authored none of the candidate, binding review, or prior blocked artifacts.
- Review date: 2026-09-20 CEST.
- Runtime evidence: live parent command line explicitly contains `--provider openai-codex -m gpt-5.6-sol --reasoning medium`; requested and actual route match.

## Evidence and checks

| Pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Immutable input identity and ancestry | Wrapper `cat-file`, `merge-base`, `show`; subject/binding/baseline commits above | PASS: all exact objects read; subject → binding delivery → baseline ancestry verified. | None. |
| ABI symbols/layout/calling contracts | Identical subject/baseline blobs for `include/ratatoskr/{context,dns,version}.h`; empty wrapper diffs | PASS: no public declaration, symbol, ABI-safe layout, calling convention, or version change. | No compiled library was produced by this design-only candidate. |
| Source API | Same public header blobs and prototypes at subject/baseline | PASS: source surface is byte-identical; no caller migration. | None. |
| Ownership/lifetime | Candidate §§1–6 and decision record; baseline private representation; binding review `e04fefa…` | PASS: caller-owned requests are detached, not freed; COMPLETE result ownership survives; mutation cannot resume. | Must be implemented exactly and rechecked at G7/G8. |
| Binding representability | Fresh binding review delivery `e04fefa…`; repository bindings read-only inspection | PASS: opaque private growth and detached terminal handles are representable; current bindings have no conflicting request wrapper. | No binding implementation is in scope. |
| Observable behavior | Candidate transition table/context-destroy rule against baseline private code and public contracts | PASS: safe deterministic teardown replaces an omitted UAF case without wire/query/public error-contract regression. | G13 should document the implemented lifecycle clarification. |
| Version/migration policy | `docs/abi.md`, `version.h`, `docs/migration-dotnet.md` identical at subject/baseline | PASS: ABI remains 1/version 0.1.0; no deprecation, major bump, or code migration required. | Release docs should describe the fix after implementation evidence. |
| Reviewer boundary | Staged/delivery diff and `git diff --check` recorded in completion | PASS when delivered: only assigned reviewer files plus named handoff Resolution. | Unrelated pre-existing work remains outside this review. |

## Disposition

`APPROVED`.

The exact candidate is binary-ABI, source-API, ownership/lifetime, binding-representability, observable-behavior, and version/migration compatible with the exact baseline. This is a scoped technical review fact only. The `protocol-orchestrator` must independently verify delivery and is solely responsible for any G4 synthesis or renewed G6 routing; fresh implementation, G7, and G8 evidence remain required.