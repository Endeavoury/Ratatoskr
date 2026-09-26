# Delegation: fresh DNS G8 configured-limits security re-review 001

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-configured-limits-security-rereview-001-delegation` |
| Workflow / stage | `dns-implementation-20260913` / `security` / G8 |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Subject | `protocol/dns`, DNS-G8-001 configured limits and synchronous UDP admission |
| Candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` (parent `git:509114307b862e8e339ded3eea5d483ea861d2d4`) |
| Candidate author | `c-protocol-implementer/g8-configured-limits-remediation-002` |
| Reviewer identity | Fresh direct Hermes CLI `security-reviewer` leaf, independent of all candidate authors and all prior G8 reviewers |

ACTIVE ROLE: `security-reviewer`

## Goal and scope

Perform exactly one independent G8 security re-review of the exact candidate after its fresh G7 approval. Assess only whether DNS-G8-001 is resolved while preserving DNS-G8-002 accounting/lifecycle safety. Establish and record the technical G8 disposition; do not route G9 or later work.

Do not implement or edit production source/headers, tests, vectors, fuzz, bindings, build files, API/design, workflow state, prior reviews, or other agents’ artifacts. Do not merge, reset, clean, stash, force push, or touch master. Do not delegate.

## Model and stopping policy

- Policy: `docs/agentic/MODEL_POLICY.md`, `security-reviewer` row.
- Requested actual provider/model/effort: `openai-codex/gpt-5.6-sol/high`.
- Invocation request: direct Hermes CLI with `--provider openai-codex --model gpt-5.6-sol --reasoning high`.
- Before substantive review, record actual exposed runtime model and reasoning. If it is not explicitly `openai-codex/gpt-5.6-sol/high`, write only an allowed `BLOCKED` completion record; do not make a technical disposition or commit/push.
- One bounded independent review only. Any quota/rate-limit: stop immediately and make no repository/state changes; return exactly `QUOTA_RATE_BLOCKER`.
- Missing/stale inputs, wrapper failure, candidate mismatch, independence conflict, or forbidden-path need are blockers, not reasons to broaden scope or retry.

## Repository and Git

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Your unique workspace: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/`.
- Read first: `AGENTS.md`; `.hermes/skills/security-reviewer/SKILL.md`; `docs/agentic/{SECURITY_MODEL,HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,MODEL_POLICY}.md`; current workflow state; this packet.
- Use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role security-reviewer -- <git args>` for every role commit/push. Before delivery verify allowed paths and `git diff --check`. Commit/push only allowed reviewer artifacts to `HEAD:refs/heads/hermes/dns-implementation-20260913`, then wrapper-read `ls-remote origin refs/heads/hermes/dns-implementation-20260913` and record the exact readback. Never substitute raw Git writes.
- Preserve all existing tracked and untracked workspaces.

## Required inputs (read-only)

1. G7 approval: `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`, candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`, reviewer delivery `git:510b5a131bcb3272caeb7eb1821444b35644cfcd`, remote reflection `git:7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`.
2. Candidate evidence: `agents/c-protocol-implementer/g8-configured-limits-remediation-002/{README.md,implementation-report.md,completion-report.md,handoffs/dns-g8-001-configured-limits-remediation-to-protocol-orchestrator.md}`.
3. Original open finding: `agents/security-reviewer/g8-accounting-security-rereview-001/{security-review.md,reviews/g8-accounting-security-rereview.md,handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md}`.
4. Approved G1–G6 inputs referenced by workflow state, including approved analysis/model/API/vectors, plus `docs/agentic/SECURITY_MODEL.md`.
5. Candidate source diff only in `src/protocols/dns/dns_parser.c`, `dns_transport_udp.c`, `dns_client.c`, and `dns_internal.h`.

## Exact allowed writes

- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/security-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/handoffs/` (only if a formal return is needed)
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/completion-report.md`

All other paths are forbidden/read-only. In particular, do not write workflow-state or any existing handoff Resolution.

## Required assessment and outputs

Independently assess hostile configured limits, integer/offset/length behavior, resource allocation/copy/traversal, terminal cleanup/no-result/accounting, detached handles, UDP truncation/oversize admission, TCP behavior after truncation, and preservation of public ABI and DNS-G8-002. Validate evidence you can actually execute, recording commands and limitations.

Create the exact allowed files. The gate record must include exact revisions, reviewer identity and independence declaration, G8 disposition, evidence, findings/residual risks, limitation, and failure route. `APPROVED` requires no unresolved blocking G8 finding; `CHANGES_REQUESTED` must give finding ID/evidence/owner/remediation; `BLOCKED` must be honest. Finish a standard completion report and return to `protocol-orchestrator` only. The orchestrator, not you, reflects state after verification.