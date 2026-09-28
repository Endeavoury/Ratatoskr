# Delegated task: fresh G9 DNS fuzz execution after corpus-decoder blocker

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-004-delegation` |
| Workflow ID / stage / assignment | `dns-implementation-20260913` / `fuzzing` (G9) / `g9-fuzz-execution-004` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator/g9-corpus-decoder-routing-001` |
| Status | `IN_PROGRESS` |
| Routing-commit rule | Determine the commit adding this packet with `git log -1 --format=%H -- <this packet path>`; it must be an ancestor of `HEAD` before execution. |
| Assumptions | G7 and G8 remain APPROVED; all pre-existing untracked paths are unrelated and must remain untouched. |
| Limitations | One local bounded campaign only; this assignment cannot approve G9. |

ACTIVE ROLE: fuzz-engineer

## Goal and scope

Run exactly one reproducible local libFuzzer campaign against only the existing `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` targets. Produce fresh plan/results and a handoff for independent G9 assessment only if all three runs are clean. Do not author or modify production code, headers, tests, fuzz sources, fuzz CMake, tracked corpus, vectors, semantics, workflow state, or public docs.

Authorized environment is solely `/home/hermes/hermes-workspace/projects/Ratatoskr`, with ephemeral build/corpus only under `/tmp`. No network, remote systems, credentials, scanning, persistence, payload/exploit work, or external services. Stop and hand off on any crash, sanitizer finding, build failure, policy uncertainty, input mismatch, or safety-envelope violation. No retries after a stop condition.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested: `openai-codex/gpt-5.6-terra`, medium; record actual runtime metadata if exposed, otherwise `unknown`.
- One campaign; no further delegation. Escalation is a handoff to the orchestrator, never a retry.

## Repository and directories

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch: `hermes/dns-implementation-20260913`; expected origin: `https://github.com/Endeavoury/Ratatoskr.git`.
- Packet path: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-corpus-decoder-routing-001/delegations/fuzz-engineer-g9-fuzz-execution-004.md`.
- Before any build/run, derive its committed routing commit with `git log -1 --format=%H -- "$packet"`; require nonempty output and `git merge-base --is-ancestor "$routing_commit" HEAD`.
- Require `git diff --quiet`; pre-existing untracked paths do not authorize writes and must be preserved.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-004/`.
- Ephemeral build: `/tmp/ratatoskr-g9-fuzz-execution-004`; ephemeral corpus: `/tmp/ratatoskr-g9-fuzz-execution-004-corpus`.

## Read first

1. `AGENTS.md`; `.hermes/skills/fuzz-engineer/SKILL.md`.
2. `docs/agentic/{HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,MODEL_POLICY.md,DIRECTORIES.md,SECURITY_MODEL.md}` and `docs/contributing.md`.
3. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`.
4. G7 `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`; G8 `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`; toolchain preflight `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`.
5. `fuzz/dns/corpus/{README.md,seeds.txt}` and the three `fuzz/dns/fuzz_dns_*.c` harnesses.

## Required input integrity

Before conversion, record and require exact SHA-256 values:

- `fuzz/dns/corpus/seeds.txt`: `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`
- `fuzz/dns/corpus/README.md`: `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`
- `fuzz/dns/fuzz_dns_packet.c`: `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`
- `fuzz/dns/fuzz_dns_name.c`: `f30ad35561305843882bb79a43af5a2ecf392fb74d7ca8b8c769dc59bbc3c4b0`
- `fuzz/dns/fuzz_dns_record.c`: `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`
- `fuzz/CMakeLists.txt`: `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`

## Only allowed repository writes

- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-004/fuzz-plan.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-004/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-004/handoffs/g9-fuzz-execution-to-security-reviewer.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-004/completion-report.md`

Everything else is read-only. Do not create repository build products, logs, corpus files, or any output beyond those four files. Do not edit `workflow-state.yaml`.

## Mandatory ephemeral corpus conversion

After digest verification, use this exact safe parsing behavior in an ephemeral Python script or `python3 -c` command, recording the exact command used: read nonempty lines, partition at the first `:`, reject a missing colon or empty label, accept `zero-length` only with an empty value, accept `maximum-size` only with exact value `repeat 00 to 65535 octets during corpus preparation` and write `b'\\0' * 65535`, and use `bytes.fromhex(value.strip())` for every other label. Reject duplicate labels and reject unexpected textual directives. Write only to the `/tmp` corpus directory and record filenames plus byte lengths.

## Build and runs

Use only LLVM 19 and existing targets:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-fuzz-execution-004 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-fuzz-execution-004 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run the three built targets sequentially against the same ephemeral corpus. Each invocation must have a 120-second OS wall guard and libFuzzer flags `-max_total_time=90 -rss_limit_mb=1024 -timeout=10`. Record exact commands, tool versions, configure/build outcome, corpus statistics, each elapsed result, stdout/stderr diagnostics, and explicit crash/no-crash disposition. No target may run in parallel.

## Outputs and acceptance

- `fuzz-plan.md`: target/invariant mapping, source provenance, sanitizer/build settings, budgets, and failure policy.
- `fuzz-results.md`: integrity checks, exact conversion evidence, build evidence, and all three run outcomes.
- Handoff: `READY_FOR_REVIEW`, nonblocking, and requests an independent security-reviewer G9 assessment only if all three builds/runs cleanly complete; otherwise `BLOCKED`, names the blocker owner, and explicitly requests no review.
- Completion: `READY_FOR_REVIEW` only after three clean runs; otherwise `BLOCKED`.

Before committing use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>` for Git actions. Verify branch/origin, stage exactly the four allowed outputs, run `git diff --cached --check`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact ref. No merge or force push.

HANDOFF TARGET: protocol-orchestrator, with security-reviewer conditional as above.

DELEGATION ALLOWANCE: none.