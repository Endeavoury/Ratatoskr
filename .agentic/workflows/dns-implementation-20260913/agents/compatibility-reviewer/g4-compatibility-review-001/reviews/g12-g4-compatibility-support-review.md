# G12-style G4 compatibility support review — DNS

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-g12-g4-compatibility-support-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `compatibility-reviewer` |
| Status | `CHANGES_REQUESTED` — mandatory G4 support evidence only |
| Revision | Subject candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`. |
| Source artifacts | Exact immutable inputs listed below. |
| Assumptions | Candidate is design-only and does not change the baseline header or implementation. |
| Open questions | Resource-default values and binding target choice are not product decisions this reviewer may select. |
| Limitations | No compiled realized header/library, runtime implementation, vector, documentation, or binding package exists; compile probes test only isolated proposed C declarations. |

## Gate identity

- **Gate / applicability:** G12-style compatibility evidence, mandatory support to applicable G4; it cannot approve overall G4.
- **Workflow stage:** `native_api_design`.
- **Candidate authors:** `protocol-api-designer / g4-api-design-001` and the replacement subject `protocol-api-designer / g4-binding-safety-remediation-001`.
- **Other reviewed author/reviewer identities:** `binding-api-designer / g4-binding-safety-review-001`; `binding-api-designer / g4-binding-safety-rereview-002`.
- **Reviewer:** `compatibility-reviewer / g4-compatibility-review-001`, fresh independent leaf.
- **Independence declaration:** I did not author or edit any candidate/review named above and wrote only this assigned compatibility-reviewer workspace. I did not perform API realization, implementation, binding work, vectors, documentation, workflow-state work, or an overall G4 decision.
- **Review date:** 2026-09-14.
- **Model / runtime evidence:** requested `gpt-5.6-sol` / medium; runtime exposed `openai-codex` / `gpt-5.6-terra`; effective reasoning effort and token/spend telemetry unknown. The request did not configure the runtime.

## Immutable input verification

| Input | Revision | SHA-256 |
| --- | --- | --- |
| Remediation candidate | `262c445a1b519b3baaa04f71fbcd59074c1baab0` | `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814` |
| Remediation completion | `262c445a1b519b3baaa04f71fbcd59074c1baab0` | `6de8c06709d92d5b99eac797e6c7b974e05f5f75630f6342fd13a639231bb55e` |
| ABI `docs/abi.md` | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b` |
| ABI `include/ratatoskr/dns.h` | `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4` | `d8d316792368150c6157001c4f5efa7b0420c5cac6ff95d81387cf942ca34ff5` |
| Original binding review | `6126fa3f076614f69864186d9e9aa8223c3c024f` | `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4` |
| Original return handoff | `6126fa3f076614f69864186d9e9aa8223c3c024f` | `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353` |
| Scoped binding re-review | `0f0eb9db033f4c26481a302df397184515dc60ad` | `e5ead3b0fa6e966c50b4a3ed7e0999d4001bb4e1b497629252699673b3354bb8` |
| G3 model | `f26745472178649a60f2cb079937d1bbe3f13c0b` | `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700` |
| G3 analysis | `5615caed0b7ad0a321d6794e71b79c4195e90384` | `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444` |

## Evidence and checks

| Pass criterion | Evidence | Observed result | Limitation |
| --- | --- | --- | --- |
| Existing ABI-1 preserved by an additive proposal | Baseline ABI policy; candidate §§1, 5–6; immutable diff has no `include/ratatoskr`/`docs/abi.md` changes | Existing surface is textually retained and intended additions use new names/opaque objects. Conditional only: no realized ABI exists. | No library/export-symbol comparison can occur. |
| Source API valid and complete | Candidate §2 and APIs 001–013; C11 syntax probes | **Fail.** Type/accessor collision and two undefined public types make the intended header uncompilable/incomplete. | Probes isolate declarations; they do not stand in for a future full header build. |
| Binding impact explicit and safe | Original review, scoped re-review, candidate event/endpoint/name sections | F-BIND-001/F-BIND-002 are scoped-approved, but bindings remain blocked by the incomplete/invalid public header. | No binding target/package is selected or exercised. |
| Behavior and ownership compatibility explicit | Candidate §§4–5; G3 model; `docs/abi.md`; `.NET` migration guide | Candidate preserves opaque ownership and structured nonzero RCODE intent, but only as design text. Existing synchronous behavior must remain unchanged. | No implementation or behavioral execution evidence. |
| Version/deprecation/migration policy followed | `docs/abi.md` §§Identity/Compatibility; `docs/migration-dotnet.md` | ABI-1 additive path is possible after correction; no existing API deprecation is proposed. No version/product choice is accepted here. | Resource defaults/binding selection remain outside scope. |

## Disposition

**CHANGES_REQUESTED.** C-COMP-001 is a blocking native API-design defect. Route to `protocol-api-designer` through `protocol-orchestrator` using `handoffs/g4-compatibility-to-api-designer-c-comp-001.md`. Re-review requires a new immutable candidate satisfying all handoff criteria and renewed independent compatibility evidence.

This record is not an overall G4 approval, does not modify G4/G5/G6/workflow state, and does not authorize later stages.
