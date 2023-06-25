// Functions 

/*
Functions for the MAX6921 VFD Driver IC on the Tor Design Viking display

9 first bits MSBs in the array represent the segments in one tube, 
next 9 bits represents the segments in the second VFD tube.
Mapping of VFD segments to data array --> 
[grid, dot, 6, 4, 3, 13, 10, 11, 14, grid, dot, 6, 4, 3, 13, 10, 11, 14, 0, 0]

The two last bits are not used and should always be set to zero.
LSB of the data array is clocked in last over the SPI bus and ends up as the MSBs (OUT1 and OUT2)
in the shift register.

// Initialize the MAX6921 
*/

VFD_init(struct *dev){

	// dev: pointer - "A variable that is used to store an address"
	dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	// Values are asigned to the variable in this case a struct?
	gpio_pin_configure(dev, ENABLE_HV, GPIO_OUTPUT);  // ENABLE HV
    gpio_pin_configure(dev, CLOCK, GPIO_OUTPUT);  // CLOCK
	gpio_pin_configure(dev, LOAD, GPIO_OUTPUT);  // LOAD
	gpio_pin_configure(dev, DATA, GPIO_OUTPUT);  // DATA
	gpio_pin_configure(dev, BLANK, GPIO_OUTPUT);  // BLANK

	gpio_pin_set(dev, ENABLE_HV, 1); // Logic HIGH enable voltage supply
	gpio_pin_set(dev, BLANK, 0); // set blank low for enable driver output
	gpio_pin_set(gpio_dev, LOAD, 1); // LOAD register with falling edge on LOAD
}


VFD_off(void){
	Disable High Voltage and Low voltage supplies. Hardware should be updated with a switch to turn off rail to MAX6921 Driver
	Set data array to zero and send to driver 
	

    
}

VFD_disp(int_vfd1, int_vfd2){
    case
    // following 9-bit data arrays produce integers 1-9:

    one = {};
    two = {};
    three = {};
    four = {};
    five = {};
    six = {};
    seven = {};
    eight = {};
    nine = {};
    
    combine all one-to-nine arrays in one array and then use input int_vfdx
    to access the array

    combined_array =[x1, x2, ..., x81 ];

    array_int1_indx_start =  combined_array
    array_int2_indx_start =  combined_array

    
}







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

				
void display_VFD(int data_array[20]) {

	const struct device *gpio_dev; // decleare pointer - "A variable that is used to store an address"
	gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));	// Values are asigned to the variable in this case a struct?

	gpio_pin_configure(gpio_dev, ENABLE_HV, GPIO_OUTPUT);  // ENABLE HV
    gpio_pin_configure(gpio_dev, CLOCK, GPIO_OUTPUT);  // CLOCK
	gpio_pin_configure(gpio_dev, LOAD, GPIO_OUTPUT);  // LOAD
	gpio_pin_configure(gpio_dev, DATA, GPIO_OUTPUT);  // DATA
	gpio_pin_configure(gpio_dev, BLANK, GPIO_OUTPUT);  // BLANK

	gpio_pin_set(gpio_dev, ENABLE_HV, 1); // Logic HIGH enable voltage supply
	gpio_pin_set(gpio_dev, BLANK, 0); // set blank low for enable driver output
	gpio_pin_set(gpio_dev, LOAD, 1); // LOAD register with falling edge on LOAD


	for(int i = 0; i < 20; i++){
		// bitbang bit array
		gpio_pin_set(gpio_dev, CLOCK, 0); // set clk low
		gpio_pin_set(gpio_dev, DATA, data_array[i]); // set data pin from data array
		gpio_pin_set(gpio_dev, CLOCK, 1); // set clk high
	}
	gpio_pin_set(gpio_dev, LOAD, 0); 
}
