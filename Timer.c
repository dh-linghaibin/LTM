
#include "Timer.h"

void TimerInit(void) {
    TIM4_IER = 0x00;//       
    TIM4_EGR = 0x01;// 
    TIM4_PSCR = 0x07;// ������ʱ��=��ʱ��/128=16MHZ/128
    TIM4_ARR = 0xFA;// �趨��װ��ʱ�ļĴ���ֵ��255�����ֵ
    //TIM4_CNTR = 0x00;// �趨�������ĳ�ֵ
    // ��ʱ����=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//   
    TIM4_CR1 = 0x01;  
}




