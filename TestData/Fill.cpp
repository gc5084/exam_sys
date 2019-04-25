// Fill.cpp: implementation of the CFill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestData.h"
#include "Fill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFill::CFill(_ConnectionPtr  m_pConnection):CBase(m_pConnection)
{

}

CFill::~CFill()
{

}
/*
显示信息函数
该函数功能为现实指定的项目信息到指定的编辑控件上
第一个参数为编辑控件的指针，第二个参数为试题的编号（数据库主关键字），
第三个参数为属性列的名称
*/
BOOL CFill::Show(CEdit* pEdit,int nIndex,CString str)
{
	CString strSQL;
	strSQL.Format("select * from fill where fnum='%d'",nIndex);

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
															//初始化记录集
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
                                                            //用指定SQL语句打开记录集

        if(m_pRecordset->GetCollect((LPCTSTR)str).vt != VT_NULL)
		    pEdit->SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect((LPCTSTR)str));
															//判断记录集对应项是否为NULL 
															//不为则在控件上显示数据 否则控件写“无信息”
		else
			pEdit->SetWindowText(_T("无信息"));
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
	
}
/*
列出所有概要信息。
参数为CListBox控件的指针
概要信息包括 试题编号 试题说明  试题备注
*/


BOOL CFill::List(CListBox* pList)
{
	CString strSQL;
	strSQL.Format("select * from fill;");
	CString strNum;
	              //记录试题编号
	CString strTil;
	              //记录试题说明
	CString strRem;
 	              //记录试题备注
	CString strAdd;
	              //记录要显示的整条记录
	int nCircle = 0;
    
	pList->SendMessage(WM_SETREDRAW,FALSE,0);
	              //重绘无效 防止闪动
	pList->ResetContent();

	try	
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0)
		{
			strNum = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum");
			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)
				strTil = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle");
			else
				strTil = _T("");
			                     //如果不是空值赋给CString对象 否则会引起异常

			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)
				strRem = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark");
			else 
				strRem =_T("");

			strAdd.Format("%-10s%-35s%s",strNum.Left(5),strTil.Left(30),strRem.Left(10));
			pList->AddString(strAdd);
		//	AfxMessageBox(strNum);
			m_pRecordset->MoveNext();
			nCircle++;
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
    pList->SendMessage(WM_SETREDRAW,TRUE,0);
	                                          //函数结束前 恢复重绘
    pList->SetCurSel(0);
	if(nCircle == 0)
		return FALSE;
	return TRUE;
}

