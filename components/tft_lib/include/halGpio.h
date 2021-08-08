#ifndef _HALGPIO_H
#define _HALGPIO_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define HIGH 1
#define LOW 0
#define OUTPUT GPIO_MODE_OUTPUT
#define INPUT GPIO_MODE_INPUT

void pinMode(int pin, int mode) {
    //INSERT GPIO DRIVE LOGIC
    gpio_reset_pin(pin);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(pin, mode);
}

void digitalWrite(int pin, int val) {
    //INSERT GPIO DRIVE LOGIC
    gpio_set_level(pin, val);

}

void delay(int msec) {
    vTaskDelay(msec / portTICK_PERIOD_MS);
}
#endif