//
// Created by Aadi on 30/8/2026.
//
#include "cpu.h"
#define To_HEX(p,n) ((p) << 8 | (n))
#define Set_Bit_N(p, n, st) (((p) & ~(1 << (n))) | (((st) & 1) << (n)))
#define Get_Bit_N(p, n) (((p) >> n) & 1)

cpu GB;
void Tick(int n) {
    GB.tc += n;
}
byte Read(hex add) {
    Tick(4);
    return GB.memory[add];
}
void Write(hex add, byte data) {
    GB.memory[add] = data;
    Tick(4);
}
byte Fetch() {
    byte opCode = GB.memory[GB.pc];
    GB.pc++;
    Tick(4);
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
    *r = Read(HL);
}
void LD_HL_r(hex HL, byte r) {
    Write(HL,r);
}
void LD_HL_n(hex hl) {
    byte n = Fetch();
    Write(hl,n);
}
void LD_A_BC(hex BC) {
    GB.A = Read(BC);
}
void LD_A_DE(hex DE) {
    GB.A = Read(DE);
}
void LD_BC_A(hex BC) {
    Write(BC,GB.A);
}
void LD_DE_A(hex DE) {
    Write(DE,GB.A);
}
void LD_A_NN() {
    //n1 = lsb, n2 = msb
    byte n1 = Fetch();
    byte n2 = Fetch();
    hex nn = To_HEX(n2,n1);
    GB.A = Read(nn);
}
void LD_NN_A() {
    byte n1 = Fetch();
    byte n2 = Fetch();
    hex nn = To_HEX(n2,n1);
    Write(nn,GB.A);
}
void LDH_A_C() {
    hex addr = 0xFF00 | GB.C;
    GB.A = Read(addr);
}
void LDH_C_A() {
    hex addr = 0xFF00 | GB.C;
    Write(addr,GB.A);
}
void LDH_A_n() {
    byte n = Fetch();
    hex addr = 0xFF00 | n;
    GB.A = Read(addr);
}
void LDH_n_A() {
    byte n = Fetch();
    hex addr = 0xFF00 | n;
    Write(addr,GB.A);
}
//hl pointer commands seem to have an issue as the original parameter HL which was made to be h << 8 | L is but h and l are not being updated after
void LD_A_HL_DEC(byte* H, byte* L) {
    GB.A = Read(To_HEX(*H,*L));
    dec_rr(H,L);
}
void LD_HL_A_DEC(byte* H, byte* L) {
    Write(To_HEX(*H,*L),GB.A);
    dec_rr(H,L);
}
void LD_A_HL_INC(byte *H, byte *L) {
    GB.A = Read(To_HEX(*H,*L));
    inc_rr(H,L);
}
void LD_HL_A_INC(byte* H, byte* L) {
    Write(To_HEX(*H,*L),GB.A);
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
    Write(nn,GB.sp);
}
void LD_SP_HL(hex HL) {
    GB.sp = HL;
}
//8 Bit arithematic operations
void ADD_r(byte r) {
    byte result = GB.A + r;
    GB.A = result;
    if (result == 0) {
        GB.F = Set_Bit_N(GB.F,7,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,7,0);
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
void ADD_HL(byte *H, byte* L) {
    hex hl = *H << 8 | *L;
    byte result = GB.A + GB.memory[hl];
    GB.A += GB.memory[hl];
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,0);
    if ((GB.A & 0x0F) + (GB.memory[hl] & 0x0F) > 0x0F) {
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
void ADD_N() {
    byte n = Fetch();
    byte result = GB.A + n;
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,0);
    if ((GB.A & 0x0F) + (n & 0x0F) > 0x0F) {
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
void ADC_r(byte r) {
    byte result = GB.A + r + Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,0);
    //recheck for correctness later
    if ((GB.A & 0x0F) + (r & 0x0F) + Get_Bit_N(GB.F,4) > 0x0F) {
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
void ADC_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A + n + Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,0);
    //recheck for correctness later
    if ((GB.A & 0x0F) + (n & 0x0F) + Get_Bit_N(GB.F,4) > 0x0F) {
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
void ADC_n() {
    byte n = Fetch();
    byte result = GB.A + n + Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,0);
    //recheck for correctness later
    if ((GB.A & 0x0F) + (n & 0x0F) + Get_Bit_N(GB.F,4) > 0x0F) {
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
void SUB_r(byte r) {
    byte result = GB.A - r;
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (r & 0x0F)) {
        GB.F = Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < r) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void SUB_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A - n;
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F)) {
        GB.F = Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void SUB_n() {
    byte n = Fetch();
    byte result = GB.A - n;
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F)) {
        GB.F = Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void SBC_r(byte r) {
    byte result = GB.A - r - Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (r & 0x0F) + Get_Bit_N(GB.F,4)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < r + Get_Bit_N(GB.F,4)) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void SBC_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A - n - Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F) + Get_Bit_N(GB.F,4)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n + Get_Bit_N(GB.F,4)) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void SBC_n() {
    byte n = Fetch();
    byte result = GB.A - n - Get_Bit_N(GB.F,4);
    GB.A = result;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F) + Get_Bit_N(GB.F,4)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n + Get_Bit_N(GB.F,4)) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void Cmp_r(byte r) {
    byte result = GB.A - r;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (r & 0x0F)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < r) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void Cmp_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A - n;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void Cmp_n() {
    byte n = Fetch();
    byte result = GB.A - n;
    if (result == 0) {
        Set_Bit_N(GB.F,7,1);
    }
    else {
        Set_Bit_N(GB.F,7,0);
    }
    Set_Bit_N(GB.F,6,1);
    if ((GB.A & 0x0F) < (n & 0x0F)) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
    if (GB.A < n) {
        GB.F = Set_Bit_N(GB.F,4,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,4,0);
    }
}
void INC_r(byte *r) {
    byte result = *r + 1;
    *r = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    if ((*r & 0x0F) + 1 > 0x0F) {
        Set_Bit_N(GB.F,5,1);
    }
    else {
        GB.F = Set_Bit_N(GB.F,5,0);
    }
}
void INC_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = n + 1;
    Write(GB.H << 8 | GB.L, result);
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,1);
    if ((n & 0x0F) + 1 > 0x0F) Set_Bit_N(GB.F,5,1);
    else Set_Bit_N(GB.F,5,0);
}
void Dec_r(byte *r) {
    byte result = *r - 1;
    *r = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,1);
    if((*r & 0x0F) == 0) Set_Bit_N(GB.F,5,1);
    else Set_Bit_N(GB.F,5,0);
}
void Dec_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = n - 1;
    Write(GB.H << 8 | GB.L, result);
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,1);
    if ((n & 0x0F) == 0) Set_Bit_N(GB.F,5,1);
    else Set_Bit_N(GB.F,5,0);
}
void AND_r(byte r) {
    byte result = GB.A & r;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,1);
    Set_Bit_N(GB.F,4,0);
}
void AND_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A & n;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,1);
    Set_Bit_N(GB.F,4,0);
}
void AND_n() {
    byte n = Fetch();
    byte result = GB.A & n;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,1);
    Set_Bit_N(GB.F,4,0);
}
void OR_r(byte r) {
    byte result = GB.A | r;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void OR_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte result = GB.A | n;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void OR_n() {
    byte n = Fetch();
    byte result = GB.A | n;
    GB.A = result;
    if (result == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void XOR_r(byte r) {
    GB.A ^= r;
    if ((GB.A ^ r)== 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void XOR_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    GB.A ^= n;
    if ((GB.A ^ n)== 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void XOR_n() {
    byte n = Fetch();
    GB.A ^= n;
    if ((GB.A ^ n)== 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void CCF() {
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,~Get_Bit_N(GB.F,4));
}
void SCF() {
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,1);
}
void DAA() {
    //TO-DO
}
void CPL() {
    GB.A = ~GB.A;
    Set_Bit_N(GB.F,6,1);
    Set_Bit_N(GB.F,5,1);
}
//16 Bit arithmatic instructions
void INC_rr(byte *r1, byte *r2) {
    if (*r2 < 0xFF) {
        (*r2)++;
    }
    else {
        *r2 = 0;
        (*r1)++;
    }
    Tick(4);
}
void DEC_rr(byte *r1, byte *r2) {
    hex rr = *r1 << 8 | *r2;
    rr--;
    *r1 = rr >> 8;
    *r2 = rr & 0x0F;
    Tick(4);
}
void ADD_HL_rr(byte r1, byte r2) {
    hex HL = GB.H << 8 | GB.L;
    hex rr = r1 << 8 | r2;
    HL += rr;
    if ((GB.H & 0x0FFF) + (GB.L & 0x0FFF) > 0x0FFF) Set_Bit_N(GB.F,6,1);
    else Set_Bit_N(GB.F,6,0);
    if ((uint32_t)GB.H + (uint32_t)GB.L > 0xFFFF) Set_Bit_N(GB.F,5,1);
    else Set_Bit_N(GB.F,5,0);
    GB.H = HL >> 8;
    GB.L = HL & 0x0F;
    Set_Bit_N(GB.F,6,0);
    Tick(4);
}
void ADD_SP_e() {
    //TO-DO
}
//Rotate, shift and bit operation instructions
void RLCA() {
    byte b7 = Get_Bit_N(GB.A,7);
    GB.A = GB.A << 1;
    Set_Bit_N(GB.A,0,b7);
    Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RRCA() {
    byte b0 = Get_Bit_N(GB.A,0);
    GB.A = GB.A >> 1;
    Set_Bit_N(GB.A,7,b0);
    Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RLA() {
    byte b7 = Get_Bit_N(GB.A,7);
    GB.A = GB.A << 1;
    Set_Bit_N(GB.A,0,Get_Bit_N(GB.F,4));
    Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RRA() {
    byte b0 = Get_Bit_N(GB.A,0);
    GB.A = GB.A >> 1;
    Set_Bit_N(GB.A,7,Get_Bit_N(GB.F,4));
    Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RLC(byte *r) {
    byte b7 = Get_Bit_N(*r,7);
    *r = *r << 1;
    Set_Bit_N(*r,0,b7);
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RLC_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b7 = Get_Bit_N(n,7);
    n = n << 1;
    Set_Bit_N(n,0,b7);
    Write(GB.H << 8 | GB.L,n);
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RRC(byte *r) {
    byte b0 = Get_Bit_N(*r,0);
    *r = *r >> 1;
    Set_Bit_N(*r,7,b0);
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RRC_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b0 = Get_Bit_N(n,0);
    n = n >> 1;
    Set_Bit_N(n,7,b0);
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
    Write(GB.H << 8 | GB.L,n);
}
void RL_r(byte *r) {
    byte b7 = Get_Bit_N(*r,7);
    *r = *r << 1;
    Set_Bit_N(*r,0,Get_Bit_N(GB.F,4));
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RL_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b0 = Get_Bit_N(n,0);
    n = n << 1;
    Set_Bit_N(n,0,Get_Bit_N(GB.F,4));
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
    Write(GB.H << 8 | GB.L,n);
}
void RR_r(byte *r) {
    byte b0 = Get_Bit_N(*r,0);
    *r = *r >> 1;
    Set_Bit_N(*r,7,Get_Bit_N(GB.F,4));
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void RR_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b0 = Get_Bit_N(n,0);
    n = n >> 1;
    Set_Bit_N(n,7,Get_Bit_N(GB.F,4));
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
    Write(GB.H << 8 | GB.L,n);
}
void SLA_r(byte *r) {
    byte b7 = Get_Bit_N(*r,7);
    *r = *r << 1;
    Set_Bit_N(*r,0,0);
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,b7);
}
void SLA_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b7 = Get_Bit_N(n,7);
    Set_Bit_N(n,0,0);
    if (n) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b7) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void SRA_r(byte *r) {
    byte b0 = Get_Bit_N(*r,0);
    byte b7 = Get_Bit_N(*r,7);
    *r = *r >> 1;
    Set_Bit_N(*r,7,b7);
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void SRA_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b7 = Get_Bit_N(n,7);
    byte b0 = Get_Bit_N(n,0);
    Set_Bit_N(n,0,0);
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
    Write(GB.H << 8 | GB.L,n);
}
void SWAP_r(byte *r) {
    byte L = *r & 0x0F;
    byte H = *r & 0xF0;
    hex LH = L << 8 | H;
    *r = LH;
    if (LH == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
}
void SWAP_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte L = n & 0x0F;
    byte H = n & 0xF0;
    hex LH = L << 8 | H;
    n = LH;
    if (LH == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    Set_Bit_N(GB.F,4,0);
    Write(GB.H << 8 | GB.L,n);
}
void SRL_r(byte *r) {
    byte b0 = Get_Bit_N(*r,0);
    *r = *r >> 1;
    Set_Bit_N(*r,7,0);
    if (*r == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void SRL_HL() {
    byte n = Read(GB.H << 8 | GB.L);
    byte b0 = Get_Bit_N(n,0);
    n = n >> 1;
    Set_Bit_N(n,7,0);
    if (n == 0) Set_Bit_N(GB.F,7,1);
    else Set_Bit_N(GB.F,7,0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,0);
    if (b0) Set_Bit_N(GB.F,4,1);
    else Set_Bit_N(GB.F,4,0);
}
void BIT_b_r(byte b,byte r) {
    byte bit = Get_Bit_N(r,b);
    Set_Bit_N(GB.F,7,bit == 0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,1);
}
void BIT_b_HL(byte b) {
    byte n = Read(GB.H << 8 | GB.L);
    byte bit = Get_Bit_N(n,b);
    Set_Bit_N(GB.F,7,bit == 0);
    Set_Bit_N(GB.F,6,0);
    Set_Bit_N(GB.F,5,1);
}
void RES_b_r(byte b, byte *r) {
    Set_Bit_N(*r,b,0);
}
void RES_b_HL(byte b) {
    byte n = Read(GB.H << 8 | GB.L);
    Set_Bit_N(n,b,0);
    Write(GB.H << 8 | GB.L,n);
}
void Set_b_r(byte b, byte *r) {
    Set_Bit_N(*r,b,1);
}
void Set_b_HL(byte b) {
    byte n = Read(GB.H << 8 | GB.L);
    Set_Bit_N(n,b,1);
    Write(GB.H << 8 | GB.L,n);
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
