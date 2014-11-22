#ifndef _TESTITEM_H
#define _TESTITEM_H

//#include "TypeDef.h"
#include "PCSC.h"

#define  RESP_OK  0x00
#define  RESP_ERR 0x01


/***********************************************************************/
#define DEVICE_ERROR_SUCCESS		0x00
#define DEVICE_ERROR_ERROR			0x01

/*********************************************************************/
//#define DEVICE_CLA					0xF0
//#define DEVICE_CLA					0xFF
/*********************************************************************/
//#define DEVICE_INS_LED				0xB0
//#define DEVICE_INS_BUZZER			0xB1
/*********************************************************************/
#define DEVICE_P1_LED_GREEN			0x00
#define DEVICE_P1_LED_BLUE			0x01
#define DEVICE_P1_LED_YELLOW		0x02
#define DEVICE_P1_LED_RED			0x03

#define DEVICE_P1_BUZZER			0x00
/*********************************************************************/
#define DEVICE_P2_LED_250MS			0x00
#define DEVICE_P2_LED_500MS			0x01
#define DEVICE_P2_LED_ON			0x02
#define DEVICE_P2_LED_OFF			0x03

#define DEVICE_P2_BUZZER_250MS		0x00
#define DEVICE_P2_BUZZER_500MS		0x01
#define DEVICE_P2_BUZZER_ON			0x02
#define DEVICE_P2_BUZZER_OFF		0x03
/*********************************************************************/
//Led Command
#define DEVICE_COMMAND_LED_LEN					0x09
#define DEVICE_COMMAND_LED_DATA_POS				0x0A
#define DEVICE_COMMAND_LED_DATA_LEN				0x09

#define DEVICE_COMMAND_LED_GREEN_FLASH_250MS	"\xF0\xB0\x00\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_GREEN_FLASH_500MS	"\xF0\xB0\x00\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_GREEN_ON				"\xF0\xB0\x00\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_GREEN_OFF			"\xF0\xB0\x00\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_BLUE_FLASH_250MS		"\xF0\xB0\x01\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_BLUE_FLASH_500MS		"\xF0\xB0\x01\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_BLUE_ON				"\xF0\xB0\x01\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_BLUE_OFF				"\xF0\xB0\x01\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_YELLOW_FLASH_250MS	"\xF0\xB0\x02\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_YELLOW_FLASH_500MS	"\xF0\xB0\x02\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_YELLOW_ON			"\xF0\xB0\x02\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_YELLOW_OFF			"\xF0\xB0\x02\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_RED_FLASH_250MS		"\xF0\xB0\x03\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_RED_FLASH_500MS		"\xF0\xB0\x03\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_RED_ON				"\xF0\xB0\x03\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_RED_OFF				"\xF0\xB0\x03\x03\x04\x00\x00\x00\x00"

/*
#define DEVICE_COMMAND_LED_GREEN_FLASH_250MS	"\xFF\xB0\x00\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_GREEN_FLASH_500MS	"\xFF\xB0\x00\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_GREEN_ON				"\xFF\xB0\x00\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_GREEN_OFF			"\xFF\xB0\x00\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_BLUE_FLASH_250MS		"\xFF\xB0\x01\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_BLUE_FLASH_500MS		"\xFF\xB0\x01\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_BLUE_ON				"\xFF\xB0\x01\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_BLUE_OFF				"\xFF\xB0\x01\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_YELLOW_FLASH_250MS	"\xFF\xB0\x02\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_YELLOW_FLASH_500MS	"\xFF\xB0\x02\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_YELLOW_ON			"\xFF\xB0\x02\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_YELLOW_OFF			"\xFF\xB0\x02\x03\x04\x00\x00\x00\x00"

#define DEVICE_COMMAND_LED_RED_FLASH_250MS		"\xFF\xB0\x03\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_RED_FLASH_500MS		"\xFF\xB0\x03\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_LED_RED_ON				"\xFF\xB0\x03\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_LED_RED_OFF				"\xFF\xB0\x03\x03\x04\x00\x00\x00\x00"
*/
/*********************************************************************/		
//Buzzer Command
#define DEVICE_COMMAND_BUZZER_LEN					0x09
#define DEVICE_COMMAND_BUZZER_DATA_POS				0x05
#define DEVICE_COMMAND_BUZZER_DATA_LEN				0x04

