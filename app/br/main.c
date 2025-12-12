#include "log.h"
#include "board_init.h"
#include "stack_if.h"
#include "br_handler.h"
#include "uart_485.h"

int main(void)
{
    board_init();
    log_init();
    uart485_init(9600);

    LOG_INFO("[BR] boot");

    wsun_init();
    wsun_start_border_router();

    br_handler_init();

    // smoke test: send sample to multicast group
    const uint8_t sample[] = {0x11,0x22,0x33};
    wsun_send_multicast((const uint8_t*)"\xff\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xaa\xbb\xcc\xdd", 4000, sample, sizeof(sample));

    while (1) {
        wsun_process();
        uart485_poll();
    }
    return 0;
}
