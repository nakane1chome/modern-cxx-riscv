/*
   Constexpr utility functions.
   SPDX-License-Identifier: Unlicense
*/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>

namespace util {

    /** Compile time bit mask calculation  */
    static constexpr std::uint32_t bitmask(unsigned int bit) {
        return 1UL << (std::uint32_t) bit;
    }

    /** Compile time check for a power of two number */
    static constexpr bool is_power_of_two(size_t SIZE) {
        return SIZE && ((SIZE & (SIZE-1)) == 0);
    }
}

#endif // UTIL_HPP
