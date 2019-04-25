#if !defined(AFX_PSHEET_H__C4BE6624_A815_4231_A38A_FC95CBFC43E9__INCLUDED_)
#define AFX_PSHEET_H__C4BE6624_A815_4231_A38A_FC95CBFC43E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPSheet
#include "InputDlg1.h"
#include "InputDlg2.h"
#include "InputDlg3.h"
class CPSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSheet)

// Construction
public:
	CPSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	CInputDlg1 m_Dlg1;
	CInputDlg2 m_Dlg2;
	CInputDlg3 m_Dlg3;

	int m_nPos;
	CWnd* m_pMWnd;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEET_H__C4BE6624_A815_4231_A38A_FC95CBFC43E9__INCLUDED_)
