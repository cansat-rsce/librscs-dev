#include <stdio.h>

#include <util/delay.h>
#include <avr/interrupt.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
#include "rscs/spi.h"
#include "rscs/stdext/stdio.h"

#include <rscs/gps_nmea.h>

/* В этом файле располагаются различные тесты */

rscs_uart_bus_t * uart1;

// инициализация отладочного UART в STDOUT
int init_uart_stdout(void)
{
	uart1 = rscs_uart_init(RSCS_UART_ID_UART1, 	RSCS_UART_FLAG_ENABLE_TX);
	if (!uart1)
		return 1;

	rscs_uart_set_baudrate(uart1, 9600);
	rscs_uart_set_character_size(uart1, 8);
	rscs_uart_set_parity(uart1, RSCS_UART_PARITY_NONE);
	rscs_uart_set_stop_bits(uart1, RSCS_UART_STOP_BITS_ONE);

	stdout = rscs_make_uart_stream(uart1);
	return 0;
}


// ========================================================
// Функции тестов
// ========================================================
// тест i2c на примере барометра bmp180
// в тесте читаются калибровочные данные устройства
//int bmp180_i2c_test(void);
/*
rscs_e bmp280_spi_test(void);
rscs_e adc_internal_test(void);
rscs_e adxl345_test(void);
rscs_e ads1115_test(void);
rscs_e tsl2561_test(void);

*/
int main(void)
{
	DDRC |= (1 << 3);
	PORTC &= (0 << 3);
	float lon = 0.0, lat = 0.0, height = 0.0;
	bool hasFix = true;

	DDRB |= (1<<5);
	PORTB |= (1<<5);
	init_uart_stdout();
	uint8_t tmp;
	//rscs_uart_read(uart1, &tmp, 1);

	DDRB |= (1 << 4);
	PORTB |= (1 << 4);

	rscs_gps_t * gps = rscs_gps_init(RSCS_UART_ID_UART0);

	while(1)
	{
		int error = rscs_gps_read(gps, &lon, &lat, &height, &hasFix);
		printf("gps_data %f, %f, %f, %d, error = %d\n", lon, lat, height, hasFix, error);

		/*
		int code = 231; //Why? Why not?!
		code = ads1115_test();
		printf("ADS1115: test complete, exit code %d\n", code);

		/*code = adxl345_test();
		printf("ADXL345: test complete, exit code %d\n", code);*/

		/*
		code = adc_internal_test();
		printf("ADC: test complete, exit code %d\n", code);*/

		/*code = bmp280_spi_test();
		printf("BMP280: test complete, exit code %d\n", code);*/

		/*code = bmp180_i2c_test();
		printf("test_complete with code: %d\n", code);*/

		//printf(" %f , %f , %f \n", lon , lat , height);
		//rscs_uart_write(uart1, "A", 1);
		_delay_ms(100);
	}

	return 0;
}





