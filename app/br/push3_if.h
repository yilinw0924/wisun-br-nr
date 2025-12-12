#ifndef PUSH3_IF_H
#define PUSH3_IF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward a meter reply (with NodeID) to Push3 host.
   In your real system this would send to the BR host link (UART/RS485/USB).
*/
void push3_forward_meter_reply(const uint8_t *node_ipv6, const uint8_t *payload, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif // PUSH3_IF_H
