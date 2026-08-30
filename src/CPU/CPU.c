//
// Created by Aadi on 30/8/2026.
//
#include "cpu.h"

cpu GB;

int Fetch(hex PC) {
    int opCode = GB.memory[PC];
    PC++;
    return opCode;
}

void Execute() {
    byte opcode = Fetch(GB.pc);

    switch (opcode) {
        case 0x40:


        default:
            return;
    }
}

void LD_r_r1(hex r, hex r1) {
    r = r1;
}