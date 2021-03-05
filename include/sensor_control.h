#ifndef __SENSOR_CONTROL_H__
#define __SENSOR_CONTROL_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"


typedef struct {
    UCHAR_T Temp_current;
    UINT16_T Humidity_current;
}APP_REPORT_DATA_T;

VOID app_device_init(VOID);

OPERATE_RET app_get_all_sensor_data(VOID);

#endif