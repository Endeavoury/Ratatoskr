# G5 boundary vector byte/coverage review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-protocol-test-engineer-g5-boundary-byte-coverage-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-test-engineer` |
| Status | `APPROVED` |
| Revision | Reviewer delivery commit recorded in `completion-report.md`; candidate is immutable at `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`. |
| Source artifacts | Candidate vector set at the identity above; analysis `git:5615caed0b7ad0a321d6794e71b79c4195e90384` / SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`; model `git:f26745472178649a60f2cb079937d1bbe3f13c0b` / SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; API design `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c` / SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`. |
| Assumptions | Review concerns the approved UDP-first stub/client vector profile and deterministic vector ID seam only. |
| Open questions | None for this byte/coverage review. |
| Limitations | No production implementation or test harness was used as an oracle; this is only the designated G5 byte/coverage disposition and does not approve G5 overall or any later stage. |

## Gate identity
- **Gate ID and applicability:** G5, applicable canonical-vector review.
- **Workflow stage:** vectors (G5).
- **Required input path and exact revision:** `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-boundary-remediation-001/vector-set.json` at `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`, SHA-256 `6950a88d55db12fc892fd39e72f84219bea6d5a81426ef4b73b4c9923232dcd6`.
- **Artifact author identity:** `vector-designer/g5-boundary-remediation-001` (delivery recorded as `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`).
- **Reviewer identity:** `protocol-test-engineer/g5-boundary-byte-coverage-review-001`, fresh independent leaf in this session.
- **Independence declaration:** I did not author or modify the candidate and am distinct from `vector-designer/g5-boundary-remediation-001` and pending `protocol-analyst/g5-boundary-interpretation-review-001`.
- **Review date:** 2026-09-19 CEST.
- **Reviewer model/effort and runtime evidence:** requested and observed route `openai-codex/gpt-5.6-terra`; requested effort medium; effective effort and usage telemetry unknown.

## Evidence and checks

| Pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Candidate identity and syntax | Candidate at `b7d05411`; `git show` blob compared with current file; SHA-256 computed locally | Current bytes equal delivery blob; digest matched exactly; JSON parsed; 29 cases | JSON syntax/structure only, not implementation execution |
| Required boundary cases | DNS-VEC-024..029 in candidate | Present exactly once: semantic boundaries 0, 1, 63, 64, 255, 256 | None |
| Exact local UTF-8 and QNAME derivation | DNS-VEC-024..029 `logical_input` and expected fields | Inputs/label vectors/wire lengths: 0→UTF-8 1, `00`, 1; 1→2, `016100`, 3; 63→64, label `[63]`, 65; 64→65, `[64]`, diagnostic 66; 255→254, `[63,63,63,61]`, 255; 256→255, `[63,63,63,62]`, diagnostic 256. Each decoded and reconstructed from label lengths. | ASCII inputs exercise UTF-8 byte identity, not non-ASCII policy |
| Exact accepted emitted bytes | DNS-VEC-024, -025, -026, -028 | Each message equals `1a2b01000001000000000000 || QNAME || 00010001`; lengths are 17, 19, 81, 271 (12-byte header + QNAME + 4-byte A/IN) and declarations match | No builder executed |
| Rejected no-I/O/cleanup outcomes | DNS-VEC-027, -029 | Both specify diagnostic only (never emitted), `sent_packets=0`, null emitted message, `ERR-LOCAL-VALIDATION`, `ST-FAILED`, no result, released context/buffers | No transport implementation executed |
| Global exact-byte declarations | All candidate hex containers | Recursive decoding found 41 hex containers and no declared-length mismatch | Semantic assertions independently checked only for scoped G5 review |
| Source consistency | Analysis DNS-REQ-002; model DOM-DNS-NAME and TR-LOCAL-REJECT; API start contract | Candidate matches 1–63 label and ≤255 expanded-name constraints; invalid inputs reject locally before I/O | No production/API oracle used |
| Candidate delivery boundary | `git diff --name-status b7d05411^ b7d05411` and `git diff --check` | Only the candidate author workspace was added; no whitespace errors | Author workspace contains its permitted accompanying records |

## Disposition

**APPROVED.** The immutable candidate supplies mechanically consumable accepted and rejected DNS-REQ-002 boundary coverage for 0/1/63/64/255/256 with exact local UTF-8 input, exact uncompressed QNAME diagnostics or emitted query bytes, correct declared lengths, and explicit no-I/O/terminal-cleanup behavior. No corrective action or handoff is required from this reviewer.
