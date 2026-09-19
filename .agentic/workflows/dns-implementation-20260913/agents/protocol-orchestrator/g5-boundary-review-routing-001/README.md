# G5 boundary-review routing

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g5-boundary-review-routing-001` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Candidate | `vector-designer/g5-boundary-remediation-001/vector-set.json` at `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6` |

## Authorized bounded scope
Administrative handling and exactly two fresh independent designated G5 reviews of the delivered boundary-remediation candidate: (1) `protocol-test-engineer` exact-byte/coverage and (2) `protocol-analyst` semantic/interpretation. No technical judgment, G5 synthesis, corrective routing, G6, implementation, or later-stage work is authorized here.

## Pre-routing evidence
- Repository root/CWD: `/home/hermes/hermes-workspace/projects/Ratatoskr`; branch `hermes/dns-implementation-20260913`; local and remote tip initially `ea42581d6dfa1207092b24b70331765fd506bb72`.
- The executable role-controlled wrapper is `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` and accepts `--role protocol-orchestrator`.
- Delivery commits `b7d05411cacfeb07be9f6bfbc36f705efdd002c5` and routing/leaf verification `50f10b90ccc0b9ac1029d7559ea9747791fe0e95` exist and are ancestors of HEAD. Candidate SHA-256 reproduces exactly.
- Candidate parses as JSON with 29 cases. DNS-VEC-024 through DNS-VEC-029 are present. The candidate delivery changed only its four assigned vector-designer files and passed `git diff --check`.
- The older reviews target immutable prior candidate SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`; they are not approval of this candidate. Their records remain historical only.

## Independence and routing
The candidate author is `vector-designer/g5-boundary-remediation-001` (delivery author identity `vector-designer`). The two reviews receive disjoint output workspaces and fresh leaf sessions. Each packet prohibits reuse of earlier G5 reviews as an approval and requires an explicit identity/independence declaration against the candidate author and the other reviewer. Their only permitted writes are their own review, README, optional handoff, and completion report.

## Model routing
Requested settings: `openai-codex/gpt-5.6-terra`, `medium` for both reviewer roles under `MODEL_POLICY.md`. Observed parent runtime: `openai-codex/gpt-5.6-terra`; effective effort and usage telemetry unknown. Runtime settings are recorded as requested versus actual; they are not configured by the packets.
