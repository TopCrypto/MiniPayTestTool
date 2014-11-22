#include "StdAfx.h"
#include "TestItem.h"

static DWORD Device_Lcd_Clear()
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalCommandLen = 0;
	USHORT usLocalResLen = 0;
	
	usLocalCommandLen = sizeof(DEVICE_LCD_CLR) - 1;
	memcpy(ucLocalCommand,(UCHAR*)DEVICE_LCD_CLR,usLocalCommandLen);

	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}
	return dwResult;

}

static DWORD Device_Display_Msg(unsigned char *pucMsg)
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalCommandLen = 0;
	USHORT usLocalResLen = 0;
	//dwResult = Device_Lcd_Clear();
	usLocalCommandLen = strlen((const char *)pucMsg);
	memcpy(ucLocalCommand,(UCHAR*)DEVICE_DIS_MSG,sizeof(DEVICE_DIS_MSG) - 1);
	memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,pucMsg,usLocalCommandLen);	
	ucLocalCommand[9] = (unsigned char )usLocalCommandLen;
	usLocalCommandLen += sizeof(DEVICE_DIS_MSG) - 1;

	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);
	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}
	return dwResult;

}

static DWORD Device_GetKey()
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalCommandLen = 0;
	USHORT usLocalResLen = 0;

	usLocalCommandLen = sizeof(DEVICE_GET_KEY) - 1;
	memcpy(ucLocalCommand,(UCHAR*)DEVICE_GET_KEY,sizeof(DEVICE_GET_KEY) - 1);
	
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		|| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}
	else
	{
		//memcpy(ucResult,ucLocalRes,usLocalResLen - 2); 
		//*usResultLen = usLocalResLen - 2;
	}

	return dwResult;

}



static DWORD Device_Led_Red_Operator(UCHAR ucType,UCHAR *ucTime)
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;	
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalResLen = 0;
	switch(ucType)
	{
	case DEVICE_P2_LED_250MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_RED_FLASH_250MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_500MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_RED_FLASH_500MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_ON:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_RED_ON,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_OFF:
		dwResult = SCard_ApduExchang((UCHAR*)DEVICE_COMMAND_LED_RED_OFF,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	default:
		dwResult = DEVICE_ERROR_ERROR;
		break;
	}

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}

	return dwResult;

}

static DWORD Device_Led_Blue_Operator(UCHAR ucType,UCHAR *ucTime)
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalResLen = 0;
	switch(ucType)
	{
	case DEVICE_P2_LED_250MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_BLUE_FLASH_250MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_500MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_BLUE_FLASH_500MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_ON:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_BLUE_ON,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_OFF:
		dwResult = SCard_ApduExchang((UCHAR*)DEVICE_COMMAND_LED_BLUE_OFF,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	default:
		dwResult = DEVICE_ERROR_ERROR;
		break;
	}

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}

	return dwResult;

}

static DWORD Device_Led_Green_Operator(UCHAR ucType,UCHAR *ucTime)
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;	
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalResLen = 0;
	switch(ucType)
	{
	case DEVICE_P2_LED_250MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_GREEN_FLASH_250MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_500MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_GREEN_FLASH_500MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_ON:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_GREEN_ON,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_OFF:
		dwResult = SCard_ApduExchang((UCHAR*)DEVICE_COMMAND_LED_GREEN_OFF,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	default:
		dwResult = DEVICE_ERROR_ERROR;
		break;
	}

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}

	return dwResult;

}

