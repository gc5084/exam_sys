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
	              //��¼������
	CString strTil;
	              //��¼����ժҪ
	CString strRem;
 	              //��¼���ⱸע
	CString strAdd;
	              //��¼Ҫ��ʾ��������¼
	int nCircle = 0;
    
	pList->SendMessage(WM_SETREDRAW,FALSE,0);
	              //�ػ���Ч ��ֹ����
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
			                     //������ǿ�ֵ����CString���� ����������쳣

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
	                                          //��������ǰ �ָ��ػ�
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
		values ('%d','���ޱ���','������������','�ޱ�ע','���޴�');",p);
		           
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
												//������ַ��� ������ַ��� ��ʱ�ַ���
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
												//�Դ�Ϊ�𰸽�ȡ��ʼ�� ������ ��������ӵ� ������

	CString strSQL;
	strSQL.Format("select * from modify where fnum='%d'",p);
												//ָ����ŵĽ�����������
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
												//��ʼ��com�������ָ����¼��

        if(m_pRecordset->GetCollect("fanswer").vt != VT_NULL)
		     strAnswer = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fanswer");
												//���������ַ���
		if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)
		     strCheck = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck");
												//�������������ַ���
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
												//��ȡ�𰸺ͼ���е���ʼ����

        temp = strAnswer.Left(nAsEnd);
												//��ȡ��һ��/***end***/����벿��
		temp = temp.Right(nAsEnd - nAsBegin - 13);
												//��ȡtemp���Ұ벿 ��ȡ���� 13Ϊ/***found***/�ĳ���

		strCheck.Insert(nCKEnd,temp);
												//�����ľ��Ӧλ��
		strAnswer.Delete(nAsBegin,13);
												//ɾ�����ַ������ѽ�ȡ����/***found***/���
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return;
												//�ַ�����ɾ�� λ�������Ѱ��
		strAnswer.Delete(nAsEnd,11);
												//ɾ�����ַ������ѽ�ȡ����/***end***/���

		strCheck.Delete(nCKBegin,13);
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return;
		strCheck.Delete(nCKEnd,11);
		                                        //����ɾ���ļ�����еı�Ǳ��			
	}
	CString strFileName;
	strFileName.Format(_T("check\\%d_fill.cpp"),p);
												//�ļ�����·���ַ���
	try
	{
		CFile outFile(strFileName,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write((LPCTSTR)strCheck,sizeof(char)*strCheck.GetLength());
		outFile.Close();
												//��������ɵļ���ַ���д���ļ�,�Դ������
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	//д��һ���ļ� ��������л����ļ���ͷ������ �ݲ�֪Ϊ�� �ȸ㶮�� �������л�
	CString strB;
strB.Format("cd check \r\n \
call VCVARS32.BAT \r\n \
cl %d_fill.cpp \r\n \
link %d_fill.obj \r\n \
%d_fill.exe",p,p,p,p);												//�������ļ�������
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
											//������ִ��������,���������ط�ʽ����
    
}

BOOL CModify::CheckOver(int n)
{
	CString str;
	CFile value;
	CFileException e;
	if(value.Open("check\\answer.txt",CFile::modeRead,&e))				//���ļ��е����ݶ����ַ�����
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