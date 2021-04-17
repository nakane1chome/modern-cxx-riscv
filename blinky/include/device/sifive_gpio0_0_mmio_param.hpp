/*
   Register and field offset and size definitions for peripheral sifive_gpio0_0.
   SPDX-License-Identifier: Unlicense
*/

#ifndef SIFIVE_GPIO0_0_MMIO_PARAMS_HPP
#define SIFIVE_GPIO0_0_MMIO_PARAMS_HPP

#include <cstdint>

namespace mmio_param {
    /* From sifive,gpio0,control peripheral generator */
    namespace sifive_gpio0_0 {
       /* Pin value */
       struct input_val_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x0;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* input_val_r */
       /* Pin input enable */
       struct input_en_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x4;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* input_en_r */
       /* Pin output enable */
       struct output_en_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x8;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* output_en_r */
       /* Output value */
       struct output_val_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0xc;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* output_val_r */
       /* Internal pull-up enable */
       struct pue_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x10;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* pue_r */
       /* Pin drive strength */
       struct ds_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x14;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* ds_r */
       /* Rise interrupt enable */
       struct rise_ie_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x18;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* rise_ie_r */
       /* Rise interrupt pending */
       struct rise_ip_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x1c;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* rise_ip_r */
       /* Fall interrupt enable */
       struct fall_ie_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x20;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* fall_ie_r */
       /* Fall interrupt pending */
       struct fall_ip_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x24;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* fall_ip_r */
       /* High interrupt enable */
       struct high_ie_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x28;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* high_ie_r */
       /* High interrupt pending */
       struct high_ip_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x2c;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* high_ip_r */
       /* Low interrupt enable */
       struct low_ie_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x30;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* low_ie_r */
       /* Low interrupt pending */
       struct low_ip_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x34;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* low_ip_r */
       /* I/O function enable */
       struct iof_en_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x38;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* iof_en_r */
       /* I/O function select */
       struct iof_sel_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x3c;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* iof_sel_r */
       /* Output XOR (invert) */
       struct out_xor_r {
           using datatype = std::uint32_t;
           static constexpr unsigned int offset = 0x40;
           static constexpr unsigned int bit_width = 32;
           static constexpr unsigned int field_count = 0;
       }; /* out_xor_r */
    }
}

#endif // SIFIVE_GPIO0_0_DEV_HPP
