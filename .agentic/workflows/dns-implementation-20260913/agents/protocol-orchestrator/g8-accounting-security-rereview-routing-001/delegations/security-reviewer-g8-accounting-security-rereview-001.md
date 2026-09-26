# Delegated task — G8 accounting security re-review

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-accounting-security-rereview-001-delegation` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `security` / `g8-accounting-security-rereview-001` |
| Target | `protocol/dns` corrective context-owned accounting implementation |
| Owner | `protocol-orchestrator` |
| Status | `IN_PROGRESS` after this sole leaf begins |
| Candidate | `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` (parent `62a2dda24194020904a75e1edce9b3d74fbd70a4`) |
| G7 evidence | Fresh independent `APPROVED` reviewer delivery `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd` |

ACTIVE ROLE: `security-reviewer`

ROLE: `security-reviewer`

GOAL: Independently perform exactly one fresh G8 security re-review of the accounting corrective candidate. Determine and record the G8 disposition, blocking findings, remediation route, and residual risks. Do not perform implementation or state coordination.

SCOPE: Security review of only candidate `c38a7fa`, which corrects DNS-G8-001 and DNS-G8-002 from `security-reviewer/g8-limits-rereview-001`. The prior G8 findings are review context, not an approval. This review may read the full relevant code/evidence but may write only its new unique workspace. Do not route G9, fuzzing, bindings, documentation, compatibility, final review, or any other stage.

## MODEL AND REASONING

- Policy: `docs/agentic/MODEL_POLICY.md`, `security-reviewer` row.
- Required actual route: provider `openai-codex`; model `gpt-5.6-sol`; reasoning `high`.
- Pre-dispatch verification: dedicated session `20260920_145142_8eb272` returned `MODEL_ROUTE_OK` under explicit `--provider openai-codex --model gpt-5.6-sol --reasoning high`.
- You must record actual runtime provider/model/effort and session identity in review/completion artifacts. A statement in this packet is not proof.
- One bounded review attempt. Actual usage/cost is `unknown` unless exposed. Astra/high is permitted only after a documented available-evidence Sol failure and only for the unresolved finding; otherwise stop.
- On quota/rate limit: stop immediately, do not make repository changes, and report `QUOTA_RATE_BLOCKER` to the parent process. Do not fabricate a gate result.

## REPOSITORY AND WORKING DIRECTORIES

- Absolute repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-accounting-security-rereview-001/`.
- Identity: one fresh security-reviewer session, independent of candidate author `c-protocol-implementer/g8-accounting-implementation-001`, all previous G7 reviewers, and `security-reviewer/g8-limits-rereview-001`.
- Shared source writer: none. All code, tests, truth and prior workspaces are read-only.
- Required Git wrapper for any Git write/push: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role security-reviewer -- ...`. If committing/pushing, use it and push `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back `origin/hermes/dns-implementation-20260913`. Never raw-commit/push.

## READ FIRST

- `AGENTS.md`
- `.hermes/skills/security-reviewer/SKILL.md`
- `docs/agentic/{SECURITY_MODEL,HANDOFFS,DIRECTORIES,ARTIFACTS,REVIEW_GATES,MODEL_POLICY}.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- This packet and `protocol-orchestrator/g8-accounting-security-rereview-routing-001/verification/g7-accounting-evidence-verification.md`

## REQUIRED INPUTS

- Candidate at `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175`; production delta is exactly `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_internal.h`, and `src/protocols/dns/dns_client.c` relative to `62a2dda24194020904a75e1edce9b3d74fbd70a4`.
- Candidate reports/handoff in `agents/c-protocol-implementer/g8-accounting-implementation-001/` at candidate revision.
- G7 record, report and completion in `agents/protocol-test-engineer/g7-accounting-native-verification-001/` at delivery `8c1383e...`, disposition `APPROVED` for `c38a7fa` only.
- Accounting design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; binding-lifetime review `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`; compatibility support review candidate delivery `git:685242c528517ec2e704c28a1f520ed4c1b76672`, review `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`.
- Prior G8 findings/report/review/handoffs at `agents/security-reviewer/g8-limits-rereview-001/`, delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`, including `DNS-G8-001` and `DNS-G8-002`.

## ALLOWED WRITES

Only these new files under the assigned workspace:

- `README.md`
- `security-review.md`
- `reviews/g8-accounting-security-rereview.md`
- `handoffs/` (only if G8 does not pass)
- `completion-report.md`

All production code/headers, tests, vectors, designs, docs, build files, workflow-root state/request/manifest, previous workspaces and all paths outside that set remain read-only. Do not amend any pre-existing handoff.

## REQUIRED OUTPUTS AND ACCEPTANCE

- Record actual model/effort/session evidence, fresh independence declaration, exact input revisions, threat scope, entrypoints/trust boundaries, checks actually run, limitations and G8 disposition.
- Re-assess both prior blocking findings: configured limits/resource disposition and global request tracking/cross-context lifecycle; assess malformed lengths, allocation/amplification, terminal no-result behavior, UDP/TCP admission, teardown/detached-handle safety, and applicable concurrency.
- `APPROVED` requires no unresolved blocking finding and explicit residual risk. `CHANGES_REQUESTED`/`BLOCKED` must name the owner, required action, and re-review criterion in a leaf-owned handoff.
- Do not update workflow state or claim/route G9. Return control to `protocol-orchestrator` after the one G8 record.

STOP CONDITIONS: candidate/G7 mismatch; non-Sol/high actual route; insufficient independence; forbidden write requirement; quota/rate error; missing prerequisite; or completion of this review. No further delegation.