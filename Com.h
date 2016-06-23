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

typedef enum {
    /*协议头帧*/
    com_head_frame = 0x3a,
    /*协议尾帧*/
    com_tail_frame = 0x0a,
    /*协议长度*/
    com_size = 8,
}com_parameter;

typedef struct com{
    /*数据缓存*/
    u8 data[com_size];
    /*协议完成标志*/
    u8 rs_ok;
    /*协议状态字节*/
    u8 rs_flag;
}com_data;

/**********************************************函数定义***************************************************** 
* 函数名称: void ComInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
void ComInit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void ComSend(u8 cmd, u8 dat1,u8 dat2,u8 dat3) 
* 输入参数: u8 cmd, u8 dat1,u8 dat2,u8 dat3 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
void ComSend(u8 cmd, u8 dat1,u8 dat2,u8 dat3);
/**********************************************函数定义***************************************************** 
* 函数名称: u8 ComGetFlag(void) 
* 输入参数: void 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
u8 ComGetFlag(void);
/**********************************************函数定义***************************************************** 
* 函数名称: u8 ComGetDate(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
u8 ComGetDate(u8 cmd);

#endif



