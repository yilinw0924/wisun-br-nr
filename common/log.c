#include "log.h"
#include "uart.h"   // default backend over UART0

void log_init(void)
{
    uart0_init(115200);    // simple debug UART
    LOG_INFO("Logger initialized");
}
