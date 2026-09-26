# G9 DNS fuzz-evidence handoff

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-evidence-to-security-reviewer-001` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target | `protocol/dns` |
| Source role | `fuzz-engineer/g9-fuzz-evidence-001` |
| Status | `BLOCKED` |
| Revision | `git:5bac8c1e9771ac9281b6b696da98efe718efc27f` (evidence input) |

## Routing

- ID: `DNS-G9-FUZZ-TO-SECURITY-001`.
- Destination: a fresh independent `security-reviewer` G9 assignment; do not assign the author of this evidence as reviewer.
- Reason: G9 requires executed fuzz evidence, but the assigned environment lacks CMake and Clang/libFuzzer.
- Blocking: **true**.

## Source artifacts and evidence

- `fuzz-plan.md` and `fuzz-results.md` in this workspace.
- Existing fuzz surface: `fuzz/CMakeLists.txt`, `fuzz/dns/fuzz_dns_{packet,name,record}.c`, and `fuzz/dns/corpus/{README.md,seeds.txt}` at `git:5bac8c1e9771ac9281b6b696da98efe718efc27f`.
- Executed preflight showed `cmake: command not found` and `clang: command not found`; no libFuzzer runtime could be located. No campaign result or crash disposition is available.

## Specific blocking problem

A plan cannot meet G9. The existing CMake fuzz targets require Clang's `-fsanitize=fuzzer,address,undefined`, but CMake and Clang are unavailable. This author cannot supply an execution result without the required toolchain.

## Requested action

`protocol-orchestrator` should arrange one fresh fuzz-engineer execution assignment in an environment with CMake and Clang compiler-rt/libFuzzer, using the exact commands and deterministic parameters in `fuzz-plan.md`. After that author supplies executed results and crash dispositions, route those artifacts to a fresh independent security reviewer for G9 technical judgment.

## Acceptance criteria

The new evidence must identify exact source revision and toolchain, build all three existing targets, decode the documented corpus plus maximum-size seed, execute each deterministic 100,000-run campaign, retain final libFuzzer statistics and any crash reruns/minimization, and distinguish unexercised UDP/TCP/stateful surfaces. The independent security reviewer then evaluates G9; this handoff is not approval.

## Resolution (destination role)

Pending. No reviewer action is requested until execution-capable evidence exists.

## Closure (orchestrator after verification)

Pending.