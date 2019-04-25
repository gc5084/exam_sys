#if !defined(AFX_FILLDLG_H__2412474D_EBC7_4B45_9FAF_1808F8B75548__INCLUDED_)
#define AFX_FILLDLG_H__2412474D_EBC7_4B45_9FAF_1808F8B75548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FillDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFillDlg dialog
#include "Base.h"
//
class CFillDlg : public CDialog
{
protected:
	CBase* m_pBase;
public:
	CFillDlg(CWnd* pParent = NULL);   // standard constructor
	CBase* GetpBase();

	int m_nNewPos;  //ÐÂ½¨Î»ÖÃ
	
	

// Dialog Data
	//{{AFX_DATA(CFillDlg)
	enum { IDD = IDD_FILL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFillDlg)
	afx_msg void OnButtonFillList();
	afx_msg void OnButtonFillDelete();
	afx_msg void OnButtonFillShow();
	afx_msg void OnButtonFillInput();
	afx_msg void OnButtonFillChange();
	afx_msg void OnButtonFillBack();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListFill();
	afx_msg void OnButtonFillCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILLDLG_H__2412474D_EBC7_4B45_9FAF_1808F8B75548__INCLUDED_)
