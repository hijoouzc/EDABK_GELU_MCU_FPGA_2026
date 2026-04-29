
# EDABK_GELI MCU & FPGA Contest 2026

## Team Introduction

**EDABK_GELU** is a student team from EDABK, School of Electrical and Electronic Engineering - Hanoi University of Science and Technology, participating in the MCU_FPGA_2026_Contest. The team consists of 4 members:
- Nguyen Dinh Anh
- Nguyen Ba Duc
- Nguyen Van Hoi
- Nguyen Duy Quyen

## Repository Overview

This repository contains 2 main projects:

### 1. FPGA_Project
- **Function:** Design a Watchdog Timer system on FPGA (Kiwi 1P5, Gowin GW1N-UV1QN48), emulating the TPS3431 IC.
- **Highlights:**
  - Configurable via UART with a custom binary protocol.
  - Written in Verilog-2001, 27MHz clock, UART 115200 8N1.
  - Includes GUI and hardware test tool.
  - Full testbenches, resource, timing, and power reports.

### 2. MCU_Project
- **Function:** Digital clock application on SN32F407 EVK board (ARM Cortex-M0).
- **Highlights:**
  - Time display on 4 7-segment LEDs, time setting, alarm, EEPROM storage, buzzer alarm.
  - Watchdog Timer for system protection.
  - Developed with Keil MDK-ARM, standard C code.

---
*This repository is for the MCU_FPGA_2026_Contest. For more details, see each project's README.*
