# Delegated task — G9 full DNS fuzz campaign execution 003

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-003-delegation` |
| Workflow / stage / target | `dns-implementation-20260913` / `fuzzing` (G9) / `protocol/dns` |
| Owner role / status | `protocol-orchestrator` / `IN_PROGRESS` on leaf start only |
| Baseline | `git:0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4` |
| Source artifacts | G7/G8 approvals; `g9-resumption-006` toolchain preflight; `g9-resumption-010` receipt; current workflow state |
| Assumptions | LLVM19 toolchain and named inputs remain available at leaf start; validate them yourself. |
| Limitations | This is campaign evidence only, not G9 approval. |

ACTIVE ROLE: `fuzz-engineer`.

## ROLE, GOAL, and scope

ROLE: `fuzz-engineer/g9-full-campaign-execution-003`, a fresh leaf unique from every prior G9 fuzz assignment.

GOAL: Perform one complete, bounded, deterministic, local-only G9 campaign across the existing DNS `packet`, `name`, and `record` fuzzer targets; produce reproducible plan/results and a handoff for later receipt verification.

SCOPE: Use only the existing local Ratatoskr repository and three existing quality-test targets. No network access, remote targets, credentials, scanning, payload development, persistence, exploitation, G9 security review, bindings, or later-stage work. Do not implement a source fix. A sanitizer/resource failure is evidence: preserve it and hand off; do not repair, change the budget, rerun beyond the specified stop policy, or self-review.

## MODEL AND REASONING

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested provider/model: `openai-codex/gpt-5.6-terra`.
- Requested reasoning effort: `medium`.
- Observed runtime provider/model/effort: record only actual telemetry, otherwise `unknown`; a prompt does not configure it.
- Context/completion targets: required reading complete; 200–400 word completion plus artifacts.
- User hard token/spend cap: none supplied.
- Attempt policy: one campaign attempt; no retry after any sanitizer/crash/timeout/RSS failure.
- Escalation: stateful generation or difficult minimization would normally escalate to Sol/high, but this packet authorizes no escalation or second attempt.
- Stop/checkpoint: missing approval/input/toolchain, baseline/ref divergence, any boundary conflict, or first campaign failure.

## REPOSITORY AND WORKING DIRECTORIES

- Repository root and command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Unique artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-full-campaign-execution-003/`.
- Shared source/corpus writes: **none**. Create derived deterministic corpus and all configure/build/log/reproducer material only below a fresh `/tmp/ratatoskr-g9-full-campaign-execution-003*` directory; do not write repository corpus.
- Only the protocol-orchestrator writes `workflow-state.yaml`. Do not modify it.
- Preserve all pre-existing unrelated untracked paths. Do not clean, reset, stash, merge, rebase, force-push, update master, or alter another agent’s workspace (except no destination resolution is assigned here).

## READ FIRST

