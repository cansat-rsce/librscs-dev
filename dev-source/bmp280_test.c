/*
 * bmp280_test.c
 *
 *  Created on: 04 марта 2017 г.
 *      Author: developer
 */
#include <stdio.h>
#include <util/delay.h>

#include "rscs/bmp280.h"

#define OPR(OP) retcode = OP; if(retcode != RSCS_E_NONE) goto end;

int bmp280_spi_test(void){
	int retcode = 0;

	rscs_bmp280_descriptor_t * bmp = rscs_bmp280_init();
	rscs_bmp280_parameters_t params = {	.pressure_oversampling = RSCS_BMP280_OVERSAMPLING_X16,
										.temperature_oversampling = RSCS_BMP280_OVERSAMPLING_X2,
										.standbytyme = RSCS_BMP280_STANDBYTIME_62DOT5MS,
										.filter = RSCS_BMP280_FILTER_X16};
	printf("BMP280: trying to setup\n");
	OPR(rscs_bmp280_setup(bmp, &params);)
	printf("BMP280: trying to changemode\n");
	OPR(rscs_bmp280_changemode(bmp, RSCS_BMP280_MODE_NORMAL);)

	int32_t rawpress = 0;
	int32_t rawtemp = 0;

	_delay_ms(2000);

	int32_t press = 2000000;
	int32_t temperature = 2000000;

	const rscs_bmp280_calibration_values_t * calvals = rscs_bmp280_get_calibration_values(bmp);

	while(1) {
		printf("BMP280: status: %d\n", rscs_bmp280_read_status(bmp));
		printf("BMP280: trying to read\n");
		OPR(rscs_bmp280_read(bmp, &rawpress, &rawtemp);)
		printf("BMP280: rawpress %lx, rawtemp %lx\n", rawpress, rawtemp);
		rscs_bmp280_calculate(calvals, rawpress, rawtemp, &press, &temperature);
		printf("Pressure: %ld, temperature %ld\n", press, temperature);
		_delay_ms(900);
	}

end:
	rscs_bmp280_deinit(bmp);
	return retcode;
}
