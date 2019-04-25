// ChangeIP.h : main header file for the CHANGEIP application
//

#if !defined(AFX_CHANGEIP_H__43C4F588_F944_4510_990D_6C519D2730E5__INCLUDED_)
#define AFX_CHANGEIP_H__43C4F588_F944_4510_990D_6C519D2730E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChangeIPApp:
// See ChangeIP.cpp for the implementation of this class
//

class CChangeIPApp : public CWinApp
{
public:
	CChangeIPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeIPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChangeIPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEIP_H__43C4F588_F944_4510_990D_6C519D2730E5__INCLUDED_)
