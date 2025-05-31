Example device independent blinky program written in pure C++ for RISC-V.

Example of bare-metal programming and low level coding. Details are here:

- [RISC-V: A Baremetal Introduction using C++. Intro.](https://philmulholland.medium.com/modern-c-for-bare-metal-risc-v-zero-to-blink-part-1-intro-def46973cbe7) 
- <https://www.five-embeddev.com/articles/2021/04/30/riscv-and-modern-c++-part1-1/>

https://philmulholland.medium.com/modern-c-for-bare-metal-risc-v-zero-to-blink-part-1-intro-def46973cbe7

The code will enter a main() function and enable a simple periodic ISR 
handler, and flash an LED.

Source Files:

- `src/startup.cpp`                          : Entry point from reset. Set up C++ runtime environment.
- `src/main.cpp`                             : Example main program. Configures timer interrupt for 1s periodic interrupt.
- `include/timer.hpp`                        : Device independent C++ driver for the RISC-V machine mode timer.
- `include/riscv-csr.hpp`                    : C++ class abstraction to access RISC-V CSRs (Generated file)
- `include/riscv-interrupts.hpp`             : List of RISC-V machine mode interrupts.
- `include/mmio_device.hpp`                  : Basic abstraction for MMIO register access.
- `include/device/sifive_gpio0_0_mmio_*.hpp` : Register definitions generated from SiFive's SVD definition.

The code is for the SiFive HiFive1 RevB board - but it should be
easily portable to any RISC-V RV32I or RV32E core. The objective is
for this to be able to be used to experiment with custom RISC-V cores
and SoCs without the need for a vendor BSP or SDK.

Build Files:

- `platformio.ini`       : Configuration for PlatformIO
- `post_build.py`        : Post build script

Other Files:

- `src/linker.lds`       : Linker script for SiFive HiFive revb board (from the metal environment).

Credits:
 - Linker file and GPIO register definitions from SiFive's Freedom-e-SDK: https://github.com/sifive/freedom-e-sdk.git
 - Startup code based on [Christopher Kormanyos's Real Time C++](https://github.com/ckormanyos/real-time-cpp).
 - Plain startup code and timer driver at: https://github.com/five-embeddev/riscv-scratchpad/tree/master/baremetal-startup-cxx
 - CSR access code from : https://github.com/five-embeddev/riscv-csr-access

