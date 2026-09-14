# G4 compatibility re-review preflight evidence

| Check | Evidence | Result |
| --- | --- | --- |
| Repository identity | `/home/hermes/hermes-workspace/projects/Ratatoskr`; origin `https://github.com/Endeavoury/Ratatoskr.git`; branch `hermes/dns-implementation-20260913` | Verified before routing. |
| Routing baseline | Local `HEAD` and wrapper-read `origin/hermes/dns-implementation-20260913` | Both `fb766f3deb0bc0b549c612a5d59eee08d4992b3d`. |
| Candidate existence/integrity | `git show e3c63fdb0766afc86d28fc32ec3071d1e7ec762c:<candidate path> | sha256sum` | `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`; matches completion/state. |
| Candidate boundary | Commit `e3c63fdb0766afc86d28fc32ec3071d1e7ec762c` names only candidate workspace `README.md`, `api-design.md`, and maintainer handoff; `git diff --check` | Verified; no realization or shared-state change in candidate commit. |
| Candidate status | `agents/protocol-api-designer/g4-compatibility-remediation-001/{api-design.md,completion-report.md}` | `READY_FOR_REVIEW`; completion requires fresh independent compatibility re-review. |
| Original support review | `agents/compatibility-reviewer/g4-compatibility-review-001/{compatibility-report.md,reviews/g12-g4-compatibility-support-review.md}` at delivery `0cb6e27b265c38e42d09d61c0883f1a086df8835` | `CHANGES_REQUESTED`, blocking `C-COMP-001`; original reviewer cannot review corrective candidate. |
| Return handoff | `agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/g4-compatibility-to-api-designer-c-comp-001.md` | Resolution names the corrective candidate and explicitly says fresh independent compatibility re-review is required; it does not approve G4. |
| ABI baseline | `include/ratatoskr/dns.h` and `docs/abi.md` at `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | Both objects exist. |
| Earlier approvals | workflow state G1/G2/G3 `APPROVED`; G4 rationale/state | G4 remains `CHANGES_REQUESTED`; `native_api_design` remains `IN_PROGRESS`; fresh re-review is unassigned. |
| Independence boundary | Candidate author `protocol-api-designer / g4-compatibility-remediation-001`; original reviewer `compatibility-reviewer / g4-compatibility-review-001` | Leaf packet requires a new child identity independent of both and every candidate/original-review subject author. |
| Unrelated worktree content | `git status --short` before writes | Pre-existing untracked `agents/binding-api-designer/g4-binding-safety-rereview-001/` observed; excluded from all writes/commits. |

No quota/rate-limit condition was observed during preflight. The required input set is sufficient to route one leaf; this preflight makes no technical compatibility disposition.