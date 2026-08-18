#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/spi.h>

#include "ili9341.h"

#define PIN_SDO 16
#define PIN_LED 21
#define PIN_SCK 14
#define PIN_SDI 15
#define PIN_DC 5
#define PIN_RESET 6
#define PIN_CS 17
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

    spi_init(spi1,10000000);
    display_config disp = {spi1,PIN_SDO,PIN_LED,PIN_SCK,PIN_SDI,PIN_DC};
    uint16_t pixels[4] =
    {
        0xF800,
        0xF800,
        0xF800,
        0xF800
    };
    Draw(&disp,50,51,50,51,pixels,4);
    while (1) {
        sleep_ms(250);
        puts("Hello World");
        sleep_ms(1000);
    }
}