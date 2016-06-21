
#include "Timer.h"

void TimerInit(void) {
    TIM4_IER = 0x00;//       
    TIM4_EGR = 0x01;// 
    TIM4_PSCR = 0x07;// 计数器时钟=主时钟/128=16MHZ/128
    TIM4_ARR = 0xFA;// 设定重装载时的寄存器值，255是最大值
    //TIM4_CNTR = 0x00;// 设定计数器的初值
    // 定时周期=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//   
    TIM4_CR1 = 0x01;  
}




