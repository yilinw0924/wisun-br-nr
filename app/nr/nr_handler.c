#include "nr_handler.h"
#include "stack_if.h"
#include "log.h"
#include "uart_485.h"
#include <string.h>
#include <stdint.h>

#define BR_PORT 4000
static uint8_t saved_br_ipv6[16];
static uint8_t meter_req_buf[512];
static uint16_t meter_req_len = 0;

/* Forward */
static void wsun_rx_cb(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6);
static void rs485_rx_cb(const uint8_t *data, uint16_t len);

void nr_handler_init(void)
{
    LOG_INFO("[NR] nr_handler_init");
    wsun_register_rx_cb(wsun_rx_cb);
    uart485_register_rx_cb(rs485_rx_cb);
}

/* This is called when NR receives a multicast (or unicast request) from BR */
static void wsun_rx_cb(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6)
{
    LOG_INFO("[NR] wsun_rx_cb payload len=%u", (unsigned)len);
    if (src_ipv6) {
        memcpy(saved_br_ipv6, src_ipv6, 16);
    } else {
        memset(saved_br_ipv6, 0, 16);
    }

    if (len > sizeof(meter_req_buf)) len = sizeof(meter_req_buf);
    memcpy(meter_req_buf, payload, len);
    meter_req_len = (uint16_t)len;

    // Forward to local meter
    uart485_send(meter_req_buf, meter_req_len);
    // Wait: reply will come via rs485_rx_cb
}

/* Called when RS-485 driver receives the meter reply.
   This will send a unicast back to the BR (saved_br_ipv6) using wsun_send_multicast()
   with dest address equal to saved BR IPv6 (treated as unicast).
*/
static void rs485_rx_cb(const uint8_t *data, uint16_t len)
{
    LOG_INFO("[NR] rs485_rx_cb meter reply len=%u", (unsigned)len);
    if (saved_br_ipv6[0] == 0) {
        LOG_WARN("[NR] No BR IPv6 saved; cannot reply");
        return;
    }

    int rc = wsun_send_multicast(saved_br_ipv6, BR_PORT, data, len);
    if (rc != 0) {
        LOG_ERROR("[NR] wsun_send_multicast(unicast) failed rc=%d", rc);
    } else {
        LOG_INFO("[NR] Sent reply to BR");
    }
}
