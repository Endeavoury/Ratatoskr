# G7 configured-limits re-review routing 002

ACTIVE ROLE: `protocol-orchestrator`

## Scope

Resume exactly one ready stage: a fresh independent G7 review of DNS-G8-001 remediation candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`. This workspace owns only routing, preflight, delivery verification, and completion records. The sole permitted leaf is `protocol-test-engineer/g7-configured-limits-rereview-002`.

No G8, G9, or later work is routed by this assignment. The orchestrator records only the designated leaf disposition; it does not assess or change technical truth.

## Baseline

- Repository: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Branch/ref: `hermes/dns-implementation-20260913`
- Local HEAD and remote-tracking ref at preflight: `a4fff37070604df1d01e03e302d545cbec2647c1`
- Candidate: `1a371fe8083e72304740d983dcb7f9f6033b6b7f`, verified ancestor of HEAD.
- Required wrapper: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`

## Boundaries

Allowed orchestrator writes are this workspace and workflow-root `workflow-state.yaml`. The leaf owns only its fresh workspace and may use the narrowly listed optional test paths only after strict necessity inspection. Production source, public headers, canonical truth, prior reviewer artifacts, and later-stage routing are forbidden.
