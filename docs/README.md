# Ratatoskr documentation

## Contracts

- [Architecture](architecture.md)
- [Repository layout and dependency rules](repository-layout.md)
- [C ABI, ownership, and compatibility](abi.md)
- [DNS behavior](dns.md)
- [DNS RFC compliance](dns-rfc-compliance.md)

## Guides

- [Agentic engineering manual and Hermes setup](agentic/README.md)
- [Build and contribution guide](contributing.md)
- [Protocol analysis and core validation plan](protocol-validation-plan.md)
- [.NET compatibility migration](migration-dotnet.md)
- [Java and Maven binding](../bindings/java/README.md)
- [Python and PyPI binding](../bindings/python/README.md)
- [Publishing](publishing.md)
- [CLI manual page](man/ratos.1)

## Legacy .NET reference

The [API reference](api-reference.md), [usage guide](usage.md), [record guide](records.md),
[DNS fundamentals](dns-fundamentals.md), and [troubleshooting guide](troubleshooting.md)
describe the preserved `DNS.Client` compatibility surface. New code should prefer the
canonical Ratatoskr API.
