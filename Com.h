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
#ifndef __COM_H
#define __COM_H

#include "Type.h"

typedef struct com{
    /*���ݻ���*/
    u8 data[8];
    /*Э����ɱ�־*/
    u8 rs_ok;
    /**/
}comdata;

#endif



