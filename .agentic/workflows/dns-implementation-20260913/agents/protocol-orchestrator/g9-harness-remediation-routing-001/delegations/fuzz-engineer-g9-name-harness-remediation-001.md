# Delegated task: G9 DNS name-harness remediation 001

| Field | Value |
| --- | --- |
| Workflow / stage / assignment | `dns-implementation-20260913` / fuzzing (G9) / `g9-name-harness-remediation-001` |
| Parent / role | `protocol-orchestrator/g9-harness-remediation-routing-001` |
| Status at dispatch | Corrective harness stage only; G9 remains BLOCKED and is not approved |
| Repository root and command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Branch / origin / dispatch baseline | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` / `f90c9bd80217cddb0e036d4dc0d8914f0cd32927` |
| Unique artifact workspace | `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/` |

## ACTIVE ROLE and mandatory reading

ACTIVE ROLE: `fuzz-engineer`. This is a fresh leaf assignment, independent of the author of `fuzz-engineer/g9-fuzz-execution-005`; do not delegate.

Before writes, read:
- `/home/hermes/hermes-workspace/projects/Ratatoskr/AGENTS.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.hermes/skills/fuzz-engineer/SKILL.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/docs/agentic/{HANDOFFS,ARTIFACTS,REVIEW_GATES,DIRECTORIES,MODEL_POLICY,SECURITY_MODEL}.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/docs/contributing.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/fuzz-results.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/handoffs/g9-fuzz-execution-to-protocol-orchestrator.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-008/verification/g9-fuzz-execution-005-delivery-verification.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/fuzz/dns/fuzz_dns_name.c`, `/home/hermes/hermes-workspace/projects/Ratatoskr/fuzz/dns/corpus/README.md`, and `/home/hermes/hermes-workspace/projects/Ratatoskr/fuzz/dns/corpus/seeds.txt`.

## Goal and scope

Examine the reported off-by-one in `/home/hermes/hermes-workspace/projects/Ratatoskr/fuzz/dns/fuzz_dns_name.c:12` where a 1,133-byte input writes past `uint8_t packet[1024]`. Implement the minimal correct bound-safe fuzz-harness remediation, then run a focused bounded local verification using only the explicit LLVM 19 toolchain. This task is not a full G9 campaign and must not claim one.

## Permitted writes and prohibitions

Your only permitted source write is exactly:
- `/home/hermes/hermes-workspace/projects/Ratatoskr/fuzz/dns/fuzz_dns_name.c`

Your only permitted artifact writes are exactly:
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/README.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-plan.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-results.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/handoffs/g9-name-harness-remediation-to-protocol-orchestrator.md`
- `/home/hermes/hermes-workspace/projects/Ratatoskr/.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/completion-report.md`

Everything else is read-only. Do not modify CMake, tests, corpus, headers, production code, docs, state, manifests, other workspaces, or unrelated untracked files. No network, packages, unrelated targets, broad source changes, security review routing, G9 approval, merge, force push, or master/main work.

## Required verification

Before changes, verify actual root, origin, branch, HEAD, remote target ref, clean tracked diff, and preserve existing untracked paths. Verify `/usr/bin/clang-19` and `/usr/bin/clang++-19` are usable; do not use unversioned compilers.

Configure a disposable build directory under `/tmp` only with:
```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-name-harness-remediation-001 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-name-harness-remediation-001 --target ratos_fuzz_dns_name --parallel 2
```

Replay a fixed existing or derived local corpus that includes the reported 1,133-byte reproducer condition and verify the fixed target exits cleanly with sanitizer instrumentation. Keep corpus/build/log data in `/tmp`; bounded local execution only. Record exact commands, input provenance/lengths, results, sanitizer outcome, source and artifact revisions, limitations, and the fact that packet/record targets and full G9 campaign were not run.

## Handoff and git

Write `READY_FOR_REVIEW` only if focused remediation verification is clean; otherwise write `BLOCKED`. In either case, hand off only to `protocol-orchestrator`; do not route a G9 security review.

For every Git operation use only this wrapper from the repository cwd:
```text
/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>
```
On quota/rate error, stop immediately with no state changes. On any other wrapper failure, retain accurate local artifacts and report BLOCKED.

If clean and deliverable, stage exactly these five paths — the source plus the four formal reports — and no other path:
1. `fuzz/dns/fuzz_dns_name.c`
2. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-plan.md`
3. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/fuzz-results.md`
4. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/handoffs/g9-name-harness-remediation-to-protocol-orchestrator.md`
5. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-name-harness-remediation-001/completion-report.md`

`README.md` is an allowed local artifact but is not among the five authorized staged paths. Run a cached-diff boundary check; commit; push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; then read back the exact origin ref. Never stage unrelated pre-existing untracked paths.

Acceptance: minimal bound-safe harness change; focused clang-19 build and replay clean; formal evidence/handoff accurately records scope and limitations; role-scoped commit/push/readback succeeds. Next responsible role after a clean handoff is an independently assigned focused fuzz verification/review; it is not a G9 security review at this stage.