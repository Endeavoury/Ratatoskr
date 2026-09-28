# Specialist completion — G8 accounting design

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-design-001-completion` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` internal request accounting |
| Owner role | `protocol-api-designer/g8-accounting-design-001` |
| Status | `READY_FOR_REVIEW` |
| Revision | Assignment delivery commit; exact revision and origin readback reported to `protocol-orchestrator`. |
| Source artifacts | G8 `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; blocker `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`; model `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; G4 `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; source candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`. |
| Assumptions | Same-context/request mutation is serialized; separate contexts remain concurrently usable. |
| Open questions | None blocking candidate review. |
| Limitations | Design-only validation; no production build, test, race detector, implementation, or technical gate review was performed. |

ROLE: `protocol-api-designer/g8-accounting-design-001`

STATUS: `READY_FOR_REVIEW`

SUMMARY:
Produced a bounded private ownership/accounting design for `DNS-G8-002`. It replaces the process-global tracker with context-owned registry/counters, defines exact accounting for every requested lifecycle path, specifies safe context destruction with live caller-owned handles, preserves separate-context concurrency and public ABI, and limits a later accounting implementation to four private files.

ARTIFACTS CREATED:
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/api-design.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/decisions/context-destroy-live-requests.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/handoffs/accounting-design-to-protocol-orchestrator.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/completion-report.md`

ARTIFACTS MODIFIED:
- `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-global-limits-remediation-001/handoffs/g8-global-limits-remediation-authority-blocker.md` — Resolution section only.

DECISIONS MADE:
- `decisions/context-destroy-live-requests.md`: context destruction cancels/detaches nonterminal requests but does not free caller-owned handles; COMPLETE result ownership is preserved.
- Outstanding slots are acquired at successful start; connection slots only at UDP-to-TCP transition; all slots release at terminal transition, not take-result/destruction.
- No process-global mutable request state and no public ABI change.

OPEN QUESTIONS:
None blocking design review. Numeric resource policy and `DNS-G8-001` remain outside this accounting assignment.

BLOCKERS:
Implementation remains blocked until this exact candidate receives the designated independent reviews and the orchestrator renews G6/write authority.

HANDOFF REQUIRED:
`protocol-orchestrator` must obtain fresh independent `binding-api-designer` and `compatibility-reviewer` dispositions, then—only if approved—issue a new exact-scope c-protocol-implementer packet and later fresh G7 then G8 review.

RECOMMENDED NEXT ROLE:
`protocol-orchestrator`, to route the two independent design reviews; no implementation route yet.

WORKING DIRECTORIES:
- Command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Owned artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/`
- Shared path changed: only the assigned authority-blocker Resolution section.
- Pre-existing unrelated untracked workspaces were preserved.

VALIDATION EVIDENCE:
- Wrapper-verified origin, branch, HEAD, exact remote ref, and ancestry of all five packet revisions before writing.
- Reviewed exact committed G8 review/handoff, blocker, G3 model, G4 design, candidate core/context/DNS client, public headers, ABI contract, role/shared instructions, and workflow state.
- Pre-commit checks will verify exact allowed-path staging and `git diff --check`; final delivery will be pushed/read back through the required wrapper.
- No build/test/race execution is claimed because production implementation and test work are forbidden.

MODEL / REASONING USED:
Requested `openai-codex/gpt-5.6-sol`, medium. Observed runtime model `gpt-5.6-sol` via session metadata; provider is `openai-codex`. Effective reasoning setting is not exposed and is recorded as unknown rather than inferred.

USAGE AND ESCALATIONS:
One evidence-driven design pass; no model escalation or retry ladder. Token/cost usage is not exposed and is unknown.
