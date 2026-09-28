# Delegated task: G9 DNS fuzz execution 005

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-005-delegation` |
| Workflow / stage / assignment | `dns-implementation-20260913` / `fuzzing` (G9) / `g9-fuzz-execution-005` |
| Parent owner | `protocol-orchestrator/g9-resumption-008` |
| Disposition on dispatch | one fresh bounded execution assignment; G9 not approved |
| Campaign-source baseline | `git:400e818790bf6a8e7f13b7b86cfaf837a11066fc` |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |

ACTIVE ROLE: `fuzz-engineer`.

## Goal and hard boundary

Run exactly one bounded, local-only quality fuzz campaign against only the pre-existing DNS targets `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`, using only a derived ephemeral copy of the fixed repository corpus `fuzz/dns/corpus/`. Do not change source, headers, tests, fuzz sources/CMake, tracked corpus, vectors, workflow state, docs, configuration, credentials, or any other agent workspace.

No network or external service; no remote targets, scanning, exploitation, payload development, persistence, credential access, package installation, or additional target. Use only `/home/hermes/hermes-workspace/projects/Ratatoskr` and ephemeral `/tmp/ratatoskr-g9-fuzz-execution-005*` paths. Do not delegate. Stop immediately and create the formal blocker handoff if any prerequisite, digest, configure/build, sanitizer, timeout, crash, resource, safety, or policy check fails. Do not retry a stopped campaign.

## Model and attempt policy

- Policy: `docs/agentic/MODEL_POLICY.md`, `fuzz-engineer` row.
- Requested: `openai-codex/gpt-5.6-terra`, reasoning `medium`; actual child route/effort must be recorded if exposed, else `unknown`.
- One campaign attempt only; no model escalation and no further delegation.

## Repository, baseline, and integrity checks

- Command cwd and repository root: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Packet: `.agentic/workflows/dns-implementation-20260913/agents/protocol-orchestrator/g9-resumption-008/delegations/fuzz-engineer-g9-fuzz-execution-005.md`.
- Before any write, build, or run: verify root, origin, branch; set `packet_commit=$(git log -1 --format=%H -- "$packet")`; require nonempty `packet_commit`, `git merge-base --is-ancestor "$packet_commit" HEAD`, and `git merge-base --is-ancestor 400e818790bf6a8e7f13b7b86cfaf837a11066fc HEAD`. This deliberately permits the routing and later leaf commits; never require `HEAD` to equal the pre-dispatch baseline.
- Require `git diff --quiet`; preserve all pre-existing untracked paths.
- Read first: `AGENTS.md`, `.hermes/skills/fuzz-engineer/SKILL.md`, `docs/agentic/{HANDOFFS,ARTIFACTS,REVIEW_GATES,MODEL_POLICY,DIRECTORIES,SECURITY_MODEL}.md`, `docs/contributing.md`, current workflow state/manifest, G7 and G8 approvals named by state, `g9-resumption-006/g9-current-toolchain-preflight.md`, and `fuzz/dns/corpus/{README.md,seeds.txt}` plus all three harnesses.
- Before conversion require these SHA-256 values: `seeds.txt` `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; corpus `README.md` `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; packet harness `abd739bc36d6d2192887ee5e78d4fef48c3776e721ebe220a718b9a679569263`; name harness `f30ad35561305843882bb79a43af5a2ecf392fb74d7ca8b8c769dc59bbc3c4b0`; record harness `2cc304d70bd752d27625620dac67ff95889029ea93a4ae3f19c195dcee3a038c`; `fuzz/CMakeLists.txt` `5f0c63e19776c3c21e06f88d0a0f1efd335997b98f905ade89ddcf300fd586a5`.

## Allowed writes and required outputs

Only these repository paths may be created/changed:

1. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/fuzz-plan.md`
2. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/fuzz-results.md`
3. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/handoffs/g9-fuzz-execution-to-protocol-orchestrator.md`
4. `.agentic/workflows/dns-implementation-20260913/agents/fuzz-engineer/g9-fuzz-execution-005/completion-report.md`

All other repository paths are read-only. Logs and derived corpus/build output must remain only in `/tmp`; summarize exact commands and relevant stdout/stderr/sanitizer diagnostics in `fuzz-results.md`.

## Corpus, build, and execution

Create the derived corpus only in `/tmp` by parsing nonempty `seeds.txt` lines at the first colon. Reject missing colon, empty label, duplicate label, unexpected textual directive, and invalid hex. Accept `zero-length:` only with an empty value. Accept `maximum-size:` only with exact text `repeat 00 to 65535 octets during corpus preparation`, writing 65535 zero bytes. Decode all other values with `bytes.fromhex(value.strip())`; record conversion command, names, and byte lengths.

Configure/build only with:

```text
cmake -S /home/hermes/hermes-workspace/projects/Ratatoskr -B /tmp/ratatoskr-g9-fuzz-execution-005 -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DRATOS_BUILD_FUZZERS=ON -DRATOS_BUILD_TESTS=OFF
cmake --build /tmp/ratatoskr-g9-fuzz-execution-005 --target ratos_fuzz_dns_packet ratos_fuzz_dns_name ratos_fuzz_dns_record --parallel 2
```

Run only those three resulting executables sequentially against the same derived corpus. Each run must use an OS 120-second wall guard and libFuzzer flags `-max_total_time=90 -rss_limit_mb=1024 -timeout=10`. Record tool versions, corpus stats, full exact invocation, elapsed time, exit status, diagnostics, and explicit crash/no-crash result for each. No parallel runs and no other test target.

## Delivery, outcome, and Git

- `fuzz-plan.md` must map targets to invariants, provenance, sanitizers, budget, and failure policy.
- `fuzz-results.md` must contain all integrity, conversion, configure/build, and three-run evidence.
- If all three runs are clean, handoff and completion are `READY_FOR_REVIEW`; handoff is nonblocking and requests only protocol-orchestrator verification before any independent G9 security review. Otherwise both are `BLOCKED`, identify the owner, and explicitly request no review.
- Do not self-approve G9 and do not route security review or later work.
- After output creation, use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role fuzz-engineer -- <git arguments>` for Git. Verify branch/origin, stage exactly the four allowed paths, run cached diff check, commit, push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact origin ref. No merge, force push, or other ref.

HANDOFF TARGET: `protocol-orchestrator`; G9 security-reviewer is conditional future work only after independently verified clean evidence.
