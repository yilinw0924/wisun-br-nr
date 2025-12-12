###############################################################################
# Top-level Makefile for VS Code build using Simplicity standalone SDK
###############################################################################

SILABS_SDK ?= $(CURDIR)/simplicity_sdk_2025.6.2   # <<-- edit to actual path
TOOLCHAIN ?= C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/gnu_arm/12.2.rel1_2023.7/bin
CC := $(TOOLCHAIN)/arm-none-eabi-gcc
OBJCOPY := $(TOOLCHAIN)/arm-none-eabi-objcopy

BUILD_DIR := build
LDSCRIPT := ldscripts/efr32fg25.ld

INCLUDES := -Iplatform -Iwsun -Icommon -Idrivers -Iboards/board_v1_3 \
            -I"$(SILABS_SDK)/platform/CMSIS/Core/Include" \
			-I"$(SILABS_SDK)/platform/common/inc" \
            -I"$(SILABS_SDK)/platform/Device/SiliconLabs/EFR32FG25/Include" \
			-I"$(SILABS_SDK)/platform/driver/gpio/inc" \
            -I"$(SILABS_SDK)/platform/emlib/inc" \
			-I"$(SILABS_SDK)/platform/peripheral/inc" \
            -I"$(SILABS_SDK)/protocol/wisun/stack/inc" \
            -I"$(SILABS_SDK)/protocol/wisun/plugin" \
            -I"$(SILABS_SDK)/protocol/wisun/plugin/cli_util"

LDFLAGS := -L"$(SILABS_SDK)/protocol/wisun/stack/lib" \
           -L"$(SILABS_SDK)/platform/radio/rail_lib/autogen/librail_release" \
           -lwisunstack -lnanostack -lwisun_network -lrail_efr32xg25_gcc_release

CFLAGS := -mcpu=cortex-m33 -mthumb -O2 -g3 -ffunction-sections -fdata-sections \
          $(INCLUDES) -DUSE_WISUN_SDK=0

# Targets
all: br nr

br:
	@mkdir -p $(BUILD_DIR)
	$(MAKE) -C app/br CC="$(CC)" OBJCOPY="$(OBJCOPY)" BUILD_DIR="$(abspath $(BUILD_DIR))" LDSCRIPT="$(abspath $(LDSCRIPT))" SILABS_SDK="$(SILABS_SDK)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

nr:
	@mkdir -p $(BUILD_DIR)
	$(MAKE) -C app/nr CC="$(CC)" OBJCOPY="$(OBJCOPY)" BUILD_DIR="$(abspath $(BUILD_DIR))" LDSCRIPT="$(abspath $(LDSCRIPT))" SILABS_SDK="$(SILABS_SDK)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

clean:
	$(MAKE) -C app/br clean || true
	$(MAKE) -C app/nr clean || true
	rm -rf $(BUILD_DIR)

.PHONY: all br nr clean
