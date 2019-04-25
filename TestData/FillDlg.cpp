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

	//��ȡ����ָ�� ��Fill��
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
																	//�����б���
	if(bTF)
	{
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_SHOW))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHANGE))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_DELETE))->EnableWindow(TRUE);
		((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHECK))->EnableWindow(TRUE);
	}
	else
		AfxMessageBox(_T("�����Ϊ�ջ�����ԭ��δ�г����⣡"));
}

//ɾ�����ⰴť������   
void CFillDlg::OnButtonFillDelete() 
{

	int nIndex = ((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)))->GetCurSel();
	if(nIndex == LB_ERR)
	{  
		MessageBox("��ѡ��һ����¼��");
		return;
	}
	
	if(MessageBox("�Ƿ�Ҫɾ���˼�¼��","ɾ��ȷ��",MB_YESNO|MB_ICONINFORMATION)==IDNO)
		return;
	
	int p = m_pBase->NtoP(nIndex);
	if(m_pBase->Delete(p) == TRUE) //������1001��ʼ
		MessageBox("ɾ���ɹ���");

	m_pBase->List((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)));
	//ˢ���б�
}


//������ʾ��ϸ��Ϣ�Ի���
void CFillDlg::OnButtonFillShow() 
{
    CShowDlg dlg(this);
    dlg.DoModal(); 
}

void CFillDlg::OnButtonFillInput() 
{
   	m_nNewPos = m_pBase->WhereIn();
	                //����½�λ��
	m_pBase->CreateNew(m_nNewPos);
	                //�½�һ����¼

	CPSheet ProSheet("¼��",this);
	ProSheet.SetWizardMode();
	if(ProSheet.DoModal()==IDCANCEL)
		m_pBase->Delete(m_nNewPos);
	                //���ȡ����¼����ɾ���½�������Ŀ

	
}

//�������ⰴť �����������ģ̬�Ի���
void CFillDlg::OnButtonFillChange() 
{
    CChangeDlg dlg(this);
	dlg.DoModal();
}

//�������ذ�ť���� �������û���OnCancel����
void CFillDlg::OnButtonFillBack() 
{
	this->OnCancel();
}

BOOL CFillDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//�Ի����ʼ��ʱ���䲿�ְ�ť����
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_SHOW))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHANGE))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_DELETE))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL_CHECK))->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
˫���б�ʱ������
˫���б���Ŀʱ������ϸ��Ϣ�Ի���
��Ŀ��Ϣ��show�Ի��� �Լ������ȡ
*/
void CFillDlg::OnDblclkListFill() 
{
    CShowDlg dlg(this);
    dlg.DoModal(); 	
}
/*
������ⰴť������
��������Ƿ��д���
����check������
���öԻ�����ʾ������ ���ڵȴ�check��������������ģ��½��̣� �ȴ�
*/
void CFillDlg::OnButtonFillCheck() 
{
	int nIndex = ((CListBox*)(this->GetDlgItem(IDC_LIST_FILL)))->GetCurSel();
	int p = m_pBase->NtoP(nIndex);
 	m_pBase->Check(p);

	CWaitDlg dlg(this);
	dlg.DoModal();


	if(m_pBase->CheckOver(p)==TRUE)
		AfxMessageBox("��ϲ ������ȷ��");
	else
		AfxMessageBox("���������룬��ϸ��飡");
}
