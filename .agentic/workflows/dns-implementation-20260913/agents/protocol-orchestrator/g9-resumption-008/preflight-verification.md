# G9 resumption 008 preflight verification

| Field | Verified value |
| --- | --- |
| Repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Origin | `https://github.com/Endeavoury/Ratatoskr.git` |
| Branch | `hermes/dns-implementation-20260913` |
| Local HEAD before routing write | `400e818790bf6a8e7f13b7b86cfaf837a11066fc` |
| Origin branch tip before routing write | `400e818790bf6a8e7f13b7b86cfaf837a11066fc` |
| Campaign-source baseline | `400e818790bf6a8e7f13b7b86cfaf837a11066fc` |
| Wrapper | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` (executable; role syntax verified) |
| Live child check | `delegate_task list`: zero live children |
| Toolchain | `/usr/bin/cmake`, `/usr/bin/ninja`, `/usr/bin/clang-19`; prior LLVM19 preflight built all three targets |

ACTIVE ROLE: `protocol-orchestrator`.

The current workflow state records G7 and G8 as APPROVED and G9 as BLOCKED solely because previous G9 leaves stopped before campaign execution. The fixed corpus and all three existing target sources exist at the campaign-source baseline. The packet uses ancestor checks rather than a self-invalidating exact post-dispatch `HEAD` equality check. No project workflow state is changed in this routing commit: it will be updated only after the fresh leaf's output, allowed-path boundary, commit, and remote ref are independently verified.

Pre-existing untracked workspaces were observed and are preserved. No genuine live specialist execution exists; historical status fields are not treated as live work.
