# Wi-SUN BR/NR Firmware Project  
Firmware for Border Router (BR) and Node Router (NR) devices based on the Silicon Labs EFR32FG25A121F1152IM56 (Ebyte E51 module).

This project replaces wired RS-485 meter communication with a Wi-SUN FAN 1.1 network, enabling Push3 to multicast meter requests through a BR to multiple distributed NRs.

---

## 📦 Project Overview

This repository contains:

- Clean, maintainable firmware (no Simplicity Studio auto-generated code)
- Separate BR and NR applications
- Manual Makefile-based build system
- RS-485 UART driver (9600/8/N/1)
- Wi-SUN stack wrapper for multicast/unicast traffic
- Platform layer for FG25 hardware
- VS Code development environment
- Simplicity Studio wrapper project for flashing & debugging

---

## 🧰 Development Environment

### Primary IDE  
**VS Code**  
- Editing  
- Build (Makefile)  
- Debugging (Cortex-Debug + J-Link)

### Secondary Tools  
**Simplicity Studio 5**  
- Device support  
- Gecko SDK  
- Wi-SUN SDK  
- Flashing/debugging via Simplicity Commander  
- No auto-generated code  

---

## 🔧 Toolchain Requirements

| Component | Version |
|----------|---------|
| Simplicity Studio 5 | Latest |
| GNU Arm Toolchain | **12.2.rel1 (2023.07)** |
| Gecko SDK Suite | **v4.4.x** |
| Wi-SUN SDK | Included in GSDK |
| Device Support | EFR32FG25 |

---

## 🚀 Quick Start

### 1. Activate toolchain environment

source tools/env-setup.sh

### 2. Build firmware

make br # build Border Router firmware
make nr # build Node Router firmware
make all

### 3. Flash firmware (via Simplicity Commander)
make flash TARGET=br
make flash TARGET=nr

### 4. Debug (VS Code)
Press **F5** (Cortex-Debug).

## 📂 Project Structure
├── app/
│ ├── br/ # Border Router application
│ └── nr/ # Node Router application
├── platform/ # HAL, clock, radio, Wi-SUN glue
├── wsun/ # Wi-SUN API wrapper
├── drivers/ # UART, GPIO, timers
├── boards/ # board pin definitions & init
├── common/ # logging, utils
├── ldscripts/ # linker scripts
├── tools/ # flash + studio project generator
├── docs/ # toolchain & onboarding docs
└── Makefile # top-level build

## 🧪 Smoke Test

After flashing BR and NR:

1. Connect BR UART to terminal  
2. Expect output:  
[BR] Boot OK
[BR] Wi-SUN init done

3. Connect NR  
4. Expect:  
[NR] Boot OK
[NR] Wi-SUN join in progress...

## 📘 Documentation

- `docs/toolchain.md` — exact toolchain versions and setup
- `docs/onboarding.md` — developer onboarding guide
- `tools/gen_studio_project.sh` — generate Simplicity Studio wrapper
- `tools/env-setup.sh` — exports GCC + SDK paths