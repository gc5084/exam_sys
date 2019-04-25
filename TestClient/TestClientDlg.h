// TestClientDlg.h : header file
//

#if !defined(AFX_TESTCLIENTDLG_H__C828DD5D_3FF4_466F_8B84_CEBD593B7CFC__INCLUDED_)
#define AFX_TESTCLIENTDLG_H__C828DD5D_3FF4_466F_8B84_CEBD593B7CFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestClientDlg dialog

class CTestClientDlg : public CDialog
{
// Construction
public:
	CTestClientDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(CTestClientDlg)
	enum { IDD = IDD_TESTCLIENT_DIALOG };
	CStatic	m_TestInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	char* fill[3];
	char* modify[3];
	char* design[3];
//	int m_textNum;


// Implementation
protected:
	CButton m_LookButton[3][3];
	CButton m_AnswerButton[3][3];
	HICON m_hIcon;

	char* m_AppPath;  // 当前应用程序路径
	CString m_TestFileName[3][3];
	
//	char*   ReadMyFile(const char* czFileName);//将文件数据 读入内存 用于上交给服务器
	void    SendOver();       //发送交卷完毕函数
	void ShowTestNumber();      //在对话框上显示试题个数

	BOOL DealLookButton(int type,int order);
	BOOL DealAnswerButton(int type,int order);
	void initFileName();      //初始化m_TestFileName二维数组
	void DisableButton();   //灰化按钮
	// Generated message map functions
	//{{AFX_MSG(CTestClientDlg)
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnLookFill1();
	afx_msg void OnLookFill2();
	afx_msg void OnLookFill3();
	afx_msg void OnLookModify1();
	afx_msg void OnLookModify2();
	afx_msg void OnLookModify3();
	afx_msg void OnLookDesign1();
	afx_msg void OnLookDesign2();
	afx_msg void OnLookDesign3();

	afx_msg void OnAnswerFill1();
	afx_msg void OnAnswerFill2();
	afx_msg void OnAnswerFill3();
	afx_msg void OnAnswerModify1();
	afx_msg void OnAnswerModify2();
	afx_msg void OnAnswerModify3();
	afx_msg void OnAnswerDesign1();
	afx_msg void OnAnswerDesign2();
	afx_msg void OnAnswerDesign3();

	afx_msg void OnTimeOver(WPARAM wParam, LPARAM lParam);
    afx_msg void OnTestSend(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMyClose(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReStart(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSendSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nTimerID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTDLG_H__C828DD5D_3FF4_466F_8B84_CEBD593B7CFC__INCLUDED_)
