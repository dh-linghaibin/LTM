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
* ������ڣ�2016/6/22
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Features.h"
#include "Com.h"
#include "Moto.h"
/**********************************************��������***************************************************** 
* ��������: void FeaturesInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
void FeaturesInit(void) { 
    
}
/**********************************************��������***************************************************** 
* ��������: void FeaturesHandle(void) 
* �������: void 
* ���ز���: void  
* ��    ��: void  
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
void FeaturesHandle(void) {
    /*����������*/
    if(ComGetFlag() == 0x01) {
        ComSetFlag(0x00);
        if(ComCheck() == 0x01) {
            switch(ComGetDate(1)) {
                /*�򿪺���*/
                case 0x01:
                    ComSend(0x80,0x01,0x00,0x00);
                    MotoSet(dir_story);
                    break;
                /*�رպ���*/
                case 0x02:
                    ComSend(0x80,0x02,0x00,0x00);
                    MotoSet(dir_reversion);
                    break;
                /*��λ����*/
                case 0x03:
                    ComSend(0x80,0x03,0x00,0x00);
                    MotoSet(dir_story);
                    break;
                case 0x04:break;
                default:break;
            }   
        } else {
            /*����ʧ��*/
            ComSend(0x44,0x00,0x00,0x00);
        }
    }
} 