static DWORD Device_Led_Yellow_Operator(UCHAR ucType,UCHAR *ucTime)
{
	DWORD dwResult = DEVICE_ERROR_SUCCESS;	
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalResLen = 0;
	switch(ucType)
	{
	case DEVICE_P2_LED_250MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_YELLOW_FLASH_250MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_500MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_YELLOW_FLASH_500MS,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_ON:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_LED_YELLOW_ON,DEVICE_COMMAND_LED_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_LED_DATA_POS,ucTime,DEVICE_COMMAND_LED_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_LED_OFF:
		dwResult = SCard_ApduExchang((UCHAR*)DEVICE_COMMAND_LED_YELLOW_OFF,DEVICE_COMMAND_LED_LEN,ucLocalRes,&usLocalResLen);
		break;
	default:
		dwResult = DEVICE_ERROR_ERROR;
		break;
	}

	if ((0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		dwResult = DEVICE_ERROR_ERROR;
	}

	return dwResult;

}


static UCHAR Device_Led_Operator(UCHAR ucColor,UCHAR ucFlashType,UCHAR *ucTime)
{
	UCHAR ucResult = DEVICE_ERROR_SUCCESS;
	DWORD dwRet = 0;
	UCHAR ucLocalRes[512] = {0};
	USHORT usLocalResLen = 0;
	switch(ucColor)
	{
	case DEVICE_P1_LED_GREEN:
		dwRet = Device_Led_Green_Operator(ucFlashType,ucTime);
		break;
	case DEVICE_P1_LED_BLUE:
		dwRet = Device_Led_Blue_Operator(ucFlashType,ucTime);
		break;
	case DEVICE_P1_LED_RED:
		dwRet = Device_Led_Red_Operator(ucFlashType,ucTime);
		break;
	case DEVICE_P1_LED_YELLOW:
		dwRet = Device_Led_Yellow_Operator(ucFlashType,ucTime);
		break;
	default:	
		ucResult = DEVICE_ERROR_ERROR;
		break;
	}

	if ((DEVICE_ERROR_SUCCESS != dwRet) 
		| (0x00 == usLocalResLen)
		| (0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		ucResult = DEVICE_ERROR_ERROR;
	}

	return ucResult;
}

static UCHAR Device_Buzzer_Operator(UCHAR ucType,UCHAR *ucTime)
{
	UCHAR ucResult = DEVICE_ERROR_SUCCESS;
	DWORD dwResult = 0;
	UCHAR ucLocalRes[512] = {0};
	UCHAR ucLocalCommand[128] = {0};
	USHORT usLocalResLen = 0;

	switch(ucType)
	{
	case DEVICE_P2_BUZZER_250MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_BUZZER_250MS,DEVICE_COMMAND_BUZZER_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_BUZZER_DATA_POS,ucTime,DEVICE_COMMAND_BUZZER_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_BUZZER_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_BUZZER_500MS:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_BUZZER_250MS,DEVICE_COMMAND_BUZZER_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_BUZZER_DATA_POS,ucTime,DEVICE_COMMAND_BUZZER_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_BUZZER_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_BUZZER_ON:
		memcpy(ucLocalCommand,(UCHAR*)DEVICE_COMMAND_BUZZER_ON,DEVICE_COMMAND_BUZZER_LEN);
		memcpy(ucLocalCommand + DEVICE_COMMAND_BUZZER_DATA_POS,ucTime,DEVICE_COMMAND_BUZZER_DATA_LEN);
		dwResult = SCard_ApduExchang(ucLocalCommand,DEVICE_COMMAND_BUZZER_LEN,ucLocalRes,&usLocalResLen);
		break;
	case DEVICE_P2_BUZZER_OFF:
		dwResult = SCard_ApduExchang((UCHAR*)DEVICE_COMMAND_BUZZER_OFF,DEVICE_COMMAND_BUZZER_LEN,ucLocalRes,&usLocalResLen);
		break;
	default:	
		ucResult = DEVICE_ERROR_ERROR;
		break;
	}
	if ((DEVICE_ERROR_SUCCESS != dwResult) 
		| (0x00 == usLocalResLen)
		| (0x90 != ucLocalRes[usLocalResLen - 2]) 
		| (0x00 != ucLocalRes[usLocalResLen - 1]))
	{
		ucResult = DEVICE_ERROR_ERROR;
	}
	return ucResult;

}

///////////////////////////////////////////////////////////////////////////////////////////////
// 迷你付二代测试CMC增加
static UCHAR Device_USB()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;
	
	usLocalCommandLen = sizeof(DEVICE_USB) - 1;
	memcpy(ucLocalCommand,DEVICE_USB,usLocalCommandLen);
	ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}
	
	return ucResult;
	
	return ucResult;


}


static UCHAR Device_SPI()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_SPI_WRITE_INDEX0) - 1;
	memcpy(ucLocalCommand,DEVICE_SPI_WRITE_INDEX0,usLocalCommandLen);
	ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		usLocalCommandLen = sizeof(DEVICE_SPI_READ_INDEX0) - 1;
		memcpy(ucLocalCommand,DEVICE_SPI_READ_INDEX0,usLocalCommandLen);
        ucLocalCommand[4] = usLocalCommandLen - 5;
		dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);
		if ((DEVICE_ERROR_SUCCESS == dwResult) 
			& (0x90 == ucLocalRes[usLocalResLen - 2]) 
			& (0x00 == ucLocalRes[usLocalResLen - 1]))
		{
			ucResult = DEVICE_ERROR_SUCCESS;
		}
	}

	return ucResult;
}

