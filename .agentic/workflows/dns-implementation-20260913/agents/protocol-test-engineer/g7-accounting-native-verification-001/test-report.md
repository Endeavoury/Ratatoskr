# DNS G7 accounting native verification report

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-g7-accounting-native-verification-001-test-report` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` context-owned request accounting |
| Owner role | `protocol-test-engineer/g7-accounting-native-verification-001` |
| Status | `APPROVED` |
| Candidate | `git:c38a7faf937571de5f0eb64885b8e5c61e5b9175` (parent `62a2dda24194020904a75e1edce9b3d74fbd70a4`) |
| Command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` (candidate extraction/build: `/tmp/ratatoskr-g7-accounting-c38`) |
| Model/reasoning | Requested `openai-codex/gpt-5.6-terra` / `medium`; observed `openai-codex/gpt-5.6-terra`; effort and usage `unknown`. |

## Independent review result

`APPROVED` for G7 at candidate `c38a7fa`.

The reviewed diff confines production changes to the four authorized paths. It removes the process-global request list, stores the intrusive registry and counters in the private context, uses request-owned slot flags for idempotent release, admits TCP only after a correlated truncated UDP response, and detaches caller-owned handles before context storage is freed.

## Executed checks

1. Wrapper-mediated Git verification:
   - `diff --name-status 62a2dda24194020904a75e1edce9b3d74fbd70a4 c38a7fa` confirmed the three candidate implementation artifacts plus only the four authorized production paths.
   - `diff --check 62a2dda24194020904a75e1edce9b3d74fbd70a4 c38a7fa` passed.
   - `merge-base --is-ancestor c38a7fa HEAD` passed; the three prerequisite approval revisions resolved.
2. Exact candidate extraction used wrapper `git archive c38a7fa`, avoiding review of mutable later source.
3. Strict candidate syntax check passed:
   ```sh
   cc -std=c11 -Wall -Wextra -Werror -Iinclude -Isrc -fsyntax-only \
     src/core/context.c src/protocols/dns/dns_client.c
   ```
4. Existing native G7 test linked against all candidate native sources and passed:
   `G7 native DNS verification tests passed`.
5. Fresh ephemeral accounting harness linked against all candidate native sources and passed. It verified:
   - per-context outstanding accounting;
   - UDP requests do not consume a TCP connection slot;
   - correlated `TC=1` acquires a TCP slot before `TCP_PENDING`/fallback event;
   - connection-cap refusal becomes terminal `RESOURCE_LIMIT`, releases outstanding capacity, and does not double-release the first request's TCP slot;
   - context destruction cancels pending work, preserves existing terminal state, clears links/flags, and permits safe caller-side destruction;
   - detached mutable operations return `RATOS_ERROR_INVALID_ARGUMENT`;
   - COMPLETE result remains takeable after context destruction;
   - two distinct-context pthread workers each complete 1,000 start/destroy cycles without assertion failure.
6. The same harness with `-fsanitize=address,undefined` and leak detection passed.

## Limitations

- `cmake` is absent, so CMake/CTest and project sanitizer configuration were not run.
- A ThreadSanitizer binary compiled but its runtime exited before tests with `FATAL: ThreadSanitizer: unexpected memory mapping`; no ThreadSanitizer pass is claimed.
- The ephemeral harness is evidence only; no test source change was necessary or authorized.

See `reviews/g7-accounting-native-verification.md` for the designated gate record.
