// TalkDlg.h: interface for the CTalkDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TALKDLG_H__628832C6_5D31_40F1_892D_C3E6EE0CE850__INCLUDED_)
#define AFX_TALKDLG_H__628832C6_5D31_40F1_892D_C3E6EE0CE850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTalkDlg : public CDialog  
{
public:
	CTalkDlg(CWnd* pParent);
	virtual ~CTalkDlg();

	virtual void OnOK();

	CString GetContent();

	enum { IDD = IDD_TALK };
protected:

	virtual void DoDataExchange(CDataExchange*);


	CEdit      m_Edit;
	CString    m_strContent;
};

#endif // !defined(AFX_TALKDLG_H__628832C6_5D31_40F1_892D_C3E6EE0CE850__INCLUDED_)
