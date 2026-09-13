# Protocol analysis and core validation plan

Status: proposed workflow; the complete RFC audit and fixture harness remain to be
implemented. DNS is the first application because it is the existing native protocol.
Repeat this workflow for each future protocol.

The required sequence is: define scope, discover specifications, extract requirements,
design exchanges, write independently verified fixtures, validate the native core,
and publish coverage and gaps. Implementation behavior must not define the expected
protocol behavior.

## 1. Establish the protocol scope and baseline

Record the protocol, supported versions, client/server role, transports, extensions,
public API, implementation revision, and audit date. Separate protocol requirements
from Ratatoskr policies such as resource budgets and display formatting.

For DNS, start with the unicast stub/client in `src/protocols/dns`, its public contract
in `include/ratatoskr/dns.h`, and [DNS behavior](dns.md). Include query construction,
response parsing, record presentation, UDP/TCP exchange, errors, and ownership.
Classify recursive resolution, authoritative service, caching, DNSSEC validation,
and additional transports individually before including them in the test scope.
An unsupported extension still needs an explicit handling policy when encountered.

Inventory existing evidence:

- `tests/dns/dns_tests.c`: builder, record presentation, and malformed packet tests.
- `tests/integration/dns_fixture_test.py`: local UDP truncation and TCP fallback.
- `tests/core/abi_tests.c`: native ABI checks.
- `tests/fixtures/dns/README.md` and `fuzz/dns`: current fixture and fuzz inputs.

The [existing RFC matrix](dns-rfc-compliance.md) is historical managed compatibility
documentation. Use it as a discovery lead, then verify every title, applicability
decision, implementation claim, and test reference against primary sources and C code.

Deliverable: `docs/protocols/dns/scope.md`, including a baseline test result.
Exit condition: every relevant native component has an identified validation layer.

## 2. Discover and review the complete applicable specification set