#define DEVICE_COMMAND_BUZZER_250MS			     "\xFF\x70\x25\x7B\x00\xFE\x70\x01\x04"
#define DEVICE_COMMAND_BUZZER_500MS				"\xF0\xB1\x00\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_BUZZER_ON				"\xF0\xB1\x00\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_BUZZER_OFF				"\xF0\xB1\x00\x03\x04\x00\x00\x00\x00"
/*
#define DEVICE_COMMAND_BUZZER_250MS			    "\xFF\xB1\x00\x00\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_BUZZER_500MS				"\xFF\xB1\x00\x01\x04\x00\x00\x00\x00"
#define DEVICE_COMMAND_BUZZER_ON				"\xFF\xB1\x00\x02\x04\x00\x00\x00\x00"		
#define DEVICE_COMMAND_BUZZER_OFF				"\xFF\xB1\x00\x03\x04\x00\x00\x00\x00"*/
/*********************************************************************/
#define DEVICE_USB                               "\xFF\x70\x25\x7B\x00\xFE\x70\x00\x00\x00"
#define DEVICE_SPI_WRITE_INDEX0			     	 "\xFF\x70\x25\x7B\x00\xFE\x70\x08\x00\x00\xFF\x23\x00\x00\x04\xBB\xBB\xBB\xBB"
#define DEVICE_SPI_READ_INDEX0					 "\xFF\x70\x25\x7B\x00\xFE\x70\x08\x00\x00\xFF\x24\x00\x00\x04"
#define DEVICE_SAM_ON							"\xFF\x70\x25\x7B\x00\xFE\x70\x06\x00\x00"
#define DEVICE_Buzzer_ON                        "\xFF\x70\x25\x7B\x00\xFE\x70\x01\x04\x00"

#define DEVICE_LCD_BACK							"\xFF\x70\x25\x7B\x00\xFE\x70\x02\x00\x00"            //LCD黑白显示测试全黑屏
#define DEVICE_LCD_WHITE					 	"\xFF\x70\x25\x7B\x00\xFE\x70\x02\x01\x00"  
#define DEVICE_LCD_BLACKLIGHT_ON				"\xFF\x70\x25\x7B\x00\xFE\x70\x03\x01\x00"            //LCD背光测试 01背光开
#define DEVICE_LCD_BLACKLIGHT_OFF				"\xFF\x70\x25\x7B\x00\xFE\x70\x03\x00\x00"            //00 背光关

#define DEVICE_KEY_BOARD					     "\xFF\x70\x25\x7B\x00\xFE\x70\x07\x00\x00"

#define DEVICE_ICC_ON						     "\xFF\x70\x25\x7B\x00\xFE\x70\x05\x00\x00" 
#define DEVICE_PICC_ON					       	"\xFF\x70\x25\x7B\x00\xFE\x70\x04\x00\x00"     
#define DEVICE_RTC_WRITE						"\xFF\x09\x00\x00\x06\x12\x11\x15\x09\x38\x50"
#define DEVICE_RTC_READ							"\xFF\x08\x00\x00\x06"

#define DEVICE_DIS_MSG						     "\xFF\x70\x25\x7B\x00\xFE\x70\x0A\x01\x00"  //LCD显示字符信息
#define DEVICE_GET_KEY							 "\xFF\x70\x25\x7B\x00\xFE\x70\x09\x00\x00" 
//#define DEVICE_GET_KEY							"\xFF\x48\x00\x00\x00"
#define DEVICE_LCD_CLR							"\xFF\x1D\x00\x00\x00"    //LCD清除指令

#define DEVICE_GETCARDSTATUS				    "\xFF\x70\x25\x7B\x00\xFE\x70\x00\x00\x00"
#define DEVICE_GETDEVVERTION					"\xF0\x02\x01\x01\x00"

#define DEVICE_KEY_VALUE_OK						0x0D
#define DEVICE_KEY_VALUE_CANCEL					0x18

#define DEVICE_ICC_CARD_EXIT					0x00
#define DEVICE_PICC_CARD_EXIT					0x08


extern  BOOL TEST_USB(CString& str);
extern	BOOL TEST_SPI(CString& str);
extern  BOOL TEST_SAM(CString& str);
extern	BOOL TEST_BUZZER(CString& str);
extern	BOOL TEST_LCDLevel(CString& str);
extern	BOOL TEST_LCDBackLight(CString& str);
extern	BOOL TEST_KeyBoard(CString& str);
extern	BOOL TEST_ICC(CString& str);
extern	BOOL TEST_PICC(CString& str);
extern  BOOL CheckPICC();

#endif
