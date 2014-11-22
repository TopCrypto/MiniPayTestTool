#include "stdafx.h"

#include <Winscard.h>
#include "SmartCard.h"
#pragma comment(lib, "Winscard.lib")


SCARD_READERSTATE ReaderState;
SCARDCONTEXT g_sc;
char ReaderName[20][50];


//DWORD UpdateDevice(char *pReaderName) 
DWORD UpdateDevice() 
{
	// TODO: Add your control notification handler code here
	DWORD		lReturn = 0;
	LPTSTR		pmszReaders = NULL, pReader=NULL;
	DWORD		cch = SCARD_AUTOALLOCATE;
	unsigned short i = 0,j = 0;
	//String		str;
	unsigned char   readercount = 0;	


	memset(ReaderName,0x00,sizeof(ReaderName));
	lReturn = SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&g_sc);

	lReturn=SCardListReaders(g_sc, NULL, (LPTSTR)&pmszReaders, &cch);


	if (SCARD_S_SUCCESS == lReturn)
	{
		readercount=0x00;
		memset(ReaderName,0x00,sizeof(ReaderName));
		pReader = pmszReaders;
		while ( '\0' != *pReader )
		{
			//str.Format("%s",pReader);			
			memcpy(ReaderName[readercount], pReader, strlen(pReader));	//save reader names 
			// Advance to the next value.
			readercount++;
			pReader = pReader +  strlen(pReader) + 1;
		}
		lReturn = SCardFreeMemory( g_sc,pmszReaders );
		if (SCARD_S_SUCCESS != lReturn)
		{

		}
	}
	return lReturn;

}


DWORD LCardConnectCard(LPCTSTR  pbReaderName,SCARDHANDLE *hScard,
					   DWORD *pdwActiveProtocol,SCARDCONTEXT *phContext,
					   BYTE *bATR)
{

	DWORD dwRet = SCARD_S_SUCCESS;
	DWORD usLen = 64;
	unsigned char ucATR[32] = {0};//DWORD dwAP;
	// Establish the context.
	dwRet = SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&g_sc);
	if ( dwRet != SCARD_S_SUCCESS  )
	{
		return dwRet;
	}

	//Connect Card
	dwRet = SCardDisconnect(*hScard,SCARD_RESET_CARD);
	dwRet = SCardConnect(g_sc, (LPCSTR)pbReaderName, 
		SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		hScard,
		pdwActiveProtocol);
	if (SCARD_S_SUCCESS == dwRet)
	{
		dwRet = SCardGetAttrib(*hScard,SCARD_ATTR_ATR_STRING,bATR,&usLen);
		//*pucAtrLen = (unsigned char)usLen;
	}	

	return dwRet;

}

DWORD LCardSendCommand(SCARDHANDLE  hScard,BYTE bSendType,
					   PBYTE pbCmd, DWORD dwCmdSize,
					   PBYTE pbRec, DWORD *dwRecLen)
{
	DWORD             dwReturn = 0;	
	if(SCARD_PROTOCOL_T0 == bSendType)
	{

		dwReturn = SCardTransmit(hScard, 
			SCARD_PCI_T0,
			pbCmd, 
			dwCmdSize, 
			NULL, 
			pbRec, 
			dwRecLen);
	}
	else if (SCARD_PROTOCOL_T1 == bSendType)
	{
		dwReturn = SCardTransmit(hScard, 
			SCARD_PCI_T1,
			pbCmd, 
			dwCmdSize, 
			NULL, 
			pbRec, 
			dwRecLen);
	}	
	return dwReturn;
}

DWORD LCardGetData(SCARDHANDLE  hScard,BYTE bSendType,
				   PBYTE pbCmd, DWORD dwCmdSize,
				   PBYTE pbResponse,PDWORD pdwResponseSize)
{

	DWORD dwReturn;
	//	SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
	BYTE			recvbuf[256];
	DWORD			recvlen = sizeof(recvbuf);
	BYTE            SW1, SW2;
	DWORD			dwDataSize = 0;

	__try
	{
		if(!bSendType)
		{
			dwReturn = SCardTransmit(hScard, 
				SCARD_PCI_T0, 
				pbCmd, 
				dwCmdSize, 
				NULL, 
				recvbuf, 
				&recvlen);
		}
		else
		{
			dwReturn = SCardTransmit(hScard, 
				SCARD_PCI_T1, 
				pbCmd, 
				dwCmdSize, 
				NULL, 
				recvbuf, 
				&recvlen);
		}
		if ( dwReturn != SCARD_S_SUCCESS )
		{
			return dwReturn;
		}
		SW1 = recvbuf[recvlen-2];
		SW2 = recvbuf[recvlen-1];

		if ( ( SW1 == 0x90 ) && ( SW2 == 0x00 ) )
		{
			dwDataSize = recvlen-2;
			memcpy(pbResponse, recvbuf, dwDataSize);
		}
		else
		{
			dwReturn = SCARD_F_UNKNOWN_ERROR;
			return dwReturn;
		}
		*pdwResponseSize = dwDataSize;
	}
	__finally
	{
	}

	return dwReturn;
}

DWORD LCardDisConnectCard(SCARDHANDLE hScard)
{
	DWORD dwRet = SCARD_S_SUCCESS;

	dwRet = SCardDisconnect(hScard, SCARD_LEAVE_CARD);
	if(dwRet != SCARD_S_SUCCESS)
	{
		return dwRet;
	}
	if(g_sc)
	{
		// Free the context.
		dwRet=SCardReleaseContext(g_sc);
		if(dwRet != SCARD_S_SUCCESS)
		{
			return dwRet;
		}
	}
	return dwRet;
}
