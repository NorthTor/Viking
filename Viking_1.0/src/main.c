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
#include <zephyr/kernel.h> 
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/spi.h>
#include <string.h>
#include "max6921.c"

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL

#define SLEEP_TIME_MS   200
#define ENABLE_TFT 		4
#define STATUS_CHARGE 	8
#define STATUS_PGOOD_BATTERY 	7

/* change this to any other UART peripheral if desired */
#define MSG_SIZE 32

const struct device * uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));
const struct device * display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

// ---- Prototype functions ----------------------------------------------------
void print_uart(char *buf);
const struct device * spi_init(void);
void spi_test_send(const struct device *spi_dev);
// -----------------------------------------------------------------------------

static const struct spi_config spi_cfg = {
	.operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB |
		     SPI_MODE_CPOL | SPI_MODE_CPHA,
	.frequency = 200000,
	.slave = 0,
};

const struct device * spi_init(void)
{
	const struct device *spi_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_sensor));
	if (spi_dev == NULL) {
		print_uart("Could not get spi device");
		return;
	}
	return spi_dev;
};


void spi_test_send(const struct device *spi_dev)
{
	int err;
	static uint8_t tx_buffer[1];
	static uint8_t rx_buffer[1];

	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
		.len = sizeof(tx_buffer)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = sizeof(rx_buffer),
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};


	err = spi_transceive(spi_dev, &spi_cfg, &tx, &rx);
	if (err) {
		print_uart("SPI error");
	} else {
		//Connect MISO to MOSI for loopback
		print_uart("TX sent");
		print_uart("RX recv");
		tx_buffer[0]++;
	}	
}


void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
};


//------------------- MAIN LOOP ----------------------------------------------------------------------

void main(void)
{		
	// VFD display initialization
	const struct device *VFD_dev;
	VFD_dev = VFD_init();

	const struct device *spi_dev2;
	print_uart("spi Example\n");
	spi_dev2 = spi_init();
	print_uart("After init\n");
	

	// TFT Enable signal 
	const struct device *gpio_dev;
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	
	
	gpio_pin_configure(gpio_dev, ENABLE_TFT, GPIO_OUTPUT);  // TFT
	gpio_pin_configure(gpio_dev, STATUS_CHARGE, GPIO_INPUT); 
	gpio_pin_configure(gpio_dev, STATUS_PGOOD_BATTERY , GPIO_INPUT); 
	gpio_pin_set(gpio_dev, ENABLE_TFT, 0); // Logic LOW enables 3.3v supply for TFT display


	const struct device *display_dev;
	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		print_uart("Could not get display device\n");
		return;
	}


// -------------- STYLES Start ----------------------------------
	uint8_t	R = 0;
	uint8_t	G = 0;
	uint8_t	B = 0;
	lv_color_t custom_color = lv_color_make(R, G, B);
	
	lv_obj_set_style_bg_color(lv_scr_act(), custom_color, LV_PART_MAIN);
	lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);

	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, custom_color);
	lv_style_set_border_width(&style, 0);

// -------------- STYLES end ----------------------------------

	lv_obj_t *bg;
	bg = lv_obj_create(lv_scr_act());
	lv_obj_set_size(bg, 80, 160);
	lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(bg, &style, LV_STATE_DEFAULT);	

	lv_obj_t *label1;
	label1 = lv_label_create(lv_scr_act());
	lv_label_set_recolor(label1, true);  
	lv_label_set_text(label1, "100k");
	lv_obj_align(label1, LV_ALIGN_CENTER, 0, -60);

	lv_obj_t *label2;
	label2 = lv_label_create(lv_scr_act());
	lv_label_set_recolor(label1, true);  
	lv_label_set_text(label2, "DESIGN");
	lv_obj_align(label2, LV_ALIGN_CENTER, 0, -45);

	lv_obj_t *label5;
	label5 = lv_label_create(lv_scr_act());
	lv_label_set_text(label5, LV_SYMBOL_POWER);
	lv_obj_align(label5, LV_ALIGN_CENTER, 0, 0);
	
	lv_task_handler();


	display_blanking_off(display_dev);


	while (1) {
		
		spi_test_send(spi_dev2);
		k_sleep(K_MSEC(1000));
		print_uart(".\n");
		

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

		lv_obj_t *label3;
		label3 = lv_label_create(lv_scr_act());
		if(power_good == 1){
			lv_label_set_text(label3, "Power: OFF");
		}
		char buf1[32];
		char buf2[32];

        snprintf(buf1, 32, "Charge: %d", bat_charging);
		snprintf(buf2, 32, "Power: %d", power_good); 
		lv_label_set_text(label3, buf1);
		lv_obj_align(label3, LV_ALIGN_BOTTOM_MID, 0, 0);

		lv_obj_t *label4;
		label4 = lv_label_create(lv_scr_act());
		lv_label_set_text(label4, buf2);
		lv_obj_align(label4, LV_ALIGN_BOTTOM_MID, 0, -15);

		lv_task_handler();
		
	}
}


