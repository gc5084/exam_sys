// SelectTestDlg.cpp: implementation of the CSelectTestDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelectTestDlg.h"
#include "SrvMyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;										
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;

BEGIN_MESSAGE_MAP(CSelectTestDlg, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBOBOX,OnSelChange)
	ON_BN_CLICKED(IDC_DELECT, OnDelect)
	ON_BN_CLICKED(IDC_ADD, OnAdd)

END_MESSAGE_MAP()

CSelectTestDlg::CSelectTestDlg(CWnd* pParent) : CDialog(CSelectTestDlg::IDD,pParent)
{
	this->nSelect = -1;
}

CSelectTestDlg::~CSelectTestDlg()
{
	//�����������
	m_listUnSelectFill.RemoveAll();
	m_listUnSelectModify.RemoveAll();
	m_listUnSelectDesign.RemoveAll();
}

void CSelectTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_SELECT,this->m_ListSelect);

	DDX_Control(pDX,IDC_UNSELECT,this->m_ListUnSelect);

	DDX_Control(pDX,IDC_COMBOBOX,this->m_ComboBox);

	DDX_Control(pDX,IDC_DELECT,this->m_ButtonDelect);

	DDX_Control(pDX,IDC_ADD,this->m_ButtonAdd);

}

BOOL CSelectTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	m_ListSelect.ModifyStyle(NULL,LBS_MULTIPLESEL);

	CString str;

	m_ComboBox.AddString("�����");
	m_ComboBox.AddString("�Ĵ���");
	m_ComboBox.AddString("�����");

	return TRUE;
}

void CSelectTestDlg::OnSelChange()
{
	//����б��ԭ����Ŀ
	m_ListSelect.ResetContent();
	m_ListUnSelect.ResetContent();

	//�����Ͽ��б�ѡ��
	int Item;
	Item = this->m_ComboBox.GetCurSel();

	POSITION pos;
	MemoryData TempMD;
	CString str;
	switch(Item)
	{
	case 0:   //�����
		{
			//ѡ���б���г���Ŀ
			pos = listTestFill.GetHeadPosition(); //��ȡͷָ��
			while(pos != NULL)
			{
				TempMD = listTestFill.GetNext(pos);//��ȡ��һ��Ԫ��
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}

			//δѡ���б���г���Ŀ
			pos = this->m_listUnSelectFill.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectFill.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 0;//��ǰ�ҳΪ�����
			break;
		}

	case 1:   //�Ĵ���
		{
			//ѡ���б���г���Ŀ
			pos = listTestModify.GetHeadPosition(); //��ȡͷָ��
			while(pos != NULL)
			{
				TempMD = listTestModify.GetNext(pos);//��ȡ��һ��Ԫ��
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}
			//δѡ���б���г���Ŀ
			pos = this->m_listUnSelectModify.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectModify.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 1;//��ǰ�ҳΪ�Ĵ���
			break;
		}

	case 2:   //�����
		{
			
			//ѡ���б���г���Ŀ
			pos = listTestDesign.GetHeadPosition(); //��ȡͷָ��
			while(pos != NULL)
			{
				TempMD = listTestDesign.GetNext(pos);//��ȡ��һ��Ԫ��
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}
			//δѡ���б���г���Ŀ
			pos = this->m_listUnSelectDesign.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectDesign.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 2;//��ǰ�ҳΪ�����
			break;
		}
	default:
		break;
	}
}

/*�޳�����Ӧ���� ��ѡ���б��ѡ������� ���е� δѡ���б��*/

