# Agent directory documentation report

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | agent-directory-ownership-documentation |
| Workflow ID | agent-directory-ownership |
| Target | agent framework |
| Owner role | documentation-writer |
| Status | READY_FOR_REVIEW |
| Revision | Candidate SHA-256 manifest in this directory |
| Source artifacts | Git baseline 378b452de858c4dc349f07ac2c7765d216a92fe0; README.md entry scope |
| Assumptions | Retain component source layout; isolate assignment artifacts |
| Open questions | None |
| Limitations | Instructions do not enforce filesystem permissions; no Hermes runtime change |

## Coverage

| Paths | Contract and verification |
| --- | --- |
| docs/agentic/DIRECTORIES.md | All 16 role workspaces, eligible shared paths, conflict handling and older-path compatibility |
| .hermes/skills/*/SKILL.md | Each role names its own workspace and links the shared directory contract |
| .agentic/templates/agent-workspaces/*/README.md | All 16 reusable directories exist; templates explicitly require instantiation |
| .agentic/templates/delegation.md | Concrete command cwd, workspace, owner and shared-file writer required |
| .agentic/templates/completion-report.md | Actual directories and changed shared paths recorded |
| .agentic/templates/workflow-state.yaml | Existing path fields reference workspace outputs; schema remains unchanged |
| AGENTS.md, .agentic/README.md, docs/repository-layout.md, docs/agentic/{README,ROLES,ARTIFACTS,HANDOFFS,WORKFLOW}.md | Entry, navigation, artifact layout and resumption agree |

## Evidence

See validation.txt for checks and candidate-sha256.txt for exact candidate revisions.
All 157 local Markdown links resolve; role/template/map coverage matches all 16 skills;
git diff --check passes. Only framework documentation and templates changed.
Production tests were not run because executable code and build behavior did not change.
No model pricing, provider configuration or runtime claims were changed or reverified.

## Review

Independent final-reviewer receives review-handoff.md and the candidate manifest.
Author submits READY_FOR_REVIEW and does not advance shared workflow state.
