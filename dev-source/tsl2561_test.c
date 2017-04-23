#include <stdio.h>

#include <util/delay.h>
#include <avr/interrupt.h>

#include "rscs/uart.h"
#include "rscs/i2c.h"
#include "rscs/tsl2561.h"
#include "rscs/spi.h"
#include "rscs/stdext/stdio.h"

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

	rscs_tsl2561_t * s1 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_LOW);
	rscs_tsl2561_t * s2 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_FLOATING);
	rscs_tsl2561_t * s3 = rscs_tsl2561_init(RSCS_TSL2561_ADDR_HIGH);

	rscs_e error1, error2, error3;

	error1 = rscs_tsl2561_setup(s1);
	error2 = rscs_tsl2561_setup(s2);
	error3 = rscs_tsl2561_setup(s3);

	while(1)
	{

		printf("error1 = %d\n", error1);
		printf("error2 = %d\n", error2);
		printf("error3 = %d\n", error3);

		error1 = rscs_tsl2561_read(s1, &sensor_data0, &sensor_data1);
		uint16_t lux1 = rscs_tsl2561_get_lux(s1, RSCS_TSL2561_GAIN_1X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);
		printf("lux1 = %d\n", lux1);

		error2 = rscs_tsl2561_read(s2, &sensor_data0, &sensor_data1);
		uint16_t lux2 = rscs_tsl2561_get_lux(s2, RSCS_TSL2561_GAIN_1X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);
		printf("lux2 = %d\n", lux2);

		error3 = rscs_tsl2561_read(s3, &sensor_data0, &sensor_data1);
		uint16_t lux3 = rscs_tsl2561_get_lux(s3, RSCS_TSL2561_GAIN_1X, RSCS_TSL2561_TYPE_CS, RSCS_TSL2561_INT_402MS, sensor_data0, sensor_data1);
		printf("lux3 = %d\n", lux3);

		_delay_ms(500);
	}

	return 0;
}





