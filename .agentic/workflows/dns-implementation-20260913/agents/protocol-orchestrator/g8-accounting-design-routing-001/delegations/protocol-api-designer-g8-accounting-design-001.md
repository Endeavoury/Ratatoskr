# Delegation: G8 DNS request-accounting design correction

## Identity and hierarchy

- **ROLE:** `protocol-api-designer` (leaf)
- **Hierarchy:** `workspace-orchestrator → protocol-orchestrator → protocol-api-designer`
- **Root task / project / workflow:** `dns-implementation-20260913` / `Ratatoskr` / `dns-implementation-20260913`
- **Stage:** scoped corrective native ownership/design work responding to blocking G8 finding `DNS-G8-002` and the implementation-authority blocker. This is design work only; it is not a G4/G7/G8 approval, implementation, test, or fuzz assignment.
- **Repository root and command cwd:** `/home/hermes/hermes-workspace/projects/Ratatoskr`

## Read first

`AGENTS.md`; exact role skill `.hermes/skills/protocol-api-designer/SKILL.md`; this packet; `docs/agentic/{ARCHITECTURE.md,ARTIFACTS.md,REVIEW_GATES.md,HANDOFFS.md,DIRECTORIES.md,MODEL_POLICY.md,SECURITY_MODEL.md}`; `docs/architecture.md`, `docs/abi.md`, and current `workflow-state.yaml`.

## Immutable inputs

1. Blocking G8 review delivery `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`:
   - `agents/security-reviewer/g8-limits-rereview-001/security-review.md`
   - `agents/security-reviewer/g8-limits-rereview-001/handoffs/dns-g8-002-global-request-tracker-race.md`
2. Blocked implementation handoff delivery `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`:
   - `agents/c-protocol-implementer/g8-global-limits-remediation-001/handoffs/g8-global-limits-remediation-authority-blocker.md`
3. Approved DNS model/API baseline: `agents/protocol-modeler/g3-disposition-partition-001/protocol-model.yaml` at `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; current approved G4 design `agents/protocol-api-designer/g4-compatibility-remediation-001/api-design.md` at `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`.
4. Read-only implementation evidence at candidate `git:7a0875e32ebaedb1d11b1736483e5d2a1df6dc25`: `src/core/core_internal.h`, `src/core/context.c`, `src/protocols/dns/dns_client.c`, and the current public ABI/header baseline.

Verify all listed commits are ancestors of the current `origin/hermes/dns-implementation-20260913` before writing. Do not substitute a newer source revision as authority.

## Exact write scope

Create and own only:

- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/README.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/api-design.md`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/decisions/`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/handoffs/`
- `.agentic/workflows/dns-implementation-20260913/agents/protocol-api-designer/g8-accounting-design-001/completion-report.md`
- The **Resolution section only** of `agents/c-protocol-implementer/g8-global-limits-remediation-001/handoffs/g8-global-limits-remediation-authority-blocker.md`.

All source, headers, tests, fuzzers, vectors, prior design/review artifacts, workflow-root files, and all other paths are read-only. Do not implement C or modify a public header. Do not close any handoff or approve any gate.

## Goal and required design result

Produce a bounded, implementation-ready internal ownership design that removes the unsafe global DNS request tracker without weakening documented separate-context concurrency or changing public ABI. It must specify:

1. context-owned representation and the exact internal core files that a later implementation must change;
2. initialization and destruction lifecycle, including the required behavior if a context is destroyed with a live request;
3. accounting updates for start, UDP-to-TCP transition, completion, failure, cancellation, take-result, and request destruction;
4. concurrency/reentrancy contract for distinct contexts, same-context callers, and request lifetime;
5. error/terminal/no-result behavior and preservation of per-context outstanding/connection caps;
6. whether the existing G4 API/ABI approval is affected, and the minimum independent review(s) required before the implementation route; and
7. exact, narrow follow-on write scope for `c-protocol-implementer` if the proposal is approved.

Return `BLOCKED` with a formal handoff rather than inventing lifecycle semantics if required model/architecture authority is missing or a public ABI/product choice is necessary.

## Acceptance criteria

- Design maps every G8-002 acceptance path to explicit state/ownership semantics and forbids unsynchronized process-global mutable tracking.
- It makes no public ABI claim without compatibility evidence and no production change.
- It states whether G4/G5/G6 evidence is stale and why; only the orchestrator may update shared state.
- It identifies the designated independent review required before implementation and a later fresh G7 then G8 review.
- Diff is restricted to this unique workspace plus the permitted handoff Resolution section.
- Completion uses standard fields and reports actual validation/limitations.

## Model, Git, and stop conditions

- **Requested route:** `openai-codex/gpt-5.6-sol`, reasoning `medium`, because this is an ownership/lifetime design correction.
- **Observed route:** record runtime metadata; do not infer it from this packet. One evidence-driven design pass; unresolved semantics return a handoff, not a retry ladder.
- For every Git operation use only `/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role protocol-api-designer -- <git arguments>`. Before commit verify origin, branch `hermes/dns-implementation-20260913`, exact allowed-path staged diff, and `diff --check`. Push only `HEAD:refs/heads/hermes/dns-implementation-20260913`, then read back that exact ref through the wrapper.
- On quota/rate error: stop immediately, do not modify shared workflow state, and report the error. No further delegation.

## Handoff target

Return the design candidate and any scoped authority resolution to `protocol-orchestrator`; it must obtain the designated independent review before a new c-protocol-implementer packet is issued.