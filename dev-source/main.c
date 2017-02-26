#include <stdio.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
#include "rscs/stdext/stdio.h"

/* В этом файле располагаются различные тесты */


// инициализация отладочного UART в STDOUT
int init_uart_stdout(void)
{
	rscs_uart_bus_t * uart = rscs_uart_init(RSCS_UART_ID_UART0, RSCS_UART_FLAG_ENABLE_TX);
	if (!uart)
		return 1;

	rscs_uart_set_baudrate(uart, 9600);
	rscs_uart_set_character_size(uart, 8);
	rscs_uart_set_parity(uart, RSCS_UART_PARITY_NONE);
	rscs_uart_set_stop_bits(uart, RSCS_UART_STOP_BITS_ONE);

	stdout = rscs_make_uart_stream(uart);
	return 0;
}


// ========================================================
// Функции тестов
// ========================================================
// тест i2c на примере барометра bmp180
// в тесте читаются калибровочные данные устройства
int bmp180_i2c_test(void);



int main(void)
{
	init_uart_stdout();

	while(1)
	{
		int code = bmp180_i2c_test();
		printf("test_complete with code: %d\n", code);
	}

	return 0;
}





