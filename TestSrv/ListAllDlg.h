// ListAllDlg.h: interface for the CListAllDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTALLDLG_H__F6DD7663_CFCA_4E40_BABB_F5FE765853B8__INCLUDED_)
#define AFX_LISTALLDLG_H__F6DD7663_CFCA_4E40_BABB_F5FE765853B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CListAllDlg : public CDialog  
{
public:
	CListAllDlg(CWnd* pParent);
	virtual ~CListAllDlg();
	enum {IDD = IDD_LISTCTRL};
protected:
	
	virtual void DoDataExchange(CDataExchange*);

	virtual BOOL OnInitDialog();
protected:
	CListCtrl  m_ListCtrl;      //表格控件类
	int     nFill;
	int     nModify;
	int     nDesign;

};

#endif // !defined(AFX_LISTALLDLG_H__F6DD7663_CFCA_4E40_BABB_F5FE765853B8__INCLUDED_)
