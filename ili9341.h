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

static inline void Set_CS(display_config* disp, bool state);
void inline Send_CMD(display_config* disp, uint8_t cmd);
void inline Send_DATA(display_config* disp, uint8_t* data, uint8_t len);
void inline Draw(display_config* disp,  uint16_t x1, uint16_t x2, uint16_t y1,uint16_t y2, uint16_t* pixel_dat,uint8_t pix_cnt);
#endif //BASIC_PICO_PROJECT_ILI9341_H