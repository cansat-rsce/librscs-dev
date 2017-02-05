#include <stdio.h>

#include "rscs/uart.h"
#include "rscs/stdext/stdio.h"


// пример оформшения теста - функция аналогичная main
// в этом примере тестируется UART
// допустим использование параметров
int uart_test(void)
{
	rscs_uart_bus_t * uart = rscs_uart_init(RSCS_UART_ID_UART0, RSCS_UART_FLAG_ENABLE_TX);
	if (!uart)
		return 1;

	rscs_uart_set_baudrate(uart, 9600);
	rscs_uart_set_character_size(uart, 8);
	rscs_uart_set_parity(uart, RSCS_UART_PARITY_NONE);
	rscs_uart_set_stop_bits(uart, RSCS_UART_STOP_BITS_ONE);

	FILE * f = rscs_make_uart_stream(uart);
	fprintf(f, "hello world!\n");

	rscs_uart_deinit(uart);

	return 0;
}


int main(void)
{
	return 0;
}
