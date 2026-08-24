//
// Created by aadia on 12/8/2026.
//
#include "ili9341.h"
#include "ili9341_hw.h"
#include <hardware/spi.h>
#include <pico/stdlib.h>
#include <stdio.h>

void Set_CS(display_config* disp, bool state) {
    gpio_put(disp->PIN_CS, state);
}

void Send_CMD(display_config* disp, uint8_t cmd) {
    gpio_put(disp->PIN_DC,0);
    spi_write_blocking(disp->spi,&cmd,1);
}

void Send_Param16(display_config* disp, uint16_t data) {
    uint8_t buffer[2] = {
        data >> 8,
        data & 0xff
    };
    gpio_put(disp->PIN_DC, 1);
    spi_write_blocking(disp->spi,buffer,2);
}
void Send_Param(display_config* disp, uint8_t param) {
    gpio_put(disp->PIN_DC, 1);
    spi_write_blocking(disp->spi,&param,1);
}

void Draw(display_config* disp,  uint16_t x1, uint16_t x2, uint16_t y1,uint16_t y2, uint16_t* pixel_dat) {
    Set_CS(disp,0);
    Send_CMD(disp,COL_ADD_SET);
    Send_Param16(disp,x1);
    Send_Param16(disp,x2);
    Set_CS(disp,1);
    Set_CS(disp,0);
    Send_CMD(disp,PA_ADD_SET);
    Send_Param16(disp,y1);
    Send_Param16(disp,y2);
    Set_CS(disp,1);
    Set_CS(disp,0);
    Send_CMD(disp,RAM_WR);
    int pix_cnt = (x2-x1 + 1) * (y2-y1 + 1);
    for (int i = 0; i < pix_cnt; i++) {
        Send_Param16(disp,pixel_dat[i]);
    }
    //Send_Param(disp,(uint8_t*)pixel_dat,pix_cnt*2);
    Set_CS(disp,1);
}
uint8_t Read_MADCTL(display_config* disp)
{
    uint8_t cmd = 0x0B;
    uint8_t dummy = 0x00;
    uint8_t response = 0x00;

    Set_CS(disp, 0);

    // Command phase
    gpio_put(disp->PIN_DC, 0);
    spi_write_blocking(disp->spi, &cmd, 1);

    // Data/read phase
    gpio_put(disp->PIN_DC, 1);
    spi_write_read_blocking(disp->spi, &dummy, &response, 1);

    Set_CS(disp, 1);

    return response;
}