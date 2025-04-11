/*
* Copyright (c) 2016 Intel Corporation
*
* SPDX-License-Identifier: Apache-2.0
*/

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED_IO_NODE DT_NODELABEL(led_io)

static const struct gpio_dt_spec led_io = GPIO_DT_SPEC_GET(LED_IO_NODE, gpios);

int main(void)
{
    int ret;
    bool led_state = true;
    
    if (!gpio_is_ready_dt(&led_io)) {
        return 0;
    }
    
    ret = gpio_pin_configure_dt(&led_io, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 0;
    }

    while (1) {
        ret = gpio_pin_toggle_dt(&led_io);
        if (ret < 0) {
            return 0;
        }

        led_state = !led_state;
        printf("LED state: %s\n", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
