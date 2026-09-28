# Delegated task: G9 DNS local fuzz evidence

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-engineer-g9-fuzz-evidence-002-delegation` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target | `protocol/dns` parser robustness |
| Owner role | `protocol-orchestrator/g9-resumption-007` |
| Status | `IN_PROGRESS` |
| Revision | Dispatch baseline `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3` |
| Source artifacts | Current workflow state; G7 and G8 records named below; current LLVM 19 preflight |
| Assumptions | Existing untracked paths are unrelated and must remain untouched. |
| Open questions | None before execution. |
| Limitations | This is a bounded local quality campaign, not a security assessment or exploit exercise. |

ACTIVE ROLE: `fuzz-engineer`

ROLE: `fuzz-engineer/g9-fuzz-evidence-002`

GOAL: Produce fresh, reproducible, bounded execution evidence for the three existing DNS parser fuzz harnesses and submit it for an independent G9 security review.

SCOPE: Authorized local Ratatoskr repository only. Build and execute only the already-existing repository targets `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` against the existing fixed local corpus `fuzz/dns/corpus/`. Do not author or modify fuzz code, corpus, CMake, production code, tests, semantics, vectors, state, or any non-artifact file.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested provider/model/effort: `openai-codex/gpt-5.6-terra/medium`.
- Observed runtime provider/model/effort: inherited child route; record actual metadata if exposed, otherwise `unknown`.
- Verification source: child runtime metadata only; do not infer from this packet.
- Context target: 8,000–16,000 task-specific tokens after complete required reading.
- Completion summary target: 200–400 words plus artifact links.
- User hard token/spend cap: none supplied.
- Attempt policy: one bounded campaign only; no retries after a crash, sanitizer diagnostic, or policy ambiguity.
- Escalation: do not escalate in this assignment; create the required blocking handoff.
- Stop/checkpoint: any crash, sanitizer report, timeout, policy ambiguity, missing prerequisite, or environment/build failure.

## Repository and working directories

- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/`.
- Workspace owner: this fresh fuzz-engineer assignment only.
- Disposable build directory: `/tmp/ratatoskr-g9-fuzz-evidence-002`; do not place build products in the repository.
- Shared source directories: none; all source and corpus paths are read-only.
- Shared-file writer / ordering: none.

## Workflow / stage / assignment

`dns-implementation-20260913` / `fuzzing` / `g9-fuzz-evidence-002`; shared state is `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml` and is read-only.

## Read first

- `AGENTS.md`
- `.hermes/skills/fuzz-engineer/SKILL.md`
- `docs/agentic/HANDOFFS.md`, `DIRECTORIES.md`, `ARTIFACTS.md`, `REVIEW_GATES.md`, `MODEL_POLICY.md`, and `SECURITY_MODEL.md`
- `docs/contributing.md`
- `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` (APPROVED; exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`)
- `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md` (APPROVED; exact candidate `1a371fe8083e72304740d983dcb7f9f6033b6b7f`)
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`
- `fuzz/CMakeLists.txt`, `fuzz/dns/fuzz_dns_packet.c`, `fuzz/dns/fuzz_dns_name.c`, `fuzz/dns/fuzz_dns_record.c`, `fuzz/dns/corpus/README.md`, `fuzz/dns/corpus/seeds.txt`

## Required baseline and commands

First verify local `HEAD` is exactly `f37171a33e62f2ad2c1440ce41295a22596c5ee3`; otherwise stop and hand off without running. Use only `/usr/bin/clang-19`, `/usr/bin/clang++-19`, CMake, and Ninja. Configure exactly:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-fuzz-evidence-002 -G Ninja \
  -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 \
  -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-fuzz-evidence-002 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run each resulting executable only with `fuzz/dns/corpus/`, `-runs=50000`, `-timeout=5`, `-rss_limit_mb=512`, `-max_len=65536`, and a per-target outer timeout of 120 seconds. Redirect stdout/stderr to its separate allowed run log. Record actual elapsed time and exit status. Do not add seed files, dictionaries, artifacts, flags that contact remote systems, or command substitutions that inspect credentials. No network access, remote systems, credentials, scanning, persistence, payload development, or exploitation is permitted.

## Files allowed to change

- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/fuzz-plan.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/logs/configure-build.log`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/logs/ratos_fuzz_dns_packet.log`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/logs/ratos_fuzz_dns_name.log`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/logs/ratos_fuzz_dns_record.log`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/diagnostics/` only for actual sanitizer/crash diagnostics
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/handoffs/g9-fuzz-evidence-to-security-reviewer.md` only after all three runs exit cleanly without sanitizer diagnostics
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/handoffs/g9-fuzz-blocker-to-protocol-orchestrator.md` on any stop condition
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-evidence-002/completion-report.md`

All other repository paths are read-only, including `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`, all code, all tests, all `fuzz/` sources/corpus/CMake files, and other agent workspaces.

## Expected outputs and acceptance

- `fuzz-plan.md`: entrypoints, fixed corpus provenance, invariants, exact sanitizer/build configuration, campaign budget, and stop policy.
- `fuzz-results.md`: baseline, corpus digest/list, exact commands, three individual run statuses, elapsed time, sanitizer/crash disposition, and limitations. It must distinguish no-finding evidence from G9 approval.
- Raw configure/build and individual run logs as listed above.
- If and only if clean evidence exists: a READY_FOR_REVIEW handoff to `security-reviewer` naming every exact artifact and revision, requesting independent G9 review.
- If a stop condition occurs: a BLOCKED handoff to `protocol-orchestrator`, preserving logs/diagnostics and naming the appropriate owner (`c-protocol-implementer` for crash/sanitizer finding; `protocol-orchestrator` for tooling or policy).
- Completion report with required standard fields. Author status is `READY_FOR_REVIEW` only after clean execution; it must never self-approve G9.

## Handoff target

`security-reviewer`, only after qualifying clean executed evidence, via the security handoff above. Otherwise `protocol-orchestrator` via the blocker handoff.

## Delegation allowance

No further delegation.

## Context contract

You have fresh context. Announce and remain `ACTIVE ROLE: fuzz-engineer`; verify scope and prerequisites before writes. Do not alter shared state. Preserve all unrelated untracked paths. Do not commit or push. Do not treat harness success, failure, or sanitizer output as G9 approval.
