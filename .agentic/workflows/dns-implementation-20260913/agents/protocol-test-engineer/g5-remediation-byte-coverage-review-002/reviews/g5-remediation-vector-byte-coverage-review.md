# G5 remediation DNS vector exact-byte and coverage review

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g5-remediation-vector-byte-coverage-review-002` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-test-engineer` |
| Status | `CHANGES_REQUESTED` |
| Revision | Review record pending wrapper-mediated delivery commit |
| Source artifacts | Corrected vector candidate `git:a8e631b338df393ddfd3ea9648f333303726d87b`, SHA-256 `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`; approved analysis `git:5615caed0b7ad0a321d6794e71b79c4195e90384` / SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`; model `git:f26745472178649a60f2cb079937d1bbe3f13c0b` / SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; API `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c` / SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520` |
| Assumptions | The approved UDP-first, TCP-after-correlated-TC profile and vector-local configured limits are authoritative. |
| Open questions | None. |
| Limitations | Review is static and independent: it used no production parser/builder, implementation, test harness, socket, or schema library. DNS-REQ-027 is intentionally downstream security/documentation evidence, not a missing G5 wire vector. |

## Gate identity
- **Gate ID and applicability:** G5, applicable canonical-vector review.
- **Workflow stage:** vectors.
- **Required input paths and exact revisions:**
  - `.agentic/workflows/dns-implementation-20260913/agents/vector-designer/g5-vectors-remediation-001/vector-set.json` at the candidate commit/digest above; both independently verified before review.
  - Corrective completion and handoff at that same commit; approved analysis, model, and API revisions listed above.
- **Artifact author assignment/agent identities:** original vector author `deleg_29cd50f7/task-0`; corrective vector author `deleg_18ffa0d9/task-0`.
- **Reviewer assignment/agent identity:** `protocol-test-engineer/g5-remediation-byte-coverage-review-002`; fresh leaf session, runtime delegation ID not exposed.
- **Independence declaration:** I did not author the original or corrected vectors and am distinct from `deleg_29cd50f7/task-0`, `deleg_18ffa0d9/task-0`, and the two prior G5 reviewers. I made no candidate, production, test, fixture, workflow-state, or G6+ change.
- **Review date:** 2026-09-19.
- **Reviewer model/effort and runtime evidence:** requested `openai-codex/gpt-5.6-terra` / medium; observed runtime model `openai-codex/gpt-5.6-terra`; effective effort and token telemetry unknown.

## Evidence and checks

| Pass criterion | Evidence path/revision | Observed result | Limitation |
| --- | --- | --- | --- |
| Immutable input identity | Candidate commit/digest above | `git show` and SHA-256 independently yielded exactly `a8e631b338df393ddfd3ea9648f333303726d87b` and `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`. | Content review only. |
| Exact encoded bytes and declared lengths | Candidate `vector-set.json` | JSON parsed; 23 sequential case IDs and all 31 recursive hex containers decoded successfully with decoded length equal to declared `byte_length`. | Does not execute a product parser. |
| DNS UDP message fields and exact consumption | Candidate; analysis DNS-REQ-006–016, 23 | Independent bounded DNS decoder confirmed valid VEC-004/005/006/012/013/014/019/020/021 layouts and exact ends; VEC-021 ends at 43 bytes with one Authority NS RR; VEC-023 structurally ends at 29 of 30 bytes. Truncated header, self-pointer, and RDLENGTH-short cases are malformed as declared. | Static decoder was review-only, not a production oracle. |
| Corrected VEC-014, 017, 019–023 | Candidate; model DOM-CONSUMPTION and TCP disposition partition | VEC-014 has a 29-byte TC UDP message, split `00`/`1d` prefix, then 29-byte body; VEC-017 rejects declared 29 above configured 28 at the 2-byte prefix; VEC-019 covers QNAME/QTYPE/QCLASS/peer/local-port/transport nonmatches; VEC-020 opcode is `1` (`0x8900`); VEC-021 authority ordering/end, VEC-022 EOF cleanup, and VEC-023 trailing-byte rejection are correctly encoded and state/cleanup-consistent. | TCP reuse/pipelining is deferred by the approved model/API. |
| Positive, negative, and boundary coverage | Analysis DNS-REQ-002 planned evidence | **Failed.** DNS-REQ-002 explicitly requires boundary vectors for label/name lengths `0/1/63/64/255/256`. The candidate has a root positive (0) and describes a 64-octet rejection, but no exact local-request input or canonical byte vectors for 1- and 63-octet labels, 255-octet maximum wire name acceptance, or 256-octet rejection. The 64 case is also not mechanically reproducible because VEC-003 supplies only `principal_fault: label_length_64`, not the input name/bytes. | This is a coverage deficiency, not a byte arithmetic defect in existing vectors. |

## Finding

### DNS-G5-COV-004 — required DNS-name boundary matrix is incomplete and partly non-reproducible
- **Severity / blocking:** gate-blocking coverage gap.
- **Requirement/design reference:** DNS-REQ-002; model `DOM-DNS-NAME` (1..63 labels, maximum expanded wire name 255); analysis planned evidence explicitly requires `0/1/63/64/255/256` boundaries.
- **Evidence:** only VEC-002 supplies the root case. VEC-003 names `label_length_64` in expected output but has no structured local name or exact wire/presentation input. No case supplies 1- or 63-octet label bytes, a 255-octet valid complete wire name, or a 256-octet invalid complete wire name.
- **Required action:** `vector-designer` must add canonical, mechanically consumable local-request vectors for the missing boundary values, with exact input representation and exact expected emitted bytes for accepted inputs; rejected inputs must state the exact local input and no-I/O/cleanup outcome. Preserve the present candidate’s corrected VEC-014, 017, and 019–023 evidence.
- **Re-review criterion:** a fresh G5 byte/coverage reviewer can decode every added boundary input, verify its declared lengths and expected emitted bytes/outcome, and map all six required boundary values to DNS-REQ-002.

## Disposition

**CHANGES_REQUESTED.** Existing wire-byte lengths, corrected framing/correlation/ordering/EOF/trailing-consumption cases, and their expected state/error/cleanup outcomes are sound on static independent review. G5 cannot pass because DNS-G5-COV-004 leaves the mandatory DNS-REQ-002 boundary matrix incomplete and VEC-003 non-mechanically specified. Responsible owner: `vector-designer`; return route: vector remediation through `protocol-orchestrator`. No handoff artifact was created because the packet authorizes one only for a blocker.
