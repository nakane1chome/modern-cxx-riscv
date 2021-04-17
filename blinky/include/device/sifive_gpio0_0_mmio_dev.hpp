/*
   Register structure definition of peripheral sifive_gpio0_0.
   SPDX-License-Identifier: Unlicense
*/

#ifndef SIFIVE_GPIO0_0_MMIO_DEV_HPP
#define SIFIVE_GPIO0_0_MMIO_DEV_HPP

#include <cstdint>
#include "mmio_device.hpp"
#include "sifive_gpio0_0_mmio_regs.hpp"

namespace driver {

/*   From sifive,gpio0,control peripheral generator */
template<std::uintptr_t BASE_ADDR> class sifive_gpio0_0_dev  {
public:
    /* Pin value */
   mmio_regs::sifive_gpio0_0::input_val<BASE_ADDR> input_val;
   
    /* Pin input enable */
   mmio_regs::sifive_gpio0_0::input_en<BASE_ADDR> input_en;
   
    /* Pin output enable */
   mmio_regs::sifive_gpio0_0::output_en<BASE_ADDR> output_en;
   
    /* Output value */
   mmio_regs::sifive_gpio0_0::output_val<BASE_ADDR> output_val;
   
    /* Internal pull-up enable */
   mmio_regs::sifive_gpio0_0::pue<BASE_ADDR> pue;
   
    /* Pin drive strength */
   mmio_regs::sifive_gpio0_0::ds<BASE_ADDR> ds;
   
    /* Rise interrupt enable */
   mmio_regs::sifive_gpio0_0::rise_ie<BASE_ADDR> rise_ie;
   
    /* Rise interrupt pending */
   mmio_regs::sifive_gpio0_0::rise_ip<BASE_ADDR> rise_ip;
   
    /* Fall interrupt enable */
   mmio_regs::sifive_gpio0_0::fall_ie<BASE_ADDR> fall_ie;
   
    /* Fall interrupt pending */
   mmio_regs::sifive_gpio0_0::fall_ip<BASE_ADDR> fall_ip;
   
    /* High interrupt enable */
   mmio_regs::sifive_gpio0_0::high_ie<BASE_ADDR> high_ie;
   
    /* High interrupt pending */
   mmio_regs::sifive_gpio0_0::high_ip<BASE_ADDR> high_ip;
   
    /* Low interrupt enable */
   mmio_regs::sifive_gpio0_0::low_ie<BASE_ADDR> low_ie;
   
    /* Low interrupt pending */
   mmio_regs::sifive_gpio0_0::low_ip<BASE_ADDR> low_ip;
   
    /* I/O function enable */
   mmio_regs::sifive_gpio0_0::iof_en<BASE_ADDR> iof_en;
   
    /* I/O function select */
   mmio_regs::sifive_gpio0_0::iof_sel<BASE_ADDR> iof_sel;
   
    /* Output XOR (invert) */
   mmio_regs::sifive_gpio0_0::out_xor<BASE_ADDR> out_xor;
   
}; /* sifive_gpio0_0_dev  */

}

#endif // SIFIVE_GPIO0_0_DEV_HPP
