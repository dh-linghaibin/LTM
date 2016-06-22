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
    /*�����ת*/
    dir_story = 1,
    /*�����ת*/
    dir_reversion = 0,
    /*�����*/
    moto_open = 1,
    /*�رյ��*/
    moto_cloose = 0,
    /*����γ�*/
    moto_all_setp = 13800,
    /*������ٶ�*/
    moto_start_sleep = 20,
}moto_parameter;     

/*�����������*/
typedef struct moto{
    /*��Ҫ�ߵĲ���*/
    u16 setp;
    /*��Ҫ�ߵ��ٶ�*/
    u8 sleep;
    /*�Ӽ��ټ���λ*/
    u16 sleep_count;
    /*һ����Ҫ�ߵĲ���*/
    u8 all_setp_s;
    u16 all_setp;
    /*�������*/
    u8 direction;
}moto;

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


