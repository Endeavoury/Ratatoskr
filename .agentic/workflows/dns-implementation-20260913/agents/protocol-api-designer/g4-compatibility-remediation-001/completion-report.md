# Specialist completion

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-completion-g4-compatibility-remediation-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-api-designer` |
| Status | `READY_FOR_REVIEW` |
| Candidate revision | `e3c63fd` |
| Candidate SHA-256 | `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520` |
| Final delivery revision | Recorded after this completion/resolution commit and wrapper remote readback. |
| Inputs | Compatibility delivery `0cb6e27b265c38e42d09d61c0883f1a086df8835`; immutable subject candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0` / `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; G3 model `f26745472178649a60f2cb079937d1bbe3f13c0b`; analysis `5615caed0b7ad0a321d6794e71b79c4195e90384`. |

ROLE: protocol-api-designer / g4-compatibility-remediation-001

STATUS: READY_FOR_REVIEW

SUMMARY:
Produced a fresh immutable design candidate resolving `C-COMP-001`. The request-state accessor is now `ratos_dns_request_get_state`, avoiding the typedef's C ordinary-identifier namespace. The candidate fully defines versioned `ratos_dns_request_options` and `ratos_dns_limits`, including field order/types, mandatory `struct_size`, initializers, reserved-field behavior, append-only evolution, borrowed/copy semantics, symbolic default-source behavior, validation, and ABI-1 implications. Baseline synchronous query and result ownership remain unchanged. No numeric resource policy was invented; it is handed to the maintainer through the orchestrator.

ARTIFACTS CREATED:
- `README.md`
- `api-design.md` — candidate at `e3c63fd`, SHA-256 `69be123010e74dbaa9e1329178bc2cd37fa9b35e6de400bf8cb7db9a3a3ab520`
- `handoffs/maintainer-resource-policy.md`
- `completion-report.md`

ARTIFACTS MODIFIED:
- Compatibility handoff `agents/compatibility-reviewer/g4-compatibility-review-001/handoffs/g4-compatibility-to-api-designer-c-comp-001.md`, Resolution section only, in the final delivery commit.

DECISIONS MADE:
- Use `ratos_dns_request_get_state` as the nonconflicting accessor.
- Treat zero in each limits field as an implementation-selected documented default source, never unlimited.
- Keep numeric resource values as an explicit maintainer decision.

OPEN QUESTIONS:
- Maintainer via protocol-orchestrator must select/document concrete resource defaults before realization claims them.

BLOCKERS:
- No authoring blocker. G4 remains `CHANGES_REQUESTED` until a fresh independent compatibility re-review evaluates this candidate; this report does not approve G4.

HANDOFF REQUIRED:
- Fresh independent compatibility-reviewer re-review of candidate `e3c63fd` and its recorded SHA-256; the protocol-orchestrator alone routes it.
- Maintainer resource-policy response through protocol-orchestrator before concrete numeric defaults are realized.

RECOMMENDED NEXT ROLE:
- protocol-orchestrator, then a fresh independent compatibility-reviewer.

VALIDATION EVIDENCE:
- Read all packet-required contracts, compatibility delivery, immutable candidate, G3 model/analysis, and ABI baseline.
- Wrapper-only Git pre-commit checks verified branch `hermes/dns-implementation-20260913`, staged allowed candidate paths, and clean `git diff --check`.
- `sha256sum` computed the candidate digest above.
- Candidate commit `e3c63fd` contains only the three owned candidate files. No header/code, test, vector, binding, documentation, review, or workflow-state change was authored.
- The unrelated untracked `agents/binding-api-designer/g4-binding-safety-rereview-001/` directory was observed before commit and preserved.

MODEL / RUNTIME EVIDENCE:
- Requested `gpt-5.6-sol` / medium. Actual exposed runtime: `openai-codex` / `gpt-5.6-terra`; effective reasoning effort, token use, and spend telemetry: unknown.

LIMITATIONS:
- Design evidence only. No realized public C header/library was compiled, no ABI binary comparison or runtime behavior was tested, and no independent re-review was authored.
