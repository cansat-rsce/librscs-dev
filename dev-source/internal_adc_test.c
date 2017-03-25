/*
 * internal_adc_test.c
 *
 *  Created on: 22 марта 2017 г.
 *      Author: developer
 */
#include <stdio.h>

#include "rscs/adc.h"
#include "rscs/error.h"


//#define OPR(OP) retcode = OP; printf("ADC: OPR: retcode: %d", )if(retcode != RSCS_E_NONE) goto end;
#define OPR(operation) \
	if ((retcode = operation) != RSCS_E_NONE) \
	{ \
		printf("error at %s: %d\n", #operation, retcode); \
		goto end; \
	}

rscs_e adc_internal_test(void) {
	rscs_e retcode = 0;
	int32_t result;

	rscs_adc_init();

	while(1) {
		for(int i = 0; i < 10; i++) {
			//printf("ADC: trying single conversion - %d of 10\n", (i+1));
			//printf("ADC: starting conversion\n");
			OPR(rscs_adc_start_single_conversion(RSCS_ADC_SINGLE_0))
			//printf("ADC: waiting result\n");
			rscs_adc_wait_result();
			//printf("ADC: getting result\n");
			OPR(rscs_adc_get_result(&result))
			printf("ADC: result is %d\n", (int)result);
		}

		//printf("ADC: trying multiple conversion\n");
		//printf("ADC: starting conversion\n");
		OPR(rscs_adc_start_continuous_conversion(RSCS_ADC_SINGLE_0))
		for(int i = 0; i < 10; i++) {
			//printf("ADC: waiting result - %d of 10\n", (i+1));
			rscs_adc_wait_result();
			//printf("ADC: getting result\n");
			OPR(rscs_adc_get_result(&result))
			printf("ADC: result is %d\n", (int)result);
		}
		rscs_adc_stop_continuous_conversion();
		rscs_adc_wait_result();
	}

end:
	return retcode;
}
