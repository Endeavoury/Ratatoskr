# Directory ownership framework maintenance

- Artifact ID: agent-directory-ownership-entry; template version: 1.
- Workflow ID: agent-directory-ownership; target: agent framework.
- Owner: documentation-writer, root author session.
- Status: READY_FOR_REVIEW.
- Source revision: 378b452de858c4dc349f07ac2c7765d216a92fe0.
- Revision: current worktree; exact candidate digests recorded in candidate-sha256.txt.
- User scope: refactor repository so every agent knows its own or combined working directory.
- Interpretation: dedicated assignment workspaces and explicit shared source ownership;
  retain the SDK dependency layout and all existing code paths.
- Allowed files: root AGENTS.md; docs/repository-layout.md; docs/agentic/ directory
  contract and navigation; .hermes/skills/*/SKILL.md directory sections and matching
  path wording; .agentic/README.md and templates; this author's entry/evidence records.
- Read-only: production source, public ABI, bindings, tests, fuzzers, build/CI behavior,
  schemas, existing workflow state and all other work items.
- Command working directory: /mnt/development/Codex/Ratatoskr.
- Workspace: .agentic/workflows/agent-directory-ownership/agents/documentation-writer/directory-refactor/.
- Acceptance: all 16 roles mapped to unique workspace templates and eligible shared
  paths; reviewers stay independent; overlapping source writes require coordination;
  no code relocation, broken local Markdown links, or schema field changes.
- Assumptions: preserve existing work-item paths; create role workspace instances as
  assignments are issued, rather than claiming all template roles are active agents.
- Open questions: none. Limitations: instruction boundaries are not a filesystem sandbox.
- Coordination: direct framework-maintenance exception in HANDOFFS.md; no fictional
  protocol manifest/state or implementation gate approvals are created.
- Requested author settings: documentation-writer escalation Terra/medium for
  cross-document contracts. Actual: existing parent runtime retained; exact model ID,
  effective reasoning and token usage are not exposed to this artifact author.
- Independent review: final-reviewer, requested gpt-5.6-sol / medium, bounded review
  of this framework diff; writes only its own review workspace. One correction pass
  then escalate concrete unresolved findings. No monetary/token cap supplied.
