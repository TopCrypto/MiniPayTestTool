
#ifndef _TYPEDEF_H
#define _TYPEDEF_H


#ifndef		UCHAR
#define 	UCHAR	unsigned char 
#endif


#ifndef		PUCHAR
#define		PUCHAR	 unsigned char *
#endif

#ifndef		USHORT	
#define		USHORT	unsigned short
#endif

#ifndef		PUSHORT
#define		PUSHORT	USHORT *
#endif

#ifndef		ULONG	
#define		ULONG	unsigned long
#endif

#ifndef		PULONG
#define		PULONG 	ULONG *
#endif
#ifndef		UINT
#define		UINT	unsigned int
#endif

#ifndef		PUINT
#define		PUINT	UINT *

#endif
#ifndef		NULL
#define		NULL		0
#endif

#ifndef		TRUE
#define		TRUE		1
#endif

#ifndef		true
#define		true		1
#endif

#ifndef		FALSE
#define		FALSE		0
#endif

#ifndef		false
#define		false		0
#endif

#define YES        0
#define NO         1

#define OK         0
#define KO         1
#define NOK        1



#ifndef		ULONG_C51
#define ULONG_C51 ULONG
#endif

#ifndef		UINT_C51
#define UINT_C51 UINT
#endif


typedef enum  { ASCII_FONT  , GB2312_FONT} FONT;


#endif
