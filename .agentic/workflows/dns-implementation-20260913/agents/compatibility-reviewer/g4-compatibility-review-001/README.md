# G4 compatibility-reviewer workspace

| Metadata | Value |
| --- | --- |
| Template version | 1 |
| Artifact ID | `dns-implementation-20260913-compatibility-reviewer-g4-compatibility-review-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `compatibility-reviewer` |
| Status | `CHANGES_REQUESTED` (scoped mandatory G4 support evidence only) |
| Revision | Delivery commit to be recorded after wrapper commit/push/readback. |
| Source artifacts | Immutable candidate `262c445a1b519b3baaa04f71fbcd59074c1baab0`; ABI baseline `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; G3 model and analysis; original and re-review binding evidence. |
| Assumptions | Review is design-only; no public header, implementation, binding, vector, or documentation realization is in scope. |
| Open questions | Resource defaults and binding target selection remain product decisions outside this review. |
| Limitations | This workspace neither approves overall G4 nor changes workflow state or any later stage. |

## Identity and boundary

ACTIVE ROLE: `compatibility-reviewer / g4-compatibility-review-001`.

This is a fresh independent leaf. I did not author or edit the subject candidate, its remediation, the original binding-safety review, or the scoped binding re-review: `protocol-api-designer/g4-api-design-001`, `protocol-api-designer/g4-binding-safety-remediation-001`, `binding-api-designer/g4-binding-safety-review-001`, and `binding-api-designer/g4-binding-safety-rereview-002`. I write only this assigned workspace.

The review compares the immutable proposed native declarations to the immutable ABI-1 baseline on ABI, C source API, bindings, and behavior. It records G12-style compatibility evidence required to support G4. It does not authorize header realization, approve overall G4, select product policy, or advance G5/G6 or later work.

## Immutable inputs verified

- Candidate API design: `262c445a1b519b3baaa04f71fbcd59074c1baab0`, SHA-256 `6d7efc5b272d8b23c591076bb29b2b6711538281341eaeee573c6d0ecc7c8814`.
- Candidate completion: same revision, SHA-256 `6de8c06709d92d5b99eac797e6c7b974e05f5f75630f6342fd13a639231bb55e`.
- ABI baseline: `e745710b95f209ad7bd3bdf4ef120e1d36b20fd4`; `docs/abi.md` SHA-256 `b33d752f7ecbdbf90cacb3520ee5c23d8ae12e0f5451d15060d6bd83b3f8904b`; `include/ratatoskr/dns.h` SHA-256 `d8d316792368150c6157001c4f5efa7b0420c5cac6ff95d81387cf942ca34ff5`.
- Binding review/handoff: `6126fa3f076614f69864186d9e9aa8223c3c024f`, SHA-256 `7ad721b4943aae4bc396e01dd4e8ce542e663b8ac2b75ef68a6e71cb4730dde4` / `1efe3b1b5095c1986f7d7b36ae243a01545ab3d7c18ebbaebd0fb85966f01353`.
- Scoped binding re-review: `0f0eb9db033f4c26481a302df397184515dc60ad`, SHA-256 `e5ead3b0fa6e966c50b4a3ed7e0999d4001bb4e1b497629252699673b3354bb8`.
- G3 model: `f26745472178649a60f2cb079937d1bbe3f13c0b`, SHA-256 `155eabcff91d1b062c509e3873dfbbc36f15be05df0f2d0506ca94635fab8700`; analysis: `5615caed0b7ad0a321d6794e71b79c4195e90384`, SHA-256 `5bc0ce7a7442060a946308de0bd6f36eb0a224c3715ae24225927bc87b48d444`.
