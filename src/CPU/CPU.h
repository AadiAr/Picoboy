//
// Created by Aadi on 30/8/2026.
//

#ifndef GB_PICO_CPU_H
#define GB_PICO_CPU_H
#include <stdio.h>
#include <inttypes.h>
#define To_HEX(p,n) ((p) << 8 | (n))
#define Set_Bit_N(p, n, st) (((p) & ~(1 << (n))) | (((st) & 1) << (n)))
#define Get_Bit_N(p, n) (((p) >> n) & 1)

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
