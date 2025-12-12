#include "uart.h"
#include "em_cmu.h"
#include "em_device.h"

static EUSART_TypeDef *g_uart;
static volatile uint8_t rx_buffer[256];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

void uart_init(const uart_config_t *cfg)
{
    g_uart = cfg->eusart;

    // --- Enable EUSART clock ---
    if (g_uart == EUSART0) {
        CMU_ClockEnable(cmuClock_EUSART0, true);
    } else if (g_uart == EUSART1) {
        CMU_ClockEnable(cmuClock_EUSART1, true);
    }

    CMU_ClockEnable(cmuClock_GPIO, true);

    // --- Configure GPIO pins ---
    GPIO_PinModeSet(cfg->tx_port, cfg->tx_pin, gpioModePushPull, 1);
    GPIO_PinModeSet(cfg->rx_port, cfg->rx_pin, gpioModeInputPull, 1);

    // Route pins to EUSART
    uint8_t idx = EUSART_NUM(g_uart);
    GPIO->EUSARTROUTE[idx].TXROUTE = 
        (cfg->tx_port << _GPIO_EUSART_TXROUTE_PORT_SHIFT) |
        (cfg->tx_pin  << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
    GPIO->EUSARTROUTE[idx].RXROUTE = 
        (cfg->rx_port << _GPIO_EUSART_RXROUTE_PORT_SHIFT) |
        (cfg->rx_pin  << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
    GPIO->EUSARTROUTE[idx].ROUTEEN = 
        GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN;

    // --- Setup UART parameters using em_eusart.h defaults ---
    EUSART_UartInit_TypeDef init = EUSART_UART_INIT_DEFAULT_HF;
    init.baudrate = cfg->baudrate;
    init.parity   = eusartNoParity;
    init.stopbits = eusartStopbits1;
    init.databits = eusartDataBits8;

    EUSART_UartInitHf(g_uart, &init);

    // --- Enable RX interrupt ---
    EUSART_IntEnable(g_uart, EUSART_IEN_RXFL);
    NVIC_EnableIRQ(EUSART0_RX_IRQn);   // Adjust for instance (EUSART1_RX_IRQn, etc.)
}

void EUSART0_RX_IRQHandler(void)
{
    uint32_t flags = EUSART_IntGet(g_uart);
    EUSART_IntClear(g_uart, flags);

    if (flags & EUSART_IF_RXFL) {
        uint8_t b = EUSART_Rx(g_uart);
        rx_buffer[rx_head++] = b;
        rx_head &= 0xFF;
    }
}

bool uart_rx_available(void)
{
    return rx_head != rx_tail;
}

uint8_t uart_read_byte(void)
{
    uint8_t b = rx_buffer[rx_tail++];
    rx_tail &= 0xFF;
    return b;
}

void uart_send_byte(uint8_t b)
{
    while (!(g_uart->STATUS & EUSART_STATUS_TXIDLE));
    EUSART_Tx(g_uart, b);
}

void uart_send_buffer(const uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        uart_send_byte(data[i]);
    }
}
