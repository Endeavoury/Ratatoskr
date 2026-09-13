# G3 DNS semantic-model correction routing

| Field | Value |
| --- | --- |
| Workflow | `dns-implementation-20260913` |
| Stage | modeling / G3 corrective return |
| Coordinator role | protocol-orchestrator |
| Assignment | `g3-model-correction-routing-001` |
| Repository root / command directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Baseline verified | `b6a47963736aaf759bc427f2e5a47aaa8e3c170a` on `hermes/dns-implementation-20260913` |
| Origin / verified remote ref | `https://github.com/Endeavoury/Ratatoskr.git` / `b6a47963736aaf759bc427f2e5a47aaa8e3c170a` |
| Scope | One bounded modeler correction for `DNS-HO-API-001-G3-TCP`; no G3 review dispatch and no G4 advancement. |

## Inputs verified

- `workflow-state.yaml`: modeling and G3 are `CHANGES_REQUESTED`; `DNS-G3-MODEL-TCP-BLOCK` remains active.
- G3 review and return handoff in `protocol-api-designer/g3-api-001`.
- G2 model and approval, and approved analysis revision `5615caed0b7ad0a321d6794e71b79c4195e90384`.
- Clean initial worktree and matching remote ref were verified before local routing writes.

## Boundary

The coordinator may write only this workspace and workflow-root `workflow-state.yaml`. The sole child owns only its newly assigned modeler workspace and the handoff destination-resolution section. Reviewer artifacts, specialist truth outside the child workspace, code, API design, tests, vectors, docs, request, and manifest remain read-only.

## Delivery prerequisite

No absolute `git-agent` wrapper was discovered before delegation: `PATH` lookup and checked paths `/usr/local/bin/git-agent`, `/usr/bin/git-agent`, `/home/hermes/.local/bin/git-agent`, and `/home/hermes/bin/git-agent` were absent; filesystem name search under `/home/hermes` returned no candidate. The delegated modeler must independently recheck and record the result. Without an absolute verified wrapper, it must record a blocker and must not substitute raw Git identity, commit, or push.
