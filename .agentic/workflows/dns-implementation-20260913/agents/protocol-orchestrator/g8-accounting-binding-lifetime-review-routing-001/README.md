# G8 accounting binding-lifetime review routing

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-g8-accounting-binding-lifetime-review-routing-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` private request/context accounting design |
| Owner role | `protocol-orchestrator/g8-accounting-binding-lifetime-review-routing-001` |
| Status | `IN_PROGRESS` — one independent binding-lifetime review dispatched; no technical gate decision by the orchestrator |
| Revision | Routing baseline `git:e138c4b35d55ccff19f1eb9abd49291adf465c0d`; design candidate `git:4a37fc293c842b206190bad369e2a3e1ad00008c` |
| Source artifacts | Candidate design, decision, handoff, and completion listed in the delegation packet |
| Assumptions | The candidate is `READY_FOR_REVIEW`; designated binding and compatibility reviews are both required before G6 renewal. |
| Open questions | Reviewer disposition is pending. |
| Limitations | This routing artifact neither approves G4 nor routes compatibility, implementation, G6 renewal, G7, G8, or any later stage. |

ACTIVE ROLE: `protocol-orchestrator`

## Scope and route

This is exactly one corrective independent `binding-api-designer` review of the private G8 accounting-design candidate. The leaf owns only its new unique review workspace. The candidate author is `protocol-api-designer/g8-accounting-design-001`; the leaf must be a separate fresh agent/session and must record that independence in its review evidence.

## State discipline

The orchestrator records only the pending assignment and routing event. It must verify required artifacts, reviewer identity/independence, exact candidate revision, allowed diff, target ancestry, and wrapper-mediated remote readback before recording the reviewer disposition. No technical gate is self-approved.

## Git discipline

All commit, push, and remote-ref readback actions use `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` with the acting role. Target only `HEAD:refs/heads/hermes/dns-implementation-20260913`. Preserve pre-existing untracked workspaces.
