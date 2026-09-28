# G9 fuzz routing preflight verification

| Field | Observed evidence |
| --- | --- |
| Workflow/stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Verified repository root | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / local HEAD | `hermes/dns-implementation-20260913` / `a4ae4e3fd94871bba4d5644b4edff891ae213047` |
| Origin / remote ref | `https://github.com/Endeavoury/Ratatoskr.git` / `origin/hermes/dns-implementation-20260913 = a4ae4e3fd94871bba4d5644b4edff891ae213047` |
| G7 prerequisite | APPROVED record at `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`, exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`, delivery `510b5a131bcb3272caeb7eb1821444b35644cfcd` |
| G8 prerequisite | APPROVED record at `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`, exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`, delivery `5d81f9f26945ad9f80f5b818bf6b147f6b37bfff` |
| Existing fuzz inputs | `fuzz/CMakeLists.txt`; `fuzz/dns/fuzz_dns_{packet,name,record}.c`; `fuzz/dns/corpus/{README.md,seeds.txt}` exist at dispatch baseline |
| Existing DNS inputs | `src/protocols/dns/{dns_parser.c,dns_packet.c,dns_builder.c,dns_client.c,dns_transport_udp.c,dns_transport_tcp.c}` exist at dispatch baseline |
| Working-tree preservation | Untracked `.agentic/dns-g8-orchestrator-prompt.txt` and prior-agent workspace directories were present before this routing and are outside the assignment scope. No tracked diff or staged diff was present. |
| Delivery wrapper | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`: present, executable, source-inspected; role allowlist includes `protocol-orchestrator` and `fuzz-engineer`; it invokes Git with role-scoped author identity. Its usage command ran successfully (exit 2 is expected for missing arguments). |

## Result

G7 and G8 are explicitly APPROVED in current workflow state, their designated records identify the same configured-limits candidate, and G9 is applicable and `NOT_STARTED`. The narrow ready route is exactly one fuzz-engineer authoring assignment. The routing packet is `delegations/fuzz-engineer-g9-fuzz-evidence-001.md`; it records exact inputs, branch delivery constraints, model request/actual inherited route, allowed paths, no-self-approval rule, and the required independent G9 security-review handoff.

This preflight does not assess fuzz strategy, harness correctness, campaign results, or G9 technical acceptance.
