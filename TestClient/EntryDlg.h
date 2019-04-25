#if !defined(AFX_ENTRYDLG_H__0D29FDB4_B6E7_4819_A6CB_0A7FA0621F8E__INCLUDED_)
#define AFX_ENTRYDLG_H__0D29FDB4_B6E7_4819_A6CB_0A7FA0621F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EntryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog

class CEntryDlg : public CDialog
{
// Construction
public:
	CEntryDlg(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CEntryDlg)
	enum { IDD = IDD_ENTRY };
	
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	BOOL m_bConnect;  //是否连接过标志
	CBitmapButton	m_bmExit;
	CBitmapButton   m_bmStart;
	CBitmap m_bitmap;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
//	BOOL InputText(char* Buffer);
//	BOOL InputFile(char* Buffer,int MajorFlag);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEntryDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual BOOL OnEraseBkgnd(CDC*   pDC);
	//}}AFX_MSG
	
	BOOL ConnectSrv();

	BOOL DealFoundNumber(char* czRecvPage,char* czNum);






	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTRYDLG_H__0D29FDB4_B6E7_4819_A6CB_0A7FA0621F8E__INCLUDED_)
