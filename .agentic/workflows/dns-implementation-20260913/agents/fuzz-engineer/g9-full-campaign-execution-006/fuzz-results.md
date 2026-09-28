# Fuzz results — G9 full DNS campaign execution 006

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-006-fuzz-results` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role / status | `fuzz-engineer` / `BLOCKED` |
| Revision | `git:87c2b7a36fdedca2370113093e53633850268a9a`; this is an uncommitted assigned workspace artifact |
| Source artifacts | G7/G8 approvals, delegation, and preflight listed in `fuzz-plan.md` |
| Open question | Resource-limit failure classification and remediation owner: `protocol-orchestrator`; this leaf must not repair it. |
| Limitations | One exact local-only attempt; logs and generated inputs are ephemeral under `/tmp`. |

## Build result

The specified LLVM19 configure command completed successfully: CMake identified Clang 19.1.7 and generated `/tmp/ratatoskr-g9-full-campaign-execution-006/build`. The exact requested build command completed exit 0 and linked all three existing targets. Build log: `/tmp/ratatoskr-g9-full-campaign-execution-006/build.log`.

## Per-target execution evidence

| Order / target | Fresh corpus | Elapsed | Exit | Runs / final RSS | Diagnostic scan | Result |
| --- | --- | ---: | ---: | --- | --- | --- |
| 1 / `ratos_fuzz_dns_packet` | `corpus-packet`, 10 files / 65,887 bytes / SHA-256 `d7ad8905…e51f42` | 91.237566814 s | 0 | 2,367,596 / not reported in final `Done` line | No ASan, UBSan, libFuzzer error/summary, or timeout marker | Clean; `Done 2367596 runs in 91 second(s)` |
| 2 / `ratos_fuzz_dns_name` | `corpus-name`, 10 files / 65,887 bytes / SHA-256 `d7ad8905…e51f42` | 91.195218965 s | 0 | 6,242,762 / 442 MB | No ASan, UBSan, libFuzzer error/summary, or timeout marker | Clean; `Done 6242762 runs in 91 second(s)` |
| 3 / `ratos_fuzz_dns_record` | `corpus-record`, 10 files / 65,887 bytes / SHA-256 `d7ad8905…e51f42` | 11.073441973 s | 71 | 18,856 / 1,112 MB | `ERROR: libFuzzer: out-of-memory (used: 1112Mb; limit: 1024Mb)` and `SUMMARY: libFuzzer: out-of-memory`; no ASan/UBSan marker | **Failure** — required RSS limit exceeded; campaign stopped. |

The exact record invocation wrote the 11-byte minimised input only in its `/tmp` run directory: `/tmp/ratatoskr-g9-full-campaign-execution-006/run-record/oom-cac13ed38e88face6006159dc20a215efb2a0989`, SHA-256 `2e3b9ab35557c5995c27fa64a98ca54496e3486450cffb7b7a025564cd77ce5e`. The log reports bytes `4f 13 01 01 01 01 7e 01 01 01 01` and `artifact_prefix='./'`; no repository artifact was written.

No later target existed after record, and none was rerun. The campaign did not reach a clean three-target disposition.

## Disposition

`BLOCKED`. Packet and name evidence is clean within their fixed budget. The record target produced a nonzero resource-limit failure under the exact required `-rss_limit_mb=1024`; this fails the campaign's no-failure invariant. This is not G9 approval and no G9 security review or later stage is requested.