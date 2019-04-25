// TestData.h : main header file for the TESTDATA application
//

#if !defined(AFX_TESTDATA_H__970E5A3A_76BD_458F_82B0_1045FC74B6F1__INCLUDED_)
#define AFX_TESTDATA_H__970E5A3A_76BD_458F_82B0_1045FC74B6F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDataApp:
// See TestData.cpp for the implementation of this class
//

class CTestDataApp : public CWinApp
{
public:
	CTestDataApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDataApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDataApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDATA_H__970E5A3A_76BD_458F_82B0_1045FC74B6F1__INCLUDED_)
