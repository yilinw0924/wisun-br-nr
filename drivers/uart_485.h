#ifndef UART_485_H
#define UART_485_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "em_eusart.h"
#include "em_gpio.h"

typedef struct {
    EUSART_TypeDef *eusart;
    GPIO_Port_TypeDef tx_port;
    uint8_t tx_pin;
    GPIO_Port_TypeDef rx_port;
    uint8_t rx_pin;

    GPIO_Port_TypeDef rts_port; // DE/RE pin
    uint8_t rts_pin;

    uint32_t baudrate;
} uart485_config_t;

void uart485_init(const uart485_config_t *cfg);
void uart485_send(const uint8_t *data, uint16_t len);
bool uart485_rx_available(void);
uint8_t uart485_read_byte(void);

#endif
