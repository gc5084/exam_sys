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
��ʾ��Ϣ����
�ú�������Ϊ��ʵָ������Ŀ��Ϣ��ָ���ı༭�ؼ���
��һ������Ϊ�༭�ؼ���ָ�룬�ڶ�������Ϊ����ı�ţ����ݿ����ؼ��֣���
����������Ϊ�����е�����
*/
BOOL CFill::Show(CEdit* pEdit,int nIndex,CString str)
{
	CString strSQL;
	strSQL.Format("select * from fill where fnum='%d'",nIndex);

	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
															//��ʼ����¼��
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
                                                            //��ָ��SQL���򿪼�¼��

        if(m_pRecordset->GetCollect((LPCTSTR)str).vt != VT_NULL)
		    pEdit->SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect((LPCTSTR)str));
															//�жϼ�¼����Ӧ���Ƿ�ΪNULL 
															//��Ϊ���ڿؼ�����ʾ���� ����ؼ�д������Ϣ��
		else
			pEdit->SetWindowText(_T("����Ϣ"));
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
	
}
/*
�г����и�Ҫ��Ϣ��
����ΪCListBox�ؼ���ָ��
��Ҫ��Ϣ���� ������ ����˵��  ���ⱸע
*/


BOOL CFill::List(CListBox* pList)
{
	CString strSQL;
	strSQL.Format("select * from fill;");
	CString strNum;
	              //��¼������
	CString strTil;
	              //��¼����˵��
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
	                                          //��������ǰ �ָ��ػ�
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
�������Ӻ���
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
									//��'�滻��'' ��ֹSQL�䷨�Դ���

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
���һ���ж�������¼
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
�����¼�¼Ӧ�����λ��
��Ϊԭ��¼�е�Ԫ�鱻ɾ�� ��������������
������Ӧ����ȱ �������Ӧλ��
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
/*
��ȡ��Ӧ��������ϳ��ַ���
Ȼ��д����Ӧ�ļ�
д�������ļ� ���ִ��
*/
void CFill::Check(int p)
{
	CString strAnswer,strCheck,temp;	
												//������ַ��� ������ַ��� ��ʱ�ַ���
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
												//�Դ�Ϊ�𰸽�ȡ��ʼ�� ������ ��������ӵ� ������

	CString strSQL;
	strSQL.Format("select * from fill where fnum='%d'",p);
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
		//���ַ�������һ��/***found***/ ����һ��/***end***/ ����ͳ���Ҫ����
		if( (nCKBegin = strCheck.Find("/***found***/")) == -1)
			return;
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return;
		//����ַ�������һ��/***found***/ ����һ��/***end***/ ����ͳ���Ҫ����

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

BOOL CFill::CheckOver(int n)
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