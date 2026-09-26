# Delegated task — DNS-G8-001 configured-limits remediation

| Field | Value |
| --- | --- |
| Artifact ID | `dns-g8-configured-limits-remediation-001-delegation-r002` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `native_implementation` / `g8-configured-limits-remediation-001` |
| Role | `c-protocol-implementer` |
| Status | `IN_PROGRESS` only after required runtime route is verified |
| Target | `protocol/dns`, blocking finding `DNS-G8-001` only |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Starting local HEAD | `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0` |
| Origin ref at routing preflight | `git:5fe96f16812e1c98ca4b1f68c120a72a3d54d00b` |
| Owned workspace | `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-configured-limits-remediation-001/` |

ACTIVE ROLE: `c-protocol-implementer`

## Read first

1. `AGENTS.md`; `.hermes/skills/c-protocol-implementer/SKILL.md`.
2. `docs/agentic/{WORKFLOW,ROLES,HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,MODEL_POLICY,SECURITY_MODEL}.md`; `docs/contributing.md`; `docs/abi.md`.
3. `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`; this packet.
4. `agents/security-reviewer/g8-accounting-security-rereview-001/{security-review.md,reviews/g8-accounting-security-rereview.md,completion-report.md,handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md}`.

## Mandatory route check and stop rule

Before substantive inspection or any write, verify actual child provider/model/effort from runtime/session evidence. It must be exactly `openai-codex/gpt-5.6-sol`, reasoning `high`. A model name in this packet is not evidence and no fallback is authorized. If unavailable or mismatched, return `BLOCKED` to the parent immediately; make **no repository change and no leaf artifact**. If a quota or rate-limit error occurs, immediately stop without state changes and return exactly `RATE_OR_QUOTA_BLOCKER`. Do not delegate further.

## Immutable inputs and technical truth

- Accounting implementation candidate: `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`.
- Fresh independent G7 approval: `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd`, scoped to `c38a7fa`.
- Completed G8 delivery: `git:1d33a8155dc6bcd3be16689d8aa134044b4449b0`, `CHANGES_REQUESTED`.
- Preserve G8 truth: `DNS-G8-002` is resolved only for `c38a7fa`; blocking `DNS-G8-001` remains. Do not self-approve G7/G8 or route review/later stages.

## Goal and exact write boundary

Produce one narrow correction for DNS-G8-001. Production writes may be only:

- `src/protocols/dns/dns_parser.c`
- `src/protocols/dns/dns_transport_udp.c`
- `src/protocols/dns/dns_client.c`
- `src/protocols/dns/dns_internal.h`

Artifact writes may be only the owned workspace `README.md`, `implementation-report.md`, `handoffs/`, and `completion-report.md`; plus only `## Resolution (destination role)` in `agents/security-reviewer/g8-accounting-security-rereview-001/handoffs/dns-g8-001-configured-limits-remediation-still-incomplete.md`. All tests, public headers, core/build files, canonical truth/reviews/state, and every other path are read-only.

Required correction: preserve every `read_name` resource result including record owners; reject or coherently cap traversal configuration above the hard maximum; apply effective/configured resource checks before overlapping hard pointer/total-RR malformed guards; reject oversized/truncated synchronous UDP datagrams before parsing on supported platforms; preserve context-owned accounting, exact-once release, terminal no-result cleanup, destruction, and detached-handle safety from `c38a7fa`. If this needs any forbidden path or contract change, stop `BLOCKED` with a narrow owned handoff.

## Validation, delivery, and return

Inspect the full `read_name` call graph before edits. Run available existing checks without test edits, record exact commands/output and limitations, and do not claim unrun checks. Before delivery use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role c-protocol-implementer -- <git args>` for every Git read/write; never raw Git. Commit only allowed paths, push exactly `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read `origin` back with the wrapper. Verify authorized paths and `diff --check`.

Return one handoff to `protocol-orchestrator` and a standard completion report. If implemented, status is `READY_FOR_REVIEW` only; fresh independent G7 and then G8 remain pending. No G7/G8/G9/later dispatch or approval is authorized.