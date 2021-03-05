/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: sht21.h
 * @Description: SHT21 IIC drive src file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-16 18:51:29
 * @LastEditTime: 20120-12-16 18:51:29
 */

#include "sensor_control.h"
#include "sht21.h"
#include "tuya_gpio.h"

/***********************************************************
*************************types define***********************
***********************************************************/
typedef enum
{
    LOW = 0,
    HIGH,
}default_level;

typedef struct {
    float temperature;
    float humidity;
}DEVICE_DATA_T;

DEVICE_DATA_T device_data = {0};

APP_REPORT_DATA_T app_report_data = {0};

/***********************************************************
*************************IO control device define***********
***********************************************************/
#define IIC_SDA_PORT                     (14)
#define IIC_SCL_PORT                     (24)

/***********************************************************
*************************about adc init*********************
***********************************************************/



/***********************************************************
*************************about iic init*********************
***********************************************************/
STATIC sht21_init_t sht21_int_param = {IIC_SDA_PORT, IIC_SCL_PORT, SHT2x_RES_10_13BIT};


/***********************************************************
*************************function***************************
***********************************************************/

STATIC VOID __ctrl_gpio_init(CONST TY_GPIO_PORT_E port, CONST BOOL_T high)
{
    tuya_gpio_inout_set(port, FALSE);
    tuya_gpio_write(port, high);
}

VOID app_device_init(VOID)
{
    INT_T op_ret = 0;
    
    // SHT21 IIC driver init 
    tuya_sht21_init(&sht21_int_param);  

}



OPERATE_RET app_get_all_sensor_data(VOID)
{
    OPERATE_RET ret = 0;

    SHORT_T hum;
    SHORT_T temp;

    hum = tuya_sht21_measure(HUMIDITY);
    device_data.humidity = tuya_sht21_cal_RH(hum);

    if(device_data.humidity > 0) {
        app_report_data.Humidity_current = (UCHAR_T)device_data.humidity;
        PR_NOTICE("humidity = %d",app_report_data.Humidity_current);
    }

    temp = tuya_sht21_measure(TEMP);
    device_data.temperature = tuya_sht21_cal_temperature(temp);
    device_data.temperature = 10*device_data.temperature;
    app_report_data.Temp_current = (UINT16_T)device_data.temperature;
    PR_NOTICE("tempre = %d",app_report_data.Temp_current);
    
    return ret;
}
