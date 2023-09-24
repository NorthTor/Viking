/*
* Copyright (c) 2012-2023 Viking TD Tordesign.net 
*/

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/spi.h>


static const struct spi_config spi_cfg = {
	.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_LSB,
}; 

const struct spi_dt_spec spi_spec = SPI_DT_SPEC_GET(DT_NODELABEL(bmi323), spi_cfg.operation, 0);


//static void spi_init(void){
//	if(spi_spec == NULL) {
//		printk("Could not get %s device\n", spi_spec);
//		return;
//	};
//}

void spi_test_send(void)
{
	int err;
	static uint8_t tx_buffer[3] = {1,1,1}; // sends 3 bytes with each byte set to 1
	static uint8_t rx_buffer[4]; // 4 byte: one address, one dummy and two data bytes

	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
		//.len = sizeof(tx_buffer)
                .len = 3
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = 3
                //sizeof(rx_buffer),
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive_dt(&spi_spec, &tx, &rx);
	if (err){
                printk("error fappening\n");
        }	
}

void main(void)
{
	printk("SPIM Example\n");
	printk("After init\n");
	while (1) {
		spi_test_send();
		//k_sleep(K_MSEC(1000));
		printk(".");
	}
}


