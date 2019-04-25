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
	
	//�ж�ʱ���Ƿ����ù����ֱ�������û��޸Ŀ���ʱ������
	if((m_pParent->nFlag&FLAG_TIME) != FLAG_TIME)
	{
		if(ntime>250||ntime<1)
		{
			CString str;
			str.Format("����ʱ��Ӧ��1��250֮��");
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
			str.Format("����ʱ��Ӧ��1��250֮��");
			AfxMessageBox(str);
			return;
			
		}

		if(AfxMessageBox("ȷ��Ҫ�޸Ŀ���ʱ����",MB_YESNO) == IDYES)
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