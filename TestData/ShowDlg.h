#if !defined(AFX_SHOWDLG_H__3E6364E3_9CE0_4902_8634_3BA0775346DD__INCLUDED_)
#define AFX_SHOWDLG_H__3E6364E3_9CE0_4902_8634_3BA0775346DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowDlg dialog
#include "FillDlg.h"

class CShowDlg : public CDialog
{
// Construction
public:
	CShowDlg(CWnd* pParent = NULL);   // standard constructor

	CFillDlg* pParentDlg;
	CString strItem;
	int nIndex;  //选择条目索引

// Dialog Data
	//{{AFX_DATA(CShowDlg)
	enum { IDD = IDD_FILL_SHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnFillBigt();
	afx_msg void OnFillBigco();
	afx_msg void OnFillBiga();
	afx_msg void OnFillBigch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWDLG_H__3E6364E3_9CE0_4902_8634_3BA0775346DD__INCLUDED_)
