
// DrawCircleRectangle.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawCircleRectangleApp: 
// �йش����ʵ�֣������ DrawCircleRectangle.cpp
//

class CDrawCircleRectangleApp : public CWinApp
{
public:
	CDrawCircleRectangleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrawCircleRectangleApp theApp;
