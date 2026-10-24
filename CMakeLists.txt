cmake_minimum_required(VERSION 3.25.2)


set(PICO_PLATFORM rp2350 CACHE STRING "Pico platform")
set(PICO_BOARD pico2 CACHE STRING "Pico board")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)
project(GB_PICO C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(GB_PICO
        "src/main.c"
        "src/Display Driver/ili9341.c"
        src/CPU/CPU.h
        src/CPU/CPU.c
        src/Graphics/PPU.c
        src/Graphics/PPU.h
        src/APU/APU.c
)

target_include_directories(GB_PICO PRIVATE "src/Display Driver")
target_include_directories(GB_PICO PRIVATE "src/CPU")
target_link_libraries(GB_PICO
        pico_stdlib
        pico_audio_i2s
        hardware_pwm
        hardware_spi
)

pico_enable_stdio_usb(GB_PICO 1)
pico_enable_stdio_uart(GB_PICO 0)

pico_add_extra_outputs(GB_PICO)