static UCHAR Device_RTC()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	UCHAR ucFirstTime[6] = {0};
	DWORD dwResult = 0;
	int i = 0;
	int j = 0;
	int k = 0;

	usLocalCommandLen = sizeof(DEVICE_RTC_WRITE) - 1;
	memcpy(ucLocalCommand,DEVICE_RTC_WRITE,usLocalCommandLen);
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{
		usLocalCommandLen = sizeof(DEVICE_RTC_READ) - 1;
		memcpy(ucLocalCommand,DEVICE_RTC_READ,usLocalCommandLen);
		dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);
		if ((DEVICE_ERROR_SUCCESS == dwResult) 
			& (0x90 == ucLocalRes[usLocalResLen - 2]) 
			& (0x00 == ucLocalRes[usLocalResLen - 1]))
		{
			memcpy(ucFirstTime,ucLocalRes,usLocalResLen - 2);

			/*for (i = 0; i<10000; i++)
				for (j = 0; j < 10000; j++)
					for (k = 0; k < 6 ; )
						k++;*/
			Sleep(1000);

			usLocalCommandLen = sizeof(DEVICE_RTC_READ) - 1;
			memcpy(ucLocalCommand,DEVICE_RTC_READ,usLocalCommandLen);
			dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);
			if ((DEVICE_ERROR_SUCCESS == dwResult) 
				& (0x90 == ucLocalRes[usLocalResLen - 2]) 
				& (0x00 == ucLocalRes[usLocalResLen - 1]))
			{
				if ((memcmp(ucLocalRes,ucFirstTime,usLocalResLen - 2)) > 0)
				{
					ucResult = DEVICE_ERROR_SUCCESS;
				}
				
			}
		}
	}

	return ucResult;
}

static UCHAR Device_SAM()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_SAM_ON) - 1;
	memcpy(ucLocalCommand,DEVICE_SAM_ON,usLocalCommandLen);
	ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}



static UCHAR Device_Buzzer()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;
	
	usLocalCommandLen = sizeof(DEVICE_Buzzer_ON) - 1;
	memcpy(ucLocalCommand,DEVICE_Buzzer_ON,usLocalCommandLen);
	ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);
	
	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}
	
	return ucResult;
}

static UCHAR Device_LcdBlack()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[512] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_LCD_BACK) - 1;
	memcpy(ucLocalCommand,DEVICE_LCD_BACK,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{			
		ucResult = DEVICE_ERROR_SUCCESS;		
	}

	return ucResult;
}

static UCHAR Device_LcdWhite()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[512] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_LCD_WHITE) - 1;
	memcpy(ucLocalCommand,DEVICE_LCD_WHITE,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}


static UCHAR Device_LcdBackLightOn()
{	
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_LCD_BLACKLIGHT_ON) - 1;
	memcpy(ucLocalCommand,DEVICE_LCD_BLACKLIGHT_ON,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}


static UCHAR Device_LcdBackLightOff()
{	
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_LCD_BLACKLIGHT_OFF) - 1;
	memcpy(ucLocalCommand,DEVICE_LCD_BLACKLIGHT_OFF,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}


static UCHAR Device_KeyBoard()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_KEY_BOARD) - 1;
	memcpy(ucLocalCommand,DEVICE_KEY_BOARD,usLocalCommandLen);

     ucLocalCommand[4] = usLocalCommandLen - 5;

	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
	return 0;
}

static UCHAR Device_ICC()
{	
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_ICC_ON) - 1;
	memcpy(ucLocalCommand,DEVICE_ICC_ON,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}

static UCHAR Device_PICC()
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;
	UCHAR ucLocalRes[256] = {0};
	USHORT usLocalResLen = 0;
	UCHAR ucLocalCommand[256] = {0};
	USHORT usLocalCommandLen = 0;
	DWORD dwResult = 0;

	usLocalCommandLen = sizeof(DEVICE_PICC_ON) - 1;
	memcpy(ucLocalCommand,DEVICE_PICC_ON,usLocalCommandLen);
	 ucLocalCommand[4] = usLocalCommandLen - 5;
	dwResult = SCard_ApduExchang(ucLocalCommand,usLocalCommandLen,ucLocalRes,&usLocalResLen);

	if ((DEVICE_ERROR_SUCCESS == dwResult) 
		& (0x90 == ucLocalRes[usLocalResLen - 2]) 
		& (0x00 == ucLocalRes[usLocalResLen - 1]))
	{		
		ucResult = DEVICE_ERROR_SUCCESS;
	}

	return ucResult;
}

