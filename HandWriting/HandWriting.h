
// HandWriting.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHandWritingApp: 
// �йش����ʵ�֣������ HandWriting.cpp
//

class CHandWritingApp : public CWinApp
{
public:
	CHandWritingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHandWritingApp theApp;