1. `AGENTS.md`
2. `.hermes/skills/fuzz-engineer/SKILL.md`
3. `docs/agentic/{HANDOFFS.md,ARTIFACTS.md,DIRECTORIES.md,REVIEW_GATES.md,SECURITY_MODEL.md,MODEL_POLICY.md}` and `docs/contributing.md`
4. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,request.md,manifest.yaml}`
5. `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-011/{README.md,preflight-verification.md}` and this packet
6. `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`
7. `agents/protocol-orchestrator/g9-resumption-010/{preflight-verification.md,verification/g9-name-harness-bounds-remediation-003-delivery-verification.md}`
8. `agents/fuzz-engineer/g9-full-campaign-execution-002/{fuzz-plan.md,fuzz-results.md,handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md}` and `agents/fuzz-engineer/g9-fuzz-execution-005/fuzz-results.md`

## Required integrity/precondition evidence

Before any write, verify and record: Git root, origin URL, branch, local HEAD, fetched `origin/hermes/dns-implementation-20260913`, and that all equal baseline `0a8fc53cd645609dfa5eda51e53f98c2ea2c2ea4`; no live specialist execution; existing unrelated untracked paths preserved; and current G7/G8 approved/G9 blocked state. If a mismatch or live specialist exists, write only a blocking report/hand-off in your own workspace; do not campaign.

Independently SHA-256 record `fuzz/dns/corpus/seeds.txt`, `fuzz/dns/corpus/README.md`, each three `fuzz_dns_*.c` sources, and `fuzz/CMakeLists.txt` before use. Validate LLVM19 (`/usr/bin/clang-19`, `/usr/bin/clang++-19`), CMake, Ninja, `/usr/bin/timeout`, and matching compiler-rt fuzzer/ASan/UBSan libraries. Stop blocked if any is absent.

## Deterministic corpus and campaign commands

Create a new `/tmp/ratatoskr-g9-full-campaign-execution-003/corpus`. Parse `fuzz/dns/corpus/seeds.txt` deterministically by splitting only at the first colon; retain literal names such as `zero-length:`. Interpret only documented special values and hexadecimal payloads; reject malformed/unexpected lines. Record converter source/digest or exact inline algorithm, every derived filename/length/SHA-256, total count/bytes, and source provenance. Do not mutate the repository corpus.

Configure and build only these targets with LLVM19 and repository sanitizers:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-full-campaign-execution-003/build -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-full-campaign-execution-003/build --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run serially in order packet, name, record. For each, use a fresh copy of the deterministic corpus so libFuzzer mutations cannot affect later targets. Capture stdout/stderr and wrapper return/elapsed/RSS in `/tmp`. Use exactly:

```text
/usr/bin/timeout 120s <target> <fresh-corpus> -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

Treat sanitizer diagnostics, crash artifacts, timeout, nonzero target/wrapper exit, or libFuzzer resource/RSS diagnostics as a failure. Stop immediately at the first failure; preserve/minimize only if automatically produced or safely reproducible within the same bounded attempt, copy evidence under `/tmp`, remove any generated repository-root artifact, and state later targets unexecuted. Never alter `-rss_limit_mb=1024`.

## Allowed changes

Only these new files in your unique workspace:

- `README.md`
- `fuzz-plan.md`
- `fuzz-results.md`
- `handoffs/g9-full-campaign-execution-to-protocol-orchestrator.md`
- `completion-report.md`

No `fuzz/` source, repository corpus, CMake, production source, headers, tests, vectors, API, state, manifest, request, bindings, or external paths may change. `/tmp/ratatoskr-g9-full-campaign-execution-003*` is ephemeral evidence only.

## Expected outputs and acceptance

Create all five files above with template metadata, exact baseline/digests, tool versions, full commands, result per target, sanitizer evidence scan, budget/stop disposition, limitations, model telemetry, and a standard completion report. The handoff must target `protocol-orchestrator/g9-resumption-011`, be `READY_FOR_REVIEW` only if all three runs clean; otherwise `BLOCKED` with exact finding/reproduction and required return route. Never claim G9 passed or route security review.

Before delivery, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer` for permitted role-scoped `git add`/`commit`/`push`, staging exclusively your five files and pushing only `HEAD:refs/heads/hermes/dns-implementation-20260913`. No raw git commit/push. Read back `origin/hermes/dns-implementation-20260913` and record its exact revision. Verify `git diff --check <baseline>..HEAD` and that the committed diff names exactly these five new leaf files; preserve unrelated untracked paths.

## Handoff and stop conditions

Handoff target: `protocol-orchestrator/g9-resumption-011`; no security-reviewer route is authorized. No further delegation.

Stop immediately and report `QUOTA_OR_RATE_LIMIT` without state changes if quota/rate limiting occurs. Stop blocked without source changes for missing prerequisites, ref divergence, live execution, toolchain/corpus failure, sanitizer/resource issue, or any ambiguity. A clean campaign remains `READY_FOR_REVIEW` pending later independent G9 security review; it is never an approval.