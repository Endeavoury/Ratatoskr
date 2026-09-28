# G9 DNS name-harness bounds remediation plan 002

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g9-name-harness-bounds-remediation-002-plan` |
| Workflow / stage | `dns-implementation-20260913` / G9 corrective name-harness validation |
| Owner / ACTIVE ROLE | `fuzz-engineer/g9-name-harness-bounds-remediation-002` |
| Status | `READY_FOR_REVIEW` |
| Repository / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Dispatch baseline / local / fetched remote | `d489d749a37548e1e711d11c10b53b2041281bbf` / same / same |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Requested / actual route | `openai-codex/gpt-5.6-terra`, medium / `openai-codex/gpt-5.6-terra`, effort telemetry unavailable |

## Scope and source-level invariant

This is exactly one no-op remediation validation of `fuzz/dns/fuzz_dns_name.c`. Live code already contains:

```c
size_t copied = size < sizeof(packet) - 17u ? size : sizeof(packet) - 17u;
```

No source correction is permitted or needed. `packet` has 1024 elements. Terminal writes occupy offsets `12 + copied` through `16 + copied`; the cap makes `copied <= 1024 - 17 = 1007`, so the highest index is `16 + 1007 = 1023`. The parser length is `copied + 17 <= 1024`.

## Focused validation plan executed

1. Preserve all existing unrelated tracked and untracked state; verify root, origin, branch, local HEAD, and fetched tracking ref equal the dispatch baseline before writes.
2. Use existing `/usr/bin/clang-19` and `/usr/bin/clang++-19` to configure an isolated Ninja sanitizer build below `/tmp/ratatoskr-g9-name-harness-bounds-remediation-002`, with fuzzers enabled and tests disabled.
3. Build only `ratos_fuzz_dns_name`.
4. Replay one isolated 1,133-byte zero-derived input with `-runs=1`, a 10-second libFuzzer timeout, a 1024-MB RSS limit, and outer `timeout 30s`.
5. Treat ASan, UBSan, crash, timeout, or RSS diagnostics as a blocker. Do not run a campaign or packet/record target.

## Seed provenance and limitation

The derived input is a local `/tmp` 1,133-byte zero file matching the historical reproducer length condition, not a repository corpus change or a claim to preserve the historical payload. This bounded replay validates the existing terminal-write cap only; it is not full G9 campaign evidence, G9 approval, a focused review, or a security review.
