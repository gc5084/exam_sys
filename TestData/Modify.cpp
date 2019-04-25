// Modify.cpp: implementation of the CModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testdata.h"
#include "Modify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModify::CModify(_ConnectionPtr  m_pConnection):CBase(m_pConnection)
{

}

CModify::~CModify()
{

}

BOOL CModify::Show(CEdit* pEdit,int nIndex,CString str)
{
	CString strSQL;
	strSQL.Format("select * from modify where fnum='%d'",nIndex);

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);


        if(m_pRecordset->GetCollect((LPCTSTR)str).vt != VT_NULL)
		    pEdit->SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect((LPCTSTR)str));
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
	
}

BOOL CModify::List(CListBox* pList)
{
	CString strSQL;
	strSQL.Format("select * from modify;");
	CString strNum;
	              //记录试题编号
	CString strTil;
	              //记录试题摘要
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

BOOL CModify::Delete(int nIndex)
{
	CString strSQL;
	strSQL.Format("delete from Modify where fnum='%d';",nIndex); 
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

BOOL CModify::SetPcon(_ConnectionPtr  m_pCon)
{
	m_pConnection = m_pCon;
	return TRUE;
}

BOOL CModify::Input(CEdit* pEdit,int nIndex,CString str)
{   
	CString strtext;
	pEdit->GetWindowText(strtext);
    strtext.Replace("'","''");

	CString strSQL;
	strSQL.Format("update Modify set %s = '%s' where fnum = '%d'",str,strtext,nIndex);

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

int  CModify::account()
{
	CString strSQL;
	strSQL.Format("select * from Modify;");

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

int CModify::WhereIn()
{
	CString strSQL;
	strSQL.Format("select * from Modify;");

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

int CModify::NtoP(int n)
{
	CString strSQL;
	strSQL.Format("select * from Modify;");
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

BOOL CModify::CreateNew(int p)
{
   	CString strSQL;
	strSQL.Format("insert into Modify(fnum,ftitle,fcontent,fremark,fanswer) \
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
void CModify::Check(int p)
{
	CString strAnswer,strCheck,temp;	
												//定义答案字符串 检测题字符串 临时字符串
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
												//以此为答案截取起始点 结束点 检测题歧视点 结束点

	CString strSQL;
	strSQL.Format("select * from modify where fnum='%d'",p);
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
		if( (nCKBegin = strCheck.Find("/***found***/")) == -1)
			return;
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return;
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

BOOL CModify::CheckOver(int n)
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
	strSQL.Format("select * from modify where fnum='%d'",n);
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