#include <stdio.h>

#include <util/delay.h>
#include <avr/interrupt.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
#include "rscs/tsl2561.h"
#include "rscs/spi.h"
#include "rscs/stdext/stdio.h"

/* В этом файле располагаются различные тесты */

rscs_uart_bus_t * uart0;

// инициализация отладочного UART в STDOUT
int init_uart_stdout(void)
{
	uart0 = rscs_uart_init(RSCS_UART_ID_UART0, 	RSCS_UART_FLAG_ENABLE_TX |
												RSCS_UART_FLAG_ENABLE_RX |
												RSCS_UART_FLAG_BUFFER_RX);
	if (!uart0)
		return 1;

	rscs_uart_set_baudrate(uart0, 9600);
	rscs_uart_set_character_size(uart0, 8);
	rscs_uart_set_parity(uart0, RSCS_UART_PARITY_NONE);
	rscs_uart_set_stop_bits(uart0, RSCS_UART_STOP_BITS_ONE);

	stdout = rscs_make_uart_stream(uart0);
	return 0;
}


// ========================================================
// Функции тестов
// ========================================================
// тест i2c на примере барометра bmp180
// в тесте читаются калибровочные данные устройства
//int bmp180_i2c_test(void);


int tsl2561_test(void)
{
	uint16_t sensor_data0;
	uint16_t sensor_data1;

	rscs_i2c_init();
	init_uart_stdout();

	rscs_tsl2561_t * s1 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_LOW);
	rscs_tsl2561_t * s2 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_FLOATING);
	rscs_tsl2561_t * s3 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_HIGH);

	rscs_e error;
	error = rscs_tsl2561_setup(s1);
	error = rscs_tsl2561_setup(s2);
	error = rscs_tsl2561_setup(s3);

	while(1)
	{

		printf("read_error %d\n", error);

		error = rscs_tsl2561_read(s1, &sensor_data0, &sensor_data1);
		error = rscs_tsl2561_read(s2, &sensor_data0, &sensor_data1);
		error = rscs_tsl2561_read(s3, &sensor_data0, &sensor_data1);

		uint16_t lux1 = rscs_tsl2561_get_lux(s1, RSCS_TSL2561_GAIN_1X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);
		uint16_t lux2 = rscs_tsl2561_get_lux(s2, RSCS_TSL2561_GAIN_1X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);
		uint16_t lux3 = rscs_tsl2561_get_lux(s3, RSCS_TSL2561_GAIN_16X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);

		printf("lux1 = %d\n", lux1);
		printf("lux2 = %d\n", lux2);
		printf("lux3 = %d\n", lux3);

		_delay_ms(500);
	}

	return 0;
}





