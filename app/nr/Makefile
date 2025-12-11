###############################################################################
# NR Firmware Makefile
###############################################################################

APP := nr

CFLAGS += -mcpu=cortex-m33 -mthumb -O2 -g3
CFLAGS += -ffunction-sections -fdata-sections -Wall
CFLAGS += -I../../platform -I../../drivers -I../../common
CFLAGS += -I../../wsun -I../../boards/board_v1_3
CFLAGS += -DNR_DEVICE

APP_SRCS = \
    main.c \
    nr_handler.c

APP_OBJS = $(APP_SRCS:.c=.o)

all: $(APP)

$(APP): $(APP_OBJS)
	$(MAKE) -C ../../platform CC=$(CC)
	$(LD) $(CFLAGS) -T $(LDSCRIPT) -Wl,--gc-sections \
		-o $(BUILD_DIR)/$(APP).elf \
		$(APP_OBJS) ../../platform/*.o
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).hex
	@echo "NR firmware built: $(BUILD_DIR)/$(APP).hex"

clean:
	rm -f $(APP_OBJS)

.PHONY: all clean
