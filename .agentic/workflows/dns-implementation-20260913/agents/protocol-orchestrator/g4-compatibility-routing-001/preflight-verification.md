# Mandatory G4 compatibility-review routing preflight

| Check | Observed evidence | Orchestration result |
| --- | --- | --- |
| Repository delivery baseline | Wrapper-mediated fetch/readback found local `HEAD` and `refs/remotes/origin/hermes/dns-implementation-20260913` both at `2f4fb280f5e610bb9a28577c7b30314052cb4994`; origin is `https://github.com/Endeavoury/Ratatoskr.git`; branch is `hermes/dns-implementation-20260913`. | Valid delivery basis for a routing-only commit. |
| Wrapper prerequisite | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is a regular executable file. All Git operations below use it with `--role protocol-orchestrator`. | Satisfied. |
| Unrelated worktree preservation | The only observed worktree change is the pre-existing untracked `.agentic/workflows/dns-implementation-20260913/agents/binding-api-designer/g4-binding-safety-rereview-001/`. | Preserve exactly; it is excluded from commits and the leaf scope. |
| G3 prerequisite | Workflow state records G3 `APPROVED`, using model `f26745472178649a60f2cb079937d1bbe3f13c0b` / SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700` and analysis `5615caed0b7ad0a321d6794e71b79c4195e90384` / SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`. | Valid prerequisite evidence; no technical re-review by this role. |
| Candidate readiness | Immutable remediation candidate and completion were wrapper-read at `262c445a1b519b3baaa04f71fbcd59074c1baab0`; candidate SHA-256 is `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`, completion SHA-256 is `6de8c06709d92d5b99eac797e6c7b974e05f5f75630f6342fd13a639231bb55e`, and its author status is `READY_FOR_REVIEW`. | Review-consumable candidate. |
| ABI baseline | `docs/abi.md` and public headers were wrapper-read at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`. Recorded checks include `docs/abi.md` SHA-256 `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b` and `include/ratatoskr/dns.h` SHA-256 `d8d316792368150c6157001c4f5efa7b0420c5cac6ff95d81387cf942ca34ff5`. | Immutable baseline available. |
| Prior binding evidence | Original review and handoff were wrapper-read at `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 respectively `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4` and `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353`. The fresh scoped re-review is at remote `0f0eb9db033f4c26481a302df397184515dc60ad`, review SHA-256 `e5ead3b0fa6e966c50b4a3ed7e0999d4001bb4e1b497629252699673b3354bb8`. | Required input history is immutable and traceable. |
| Scope / gate authority | State records G4 `CHANGES_REQUESTED`, native API design `IN_PROGRESS`, G5/G6 `NOT_STARTED`, and mandatory G12 applicability. The re-review explicitly limits itself to F-BIND-001/F-BIND-002 and disclaims overall G4 and compatibility authority. | Compatibility reviewer may provide only mandatory G4 support evidence; no state/gate advancement is authorized. |
| Live execution check | No live compatibility-reviewer assignment or scheduler execution is recorded in workflow state; historical `IN_PROGRESS`/`CHANGES_REQUESTED` records are not treated as live. | One fresh leaf may be dispatched. |

## Disposition

`READY_TO_ROUTE_ONE_COMPATIBILITY_REVIEWER`. This is a routing finding, not an ABI, source, binding, or behavior compatibility conclusion. The child must independently assess those axes and record its own disposition, without claiming overall G4 authority.

## Model routing

Policy requires `gpt-5.6-sol` / medium for `compatibility-reviewer`. Requested child setting is `gpt-5.6-sol` / medium. The exposed parent route is `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry are unknown. Hermes delegation has no per-task model argument, so the child packet requires truthful actual-route telemetry and rejects any claim that the request itself changed model configuration. One bounded attempt only; any quota/rate-limit error requires immediate stop with no child state/commit changes.
