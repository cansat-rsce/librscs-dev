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
#include "rscs/i2c.h"

#define OPR(OP) retcode = OP; if(retcode != RSCS_E_NONE) goto end;

rscs_e adxl345_test(void) {
	rscs_e retcode = RSCS_E_NONE;

	rscs_i2c_init();
	rscs_adxl345_t * adxl = rscs_adxl345_initi2c(RSCS_ADXL345_ADDR_ALT);

	_delay_ms(1);

	int16_t x = 0, y = 0, z = 0;
	float x_g, y_g, z_g;
	uint8_t devid = 0;

	while(1) {
		//OPR(rscs_adxl345_read(adxl, &x, &y, &z))
		//OPR(rscs_adxl345_getRegisterValue(adxl, 0, &devid))
		//printf("ADXL345: data: %d  %d  %d\n", x, y, z);
		//printf("ADXL345: devid: %d\n", devid);
		rscs_adxl345_GetGXYZ(adxl, &x, &y, &z, &x_g, &y_g, &z_g);
		printf("%g  %g  %g; %d  %d  %d\n", x_g, y_g, z_g, x, y, z);
		_delay_ms(1);
	}

end:
	return retcode;
}

