/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/6/22
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#ifndef __COM_H
#define __COM_H

#include "Type.h"

typedef struct com{
    /*数据缓存*/
    u8 data[8];
    /*协议完成标志*/
    u8 rs_ok;
    /**/
}comdata;

#endif



