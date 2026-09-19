# G5 boundary remediation routing

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g5-boundary-remediation-routing-001` |
| Workflow ID | `dns-implementation-20260913` |
| Target | `protocol/dns` |
| Owner role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` |
| Revision | Routing state delivery pending wrapper-mediated commit |
| Source artifacts | Corrected candidate `git:a8e631b338df393ddfd3ea9648f333303726d87b` / `sha256:0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`; byte review remote `git:43979c78c33247cf990002ec1392606f24bc7427`; interpretation review remote `git:525ba264e97e579c5a2720db8706bb286d85d343` |
| Assumptions | The two supplied remote review records are the fresh designated G5 reviews of the immutable corrected candidate. |
| Open questions | None. |
| Limitations | This is administrative routing only. It does not synthesize G5, approve technical vector truth, route reviewers, or route G6/later work. |

ACTIVE ROLE: protocol-orchestrator

## Verified review evidence

- The wrapper read remote ref `refs/remotes/origin/hermes/dns-implementation-20260913` as `43979c78c33247cf990002ec1392606f24bc7427` after fetch.
- `525ba264e97e579c5a2720db8706bb286d85d343` is an ancestor of that remote ref. The byte review and its completion record are present at `43979c...`; the interpretation review and completion record are present at `525ba...`.
- Both review records identify the exact candidate commit and SHA-256 above, declare independent fresh reviewer contexts distinct from original author `deleg_29cd50f7/task-0`, remediation author `deleg_18ffa0d9/task-0`, and prior reviewers, and write only their reviewer workspaces.
- The byte/coverage reviewer returned `CHANGES_REQUESTED` for blocking `DNS-G5-COV-004`. The interpretation reviewer returned `APPROVED`; its scoped approval cannot override the blocking designated byte/coverage disposition.
- The corrected candidate was wrapper-checked at `a8e631b338df393ddfd3ea9648f333303726d87b`: its delivery diff is limited to the prior remediation workspace and `git diff --check` is clean. Its exact vector digest was recomputed as `0a34f720c7b4f06739da5a00bde83c177ae147e9551df0ea10d54366e09e481c`.

## Required corrective route

Route exactly one fresh `vector-designer` authoring assignment, `g5-boundary-remediation-001`, limited to DNS-G5-COV-004. It must add canonical mechanically consumable local-request boundary vectors for DNS-REQ-002 at `0/1/63/64/255/256`: exact local inputs and emitted bytes for accepted values; exact local input and rejected/no-I/O/cleanup outcome for rejected values. The existing corrected VEC-014, VEC-017, and VEC-019 through VEC-023 must be preserved. The leaf must not edit the existing candidate, shared workflow state, source, tests, fuzzing, bindings, documentation, reviewer records, G6, or later artifacts.

G5 and vectors remain `CHANGES_REQUESTED`; no technical G5 approval is made. Future independent reviews are not routed by this assignment.
