#include <stdio.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
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

int bmp280_spi_test(void);



int main(void)
{
	DDRB |= (1<<5);
	PORTB |= (1<<5);
	init_uart_stdout();

	uint8_t tmp;
	rscs_uart_read(uart0, &tmp, 1);

	while(1)
	{
		int code = 231; //Why? Why not?!

		code = bmp280_spi_test();
		printf("BMP280: test complete, exit code %d\n", code);

		/*code = bmp180_i2c_test();
		printf("test_complete with code: %d\n", code);*/
	}

	return 0;
}





