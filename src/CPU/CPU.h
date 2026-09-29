//
// Created by Aadi on 30/8/2026.
//

#ifndef GB_PICO_CPU_H
#define GB_PICO_CPU_H
#include <stdio.h>
#include <inttypes.h>

typedef uint16_t hex;
typedef uint8_t byte;

typedef struct {
    byte A;
    byte B;
    byte C;
    byte D;
    byte E;
    byte H;
    byte L;
    //bit 7 = z, 6 = n, 5 = h, 4 = c
    byte F;
    hex sp;
    hex pc;
    byte ir;
    byte ie;
    byte memory[0xFFFF];
    //T-Cycles and M cycles
    int tc;
    int mc;
}cpu;

#endif //GB_PICO_CPU_H
