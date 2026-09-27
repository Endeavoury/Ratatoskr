# G9 DNS fuzz execution results

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g9-fuzz-execution-002-results` |
| Workflow ID / stage | `dns-implementation-20260913` / `fuzzing` (G9) |
| Target | `protocol/dns` |
| Owner role | `fuzz-engineer/g9-fuzz-execution-002` |
| Status | `BLOCKED` |
| Execution revision | Local `git:f4a3d9a1dc8faca3e8cca2ce87d4af4e64f328ba`; dispatch `git:f37171a33e62f2ad2c1440ce41295a22596c5ee3` is an ancestor; the three harnesses and seed sources were unchanged between dispatch and execution HEAD. |
| Source artifacts | `fuzz/dns/corpus/README.md` SHA-256 `5f5ab470f17fe4acbe5fd934c113dc8d139bb750c105580699f88252bb61f551`; `fuzz/dns/corpus/seeds.txt` SHA-256 `8ab59177ff61b8beddc5de0749ee03a6f4f089563a6813fd1173757db4f38b07`; G8 approved review and G9 LLVM19 preflight named in `fuzz-plan.md`. |
| Assumptions | Existing untracked repository artifacts were preserved. |
| Open questions | A fresh, separately authorized fuzz-engineer assignment must supply/validate a correct fixed-corpus conversion command before any campaign attempt. |
| Limitations | No CMake configure/build completed and no fuzzer target ran. This is not G9 evidence and requests no G9 approval. |

## Preflight observed

- Command working directory: `/home/hermes/hermes-workspace/projects/Ratatoskr`.
- Toolchain observed before the failed prerequisite: `/usr/bin/clang-19` and `/usr/bin/clang++-19`, Debian Clang `19.1.7`; CMake `3.31.6`; Ninja `1.12.1`.
- Required wrapper exists and is executable: `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh`.
- Planned build directory: `/tmp/ratatoskr-g9-fuzz-execution-002`; planned corpus directory: `/tmp/ratatoskr-g9-fuzz-execution-002-corpus`.

## Exact prerequisite command and disposition

The single bounded campaign attempt stopped in corpus preparation, before the required CMake command. The issued decoder was:

```text
REPO="$repo" CORPUS="$corpus" python3 -c 'import os, pathlib
repo=pathlib.Path(os.environ["REPO"]); out=pathlib.Path(os.environ["CORPUS"]); out.mkdir(parents=True, exist_ok=True)
for line in (repo/"fuzz/dns/corpus/seeds.txt").read_text().splitlines():
 label, value = line.split(": ", 1)
 if label == "zero-length": data=b""
 elif label == "maximum-size": data=b"\\0" * 65535
 else: data=bytes.fromhex(value)
 (out/label).write_bytes(data)'
```

It exited `1` with this complete diagnostic tail:

```text
Traceback (most recent call last):
  File "<string>", line 4, in <module>
    label, value = line.split(": ", 1)
    ^^^^^^^^^^^^
ValueError: not enough values to unpack (expected 2, got 1)
```

The first source line is `zero-length:` without a trailing space, while the decoder required `": "`. Therefore the fixed binary corpus was not prepared, CMake was not configured, targets were not built, and no target received `-max_total_time=90 -rss_limit_mb=1024 -timeout=10` or the 120-second OS guard. Per the packet’s one-attempt/no-retry policy, execution stopped immediately. No sanitizer crash occurred because no target executed; this prerequisite failure blocks G9 campaign evidence.

## Per-target result

| Target | Result | Elapsed | Sanitizer diagnostics |
| --- | --- | ---: | --- |
| `ratos_fuzz_dns_packet` | NOT RUN — prerequisite failure | 0 s | None; target not built/run. |
| `ratos_fuzz_dns_name` | NOT RUN — prerequisite failure | 0 s | None; target not built/run. |
| `ratos_fuzz_dns_record` | NOT RUN — prerequisite failure | 0 s | None; target not built/run. |
