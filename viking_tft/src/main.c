/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/zephyr.h>
#include <sys/printk.h>
#include <drivers/gpio.h>
#include <zephyr/logging/log.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL

#define SLEEP_TIME_MS   100
#define ENABLE_TFT 		4
#define STATUS_CHARGE 	8
#define STATUS_PGOOD_BATTERY 	7

#define CLOCK 21
#define LOAD 22
#define BLANK 23
#define DATA 24
#define ENABLE_HV 25


/* function declaration */
void display_VFD(int data_array[20]);



void main(void)
{		
	int data1[] = {	1,0,0,1,0,0,0,0,0,
					1,0,0,1,0,0,0,0,0,
					0,0
				};

	int data2[] = {	1,0,1,0,0,0,0,0,0,
					1,0,1,0,0,0,0,0,0,
					0,0
				};

	int data3[] = {	1,0,0,0,0,0,1,0,0,
					1,0,0,0,0,0,1,0,0,
					0,0
				};

	int data4[] = {	1,0,0,0,0,0,0,1,0,
					1,0,0,0,0,0,0,1,0,
					0,0
				};
	int data5[] = {	1,0,0,0,0,0,0,0,1,
					1,0,0,0,0,0,0,0,1,
					0,0
				};	
	
	int data6[] = {	1,0,0,0,1,0,0,0,0,
					1,0,0,0,1,0,0,0,0,
					0,0
				};



	const struct device *display_dev;

	lv_obj_t *label1;
	lv_obj_t *label2;
	lv_obj_t *label3;
	lv_obj_t *label4;

	const struct device *gpio_dev;
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	
	gpio_pin_configure(gpio_dev, ENABLE_TFT, GPIO_OUTPUT);  // ENABLE HV
	gpio_pin_configure(gpio_dev, STATUS_CHARGE, GPIO_INPUT);  // ENABLE HV
	gpio_pin_configure(gpio_dev, STATUS_PGOOD_BATTERY , GPIO_INPUT);  // ENABLE HV
	gpio_pin_set(gpio_dev, ENABLE_TFT, 0); // Logic LOW enables 3.3v supply for TFT display


	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		printk("Could not get device\n", display_dev);
		return;
	}


	label1 = lv_label_create(lv_scr_act());
	label2 = lv_label_create(lv_scr_act());
	label3 = lv_label_create(lv_scr_act());
	label4 = lv_label_create(lv_scr_act());

	lv_label_set_text(label1, "TOR");
	lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
	lv_label_set_text(label2, "DESIGN");
	lv_obj_align(label2, LV_ALIGN_CENTER, 0, 15);

	lv_task_handler();
	display_blanking_off(display_dev);


	while (1) {
		display_VFD(data1);
		k_msleep(SLEEP_TIME_MS);
		display_VFD(data2);
		k_msleep(SLEEP_TIME_MS);
		display_VFD(data3);
		k_msleep(SLEEP_TIME_MS);
		display_VFD(data4);
		k_msleep(SLEEP_TIME_MS);
		display_VFD(data5);
		k_msleep(SLEEP_TIME_MS);
		display_VFD(data6);
		k_msleep(SLEEP_TIME_MS);

		int power_good = gpio_pin_get_raw(gpio_dev, STATUS_PGOOD_BATTERY); // 0 indicates valid external power source connected, 1 = no power source
		int bat_charging = gpio_pin_get_raw(gpio_dev, STATUS_CHARGE); // 0 indicates battery charging, 1 = no charging taking place

		if(power_good = 1){
			lv_label_set_text(label3, "Power: OFF");
		}
		char buf1[32];
		char buf2[32];

        snprintf(buf1, 32, "Charge: %d", bat_charging);
		printf(buf2, 32, "Power: %d", power_good); 
		lv_label_set_text(label3, buf1);
		lv_obj_align(label3, LV_ALIGN_BOTTOM_MID, 0, 0);

		lv_label_set_text(label4, buf2);
		lv_obj_align(label4, LV_ALIGN_BOTTOM_MID, 0, -15);

		lv_task_handler();
		
	}
}


// Functions 
void display_VFD(int data_array[20]) {

	const struct device *gpio_dev;
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	

	gpio_pin_configure(gpio_dev, ENABLE_HV, GPIO_OUTPUT);  // ENABLE HV
    gpio_pin_configure(gpio_dev, CLOCK, GPIO_OUTPUT);  // CLOCK
	gpio_pin_configure(gpio_dev, LOAD, GPIO_OUTPUT);  // LOAD
	gpio_pin_configure(gpio_dev, DATA, GPIO_OUTPUT);  // DATA
	gpio_pin_configure(gpio_dev, BLANK, GPIO_OUTPUT);  // BLANK

	gpio_pin_set(gpio_dev, ENABLE_HV, 1); // Logic HIGH enable voltage supply
	gpio_pin_set(gpio_dev, BLANK, 0); // set blank low for enable driver output
	gpio_pin_set(gpio_dev, LOAD, 1); // LOAD register with falling edge on LOAD


	for(int i = 0; i < 20; i++){
		// bitbang bit array into max6921 driver
		gpio_pin_set(gpio_dev, CLOCK, 0); // set clk low
		gpio_pin_set(gpio_dev, DATA, data_array[i]); // set data pin from data array
		gpio_pin_set(gpio_dev, CLOCK, 1); // set clk high
	}
	gpio_pin_set(gpio_dev, LOAD, 0); 
}
