# G3 disposition-partition review routing

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Active role | `protocol-orchestrator` |
| Assignment | `g3-disposition-review-routing-001` |
| Scope | Route exactly one fresh, independent `protocol-api-designer` G3 review of the READY_FOR_REVIEW disposition-partition model. |
| Repository root / command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline | `fde16d8ede7443e9a5fd93188ed2a05fda4d986f` on `hermes/dns-implementation-20260913` |
| Origin / remote ref at routing inspection | `https://github.com/Endeavoury/Ratatoskr.git` / `fde16d8ede7443e9a5fd93188ed2a05fda4d986f` |
| Child workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g3-disposition-review-001/` |
| Handoff target | `protocol-orchestrator` after one G3 disposition; no G4 routing. |

## Preconditions and boundary

- The candidate modeler assignment `g3-disposition-partition-001` is `READY_FOR_REVIEW`; its model content revision is `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`.
- G3 and modeling remain `CHANGES_REQUESTED` pending this independent reviewer disposition. G4 and later stages remain unadvanced.
- The designated reviewer must be a fresh child identity, distinct from `g3-api-001` and `g3-corrective-review-001`; the pre-dispatch state records those prior identities as `pending independent child assignment` and `deleg_f2099944/task-0` respectively.
- The role-controlled wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` was independently found, is an executable regular file, and accepts `--role protocol-orchestrator` / `--role protocol-api-designer`. Its body invokes Git with canonical role identity.
- Requested reviewer policy is `gpt-5.6-sol` / medium. Parent runtime exposed `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage are unknown. No Hermes configuration was changed.

The complete fresh-context leaf packet is `delegations/protocol-api-designer-g3-disposition-review-001.md`. This routing record makes no technical G3 judgment and does not authorize design, implementation, tests, headers, or later-stage work.
