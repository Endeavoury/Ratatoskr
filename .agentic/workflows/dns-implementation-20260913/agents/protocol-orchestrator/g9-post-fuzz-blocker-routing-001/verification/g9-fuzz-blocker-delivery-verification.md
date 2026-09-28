# G9 fuzz blocker delivery verification

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-blocker-delivery-verification-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator/g9-post-fuzz-blocker-routing-001` |
| Status | `BLOCKED` |
| Revision | Evidence baseline `git:5bac8c1e9771ac9281b6b696da98efe718efc27f`; wrapper delivery `git:4fe0e9417b659759786c41cb6707d15077111b15` |
| Source artifacts | Fuzz-engineer plan, results, blocked handoff, and completion report listed below |
| Assumptions | None. |
| Open questions | Environment maintainer must supply the required execution toolchain. |
| Limitations | No G9 campaign or independent G9 security review occurred. |

## Verified evidence

- Before delivery, local `HEAD` and `origin/hermes/dns-implementation-20260913` both resolved to `5bac8c1e9771ac9281b6b696da98efe718efc27f`.
- `git log --all` and `git ls-tree -r origin/hermes/dns-implementation-20260913` contained no `agents/fuzz-engineer/g9-fuzz-evidence-001` paths. The artifacts were untracked, so no earlier wrapper delivery was verified.
- The five evidence files were checksum-recorded before staging. The required wrapper staged exactly those five files; `git diff --cached --check` passed.
- `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-orchestrator -- commit -m "record DNS G9 fuzz toolchain blocker"` created `4fe0e9417b659759786c41cb6707d15077111b15`.
- The same wrapper pushed `HEAD:refs/heads/hermes/dns-implementation-20260913`; immediate `git ls-remote origin refs/heads/hermes/dns-implementation-20260913` returned `4fe0e9417b659759786c41cb6707d15077111b15`.
- `fuzz-results.md` records that `cmake`, `ctest`, Clang 16–18, Ninja, `llvm-profdata`, and `llvm-cov` are absent. Existing `fuzz/CMakeLists.txt` requires Clang/libFuzzer with `-fsanitize=fuzzer,address,undefined`; GCC/Make are not substituted.

## Authorized routing disposition

G9 is `BLOCKED`, not approved and not ready for security review. Preserve the delivered fuzz artifacts as evidence. The required input is an environment-maintainer-provided CMake + Clang/compiler-rt libFuzzer + ASan/UBSan execution environment. After provisioning, the protocol orchestrator must issue one new, complete fuzz-engineer execution assignment; a fresh independent security-reviewer can be routed only after executed evidence is delivered.
