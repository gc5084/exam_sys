#if !defined(AFX_BIGSHOWDLG_H__8E2714B5_CDDB_450B_A56B_075BDEC2E372__INCLUDED_)
#define AFX_BIGSHOWDLG_H__8E2714B5_CDDB_450B_A56B_075BDEC2E372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BigShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBigShowDlg dialog
#include "ShowDlg.h"
class CBigShowDlg : public CDialog
{
// Construction
public:
	CBigShowDlg(CWnd* pParent = NULL);   // standard constructor
	CShowDlg* m_pParent;

// Dialog Data
	//{{AFX_DATA(CBigShowDlg)
	enum { IDD = IDD_BIGSHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBigShowDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGSHOWDLG_H__8E2714B5_CDDB_450B_A56B_075BDEC2E372__INCLUDED_)
