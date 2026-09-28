# Delegated task — G9 full DNS fuzz campaign execution 006

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-006-delegation` |
| Workflow / stage / target | `dns-implementation-20260913` / `fuzzing` (G9) / `protocol/dns` |
| Parent | `protocol-orchestrator/g9-resumption-008` |
| Baseline at dispatch | `git:87c2b7a36fdedca2370113093e53633850268a9a` |
| Command cwd / repository | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Artifact workspace | `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-006/` |

ACTIVE ROLE: `fuzz-engineer`.

## Goal and scope

Run exactly one bounded, serial, local-only quality fuzz campaign using only existing targets `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`. This is campaign evidence only; do not self-approve G9 and do not route security review or any later stage.

READ FIRST: `AGENTS.md`; `.hermes/skills/fuzz-engineer/SKILL.md`; `docs/agentic/{HANDOFFS,ARTIFACTS,DIRECTORIES,REVIEW_GATES,SECURITY_MODEL,MODEL_POLICY}.md`; `docs/contributing.md`; workflow state and G7/G8 approval records; this delegation; and `g9-resumption-008/verification/g9-current-toolchain-preflight-008.md`.

## Model, safety, and stopping policy

- Requested model/effort: `openai-codex/gpt-5.6-terra` / medium. Record actual telemetry if exposed; otherwise unknown. No escalation or further delegation.
- No network, external services, remote targets, credentials, scanning, exploitation, persistence, package install, source repair, or any target other than the three named executables.
- One campaign attempt only. Stop at the first unavailable prerequisite, integrity mismatch, sanitizer diagnostic, crash, timeout, nonzero exit, RSS/resource failure, or policy ambiguity. Do not retry or alter limits.
- Preserve unrelated untracked files. Do not clean, reset, stash, merge, rebase, force-push, or write outside the explicit paths.

## Preconditions and command boundaries

Before any campaign work, verify repository root, origin, branch, local/remote baseline, no live specialist campaign, G7/G8 APPROVED and G9 BLOCKED/IN_PROGRESS only for this assignment. Record SHA-256 values for `fuzz/dns/corpus/seeds.txt`, `fuzz/dns/corpus/README.md`, all three `fuzz/dns/fuzz_dns_*.c`, and `fuzz/CMakeLists.txt`. Explicitly verify `/usr/bin/clang-19`, `/usr/bin/clang++-19`, CMake, Ninja, `/usr/bin/timeout`, and the matching fuzzer/ASan/UBSan runtime archives.

Derive corpus only below `/tmp/ratatoskr-g9-full-campaign-execution-006/`: parse each nonempty `seeds.txt` line at its first colon; accept `zero-length:` only as empty bytes; accept `maximum-size:` only with the documented 65535-zero-byte directive; decode remaining values as hex; reject malformed entries. Never mutate the repository corpus.

Configure/build only:

```text
/usr/bin/cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-006/build -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
/usr/bin/cmake --build /tmp/ratatoskr-g9-full-campaign-execution-006/build --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run the three built binaries serially in packet/name/record order, each against a fresh copy of the derived corpus, exactly as:

```text
/usr/bin/timeout 120s <target> <fresh-corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

Record exact invocations, tool versions, input provenance/digests, corpus files/lengths, build results, elapsed time, exit status, diagnostic scan, and explicit per-target crash/no-crash result. If any target fails, later targets remain unexecuted.

## Allowed writes and required output

Only create these files in the unique leaf workspace:

1. `README.md`
2. `fuzz-plan.md`
3. `fuzz-results.md`
4. `handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
5. `completion-report.md`

All production, headers, tests, fuzz sources/corpus/CMake registration, docs, request, manifest, workflow state, and all other agent workspaces are read-only. `/tmp/ratatoskr-g9-full-campaign-execution-006*` is ephemeral evidence only.

A clean three-target campaign returns `READY_FOR_REVIEW` to `protocol-orchestrator` only. Any failure returns `BLOCKED` with a formal handoff and explicitly requests no G9 security review. The wrapper `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` was not verified executable by the parent: do not raw-git commit/push as a substitute; report the delivery limitation.
