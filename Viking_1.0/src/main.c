/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h> 
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/spi.h>
#include "max6921.c"

#define SLEEP_TIME_MS   200
#define ENABLE_TFT 		4
#define STATUS_CHARGE 	8
#define STATUS_PGOOD_BATTERY 	7


// ---- Prototype Functions ----------------------------------------------------

// -----------------------------------------------------------------------------

//------------------- MAIN LOOP ----------------------------------------------------------------------

void main(void)
{		
	// VFD display initialization
	const struct device *VFD_dev;
	VFD_dev = VFD_init();
	
	const struct device *gpio_dev;
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	
	
	gpio_pin_configure(gpio_dev, STATUS_CHARGE, GPIO_INPUT); 
	gpio_pin_configure(gpio_dev, STATUS_PGOOD_BATTERY , GPIO_INPUT); 
	gpio_pin_set(gpio_dev, ENABLE_TFT, 0); // Logic LOW enables 3.3v supply for TFT display


// -------------- STYLES Start ----------------------------------
	while (1) {
	
		k_sleep(K_MSEC(1000));
		
		int a = 0;
		int b = 0;
		while(a < 10){
			VFD_disp(VFD_dev, a, b);
			while(b < 10){
				VFD_disp(VFD_dev, a, b);
				k_msleep(SLEEP_TIME_MS);
				b++;
			}
			b = 0;
			a++;		
		}

		int power_good = gpio_pin_get_raw(gpio_dev, STATUS_PGOOD_BATTERY); // 0 indicates valid external power source connected, 1 = no power source
		int bat_charging = gpio_pin_get_raw(gpio_dev, STATUS_CHARGE); // 0 indicates battery charging, 1 = no charging taking place
	
	}
}


