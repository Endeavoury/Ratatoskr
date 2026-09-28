#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "ratatoskr/dns.h"

static void test_dns_vec_003_rejects_64_octet_label(void) {
    ratos_context *context = ratos_context_create();
    ratos_dns_endpoint endpoint;
    ratos_dns_request_options options;
    ratos_dns_request *request = NULL;
    uint8_t address[4] = {192u, 0u, 2u, 53u};
    char name[66];

    assert(context != NULL);
    memset(name, 'a', 64u);
    name[64] = '.';
    name[65] = '\0';

    ratos_dns_endpoint_init(&endpoint);
    endpoint.family = RATOS_DNS_ADDRESS_FAMILY_IPV4;
    endpoint.port = 53u;
    endpoint.address = address;
    endpoint.address_len = sizeof(address);

    ratos_dns_request_options_init(&options);
    options.upstream = &endpoint;

    assert(ratos_dns_request_start(context, name, &options, &request)
        == RATOS_ERROR_INVALID_ARGUMENT);
    assert(request == NULL);
    ratos_context_destroy(context);
}

int main(void) {
    test_dns_vec_003_rejects_64_octet_label();
    puts("G7 native DNS verification tests passed");
    return 0;
}
