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
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SDI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SDO, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);
    gpio_put(PIN_LED, 1);

    gpio_init(PIN_RESET);
    gpio_set_dir(PIN_RESET, GPIO_OUT);

    gpio_put(PIN_RESET, 0);
    sleep_ms(10);
    gpio_put(PIN_RESET, 1);
    sleep_ms(120);

    spi_init(spi1,10000000);
    display_config disp = {spi1,PIN_SDO,PIN_LED,PIN_SCK,PIN_SDI,PIN_DC,PIN_RESET,PIN_CS};
    Send_CMD(&disp,SLP_OUT);
    sleep_ms(120);
    Set_CS(&disp, 0);
    Send_CMD(&disp,PIX_FMT);
    Send_Param(&disp,0x55);
    Send_CMD(&disp,MADCTL);
    Send_Param(&disp,0x48);
    Send_CMD(&disp,DISP_ON);
    Set_CS(&disp, 1);
    sleep_ms(2000);

    Send_CMD(&disp, MADCTL);
    Send_Param(&disp, 0x48);
    sleep_ms(1000);

    printf("Reading default MADCTL...\n");

    uint8_t madctl = Read_MADCTL(&disp);

    printf("MADCTL = 0x%02X\n", madctl);
    while (1) {
        sleep_ms(1000);
        printf("MADCTL = 0x%02X\n", madctl);
    }
    // uint16_t pixels[240 * 320];
    //
    // for (int i = 0; i < 240 * 320; i++) {
    //     pixels[i] = 0xF800;
    // }
    //
    // Draw(&disp, 0, 239, 0, 319, pixels);
}