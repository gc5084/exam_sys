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

/*构造函数
根据父类指针（主窗口）获得要显示学生的数组索引
添加三个属性页
 */
CInforSheet::CInforSheet(LPCTSTR pszCaption,CWnd* pParent): 
              CPropertySheet(pszCaption,pParent,0)
{
	m_nStu = ((CMainWindow*)pParent)->nRightDown;
	                     //nRightDown为主窗口记录上下文菜单弹出时所在的区域
	                     //因为区域数组和学生数组是一一对应的
	AddPage(&m_StuPage);
	AddPage(&m_TestPage);
	AddPage(&m_PointPage);
}

CInforSheet::CInforSheet(LPCTSTR pszCaption,char* czNumber): 
              CPropertySheet("显示信息",NULL,0)
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
