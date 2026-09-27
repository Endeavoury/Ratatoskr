# G9 resumption 009 preflight verification

**ACTIVE ROLE:** `protocol-orchestrator`.

- Verified repository root `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `hermes/dns-implementation-20260913`, local HEAD and fetched origin ref `d489d749a37548e1e711d11c10b53b2041281bbf`.
- `workflow-state.yaml` records G1–G8 APPROVED and fuzzing/G9 BLOCKED. No state update is made before the leaf result is independently verified.
- The blocking G9 execution-005 artifacts exist and report UBSan index 1024 / ASan stack-buffer-overflow on an 1,133-byte input; record target was not executed. The handoff asks the orchestrator to issue a separately scoped fuzz-engineer remediation and not route G9 security review.
- Current `fuzz/dns/fuzz_dns_name.c` at dispatch baseline already uses `size < sizeof(packet) - 17u ? size : sizeof(packet) - 17u`. Fix commit `2c9e9b945352642d27cf703132e8e5e525b8b5cb` is an ancestor of dispatch baseline, so a new correction may be an authorized no-op rather than an edit.
- The absolute git-agent wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is executable. Nesting permission was supplied: `orchestrator_enabled=true`, `max_spawn_depth=2`; no live delegation existed at assignment start.
- Pre-existing untracked paths were observed through `git status --porcelain=v1` and are excluded from any staging or verification scope.

**Selected route:** exactly one `fuzz-engineer` leaf, `g9-name-harness-bounds-remediation-002`; bounded to one attempt, no child delegation. No campaign, review, or other workflow stage is authorized.