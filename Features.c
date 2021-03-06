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
#include "Features.h"
#include "Com.h"
#include "Moto.h"
/**********************************************函数定义***************************************************** 
* 函数名称: void FeaturesInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
void FeaturesInit(void) { 
    
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FeaturesHandle(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: void  
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
void FeaturesHandle(void) {
    /*处理串口命令*/
    if(ComGetFlag() == 0x01) {
        ComSetFlag(0x00);
        if(ComCheck() == 0x01) {
            switch(ComGetDate(1)) {
                /*打开盒子*/
                case 0x01:
                    ComSend(0x80,0x01,0x00,0x00);
                    MotoSet(dir_story);
                    break;
                /*关闭盒子*/
                case 0x02:
                    ComSend(0x80,0x02,0x00,0x00);
                    MotoSet(dir_reversion);
                    break;
                /*复位盒子*/
                case 0x03:
                    ComSend(0x80,0x03,0x00,0x00);
                    MotoSet(dir_story);
                    break;
                case 0x04:break;
                default:break;
            }   
        } else {
            /*检验失败*/
            ComSend(0x44,0x00,0x00,0x00);
        }
    }
} 

