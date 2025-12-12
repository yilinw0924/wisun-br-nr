APP := nr
SRCS := main.c nr_handler.c
OBJS := $(SRCS:.c=.o)

CC ?= arm-none-eabi-gcc
OBJCOPY ?= arm-none-eabi-objcopy
BUILD_DIR ?= ../../build
LDSCRIPT ?= ../../ldscripts/efr32fg25.ld
CFLAGS += -DBR_DEVICE
LDFLAGS ?=

CFLAGS += $(CFLAGS)

all: $(BUILD_DIR)/$(APP).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(APP).elf: $(OBJS)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) -Wl,--gc-sections -o $@ $(OBJS) $(LDFLAGS)
	$(OBJCOPY) -O ihex $@ $(BUILD_DIR)/$(APP).hex
	@echo "Built $(BUILD_DIR)/$(APP).hex"

clean:
	rm -f $(OBJS) $(BUILD_DIR)/$(APP).elf $(BUILD_DIR)/$(APP).hex

.PHONY: all clean