Start with the protocol's foundational specifications. For DNS, RFC 1034 and RFC 1035
are discovery seeds, not a complete list. The [RFC Editor information page for RFC
1035](https://www.rfc-editor.org/info/rfc1035/) exposes its update relationships.

1. Traverse normative references and both directions of Updates/Obsoletes links.
   Maintain a visited set and follow successors recursively.
2. Search the RFC Editor and IETF Datatracker by protocol, feature, transport, and
   record type; related extensions need not formally update a foundational RFC.
3. Inspect relevant IANA registries and their referenced specifications for assigned
   fields, record types, flags, options, and error codes.
4. Review errata and record their status. Reported errata and Internet-Drafts are
   review inputs, not automatically authoritative requirements.
5. Read applicable sections, resolve updates at the requirement level, and distinguish
   standards, experimental documents, informational guidance, and obsolete behavior.
6. Classify every discovered document as applicable, optional/deferred, superseded,
   or out of scope, with a reason. Preserve excluded documents in the inventory.

Record RFC number, verified title, status, source URL, review date, relevant sections,
update/obsolescence links, errata disposition, scope decision, and reviewer notes.
Capture the source version or checksum for reproducibility, including registry snapshots.

Deliverable: `docs/protocols/dns/specifications.csv`.
Exit condition: discovery queues are empty, every discovered document is classified,
and every applicable section has been reviewed. Describe completeness relative to
the recorded scope and audit date; schedule rediscovery when scope or standards change.

## 3. Convert specifications into testable requirements

Create one stable requirement ID per independently testable rule, for example
`DNS-WIRE-HEADER-001`. Record:

| Field | Purpose |
| --- | --- |
| Source | RFC and section, including effective updates/errata |
| Rule | Paraphrased requirement and normative strength |
| Applicability | Role, feature, version, transport, and preconditions |
| Expected behavior | Observable success, rejection, ignore, retry, or unsupported result |
| Implementation | Native source/function or a confirmed implementation gap |
| Evidence | Fixture IDs, test IDs, and latest execution result |
| Disposition | Unreviewed, missing, partial, verified, or excluded with rationale |

Include rules expressed without uppercase normative keywords. Record reasons for
departures from SHOULD requirements. Keep RFC requirements, interoperability choices,
and local API/security policies distinguishable. If the correct interpretation is
unresolved, flag it for review rather than turning existing behavior into an oracle.

Deliverable: `docs/protocols/dns/requirements.csv`.
Exit condition: each applicable rule has an observable assertion or a documented
reason that packet fixtures alone cannot validate it, with an alternative check.

## 4. Design request/response exchanges before encoding bytes

For each requirement, define the setup, logical request, server messages, expected
native result, and any expected state transition. An exchange may contain several
messages or no response, as in timeout tests.

Cover these independent dimensions:

- Valid minimum and representative messages for every supported operation/record.
- Boundaries: zero, minimum, maximum, and just outside permitted sizes/counts.
- Malformed input: incomplete fields, inconsistent lengths/counts, invalid names,
  compression cycles and invalid pointers, unsupported flags, and trailing bytes.
- Correlation: unexpected transaction ID, opcode, question, class, or peer.
- Valid negative outcomes: empty answers and protocol error responses, distinguished
  from malformed packets and transport failures according to the API contract.
- Extensions and unknown values: preserve, ignore, or reject as specified.
- Transport sequences: truncation fallback, fragmented TCP prefix/body, early EOF,
  timeout, and multiple frames where applicable to the supported transport role.
- API behavior: invalid arguments, result ownership, error reporting, and cleanup.

Use one principal fault per negative fixture so its expected failure is unambiguous;
add combinations later. Label implementation gaps without claiming they pass.

Deliverable: a case catalogue mapping requirement IDs to planned fixture IDs.
Exit condition: all applicable rules have cases, including meaningful failure paths.

## 5. Produce text and byte-array fixtures from the same reviewed case

Proposed layout under `tests/fixtures/<protocol>/`:

```text
manifest.json
cases/<case-id>/case.json
cases/<case-id>/request.txt
cases/<case-id>/request.hex
cases/<case-id>/response.txt
cases/<case-id>/response.hex
generated/fixtures.h
```

Number message files for exchanges with multiple messages. Omit absent responses
explicitly in metadata. Each case records schema version, ID, requirement references,
provenance, input arguments, fixed transaction fields, transport/framing, expected
fields and text, expected native status, timing/events if needed, and byte lengths.

Text is a human-readable field explanation for binary protocols such as DNS; it is
not itself the wire encoding. For text protocols, separately preserve literal wire
text with exact encoding, line endings, separators, and byte lengths.

Make reviewed `.hex` files the authoritative wire bytes. A small test-only converter
should validate hex syntax and lengths and emit immutable `uint8_t` arrays plus
explicit lengths. It may also emit binary fuzz inputs. It must not use the production
builder/parser to derive expected packets or results. CI should detect stale generated
arrays. Review field offsets and independently decode valid examples; pin any external
decoder version and resolve disagreements against the specifications.

Never repair intentionally malformed bytes during generation. Use synthetic data,
deterministic IDs, and loopback transports; tests must not require public DNS.

### Worked DNS fixture: A query and successful response

This is a seed example, not a completed compliance claim. Message fields and name
compression follow [RFC 1035 section 4.1](https://www.rfc-editor.org/rfc/rfc1035.html#section-4.1).

`request.txt`:

```text
ID: 0x1234
Flags: 0x0100 (query, opcode QUERY, RD=1)
Counts: question=1, answer=0, authority=0, additional=0
Question: example.com. IN A
DNS message length: 29 bytes
```

`response.txt`:

```text
ID: 0x1234
Flags: 0x8180 (response, opcode QUERY, RD=1, RA=1, RCODE=NOERROR)
Counts: question=1, answer=1, authority=0, additional=0
Question: example.com. IN A
Answer: example.com. 300 IN A 192.0.2.1
Answer owner: compression pointer 0xc00c to message offset 12
DNS message length: 45 bytes
Expected native status: RATOS_OK
Expected record count: 1
Expected native record text: 192.0.2.1
```

Equivalent C byte arrays (each integer represents one octet):

```c
static const uint8_t request[] = {
    0x12, 0x34, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65,
    0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01
};

static const uint8_t response[] = {
    0x12, 0x34, 0x81, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65,
    0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01,
    0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2c,
    0x00, 0x04, 0xc0, 0x00, 0x02, 0x01
};
```

These arrays contain DNS payloads only. UDP sends them directly. TCP adds `00 1d`
before the request and `00 2d` before the response; those prefixes describe the DNS
payload length and are not counted in DNS compression offsets.
TCP framing is specified in [RFC 1035 section 4.2.2](https://www.rfc-editor.org/rfc/rfc1035.html#section-4.2.2).

For this case, compare every builder byte using fixed ID `0x1234`, then separately
parse the response with the expected ID/name/type. Assert flags, counts, owner, type,
class where observable, TTL, section, address bytes, text, and successful cleanup.
Do not substitute a builder/parser round trip for these independent expectations.

Deliverable: reviewed case files and deterministic generated arrays.
Exit condition: bytes, text, expected fields, provenance, and requirements agree.

## 6. Validate the canonical native core in layers

| Layer | Validation | Integration point |
| --- | --- | --- |
| Fixture integrity | Schema, references, lengths, generated array freshness | Test-only converter/checker |
| Builder | Fixed logical input produces exact expected bytes | `ratos_dns_build_query`, native tests |
| Parser | Fixed response bytes produce expected fields/text or exact error | `ratos_dns_parse_response`, native tests |
| Transport | Ordered scripted exchange produces correct writes, reads, fallback, and timeout | Native query API and local server fixture |
| ABI/ownership | Accessors, output validity, allocation lifetime, cleanup on success/error | Native ABI tests and sanitizers |
| Consumers | Representative CLI/binding output agrees with native results | Existing CLI integration and binding tests |

Use byte-for-byte equality for a specified deterministic encoding. Where multiple
encodings are legal, test semantic equivalence separately and state which encoding
the builder promises. Do not demand reserialization of responses unless the API
actually supports it. Handle random production query IDs by validating their use and
echoing them in the local server, rather than weakening production randomness.

Extend existing native tests and register checks in `tests/CMakeLists.txt`. Assertions
must execute in Release as well as Debug; the existing C tests use `assert`, so account
for `NDEBUG` when implementing the harness. Retain the CLI integration test and add
direct native transport coverage to localize failures.

After deterministic tests pass, run sanitizer checks and seed the existing fuzz
targets with valid and malformed fixtures. Promote minimized crashes to permanent
regression cases. Differential decoding is supporting evidence, not the final oracle.

Deliverable: executable tests that report fixture and requirement IDs on failure.
Exit condition: mandatory cases pass without leaks, invalid memory access, hangs,
or dependence on internet services. Deferred capabilities remain visible as gaps.

## 7. Publish evidence and maintain coverage

Report applicable requirements, verified requirements, failures, missing cases,
deferred features, and justified exclusions separately. Coverage is verified
applicable requirements divided by applicable requirements; raw test counts and code
coverage cannot establish RFC compliance. Include the revision, platform, build mode,
tool versions, specification snapshot, and execution date.

Use the existing `dev`, `release`, and `sanitize` CMake presets as appropriate. CI
should block on fixture drift, regressions in accepted requirements, and missing
requirement mappings for new protocol behavior. Track known gaps explicitly; do not
silently skip failures or describe the whole protocol as compliant.

## Implementation order

1. Complete the DNS scope, specification inventory, and requirement review.
2. Define the fixture schema and independently review the worked A exchange.
3. Add the converter and native builder/parser fixture runner.
4. Expand to supported records, boundary cases, malformed input, and error responses.
5. Add native transport scenarios, ownership checks, and fuzz regression fixtures.
6. Integrate CI evidence and publish a native requirements matrix.

Each step depends on the preceding deliverables. Extend this same process to the next
protocol using its own requirements and fixtures; a shared production protocol
framework is not needed to share the validation workflow.
