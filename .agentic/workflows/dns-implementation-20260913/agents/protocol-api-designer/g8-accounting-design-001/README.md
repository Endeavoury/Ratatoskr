# G8 DNS request-accounting design correction

- Workflow: `dns-implementation-20260913`
- Assignment: `protocol-api-designer/g8-accounting-design-001`
- Active role: `protocol-api-designer` (leaf)
- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/`
- Status: `READY_FOR_REVIEW`
- Handoff target: `protocol-orchestrator`

## Immutable inputs

- G8 review and `DNS-G8-002` handoff: `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`
- Implementation authority blocker: `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`
- Approved G3 model: `git:f26745472178649a60f2cb079937d1bbe3f13c0b`
- Approved G4 design: `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`
- Read-only implementation candidate: `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`

All listed revisions were verified as ancestors of `origin/hermes/dns-implementation-20260913` before writing.

## Write boundary

This assignment owns only this workspace and the Resolution section of `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-global-limits-remediation-001/handoffs/g8-global-limits-remediation-authority-blocker.md`. Production source, public headers, tests, fuzzers, vectors, prior reviews, and workflow-root records remain unchanged.

## Outputs

- `api-design.md`: implementation-ready private ownership/accounting supplement.
- `decisions/context-destroy-live-requests.md`: teardown/lifetime decision.
- `handoffs/accounting-design-to-protocol-orchestrator.md`: review and renewed-authority request.
- `completion-report.md`: assignment result and checks.
