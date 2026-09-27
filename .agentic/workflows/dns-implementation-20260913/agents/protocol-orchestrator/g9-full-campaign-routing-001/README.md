# G9 full campaign routing 001

| Field | Value |
| --- | --- |
| Active role | `protocol-orchestrator` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Status | `BLOCKED` pending a fresh campaign; one execution leaf is recorded `IN_PROGRESS` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Pre-dispatch baseline | `git:12f0c4941727c6b3069835e00a79416ae42711db` |
| Origin / branch | `https://github.com/Endeavoury/Ratatoskr.git` / `hermes/dns-implementation-20260913` |

## Scope

ACTIVE ROLE: `protocol-orchestrator`.

The focused name-harness remediation and its independent focused review are approved only for that correction (`git:04715d1771c90b1f8d82686947b5cc1bb96dcf39`). They do not establish G9. This routing creates exactly one fresh `fuzz-engineer` leaf for the sole remaining G9 execution stage: one bounded, serial, sanitizer-instrumented campaign over the existing DNS packet, name, and record targets. No G9 security review, other specialist assignment, or later workflow stage is authorized.

The leaf must use its committed delegation packet, independently verify its inputs and source digests, use only the named local repository and `/tmp` ephemeral paths, and stop formally on any sanitizer/crash/UB/build/integrity failure. G9 and the workflow remain `BLOCKED` until the later designated independent G9 security-reviewer gate is separately routed and records a disposition.

## Boundaries

This workspace owns only the delegation and routing evidence. The leaf owns only its four named report artifacts beneath `agents/fuzz-engineer/g9-full-campaign-execution-001/`; all source, corpus, CMake, tests, vectors, prior workspaces, and shared state remain read-only. No source change is authorized.
