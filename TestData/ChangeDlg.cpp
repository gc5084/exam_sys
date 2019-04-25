// ChangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "ChangeDlg.h"
#include "FillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg dialog


CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pWnd = (CFillDlg*)pParent;
}


void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeDlg)
	ON_CBN_SELCHANGE(IDC_COMBO,OnSelChange)
	ON_BN_CLICKED(IDC_FILL_DO, OnFillDo)
	ON_BN_CLICKED(ID_FILL_CHANGE_BACK, OnFillChangeBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg message handlers

BOOL CChangeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("标题摘要");
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("试题内容");
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("试题答案");
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("阅卷内容");
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("阅卷输出");
	((CComboBox*)GetDlgItem(IDC_COMBO))->AddString("备注");


	//((CComboBox*)GetDlgItem(IDC_COMBO))->SetCurSel(0);
	((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(FALSE);

	m_nPos = ((CListBox*)m_pWnd->GetDlgItem(IDC_LIST_FILL))->GetCurSel();
    
	m_nPos = m_pWnd->GetpBase()->NtoP(m_nPos);
	                            //数据主键 然后Show参2
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*
 组合列表框改变选项后 处理CBN_SELCHANGE消息的函数
 每次改变后对应的原编辑框会显示内容
*/
void CChangeDlg::OnSelChange()
{
	int nItem;
    nItem = ((CComboBox*)GetDlgItem(IDC_COMBO))->GetCurSel();
                                                //获取组合列表框的选项
	switch(nItem)
	{
	case 0:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"ftitle");
		break;

	case 1:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"fcontent");
		break;

	case 2:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"fanswer");
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"fcheck");
		break;
	case 4:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"fout");
		break;

	case 5:
		((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->SetWindowText("");
        
		m_pWnd->GetpBase()->Show((CEdit*)GetDlgItem(IDC_CHANGE_OLD),m_nPos,"fremark");
		break;
	default: ((CButton*)GetDlgItem(IDC_FILL_DO))->EnableWindow(FALSE);break;

	}
}

void CChangeDlg::OnFillDo() 
{
	int nItem;
    nItem = ((CComboBox*)GetDlgItem(IDC_COMBO))->GetCurSel();
                                                //获取组合列表框的选项
	CString str;
	switch(nItem)
	{
	case 0:
    
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
		if(str.IsEmpty() == TRUE)
		{
			AfxMessageBox("标题摘要不能为空！");
			return;
		}
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"ftitle");
		break;

	case 1:
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
		if(str.IsEmpty() == TRUE)
		{
			AfxMessageBox("试题内容不能为空！");
			return;
		}
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"fcontent");
		break;
	case 2:
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
		if(str.IsEmpty() == TRUE)
		{
			AfxMessageBox("答案不能为空！");
			return;
		}
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"fanswer");
		break;
	case 3:
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
		if(str.IsEmpty() == TRUE)
		{
			AfxMessageBox("阅卷内容不能为空！");
			return;
		}
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"fcheck");
		break;
	case 4:
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
		if(str.IsEmpty() == TRUE)
		{
			AfxMessageBox("阅卷输出不能为空！");
			return;
		}
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"fout");
		break;

	case 5:
		((CEdit*)GetDlgItem(IDC_CHANGE_NEW))->GetWindowText(str);
	
		m_pWnd->GetpBase()->Input((CEdit*)GetDlgItem(IDC_CHANGE_NEW),m_nPos,"fremark");
		break;
	default: break;
	}

	AfxMessageBox("修改完成！");
  	
}

void CChangeDlg::OnFillChangeBack() 
{
   this->OnCancel();	
}
