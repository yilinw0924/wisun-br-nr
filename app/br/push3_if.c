#include "push3_if.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include "../common/ipv6_utils.h"

void push3_forward_meter_reply(const uint8_t *node_ipv6, const uint8_t *payload, uint16_t len)
{
    char ip6[64] = {0};
    if (node_ipv6) ipv6_to_str(node_ipv6, ip6, sizeof(ip6));
    LOG_INFO("[Push3 IF] Forwarding reply from %s len=%u", ip6, (unsigned)len);

    // For now print to console for debugging
    printf("PUSH3_REPLY Node=%s PayloadLen=%u DataHex=", ip6, (unsigned)len);
    for (uint16_t i=0;i<len;i++) printf("%02X", payload[i]);
    printf("\n");
}
