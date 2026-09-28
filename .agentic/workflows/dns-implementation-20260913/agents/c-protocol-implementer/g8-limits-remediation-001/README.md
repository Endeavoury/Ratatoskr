# DNS-G8-001 limits remediation

| Metadata | Value |
| --- | --- |
| Artifact ID | `dns-implementation-20260913-g8-limits-remediation-001` |
| Workflow ID / target | `dns-implementation-20260913` / `protocol/dns` |
| Owner role | `c-protocol-implementer` |
| Status | `READY_FOR_REVIEW` |
| Baseline | `git:9275f66dba3c19440da28ca86bd53777490b3e59` |
| Reviewed input | `git:4b801fbdf782c4aca4c6427ad930a48cb5e029ee`; `dns_client.c` `sha256:6eb4165fa6507289e9008490745f8066cf7e2da226691f917898008848f4aa88` |

## Scope

Authorized DNS-G8-001 native remediation only. Changed production sources are limited to the five assigned private DNS implementation files. Tests, public headers, workflow state, reviews, G9, and other roles' artifacts remain unchanged. The security-reviewer handoff Resolution is updated separately after this candidate and report evidence exist.
