#pragma once
#include <stdint.h>

typedef void (*wsun_rx_callback_t)(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6);

void wsun_init(void);
void wsun_start_border_router(void);
void wsun_start_node_router(void);
int  wsun_send_multicast(const uint8_t *addr6, uint16_t port, const uint8_t *buf, uint16_t len);
void wsun_register_rx_cb(wsun_rx_callback_t cb);
void wsun_process(void);

/* Helper used by SDK-based receive path to deliver payloads to app */
void wsun_invoke_rx_cb_from_sdk(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6);
