# G8 accounting security re-review routing

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Active role | `protocol-orchestrator` |
| Assignment | `g8-accounting-security-rereview-routing-001` |
| Scope | Administrative reconciliation of fresh G7 accounting approval and routing of exactly one fresh G8 security re-review. |
| Candidate | `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` |
| G7 reviewer delivery | `git:8c1383e4bcfa2aab7692dd863f9532f14a13a0bd` |
| Required reviewer route | `openai-codex/gpt-5.6-sol`, reasoning `high` |
| Allowed writes | This workspace, new `security-reviewer/g8-accounting-security-rereview-001/` workspace, and `workflow-state.yaml` only. |
| Forbidden | Production/tests/vectors/designs/other workspaces; G9 and later; technical self-approval. |

This route is limited to a fresh independent G8 review of the accounting corrective candidate. The designated security reviewer alone determines the technical G8 disposition. No G9 route is authorized.