void CSelectTestDlg::OnDelect()
{
	//��ȡ��ѡ�����Ŀ���� ������aryListBoxSel��
	int nCount = this->m_ListSelect.GetSelCount();
	                                   //�õ�ѡ����Ŀ������
	CArray<int,int> aryListBoxSel;
	                       //����һ�������������ڴ��ѡ����Ŀ������
	aryListBoxSel.SetSize(nCount);
                          //�������СΪѡ����Ŀ������
	m_ListSelect.GetSelItems(nCount, aryListBoxSel.GetData());
	                  //����Ŀ��������aryListBoxSel ��GetData()�ṩ�����ָ��
	
	//���������е�����ɾ�����������е���Ŀ�����ڱ�ɾ���б�
	int n,j; //ѭ������
	POSITION pos;
	switch(nSelect)      //���ݵ�ǰ�ҳȷ���������Ǹ�����
	{
	case 0:  //��ǰ�ҳΪ�����
		for(n=0;n<nCount;n++)
		{
			pos = listTestFill.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestFill.GetNext(pos);	
			}

			//��ӵ�δѡ���б�
			m_listUnSelectFill.AddTail(listTestFill.GetAt(pos));

			//��ԭ�б���ɾ�� 
			listTestFill.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	case 1:  //��ǰ�ҳΪ�Ĵ���
		for(n=0;n<nCount;n++)
		{
			pos = listTestModify.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestModify.GetNext(pos);
			}
			//��ӵ�δѡ���б�
			m_listUnSelectModify.AddTail(listTestModify.GetAt(pos));

			//��ԭ�б���ɾ�� 
			listTestModify.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	case 2:
		for(n=0;n<nCount;n++)
		{
			pos = listTestDesign.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestDesign.GetNext(pos);
			}

			//��ӵ�δѡ���б�
			m_listUnSelectDesign.AddTail(listTestDesign.GetAt(pos));

			//��ԭ�б���ɾ�� 
			listTestDesign.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	default:
		break;
	}

	//������Ͽ�ѡ����ˢ���б��
	OnSelChange();

	
}

/*�ָ�����Ӧ���� ��δѡ���б��ѡ������� ���е� ѡ���б��*/
void CSelectTestDlg::OnAdd()
{
	//��ȡ��ѡ�����Ŀ���� ������aryListBoxSel��
	int nCount = this->m_ListUnSelect.GetSelCount();
	                                   //�õ�δѡ���б��ѡ����Ŀ������
	CArray<int,int> aryListBoxSel;
	                       //����һ�������������ڴ��ѡ����Ŀ������
	aryListBoxSel.SetSize(nCount);
                          //�������СΪѡ����Ŀ������
	m_ListUnSelect.GetSelItems(nCount, aryListBoxSel.GetData());
	                  //����Ŀ��������aryListBoxSel ��GetData()�ṩ�����ָ��
	
	//���������е�����ɾ�����������е���Ŀ�����ڱ�ɾ���б�
	int n,j; //ѭ������
	POSITION pos;
	switch(nSelect)      //���ݵ�ǰ�ҳȷ���������Ǹ�����
	{
	case 0:  //��ǰ�ҳΪ�����
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectFill.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectFill.GetNext(pos);	
			}

			//��ӵ�ѡ���б�
			listTestFill.AddTail(m_listUnSelectFill.GetAt(pos));

			//��ԭ�б���ɾ�� 
			m_listUnSelectFill.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	case 1:  //��ǰ�ҳΪ�Ĵ���
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectModify.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectModify.GetNext(pos);
			}
			//��ӵ�δѡ���б�
			listTestModify.AddTail(m_listUnSelectModify.GetAt(pos));

			//��ԭ�б���ɾ�� 
			m_listUnSelectModify.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	case 2:
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectDesign.GetHeadPosition();

			//����ѭ�� ��posѭ��������λ��
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectDesign.GetNext(pos);
			}

			//��ӵ�δѡ���б�
			listTestDesign.AddTail(m_listUnSelectDesign.GetAt(pos));

			//��ԭ�б���ɾ�� 
			m_listUnSelectDesign.RemoveAt(pos);//ɾ��

			//�����еĵ�ǰԪ�ؽ���ɾ�� �޸���һ��λ���д��������
			if(n < nCount-1)//n�Ѿ������һ��Ԫ����
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) �Ѿ��м���Ԫ�ر�ɾ��
		}
		break;
	default:
		break;
	}

	//������Ͽ�ѡ����ˢ���б��
	OnSelChange();
}

//����OnCancel ʹesc������ȡ���Ի���
void CSelectTestDlg::OnCancel()
{}

