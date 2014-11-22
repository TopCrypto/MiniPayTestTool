#ifndef _PCSC_H

#define PCSC_SUCCESS	0
#define PCSC_DATAERR	1

DWORD SCard_UpdateDevice();
DWORD SCard_Connect(LPCTSTR  pbReaderName,BYTE *bATR);
DWORD SCard_ApduExchang(UCHAR *pcuCommand,USHORT usCommandLen,UCHAR *pucResond,USHORT *pusRespondLen);
#define _PCSC_H
#endif
