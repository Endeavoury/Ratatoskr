# Delegated task: fresh G9 DNS full fuzz campaign (portable measurement)

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-002-delegation` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `fuzzing` (G9) / `g9-full-campaign-execution-002` |
| Target | `protocol/dns`; three existing local DNS fuzz targets only |
| Owner / hierarchy | `protocol-orchestrator/g9-full-campaign-reroute-002`; workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Status | `IN_PROGRESS` |
| Dispatch baseline | `git:cb0918853f8d795c9abe07241a87b03fc90cb229` |

ACTIVE ROLE: `fuzz-engineer`

## Goal and scope

Execute exactly one fresh local, bounded, serial G9 campaign against only `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`. Produce reproducible plan/results, corpus and source provenance, exact commands/budgets/diagnostics, per-target elapsed monotonic time plus RSS measurement, and disposition. The prior campaign (`g9-full-campaign-execution-001`) stopped before launching its first target because it wrapped `/usr/bin/time`, which is absent. Correct that wrapper only: use `/usr/bin/python3` to invoke `/usr/bin/timeout`, measure `time.monotonic()` elapsed time and `resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss` before/after. Do not use `/usr/bin/time`.

No network, services, credentials, scanning, payload/exploit development, persistence, source/CMake/test/fuzz/corpus modification, shared workflow-state write, review routing, or further delegation. Use existing local targets and read-only tracked corpus only. Ephemeral build/corpus/log paths must be under `/tmp`.

## Model and attempt policy

- Read `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested route: `openai-codex/gpt-5.6-terra`, medium. Effective model is `gpt-5.6-terra`; effort setting is unavailable. Record actual effort as `unknown`; never invent it.
- One campaign only. No retry after any stop condition. Escalation is one formal handoff to `protocol-orchestrator`, never another leaf or run.

## Repository, reading, and inputs

- Root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch/origin: `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git`.
- Your workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-002/`.
- Build/corpus directories: `/tmp/ratatoskr-g9-full-campaign-execution-002` and `/tmp/ratatoskr-g9-full-campaign-execution-002-corpus`.
- Read first: `AGENTS.md`; `.hermes/skills/fuzz-engineer/SKILL.md`; `docs/agentic/{HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md,SECURITY_MODEL.md}`; `docs/contributing.md`; workflow state; `manifest.yaml`; the G7/G8 records below; `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`; prior full-campaign packet/results/handoff/completion; `agents/protocol-orchestrator/g9-resumption-009/`; name-harness remediation/review; `fuzz/dns/corpus/{README.md,seeds.txt}`; all three harnesses; `fuzz/CMakeLists.txt`.
- Before conversion/build/run: verify repository root/origin/branch; `git log -1 --format=%H -- <this-packet>` is an ancestor of HEAD; `git diff --quiet`; preserve all pre-existing untracked paths.
- Required approvals: `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` (candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`) and `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`.
- Require SHA-256: `fuzz/dns/corpus/seeds.txt` `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet harness `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`; name harness `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`; record harness `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

## Allowed writes and outputs

Write only these four repository files:

1. `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-plan.md`
2. `agents/fuzz-engineer/g9-full-campaign-execution-002/fuzz-results.md`
3. `agents/fuzz-engineer/g9-full-campaign-execution-002/handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
4. `agents/fuzz-engineer/g9-full-campaign-execution-002/completion-report.md`

Every other repository path is read-only, including all source, fuzz harnesses/CMake, corpus, prior artifacts, and `workflow-state.yaml`.

Decode the fixed local seed descriptions under the `/tmp` corpus using first-colon partition: reject missing colon, empty/duplicate label, and unexpected directive; permit `zero-length:` only with empty value; permit `maximum-size` only with exact value `repeat 00 to 65535 octets during corpus preparation` and emit 65,535 NUL bytes; otherwise `bytes.fromhex(value.strip())`. Record labels, filenames, lengths, SHA-256 values, and decoder command.

## Build and run

Build exactly:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-002 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-002 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run targets sequentially, no parallelism, with exactly these flags inside a Python portable measurement wrapper:

```text
/usr/bin/timeout 120s <target> <ephemeral-corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

The wrapper must record target command, return code, elapsed monotonic seconds, child `ru_maxrss` before/after/delta/units, complete stdout/stderr, and explicit sanitizer/crash/no-crash disposition. Do not alter target arguments. `/usr/bin/timeout` and `/usr/bin/python3` exist; `/usr/bin/time` does not and must not be invoked.

Stop immediately, with no remaining target and no retry, on any provenance/ancestry/cleanliness mismatch, build failure, nonzero result, sanitizer/crash/UB, timeout, or resource diagnostic. If all three runs are clean, write `READY_FOR_REVIEW` artifacts and a nonblocking handoff to `protocol-orchestrator` requesting later independent G9 security review; do not dispatch it. Otherwise return `BLOCKED` to `protocol-orchestrator`; do not route security review.

## Delivery

Before commit, stage exactly the four output files. Use only:

```text
/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>
```

Run `git diff --cached --check`; push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; perform exact `git ls-remote` readback. No merge, force push, master push, raw commit/push, or state update.

## Handoff and completion

Handoff target: `protocol-orchestrator`, at your listed handoff path. Use the standard handoff/completion templates and make the packet self-contained. Report `READY_FOR_REVIEW` only for clean authored campaign evidence, never a technical G9 approval. No further delegation.