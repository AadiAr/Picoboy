cmake_minimum_required(VERSION 3.25.2)


set(PICO_PLATFORM rp2350 CACHE STRING "Pico platform")
set(PICO_BOARD pico2 CACHE STRING "Pico board")

include("C:/Program Files/Raspberry Pi/Pico SDK v2.2.0/pico-sdk/external/pico_sdk_import.cmake")

project(Basic_Pico_Project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(Basic_Pico_Project main.c)
pico_add_extra_outputs(Basic_Pico_Project)
target_link_libraries(Basic_Pico_Project pico_stdlib)

