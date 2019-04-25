#if !defined(AFX_INPUTDLG3_H__0D85A6D5_C7DF_48B0_A9E3_1AD59FF82AB3__INCLUDED_)
#define AFX_INPUTDLG3_H__0D85A6D5_C7DF_48B0_A9E3_1AD59FF82AB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDlg3 dialog

class CInputDlg3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputDlg3)

// Construction
public:
	CInputDlg3();
	~CInputDlg3();
	int nPos; //保存录入新元素的主键号码

// Dialog Data
	//{{AFX_DATA(CInputDlg3)
	enum { IDD = IDD_INPUT_3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg3)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInputDlg3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG3_H__0D85A6D5_C7DF_48B0_A9E3_1AD59FF82AB3__INCLUDED_)
