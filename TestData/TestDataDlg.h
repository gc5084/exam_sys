// TestDataDlg.h : header file
//

#if !defined(AFX_TESTDATADLG_H__965FF5D8_66C9_4490_94D2_DC673139D028__INCLUDED_)
#define AFX_TESTDATADLG_H__965FF5D8_66C9_4490_94D2_DC673139D028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDataDlg dialog

/*主对话框，在主对话框中定义的变量有
  _ConnectionPtr  m_pConnection; 数据库的链接变量

*/

#include "Fill.h"
#include "Base.h"
class CTestDataDlg : public CDialog
{
// Construction
public:
	CTestDataDlg(CWnd* pParent = NULL);	// standard constructor

	_ConnectionPtr  m_pConnection;
	CBase* m_pB;
	//定义链接对象指针

// Dialog Data
	//{{AFX_DATA(CTestDataDlg)
	enum { IDD = IDD_TESTDATA_DIALOG };
	CBitmapButton	m_bmExit;
	CBitmapButton   m_bmLink;
	CBitmapButton   m_bmCut;
	CBitmapButton   m_bmFill;
	CBitmapButton   m_bmModify;
	CBitmapButton   m_bmDesign;
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
   
	// Generated message map functions
	//{{AFX_MSG(CTestDataDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLink();
	afx_msg void OnButtonCut();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonFill();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonDesign();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDATADLG_H__965FF5D8_66C9_4490_94D2_DC673139D028__INCLUDED_)
