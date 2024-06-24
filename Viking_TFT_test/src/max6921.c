// Autohor: Tor Kaufmann Gjerde

/*
Driver for the MAX6921 Vacuum Florecent Display Driver IC 
Used in the Viking hardware configuration.

9 first bits MSBs in the array represent the segments in one tube, 
next 9 bits represents the segments in the second VFD tube.
Mapping of VFD segments to data array --> 
[grid, dot, 6, 4, 3, 13, 10, 11, 14, grid, dot, 6, 4, 3, 13, 10, 11, 14, 0, 0]

The two last bits are not used in HW and should always be set to zero.
LSB of the data array is clocked in last over the SPI bus and ends up as the MSBs (OUT1 and OUT2)
in the shift register.

*/

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "max6921.h"



// ---- Prototype functions ----------------------------------------
const struct device * VFD_init(void);
int VFD_disp(const struct device *dev, int vfd1, int vfd2);
int disp_VFD_20_bit(const struct device *dev, int data_array[20]);
// -----------------------------------------------------------------



// function to Initialize the MAX6921 
const struct device * VFD_init(void){

	const struct device *gpio_dev;
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
	
	gpio_pin_configure(gpio_dev, ENABLE_DISP, GPIO_OUTPUT); // enable 3.3v power for max driver (and TFT driver)
	gpio_pin_configure(gpio_dev, ENABLE_HV, GPIO_OUTPUT);  // ENABLE HV
    gpio_pin_configure(gpio_dev, CLOCK, GPIO_OUTPUT);  // CLOCK
	gpio_pin_configure(gpio_dev, LOAD, GPIO_OUTPUT);  // LOAD
	gpio_pin_configure(gpio_dev, DATA, GPIO_OUTPUT);  // DATA
	gpio_pin_configure(gpio_dev, BLANK, GPIO_OUTPUT);  // BLANK

	return gpio_dev;
}

/*
VFD_off(void){
	Disable High Voltage and Low voltage supplies. Hardware should be updated with a switch to turn off rail to MAX6921 Driver
	Set data array to zero and send to driver 
}

int VFD_disp_seg(){

}
*/


int VFD_disp(const struct device *VFD_dev, int vfd1, int vfd2){
// [grid, dot, 6, 4, 3, 13, 10, 11, 14, grid, dot, 6, 4, 3, 13, 10, 11, 14, 0, 0]
    //following 9-bit data arrays produce integers 1-9:

	int bit_map[10][10] = {
		{1, 0, 1, 1, 1, 0, 1, 1, 1},   // number 0, row 1
   		{1, 0, 1, 0, 0, 0, 1, 0, 0},   // number 1, row 2  
   		{1, 0, 0, 1, 1, 1, 1, 1, 0},   // number 2, row 3 etc.
   		{1, 0, 1, 1, 0, 1, 1, 1, 0},   // number 3
   		{1, 0, 1, 0, 0, 1, 1, 0, 1},   // number 4
   		{1, 0, 1, 1, 0, 1, 0, 1, 1},   // number 5
   		{1, 0, 1, 1, 1, 1, 0, 1, 1},   // number 6
   		{1, 0, 1, 0, 0, 0, 1, 1, 0},   // number 7
   		{1, 0, 1, 1, 1, 1, 1, 1, 1},   // number 8
   		{1, 0, 1, 0, 0, 1, 1, 1, 1}     // number 9
		};

	int bit_array[20] = {0,0,0,0,0,0,0,0,0,0,
						 0,0,0,0,0,0,0,0,0,0 
						};
	
	int i = 0;
	int cnt = 0;
	while(cnt<18){
		// 18 as the last to bits in the array is not used  and remains zero
		if(i > 8){
			i = 0;
		}
		if(cnt < 9){
			bit_array[cnt] = bit_map[vfd1][i];
		}
		if(cnt > 8){
			bit_array[cnt] = bit_map[vfd2][i];
		};
		i++; 
		cnt++;		
	}
	//send the 20-bit array to max6921 
	int ret = disp_VFD_20_bit(VFD_dev, bit_array);
	return ret;
} 	



// Bit-bang function for 20-bit data transfer
int disp_VFD_20_bit(const struct device *gpio_dev, int data_array[20]) {
	
	gpio_pin_set(gpio_dev, ENABLE_DISP, 0); // Logic LOW enable voltage 3.3v supply for MAX driver (also enables 3.3v to TFT)
	gpio_pin_set(gpio_dev, ENABLE_HV, 1); // Logic HIGH enable voltage supply
	gpio_pin_set(gpio_dev, BLANK, 0); // set blank low for enable driver output
	gpio_pin_set(gpio_dev, LOAD, 1); // LOAD register with falling edge on LOAD

	for(int i = 0; i < 20; i++){
		// bitbang bit array
		gpio_pin_set(gpio_dev, CLOCK, 0); // set clk low
		gpio_pin_set(gpio_dev, DATA, data_array[i]); // set data pin from data array
		gpio_pin_set(gpio_dev, CLOCK, 1); // set clk high
	}
	gpio_pin_set(gpio_dev, CLOCK, 0); // set clk line low again until next transfer is initiated
	gpio_pin_set(gpio_dev, LOAD, 0); // LOAD register with falling edge on LOAD

	return 0;
}
