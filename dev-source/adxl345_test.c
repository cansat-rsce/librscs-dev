/*
 * adxl345_test.c
 *
 *  Created on: 25 марта 2017 г.
 *      Author: developer
 */
#include "util/delay.h"
#include "stdio.h"

#include "rscs/error.h"

#include "rscs/adxl345.h"

#define OPR(OP) retcode = OP; if(retcode != RSCS_E_NONE) goto end;

rscs_e adxl345_test(void) {
	rscs_e retcode = RSCS_E_NONE;

	rscs_adxl345_t * adxl = rscs_adxl345_init(RSCS_ADXL345_SPI, RSCS_ADXL345_ADDR_MAIN, &DDRB, &PORTB, 0);

	_delay_ms(1);

	int16_t x = 0, y = 0, z = 0;
	uint8_t devid = 0;

	while(1) {
		OPR(rscs_adxl345_read(adxl, &x, &y, &z))
		printf("ADXL345: data: %d  %d  %d\n", x, y, z);
		_delay_ms(1);
	}

end:
	return retcode;
}

