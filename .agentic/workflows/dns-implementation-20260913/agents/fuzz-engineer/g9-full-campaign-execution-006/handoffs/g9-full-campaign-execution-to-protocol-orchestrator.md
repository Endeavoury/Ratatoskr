# Handoff: G9 full campaign execution 006 to protocol orchestrator

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-full-campaign-execution-006-handoff` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role / status | `fuzz-engineer` / `BLOCKED` |
| Revision | `git:87c2b7a36fdedca2370113093e53633850268a9a`; uncommitted assigned workspace artifact |
| Source artifacts | `fuzz-plan.md`, `fuzz-results.md`, dispatch delegation, LLVM19 preflight, approved G7/G8 records |
| Assumptions | The exact 1024 MB RSS cap is mandatory for this attempt. |
| Limitations | Generated evidence is retained under `/tmp` only; no source diagnosis or repair was authorized. |

## Routing

- ID / workflow / stage: `DNS-G9-FULL-CAMPAIGN-006-RSS-001` / `dns-implementation-20260913` / fuzzing (G9).
- Source role and assignment: `fuzz-engineer/g9-full-campaign-execution-006`.
- Destination role: `protocol-orchestrator`.
- Target: `protocol/dns`, existing `ratos_fuzz_dns_record` target.
- Reason: one mandated serial campaign ran packet/name/record. Packet and name completed cleanly; record exceeded the exact RSS limit and exited 71.
- Blocking: true.
- Status: `BLOCKED`.

## Source artifacts and reproduction

All input checksums, commands, tool versions, fresh-corpus provenance, build result, logs, and diagnostics are in `fuzz-plan.md` and `fuzz-results.md`. Reproduction is limited to a separately authorized new campaign: the executed record command was:

```text
/usr/bin/timeout 120s /tmp/ratatoskr-g9-full-campaign-execution-006/build/fuzz/ratos_fuzz_dns_record /tmp/ratatoskr-g9-full-campaign-execution-006/corpus-record -max_total_time=90 -rss_limit_mb=1024 -timeout=10
```

Observed at 11.073441973 seconds: `ERROR: libFuzzer: out-of-memory (used: 1112Mb; limit: 1024Mb)`, `SUMMARY: libFuzzer: out-of-memory`, exit 71. The retained ephemeral 11-byte OOM input is SHA-256 `2e3b9ab35557c5995c27fa64a98ca54496e3486450cffb7b7a025564cd77ce5e` at the path recorded in `fuzz-results.md`.

## Specific problem

The required record target exceeded its mandatory RSS cap. This fuzz-engineer assignment has no authority to determine whether this is a harness/corpus resource policy issue or a native resource-management defect, to alter the cap, or to patch fuzz/production code. The failure is a blocking campaign result, not a clean G9 candidate.

## Requested action

Keep G9 blocked; classify the failure and, if remediation is authorized, route only the responsible owner under a new scoped assignment. Do **not** route G9 security review or any later stage from this result. Do not treat packet/name cleanliness as an accepted G9 disposition.

## Acceptance criteria

1. Orchestrator records this blocking evidence without changing this leaf's artifacts or self-approving G9.
2. Any proposed remediation identifies the owner and permitted files, preserves the fixed source corpus as canonical input, and is independently reviewed through applicable earlier gates.
3. A new campaign, if later authorized, uses a fresh unique workspace and produces clean required evidence before a separate independent security-reviewer G9 assessment.

## Resolution (destination role)

`protocol-orchestrator/g9-resumption-008` independently read the results, handoff, completion report, and worktree evidence. It records the exact fixed-budget RSS failure as blocking. No code/resource-policy classification or remediation is authorized by this assignment.

## Closure (orchestrator after verification)

Verified 2026-09-28: packet/name completed cleanly, record returned 71 with `libFuzzer: out-of-memory (used: 1112Mb; limit: 1024Mb)`, and the leaf changed only its five assigned workspace artifacts. Workflow/stage/G9 return to `BLOCKED`; no G9 security review or later stage was dispatched. Handoff remains `BLOCKED` pending a separately authorized responsible-owner resolution.