BOOL CFill::Delete(int nIndex)
{
	CString strSQL;
	strSQL.Format("delete from fill where fnum='%d';",nIndex); 
	try
	{
		m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}
/*
设置链接函数
*/
BOOL CFill::SetPcon(_ConnectionPtr  m_pCon)
{
	m_pConnection = m_pCon;
	return TRUE;
}

BOOL CFill::Input(CEdit* pEdit,int nIndex,CString str)
{   
	CString strtext;
	pEdit->GetWindowText(strtext);
    strtext.Replace("'","''");
									//将'替换成'' 防止SQL句法性错误

	CString strSQL;
	strSQL.Format("update fill set %s = '%s' where fnum = '%d'",str,strtext,nIndex);

	try
	{
		m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;

}

/*
获得一共有多少条记录
*/
int  CFill::account()
{
	CString strSQL;
	strSQL.Format("select * from fill;");

	int naccount = 0;

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0)
		{
			naccount++;
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return naccount;

}
/*
计算新记录应插入的位置
因为原记录有的元组被删除 试题主键不连续
新试题应填充空缺 计算出相应位置
*/
int CFill::WhereIn()
{
	CString strSQL;
	strSQL.Format("select * from fill;");

	int nInPos = 1001;

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0)
		{
			
			if(atoi((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum")) != nInPos)
				return nInPos;
			m_pRecordset->MoveNext();
			nInPos++;
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return nInPos;
}

int CFill::NtoP(int n)
{
	CString strSQL;
	strSQL.Format("select * from fill;");
    int p,i=-1;

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0 && i!=n)
		{
			
			p = atoi((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
			m_pRecordset->MoveNext();
			i++;
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
    
	return p;

}

BOOL CFill::CreateNew(int p)
{
   	CString strSQL;
	strSQL.Format("insert into fill(fnum,ftitle,fcontent,fremark,fanswer) \
		values ('%d','暂无标题','暂无试题内容','无备注','暂无答案');",p);
		           
	try
	{
		m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}
/*
读取相应部分再组合成字符串
然后写入相应文件
写批处理文件 最后执行
*/
void CFill::Check(int p)
{
	CString strAnswer,strCheck,temp;	
												//定义答案字符串 检测题字符串 临时字符串
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
												//以此为答案截取起始点 结束点 检测题歧视点 结束点

	CString strSQL;
	strSQL.Format("select * from fill where fnum='%d'",p);
												//指定题号的将被检测的试题
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
												//初始化com组件，打开指定记录集

        if(m_pRecordset->GetCollect("fanswer").vt != VT_NULL)
		     strAnswer = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fanswer");
												//答案项放入答案字符串
		if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)
		     strCheck = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck");
												//检测题项放入检测字符串
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	while(strAnswer.Find("/***found***/")!=-1)
	{
        nAsBegin = strAnswer.Find("/***found***/");
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return;
		//答案字符串中有一个/***found***/ 就有一个/***end***/ 否则就出错要返回
		if( (nCKBegin = strCheck.Find("/***found***/")) == -1)
			return;
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return;
		//检查字符串中有一个/***found***/ 就有一个/***end***/ 否则就出错要返回

												//获取答案和检测中的起始结束

        temp = strAnswer.Left(nAsEnd);
												//截取第一个/***end***/的左半部分
		temp = temp.Right(nAsEnd - nAsBegin - 13);
												//截取temp中右半部 提取内容 13为/***found***/的长度

		strCheck.Insert(nCKEnd,temp);
												//插入阅卷对应位置
		strAnswer.Delete(nAsBegin,13);
												//删除答案字符串中已截取过的/***found***/标记
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return;
												//字符串被删改 位置需从新寻找
		strAnswer.Delete(nAsEnd,11);
												//删除答案字符串中已截取过的/***end***/标记

		strCheck.Delete(nCKBegin,13);
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return;
		strCheck.Delete(nCKEnd,11);
		                                        //如上删除的检测题中的标记标记			
	}
	CString strFileName;
	strFileName.Format(_T("check\\%d_fill.cpp"),p);
												//文件名含路径字符串
	try
	{
		CFile outFile(strFileName,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write((LPCTSTR)strCheck,sizeof(char)*strCheck.GetLength());
		outFile.Close();
												//将插入完成的检测字符串写入文件,以待被检测
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	//写入一个文件 如果用序列化，文件开头有乱码 暂不知为何 等搞懂了 再用序列化
	CString strB;
strB.Format("cd check \r\n \
call VCVARS32.BAT \r\n \
cl %d_fill.cpp \r\n \
link %d_fill.obj \r\n \
%d_fill.exe",p,p,p,p);												//批处理文件的内容
	try
	{
		CFile fillBat("check\\Check.bat",CFile::modeReadWrite|CFile::modeCreate);
		fillBat.Write(strB,sizeof(char)*strB.GetLength());
		fillBat.Close();
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
        return;
	}

	WinExec("check\\Check.bat",SW_HIDE);
											//开进程执行批处理,进程以隐藏方式运行
    
}

BOOL CFill::CheckOver(int n)
{
	CString str;
	CFile value;
	CFileException e;
	if(value.Open("check\\answer.txt",CFile::modeRead,&e))				//把文件中的数据读入字符串。
	{
		char* buffur = new char[value.GetLength()+1];
		value.Read(buffur,value.GetLength()*sizeof(char));
		buffur[value.GetLength()] = 0;							
		str = buffur;
		delete []buffur;
		
	}
	else
		return FALSE;

	CString strSQL;
	strSQL.Format("select * from fill where fnum='%d'",n);
	CString strOut;

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);


        if(m_pRecordset->GetCollect("fout").vt != VT_NULL)
		     strOut = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout");
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	if(strOut.Compare(str)==0)
		return TRUE;
	else
		return FALSE;

}