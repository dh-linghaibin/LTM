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
#include "Com.h"
/**********************************************函数定义***************************************************** 
* 函数名称: void ComInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
void ComInit(void) { 
    PD_DDR &= ~BIT(6);//TX
    PD_CR1 |= BIT(6); 
    PD_CR2 &= ~BIT(6);

    PD_DDR |= BIT(5);//RX
    PD_CR1 |= BIT(5); 
    PD_CR2 |= BIT(5);

    UART1_CR1=0x00;
    UART1_CR2=0x00;
    UART1_CR3=0x00; 
    UART1_BRR2=0x02;//02 0a
    UART1_BRR1=0x68;//68 08
    UART1_CR2=0x2c;//允许接收，发送，开接收中断
}


#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{
    u8 data;
    data = UART1_DR;
    /*等待数据接受完成*/
    while((UART1_SR & 0x80) == 0x00);

    return;
}


