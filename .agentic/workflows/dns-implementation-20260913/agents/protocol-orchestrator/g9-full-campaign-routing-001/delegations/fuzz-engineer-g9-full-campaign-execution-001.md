# Delegated task: fresh G9 DNS full fuzz campaign

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-001-delegation` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `fuzzing` (G9) / `g9-full-campaign-execution-001` |
| Owner role | `protocol-orchestrator/g9-full-campaign-routing-001` |
| Status | `IN_PROGRESS` |
| Pre-dispatch baseline | `git:12f0c4941727c6b3069835e00a79416ae42711db` |

ACTIVE ROLE: `fuzz-engineer`

## GOAL AND SCOPE

Execute exactly one fresh, local, bounded, serial G9 campaign against only the existing `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` targets. Record reproducible plan, source/corpus provenance, exact commands/tool versions/budgets/results, and minimized failures if any. The focused name-harness repair reviewed at `git:04715d1771c90b1f8d82686947b5cc1bb96dcf39` is an input, not G9 approval.

Only this campaign is authorized. Do not modify any production source, headers, tests, fuzz source/CMake, tracked corpus, vectors, semantics, docs, workflow state, or prior workspace. No network access, remote target, credential access, scanning, persistence, exploit/payload work, or external service. Use only this repository and ephemeral build/corpus paths under `/tmp`.

## MODEL AND REASONING

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested: `openai-codex/gpt-5.6-terra`, medium. Record actual route/effort if exposed, otherwise `unknown`; a prompt does not change runtime.
- Context/completion target: 8,000–16,000 tokens where practical; 200–400-word completion plus artifact links.
- Attempt policy: one campaign only; no retry after a stop condition. Escalation is a formal handoff to `protocol-orchestrator`, never another leaf or run.

## REPOSITORY AND REQUIRED READING

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch/origin: `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-001/`.
- Ephemeral build/corpus: `/tmp/ratatoskr-g9-full-campaign-execution-001` and `/tmp/ratatoskr-g9-full-campaign-execution-001-corpus`.
- First read `AGENTS.md`; `.hermes/skills/fuzz-engineer/SKILL.md`; `docs/agentic/{HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md,SECURITY_MODEL.md}`; `docs/contributing.md`; workflow state/manifest; the G7 and G8 records below; the focused remediation/review records; toolchain preflight; `fuzz/dns/corpus/{README.md,seeds.txt}` and all three harnesses.
- Before conversion/build/run: derive this packet's commit with `git log -1 --format=%H -- <packet-path>` and require it is an ancestor of `HEAD`; require `git diff --quiet`; verify root/origin/branch and preserve all pre-existing untracked paths.

## REQUIRED INPUTS AND DIGESTS

- G7 APPROVED: `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` (candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`).
- G8 APPROVED: `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`.
- Toolchain: `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`.
- Focused remediation/review: `agents/fuzz-engineer/g9-name-harness-remediation-001/{fuzz-plan.md,fuzz-results.md,handoffs/g9-name-harness-remediation-to-protocol-orchestrator.md,completion-report.md}` and `agents/fuzz-engineer/g9-name-harness-focused-review-001/{reviews/g9-name-harness-focused-review.md,completion-report.md}`.
- Require SHA-256: seeds `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus README `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet harness `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`; name harness `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`; record harness `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

## ALLOWED WRITES AND OUTPUTS

Only write these four repository files:

1. `agents/fuzz-engineer/g9-full-campaign-execution-001/fuzz-plan.md`
2. `agents/fuzz-engineer/g9-full-campaign-execution-001/fuzz-results.md`
3. `agents/fuzz-engineer/g9-full-campaign-execution-001/handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
4. `agents/fuzz-engineer/g9-full-campaign-execution-001/completion-report.md`

All other repository paths are read-only, including `.agentic/workflows/dns-implementation-20260913/workflow-state.yaml`. Use the first-colon corpus decoder: each nonempty seed line must partition on the first `:`; reject missing colon, empty label, duplicate label, unexpected directives; accept `zero-length` only with empty value; accept `maximum-size` only with exact value `repeat 00 to 65535 octets during corpus preparation` and emit 65,535 NUL bytes; otherwise use `bytes.fromhex(value.strip())`. Write converted inputs only under the ephemeral `/tmp` corpus and record labels, filenames, lengths, and decoder command.

## BUILD, BUDGET, STOP, AND HANDOFF

Configure and build only with:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-001 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-001 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run those three targets sequentially, never in parallel, against the same ephemeral corpus. Each command must have `timeout 120s` and libFuzzer `-max_total_time=90 -rss_limit_mb=1024 -timeout=10`. Record elapsed result plus complete stdout/stderr diagnostics and explicit sanitizer/crash/no-crash disposition.

Stop immediately—do not run remaining targets or retry—on any digest/ancestry/cleanliness mismatch, build failure, nonzero exit, sanitizer diagnostic, crash, timeout, UB, or resource diagnostic. Minimize/replay the actual failure only if safe within the same 120-second envelope, retain its reproducible command/input SHA-256 in the four records, and return `BLOCKED` to protocol-orchestrator. Do not route security review.

If all three runs cleanly complete, write a nonblocking `READY_FOR_REVIEW` handoff to protocol-orchestrator requesting later independent G9 security review; do not dispatch it. Before committing, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>`, stage exactly the four outputs, run `git diff --cached --check`, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact remote ref. No merge, force push, or further delegation.
