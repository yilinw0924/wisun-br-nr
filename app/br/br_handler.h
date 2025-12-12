#ifndef BR_HANDLER_H
#define BR_HANDLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Initialize BR handler (register callbacks, etc.) */
void br_handler_init(void);

/**
 * Called by the Push3 interface (or test harness) to request a meter read.
 * The BR will multicast the payload to the NR group and return 0 on successful send.
 */
int br_send_meter_request_from_push3(const uint8_t *payload, uint16_t len);

/** Called by wsun wrapper when an NR unicast reply arrives */
void br_handle_nr_reply(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6);

#ifdef __cplusplus
}
#endif

#endif // BR_HANDLER_H
