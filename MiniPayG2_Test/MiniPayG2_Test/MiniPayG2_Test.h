// MiniPayG2_Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMiniPayG2_TestApp:
// �йش����ʵ�֣������ MiniPayG2_Test.cpp
//

class CMiniPayG2_TestApp : public CWinApp
{
public:
	CMiniPayG2_TestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMiniPayG2_TestApp theApp;