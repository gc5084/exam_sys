/////////////////////////////////////////////////////////////////////
//类名：CCheckDlg
//说明：检查试题对话框类
//功能：检查所有考生答卷的错对
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_)
#define AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMainWnd.h"

class CCheckDlg : public CDialog  
{
public:
	CCheckDlg(CWnd* pParent);
	virtual ~CCheckDlg();
	virtual void OnOK();

	enum {IDD = IDD_CHECKDLG};
protected:
	CMainWindow* m_pParent;

	int          nStu;//记录有多少了学生已交卷 用于进度条总数的显示

	CStatic*       m_pStatic;
	CProgressCtrl* m_pProgressCtrl;

	virtual BOOL OnInitDialog();


};

#endif // !defined(AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_)
