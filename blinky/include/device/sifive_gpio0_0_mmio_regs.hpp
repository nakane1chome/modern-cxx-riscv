/*
   Register class and field definition for peripheral sifive_gpio0_0.
   SPDX-License-Identifier: Unlicense
*/

#ifndef SIFIVE_GPIO0_0_MMIO_REGS_HPP
#define SIFIVE_GPIO0_0_MMIO_REGS_HPP

#include <cstdint>
#include "mmio_device.hpp"
#include "sifive_gpio0_0_mmio_param.hpp"

namespace mmio_regs {
    /* From sifive,gpio0,control peripheral generator */
    namespace sifive_gpio0_0 {
        /* Pin value */
        template<const std::uintptr_t BASE_ADDR> class input_val 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::input_val_r> {
        }; /* input_val */
        /* Pin input enable */
        template<const std::uintptr_t BASE_ADDR> class input_en 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::input_en_r> {
        }; /* input_en */
        /* Pin output enable */
        template<const std::uintptr_t BASE_ADDR> class output_en 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::output_en_r> {
        }; /* output_en */
        /* Output value */
        template<const std::uintptr_t BASE_ADDR> class output_val 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::output_val_r> {
        }; /* output_val */
        /* Internal pull-up enable */
        template<const std::uintptr_t BASE_ADDR> class pue 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::pue_r> {
        }; /* pue */
        /* Pin drive strength */
        template<const std::uintptr_t BASE_ADDR> class ds 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::ds_r> {
        }; /* ds */
        /* Rise interrupt enable */
        template<const std::uintptr_t BASE_ADDR> class rise_ie 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::rise_ie_r> {
        }; /* rise_ie */
        /* Rise interrupt pending */
        template<const std::uintptr_t BASE_ADDR> class rise_ip 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::rise_ip_r> {
        }; /* rise_ip */
        /* Fall interrupt enable */
        template<const std::uintptr_t BASE_ADDR> class fall_ie 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::fall_ie_r> {
        }; /* fall_ie */
        /* Fall interrupt pending */
        template<const std::uintptr_t BASE_ADDR> class fall_ip 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::fall_ip_r> {
        }; /* fall_ip */
        /* High interrupt enable */
        template<const std::uintptr_t BASE_ADDR> class high_ie 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::high_ie_r> {
        }; /* high_ie */
        /* High interrupt pending */
        template<const std::uintptr_t BASE_ADDR> class high_ip 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::high_ip_r> {
        }; /* high_ip */
        /* Low interrupt enable */
        template<const std::uintptr_t BASE_ADDR> class low_ie 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::low_ie_r> {
        }; /* low_ie */
        /* Low interrupt pending */
        template<const std::uintptr_t BASE_ADDR> class low_ip 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::low_ip_r> {
        }; /* low_ip */
        /* I/O function enable */
        template<const std::uintptr_t BASE_ADDR> class iof_en 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::iof_en_r> {
        }; /* iof_en */
        /* I/O function select */
        template<const std::uintptr_t BASE_ADDR> class iof_sel 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::iof_sel_r> {
        }; /* iof_sel */
        /* Output XOR (invert) */
        template<const std::uintptr_t BASE_ADDR> class out_xor 
            : public mmio_device::reg<BASE_ADDR, 
                                mmio_param::sifive_gpio0_0::out_xor_r> {
        }; /* out_xor */
    } /* sifive_gpio0_0 */
} /* mmio_regs */

#endif // SIFIVE_GPIO0_0_DEV_HPP