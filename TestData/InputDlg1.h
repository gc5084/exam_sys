#if !defined(AFX_INPUTDLG1_H__2070B170_F106_4732_9685_FFC5F9255BC8__INCLUDED_)
#define AFX_INPUTDLG1_H__2070B170_F106_4732_9685_FFC5F9255BC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDlg1 dialog

class CInputDlg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputDlg1)

// Construction
public:
	CInputDlg1();
	~CInputDlg1();

	int nPos;

// Dialog Data
	//{{AFX_DATA(CInputDlg1)
	enum { IDD = IDD_INPUT_1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg1)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInputDlg1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG1_H__2070B170_F106_4732_9685_FFC5F9255BC8__INCLUDED_)
