###############################################################################
# Platform Makefile: HAL + Drivers + Wi-SUN Wrapper
###############################################################################

CFLAGS += -mcpu=cortex-m33 -mthumb -O2 -g3
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -I. -I../drivers -I../boards/board_v1_3 -I../wsun -I../common
CFLAGS += -DPLATFORM_EFR32FG25

PLATFORM_SRCS = \
    platform_init.c \
    platform_clock.c \
    platform_radio.c \
    ../drivers/uart_485.c \
    ../drivers/gpio.c \
    ../common/log.c \
    ../wsun/stack_if.c \
    ../boards/board_v1_3/board_init.c

PLATFORM_OBJS = $(PLATFORM_SRCS:.c=.o)

all: $(PLATFORM_OBJS)

clean:
	rm -f $(PLATFORM_OBJS)

.PHONY: all clean
