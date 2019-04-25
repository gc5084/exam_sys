// ChangeIPDlg.h : header file
//

#if !defined(AFX_CHANGEIPDLG_H__908760E0_D8F9_4157_B376_7E8813A3226A__INCLUDED_)
#define AFX_CHANGEIPDLG_H__908760E0_D8F9_4157_B376_7E8813A3226A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChangeIPDlg dialog

class CChangeIPDlg : public CDialog
{
// Construction
public:
	CChangeIPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeIPDlg)
	enum { IDD = IDD_CHANGEIP_DIALOG };
	CIPAddressCtrl	m_IPControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeIPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChangeIPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEIPDLG_H__908760E0_D8F9_4157_B376_7E8813A3226A__INCLUDED_)
