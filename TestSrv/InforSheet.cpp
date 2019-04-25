// InforSheet.cpp: implementation of the CInforSheet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InforSheet.h"
#include "SrvMainWnd.h"
#include "StuInfor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CStuInfor* arrStu[MAXNUM];

/*���캯��
���ݸ���ָ�루�����ڣ����Ҫ��ʾѧ������������
�����������ҳ
 */
CInforSheet::CInforSheet(LPCTSTR pszCaption,CWnd* pParent): 
              CPropertySheet(pszCaption,pParent,0)
{
	m_nStu = ((CMainWindow*)pParent)->nRightDown;
	                     //nRightDownΪ�����ڼ�¼�����Ĳ˵�����ʱ���ڵ�����
	                     //��Ϊ���������ѧ��������һһ��Ӧ��
	AddPage(&m_StuPage);
	AddPage(&m_TestPage);
	AddPage(&m_PointPage);
}

CInforSheet::CInforSheet(LPCTSTR pszCaption,char* czNumber): 
              CPropertySheet("��ʾ��Ϣ",NULL,0)
{
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			if(strcmp(arrStu[n]->strNum,czNumber) == 0)
			{
				m_nStu = n;
				break;
			}
		}
	}
	AddPage(&m_StuPage);
	AddPage(&m_TestPage);
	AddPage(&m_PointPage);
}

CInforSheet::~CInforSheet()
{

}
