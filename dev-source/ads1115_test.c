/*
 * ads1115_test.c
 *
 *  Created on: 01 апр. 2017 г.
 *      Author: developer
 */
#include "rscs/ads1115.h"
#include <stdio.h>
#include <util/delay.h>

#define OPR(OP) retcode = OP; if(retcode != RSCS_E_NONE) goto end;

rscs_e ads1115_test() {
	rscs_i2c_init();
	rscs_e retcode = RSCS_E_NONE;
	rscs_ads1115_t * ads = rscs_ads1115_init(RSCS_ADS1115_ADDR_GND);
	printf("ADS1115: changing range\n");
	OPR(rscs_ads1115_set_range(ads, RSCS_ADS1115_RANGE_6DOT144))
	printf("ADS1115: changing rate\n");
	OPR(rscs_ads1115_set_datarate(ads, RSCS_ADS1115_DATARATE_860SPS))
	printf("ADS1115: changing channel\n");
	printf("ADS1115: starting continuous\n");
	OPR(rscs_ads1115_start_continuous(ads, RSCS_ADS1115_CHANNEL_0))


	int16_t result;

	while(1){
		printf("ADS1115: reading\n");
		OPR(rscs_ads1115_read(ads, &result))
		printf("ADS1115: result %x   %f\n", result, result * 0.1875);
		/*printf("ADS1115: starting single\n");
		OPR(rscs_ads1115_start_single(ads))*/
		_delay_ms(100);
		/*printf("ADS1115: waiting result\n");
		OPR(rscs_ads1115_wait_result(ads))*/
	}

end:
	rscs_ads1115_deinit(ads);
	return retcode;

}
