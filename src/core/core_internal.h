#ifndef RATOS_CORE_INTERNAL_H
#define RATOS_CORE_INTERNAL_H
#include <stddef.h>
#include "ratatoskr/context.h"
#include "ratatoskr/error.h"
#include "ratatoskr/dns.h"
struct ratos_context { char error_message[512]; ratos_dns_limits dns_limits; };
void ratos_set_error(ratos_context *ctx, const char *format, ...);
char *ratos_strdup(const char *value);
#endif
