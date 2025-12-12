#include "stack_if.h"
#include "log.h"
#include <string.h>

#ifndef USE_WISUN_SDK
#define USE_WISUN_SDK 0
#endif

static wsun_rx_callback_t g_rx_cb = NULL;

/* If your Studio project exposes an API like sl_wisun_init or sl_wisun_start,
   we will call them here when USE_WISUN_SDK=1.
   Typical Studio Wi-SUN projects have sl_wisun_* helper files.
*/

#if USE_WISUN_SDK

/* Try to include common Studio headers; adjust if file names differ */
#include "sl_wisun.h"        // optional
#include "sl_wisun_api.h"    // optional
#include "socket_api.h"      // nanostack socket API
#include "net_ipv6.h"

static int app_socket_fd = -1;
static uint16_t app_port = 4000;

#endif

void wsun_init(void)
{
    LOG_INFO("[WSUN] init");
#if USE_WISUN_SDK
    LOG_INFO("[WSUN sdk] calling Studio Wi-SUN init helpers (if available)");

    // If your project has sl_wisun_init() or a similar function, call it here.
    // Example (uncomment when available):
    // sl_wisun_init();

    // Create socket (nanostack) if stack requires app socket
    // app_socket_fd = ns_socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
#else
    LOG_INFO("[WSUN stub] init (no SDK)");
#endif
}

void wsun_start_border_router(void)
{
    LOG_INFO("[WSUN] start_border_router");
#if USE_WISUN_SDK
    LOG_INFO("[WSUN sdk] start BR via studio helper");

    // Example pseudocode using Studio provided functions:
    // sl_wisun_br_start();
    // bind socket:
    // ns_sockaddr_t addr;
    // memset(&addr, 0, sizeof(addr));
    // addr.version = SOCKET_IPV6;
    // addr.port = app_port;
    // ns_bind(app_socket_fd, (const uint8_t*)&addr, sizeof(addr));
#else
    LOG_INFO("[WSUN stub] Border Router started; stub IPv6=fe80::1");
#endif
}

void wsun_start_node_router(void)
{
    LOG_INFO("[WSUN] start_node_router");
#if USE_WISUN_SDK
    LOG_INFO("[WSUN sdk] join network (Studio helper)");
    // Example: sl_wisun_join();
#else
    LOG_INFO("[WSUN stub] Node Router started (stub)");
#endif
}

int wsun_send_multicast(const uint8_t *addr6, uint16_t port, const uint8_t *buf, uint16_t len)
{
    LOG_INFO("[WSUN] send_multicast len=%u port=%u", (unsigned)len, (unsigned)port);
#if USE_WISUN_SDK
    if (app_socket_fd < 0) {
        LOG_ERROR("app_socket_fd invalid");
        return -1;
    }
    // Build ns_sockaddr_t dst from addr6 and port, then ns_sendto(...)
    // ns_sendto(app_socket_fd, buf, len, 0, (const uint8_t*)&dst, sizeof(dst));
    return 0;
#else
    (void)addr6; (void)port; (void)buf; (void)len;
    // stub: simulate immediate reception for development: call registered callback
    if (g_rx_cb) {
        uint8_t fake_src[16] = {0xfe,0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
        g_rx_cb(buf, len, fake_src);
    }
    return 0;
#endif
}

void wsun_register_rx_cb(wsun_rx_callback_t cb)
{
    g_rx_cb = cb;
}

void wsun_process(void)
{
#if USE_WISUN_SDK
    // If your stack needs periodic service, call it here.
#else
    // nothing in stub mode
#endif
}

void wsun_invoke_rx_cb_from_sdk(const uint8_t *payload, uint16_t len, const uint8_t *src_ipv6)
{
    if (g_rx_cb) g_rx_cb(payload, len, src_ipv6);
}
