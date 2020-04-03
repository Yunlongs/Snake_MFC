
// TRY 3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTRY3App:
// See TRY 3.cpp for the implementation of this class
//

class CTRY3App : public CWinApp
{
public:
	CTRY3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTRY3App theApp;