# DNS G8 configured-limits security re-review routing 001

| Field | Value |
| --- | --- |
| Workflow / stage / assignment | `dns-implementation-20260913` / `security` / `g8-configured-limits-security-rereview-001` |
| Active role | `protocol-orchestrator` |
| Status | `IN_PROGRESS` — exactly one fresh independent G8 leaf is authorized |
| Repository root / command cwd | `/home/hermes/hermes-workspace/projects/Ratatoskr` |
| Candidate | `git:1a371fe8083e72304740d983dcb7f9f6033b6b7f` |
| Candidate parent | `git:509114307b862e8e339ded3eea5d483ea861d2d4` |
| Required reviewer route | `openai-codex/gpt-5.6-sol`, reasoning `high` |
| Required Git wrapper | `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh` |

## Scope and authority

This is the sole ready corrective stage: one independent G8 security re-review of the exact candidate after the fresh G7 approval. It does not authorize implementation, tests, vectors, design, workflow changes by the leaf, G9/fuzzing, later stages, merges, master, or a second review.

The reviewer is a newly launched direct Hermes CLI session and must be independent of candidate author `c-protocol-implementer/g8-configured-limits-remediation-002` and every prior G8 security-reviewer assignment, including `security-reviewer/g8-accounting-security-rereview-001` and `security-reviewer/g8-security-review-001`. The reviewer may write only the five exact files/paths in its packet. The protocol-orchestrator alone owns workflow-state reflection after verifying the leaf delivery.

## Verified preconditions

- G1–G6 and G7 are `APPROVED`; G7 record is `agents/protocol-test-engineer/g7-configured-limits-rereview-003/reviews/g7-configured-limits-rereview.md` for the exact candidate, reviewer delivery `git:510b5a131bcb3272caeb7eb1821444b35644cfcd`, remote delivery reflection `git:7720bfe2bf96020fa0f84ccf2d6bbb52247c510d`.
- G8 remains `CHANGES_REQUESTED` only for `DNS-G8-001`; its prior record and unresolved handoff are read-only evidence.
- The candidate is an ancestor of local `HEAD` and changes exactly `src/protocols/dns/dns_client.c`, `dns_internal.h`, `dns_parser.c`, and `dns_transport_udp.c`.
- The absolute wrapper exists, is executable (`700 hermes:hermes`), admits `protocol-orchestrator` and `security-reviewer`, and was used for this preflight. Origin, branch, and remote ref are recorded in `preflight-verification.md`.

## Stop rules

If the direct session does not actually report `openai-codex/gpt-5.6-sol` and `high`, it must create no technical G8 disposition and return `BLOCKED` only within its allowed workspace. On quota/rate-limit, stop immediately without any repository or state changes. Any missing input, candidate mismatch, forbidden-path need, wrapper failure, or unresolved blocker stops the stage. No other leaf may be dispatched.