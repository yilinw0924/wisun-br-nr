#include "br_handler.h"
#include "stack_if.h"
#include "log.h"
#include <string.h>
#include <stdio.h>
#include "../common/ipv6_utils.h"
#include "push3_if.h"

/* Multicast group used by BR->NR requests (example) */
static const uint8_t BR_NRS_MULTICAST_ADDR[16] = {
    0xff, 0x03, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x12,0x34,0x56,0x78
};

static const uint16_t PUSH3_PORT = 4000;

/* Local buffer for collecting NR responses if you want to aggregate */
#define MAX_REPLY 512

void br_handler_init(void)
{
    LOG_INFO("[BR] br_handler_init");
    wsun_register_rx_cb(br_handle_nr_reply);
}

/* Called by external Push3 interface. Returns 0 if multicast sent. */
int br_send_meter_request_from_push3(const uint8_t *payload, uint16_t len)
{
    if (!payload || len == 0) {
        LOG_WARN("[BR] empty push3 request");
        return -1;
    }
    LOG_INFO("[BR] push3 -> multicast to NRs, len=%u", (unsigned)len);
    int rc = wsun_send_multicast(BR_NRS_MULTICAST_ADDR, PUSH3_PORT, payload, len);
    if (rc != 0) {
        LOG_ERROR("[BR] wsun_send_multicast failed rc=%d", rc);
        return -1;
    }
    return 0;
}

/* Called by wsun wrapper when an NR replies to BR.
   We forward the reply to Push3 (via push3_if) including the NR NodeID (src_ipv6).
*/
void br_handle_nr_reply(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6)
{
    char ip6str[64];
    if (src_ipv6) {
        ipv6_to_str(src_ipv6, ip6str, sizeof(ip6str));
    } else {
        snprintf(ip6str, sizeof(ip6str), "(unknown)");
    }
    LOG_INFO("[BR] Received NR reply from %s len=%u", ip6str, (unsigned)len);

    // For push3 forwarding, create a small message that contains NodeID + payload
    // Push3 protocol is external — here we call a stub helper that sends NodeID+payload.
    push3_forward_meter_reply(src_ipv6, payload, len);
}
