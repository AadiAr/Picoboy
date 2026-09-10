//
// Created by Aadi on 30/8/2026.
//
#include "cpu.h"
#define To_HEX(p,n) (p << 8 | n)
#define Set_Bit_N(p, n, st) ((p & ~(1 << n)) | ((st & 1) << n))
cpu GB;

byte Fetch() {
    byte opCode = GB.memory[GB.pc];
    GB.pc++;
    return opCode;
}
void inc_rr(byte* r1, byte* r2) {
    //r1 msb r2 lsb
    if (*r2 == 0xFF) {
        (*r1)++;
        *r2 = 0x00;
    }
    else{(*r2)++;}
}
void dec_rr(byte* r1, byte* r2) {
    if (*r2 == 0x00) {
        (*r1)--;
        *r2 = 0xFF;
    }
    else{(*r2)--;}
}
hex get_rr(byte r1, byte r2) {
    return r1 << 8 | r2;
}
//8 bit load instr.
void LD_r_r1(byte *r, byte r1) {
    *r = r1;
}
void LD_r_HL(byte *r, hex HL) {
    *r = GB.memory[HL];
}
void LD_HL_r(hex HL, byte r) {
    GB.memory[HL] = r;
}
void LD_HL_n(hex hl) {
    byte n = Fetch();
    GB.memory[hl] = n;
}
void LD_A_BC(hex BC) {
    GB.A = GB.memory[BC];
}
void LD_A_DE(hex DE) {
    GB.A = GB.memory[DE];
}
void LD_BC_A(hex BC) {
    GB.memory[BC] = GB.A;
}
void LD_DE_A(hex DE) {
    GB.memory[DE] = GB.A;
}
void LD_A_NN() {
    //n1 = lsb, n2 = msb
    byte n1 = Fetch();
    byte n2 = Fetch();
    hex nn = To_HEX(n2,n1);
    GB.A = GB.memory[nn];
}
void LD_NN_A() {
    byte n1 = Fetch();
    byte n2 = Fetch();
    hex nn = To_HEX(n2,n1);
    GB.memory[nn] = GB.A;
}
void LDH_A_C() {
    hex addr = 0xFF00 | GB.C;
    GB.A = GB.memory[addr];
}
void LDH_C_A() {
    hex addr = 0xFF00 | GB.C;
    GB.memory[addr] = GB.A;
}
void LDH_A_n() {
    byte n = Fetch();
    hex addr = 0xFF00 | n;
    GB.A = GB.memory[addr];
}
void LDH_n_A() {
    byte n = Fetch();
    hex addr = 0xFF00 | n;
    GB.memory[addr] = GB.A;
}
//hl pointer commands seem to have an issue as the original parameter HL which was made to be h << 8 | L is but h and l are not being updated after
void LD_A_HL_DEC(byte* H, byte* L) {
    GB.A = GB.memory[To_HEX(*H,*L)];
    dec_rr(H,L);
}
void LD_HL_A_DEC(byte* H, byte* L) {
    GB.memory[To_HEX(*H,*L)] = GB.A;
    dec_rr(H,L);
}
void LD_A_HL_INC(byte *H, byte *L) {
    GB.A = GB.memory[To_HEX(*H,*L)];
    inc_rr(H,L);
}
void LD_HL_A_INC(byte* H, byte* L) {
    GB.memory[To_HEX(*H,*L)] = GB.A;
    inc_rr(H,L);
}
//16 bit load instr.
void LD_rr_nn(byte *r1, byte *r2) {
    byte n1 = Fetch();
    byte n2 = Fetch();
    *r1 = n2;
    *r2 = n1;
}
//check stack functioning for the following
void LD_nn_SP() {
    byte n1 = Fetch();
    byte n2 = Fetch();
    hex nn = n2 << 8 | n1;
    GB.memory[nn] = GB.sp;
}
void LD_SP_HL(hex HL) {
    GB.sp = HL;
}
//8 Bit arithematic operations
void ADD_r(byte r) {
    byte result = GB.A + r;
    if (result == 0) {
        GB.F = Set_Bit_N(GB.F,7,1);
    }
    GB.F = Set_Bit_N(GB.F,6,0);
    if ((GB.A & 0x0F) + (r & 0x0F) > 0x0F) {
        GB.F = Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (result > 0xFF) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void Execute() {
    byte opcode = Fetch();
    hex HL = GB.H << 8 | GB.L;
    switch (opcode) {
        //0x40 onwards Load instructions
        case 0x40:
            LD_r_r1(&GB.B, GB.B);
            break;
        case 0x41:
            LD_r_r1(&GB.B, GB.C);
            break;
        case 0x42:
            LD_r_r1(&GB.B, GB.D);
            break;
        case 0x43:
            LD_r_r1(&GB.B, GB.E);
            break;
        case 0x44:
            LD_r_r1(&GB.B, GB.H);
            break;
        case 0x45:
            LD_r_r1(&GB.B, GB.L);
            break;
        case 0x46:
            LD_r_HL(&GB.B, HL);
            break;
        case 0x47:
            LD_r_r1(&GB.B, GB.A);
            break;
        case 0x48:
            LD_r_r1(&GB.C, GB.B);
            break;
        case 0x49:
            LD_r_r1(&GB.C, GB.C);
            break;
        case 0x4A:
            LD_r_r1(&GB.C, GB.D);
            break;
        case 0x4B:
            LD_r_r1(&GB.C, GB.E);
            break;
        case 0x4C:
            LD_r_r1(&GB.C, GB.H);
            break;
        case 0x4D:
            LD_r_r1(&GB.C, GB.L);
            break;
        case 0x4E:
            LD_r_HL(&GB.C, HL);
            break;
        case 0x4F:
            LD_r_r1(&GB.C, GB.A);
            break;
        case 0x50:
            LD_r_r1(&GB.D, GB.B);
            break;
        case 0x51:
            LD_r_r1(&GB.D, GB.C);
            break;
        case 0x52:
            LD_r_r1(&GB.D, GB.D);
            break;
        case 0x53:
            LD_r_r1(&GB.D, GB.E);
            break;
        case 0x54:
            LD_r_r1(&GB.D, GB.H);
            break;
        case 0x55:
            LD_r_r1(&GB.D, GB.L);
            break;
        case 0x56:
            LD_r_HL(&GB.D, HL);
            break;
        case 0x57:
            LD_r_r1(&GB.D, GB.A);
            break;
        case 0x58:
            LD_r_r1(&GB.E, GB.B);
            break;
        case 0x59:
            LD_r_r1(&GB.E, GB.C);
            break;
        case 0x5A:
            LD_r_r1(&GB.E, GB.D);
            break;
        case 0x5B:
            LD_r_r1(&GB.E, GB.E);
            break;
        case 0x5C:
            LD_r_r1(&GB.E, GB.H);
            break;
        case 0x5D:
            LD_r_r1(&GB.E, GB.L);
            break;
        case 0x5E:
            LD_r_HL(&GB.E, HL);
            break;
        case 0x5F:
            LD_r_r1(&GB.E, GB.A);
            break;
        case 0x60:
            LD_r_r1(&GB.H, GB.B);
            break;
        case 0x61:
            LD_r_r1(&GB.H, GB.C);
            break;
        case 0x62:
            LD_r_r1(&GB.H, GB.D);
            break;
        case 0x63:
            LD_r_r1(&GB.H, GB.E);
            break;
        case 0x64:
            LD_r_r1(&GB.H, GB.H);
            break;
        case 0x65:
            LD_r_r1(&GB.H, GB.L);
            break;
        case 0x66:
            LD_r_HL(&GB.H, HL);
            break;
        case 0x67:
            LD_r_r1(&GB.H, GB.A);
            break;
        case 0x68:
            LD_r_r1(&GB.L, GB.B);
            break;
        case 0x69:
            LD_r_r1(&GB.L, GB.C);
            break;
        case 0x6A:
            LD_r_r1(&GB.L, GB.D);
            break;
        case 0x6B:
            LD_r_r1(&GB.L, GB.E);
            break;
        case 0x6C:
            LD_r_r1(&GB.L, GB.H);
            break;
        case 0x6D:
            LD_r_r1(&GB.L, GB.L);
            break;
        case 0x6E:
            LD_r_HL(&GB.L, HL);
            break;
        case 0x6F:
            LD_r_r1(&GB.L, GB.A);
            break;
        case 0x70:
            LD_HL_r(HL, GB.B);
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
            LD_r_r1(&GB.A, GB.B);
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
