/* Base classes for MMIO registers and fields.
   SPDX-License-Identifier: Unlicense
*/

#ifndef MMIO_DEVICE_HPP
#define MMIO_DEVICE_HPP

#include <cstdint>

namespace mmio_device {

    /** Generic definintion of a 32 bit register mapped to 32 bit address space.
    */
    struct generic_32bit_register_spec {
        struct reg {
            using datatype = std::uint32_t;
            static constexpr unsigned int offset = 0x0;
            static constexpr unsigned int bit_width = 32;
            static constexpr unsigned int field_count = 0;
        };
    };
    /** Generic definintion of a 64 bit register mapped to 32 bit address space.
    */
    struct generic_64bit_register_spec {
        struct reg {
            using datatype = std::uint64_t;
            static constexpr unsigned int offset = 0x0;
            static constexpr unsigned int bit_width = 64;
            static constexpr unsigned int field_count = 0;
        }; 
        struct high_reg {
            using datatype = std::uint32_t;
            static constexpr unsigned int offset = __ORDER_LITTLE_ENDIAN__ ? 0x4 : 0x0;
            static constexpr unsigned int bit_width = 32;
            static constexpr unsigned int field_count = 0;
        }; 
        struct low_reg {
            using datatype = std::uint32_t;
            static constexpr unsigned int offset = __ORDER_LITTLE_ENDIAN__ ? 0x0 : 0x4;
            static constexpr unsigned int bit_width = 32;
            static constexpr unsigned int field_count = 0;
        }; 
    };

/** Base class for all MMIO registers.

    Class R should define the following type:

    datatype - common data type for all registers. e.g uint32_t

    Class R should define the following static constexpr member:
    
    offset   - Byte offset from BASE_ADDR for register

 */
template<uintptr_t BASE_ADDR, class R> class reg {
    public :

    using datatype_t = typename R::datatype;
    
    void write(datatype_t value) {
        *reinterpret_cast<volatile datatype_t*>(BASE_ADDR + R::offset) = value;
    }
    void set(datatype_t value) { 
        *reinterpret_cast<volatile datatype_t*>(BASE_ADDR + R::offset) |= value;
    }
    void clr(datatype_t value) { 
        *reinterpret_cast<volatile datatype_t*>(BASE_ADDR + R::offset) &= ~value;
    }
    datatype_t read(void) {
        return *reinterpret_cast<volatile datatype_t*>(BASE_ADDR + R::offset);
    }
    datatype_t operator=(datatype_t value) {
        write(value);
        return read();
    }
    void operator&=(datatype_t value) {
        write(read()&value);
    }
    void operator|=(datatype_t value) {
        write(read()|value);
    }
    void operator^=(datatype_t value) {
        write(read()^value);
    }
};

/** Base class for all register fields 

    Class R is the same class passed to mmio_device::reg<>

    Class F should define the following type:

    datatype - A datatype large enough to hold the field. e.g bool for single bits, uint8 for a 3 bit field. 

    Class F should define the following static constexpr member:
    
    bit_mask   - A mask for the location of the field within the parent register.
    bit_offset - The LSB of the field.


 */
template<uintptr_t BASE_ADDR, class R, class F> class reg_field {
    public :

    using r_datatype_t = typename R::datatype;
    using f_datatype_t = typename F::datatype;

    /** Return the mask for this field. */
    constexpr r_datatype_t mask(void) const {
        return F::bit_mask;
    }

    /** Mask and locate the field at the bit offset for the given field.
        Does not write to hardware.
     */
    r_datatype_t format(f_datatype_t value) {
        return ((r_datatype_t)value << F::bit_offset) & F::bit_mask;
    }
    /** Mask and extract the field at the bit offset for the given register value.
        Does not read from to hardware.
     */
    f_datatype_t extract(r_datatype_t value) {
        return (value & F::bit_mask) >> F::bit_offset ;
    }

    /** Write to a field.
        Will use a read-modify-write unless these conditions are met:
        - The field is at offset 0 and occupies the whole register.
        - The register has just one field.
     */
    void write(f_datatype_t value) {
        if constexpr ((R::bit_width == F::bit_width) && (F::bit_offset == 0)) {
           // Write to single bit.
           *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) = (r_datatype_t) value ;
        } else if constexpr (R::field_count == 1) {
           // Write to single field.
           *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) = 
               ((r_datatype_t)value << F::bit_offset) & F::bit_mask;
        } else {
            // Read write modify
            r_datatype_t reg_value = *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset);
            reg_value = (((r_datatype_t)value << F::bit_offset) & F::bit_mask) | (reg_value & ~F::bit_mask);
            *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) = reg_value;
        }
    }
    /** Set all the bits in this field. */
    void set(void) {
        if constexpr (R::field_count == 1) {
                *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) = F::bit_mask;
        } else {
                *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) |= F::bit_mask;
        }
    }
    /** Clear all the bits in this field. */
    void clear(void) {
        if constexpr (R::field_count == 1) {
                *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) = 0;
        } else {
                *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset) &= ~F::bit_mask;
        }
    }
    /** Read the field.
     * @retval The register will be read, masked and shifted such that the field is aligned at bit 0.
     */
    f_datatype_t read(void) {
        if constexpr ((R::bit_width == F::bit_width) && (F::bit_offset == 0)) {
            return (f_datatype_t) *reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset);
        } else {
            return (f_datatype_t) ((*reinterpret_cast<volatile r_datatype_t*>(BASE_ADDR + R::offset)) & F::bit_mask)  >> F::bit_offset;
        }
    }
    /** Read the field after writing the register using an 'OR' atomic operation.
     * @retval The register will be read, masked and shifted such that the field is aligned at bit 0.
     */
    f_datatype_t read_after_or(r_datatype_t value) {
#ifdef __riscv_atomic
        uint32_t dest;
        uintptr_t addr = BASE_ADDR + R::offset;
        __asm__ volatile ("amoor.w    %0, %1, (%2)"  /* read and write atomically */
                          : "=r" (dest) /* output: register %0 */
                          : "r" (value), "r" (addr)  /* input: register %1 */
                          : /* clobbers: none */);       
        return (dest & F::bit_mask) >> F::bit_offset;
#else
        write(value|read());
        return read();
#endif
    }
};

} // namespace

#endif // #ifndef MMIO_DEVICE_HPP
