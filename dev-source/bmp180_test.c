#include "rscs/i2c.h"

#include <stdio.h>

// выполнение операции и проверка её результата.
// если результат операции не корректен - об этом будет написано сообщение в stdout
// и будет осуществлен переход на метку `end`
#define CHECK_REPORT_ERROR(operation) \
	if ((error = operation) != RSCS_E_NONE) \
	{ \
		printf("error at %s: %d\n", #operation, error); \
		goto end; \
	}



int bmp180_i2c_test(void)
{
	rscs_e error;
	const uint8_t bmp180_addr = 0b1110111; 		// адрес bmp180
	const uint8_t bmp180_cal_data_addr = 0xAA;	// адрес конфигурационных регистов

	rscs_i2c_init();


	CHECK_REPORT_ERROR(rscs_i2c_start());
	CHECK_REPORT_ERROR(rscs_i2c_send_slaw(bmp180_addr, rscs_i2c_slaw_write));

	struct
	{
		int16_t ac1;
		int16_t ac2;
		int16_t ac3;
		uint16_t ac4;
		uint16_t ac5;
		uint16_t ac6;
		int16_t b1;
		int16_t b2;
		int16_t mb;
		int16_t mc;
		int16_t md;
	} calib_data;
	memset(&calib_data, 0x00, sizeof(calib_data));

	CHECK_REPORT_ERROR(rscs_i2c_write_byte(bmp180_cal_data_addr));
	CHECK_REPORT_ERROR(rscs_i2c_start());
	CHECK_REPORT_ERROR(rscs_i2c_send_slaw(bmp180_addr, rscs_i2c_slaw_read));
	CHECK_REPORT_ERROR(rscs_i2c_read(&calib_data, sizeof(calib_data), true));

	printf("calib_data:\n"
			"ac1 = %d\n"
			"ac2 = %d\n"
			"ac3 = %d\n"
			"ac4 = %d\n"
			"ac5 = %ud\n"
			"ac6 = %ud\n"
			"b1 = %d\n"
			"b2 = %d\n"
			"mb = %d\n"
			"mc = %d\n"
			"md = %d\n",
			calib_data.ac1, calib_data.ac2, calib_data.ac3, calib_data.ac4, calib_data.ac5, calib_data.ac6,
			calib_data.b1, calib_data.b2, calib_data.mb, calib_data.mc, calib_data.md);

	rscs_i2c_stop();

end:
	rscs_i2c_stop();
	return error;
}
