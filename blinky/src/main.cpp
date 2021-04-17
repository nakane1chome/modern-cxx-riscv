/*
   Simple C++ RISC-V blinky program
   SPDX-License-Identifier: Unlicense

   (Phil Mulholland @ http://www.shincbm.com/) 

   Example of Modern C++ programming for the RISC-V processor

   Setup a periodic timer using std::chrono and execute a lambda
   function as an interrupt handler to perform the classic one second
   LED blink exercise.

*/

// RISC-V CSR definitions and access classes
#include "riscv-csr.hpp"

// RISC-V interrupt definitions
#include "riscv-interrupts.hpp"

// MMIO Device interface definition.
// These are generated from:
// freedom-e-sdk/bsp/sifive-hifive1-revb/design.svd
#include "device/sifive_gpio0_0_mmio_dev.hpp"

// Generic machine mode timer driver
#include "timer.hpp"

// Misc utils
#include "util.hpp"

// Base address for GPIO MMIO
static constexpr uintptr_t SIFIVE_GPIO0_0 = 0x10012000;
// LED location, from freedom-e-sdk/bsp/sifive-hifive1-revb/core.dts
static constexpr int LED_RED=22;
static constexpr int LED_GREEN=19;
static constexpr int LED_BLUE=21;
static constexpr unsigned int LED_MASK_WHITE=util::bitmask(LED_RED)|util::bitmask(LED_GREEN)|util::bitmask(LED_BLUE);

// Place the IRQ related code in a seperate namespace
namespace irq {
    // Machine mode interrupt service routine
    // Defined as an interrupt function to ensure correct 'mret' exit is generated.
    static void entry(void) __attribute__ ((interrupt ("machine")));

    /** IRQ Handler class. Allows a lambda function (or other function
     * object) to be registered as the machine mode IRQ hander.
     */
    class handler {
    public:
        /** Create an IRQ handler class to install a 
            function as the machine mode irq handler */
        template<class T> handler(T const &isr_handler);
        // Boilerplate delete defaults - non copyable class
        handler(const handler&) = delete;
        handler &operator=(const handler&) = delete;
        handler(handler&&) = delete;
        handler &operator=(handler&&) = delete;
    private :
        inline static void (*_execute_handler)(void); 
        // Trampoline function is required to bridge from the entry point
        // function declared with specific attributes and alignments to this class member.
        friend void entry(void);
        static inline void handler_entry(void) {
            _execute_handler();
        }
    };
}

int main(void) {

    // Device drivers
    driver::sifive_gpio0_0_dev<SIFIVE_GPIO0_0> gpio_dev;
    driver::timer<> mtimer;

    // Device Setup       

    // Save the timer value at this time.
    auto timestamp = mtimer.get_time<driver::timer<>::timer_ticks>().count();
    // Setup timer for 1 second interval
    // std::chrono allows us to specify the time units in
    // We could even use `1 s` via chrono::literals
    // This comes at no cost as the timer driver has defined it's hardware clock period as a type timer::timer_ticks
    // and the conversion via std::chrono::duration_cast<timer_ticks>() is done at compile time
    mtimer.set_time_cmp(std::chrono::seconds{1});

    // Enable GPIO
    gpio_dev.output_val &= ~(LED_MASK_WHITE);
    gpio_dev.output_en  |=  (LED_MASK_WHITE);

    // The periodic interrupt lambda function.
    // The context (drivers etc) is captured via reference using [&]
    static const auto handler = [&] (void) 
        {
            // In RISC-V the mcause register stores the cause of any interrupt or exception.            
            auto this_cause = riscv::csrs.mcause.read();
            // For simplicity non-vectored interrupt mode is used. 
            // The top bit of the mcause register indicates if this is an interrupt or exception.
            if (this_cause &  riscv::csr::mcause_data::interrupt::BIT_MASK) {
                this_cause &= 0xFF;
                // De-multiplex the interrupt
                // The cause register LSBs hold an integer value that represents the interrupt source
                switch (this_cause) {
                case riscv::interrupts::mti :
                    // A machine timer interrupt
                    // RISC-V machine mode timer interrupts are not repeating.
                    // Set the timer compare register to the current time + one second
                    mtimer.set_time_cmp(std::chrono::seconds{1});
                    // Save the timestamp as a raw counter in units of the hardware counter.
                    // While there is quite a bit of code here, it can be resolved at compile time to a simple
                    // MMIO register read.
                    timestamp = mtimer.get_time<driver::timer<>::timer_ticks>().count();
                    // Xor to invert. This can be compiled to a write to the toggle register via operator overloading.
                    gpio_dev.output_val ^= (LED_MASK_WHITE);
                    break;
                }
            }
            // TODO - else handle exceptions - for simplicity exceptions are not handled.
        };

    // Install the above lambda function as the machine mode IRQ handler.
    irq::handler irq_handler(handler);

    // Enable interrupts
    riscv::csrs.mie.mti.set();
    // Global interrupt enable
    riscv::csrs.mstatus.mie.set();

    // Busy loop
    do {
        __asm__ volatile ("wfi");  
    } while (true);

    return 0; // Never executed
}

// Implement the IRQ handler
namespace irq {

    // IRQ handler constructor
    // This is defined as a template to prevent dynamic memory allocation
    // by ensuring code can be generated according to the lambda function type defined in main.
    // That ensures a std::function() does not need to be used as a generic function call interface.
    template<class T> handler::handler(T const &isr_handler) {
        // This will call the C++ function object method that represents the lamda function above.
        // This is required to provide the context of the function call that is captured by the lambda.
        // A RISC-V optimization uses the MSCRATCH register to hold the function object context pointer.
        _execute_handler = [](void)
            {
                // Read the context from the interrupt scratch register.
                uintptr_t isr_context = riscv::csrs.mscratch.read();
                // Call into the lambda function.
                return ((T *)isr_context)->operator()();
            };
        // Get a pointer to the IRQ context and save in the interrupt scratch register.
        uintptr_t isr_context = (uintptr_t)&isr_handler;
        riscv::csrs.mscratch.write( reinterpret_cast<std::uintptr_t>(isr_context) );
        // Write the entry() function to the mtvec register to install our IRQ handler.
        riscv::csrs.mtvec.write( reinterpret_cast<std::uintptr_t>(entry) );
    }      
    
#pragma GCC push_options
// Force the alignment for mtvec.BASE.
// A 'xC' extension program could be aligned to to bytes.
#pragma GCC optimize ("align-functions=4")
    static void entry(void)  {
        // Jump into the function defined within the irq::handler class.
        handler::handler_entry();
    }
#pragma GCC pop_options
}
