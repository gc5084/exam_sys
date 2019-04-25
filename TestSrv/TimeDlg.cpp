// TimeDlg.cpp: implementation of the CTimeDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeDlg.h"
#include "SrvMainWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern int GTestTime;
CTimeDlg::CTimeDlg(CWnd* pParent) : CDialog(CTimeDlg::IDD,pParent)
{
    this->m_pParent = (CMainWindow*)pParent;
}

CTimeDlg::~CTimeDlg()
{

}

void CTimeDlg::OnOK()
{
	
	int ntime = (int)GetDlgItemInt(IDC_EDIT_TIME);
	
	//判断时间是否设置过，分别进入设置或修改考试时间代码段
	if((m_pParent->nFlag&FLAG_TIME) != FLAG_TIME)
	{
		if(ntime>250||ntime<1)
		{
			CString str;
			str.Format("考试时间应在1～250之间");
			AfxMessageBox(str);
			return;
			
		}
		GTestTime = ntime;		
	}

	else
	{


		if(ntime>250||ntime<1)
		{
			CString str;
			str.Format("考试时间应在1～250之间");
			AfxMessageBox(str);
			return;
			
		}

		if(AfxMessageBox("确定要修改考试时间吗？",MB_YESNO) == IDYES)
		{
			GTestTime = ntime;
		}
		else
		{
			return;
		}

	}

	m_pParent->nFlag |= FLAG_TIME;
	CDialog::OnOK();
		
}