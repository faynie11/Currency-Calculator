
// Projekt_nr_3_v3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CProjektnr3v3App:
// See Projekt_nr_3_v3.cpp for the implementation of this class
//

class CProjektnr3v3App : public CWinApp
{
public:
	CProjektnr3v3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProjektnr3v3App theApp;
