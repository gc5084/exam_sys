#if !defined(AFX_INPUTDLG2_H__F524B181_FA8F_4057_9C6E_E51CC04B38CF__INCLUDED_)
#define AFX_INPUTDLG2_H__F524B181_FA8F_4057_9C6E_E51CC04B38CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDlg2 dialog

class CInputDlg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputDlg2)

// Construction
public:
	CInputDlg2();
	~CInputDlg2();

	int nPos; //保存录入新元素的主键号码

// Dialog Data
	//{{AFX_DATA(CInputDlg2)
	enum { IDD = IDD_INPUT_2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInputDlg2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG2_H__F524B181_FA8F_4057_9C6E_E51CC04B38CF__INCLUDED_)
