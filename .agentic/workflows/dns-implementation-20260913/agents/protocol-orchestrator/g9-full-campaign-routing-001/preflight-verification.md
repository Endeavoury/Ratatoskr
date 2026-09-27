# G9 full campaign dispatch preflight

| Field | Verified value |
| --- | --- |
| Active role | `protocol-orchestrator` |
| Workflow / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Pre-dispatch local and origin ref | `git:12f0c4941727c6b3069835e00a79416ae42711db` |
| Branch / origin | `hermes/dns-implementation-20260913` / `https://github.com/Endeavoury/Ratatoskr.git` |
| Tracked worktree | clean; preserved unrelated untracked paths remain present |
| G7 / G8 prerequisites | independently recorded `APPROVED` for candidate `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| G9 status | `BLOCKED`; no G9 technical disposition asserted |

The prior full execution (`g9-fuzz-execution-005`) stopped on the now-remediated name-harness overflow. The focused remediation at `git:2c9e9b945352642d27cf703132e8e5e525b8b5cb` and independent focused review at `git:04715d1771c90b1f8d82686947b5cc1bb96dcf39` verify only the cap correction. Current source digests match the fresh packet, including corrected `fuzz_dns_name.c` SHA-256 `b82a552ca83f20a6c6cad10beb5c4c49ec6b607350b350f3516cc39e76aec31f`.

`/usr/bin/clang-19`, `/usr/bin/clang++-19`, CMake/Ninja, and repository-defined libFuzzer/ASan/UBSan targets were established by the committed LLVM19 preflight. Exactly one fresh fuzz-engineer execution assignment is authorized by the sibling delegation. Its output is limited to four report files; no source or shared-state write is allowed. No security review or later stage is included.
