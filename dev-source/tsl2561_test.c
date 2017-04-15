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


int main(void)
{
	uint16_t sensor_data0;
	uint16_t sensor_data1;

	rscs_i2c_init();
	init_uart_stdout();
	rscs_e error = rscs_tsl2561_init();
	printf("init_error %d\n", error);

	while(1)
	{
		error = rscs_tsl2561_read(&sensor_data0, &sensor_data1);
		printf("read_error %d\n", error);
		uint16_t lux = get_lux(0, 2, sensor_data0, sensor_data1, 1);
		printf("lux = %d\n", lux);
		_delay_ms(500);
	}

	return 0;
}





