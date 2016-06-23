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
    /*限位开关*/
    PC_DDR_DDR3 = 0;
    PC_CR1_C13 = 0;
    PC_CR2_C23 = 0;
    /*定时器初始化*/
    TIM4_IER = 0x00;       
    TIM4_EGR = 0x01;
    TIM4_PSCR = 0x01;// 计数器时钟=主时钟/128=16MHZ/128
    TIM4_ARR = 0x30;// 设定重装载时的寄存器值，255是最大值 0x10
    //TIM4_CNTR = 0x00;// 设定计数器的初值
    // 定时周期=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//  
    /*关闭电机 0x01 打开*/
    TIM4_CR1 = 0x00;  
    
    /*关闭电机*/
    MOTO_ENABLE = moto_cloose;
    /*设置步进电机方向*/
    moto_one.direction = dir_story;
    MOTO_DIRECTION = moto_one.direction;
    /*初始化电机速度*/
    moto_one.sleep = moto_start_sleep;
    /*初始化需要走的步数*/
    moto_one.setp = 0x00;
    /*开机运行关门*/
    MotoSet(dir_story);
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoReadLimit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void MotoReadLimit(void) {
    /*只有关门的时候才有限位*/
    if(moto_one.direction == dir_story) {
        if(MOTO_LIMIT == 0) {
            moto_one.all_setp = 0;
            /*关闭电机*/
            MOTO_ENABLE = moto_cloose;
            /*设置步进电机起步速度*/
            moto_one.sleep = moto_start_sleep;
            /*关闭电机*/
            TIM4_CR1 = 0x00;  
            /*设置电机位置*/
            moto_one.position = dir_story;
            /*结束*/
            moto_one.setp = 0x00;
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MotoSet(u8 diection) 
* 输入参数: u8 diection 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void MotoSet(moto_parameter diection) {
    if(moto_one.setp == 0x00) {//在运行的时候不能操作
        /*是否在需要到达的位置*/
        if(diection == moto_one.position) {
            
        } else {
            if(diection == dir_story) {
                /*设置步进电机方向*/
                moto_one.direction = dir_story;
            } else {
                /*设置步进电机方向*/
                moto_one.direction = dir_reversion;
            }
            /*打开电机*/
            MOTO_ENABLE = moto_open;
            /*设置步进电机方向*/
            MOTO_DIRECTION = moto_one.direction;
            /*初始化电机速度*/
            moto_one.sleep = moto_start_sleep;
            /*保存电机方向*/
            moto_one.position = moto_one.direction;
            /*打开电机*/
            TIM4_CR1 = 0x01;  
            /*开始*/
            moto_one.setp = 0x01;
        }
    }
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
    if(pulse_count > moto_one.sleep) {
         /*判断周期*/
        static u8 dir = 0;
        pulse_count = 0;
        /*产生脉冲*/
        dir = ~dir;
        MOTO_PULSE = dir;
        /*统计已走步数*/
        moto_one.all_setp_s++;
        /*判断是不是快走完了*/
        if(moto_one.all_setp_s > moto_add_time) {
            moto_one.all_setp_s = 0;
            /*每100步累加一次*/
            moto_one.all_setp++;
            /*加速阶段*/
            if(moto_one.all_setp < (moto_start_sleep-moto_end_sleep) ) {
                if(moto_one.sleep > moto_end_sleep) {
                    /*需要加速*/
                    //moto_one.sleep_count++;
                   // if(moto_one.sleep_count > 2) {
                      //  moto_one.sleep_count = 0;
                        /*加速*/
                        moto_one.sleep--;
                    //}
                }  
            }
             /*减速阶段*/
            else if( (moto_one.all_setp > (moto_all_setp-20)) 
                    && (moto_one.all_setp < moto_all_setp) ){
                /*开始减速*/
                if(moto_one.sleep < moto_start_sleep) {
                    moto_one.sleep++;
                }
            }
            /*停止 走完全程*/
            else if(moto_one.all_setp > moto_all_setp) {
                moto_one.all_setp = 0;
                /*关闭电机*/
                MOTO_ENABLE = moto_cloose;
                /*设置步进电机方向*/
                //moto_one.direction = ~moto_one.direction;
                //MOTO_DIRECTION = moto_one.direction;
                /*设置步进电机起步速度*/
                moto_one.sleep = moto_start_sleep;
                /*打开电机*/
                //MOTO_ENABLE = moto_open;
                /*关闭电机*/
                TIM4_CR1 = 0x00; 
                /*结束*/
                moto_one.setp = 0x00;
            } else {
                
            }
        }
    }
    INTEN
    return;
}