static  UCHAR Device_GetMediaStatus(UCHAR *pOutData)
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;		
	UCHAR ucCommandBuffer[256];
	USHORT usCommandLen = 0;
	USHORT usRespondeLen = 256;
	UCHAR  ucRespondBuffer[256];	
	USHORT usMsgLen = 0;
	memcpy(&ucCommandBuffer,DEVICE_GETCARDSTATUS,sizeof(DEVICE_GETCARDSTATUS) - 1);
	usCommandLen = sizeof(DEVICE_GETCARDSTATUS) - 1 ;
	 ucCommandBuffer[4] = usCommandLen - 5;
	if (DEVICE_ERROR_SUCCESS == SCard_ApduExchang((UCHAR *)ucCommandBuffer,usCommandLen,(UCHAR *)ucRespondBuffer,&usRespondeLen))
	{	
		if ((0x90 == ucRespondBuffer[usRespondeLen - 2]) & (0x00 == ucRespondBuffer[usRespondeLen - 1]))
			{
				ucResult = DEVICE_ERROR_SUCCESS ;	//Card power on Ok
				*pOutData = ucRespondBuffer[0];
			}
	}
	return ucResult;	
}
static UCHAR Device_GetVersion(/*UCHAR *pOutData*/)
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;		
	UCHAR ucCommandBuffer[256];
	USHORT usCommandLen = 0;
	USHORT usRespondeLen = 256;
	UCHAR  ucRespondBuffer[256];	
	USHORT usMsgLen = 0;
	memcpy(&ucCommandBuffer,DEVICE_GETDEVVERTION,sizeof(DEVICE_GETDEVVERTION) - 1);
	usCommandLen = sizeof(DEVICE_GETDEVVERTION) - 1 ;
	if (DEVICE_ERROR_SUCCESS == SCard_ApduExchang((UCHAR *)ucCommandBuffer,usCommandLen,(UCHAR *)ucRespondBuffer,&usRespondeLen))
	{	
		if ((0x90 == ucRespondBuffer[usRespondeLen - 2]) & (0x00 == ucRespondBuffer[usRespondeLen - 1]))
		{
			ucResult = DEVICE_ERROR_SUCCESS ;	//Card power on Ok
			//	*pOutData = ucRespondBuffer[0];
		}
	}
	return ucResult;
}


static UCHAR Device_CheckPICC(/*UCHAR *pOutData*/)
{
	UCHAR ucResult = DEVICE_ERROR_ERROR;		
	UCHAR ucCommandBuffer[256];
	USHORT usCommandLen = 0;
	USHORT usRespondeLen = 256;
	UCHAR  ucRespondBuffer[256];	
	USHORT usMsgLen = 0;
	memcpy(&ucCommandBuffer,DEVICE_PICC_ON,sizeof(DEVICE_PICC_ON) - 1);
	usCommandLen = sizeof(DEVICE_PICC_ON) - 1 ;
	ucCommandBuffer[4] = usCommandLen - 5;
	if (DEVICE_ERROR_SUCCESS == SCard_ApduExchang((UCHAR *)ucCommandBuffer,usCommandLen,(UCHAR *)ucRespondBuffer,&usRespondeLen))
	{	
		if ((0x90 == ucRespondBuffer[usRespondeLen - 2]) & (0x00 == ucRespondBuffer[usRespondeLen - 1]))
		{
			ucResult = DEVICE_ERROR_SUCCESS ;	//Card power on Ok
			//	*pOutData = ucRespondBuffer[0];
		}
	}
	return ucResult;
}

BOOL TEST_USB(CString& str)
{
   BOOL bResult = FALSE;
   UCHAR ucRet = RESP_ERR;
   
   ucRet = Device_USB();
   if(ucRet != RESP_OK)
   {
	  str = "注意：USB接口测试失败";
	  bResult = FALSE;

   }else
   {
      str = "USB接口测试成功！！！";
	  bResult = TRUE;
   }

	return bResult;
}


BOOL TEST_SPI(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	ucRet = Device_SPI();
	if(ucRet != RESP_OK)
	{
		str = "注意：SPI FLASH接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "SPI FLASH接口测试成功！！！";
		bResult = TRUE;
	}
   	return bResult;
}

BOOL TEST_SAM(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	ucRet = Device_SAM();
	if(ucRet != RESP_OK)
	{
		str = "注意：SAM接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "SAM接口测试成功！！！";
		bResult = TRUE;
	}
	return bResult;
}

BOOL TEST_BUZZER(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	Device_Display_Msg((unsigned char *)"蜂鸣器有响，请按【确认】键，否则按【取消】键");
	ucRet = Device_Buzzer();
	
	if(ucRet != RESP_OK)
	{
		str = "注意：蜂鸣器接口测试失败";
		bResult = FALSE;
		return bResult;
	}

	ucRet = (UCHAR)Device_GetKey();
	if(ucRet != RESP_OK)
	{
		str = "注意：蜂鸣器接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "蜂鸣器接口测试成功！！！";
		bResult = TRUE;
	}
	return bResult;
}

