# STM32_BareMetel

This repository contains bare-metal code for the STM32 microcontroller, written in C without any operating system or HAL/LL libraries. It focuses on directly accessing hardware through memory-mapped registers for precise low-level control.

## 🚀 Features

- Direct register-level programming (no CMSIS, HAL, or CubeMX)
- GPIO input/output configuration
- LED control using GPIOA
- Switch (button) reading using GPIOC
- Delay implementation using software loops

## 📁 Project Structure


STM32_BareMetel/
├── main.c # Main source code with LED and switch logic
├── Makefile # For compiling the code using arm-none-eabi-gcc
├── linker.ld # Linker script for STM32 memory layout
└── startup.s # Startup code and vector table (if applicable)


## 🛠 Requirements

- STM32F4 series microcontroller (e.g., STM32F401)
- ARM GCC toolchain (`arm-none-eabi-gcc`)
- ST-Link or compatible programmer
- `openocd` or STM32CubeProgrammer for flashing

## 🔧 Build and Flash

### 🧱 Compile the Code
```bash
make

