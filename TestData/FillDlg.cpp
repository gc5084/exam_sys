// FillDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "FillDlg.h"
#include "TestDataDlg.h"
#include "Fill.h"
#include "ShowDlg.h"
#include "PSheet.h"
#include "ChangeDlg.h"
#include "TestDataDlg.h"
#include "WaitDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFillDlg dialog


CFillDlg::CFillDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFillDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFillDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//获取链接指针 给Fill类
	m_pBase = ((CTestDataDlg*)pParent)->m_pB;
}


void CFillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFillDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

CBase* CFillDlg::GetpBase()
{
	return m_pBase;
}


BEGIN_MESSAGE_MAP(CFillDlg, CDialog)
	//{{AFX_MSG_MAP(CFillDlg)
	ON_BN_CLICKED(IDC_BUTTON_FILL_LIST, OnButtonFillList)
	ON_BN_CLICKED(IDC_BUTTON_FILL_DELETE, OnButtonFillDelete)
	ON_BN_CLICKED(IDC_BUTTON_FILL_SHOW, OnButtonFillShow)
	ON_BN_CLICKED(IDC_BUTTON_FILL_INPUT, OnButtonFillInput)
	ON_BN_CLICKED(IDC_BUTTON_FILL_CHANGE, OnButtonFillChange)
	ON_BN_CLICKED(IDC_BUTTON_FILL_BACK, OnButtonFillBack)
	ON_LBN_DBLCLK(IDC_LIST_FILL, OnDblclkListFill)
	ON_BN_CLICKED(IDC_BUTTON_FILL_CHECK, OnButtonFillCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFillDlg message handlers

void CFillDlg::OnButtonFillList() 
{
   	BOOL bTF = m_pBase->List((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)));
																	//调用列表函数
	if(bTF)
	{
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_SHOW))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHANGE))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_DELETE))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHECK))->EnableWindow(TRUE);
	}
	else
		AfxMessageBox(_T("试题库为空或其它原因未列出试题！"));
}

//删除试题按钮处理函数   
void CFillDlg::OnButtonFillDelete() 
{

	int nIndex = ((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)))->GetCurSel();
	if(nIndex == LB_ERR)
	{  
		MessageBox("请选择一条记录！");
		return;
	}
	
	if(MessageBox("是否要删除此记录？","删除确认",MB_YESNO|MB_ICONINFORMATION)==IDNO)
		return;
	
	int p = m_pBase->NtoP(nIndex);
	if(m_pBase->Delete(p) == TRUE) //主键从1001开始
		MessageBox("删除成功！");

	m_pBase->List((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)));
	//刷新列表
}


//调用显示详细信息对话框
void CFillDlg::OnButtonFillShow() 
{
    CShowDlg dlg(this);
    dlg.DoModal(); 
}

void CFillDlg::OnButtonFillInput() 
{
   	m_nNewPos = m_pBase->WhereIn();
	                //获得新建位置
	m_pBase->CreateNew(m_nNewPos);
	                //新建一条记录

	CPSheet ProSheet("录入",this);
	ProSheet.SetWizardMode();
	if(ProSheet.DoModal()==IDCANCEL)
		m_pBase->Delete(m_nNewPos);
	                //如果取消了录入则删除新建试题条目

	
}

//更改试题按钮 进入更改试题模态对话框
void CFillDlg::OnButtonFillChange() 
{
    CChangeDlg dlg(this);
	dlg.DoModal();
}

//单击返回按钮函数 函数调用基类OnCancel返回
void CFillDlg::OnButtonFillBack() 
{
	this->OnCancel();
}

BOOL CFillDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//对话框初始化时让其部分按钮灰显
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_SHOW))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHANGE))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_DELETE))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHECK))->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
双击列表时处理函数
双击列表项目时弹出详细信息对话框，
条目信息由show对话框 自己负责获取
*/
void CFillDlg::OnDblclkListFill() 
{
    CShowDlg dlg(this);
    dlg.DoModal(); 	
}
/*
检查试题按钮处理函数
检查试题是否有错误
调用check函数，
调用对话框显示进度条 用于等待check函数调用批处理的（新进程） 等待
*/
void CFillDlg::OnButtonFillCheck() 
{
	int nIndex = ((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)))->GetCurSel();
	int p = m_pBase->NtoP(nIndex);
 	m_pBase->Check(p);

	CWaitDlg dlg(this);
	dlg.DoModal();


	if(m_pBase->CheckOver(p)==TRUE)
		AfxMessageBox("恭喜 试题正确！");
	else
		AfxMessageBox("试题有误请，详细检查！");
}
