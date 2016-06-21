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
#include "Sys.h"
#include "Moto.h"


int main( void ) {
    /*系统时钟初始化*/
    SysInit();
    /*步进电机初始化*/
    MotoInit();
    /*开启全局中断*/
    INTEN
    while(1) {
        
    }
}
