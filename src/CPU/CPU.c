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

void LD_r_r1(byte r, byte r1) {
    r = r1;
}
void LD_r_HL(byte r, hex HL) {
    r = GB.memory[HL];
}
void LD_HL_r(hex HL, byte r) {
    GB.memory[HL] = r;
}
void Execute() {
    byte opcode = Fetch(GB.pc);
    hex HL = GB.H << 8 | GB.L;
    switch (opcode) {
        //0x40 onwards Load instructions
        case 0x40:
            LD_r_r1(GB.B, GB.B);
            break;
        case 0x41:
            LD_r_r1(GB.B, GB.C);
            break;
        case 0x42:
            LD_r_r1(GB.B, GB.D);
            break;
        case 0x43:
            LD_r_r1(GB.B, GB.E);
            break;
        case 0x44:
            LD_r_r1(GB.B, GB.H);
            break;
        case 0x45:
            LD_r_r1(GB.B, GB.L);
            break;
        case 0x46:
            LD_r_HL(GB.B, HL);
            break;
        case 0x47:
            LD_r_r1(GB.B, GB.A);
            break;
        case 0x48:
            LD_r_r1(GB.C, GB.B);
            break;
        case 0x49:
            LD_r_r1(GB.C, GB.C);
            break;
        case 0x4A:
            LD_r_r1(GB.C, GB.D);
            break;
        case 0x4B:
            LD_r_r1(GB.C, GB.E);
            break;
        case 0x4C:
            LD_r_r1(GB.C, GB.H);
            break;
        case 0x4D:
            LD_r_r1(GB.C, GB.L);
            break;
        case 0x4E:
            LD_r_HL(GB.C, HL);
            break;
        case 0x4F:
            LD_r_r1(GB.C, GB.A);
            break;
        case 0x50:
            LD_r_r1(GB.D, GB.B);
            break;
        case 0x51:
            LD_r_r1(GB.D, GB.C);
            break;
        case 0x52:
            LD_r_r1(GB.D, GB.D);
            break;
        case 0x53:
            LD_r_r1(GB.D, GB.E);
            break;
        case 0x54:
            LD_r_r1(GB.D, GB.H);
            break;
        case 0x55:
            LD_r_r1(GB.D, GB.L);
            break;
        case 0x56:
            LD_r_HL(GB.D, HL);
            break;
        case 0x57:
            LD_r_r1(GB.D, GB.A);
            break;
        case 0x58:
            LD_r_r1(GB.E, GB.B);
            break;
        case 0x59:
            LD_r_r1(GB.E, GB.C);
            break;
        case 0x5A:
            LD_r_r1(GB.E, GB.D);
            break;
        case 0x5B:
            LD_r_r1(GB.E, GB.E);
            break;
        case 0x5C:
            LD_r_r1(GB.E, GB.H);
            break;
        case 0x5D:
            LD_r_r1(GB.E, GB.L);
            break;
        case 0x5E:
            LD_r_HL(GB.E, HL);
            break;
        case 0x5F:
            LD_r_r1(GB.E, GB.A);
            break;
        case 0x60:
            LD_r_r1(GB.H, GB.B);
            break;
        case 0x61:
            LD_r_r1(GB.H, GB.C);
            break;
        case 0x62:
            LD_r_r1(GB.H, GB.D);
            break;
        case 0x63:
            LD_r_r1(GB.H, GB.E);
            break;
        case 0x64:
            LD_r_r1(GB.H, GB.H);
            break;
        case 0x65:
            LD_r_r1(GB.H, GB.L);
            break;
        case 0x66:
            LD_r_HL(GB.H, HL);
            break;
        case 0x67:
            LD_r_r1(GB.H, GB.A);
            break;
        case 0x68:
            LD_r_r1(GB.L, GB.B);
            break;
        case 0x69:
            LD_r_r1(GB.L, GB.C);
            break;
        case 0x6A:
            LD_r_r1(GB.L, GB.D);
            break;
        case 0x6B:
            LD_r_r1(GB.L, GB.E);
            break;
        case 0x6C:
            LD_r_r1(GB.L, GB.H);
            break;
        case 0x6D:
            LD_r_r1(GB.L, GB.L);
            break;
        case 0x6E:
            LD_r_HL(GB.L, HL);
            break;
        case 0x6F:
            LD_r_r1(GB.L, GB.A);
            break;
        case 0x70:
            LD_r_r1(HL, GB.B);
            break;
        case 0x71:
            LD_HL_r(HL, GB.C);
            break;
        case 0x72:
            LD_HL_r(HL, GB.D);
            break;
        case 0x73:
            LD_HL_r(HL, GB.E);
            break;
        case 0x74:
            LD_HL_r(HL, GB.H);
            break;
        case 0x75:
            LD_HL_r(HL, GB.L);
            break;
        case 0x76:
            //HALT
            break;
        case 0x77:
            LD_HL_r(HL, GB.A);
            break;
        case 0x78:
            LD_r_r1(GB.A, GB.B);
            break;
        case 0x79:
            LD_HL_r(GB.A, GB.C);
            break;
        case 0x7A:
            LD_HL_r(GB.A, GB.D);
            break;
        case 0x7B:
            LD_HL_r(GB.A, GB.E);
            break;
        case 0x7C:
            LD_HL_r(GB.A, GB.H);
            break;
        case 0x7D:
            LD_HL_r(GB.A, GB.L);
            break;
        case 0x7E:
            LD_HL_r(HL, GB.A);
            break;
        case 0x7F:
            LD_HL_r(GB.A, GB.A);
            break;
        default:
            return;
    }
}
