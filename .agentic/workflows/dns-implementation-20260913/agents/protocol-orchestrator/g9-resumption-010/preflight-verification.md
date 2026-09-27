# G9 resumption 010 preflight verification

ACTIVE ROLE: `protocol-orchestrator`.

- Verified Git root `/home/hermes/hermes-workspace/projects/Ratatoskr`, origin `https://github.com/Endeavoury/Ratatoskr.git`, branch `hermes/dns-implementation-20260913`, local HEAD and `origin/hermes/dns-implementation-20260913` both `2c6b0bc742d3db88cc94b9e6e354b362ee0f6055`.
- Existing workflow state remains `workflow/fuzzing/G9 = BLOCKED`; G7 and G8 are APPROVED. No state change is made before leaf receipt is verified.
- Verified `g9-fuzz-execution-005` four-output delivery through its dedicated delivery-verification record: it recorded an ASan/UBSan stack-buffer-overflow at `fuzz/dns/fuzz_dns_name.c:12`, clean packet run, and unexecuted record run. Its blocking handoff expressly requests separately scoped fuzz-engineer remediation and no G9 security review.
- Current `fuzz/dns/fuzz_dns_name.c` has `copied = size < sizeof(packet) - 17u ? size : sizeof(packet) - 17u`; terminal writes occupy `12u + copied` through `16u + copied`, so copied at most 1007 yields maximum index 1023. The current source therefore needs a fresh focused no-op validation rather than speculative change.
- Historical `g9-name-harness-bounds-remediation-002` is treated as completed history only, not live authorization or current validation.
- Pre-existing unrelated untracked paths were observed and must not be staged. The wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` is the only commit/push route. Nesting is authorized with one leaf at max depth 2.

Selected route: exactly one fuzz-engineer leaf `g9-name-harness-bounds-remediation-003`; no campaign, review, or later stage.
