# DNS-G7-001 implementation report

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-c-protocol-implementer-g7-local-label-remediation-001-implementation-report` |
| Workflow ID / stage | `dns-implementation-20260913` / corrective return from G7 `native_verification` |
| Target | `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Routing baseline / source revision | `git:37a59e7cba78a2b1455d407ec70854fd8255ce9e` |
| Modified-source content digest | `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88` (`src/protocols/dns/dns_client.c`) |
| Source artifacts | G7 handoff and test report at current working-tree content; DNS-REQ-002; DNS-VEC-003 |
| Assumptions | The approved G6 truth and synchronous API remain unchanged. |
| Open questions | None. |
| Limitations | CMake and CTest were not found on PATH and are not claimed. No commit or push occurred because no absolute executable `git-agent` wrapper was found. |

## Scoped change and trace

Added the private `request_name_valid` helper in `src/protocols/dns/dns_client.c`. It mirrors the existing DNS presentation-name boundary handling needed by request start: it rejects empty interior labels, incomplete or out-of-range decimal escapes, labels exceeding 63 decoded octets, and encoded names exceeding 255 octets. `ratos_dns_request_start` invokes it after its existing null/option/endpoint validation and before `calloc`, `ratos_strdup`, request ID generation, or request/context attachment.

This directly remediates `DNS-G7-001` and supplies the local observable required by `DNS-REQ-002` / `DNS-VEC-003`: a 64-octet label returns `RATOS_ERROR_INVALID_ARGUMENT`; because `*out` is initialized to `NULL` before validation, no request escapes. No header, public API, test, vector, model, analysis, documentation, or workflow-state file changed.

## Validation evidence

Command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.

- The packet-prescribed C11 build and run of `tests/dns/dns_tests.c` passed: `Ratatoskr DNS native tests passed`.
- The packet-prescribed C11 build and run of `tests/dns/dns_g7_native_verification_tests.c` passed: `G7 native DNS verification tests passed`.
- The specified native source set passed `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only`.
- `git diff --check` passed.
- `command -v cmake` and `command -v ctest` returned no paths; CMake/CTest are unclaimed.

## Review and delivery status

G7 remains pending a fresh independent `protocol-test-engineer` re-review of this implementation and its authored regression. This author has not approved G7.

Delivery blocker: no absolute executable `git-agent` wrapper. PATH lookup found no `git-agent`; `/home/hermes/.local/bin/git-agent`, `/usr/local/bin/git-agent`, `/usr/bin/git-agent`, and `/bin/git-agent` were not executable. Per packet policy, no raw Git commit or push was attempted.