# Agentic artifact scaffolding

Read [the operating manual](../docs/agentic/README.md).
`templates/` contains uninstantiated records; `schemas/` describes the two core
machine-readable interchange shapes. No workflow is started by these files.

Future authorized requests create `workflows/<unique-work-id>/` with a request,
manifest, state, artifact revisions, review gates and handoffs. Git is the history
store; Hermes is the runtime. There is no script, server, database, build dependency
or generated production functionality in this framework.

See [ARTIFACTS.md](../docs/agentic/ARTIFACTS.md) for ownership and
[WORKFLOW.md](../docs/agentic/WORKFLOW.md) for resumption.

