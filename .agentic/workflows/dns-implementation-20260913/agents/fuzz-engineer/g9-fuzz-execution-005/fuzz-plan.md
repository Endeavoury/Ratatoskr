# G9 DNS fuzz plan — execution 005

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-005-plan` |
| Workflow / stage | `dns-implementation-20260913` / fuzzing (G9) |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-fuzz-execution-005` |
| Status | `BLOCKED` — campaign stopped after a sanitizer finding in the second target |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Campaign baseline | `git:400e818790bf6a8e7f13b7b86cfaf837a11066fc` is an ancestor of dispatch HEAD `git:bf7ea8b929f45afdb2a9e206cac15bf9eb0f6c15` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, `medium` / `unknown` (no route/effort telemetry exposed) |

## Scope and provenance

This was exactly one local-only campaign against the pre-existing targets `ratos_fuzz_dns_packet`, `ratos_fuzz_dns_name`, and `ratos_fuzz_dns_record`; no source, tracked corpus, vector, configuration, workflow-state, network, credential, or external target action was authorized. The fixed input descriptions were `fuzz/dns/corpus/seeds.txt` and `fuzz/dns/corpus/README.md`. Their verified SHA-256 values and those of all three harnesses and `fuzz/CMakeLists.txt` are recorded in `fuzz-results.md`.

First-colon conversion was permitted only into `/tmp/ratatoskr-g9-fuzz-execution-005/corpus`: empty `zero-length:` becomes 0 bytes; the exact `maximum-size:` directive becomes 65,535 zero bytes; every other value is decoded with `bytes.fromhex(value.strip())`. The converter rejects missing colon, empty/duplicate label, unexpected text directive, and invalid hex.

## Target mapping and invariants

| Target | Existing harness entrypoint | Seed/invariant focus |
| --- | --- | --- |
| `ratos_fuzz_dns_packet` | `ratos_dns_parse_response` over raw packet data | Hostile complete/truncated DNS packets, compression/pointer errors, RDLENGTH and packet-size boundaries; no ASan/UBSan report, crash, timeout, or RSS-limit failure. |
| `ratos_fuzz_dns_name` | Synthetic response with mutated name section passed to `ratos_dns_parse_response` | Name labels, terminators, compression and bounded local packet construction; no harness or parser undefined behavior, ASan/UBSan report, crash, timeout, or RSS-limit failure. |
| `ratos_fuzz_dns_record` | Synthetic answer record with mutated type/class/TTL/RDLENGTH/payload | Record parsing and length/accounting boundaries; no ASan/UBSan report, crash, timeout, or RSS-limit failure. |

The existing CMake registration applies `-fsanitize=fuzzer,address,undefined` to all targets. Configure/build commands and per-run invocation are fixed in the delegation packet. Each serial run is guarded by `timeout 120s` and uses `-max_total_time=90 -rss_limit_mb=1024 -timeout=10`.

## Failure policy

Any configure/build/sanitizer/timeout/crash/resource/safety/policy failure immediately stops the campaign with no retry and no remaining target execution. Record only the evidence, preserve the generated crash input under `/tmp`, return a blocking handoff to `protocol-orchestrator`, and do not self-approve or route G9 security review.
