# OpenAI model and reasoning policy

ACTIVE ROLE remains the specialist's role; model selection does not change ownership,
permissions, required reading, or review gates. This policy applies to future work.
It does not configure Hermes, make API calls, or authorize implementation.

## Scope and source baseline

Reviewed 2026-09-13. “ChatGPT models” here means OpenAI models available through the
developer's configured Hermes provider. Use explicit provider model IDs, not ChatGPT
UI labels such as a thinking mode. Availability and supported settings depend on the
account and route; a model listed in documentation is not proof of account access.

OpenAI identifies Luna as cost-oriented, Terra as balanced, Sol for complex work,
and Astra for the hardest work. The table below snapshots standard input/output
prices per million tokens; it excludes caching discounts, tools, special service
tiers and provider markups. Verify current prices before estimating spend.
[Official model catalogue](https://developers.openai.com/api/docs/models).

| Model ID | Policy use | Input / output USD per million tokens |
| --- | --- | --- |
| `gpt-5.6-luna` | Bounded evidence collection and documentation | $0.20 / $1.20 |
| `gpt-5.6-terra` | Most analysis, modeling, verification and binding work | $2 / $12 |
| `gpt-5.6-sol` | High-consequence design and independent review | $4 / $20 |
| `gpt-6-astra` | Exceptional unresolved cross-component problems | $10 / $50 |

These role assignments are repository recommendations, not published OpenAI
benchmarks for Ratatoskr. Evaluate acceptance quality and total usage on completed
work before changing defaults. OpenAI recommends choosing models against quality,
cost and latency needs; a cheaper model that needs repeated repair can cost more.
[Model selection guidance](https://developers.openai.com/api/docs/guides/model-selection).

## Default for every role

Use the default for a bounded assignment with its required inputs available. Review
assignments use the reviewer's row, not the artifact author's setting. All reviewers
remain independent even when they use the same model family as the author.

| Active role | Default model | Reasoning | Escalate when / next setting |
| --- | --- | --- | --- |
| protocol-orchestrator | `gpt-5.6-terra` | `low` | Novel dependency graph or conflicting scope: Terra `medium`; unresolved coordination: Sol `medium` |
| protocol-researcher | `gpt-5.6-luna` | `low` | Large update/errata graph or missed sources: Terra `medium`; interpretation still belongs to analyst |
| protocol-analyst | `gpt-5.6-terra` | `medium` | Conflicting normative rules or subtle state/framing requirements: Sol `high` |
| protocol-modeler | `gpt-5.6-terra` | `medium` | Coupled state machines, multiplexing or difficult semantic invariants: Sol `high` |
| protocol-api-designer | `gpt-5.6-sol` | `medium` | Complex ownership, streaming/callback ABI or binary evolution: Sol `high` |
| vector-designer | `gpt-5.6-terra` | `medium` | Bit-level ambiguity or complex temporal expectations: Sol `high`; missing truth goes upstream |
| c-protocol-implementer | `gpt-5.6-terra` | `medium` | Concurrency, arithmetic/lifetime defects or intricate incremental state: Sol `high` |
| protocol-test-engineer | `gpt-5.6-terra` | `medium` | Nondeterministic state/transport failures or hard oracle/harness distinction: Sol `high` |
| security-reviewer | `gpt-5.6-sol` | `high` | Unresolved adversarial interaction across components: Astra `high`, restricted to that finding |
| fuzz-engineer | `gpt-5.6-terra` | `medium` | Stateful generation/invariant design or difficult failure minimization: Sol `high` |
| binding-api-designer | `gpt-5.6-terra` | `medium` | Unclear runtime/callback ownership or unsafe ABI representation: Sol `high` |
| binding-implementer | `gpt-5.6-terra` | `low` | New FFI/lifetime/async patterns: Terra `medium`; unresolved concurrency: Sol `high` |
| conformance-reviewer | `gpt-5.6-terra` | `medium` | Native/adapter/binding discrepancies not localized by evidence: Sol `high` |
| documentation-writer | `gpt-5.6-luna` | `low` | Cross-document contract conflicts or substantial framework architecture changes: Terra `medium` |
| compatibility-reviewer | `gpt-5.6-sol` | `medium` | ABI layout, lifetime, version negotiation or multi-runtime break: Sol `high` |
| final-reviewer | `gpt-5.6-sol` | `medium` | Conflicting gate evidence or wide cross-component impact: Sol `high` |

Start directly at the listed escalation setting when the assignment clearly meets
its trigger. Do not pay for a predictable failed cheap attempt. Conversely, do not
upgrade every stage because one stage needed a stronger model. For simple binding
work, `low` assumes the mapping and established FFI conventions are already approved.

## Reasoning and token use

Lower model prices reduce cost per token, not necessarily token count. Reduce total
tokens through bounded context, clear acceptance, fewer repeated calls and suitable
reasoning effort. Reasoning tokens are billed as output even when not visible, and
reasoning effort is a depth control, not a hard token budget. A short final answer
alone does not establish a cheap run.
[Reasoning-token guidance](https://developers.openai.com/api/docs/guides/reasoning).

Use `low` for well-specified routing/extraction/wrapping, `medium` for multi-step
technical reasoning, and `high` for the explicit difficult cases above. Do not
default to `xhigh` or `max`; justify and bound any exceptional use in the assignment.
Do not assume `none`, `minimal`, or `ultra` is supported because a client UI accepts
the label. The selected model/provider must support the requested effort.
[Supported models and efforts](https://developers.openai.com/api/docs/models).

## Assignment budget and escalation rules

These are soft operating targets, not Hermes/API limits or measured guarantees:

- Keep a delegation packet around 500–1,000 words: exact paths, source sections,
  revisions, boundary, deliverables and criteria. Do not paste parent chat or whole
  repository files when file references suffice.
- Start with roughly 8,000–16,000 tokens of task-specific context where practical.
  Read every required instruction/source section fully; split a large RFC inventory
  into scoped source groups rather than truncating evidence or omitting requirements.
- Load the active skill and required shared contracts, not all 16 full skills into
  each worker. Reuse approved inventories/models and review the relevant diff.
- Aim for 200–400 words in the completion summary plus artifact links. Artifact size
  follows completeness requirements; do not omit cases or findings to meet a quota.
- Allow one evidence-driven correction on the default setting. If the same quality
  failure remains, produce a concise failure/handoff record and escalate the bounded
  problem once. Then return unresolved decisions to the owner/orchestrator rather
  than repeating an unbounded model ladder.
- Missing sources, authority, tools or an upstream decision call for a handoff, not
  more reasoning. Do not resend the same context hoping a stronger model invents it.
- Keep concurrent delegation at one or two children initially. Parallelize disjoint
  work for latency, not as a claimed token saving. Avoid duplicate full-document
  reviews and speculative branches; preserve required independent gate review.

Use Astra only after a documented Sol failure on an available-evidence problem,
or an explicit user choice. Keep normal escalation within the predeclared scope
and spend authority. If a user supplied a monetary/token cap, do not exceed it;
checkpoint artifacts and report the remaining work instead of marking it complete.
Without a hard cap, use the bounded escalation policy above without repeatedly
asking for approval for routine settings changes.

An API output-token cap is per response, not a workflow budget; an overly small cap
can cut off reasoning and trigger retries. Do not impose tiny hard response caps on
design/code artifacts. Record actual input, output and reasoning usage when the
runtime exposes it; use `unknown` otherwise. Avoid double-counting reasoning tokens
when they are already included in the provider's output total.

## Applying this policy in Hermes

The role matrix is an instruction policy, not automatic model dispatch. Current
Hermes uses `delegation.model` for all delegated children and has no per-task model
argument. An unset delegation model inherits the parent model. Writing a model name
inside a prompt or SKILL.md does not switch the model.
[Hermes delegation model override](https://hermes-agent.nousresearch.com/docs/user-guide/features/delegation#model-override).

Before assigning work, the orchestrator records requested model/effort and verifies
the actual configured route. Group only roles compatible with the same setting in
one delegated batch. For a different tier, use a separately configured Hermes
session/profile and the durable delegation packet. Do not change a shared profile
under active children. Do not silently run security review on a cheaper inherited
worker model. If the selected route is unavailable, report the mismatch and select
an explicitly documented equivalent or leave the assignment ready for another session.

Hermes documents `agent.reasoning_effort`, `/reasoning` and per-model reasoning
overrides. Check effective settings for the installed provider and child; a desired
value in the packet is not proof that it was sent. These templates introduce no
unsupported `delegation.reasoning_effort` key.
[Hermes reasoning configuration](https://hermes-agent.nousresearch.com/docs/user-guide/configuration#reasoning-effort).

An illustrative developer-local configuration for a Terra/medium work session is:

```yaml
model:
  default: gpt-5.6-terra
agent:
  reasoning_effort: medium
delegation:
  model: gpt-5.6-terra
```

Merge only after checking installed Hermes configuration and provider spelling.
Provider/auth setup remains local and is intentionally omitted. Use Luna/low for
compatible cheaper batches and Sol/high for security batches by configuring the
corresponding session before work starts. This repository does not write local
config, install providers, or verify subscription/API billing entitlements.

## Durable evidence and tuning

The [delegation template](../../.agentic/templates/delegation.md) records requested
settings, observed route, budget/stopping policy and escalation trigger. The
[completion template](../../.agentic/templates/completion-report.md) records actual
settings, attempts, usage if exposed and deviations. Workflow assignments already
reference delegation paths; keep detailed model policy there rather than duplicating
it in the state schema. A new session can recover the choice from those files.

After a few representative accepted assignments, compare total usage including failed
attempts/reviews, elapsed time, gate rejection rate and escaped defects. Lower effort
or model tier only when acceptance quality holds; increase it only for a measured
quality problem. Recheck official model IDs, efforts, pricing and Hermes routing
on model/provider upgrades. No policy choice may weaken a review gate to save tokens.
