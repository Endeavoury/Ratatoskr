# G3 disposition-partition routing

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Active role | `protocol-orchestrator` |
| Assignment | `g3-disposition-partition-routing-001` |
| Scope | Route exactly one corrective protocol-modeler stage for the open G3 disposition-partition handoff. |
| Repository root / command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline before dispatch | `fa2cf017b2505c0aacae3cacbe65714a960a8e9c` on `hermes/dns-implementation-20260913` |
| Origin / remote delivery ref before dispatch | `https://github.com/Endeavoury/Ratatoskr.git` / `fa2cf017b2505c0aacae3cacbe65714a960a8e9c` |
| Child workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-disposition-partition-001/` |
| Handoff target | Fresh independent G3 review by `protocol-api-designer`; not routed in this assignment. |

## Pre-dispatch evidence

- No live child was reported by `delegate_task list`.
- The repository root, origin, delivery branch, HEAD, clean status, and matching remote ref were verified at dispatch baseline.
- `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` was verified as an executable regular file (`700`) and inspected. It scopes Git identity through `--role`.
- Requested leaf runtime policy: `gpt-5.6-terra` / `medium`. Actual exposed runtime: `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and usage telemetry unknown. No Hermes settings were changed.

The complete leaf packet is `delegations/protocol-modeler-g3-disposition-partition-001.md`. This orchestration assignment does not judge G3 technical correctness or route the reviewer.