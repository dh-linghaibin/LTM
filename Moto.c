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
    /*��λ����*/
    PC_DDR_DDR3 = 0;
    PC_CR1_C13 = 0;
    PC_CR2_C23 = 0;
    /*��ʱ����ʼ��*/
    TIM4_IER = 0x00;       
    TIM4_EGR = 0x01;
    TIM4_PSCR = 0x01;// ������ʱ��=��ʱ��/128=16MHZ/128
    TIM4_ARR = 0x30;// �趨��װ��ʱ�ļĴ���ֵ��255�����ֵ 0x10
    //TIM4_CNTR = 0x00;// �趨�������ĳ�ֵ
    // ��ʱ����=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//  
    /*�رյ�� 0x01 ��*/
    TIM4_CR1 = 0x00;  
    
    /*�رյ��*/
    MOTO_ENABLE = moto_cloose;
    /*���ò����������*/
    moto_one.direction = dir_story;
    MOTO_DIRECTION = moto_one.direction;
    /*��ʼ������ٶ�*/
    moto_one.sleep = moto_start_sleep;
    /*��ʼ����Ҫ�ߵĲ���*/
    moto_one.setp = 0x00;
    /*�������й���*/
    MotoSet(dir_story);
}
/**********************************************��������***************************************************** 
* ��������: void MotoReadLimit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
void MotoReadLimit(void) {
    /*ֻ�й��ŵ�ʱ�������λ*/
    if(moto_one.direction == dir_story) {
        if(MOTO_LIMIT == 0) {
            moto_one.all_setp = 0;
            /*�رյ��*/
            MOTO_ENABLE = moto_cloose;
            /*���ò���������ٶ�*/
            moto_one.sleep = moto_start_sleep;
            /*�رյ��*/
            TIM4_CR1 = 0x00;  
            /*���õ��λ��*/
            moto_one.position = dir_story;
            /*����*/
            moto_one.setp = 0x00;
        }
    }
}
/**********************************************��������***************************************************** 
* ��������: void MotoSet(u8 diection) 
* �������: u8 diection 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
void MotoSet(moto_parameter diection) {
    if(moto_one.setp == 0x00) {//�����е�ʱ���ܲ���
        /*�Ƿ�����Ҫ�����λ��*/
        if(diection == moto_one.position) {
            
        } else {
            if(diection == dir_story) {
                /*���ò����������*/
                moto_one.direction = dir_story;
            } else {
                /*���ò����������*/
                moto_one.direction = dir_reversion;
            }
            /*�򿪵��*/
            MOTO_ENABLE = moto_open;
            /*���ò����������*/
            MOTO_DIRECTION = moto_one.direction;
            /*��ʼ������ٶ�*/
            moto_one.sleep = moto_start_sleep;
            /*����������*/
            moto_one.position = moto_one.direction;
            /*�򿪵��*/
            TIM4_CR1 = 0x01;  
            /*��ʼ*/
            moto_one.setp = 0x01;
        }
    }
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
    if(pulse_count > moto_one.sleep) {
         /*�ж�����*/
        static u8 dir = 0;
        pulse_count = 0;
        /*��������*/
        dir = ~dir;
        MOTO_PULSE = dir;
        /*ͳ�����߲���*/
        moto_one.all_setp_s++;
        /*�ж��ǲ��ǿ�������*/
        if(moto_one.all_setp_s > moto_add_time) {
            moto_one.all_setp_s = 0;
            /*ÿ100���ۼ�һ��*/
            moto_one.all_setp++;
            /*���ٽ׶�*/
            if(moto_one.all_setp < (moto_start_sleep-moto_end_sleep) ) {
                if(moto_one.sleep > moto_end_sleep) {
                    /*��Ҫ����*/
                    //moto_one.sleep_count++;
                   // if(moto_one.sleep_count > 2) {
                      //  moto_one.sleep_count = 0;
                        /*����*/
                        moto_one.sleep--;
                    //}
                }  
            }
             /*���ٽ׶�*/
            else if( (moto_one.all_setp > (moto_all_setp-20)) 
                    && (moto_one.all_setp < moto_all_setp) ){
                /*��ʼ����*/
                if(moto_one.sleep < moto_start_sleep) {
                    moto_one.sleep++;
                }
            }
            /*ֹͣ ����ȫ��*/
            else if(moto_one.all_setp > moto_all_setp) {
                moto_one.all_setp = 0;
                /*�رյ��*/
                MOTO_ENABLE = moto_cloose;
                /*���ò����������*/
                //moto_one.direction = ~moto_one.direction;
                //MOTO_DIRECTION = moto_one.direction;
                /*���ò���������ٶ�*/
                moto_one.sleep = moto_start_sleep;
                /*�򿪵��*/
                //MOTO_ENABLE = moto_open;
                /*�رյ��*/
                TIM4_CR1 = 0x00; 
                /*����*/
                moto_one.setp = 0x00;
            } else {
                
            }
        }
    }
    INTEN
    return;
}
