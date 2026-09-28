# Delegated task — G9 corrective DNS full fuzz campaign execution 004

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-004-delegation` |
| Root task / project / hierarchy | `dns-implementation-20260913-resumption` / Ratatoskr / workspace-orchestrator → protocol-orchestrator → fuzz-engineer leaf |
| Workflow / stage / target | `dns-implementation-20260913` / `fuzzing` (G9) / `protocol/dns` |
| Owner / initial status | `fuzz-engineer/g9-full-campaign-execution-004` / `IN_PROGRESS` |
| Dispatch baseline | `git:464702783c7174212644a4d6416a72958c057cae`; verify the committed packet is an ancestor of local HEAD and fetched origin before execution |
| Limitations | Campaign evidence only; never G9 approval |

ACTIVE ROLE: `fuzz-engineer`.

## ROLE, GOAL, and SCOPE

ROLE: fresh `fuzz-engineer` leaf, unique from every prior G9 assignment.

GOAL: execute exactly one bounded, deterministic, local-only campaign over only the existing `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record` targets, then return reproducible evidence to the protocol orchestrator.

SCOPE: no network/remote target, credentials, scanning, exploit or payload work, source fix, harness/CMake/corpus/test/API/vector/workflow-state edit, review routing, binding, documentation, package install, merge, or master operation. Do not retry after any campaign failure. Preserve all existing untracked artifacts.

## MODEL, BUDGET, AND STOP POLICY

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested route: `openai-codex/gpt-5.6-terra`, reasoning `medium`.
- Record actual inherited provider/model/effort only if telemetry exposes it; otherwise `unknown`.
- One configure/build and one serial run per target; no escalation, re-run, repair, or extra role.
- For each target, use exactly `/usr/bin/timeout 120s <target> <fresh-corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10`.
- On a quota or rate-limit error: stop immediately, make no changes, and report exactly `QUOTA_OR_RATE_LIMIT`.
- On any prerequisite mismatch, build failure, sanitizer diagnostic, crash, nonzero exit, timeout, or RSS/resource diagnostic: record factual `BLOCKED` results/handoff/completion in your workspace, stop without fixes or later-role routing.

## REPOSITORY, WORKSPACE, AND WRITE BOUNDARY

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch/origin: `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git`.
- Your unique workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-004/`.
- Allowed repository files only:
  1. `README.md`
  2. `fuzz-plan.md`
  3. `fuzz-results.md`
  4. `handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
  5. `completion-report.md`
  under that workspace.
- Allowed ephemeral paths only: `/tmp/ratatoskr-g9-full-campaign-execution-004*` for build, logs, copied corpus, and an auditable converter. No repository-root artifacts may remain.
- All other repository paths are read-only, including `workflow-state.yaml`, tracked corpus, `fuzz/`, production, headers, tests, vectors, docs, bindings, and other workspaces.

## READ FIRST

1. `AGENTS.md` and this full packet.
2. `.hermes/skills/fuzz-engineer/SKILL.md`.
3. `docs/agentic/{WORKFLOW.md,ROLES.md,HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,DIRECTORIES.md,MODEL_POLICY.md,SECURITY_MODEL.md}` and `docs/contributing.md`.
4. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,request.md,manifest.yaml}`.
5. G7: `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`; G8: `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`.
6. `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`, `agents/protocol-orchestrator/g9-execution-routing-002/completion-report.md`, and all relevant prior G9 execution plan/results/handoffs, particularly `agents/fuzz-engineer/g9-full-campaign-execution-002/` and `g9-full-campaign-execution-003/`.
7. `fuzz/dns/corpus/{README.md,seeds.txt}`, `fuzz/dns/fuzz_dns_{packet,name,record}.c`, and `fuzz/CMakeLists.txt`.

## REQUIRED PRE-FLIGHT AND INPUT INTEGRITY

Before any write or execution, verify/record Git root, origin, branch, local HEAD, fetched origin ref, packet ancestry, pre-existing untracked paths, no live G9 worker, G7/G8 approved and G9 not approved. Verify exact SHA-256 values:

- `fuzz/dns/corpus/seeds.txt`: `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`
- `fuzz/dns/corpus/README.md`: `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`
- packet/name/record harnesses: `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`, `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`, `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`
- `fuzz/CMakeLists.txt`: `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

Verify `/usr/bin/clang-19`, `/usr/bin/clang++-19`, CMake, Ninja, `/usr/bin/timeout`, and matching LLVM19 fuzzer/ASan/UBSan runtimes. No substitute compiler or toolchain is allowed.

## CORPUS, BUILD, AND RUN

Create a fixed derived corpus under `/tmp`. Parse every `seeds.txt` line with first-colon semantics (`label, separator, value = line.partition(':')`), never `': '` parsing. Reject missing/duplicate/empty labels and unsupported directives. Permit literal `zero-length:` with empty payload; turn exact `maximum-size: repeat 00 to 65535 octets during corpus preparation` into 65,535 NUL bytes; otherwise decode stripped hexadecimal. Record source provenance, converter algorithm/digest, output filenames, sizes, SHA-256s, totals.

Configure/build only:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-004/build -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-004/build --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run packet, then name, then record serially. Use a fresh copied fixed corpus for every target. Capture full stdout/stderr plus monotonic elapsed time and child `ru_maxrss` using a safe local Python wrapper; `/usr/bin/time` is prohibited. Scan evidence for sanitizer/crash/resource markers. Stop at first failure and mark later targets unexecuted.

## OUTPUTS, HANDOFF, AND DELIVERY

Create all five allowed files with template metadata, exact commands/results, tool versions, input and corpus digests, budget, limitations, actual route telemetry, and standard completion fields. Your handoff targets `protocol-orchestrator/g9-corrective-full-campaign-routing-004`. It may be `READY_FOR_REVIEW` only if all three bounded runs are clean; otherwise it is `BLOCKED`. Do not approve G9 and do not dispatch security review.

Before delivery, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git args>` for add/commit/push. Stage exactly your five files, run cached diff check, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, never merge/force-push/push master, then read back the exact remote ref and record it. No further delegation.
