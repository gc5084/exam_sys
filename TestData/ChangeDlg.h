#if !defined(AFX_CHANGEDLG_H__7355B32E_6699_45EC_AF53_1F7CA2ADB1CC__INCLUDED_)
#define AFX_CHANGEDLG_H__7355B32E_6699_45EC_AF53_1F7CA2ADB1CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg dialog
#include "FillDlg.h"
class CChangeDlg : public CDialog
{
// Construction
public:
	CChangeDlg(CWnd* pParent = NULL);   // standard constructor

	CFillDlg* m_pWnd;
	int m_nPos;

// Dialog Data
	//{{AFX_DATA(CChangeDlg)
	enum { IDD = IDD_FILL_CHANGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	                       //列表选择改变
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChange();
	afx_msg void OnFillDo();
	afx_msg void OnFillChangeBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEDLG_H__7355B32E_6699_45EC_AF53_1F7CA2ADB1CC__INCLUDED_)
