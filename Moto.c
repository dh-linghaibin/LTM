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
#include "Moto.h"

/*定义电机参数*/
static moto moto_one;
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/21
************************************************************************************************************/ 
void MotoInit(void) { 
    /*使能 高电平 使能*/  
    PA_DDR_DDR1 = 1;
    PA_CR1_C11 = 1;
    PA_CR2_C21 = 0;
    /*电机方向 高电平正转*/  
    PA_DDR_DDR2 = 1;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 0;
    /*脉冲*/  
    PA_DDR_DDR3 = 1;
    PA_CR1_C13 = 1;
    PA_CR2_C23 = 0;
    /*定时器初始化*/
    TIM4_IER = 0x00;       
    TIM4_EGR = 0x01;
    TIM4_PSCR = 0x01;// 计数器时钟=主时钟/128=16MHZ/128
    TIM4_ARR = 0x3b;// 设定重装载时的寄存器值，255是最大值
    //TIM4_CNTR = 0x00;// 设定计数器的初值
    // 定时周期=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//   
    TIM4_CR1 = 0x01;  
    
    /*关闭电机*/
    MOTO_ENABLE = 1;
    MOTO_DIRECTION = 0;
    /*初始化电机速度*/
    moto_one.sleep = 20;
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    INTOFF
    static u16 pulse_count = 0;
    /*清除中断标志*/
    TIM4_SR = 0x00;
    /*累加计数*/
    pulse_count++;
    /*判断周期*/
    if(pulse_count > moto_one.sleep) {
        static u8 dir = 0;
        pulse_count = 0;
        /*产生脉冲*/
        if(dir == 0) {
            dir = 1;
            MOTO_PULSE = 0;
        } else {
            dir = 0;
            MOTO_PULSE = 1;
        }
        if(moto_one.setp > 0) {
            moto_one.setp--;
        }
    }
    INTEN
    return;
}
