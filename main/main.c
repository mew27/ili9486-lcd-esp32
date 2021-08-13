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

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define OFFSET_X 0
#define OFFSET_Y 0

void app_main(void)
{
    TFT_t dev;
    char ppath[128];

    printf("Init TFT device!\n");

    lcdInterface(&dev, ppath);
    lcdReset(&dev);
    ili9486_lcdInit(&dev, SCREEN_WIDTH, SCREEN_HEIGHT, OFFSET_X, OFFSET_Y);

    //taskDISABLE_INTERRUPTS();
    lcdFillScreen(&dev, 0x23164);
    //taskENABLE_INTERRUPTS();

    lcdDrawFillCircle(&dev, 150, 150, 100, 0xFABC);

    //lcdDrawFillArrow(&dev, 150, 250, 150, 350, 5, RED);

    vTaskDelay(1000);

    IdleModeOn(&dev);

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
