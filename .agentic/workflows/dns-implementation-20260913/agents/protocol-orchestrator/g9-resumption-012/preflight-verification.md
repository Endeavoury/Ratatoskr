# G9 resumption 012 preflight verification

ACTIVE ROLE: `protocol-orchestrator`.

## Commands and observed repository identity

Executed from `/home/hermes/hermes-workspace/projects/Ratatoskr`:

```text
git rev-parse --show-toplevel
git remote get-url origin
git branch --show-current
git rev-parse HEAD
git fetch origin hermes/dns-implementation-20260913
git rev-parse origin/hermes/dns-implementation-20260913
git status --porcelain=v1
```

| Check | Observed value |
| --- | --- |
| Git root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Origin | `https://github.com/Endeavoury/Ratatoskr.git` |
| Branch | `hermes/dns-implementation-20260913` |
| Local HEAD / packet-delivery candidate | `38e347a685767058a1109933960eb96d32bc8d3c` |
| Fetched `origin/hermes/dns-implementation-20260913` | `38e347a685767058a1109933960eb96d32bc8d3c` |
| Immutable workflow source/evidence baseline from state | `42b0611efa90e4b62f06d07cca64044ae9f090a7` |

`git status --porcelain=v1` showed pre-existing unrelated untracked `.agentic` paths. They are preserved; this assignment stages only its own new workspace files.

## Resource-policy prerequisite

Read-only verification of the current required evidence found:

- `agents/protocol-orchestrator/g9-resource-policy-escalation-001/handoffs/dns-g9-resource-policy-to-maintainer-001.md` is `BLOCKED`, `blocking: true`, and its destination resolution remains `Pending maintainer/product decision.`
- `agents/protocol-api-designer/g9-record-resource-assessment-001/api-design.md` and its return handoff are `BLOCKED`; they authorize no candidate private path and require the maintainer decision before a fresh G6 authority assessment.
- `workflow-state.yaml` remains workflow/G9 `BLOCKED` and indexes `DNS-G9-RESOURCE-POLICY-MAINTAINER-001`.
- A workflow-wide `*maintainer*` filename check found only the unresolved escalation handoff and historical API-design maintainer-policy handoff; no returned maintainer decision artifact exists.

## Route decision

The unresolved maintainer/product resource-policy decision is a mandatory blocker. A new campaign would be speculative because the record-target resource failure has no approved numeric policy, revision-bound corrective design, exact private path, or fresh G6 authority. Therefore no fuzz-engineer leaf, G9 security review, binding work, later-stage work, packet, or workflow-state modification is created. The fixed G9 `-rss_limit_mb=1024` remains unchanged.
