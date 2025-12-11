###############################################################################
# Top-Level Makefile for Wi-SUN BR/NR Firmware
# Target MCU: EFR32FG25A121F1152IM56 (Ebyte E51)
###############################################################################

# Default target
TARGET ?= br

# Toolchain (Simplicity Studio installs this here)
TOOLCHAIN_PATH ?= /opt/SimplicityStudio_v5/developer/toolchains/gnu_arm/10.3_2021.10/bin
CC      := $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
LD      := $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
AR      := $(TOOLCHAIN_PATH)/arm-none-eabi-ar
OBJCOPY := $(TOOLCHAIN_PATH)/arm-none-eabi-objcopy

# Output directory
BUILD_DIR := build

# Board linker script
LDSCRIPT := ldscripts/efr32fg25.ld

# Default build
all: br nr

br:
	$(MAKE) -C app/br CC=$(CC) LD=$(LD) OBJCOPY=$(OBJCOPY) \
		BUILD_DIR=$(abspath $(BUILD_DIR)) \
		LDSCRIPT=$(abspath $(LDSCRIPT))

nr:
	$(MAKE) -C app/nr CC=$(CC) LD=$(LD) OBJCOPY=$(OBJCOPY) \
		BUILD_DIR=$(abspath $(BUILD_DIR)) \
		LDSCRIPT=$(abspath $(LDSCRIPT))

clean:
	$(MAKE) -C app/br clean
	$(MAKE) -C app/nr clean
	$(MAKE) -C platform clean
	rm -rf $(BUILD_DIR)

flash:
	tools/flash.sh $(TARGET)

open-studio:
	tools/gen_studio_project.sh

.PHONY: all br nr clean flash open-studio
