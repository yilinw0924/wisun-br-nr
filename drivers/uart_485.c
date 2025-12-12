#include "uart_485.h"
#include "em_cmu.h"

static EUSART_TypeDef *g_485;
static GPIO_Port_TypeDef rts_port_g;
static uint8_t rts_pin_g;

static volatile uint8_t rx_buf_485[256];
static volatile uint16_t rx_h_485 = 0;
static volatile uint16_t rx_t_485 = 0;

void uart485_init(const uart485_config_t *cfg)
{
    g_485 = cfg->eusart;

    if (g_485 == EUSART0) {
        CMU_ClockEnable(cmuClock_EUSART0, true);
    } else if (g_485 == EUSART1) {
        CMU_ClockEnable(cmuClock_EUSART1, true);
    }

    CMU_ClockEnable(cmuClock_GPIO, true);

    // TX, RX pins
    GPIO_PinModeSet(cfg->tx_port, cfg->tx_pin, gpioModePushPull, 1);
    GPIO_PinModeSet(cfg->rx_port, cfg->rx_pin, gpioModeInputPullFilter, 1);

    // RTS pin (DE/RE)
    rts_port_g = cfg->rts_port;
    rts_pin_g  = cfg->rts_pin;
    GPIO_PinModeSet(rts_port_g, rts_pin_g, gpioModePushPull, 0);
    GPIO_PinOutClear(rts_port_g, rts_pin_g);

    uint8_t idx = EUSART_NUM(g_485);
    GPIO->EUSARTROUTE[idx].TXROUTE =
        (cfg->tx_port << _GPIO_EUSART_TXROUTE_PORT_SHIFT) |
        (cfg->tx_pin  << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
    GPIO->EUSARTROUTE[idx].RXROUTE =
        (cfg->rx_port << _GPIO_EUSART_RXROUTE_PORT_SHIFT) |
        (cfg->rx_pin  << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
    GPIO->EUSARTROUTE[idx].ROUTEEN =
        GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN;

    EUSART_UartInit_TypeDef init = EUSART_UART_INIT_DEFAULT_HF;
    init.baudrate = cfg->baudrate;

    EUSART_UartInitHf(g_485, &init);

    // Enable RX interrupt
    EUSART_IntEnable(g_485, EUSART_IEN_RXFL);

    NVIC_EnableIRQ(EUSART1_RX_IRQn); // Adjust instance
}

void uart485_send(const uint8_t *data, uint16_t len)
{
    GPIO_PinOutSet(rts_port_g, rts_pin_g);   // Enable driver

    for (uint16_t i = 0; i < len; i++) {
        EUSART_Tx(g_485, data[i]);
        while (!(g_485->STATUS & EUSART_STATUS_TXIDLE));
    }

    GPIO_PinOutClear(rts_port_g, rts_pin_g); // Disable driver
}

bool uart485_rx_available(void)
{
    return rx_h_485 != rx_t_485;
}

uint8_t uart485_read_byte(void)
{
    uint8_t b = rx_buf_485[rx_t_485++];
    rx_t_485 &= 0xFF;
    return b;
}

void EUSART1_RX_IRQHandler(void)
{
    uint32_t flags = EUSART_IntGet(g_485);
    EUSART_IntClear(g_485, flags);

    if (flags & EUSART_IF_RXFL) {
        uint8_t b = EUSART_Rx(g_485);
        rx_buf_485[rx_h_485++] = b;
        rx_h_485 &= 0xFF;
    }
}
