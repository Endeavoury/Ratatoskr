# Delegation: G8 accounting corrective implementation

## Identity

- **Workflow/root ID:** `dns-implementation-20260913`
- **Project:** Ratatoskr
- **Role:** `c-protocol-implementer`
- **Assignment:** `g8-accounting-implementation-001`
- **Hierarchy:** protocol-orchestrator → exactly one specialist leaf; do not delegate.
- **Repository root and command cwd:** `/home/hermes/hermes-workspace/projects/Ratatoskr`
- **Owned workspace:** `.agentic/workflows/dns-implementation-20260913/agents/c-protocol-implementer/g8-accounting-implementation-001/`
- **Handoff target:** `protocol-orchestrator` only.

## Read first

1. `AGENTS.md`
2. `.hermes/skills/c-protocol-implementer/SKILL.md`
3. This packet and `../preflight-verification.md`
4. `docs/agentic/{ARTIFACTS,SECURITY_MODEL,REVIEW_GATES,DIRECTORIES,HANDOFFS,MODEL_POLICY}.md`, `docs/contributing.md`, `docs/abi.md`
5. Current `workflow-state.yaml` and the exact immutable inputs below.

## Approved baseline and immutable inputs

- Verified routing baseline/head/origin: `git:685242c528517ec2e704c28a1f520ed4c1b76672` on `hermes/dns-implementation-20260913`.
- Exact accounting design candidate: `git:4a37fc293c842b206190bad369e2a3e1ad00008c`, especially `agents/protocol-api-designer/g8-accounting-design-001/{api-design.md,decisions/context-destroy-live-requests.md,handoffs/accounting-design-to-protocol-orchestrator.md,completion-report.md}`.
- Binding-lifetime scoped `APPROVED`: `git:e04fefa07e72427adc7ecbab339fef96bc04b3b7`.
- Compatibility review-002 scoped `APPROVED`: `git:aa2ebfaa8379d74a539ef95caf02d925f799d229`, baseline `git:e804eb46f9aca14c4be6152e154a0b518f34c7fe`.
- Existing approved model: `git:f26745472178649a60f2cb079937d1bbe3f13c0b`; prior G4 candidate: `git:e3c63fdb0766afc86d28fc32ec3071d1e7ec762c`; approved vectors: `git:b7d05411cacfeb07be9f6bfbc36f705efdd002c5`.
- G8 finding/review: `git:844cc88ad3f57f3c70c5d3cab7dd80b4a05d794f`; G8 implementation-authority blocker: `git:d46df3b86118ab0a7bda8aef6953ac26ec937164`.

## Write boundary

**May modify exactly:**

1. `src/core/core_internal.h`
2. `src/core/context.c`
3. `src/protocols/dns/dns_internal.h`
4. `src/protocols/dns/dns_client.c`
5. Files inside your owned workspace above, including `README.md`, `implementation-report.md`, `handoffs/`, and `completion-report.md`.
6. Only explicitly named destination `## Resolution (destination)` sections in required formal handoffs, if any.

**Forbidden:** every other path. In particular do not change public headers, tests, CMake/build files, transport files, parser, bindings, docs, vectors, workflow state, review artifacts, or other agent workspaces. Do not alter approved design truth. Do not route/execute G7, G8 re-review, G9, bindings, docs, compatibility final, or any later stage.

## Required behavior

Implement the approved private design exactly:

- Replace process-global mutable request tracking with a per-`ratos_context` registry and per-context outstanding/TCP-connection counters.
- Use explicit per-request ownership flags and centralized idempotent helpers so slots are acquired/released exactly once; no underflow.
- Attach only fully constructed requests. Release slots on COMPLETE, failure, cancellation, and request destruction without changing take-result accounting.
- At UDP→TCP fallback, acquire a per-context TCP slot; a cap refusal becomes terminal RESOURCE_LIMIT/no-result, releases the outstanding slot, but leaves the caller-owned request inspectable/destroyable.
- Before `ratos_context_destroy` frees context storage, detach all attached request handles. Never free caller-owned requests. Pending requests become CANCELLED/no-result with released flags/counters; terminal state remains; COMPLETE result remains takeable.
- After detachment, state/error inspection, COMPLETE take-result, and request destruction must access only request-owned storage safely; further mutable transport/parser work must not resume.
- Preserve same-context external serialization and distinct-context concurrency; introduce no process-global mutable tracker.

## Validation and reporting

- Inspect the dirty tree before edits and preserve all unrelated changes.
- Run compile/test evidence only using existing repository capabilities and without changing tests/build files. Record exact commands, output/result, and unavailable-capability limitations.
- Check the final diff against the four-file production boundary and run `git diff --check` through the required wrapper.
- Write implementation trace/report, formal handoff to `protocol-orchestrator`, and completion report. Completion must be `READY_FOR_REVIEW`, never self-approved.
- State actual model/effort and usage accurately: requested `openai-codex/gpt-5.6-terra` / `medium`; this child inherits Terra route, but effective reasoning effort must be reported as observed or `unknown`, never assumed. One bounded attempt only; do not retry quota/rate errors. On any quota/rate error, stop without writes and report it.

## Git protocol

For **every Git command**, use exactly:

`/home/hermes/hermes-workspace/.hermes-control/integrations/github/git-agent.sh --role c-protocol-implementer -- <git arguments>`

No raw Git command. Commit/push only with the wrapper and only:

`push origin HEAD:refs/heads/hermes/dns-implementation-20260913`

Never merge or push master. After push, wrapper-read the exact remote ref and report it. If wrapper, immutable input, G6 authority, boundary, or validation prerequisite fails, make no production change; write a durable `BLOCKED` artifact only in your workspace and hand it back.

## Acceptance

A valid delivery has only the four authorized production paths, own assigned artifacts, and any named Resolution section; proves the required accounting/lifetime semantics; contains honest compile/test evidence; has a wrapper-mediated commit/push with exact remote readback; and returns a formal `READY_FOR_REVIEW` handoff to `protocol-orchestrator`. This assignment authorizes no downstream review or further stage.
