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
#include <zephyr/drivers/fuel_gauge.h>
#include <string.h>
#include "max6921.c"

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL

#define SLEEP_TIME_MS   1000
#define ENABLE_TFT 		4  // PWM and enable for TFT LEDs
//#define ENABLE_DISP 	27 // Enable pin, enables TFT and VFD 3.3 volt power for drivers.
#define STATUS_CHARGE 	8  // GPIO connected to charge status of BQxx charge IC
#define STATUS_PGOOD_BATTERY 	7 // GPIO connected to battery status of BQxx charge IC
#define NRF_LED 29 // LED on Viking PCB 

/* change this to any other UART peripheral if desired */
#define MSG_SIZE 32

static const struct spi_config spi_cfg = {
	.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_MSB,
}; 

const struct device * display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
const struct device * gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	
const struct spi_dt_spec spi_spec = SPI_DT_SPEC_GET(DT_NODELABEL(bmi323), spi_cfg.operation, 0);
const struct device *const i2c_dev = DEVICE_DT_GET(DT_CHOSEN(maxim_max17048));


// -------- FUNCTIONS ---------------------------------------------------------------------

void bmi323_read_reg(int addr, int *rx_buffer)
{	// input: 7-bit register to read, pointer to rx buffer
	uint8_t reg = 128 + addr;
	int err;
	uint8_t tx_buffer[4] = {reg,0,0,0}; // buffer that holds address to read. Only first bytes valid	
	
	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
                .len = 4
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};


	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = 4	
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive_dt(&spi_spec, &tx, &rx);
	if (err){
                printk("error happening here\n");
        }
}

void bmi323_read_burst(int start_addr, int nbr_words, int *rx_buffer)
{	// start_addr: the start address to burst read
	// nbr_word: the number of words to read 
	int err;
	int nbr_bytes = (nbr_words * 2) + 2; // 2 bytes per word 

	uint8_t tx_buffer[nbr_bytes]; // buffer that holds address to read. Only first bytes valid	
	tx_buffer[0] = 128 + start_addr; // the MSB in the 8-bit address field need to be high to "read". 

	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
                .len = nbr_bytes
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};


	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = nbr_bytes	
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive_dt(&spi_spec, &tx, &rx);
	if (err){
                printk("error happening here\n");
        }
}

void bmi323_write_reg(int addr, int *tx_buffer)
{	// input: 7-bit register to read, pointer to rx buffer
	int err;

	uint8_t rx_buffer[3] = {0,0,0}; // buffer for rx - discarded not used for write	
	
	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
                .len = 3
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};


	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = 3	
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive_dt(&spi_spec, &tx, &rx);
	if (err){
                printk("error happening here\n");
        }
}


uint8_t rx_buffer[4] = {0,0,0,0}; // buffer that hold received data. Only two last bytes valid
uint8_t tx_buffer[3] = {0,0,0}; // buffer that hold transmit address and data to send
int16_t acc_x;
int16_t acc_y;
int16_t acc_z;
uint8_t rx_buffer_data[6+2]; // buffer that hold received data. Only two last bytes valid

struct fuel_gauge_get_property props[] = {
			{.property_type = FUEL_GAUGE_RUNTIME_TO_EMPTY,},
			{.property_type = FUEL_GAUGE_RUNTIME_TO_FULL,},
			{.property_type = FUEL_GAUGE_STATE_OF_CHARGE,},
			{.property_type = FUEL_GAUGE_VOLTAGE,}
		};

//------------------- MAIN LOOP ------------------------------------------------

