/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/6/21
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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

/*��� ʹ��*/
#define MOTO_ENABLE     PA_ODR_ODR1
/*��� ����*/
#define MOTO_DIRECTION  PA_ODR_ODR2
/*��� ����*/
#define MOTO_PULSE      PA_ODR_ODR3

/**********************************************��������***************************************************** 
* ��������: void MotoInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/21
************************************************************************************************************/ 
void MotoInit(void);     

#ifdef __cplusplus
}
#endif

#endif


