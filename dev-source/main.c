#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
#include "rscs/servo.h"
#include "rscs/ina219.h"

#include "rscs/stdext/stdio.h"


/* В этом файле располагаются различные тесты */

rscs_uart_bus_t * uart0;
// инициализация отладочного UART в STDOUT

int ina219_test()
{
	rscs_ina219_t * device;
	rscs_e error;

	uint16_t powerValue;
	uint8_t ina219_adr = (0b1000101);

	device = rscs_ina219_init(ina219_adr);
	printf("init Ok\n");

	error = rscs_ina219_set_cal(device, 50, 100);
	if (error != RSCS_E_NONE){
		printf("calibration error , error # %i\n", error);
		return error;
	}
	printf("calibration Ok!\n");

	error = rscs_ina219_start_continuous(device,RSCS_INA219_CHANNEL_POWER);
	if (error != RSCS_E_NONE){
		printf("start error , error # %i\n", error);
		return error;
	}
	printf("start Ok!\n");

	while(1)
	{
		error = rscs_ina219_read(device, RSCS_INA219_CHANNEL_POWER, &powerValue);
		printf("%i", powerValue);
		_delay_us(100);
	}

	return RSCS_E_NONE;
}
int init_uart_stdout(void)
{
	uart0 = rscs_uart_init(RSCS_UART_ID_UART0, 	RSCS_UART_FLAG_ENABLE_TX |
												RSCS_UART_FLAG_BUFFER_TX |
												RSCS_UART_FLAG_ENABLE_RX |
												RSCS_UART_FLAG_BUFFER_RX);
	if (!uart0)
		return 1;

	rscs_uart_set_baudrate(uart0, 57600);
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

/*int servo_test()
{
	rscs_servo_init(2);
	rscs_servo_timer_init();
	char buffer[20] = { 0 };
	uint16_t buffer_carret = 0;
	printf("initialized\n");
	while(1)
	{
		size_t readed = rscs_uart_read_some(uart0,
				&buffer[buffer_carret],
				sizeof(buffer) - buffer_carret);
		buffer_carret += readed;
		if (buffer_carret != 0)
		{
			if (buffer[buffer_carret-1] == '\n')
			{
				printf("Command ended\n");
				int com1;
				int com2;
				int result = sscanf(buffer, "%d %d", &com1, &com2);
				if (!result)
				{
					printf("FAILED\n");
				}
				else
				{
					_servo_set_mcs(1, com2);
					_servo_set_mcs(0, com1);
					for(int i = 0; i < 20; i++)
					{
						buffer[i] = 0;
					}
					buffer_carret = 0;
				}
			}
		}
	}
	return 0;
}*/

int main(void)
{
	sei();
	init_uart_stdout();
	rscs_i2c_init();
	//rscs_i2c_set_scl_rate(16);
	printf("hellloooo\n");

	ina219_test();

	//printf("you're so stupid");

	//DDRB |= (1 << 5);
	//servo_test();

	while(1)
	{
		//int code = bmp180_i2c_test();
		//printf("test_complete with code: %d\n", code);
	}

	return 0;
}





