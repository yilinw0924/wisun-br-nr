#ifndef UART_H
#define UART_H

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
    uint32_t baudrate;
} uart_config_t;

void uart_init(const uart_config_t *cfg);
void uart_send_byte(uint8_t byte);
void uart_send_buffer(const uint8_t *data, uint16_t len);
uint8_t uart_read_byte(void);
bool uart_rx_available(void);

#endif
