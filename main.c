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
#include "Sys.h"
#include "Moto.h"
#include "Com.h"
#include "Features.h"
#include "Test.h"

int main( void ) {
    /*ϵͳʱ�ӳ�ʼ��*/
    SysInit();
    /*���������ʼ��*/
    MotoInit();
    /*���ڳ�ʼ��*/
    ComInit();
    /*���Գ����ʼ��*/
    TestInit();
    /*����ȫ���ж�*/
    INTEN
    while(1) {
        /*�����߳�*/
        FeaturesHandle();
        /*���λ�ü��*/
        MotoReadLimit();
        /*������������*/
        TestReadBu();
    }
}
