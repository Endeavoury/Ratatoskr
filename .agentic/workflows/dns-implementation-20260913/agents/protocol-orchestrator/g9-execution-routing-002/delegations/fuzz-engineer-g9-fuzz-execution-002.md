# Delegated task: G9 DNS fuzz execution

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-002-delegation` |
| Workflow ID / stage / assignment | `dns-implementation-20260913` / `fuzzing` (G9) / `g9-fuzz-execution-002` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator/g9-execution-routing-002` |
| Status | `IN_PROGRESS` |
| Revision | Dispatch baseline `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3` |
| Assumptions | G7 and G8 records remain approved; pre-existing untracked artifacts are unrelated and must remain untouched. |
| Open questions | None at dispatch. |
| Limitations | Local bounded campaign only; this assignment cannot approve G9. |

ACTIVE ROLE: fuzz-engineer

## Goal and scope

Run one reproducible, bounded local libFuzzer campaign against the three already-existing DNS targets: `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`. Produce fresh plan/results evidence for independent G9 review. This is execution evidence only: do not author or change fuzz code, CMake, corpus, production code, headers, ordinary tests, vectors, semantics, workflow state, or public docs.

The authorized environment is only the local repository at the root below. Do not use network access, remote targets, credentials, scanning, exploitation, payload development, persistence, or external services. No security review is authorized or requested. Stop on any sanitizer crash or other reproducible fuzz failure; preserve only diagnostics/evidence in the allowed artifacts and issue the required blocking handoff. Do not apply native fixes.

## Model and reasoning

- Policy: `docs/agentic/MODEL_POLICY.md`, fuzz-engineer row.
- Requested route / effort: `openai-codex/gpt-5.6-terra`, `medium`.
- Observed route / effort: inherited child route must be recorded from runtime metadata if exposed; otherwise `unknown` (a prompt does not configure it).
- Context / completion target: required reading complete; 200–400-word completion plus links.
- User hard spend cap: none supplied.
- Attempt policy: one bounded campaign; no retry after a crash or prerequisite failure.
- Escalation: difficult failure minimization would request `gpt-5.6-sol/high` via the orchestrator, not be silently retried.

## Repository and workflow

- Repository root and command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Branch: `hermes/dns-implementation-20260913`; dispatch baseline `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3`.
- Artifact workspace: `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-002/`.
- Workspace owner: fresh fuzz-engineer leaf, assignment `g9-fuzz-execution-002`.
- Shared source directories: none. Use an ephemeral `/tmp/ratatoskr-g9-fuzz-execution-002` build directory and ephemeral `/tmp` corpus/artifact directories only.
- Shared-state writer: protocol-orchestrator only. Do not edit `workflow-state.yaml`.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/fuzz-engineer/SKILL.md`
3. `docs/agentic/{HANDOFFS.md,ARTIFACTS.md,REVIEW_GATES.md,MODEL_POLICY.md,DIRECTORIES.md,SECURITY_MODEL.md}`
4. `docs/contributing.md`
5. `.agentic/workflows/dns-implementation-20260913/{workflow-state.yaml,manifest.yaml}`
6. `agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`
7. `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`
8. `fuzz/dns/corpus/{README.md,seeds.txt}` and the three existing `fuzz/dns/fuzz_dns_*.c` harnesses.

## Approved inputs

- G7 APPROVED: `.agentic/workflows/dns-implementation-20260913/agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md`.
- G8 APPROVED: `.agentic/workflows/dns-implementation-20260913/agents/security-reviewer/g8-configured-limits-security-rereview-001/reviews/g8-configured-limits-security-rereview.md`, exact candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f`.
- Toolchain preflight: `agents/protocol-orchestrator/g9-resumption-006/g9-current-toolchain-preflight.md`, explicitly usable CMake, `/usr/bin/clang-19`, `/usr/bin/clang++-19`, and compiler-rt.
- Fixed seed provenance: tracked `fuzz/dns/corpus/README.md` and `fuzz/dns/corpus/seeds.txt` at the dispatch revision. Prepare an ephemeral binary corpus from those descriptions only; include the zero-length seed and a 65,535-zero-byte maximum-size seed as described, and record the conversion command and source-file digest in results.

## Allowed writes — exact files only

- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-002/fuzz-plan.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-002/fuzz-results.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-002/handoffs/g9-fuzz-execution-to-security-reviewer.md`
- `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-002/completion-report.md`

Every other path is read-only, including all `fuzz/` paths, all production code, headers, tests, vectors, docs, manifests, shared workflow state, and other agent workspaces. Do not create repository build products, corpora, logs, or files outside the four listed outputs.

## Required execution envelope

Use the explicit LLVM 19 toolchain and existing targets only. Capture exact commands, tool versions, build revision, seed provenance/digest, sanitizer diagnostics, timeout/memory limits, elapsed time, exit disposition, corpus statistics if printed, and per-target result.

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr \
  -B /tmp/ratatoskr-g9-fuzz-execution-002 -G Ninja \
  -DCMAKE_C_COMPILER=/usr/bin/clang-19 \
  -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 \
  -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-fuzz-execution-002 \
  --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run each target against the same ephemeral decoded fixed corpus with a 90-second `-max_total_time`, `-rss_limit_mb=1024`, and `-timeout=10`; apply an OS wall-clock guard of 120 seconds per target. Keep generated artifacts outside the repository. Do not run targets in parallel. Record any diagnostic tail directly in `fuzz-results.md`; do not retain separate repository logs.

## Expected outputs and dispositions

- `fuzz-plan.md`: reachable target mapping, invariants, seed source, build/sanitizer settings, exact bounded budget and failure handling.
- `fuzz-results.md`: exact commands and outputs, revision, seed provenance/digest, diagnostics, per-target elapsed/result, and limitations. State clearly whether a crash occurred.
- `handoffs/g9-fuzz-execution-to-security-reviewer.md`: if all targets finish without sanitizer crash, a `READY_FOR_REVIEW`, nonblocking handoff requesting independent G9 assessment; if any prerequisite/build/campaign failure occurs, set `BLOCKED`, identify the owning role, and do not request G9 approval.
- `completion-report.md`: standard template fields. Report `READY_FOR_REVIEW` only after all three campaigns finish cleanly; otherwise `BLOCKED`.

## Delivery, acceptance, and stops

Before any commit, verify branch/origin, exact staged allowed paths, and `git diff --cached --check`. For every project Git commit/push/readback use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>`. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`; never merge or push master. Read back that exact origin ref after push and record it.

Acceptance is complete, durable local campaign evidence for all three existing targets, with no unauthorized repository changes, returned as `READY_FOR_REVIEW` for a future independent `security-reviewer` G9 gate only. The leaf must not dispatch or perform that review. Missing/stale prerequisite, toolchain/build failure, sanitizer crash, boundary conflict, or quota/rate-limit error stops work immediately and yields a clear `BLOCKED` handoff. No further delegation is allowed.
