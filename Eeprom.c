
#include "Eeprom.h"

void EeepromInit(void) {
    FLASH_CR1 = 0X00;
	FLASH_CR2 = 0X00;
	FLASH_NCR2 = 0XFF;
	FLASH_DUKR = 0XAE;
	FLASH_DUKR = 0X56;
	while(!(FLASH_IAPSR&0X08));
}


void EepromWrite(u8 addr,u8 dat) {
	volatile u8 *p;
    FLASH_DUKR=0xAE;                // д���һ����Կ
    FLASH_DUKR=0x56;                // д��ڶ�����Կ	
    while((FLASH_IAPSR&0x04));
	p = (u8 *)(0x4000+addr);
	*p = dat;
	while(!(FLASH_IAPSR&0X40));
    FLASH_IAPSR&=0xF7;              //����д����
}
/***************************************
Function: Eeprom_Read
Function: Read variable corresponding to the address saved
Input: Address
Output: None
Explanation:
***************************************/
u8 EepromRead(u8 addr) {
	volatile u8 *p;
	p = (u8 *)(0x4000+addr);
	return *p;
}


void Write_Option_Byte(void) {   
    unsigned char opt[6] = {0,0,0,0,0,0};
    /*����Flash*/
    do {
        FLASH_DUKR = 0xAE;
        FLASH_DUKR = 0x56;      
    } while(!(FLASH_IAPSR & 0X08));
    /*��ѡ���ֽڽ���д����ʹ��*/
    FLASH_CR2 = 0X80;
    /*�������ƼĴ���*/
    FLASH_NCR2 = 0X7F;
    /*д����,0x02:PD2��0x00:PA3*/
//    *((unsigned char *)0x4800) = opt[0];
//
//    *((unsigned char *)0x4801) = opt[1];
//    *((unsigned char *)0x4802) = ~opt[1];
//
    *((unsigned char *)0x4803) = 0x01;//opt[2];
//    *((unsigned char *)0x4804) = ~opt[2];
//
//    *((unsigned char *)0x4805) = opt[3];
//    *((unsigned char *)0x4806) = ~opt[3];
//
//    *((unsigned char *)0x4807) = opt[4];
//    *((unsigned char *)0x4808) = ~opt[0];
//
//    *((unsigned char *)0x4809) = opt[5];
//    *((unsigned char *)0x480A) = ~opt[5];  
    /*�ȴ�д����*/
    while(!(FLASH_IAPSR & 0x04));
}

