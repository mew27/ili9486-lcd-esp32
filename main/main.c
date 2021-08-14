/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "tft_lib.h"
#include "ili9486.h"
#include <driver/gpio.h>
#include <math.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define OFFSET_X 0
#define OFFSET_Y 0

void mylcdDrawCircle(TFT_t* dev, int x0, int y0, int r, uint16_t color) {
    float r1 = r * 0.70710678118;
    float r2 = sqrt(r*r - pow(r1, 2));

    uint16_t x0s, y0s;

    if(x0 < r2)
        x0s = 0;
    else
        x0s = x0 - r2;

    if (y0 < r1)
        y0s = 0;
    else
        y0s = y0 - r1;

    lcdDrawFillRect(dev, x0s, y0s, x0 + r2, y0 + r1, color);

    int found = false, exwhile = false;
    int startX = 0, startY = 0;


    for(int x = x0 - r; x < x0 - r2; x++) {
        startX = x;
        int y = y0 - r1;
        startY = y;
        found = false;
        exwhile = false;
        int xx = x - x0;

        while (y < y0 + r1 && exwhile == false) {
            int yy = y - y0;
            if (found == false ) {
                if (xx*xx + yy * yy <= r * r) {
                    found = true;
                    startY = y;
                }
            } else {
                if (xx*xx + yy * yy > r * r) {
                    exwhile = true;
                }
            }
            y++;
        }
        lcdDrawFillRect(dev, startX, startY, startX, y - 1, color);
    }

    for(int y = y0 - r; y < y0 - r1; y++) {
        startY = y;
        int x = x0 - r2;
        startX = x;
        found = false;
        exwhile = false;
        int yy = y - y0;

        while (x < x0 + r2 && exwhile == false) {
            int xx = x - x0;
            if (found == false ) {
                if (xx*xx + yy * yy <= r * r) {
                    found = true;
                    startX = x;
                }
            } else {
                if (xx*xx + yy * yy > r * r) {
                    exwhile = true;
                }
            }
            x++;
        }
        lcdDrawFillRect(dev, startX, startY, x - 1, startY, color);
    }

    for(int x = x0 + r2; x < x0 + r; x++) {
        startX = x;
        int y = y0 - r1;
        startY = y;
        found = false;
        exwhile = false;
        int xx = x - x0;

        while (y < y0 + r1 && exwhile == false) {
            int yy = y - y0;
            if (found == false ) {
                if (xx*xx + yy * yy <= r * r) {
                    found = true;
                    startY = y;
                }
            } else {
                if (xx*xx + yy * yy > r * r) {
                    exwhile = true;
                }
            }
            y++;
        }
        lcdDrawFillRect(dev, startX, startY, startX, y - 1, color);
    }

    for(int y = y0 + r1; y < y0 + r; y++) {
        startY = y;
        int x = x0 - r2 ;
        startX = x;
        found = false;
        exwhile = false;
        int yy = y - y0;

        while (x < x0 + r2 && exwhile == false) {
            int xx = x - x0;
            if (found == false ) {
                if (xx*xx + yy * yy <= r * r) {
                    found = true;
                    startX = x;
                }
            } else {
                if (xx*xx + yy * yy > r * r) {
                    exwhile = true;
                }
            }
            x++;
        }
        lcdDrawFillRect(dev, startX, startY, x - 1, startY, color);
    }
}

void app_main(void)
{
    TFT_t dev;
    char ppath[128];

    printf("Init TFT device!\n");

    lcdInterface(&dev, ppath);
    lcdReset(&dev);
    ili9486_lcdInit(&dev, SCREEN_WIDTH, SCREEN_HEIGHT, OFFSET_X, OFFSET_Y);

    //taskDISABLE_INTERRUPTS();
    lcdFillScreen(&dev, BLACK);
    //taskENABLE_INTERRUPTS();

    int r = 120;
    lcdDrawFillCircle(&dev, 150, 120, r, RED);
    //lcdDrawFillRect(&dev, 150 - r2, 150 - r*r1 + 1, 150 + r2, 150 + r*r1, BLUE);
    mylcdDrawCircle(&dev, 150, 340, r, BLUE);

    //lcdDrawFillCircle(&dev, 150, 350, r, RED);

    //lcdDrawFillArrow(&dev, 150, 250, 150, 350, 5, RED);

    vTaskDelay(1000);

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
            
    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

}
