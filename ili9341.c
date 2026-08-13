//
// Created by aadia on 12/8/2026.
//
#include "ili9341.h"
#include "ili9341_hw.h"
#include <hardware/spi.h>
#include <pico/stdlib.h>
#include <stdio.h>

static inline void Set_CS(display_config* disp, bool state) {
    gpio_put(disp->PIN_CS, state);
}

void inline Send_CMD(display_config* disp, uint8_t cmd) {
    Set_CS(disp, 0);
    gpio_put(disp->PIN_DC,0);
    spi_write_blocking(disp->spi,&cmd,1);
    Set_CS(disp,1);
}

void inline Send_DATA(display_config* disp, uint8_t* data, uint8_t len) {
    Set_CS(disp,0);
    gpio_put(disp->PIN_DC, 1);
    spi_write_blocking(disp->spi,data,len);
    Set_CS(disp,1);
}

void inline Draw(display_config* disp,  uint16_t x1, uint16_t x2, uint16_t y1,uint16_t y2, uint16_t* pixel_dat,uint8_t pix_cnt) {
    Send_CMD(disp,COL_ADD_SET);
    Send_DATA(disp,(uint8_t*)&x1,2);
    Send_DATA(disp,(uint8_t*)&x2,2);
    Send_CMD(disp,PA_ADD_SET);
    Send_DATA(disp,(uint8_t*)&y1,2);
    Send_DATA(disp,(uint8_t*)&y2,2);
    Send_CMD(disp,RAM_WR);
    Send_DATA(disp,(uint8_t*)pixel_dat,pix_cnt*2);
}