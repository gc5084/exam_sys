#if !defined(AFX_TOPWINDOW_H__83BB2A3C_4AB5_48E1_A627_C18EDC4022F7__INCLUDED_)
#define AFX_TOPWINDOW_H__83BB2A3C_4AB5_48E1_A627_C18EDC4022F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTopWindow frame

class CTopWindow : public CWnd
{
	DECLARE_DYNCREATE(CTopWindow)
protected:
	

// Attributes
public:
	CTopWindow(); 
	void ShowInfor();
	afx_msg void OnTimeUp(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSend();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopWindow)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTopWindow();
	CBitmapButton m_button;
									//ͼ�ΰ�ť
	CFont m_fontMain;
									//������
	CRect m_rectR;
									//��Ҫ�ػ������
	CRect m_rectAll;
									//��������
	int   m_cxChar;
	int   m_cyChar;
									//��������Ϣ
	int   arrTabStop[3];
									//�Ʊ��ֹͣλ


	// Generated message map functions
	//{{AFX_MSG(CTopWindow)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPWINDOW_H__83BB2A3C_4AB5_48E1_A627_C18EDC4022F7__INCLUDED_)
