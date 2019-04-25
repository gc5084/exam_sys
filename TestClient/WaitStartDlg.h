#if !defined(AFX_WAITSTARTDLG_H__580EBA58_BB27_4AB9_8F37_6D70F9103CAE__INCLUDED_)
#define AFX_WAITSTARTDLG_H__580EBA58_BB27_4AB9_8F37_6D70F9103CAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitStartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaitStartDlg dialog

class CWaitStartDlg : public CDialog
{
// Construction
public:
	CWaitStartDlg(CWnd* pParent = NULL);   // standard constructor
	void GetInitMessage(CString Number);

	afx_msg void OnTestSendOver(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReStart(WPARAM wParam, LPARAM lParam);

// Dialog Data
	//{{AFX_DATA(CWaitStartDlg)
	enum { IDD = IDD_WAITSTART };
	CString	m_Name;
	CString	m_Num;
	CString	m_Time;
	//}}AFX_DATA
	void SendRequestTest(BOOL result);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitStartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	BOOL m_SendRequest; //是否需要发送请求试题标志
	// Generated message map functions
	//{{AFX_MSG(CWaitStartDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITSTARTDLG_H__580EBA58_BB27_4AB9_8F37_6D70F9103CAE__INCLUDED_)
