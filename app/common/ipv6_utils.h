#ifndef IPV6_UTILS_H
#define IPV6_UTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void ipv6_to_str(const uint8_t ipv6[16], char *out, int out_len);

#ifdef __cplusplus
}
#endif

#endif // IPV6_UTILS_H