void main(void)
{		
	k_sleep(K_MSEC(2000));

	// Initialize fuel gauge
	if (i2c_dev == NULL) {
		printk("\nError: no device found.\n");
		return 0;
	}

	if (!device_is_ready(i2c_dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       i2c_dev->name);
		return 0;
	}

	if (i2c_dev == NULL) {
		printk("Found device \"%s\", getting fuel gauge data\n", i2c_dev->name);
		return 0;
	}

	// Initialize BMI accelerometer sensor
	bmi323_read_reg(0x00, &rx_buffer); // Read Chip ID:
	bmi323_read_reg(0x01, &rx_buffer); // Check Power status, 0b0 = ok
	bmi323_read_reg(0x02, &rx_buffer); // sensor status 0b1 = ok, cleared after first read
	//printk("%d ",   rx_buffer[2]); // Data 7:0
	//printk("%d\n",  rx_buffer[3]); // Data 15:8
	k_sleep(K_MSEC(20)); // some delay for setup 
	uint8_t tx_buffer[3] = {0x20,0x27,0x31}; // set accelerometer 
	bmi323_write_reg(0x03, &tx_buffer);
	
	// VFD display initialization
	const struct device *VFD_dev;
	//VFD_dev = VFD_init();	

	// GPIO signals setup
	gpio_pin_configure(gpio_dev, ENABLE_TFT, GPIO_OUTPUT);  // TFT enable (PWM)
	gpio_pin_configure(gpio_dev, ENABLE_DISP, GPIO_OUTPUT);  // VFD enable
	gpio_pin_configure(gpio_dev, NRF_LED, GPIO_OUTPUT);  // LED enable
	gpio_pin_configure(gpio_dev, STATUS_CHARGE, GPIO_INPUT); 
	gpio_pin_configure(gpio_dev, STATUS_PGOOD_BATTERY , GPIO_INPUT); 
	gpio_pin_set(gpio_dev, ENABLE_TFT, 0); // Logic LOW enables 3.3v supply for LED in TFT display
	gpio_pin_set(gpio_dev, ENABLE_DISP, 0); // Logic LOW enables 3.3v supply TFT driver and VFD driver
	gpio_pin_set(gpio_dev, NRF_LED, 0);  // turn on LED

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
	lv_label_set_text(label1, "#ff0000 TOR#"); 
	lv_obj_align(label1, LV_ALIGN_CENTER, 0, -60);

	lv_obj_t *label2;
	label2 = lv_label_create(lv_scr_act());
	lv_label_set_recolor(label2, true);  
	lv_label_set_text(label2, "DESIGN");
	lv_obj_align(label2, LV_ALIGN_CENTER, 0, -45);

	lv_obj_t *label3;
	label3 = lv_label_create(lv_scr_act());
	lv_label_set_text(label3, LV_SYMBOL_BATTERY_3);
	lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);

	display_blanking_off(display_dev);

	lv_obj_t *label4;
	label4 = lv_label_create(lv_scr_act());
	lv_obj_align(label4, LV_ALIGN_BOTTOM_MID, 0, -60);

	lv_obj_t *label5;
	label5 = lv_label_create(lv_scr_act());
	lv_obj_align(label5, LV_ALIGN_BOTTOM_MID, 0, -45);
	
	lv_obj_t *label6;
	label6 = lv_label_create(lv_scr_act());
	lv_obj_align(label6, LV_ALIGN_BOTTOM_MID, 0, -30);

	lv_obj_t *label7;
	label7 = lv_label_create(lv_scr_act());
	lv_obj_align(label7, LV_ALIGN_BOTTOM_MID, 0, -15);

	lv_obj_t *label8;
	label8 = lv_label_create(lv_scr_act());
	lv_obj_align(label8, LV_ALIGN_BOTTOM_MID, 0, 0);

	lv_obj_t *label9;
	label9 = lv_label_create(lv_scr_act());
	lv_obj_align(label9, LV_ALIGN_CENTER, 0, -15);

	char x_buf[16];
	char y_buf[16];
	char z_buf[16];
	char p_good[16];
	char b_good[16];
	char voltage_buf[16];

	int ret = 0;

	while (1) {
		
		k_sleep(K_MSEC(2000));
		gpio_pin_set(gpio_dev, NRF_LED, 1); // turn on LED
		k_sleep(K_MSEC(100));
		gpio_pin_set(gpio_dev, NRF_LED, 0);  // turn off LED

		ret = fuel_gauge_get_prop(i2c_dev, props, ARRAY_SIZE(props));
		int bat_voltage;
		if (ret < 0) {
			printk("Error: cannot get properties\n");
		} else {
			if (ret != 0) {
				printk("Warning: Some properties failed\n");
			}

			if (props[3].status == 0) {
				bat_voltage = props[3].value.voltage;
				printk("Voltage %d\n", bat_voltage);
			} else {
				printk(
				"Property FUEL_GAUGE_VOLTAGE failed with error %d\n",
				props[3].status
				);
			}
		}
		snprintf(voltage_buf, 16, "%d volt", bat_voltage);
		lv_label_set_text(label9, voltage_buf);
		
		bmi323_read_burst(0x03, 3,  &rx_buffer_data);
		acc_x = (((rx_buffer_data[3]) << 8) | (rx_buffer_data[2])); // left shift MSByte and OR with LSB to form 16-bit value
		acc_y = (((rx_buffer_data[5]) << 8) | (rx_buffer_data[4])); // left shift MSByte and OR with LSB to form 16-bit value
		acc_z = (((rx_buffer_data[7]) << 8) | (rx_buffer_data[6])); // left shift MSByte and OR with LSB to form 16-bit value
		snprintf(x_buf, 16, "x: %d", acc_x);
		snprintf(y_buf, 16, "y: %d", acc_y);
		snprintf(z_buf, 16, "z: %d", acc_z);
		lv_label_set_text(label4, x_buf);
		lv_label_set_text(label5, y_buf);
		lv_label_set_text(label6, z_buf);

		int16_t power_good = gpio_pin_get_raw(gpio_dev, STATUS_PGOOD_BATTERY); // 0 indicates valid external power source connected, 1 = no power source
		int16_t bat_charging = gpio_pin_get_raw(gpio_dev, STATUS_CHARGE); // 0 indicates battery charging, 1 = no charging taking place

		//printk("External power:%d,", power_good);
		//printk("Charging:%d,", bat_charging);

		snprintf(b_good, 16, "Charge: %d", bat_charging);
		snprintf(p_good, 16, "Power: %d", power_good); 
		lv_label_set_text(label7, b_good);
		lv_label_set_text(label8, p_good);

		lv_task_handler();	
	}
}


