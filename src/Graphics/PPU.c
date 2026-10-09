//
// Created by aadia on 30/9/2026.
//

#include "PPU.h"
#include <ili9341.h>
#include "CPU.h"
cpu GB;
//VRAM 0x8000-0x9FFF
//Tile data blocks 0x8000 - 0x97FF
//Tile map 0 0x9800 - 0x9BFF
//Tile map 1 0x9C00 - 0x9FFF

//Registers
//LCDC -> FF40
//LY FF44
//LYC FF45
//STAT (Lcd status) FF41
void Update(int ticks) {

}
void OAM_SCAN() {
    int objcnt;
    do {
    //if LY == byte 0 -> objcnt ++
    //sel obj

    }
    while (objcnt < 10);
}
hex GetPixel(byte n1,byte n2) {
    hex pixel = 0x0000;
    for (int i = 7; i > 0; i--) {
        Set_Bit_N(pixel,i*2 + 1,Get_Bit_N(n2,i));
        Set_Bit_N(pixel,i*2,Get_Bit_N(n1,i));
    }
    return pixel;
}