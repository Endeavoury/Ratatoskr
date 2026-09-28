# Delegated task — G9 DNS name-harness focused independent review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-focused-review-001-delegation` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `DISPATCHED` |
| Revision | dispatch baseline `git:d7dae4ecb33ff6c94cd5fc99e880fce2c4de42a8` |
| Source artifacts | Candidate and remediation delivery at `git:2c9e9b945352642d27cf703132e8e5e525b8b5cb`; prior failure verification at `git:419992875eac88839a29efca0b06552bd02ae326` |
| Assumptions | The candidate is a focused remediation submitted READY_FOR_REVIEW, not G9 evidence. |
| Open questions | None; report any evidence mismatch as a finding. |
| Limitations | No full G9 campaign and no security review are authorized. |

ACTIVE ROLE: fuzz-engineer

ROLE: fuzz-engineer, fresh independent reviewer leaf.

GOAL: Independently verify/review only the G9 DNS name-harness remediation candidate. You are distinct from remediation author `deleg_9f677c42/task-0`; do not rely on its conclusion.

SCOPE: Focused read-only review of `fuzz/dns/fuzz_dns_name.c` at candidate delivery `git:2c9e9b945352642d27cf703132e8e5e525b8b5cb`. Do not amend source, corpus, CMake, tests, or state. This is not a G9 gate approval, full G9 campaign, or security review.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested provider/model ID: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: unknown to coordinator; record only telemetry actually exposed to you.
- Context target: 8,000–16,000 task-specific tokens with all required reading complete.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one focused independent review; no remediation attempt.
- Escalation: do not escalate by routing/delegating; evidence mismatch is a finding.
- Stop/checkpoint: quota or rate error—stop immediately, do not write state or retry; report the error if an artifact already exists.

## Repository and working directories

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-focused-review-001/`
- Workspace owner: `fuzz-engineer/g9-name-harness-focused-review-001`, fresh leaf reviewer identity.
- Shared source: none writable; candidate source is read-only.
- Git wrapper for every Git operation: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git args>` from repository cwd only.
- If you commit allowed artifacts, use that wrapper and push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; never master/main; read back the exact remote ref after push. Do not commit/push unrelated changes.

## Workflow/stage/assignment

- Workflow/stage: `dns-implementation-20260913` / fuzzing (G9 focused remediation review)
- Assignment: `g9-name-harness-focused-review-001`
- Shared state is read-only: `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`

## Read first

- `AGENTS.md`
- `.hermes/skills/fuzz-engineer/SKILL.md`
- `docs/agentic/{WORKFLOW,HANDOFFS,ARTIFACTS,REVIEW_GATES,DIRECTORIES,ROLES,MODEL_POLICY,SECURITY_MODEL}.md`
- `.agentic/workflows/dns-implementation-20260913/{request.md,manifest.yaml,workflow-state.yaml}`
- This packet.

## Required inputs

- Candidate source: `fuzz/dns/fuzz_dns_name.c` at `git:2c9e9b945352642d27cf703132e8e5e525b8b5cb`.
- Remediation report: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-results.md`.
- Remediation handoff: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/handoffs/g9-name-harness-remediation-to-protocol-orchestrator.md`.
- Remediation completion: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/completion-report.md`.
- Delivery verification: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-harness-remediation-routing-001/verification/g9-name-harness-remediation-001-delivery-verification.md`.
- Failure evidence: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-008/verification/g9-fuzz-execution-005-delivery-verification.md`.

## Allowed writes (only)

- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-focused-review-001/reviews/g9-name-harness-focused-review.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-focused-review-001/completion-report.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-focused-review-001/handoffs/g9-name-harness-focused-review-to-protocol-orchestrator.md` if required by disposition.

All source, corpus, CMake, test code, workflow state, other specialist artifacts, request, manifest, docs and all other paths are read-only.

## Expected outputs and acceptance criteria

Write a focused review record and completion report (and handoff if findings/blocker require it), with exact revisions and reviewer identity. It must independently:

1. Verify candidate revision ancestry and remote branch availability/readback.
2. Verify candidate delivery diff from parent `f90c9bd80217cddb0e036d4dc0d8914f0cd32927` has exactly these five paths: `fuzz/dns/fuzz_dns_name.c` and the four remediation reports listed above; check whitespace/diff boundary.
3. Inspect the code and verify cap arithmetic: `copied` maximum is 1007 and terminal write maximum index is 1023 for `packet[1024]`.
4. Verify LLVM19-only focused build/replay evidence and sanitizer-clean 1,133-byte replay. Independently reproduce an appropriate focused LLVM19 build/replay in `/tmp` when capability is present. Record actual commands, compiler paths/versions, exit status, target and diagnostics; if capability unavailable, report it honestly and do not claim reproduction.
5. Return `APPROVED` only if all focused criteria pass, otherwise `CHANGES_REQUESTED` or `BLOCKED` with factual evidence and a precise owner route.

An APPROVED focused review does not approve G9 and must explicitly retain G9 BLOCKED pending a fresh complete campaign and designated G9 security review. Do not self-approve G9.

## Handoff target

`protocol-orchestrator`, via the assigned handoff path when needed. Do not route another role or stage.

## Stop conditions

- Quota/rate error: stop immediately and make no state changes or retries.
- Missing/non-ancestral candidate, unauthorized diff, failed build/replay, sanitizer diagnostic, or inability to establish required evidence: record factual CHANGES_REQUESTED/BLOCKED; do not fix anything.
- No further delegation.