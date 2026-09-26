# Delegated task — DNS-G8-001 configured-limits remediation 002

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-configured-limits-remediation-002-delegation` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `native_implementation` / `g8-configured-limits-remediation-002` |
| Owner | `protocol-orchestrator` |
| Status | `IN_PROGRESS` only after this direct leaf starts |
| Current baseline | `git:9afc2e8825619dccc73e8eed00a431f838dd8a47` |
| Reviewed implementation subject | `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` |
| G7 and G8 evidence | `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`; `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |

ACTIVE ROLE: `c-protocol-implementer`

## Goal and scope

Produce exactly one narrowly scoped native corrective candidate for blocking `DNS-G8-001`, then return `READY_FOR_REVIEW` or `BLOCKED` to `protocol-orchestrator`. Preserve the context-owned accounting, exact-once release, terminal cleanup/no-result, context destruction, and detached-handle behavior that resolved `DNS-G8-002` in `c38a7fa`. Do not review or route G7, G8, G9, or any other work, and do not claim a gate passed.

## Required runtime and Git transport

This leaf is invoked with actual provider `openai-codex`, model `gpt-5.6-sol`, reasoning `high`; record actual session/route evidence in both reports. One bounded attempt only; no delegation, fallback, or retry. Every Git read and write must use exactly:

`/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role c-protocol-implementer -- <git args>`

Never raw-Git a write, merge, reset, clean, stash, force-push, or push master. Before work, wrapper-read root/origin/branch/HEAD/status and confirm the baseline is an ancestor of HEAD; preserve all unrelated tracked/untracked content. Commit only the explicit allowed paths. Push exactly `HEAD:refs/heads/hermes/dns-implementation-20260913`, then wrapper-read `origin refs/heads/hermes/dns-implementation-20260913`. Report source candidate SHA, artifact-delivery SHA, and exact remote readback.

If a quota/rate-limit error occurs, immediately stop with no repository changes and return exactly `QUOTA_RATE_BLOCKER`. If actual route, wrapper, or baseline conflicts, do not touch production or shared state; write only a valid owned blocker artifact if allowed and return `BLOCKED`.

## Repository and reading

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Branch: `hermes/dns-implementation-20260913`
- Unique artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-002/`
- Read first: `AGENTS.md`; `.hermes/skills/c-protocol-implementer/SKILL.md`; `docs/agentic/{WORKFLOW,ROLES,HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,MODEL_POLICY,SECURITY_MODEL}.md`; `docs/contributing.md`; `docs/abi.md`; current `workflow-state.yaml`; this packet; G8 `security-review.md`, `reviews/g8-accounting-security-rereview.md`, and handoff `dns-g8-001-configured-limits-remediation-still-incomplete.md`.

## Exact write boundary

Production files, only:

- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_internal.h`

Own workspace files: `README.md`, `implementation-report.md`, `handoffs/`, `completion-report.md` below the unique workspace. Existing-artifact exception: only the `## Resolution (destination role)` section of `agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`.

Everything else is forbidden: tests/test registration, public headers, `src/core`, build files, workflow state, approved truth, reviews, vectors, and every other workspace.

## Required correction and evidence

1. Preserve resource disposition from every `read_name` caller, including record-owner parsing.
2. Reject or cap explicit compression-pointer traversal limits above the implementation maximum so accepted settings are enforceable.
3. Apply configured/effective resource checks before overlapping hard malformed guards for pointer traversal and total-RR limits.
4. Detect oversized/truncated synchronous UDP datagrams before parsing or accepting a truncated correlated prefix on supported platforms.
5. Preserve all `DNS-G8-002` behaviors and public ABI unchanged.

Inspect the complete current call graph before editing. Run available existing relevant validation without changing tests; record exact commands, outputs, candidate boundary, `diff --check`, and limitations. Do not claim CMake/CTest, sanitizer, socket or dynamic boundary evidence unless actually executed. If a correction needs a forbidden path, test authorship, or unapproved ABI/design decision, stop with a narrow owned handoff.

## Outputs and handoff

Create the four owned artifact forms above, including a return handoff to `protocol-orchestrator`. Update the permitted handoff Resolution only after a candidate exists. `READY_FOR_REVIEW` requires authorized-path delivery, wrapper push/readback, validation evidence, no known in-scope defect, and preserved accounting behavior. Fresh independent G7 then G8 are required later but are not part of this task.
