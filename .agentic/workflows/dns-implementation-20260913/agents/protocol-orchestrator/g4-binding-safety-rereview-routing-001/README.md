# G4 binding-safety re-review routing

- **Workflow / target:** `dns-implementation-20260913` / `protocol/dns`
- **Role / assignment:** `protocol-orchestrator / g4-binding-safety-rereview-routing-001`
- **Scope:** Route exactly one fresh independent binding-safety re-review of the delivered remediation candidate, limited to `F-BIND-001` and `F-BIND-002`.
- **Repository root and command directory:** `/home/hermes/hermes-workspace/projects/Ratatoskr`
- **Baseline before routing artifacts:** `232940996939a2316e6b55f708e0f99bb9b621a4`; branch `hermes/dns-implementation-20260913`; origin `https://github.com/Endeavoury/Ratatoskr.git`.
- **Candidate:** `../protocol-api-designer/g4-binding-safety-remediation-001/api-design.md` at delivery commit `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`.
- **Boundary:** No compatibility review, G4 overall approval, implementation, headers, tests, bindings, docs, vectors, or later-stage routing. Compatibility review remains independently mandatory.
- **Allowed orchestrator writes:** this directory and `workflow-state.yaml` only after exact leaf remote delivery verification.
- **Delivery rule:** Every commit/push uses `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role <role> -- ...`, pushes `HEAD:refs/heads/hermes/dns-implementation-20260913`, then fetches/reads that exact remote ref. No raw-Git substitute.
