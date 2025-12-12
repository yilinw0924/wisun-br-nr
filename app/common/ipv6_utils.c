#include "ipv6_utils.h"
#include <stdio.h>

void ipv6_to_str(const uint8_t ipv6[16], char *out, int out_len)
{
    if (!ipv6 || !out) return;
    // Simple formatting: last 4 bytes as hex: xxxx:xxxx
    // For full formatting you'd do proper IPv6 compression; this is enough for logs.
    snprintf(out, out_len,
             "%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",
             ipv6[0],ipv6[1],ipv6[2],ipv6[3], ipv6[4],ipv6[5],ipv6[6],ipv6[7],
             ipv6[8],ipv6[9],ipv6[10],ipv6[11], ipv6[12],ipv6[13],ipv6[14],ipv6[15]);
}
