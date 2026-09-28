# DNS G3 semantic-model correction

| Field | Value |
| --- | --- |
| Assignment | `g3-model-correction-001` |
| Active role | `protocol-modeler` |
| Workflow / stage | `dns-implementation-20260913` / modeling corrective return for G3 |
| Target | `protocol/dns` |
| Command working directory | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/protocol-modeler/g3-model-correction-001/` |
| Requested runtime | `gpt-5.6-terra` / medium |
| Actual exposed runtime | `openai-codex` / `gpt-5.6-terra`; reasoning effort and usage unknown |
| Attempt count | One evidence-driven correction attempt |

## Scope

This assignment corrects only the G3 TCP semantic findings: observable incremental consumption and terminal correlated-frame dispositions. It does not author API design, review G3, alter shared workflow state, or modify code, tests, vectors, bindings, docs, request, or manifest.

## Git-delivery blocker

Before leaf artifact work, wrapper discovery found no verified absolute `git-agent` wrapper: `command -v git-agent` returned no path; executable checks at `/usr/local/bin/git-agent`, `/usr/bin/git-agent`, `/bin/git-agent`, `/home/hermes/.local/bin/git-agent`, and `/home/hermes/bin/git-agent` found none; a filename search under `/home/hermes` returned zero matches. Therefore no raw-Git commit or push was used. The corrective candidate is local and requires a verified wrapper for delivery and remote-ref readback.
