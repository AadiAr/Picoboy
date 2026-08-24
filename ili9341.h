//
// Created by aadia on 12/8/2026.
//

#ifndef BASIC_PICO_PROJECT_ILI9341_H
#define BASIC_PICO_PROJECT_ILI9341_H

#include <pico/stdlib.h>
#include <hardware/spi.h>

#include "ili9341_hw.h"

#define GET_DATA_BIT(p, n)  ((*((uint32_t *)(p) + ((n) >> 5)) \
>> (31 - ((n) & 31))) & 1)
#define SET_DATA_BIT(p, n)  (*((uint32_t *)(p) + ((n) >> 5)) \
|= (0x80000000 >> ((n) & 31)))
#define CLR_DATA_BIT(p, n)  (*((uint32_t *)(p) + ((n) >> 5)) \
&=~(0x80000000 >> ((n) & 31)))

typedef struct {
    spi_inst_t *spi;

    int PIN_SDO;
    int PIN_LED;
    int PIN_SCK;
    int PIN_SDI;
    int PIN_DC;
    int PIN_RESET;
    int PIN_CS;
}   display_config;
uint8_t Read_MADCTL(display_config* disp);
void Set_CS(display_config* disp, bool state);
void Send_CMD(display_config* disp, uint8_t cmd);
void Send_Param16(display_config* disp, uint16_t data);
void Draw(display_config* disp,  uint16_t x1, uint16_t x2, uint16_t y1,uint16_t y2, uint16_t* pixel_dat);
void Send_Param(display_config* disp, uint8_t param);
#endif //BASIC_PICO_PROJECT_ILI9341_H