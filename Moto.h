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
    LTK_LED0 = 0,
    LTK_LED1 = 1,
    LTK_LED2 = 2,
    LTK_INVALID_LED
}ltk_led_t;     

/*电机 使能*/
#define MOTO_ENABLE     PA_ODR_ODR1
/*电机 方向*/
#define MOTO_DIRECTION  PA_ODR_ODR2
/*电机 脉冲*/
#define MOTO_PULSE      PA_ODR_ODR3

/**********************************************函数定义***************************************************** 
* 函数名称: void MotoInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/21
************************************************************************************************************/ 
void MotoInit(void);     

#ifdef __cplusplus
}
#endif

#endif


