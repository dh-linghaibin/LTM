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
#include "Moto.h"

/*����������*/
static moto moto_one;
/**********************************************��������***************************************************** 
* ��������: void MotoInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/21
************************************************************************************************************/ 
void MotoInit(void) { 
    /*ʹ�� �ߵ�ƽ ʹ��*/  
    PA_DDR_DDR1 = 1;
    PA_CR1_C11 = 1;
    PA_CR2_C21 = 0;
    /*������� �ߵ�ƽ��ת*/  
    PA_DDR_DDR2 = 1;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 0;
    /*����*/  
    PA_DDR_DDR3 = 1;
    PA_CR1_C13 = 1;
    PA_CR2_C23 = 0;
    /*��ʱ����ʼ��*/
    TIM4_IER = 0x00;       
    TIM4_EGR = 0x01;
    TIM4_PSCR = 0x01;// ������ʱ��=��ʱ��/128=16MHZ/128
    TIM4_ARR = 0x10;// �趨��װ��ʱ�ļĴ���ֵ��255�����ֵ
    //TIM4_CNTR = 0x00;// �趨�������ĳ�ֵ
    // ��ʱ����=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//   
    TIM4_CR1 = 0x01;  
    
    /*�رյ��*/
    MOTO_ENABLE = dir_story;
    /*���ò����������*/
    moto_one.direction = dir_story;
    MOTO_DIRECTION = moto_one.direction;
    /*��ʼ������ٶ�*/
    moto_one.sleep = moto_start_sleep;
    /*��ʼ����Ҫ�ߵĲ���*/
    moto_one.setp = moto_all_setp;
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    INTOFF
    static u16 pulse_count = 0;
    /*����жϱ�־*/
    TIM4_SR = 0x00;
    /*�ۼӼ���*/
    pulse_count++;
    /*�ж�����*/
    if(pulse_count > moto_one.sleep) {
        static u8 dir = 0;
        pulse_count = 0;
        /*��������*/
        if(dir == 0) {
            dir = 1;
            MOTO_PULSE = 0;
        } else {
            dir = 0;
            MOTO_PULSE = 1;
        }
        moto_one.all_setp_s++;
        /*�ж��ǲ��ǿ�������*/
        if(moto_one.all_setp_s > 100) {
            moto_one.all_setp_s = 0;
            moto_one.all_setp++;
            if(moto_one.all_setp > 13730) {
                /*��ʼ����*/
                if(moto_one.sleep < 30) {
                    moto_one.sleep++;
                }
            }
            if(moto_one.all_setp > 13800) {
                moto_one.all_setp = 0;
                /*�رյ��*/
                MOTO_ENABLE = 0;
                /*���ò����������*/
                moto_one.direction = ~moto_one.direction;
                MOTO_DIRECTION = moto_one.direction;
                /*���ò���������ٶ�*/
                moto_one.sleep = 30;
                /*�򿪵��*/
                MOTO_ENABLE = 1;
            }
        }
        if(moto_one.setp > 0) {
            /*���Զ���*/
            //moto_one.setp--;
            moto_one.sleep_count++;
            if(moto_one.sleep_count > 200) {
                moto_one.sleep_count = 0;
                /*����*/
                if(moto_one.sleep > 4) {
                    moto_one.sleep--;
                }
            }
        } else {
            /*�����Ѿ�����*/
        }
    }
    INTEN
    return;
}
