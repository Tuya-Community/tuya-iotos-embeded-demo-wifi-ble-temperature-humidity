/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: light_init.h
 * @Description: light init process include file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-21 11:30:03
 * @LastEditTime: 2020-12-21 11:30:03
 */

#include "app_sensor.h"
#include "sensor_control.h"
#include "uni_time_queue.h"
#include "sys_timer.h"
#include "tuya_iot_wifi_api.h"
#include "FreeRTOS.h"
#include "uni_thread.h"
#include "queue.h"

extern APP_REPORT_DATA_T app_report_data;

STATIC VOID sensor_data_get_theard(PVOID_T pArg);
STATIC VOID sensor_data_deal_theard(PVOID_T pArg);
STATIC VOID sensor_data_report_theard(PVOID_T pArg);


OPERATE_RET app_sensor_init(IN APP_SENSOR_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;


    if(APP_SENSOR_NORMAL == mode) {
        app_device_init();
        tuya_hal_system_sleep(1000);

        tuya_hal_thread_create(NULL, "thread_data_get", 512, TRD_PRIO_4, sensor_data_get_theard, NULL);

        tuya_hal_thread_create(NULL, "thread_data_report", 512, TRD_PRIO_4, sensor_data_report_theard, NULL);
        
    }else {

    }

    return OPRT_OK;
}

STATIC VOID sensor_data_get_theard(PVOID_T pArg)
{   
    OPERATE_RET op_ret = OPRT_OK;
    while(1) {
        tuya_hal_system_sleep(1000);
        PR_ERR("app_get_all_sensor_data");
        
        op_ret = app_get_all_sensor_data();
        if(OPRT_OK != op_ret) {
            PR_ERR("app_get_all_sensor_data fail,err_num:%d",op_ret);
        }
    }
}

STATIC VOID sensor_data_deal_theard(PVOID_T pArg)
{   
    while(1) {
        tuya_hal_system_sleep(1000);
        
    }
}

STATIC VOID sensor_data_report_theard(PVOID_T pArg)
{   
    while(1) {
        tuya_hal_system_sleep(5000);
        app_report_all_dp_status();
    }

}

VOID app_report_all_dp_status(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 2;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = DPID_TEMP_CURRENT;
    dp_arr[0].type = PROP_VALUE;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = app_report_data.Temp_current;

    dp_arr[1].dpid = DPID_HUMIDITY_CURRENT;
    dp_arr[1].type = PROP_VALUE;
    dp_arr[1].time_stamp = 0;
    dp_arr[1].value.dp_value = app_report_data.Humidity_current;
    
    op_ret = dev_report_dp_json_async(NULL,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    return;
}


VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);

    return;

}