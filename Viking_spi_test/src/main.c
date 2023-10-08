/*
* Copyright (c) 2012-2023 Viking TD Tordesign.net 
*/

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/spi.h>


static const struct spi_config spi_cfg = {
	.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_MSB,
}; 

const struct spi_dt_spec spi_spec = SPI_DT_SPEC_GET(DT_NODELABEL(bmi323), spi_cfg.operation, 0);


/*
int bmi323_com_status(void){
	// device communication test
	// 1. Read 16 bit register at address 0x00 - configures to SPI
	// 2. Read 16 bit register at address 0x00 - if value 0 com. test ok.
	static uint8_t rx_buffer[2]; // 2 byte buffer 16 bits of data
	static uint8_t tx_buffer[2]; // 2 byte buffer 16 bits of data
	// we want to send and receive 4 bytes.
	// actual data is sent during the first byte clocks and actual data transmitted during the last two byte clocks
	
	printk(rx_buffer);
}


int bmi323_init_status(void){
// initialize bme323 -> check that power ok and sensor status 
}

int bmi323_write(uint8_t register_to_write, int *tx_buffer){
	// input: 7 bit register to read, pointer to tx buffer.
}

*/


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

void main(void)
{	k_sleep(K_MSEC(2000));
	//printk("SPIM Example\n");
	bmi323_read_reg(0x00, &rx_buffer); // Read Chip ID:
	
	//printk("%x ",   rx_buffer[2]); // Data 7:0
	//printk("%x\n",  rx_buffer[3]); // Data 15:8

	bmi323_read_reg(0x01, &rx_buffer); // Check Power status, 0b0 = ok
	//printk("%x ",   rx_buffer[2]); // Data 7:0
	//printk("%x\n",  rx_buffer[3]); // Data 15:8
	
	bmi323_read_reg(0x02, &rx_buffer); // sensor status 0b1 = ok, cleared after first read
	//printk("%d ",   rx_buffer[2]); // Data 7:0
	//printk("%d\n",  rx_buffer[3]); // Data 15:8
	//printk("After init\n");

	
	uint8_t tx_buffer[3] = {0x20,0x27,0x31}; // set accelerometer 
	bmi323_write_reg(0x03, &tx_buffer);
	uint16_t acc_x;
	uint16_t acc_y;
	uint16_t acc_z;
	uint8_t rx_buffer[6+2]; // buffer that hold received data. Only two last bytes valid
	while (1) {
		bmi323_read_burst(0x03, 3,  &rx_buffer);
		k_sleep(K_MSEC(10));
		acc_x = (((rx_buffer[3]) << 8) | (rx_buffer[2])); // left shift MSByte and OR with LSB to form 16-bit value
		acc_y = (((rx_buffer[5]) << 8) | (rx_buffer[4])); // left shift MSByte and OR with LSB to form 16-bit value
		acc_z = (((rx_buffer[7]) << 8) | (rx_buffer[6])); // left shift MSByte and OR with LSB to form 16-bit value
		printk("Acc_x:%d,",acc_x);
		printk("Acc_y:%d,",acc_y);
		printk("Acc_z:%d,",acc_z - 60000);
		printk("\n");

		k_sleep(K_MSEC(10));
	}
}


