# G8 accounting corrective implementation report

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g8-accounting-implementation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` internal request accounting and context/request lifetime |
| Owner role | `c-protocol-implementer/g8-accounting-implementation-001` |
| Status | `READY_FOR_REVIEW` |
| Delivery revision | Wrapper-mediated delivery commit reported with this assignment handoff. |
| Source artifacts | Accounting design `git:4a37fc293c842b206190bad369e2a3e1ad00008c`; binding approval `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`; compatibility approval `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`; routing delivery `git:62a2dda24194020904a75e1edce9b3d74fbd70a4`. |
| Assumptions | Same-context request/context mutation is externally serialized; distinct contexts may be used concurrently. |
| Open questions | None for this implementation scope. |
| Limitations | No new tests or build configuration were authorized; CMake is unavailable. Fresh independent G7 then G8 review remain required. |

## Implementation trace

| Design requirement | Realization |
| --- | --- |
| Per-context registry/counters; no global tracker | `ratos_context` now owns `dns_requests`, `dns_outstanding_requests`, and `dns_connections`; the process-global request list and scan were removed. |
| Exact-once accounting | Request-owned outstanding/TCP-slot flags and centralized acquire/release helpers prevent duplicate release and guard decrements. |
| Start and TCP admission | Fully constructed requests acquire and attach an outstanding slot before exposure. TCP capacity is acquired only after correlated truncated UDP response; refusal becomes terminal `RESOURCE_LIMIT`/no-result and releases outstanding capacity. |
| Terminal cleanup | Completion, parser/failure, cancellation, destruction, and context teardown call centralized slot release. `take_result` transfers only the result. |
| Safe context destruction | `ratos_context_destroy` invokes DNS detachment before freeing context storage. Pending requests become cancelled/no-result; terminal requests retain state and COMPLETE results; every handle clears its context/list link. |
| Post-detach safety | State/error accessors, COMPLETE take-result, and request destruction use request-owned storage. Receive/transport/cancel operations reject detached handles without dereferencing context storage. |

## Validation evidence

Command cwd: `/home/hermes/hermes-workspace/projects/Ratatoskr`.

- `cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only src/core/context.c src/protocols/dns/dns_client.c` — passed.
- `cc -std=c11 -D_POSIX_C_SOURCE=200112L -Wall -Wextra -Werror -Iinclude -Isrc tests/dns/dns_g7_native_verification_tests.c ... -o /tmp/ratatoskr-g8-accounting-g7 && /tmp/ratatoskr-g8-accounting-g7` — passed; output: `G7 native DNS verification tests passed`.
- Required wrapper `git diff --check` — passed before artifact creation; final wrapper diff/check and delivery verification are recorded after staging below.
- `cmake` is not installed (`command -v cmake` produced no path), so CMake/CTest and sanitizer execution were unavailable and are not claimed.

The validation above is implementation evidence only, not independent G7/G8 review.
