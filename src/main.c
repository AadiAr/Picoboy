#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

#include "ili9341.h"

#define PIN_SDO 12
#define PIN_LED 16
#define PIN_SCK 10
#define PIN_SDI 11
#define PIN_DC 3
#define PIN_RESET 4
#define PIN_CS 13
//#define PIN_GND
//#define PIN_VCC

int main(void) {
    stdio_init_all();
    display_config disp = {spi1,PIN_SDO,PIN_LED,PIN_SCK,PIN_SDI,PIN_DC,PIN_RESET,PIN_CS};
    Init_DISP(&disp);
    sleep_ms(1000);

    //MADCTL
    printf("Reading default MADCTL...\n");
    uint8_t madctl = Read_MADCTL(&disp);
    printf("MADCTL = 0x%02X\n", madctl);

    uint16_t pixels[240 * 320];
    uint16_t buffer[240 * 320];

    for (int i = 0; i < 240 * 320; i++) {
        pixels[i] = 0x001F;
    }
    Draw(&disp, 0, 239, 0, 319, pixels);
}