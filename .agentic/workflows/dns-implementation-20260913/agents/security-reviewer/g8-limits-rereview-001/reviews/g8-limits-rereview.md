# Gate review: G8 DNS limits remediation

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-security-reviewer-g8-limits-rereview-001-g8-review` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `security-reviewer/g8-limits-rereview-001` |
| Status | `CHANGES_REQUESTED` |
| Revision | Candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; author delivery `git:3bb81004050ca860ce8d9572f4e834847daf5b96`; G7 reviewer delivery `git:defb3e03ee0d2b6fc3a59b2ed446b0509512362d` |
| Source artifacts | Exact inputs and hashes in `../security-review.md` |
| Assumptions | Separate contexts retain the repository's documented concurrent-use contract. |
| Open questions | None; both blocking defects have implementation return routes. |
| Limitations | CMake/CTest absent; no G9 fuzzing or new test/probe authoring; dynamic race/socket reproduction not executed. |

## Gate identity

- Gate ID and applicability: `G8`, applicable hostile-input and runtime security review.
- Workflow stage: `security`.
- Required input paths and exact revisions: candidate `7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`; author delivery `3bb81004050ca860ce8d9572f4e834847daf5b96`; approved G7 review delivery `defb3e03ee0d2b6fc3a59b2ed446b0509512362d`; prior G8 delivery `90a02df18522b6c311e236dc03c82583971c7511`; approved analysis/model/API/vector revisions and hashes recorded in `../security-review.md`.
- Artifact author assignments/identities: `c-protocol-implementer/g8-limits-remediation-001` (`deleg_060817fb/task-0`) and `c-protocol-implementer/g7-limits-remediation-001` (`deleg_75f038be/task-0`).
- G7 reviewer assignment/identity: `protocol-test-engineer/g7-limits-rereview-001` (`deleg_c770b2ea/task-0`).
- Reviewer assignment/identity: fresh `security-reviewer/g8-limits-rereview-001`; direct CLI leaf, runtime session ID not exposed.
- Independence declaration: this reviewer did not author the candidate, remediation, G7 evidence, prior G8 evidence, tests, vectors, API, or workflow state and wrote only this assigned reviewer workspace.
- Review date: `2026-09-20T04:39:48+02:00`.
- Reviewer model/effort and runtime evidence: requested and actual current-session route `openai-codex/gpt-5.6-sol` / `high`, exposed by startup/runtime metadata. Persistent profile defaults remain Terra/unset but are not this session's route. Usage telemetry is unknown.

## Evidence and checks

| Pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Candidate, author delivery, and G7 evidence are current and immutable | Wrapper ancestry to HEAD/origin; source diff `7a0875e..HEAD`; hashes in `../security-review.md` | Pass: all required commits are ancestors; no post-candidate production/header/test/build delta | Pre-existing unrelated untracked workspaces were preserved |
| Fresh G7 approval matches candidate | `g7-limits-rereview-001/reviews/g7-limits-rereview.md`, delivery `defb3e0`, `sha256:e8f094...fb06e` | Pass: G7 is APPROVED for two configured name-limit probes and terminal no-result behavior | Its probes do not cover record-owner propagation, default hard-bound ordering, sync UDP truncation, or concurrency |
| Hostile limits are enforced before allocation/iteration/copy/traversal | Candidate source review; `DNS-REQ-024`; `INV-BOUNDED-PARSING` | Partial/fail: normal configured checks exist, but DNS-G8-001 has four reachable enforcement/disposition gaps | Dynamic custom probes forbidden/not authored |
| UDP and TCP excess are terminal with no result | `dns_client.c:184-188,219-241`; G7 evidence | Partial: incremental UDP/TCP frame and reviewed G7 cases clean up and expose no result | Synchronous POSIX UDP cannot detect over-limit datagram truncation |
| Lifetime and documented separate-context concurrency are safe | `docs/architecture.md:67-72`; `dns_client.c:193-199,212-216,247` | Fail: DNS-G8-002 unsynchronized global request list permits cross-context data race/UAF | No dynamic race run; direct C11 lifetime/control-flow evidence |
| Candidate compiles under strict C11 syntax checks | `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only src/core/*.c src/protocols/dns/*.c` | Pass | CMake/CTest unavailable |
| No unresolved blocking security finding remains | `../security-review.md`; handoffs | **Fail**: DNS-G8-001 and DNS-G8-002 are blocking | G9 intentionally not run |
| Reviewer boundary and independence | wrapper status/diff and assignment scope | Pass before delivery: only assigned reviewer outputs created | Final commit/readback recorded in completion metadata after delivery |

## Disposition

**CHANGES_REQUESTED.** Candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25` does not satisfy G8. Blocking findings are:

1. `DNS-G8-001` (Medium): configured-limit remediation remains incomplete across record-owner error propagation, default hard-bound disposition, accepted pointer maxima, and synchronous UDP truncation detection. Owner: `c-protocol-implementer`; handoff `../handoffs/dns-g8-001-configured-limits-remediation-incomplete.md`.
2. `DNS-G8-002` (High): remediation introduced an unsynchronized process-global request tracker contrary to documented separate-context concurrency. Owner: `c-protocol-implementer`; handoff `../handoffs/dns-g8-002-global-request-tracker-race.md`.

A new corrective revision, fresh independent G7, and fresh independent G8 re-review are required. This record does not update workflow state and does not route or approve G9.