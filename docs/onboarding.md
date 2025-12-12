# Developer Onboarding Manual  
Wi-SUN BR/NR Firmware Project

Welcome! This guide will get you fully operational with the development environment for the Wi-SUN BR/NR firmware project.

---

# 1. Install Required Tools

## 1.1 Simplicity Studio 5
Install from Silicon Labs. Required packages:
- Gecko SDK Suite v4.x
- Wi-SUN SDK
- J-Link Debugger Support
- EFR32FG25 device support

## 1.2 GNU Arm Toolchain
Installed automatically in:
"C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\12.2.rel1_2023.7\bin"

## 1.3 VS Code
Extensions:
- *ms-vscode.cpptools*  
- *marus25.cortex-debug*  
- *ms-vscode.git*  

---

# 2. Activate Build Environment
source tools/env-setup.sh

This configures:
- PATH → GNU Arm toolchain
- SILABS_SDK
- WISUN_SDK
- CC / LD / OBJCOPY variables

---

# 3. Build the Firmware

## BR Firmware
make br

## NR Firmware

Artifacts appear under `/build`.


# 4. Flashing Firmware

### Using Makefile wrapper
make flash TARGET=br
make flash TARGET=nr

### Or manually:
simplicity_commander flash --device EFR32FG25A121F1152IM56 --image build/br.hex

# 5. Debugging with VS Code

1. Open `.code-workspace` file  
2. Select **Run and Debug → Cortex-Debug**  
3. Press **F5**

Breakpoints should work immediately.

---

# 6. Debugging with Simplicity Studio

Use only for:
- Flashing  
- Debug sessions  
- Energy profiler  

Do **not** use Studio code generation.

---

# 7. Project Build Architecture

### VS Code  
→ Edit code → `make br` / `make nr`

### Studio  
→ Calls Makefile automatically  
→ Provides debug interface only

---

# 8. BR/NR Applications

- **BR** forms Wi-SUN FAN network  
- **NR** joins network and bridges RS-485 → Wi-SUN

Both share platform, drivers, and wsun stack.

---

# 9. File Locations

- RS-485 UART driver → `/drivers/uart_485.c`
- Wi-SUN API → `/wsun/stack_if.c`
- BR logic → `/app/br/main.c`
- NR logic → `/app/nr/main.c`

---

# 10. Smoke Test Checklist

After flashing:

### BR:
- Boots and prints:
[BR] Boot OK
[BR] Wi-SUN init done

### NR:
- Boots and prints:
[NR] Boot OK
[NR] Wi-SUN join in progress...

---

You are now ready to begin development!