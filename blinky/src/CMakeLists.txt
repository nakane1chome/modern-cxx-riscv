
cmake_minimum_required(VERSION 3.10)

# set the project name
project(modern_cxx_blinky CXX)

# specify the C++ standard
set(CMAKE_CXX_FLAGS "\
  -std=c++17 \
  -Os \
  -g \
  -Wall \
  -ffunction-sections \
  -fno-rtti \
  -fno-use-cxa-atexit \
  -fno-exceptions \
  -fno-nonansi-builtins \
  -fno-threadsafe-statics \
  -fno-enforce-eh-specs \
  -ftemplate-depth=32 \
  -Wzero-as-null-pointer-constant \
")
set ( STACK_SIZE 0xf00 )
set ( TARGET modern_cxx_blinky)

# add the executable

add_executable(${TARGET}.elf main.cpp startup.cpp ) 
SET(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker.lds")

set_target_properties(${TARGET}.elf PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")
target_include_directories(${TARGET}.elf PRIVATE ../include/ )

# Linker control
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -fno-exceptions  -Xlinker --defsym=__stack_size=${STACK_SIZE} -T ${LINKER_SCRIPT} -Wl,-Map=${TARGET}.map")

# Post processing command to create a disassembly file 
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S  ${TARGET}.elf > ${TARGET}.disasm
        COMMENT "Invoking: Disassemble")

# Post processing command to create a hex file 
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex  ${TARGET}.elf  ${TARGET}.hex
        COMMENT "Invoking: Hexdump")

# Pre-processing command to create disassembly for each source file
foreach (SRC_MODULE main startup)
  add_custom_command(TARGET ${TARGET}.elf 
                     PRE_LINK
                     COMMAND ${CMAKE_OBJDUMP} -S CMakeFiles/${TARGET}.elf.dir/${SRC_MODULE}.cpp.obj > ${SRC_MODULE}.s
                     COMMENT "Invoking: Disassemble ( CMakeFiles/${TARGET}.elf.dir/${SRC_MODULE}.cpp.obj)")
endforeach()

SET(DCMAKE_EXPORT_COMPILE_COMMANDS ON)
