#!/bin/bash
#
# Environment setup for Wi-SUN BR/NR firmware project.
# Loads GNU ARM toolchain and Gecko SDK paths from Simplicity Studio 5.
#

echo "Setting up build environment..."

# >>>>>> MODIFY THESE PATHS FOR YOUR SYSTEM <<<<<<

# Path to GNU Arm Toolchain installed by Simplicity Studio
export GNU_ARM_PATH="C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\12.2.rel1_2023.7\bin"

# Path to Silicon Labs Gecko SDK
export SILABS_SDK="../simplicity_sdk_2025.6.2"

# Path to Wi-SUN FAN stack inside SDK
export WISUN_SDK="$SILABS_SDK/protocol/wisun"

# Add GCC toolchain to PATH
export PATH="$GNU_ARM_PATH:$PATH"

# Export CC/LD variables so Makefile does not need absolute paths
export CC="arm-none-eabi-gcc"
export LD="arm-none-eabi-gcc"
export OBJCOPY="arm-none-eabi-objcopy"
export AR="arm-none-eabi-ar"

echo "Done."
echo "GNU Arm Toolchain: $GNU_ARM_PATH"
echo "Gecko SDK path   : $SILABS_SDK"
echo "Wi-SUN stack path: $WISUN_SDK"
