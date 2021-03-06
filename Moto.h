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
* 完成日期：2016/6/21
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/

#ifndef __MOTO_H
#define __MOTO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "Type.h"

typedef enum
{
    /*电机正转*/
    dir_story = 1,
    /*电机反转*/
    dir_reversion = 0,
    /*电机打开*/
    moto_open = 1,
    /*关闭电机*/
    moto_cloose = 0,
    /*电机一次最多的步数 13800*/
    moto_all_setp = 1000,
    /*电机起步速度*/
    moto_start_sleep = 18,
    /*电机最高速度*/
    moto_end_sleep = 3,
    /*电机加速时间*/
    moto_add_time = 100,
}moto_parameter;     

/*步进电机参数*/
typedef struct moto{
    /*需要走的布数*/
    u16 setp;
    /*需要走的速度*/
    u8 sleep;
    /*加减速计数位*/
    u16 sleep_count;
    /*一共需要走的步数*/
    u8 all_setp_s;
    u16 all_setp;
    /*电机方向*/
    u8 direction;
    /*电机所在的位置*/
    u8 position;
}moto;

/*电机 使能*/
#define MOTO_ENABLE     PA_ODR_ODR1
/*电机 方向*/
#define MOTO_DIRECTION  PA_ODR_ODR2
/*电机 脉冲*/
#define MOTO_PULSE      PA_ODR_ODR3
/*到位 开关*/
#define MOTO_LIMIT      PC_IDR_IDR3
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/21
************************************************************************************************************/ 
void MotoInit(void);     
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoReadLimit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void MotoReadLimit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoSet(u8 diection) 
* 输入参数: u8 diection 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void MotoSet(moto_parameter diection);

#ifdef __cplusplus
}
#endif

#endif


