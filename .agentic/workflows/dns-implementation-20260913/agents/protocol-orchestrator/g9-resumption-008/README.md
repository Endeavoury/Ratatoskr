# G9 resumption 008

ACTIVE ROLE: `protocol-orchestrator`.

This assignment reconciles the contradictory versioned-LLVM and PATH-only G9 preflights. It owns only the fresh preflight, one fuzz-engineer delegation, an administrative state transition justified by that preflight, and coordination completion evidence.

- Workflow/stage: `dns-implementation-20260913` / `fuzzing` (G9)
- Repository and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`
- Baseline before preflight: local and origin `87c2b7a36fdedca2370113093e53633850268a9a`
- Allowed writes: this workspace and `workflow-state.yaml` only.
- Prohibited: production, headers, tests, fuzz sources/corpus/CMake registration, docs, manifest/request, other-role workspaces, G9 review, and later stages.
- Model policy: requested `openai-codex/gpt-5.6-terra` / medium for the fuzz leaf; current runtime exposes `openai-codex/gpt-5.6-terra`, reasoning telemetry unavailable.
- Git delivery: no executable absolute git-agent wrapper was found. No raw-git commit or push is permitted.