BOOL TEST_LCDLevel(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	ucRet = Device_LcdBlack();
	if(ucRet != RESP_OK)
	{
	  str = "注意：LCD对比度接口测试失败";
      bResult = FALSE;
	  return bResult;
	}

     ucRet = (UCHAR)Device_GetKey();
	if(ucRet != RESP_OK)
	{
		str = "注意：LCD对比度接口测试失败";
		bResult = FALSE;
		return bResult;
	}
	else
	{
		ucRet = Device_LcdWhite();
		if(ucRet != RESP_OK)
		{
			str = "注意：LCD对比度接口测试失败";
			bResult = FALSE;
			return bResult;
		}

		ucRet = (UCHAR)Device_GetKey();
	}

	if(ucRet != RESP_OK)
	{
		str = "注意：LCD对比度接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "LCD对比度接口测试成功！！！";
		bResult = TRUE;
	}
	return bResult;
}

BOOL TEST_LCDBackLight(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	Device_Display_Msg((unsigned char *)"液晶屏的背光灯点亮，请按【确认】键，否则按【取消】键！");
	ucRet = Device_LcdBackLightOn();
	if(ucRet != RESP_OK)
	{
		str = "注意：LCD背光接口测试失败";
		bResult = FALSE;
		return bResult;
	}

	ucRet = (UCHAR)Device_GetKey();
	if(ucRet != RESP_OK)
	{
		str = "注意：LCD背光接口测试失败";
		bResult = FALSE;
		return bResult;
	}
	else
	{
		Device_Display_Msg((unsigned char *)"液晶屏的背光灯关闭，请按【确认】键，否则按【取消】键！");
		ucRet = Device_LcdBackLightOff();
		if(ucRet != RESP_OK)
		{
			str = "注意：LCD背光接口测试失败";
			bResult = FALSE;
			return bResult;
		}
 
		ucRet = (UCHAR)Device_GetKey();
	}

		if(ucRet != RESP_OK)
		{
			str = "注意：LCD背光接口测试失败";
			bResult = FALSE;

		}else
		{
			str = "LCD背光接口测试成功！！！";
			bResult = TRUE;
		}
	return bResult;
}

BOOL TEST_KeyBoard(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;

	ucRet = Device_KeyBoard();
	if(ucRet != RESP_OK)
	{
		str = "注意：按键接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "按键接口测试成功！！！";
		bResult = TRUE;
	}
	return bResult;
}

BOOL TEST_ICC(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;
	int  i = 0;

	Device_Display_Msg((unsigned char *)"请插入接触式卡片,按任意键确认");
    ucRet = (UCHAR) Device_GetKey();
    Device_Display_Msg((unsigned char *)"...");

	DWORD dwStart = GetTickCount();
	DWORD dwEnd   = dwStart;

    do 
    {
		dwEnd = GetTickCount()-dwStart;
        ucRet = Device_ICC();
        if(ucRet != RESP_OK)
		{
		   i = 0;
		}

        if(i ==3)
		{
			break;
		}

    } while (dwEnd < 8000);

	if(ucRet != RESP_OK)
	{
		str = "注意：ICC接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "ICC 接口测试成功！！！";
		bResult = TRUE;
	}
	return bResult;
}

BOOL CheckPICC()
{
  BOOL bResult = FALSE;
  UCHAR ucRet = RESP_ERR;
  ucRet = Device_PICC();
  if(ucRet != RESP_OK)
  {
	  bResult = FALSE;

  }else
  {
	  bResult = TRUE;
  }

  return bResult;
}





BOOL TEST_PICC(CString& str)
{
	BOOL bResult = FALSE;
	UCHAR ucRet = RESP_ERR;
    int i = 0;

	Device_Display_Msg((unsigned char *)"请挥非接触卡后,按任意键确认");
    ucRet = (UCHAR)Device_GetKey();
	Device_Display_Msg((unsigned char *)"...");

	DWORD dwStart = GetTickCount();
	DWORD dwEnd   = dwStart;

	do 
	{
        i++;
		dwEnd = GetTickCount()-dwStart;
		ucRet = Device_PICC();
		if(ucRet != RESP_OK)
		{
		   i = 0;
		}

		if(i == 3)
		{
			break;
		}


	} while (dwEnd <= 8000);

	if(ucRet != RESP_OK)
	{
		str = "注意：PICC接口测试失败";
		bResult = FALSE;

	}else
	{
		str = "PICC接口测试成功！！！";
		bResult = TRUE;
	}

	return bResult;
}