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

#ifndef __APP_SENSOR_H__
#define __APP_SENSOR_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"
#include "tuya_cloud_com_defs.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/***********************************************************
*************************variable define********************
***********************************************************/
typedef enum{
    APP_SENSOR_NORMAL,
    APP_SENSOR_PRODTEST
}APP_SENSOR_MODE;

#define DPID_TEMP_CURRENT            1
#define DPID_HUMIDITY_CURRENT        2


OPERATE_RET app_sensor_init(IN APP_SENSOR_MODE mode);

VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root);
VOID app_report_all_dp_status(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __LIHGT_INIT_H__ */