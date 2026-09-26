# G7 native DNS verification report

| Field | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g7-native-verification-001-test-report` |
| Workflow / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `protocol-test-engineer` |
| Status | `CHANGES_REQUESTED` |
| Reviewer independence | Independent of `c-protocol-implementer/g6-native-implementation-001`; this assignment authored no production code. |
| G6 subject / current routing baseline | `eaa191ba25fde6b4224e0cacccee92adbdfd5701` / `3b2803d0a1c92c1d73e36fa1e258305b5f06d4d8` |
| G7 packet baseline | `855c897c46c053978ae72b4dab6bda356bf4168d` |
| Approved inputs | analysis `5615cae` SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`; model `f267454` SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; API `e3c63f` SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`; vectors `b7d0541` SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`. |

## Independent evidence

The G6 delivery is an ancestor of the routing baseline. Its delivery-to-baseline diff is limited to the reported implementation paths and G6 artifacts; `git diff --check eaa191ba25fde6b4224e0cacccee92adbdfd5701^..855c897c46c053978ae72b4dab6bda356bf4168d` passed. Five historical untracked workspaces were present before this assignment and remain untouched.

Existing native coverage was inspected before authoring any G7 test: `tests/CMakeLists.txt`, `tests/dns/dns_tests.c`, `tests/integration/dns_fixture_test.py`, and `tests/fixtures/dns/README.md`. CMake and CTest are unavailable (`command -v cmake` and `command -v ctest` produced no paths), so no CMake configure/build/CTest result is claimed.

Feasible manual native evidence passed:

```sh
cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc \
  src/core/context.c src/core/error.c src/core/memory.c src/core/version.c \
  src/protocols/dns/dns_builder.c src/protocols/dns/dns_client.c \
  src/protocols/dns/dns_packet.c src/protocols/dns/dns_parser.c \
  src/protocols/dns/dns_transport_tcp.c src/protocols/dns/dns_transport_udp.c \
  tests/dns/dns_tests.c -o build/g7-native-verification-001/ratos_dns_tests
build/g7-native-verification-001/ratos_dns_tests
```

Output: `Ratatoskr DNS native tests passed`. The same source set passed `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only`.

## Finding

### DNS-G7-001 — local request accepts a 64-octet DNS label

**Blocking: yes. Owner: `c-protocol-implementer`.** DNS-REQ-002 and canonical `DNS-VEC-003` require a 64-octet label to be rejected locally with no request/context. `ratos_dns_request_start` in `src/protocols/dns/dns_client.c` checks only `strlen(name) == 0 || strlen(name) > 255`; it neither validates individual label length nor calls the existing query builder. Therefore it returns success and creates a request for `"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."`.

The independently authored regression `tests/dns/dns_g7_native_verification_tests.c` asserts the approved `DNS-VEC-003` observable: `ratos_dns_request_start(...) == RATOS_ERROR_INVALID_ARGUMENT` and `request == NULL`. Its manual build completed, then execution failed at that assertion (exit 134). This authored test is evidence only and is not self-approved; a later independent test-engineer must review the harness after remediation.

## Disposition and limitations

`CHANGES_REQUESTED`: a demonstrated code defect blocks a READY_FOR_REVIEW submission. No G7 approval or pass is claimed. The formal return is `handoffs/dns-g7-001-local-label-validation.md`. No security/G8+ work was started.

Writes are limited to this assignment workspace plus the explicitly allowed G7 test and its sole `tests/CMakeLists.txt` registration. No production, canonical truth, workflow-state, existing-test, binding, fuzz, documentation, or unrelated-workspace path was modified.
