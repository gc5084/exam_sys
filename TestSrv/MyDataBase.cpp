// MyDataBase.cpp: implementation of the CMyDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SrvMyApp.h"
#include "MyDataBase.h"
#include "StuInfor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CStuInfor* arrStu[80];
										

CMyDataBase::CMyDataBase()
{
	//��ʼ��com����
	::CoInitialize(NULL);
	//��ʼ�����Ӷ���
	m_pConnection.CreateInstance(__uuidof(Connection));
	//��ʼ����¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
		
}

CMyDataBase::~CMyDataBase()
{

}

//����SQL���ݿ�
BOOL CMyDataBase::ConnectSQL()
{
	CString str;
	str.Format("Provider=SQLOLEDB.1;Persist Security Info=False;\
		Integrated Security=SSPI;Data Source=.;database=TestData");
	try
	{
		if(m_pConnection->State)
		{
			m_pConnection->Close();
		}
		
		m_pConnection->Open((_bstr_t)str,"","",adModeUnknown);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	

	return TRUE;
}

//�ر�SQL���ݿ�
BOOL CMyDataBase::CloseSQL()
{
	try
	{
		if(m_pConnection->State)
		{
			m_pConnection->Close();
			return TRUE;
		}
		return FALSE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	

}

BOOL CMyDataBase::ConnectExcel(CString strPathName)
{
	try
	{

		if(m_pConnection->State)
		{
			m_pConnection->Close();
		}
		CString str,strSQL;
	    str.Format("Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Data Source=%s;Extended Properties=Excel 8.0;",strPathName);
		//ִ������
		m_pConnection->Open((_bstr_t)str,"","",adModeUnknown);

	}

	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}

BOOL CMyDataBase::CloseExcel()
{
	return TRUE;
}

int CMyDataBase::LoadTest()
{
	CString strSQL;
	char* czTemp;
	int   nTemp;
	MemoryData TempData;			//����������Ϣ�Ľṹ

	try
	{
		//�������ݿ�
		ConnectSQL();

//���������
		strSQL.Format("select * from fill;");
		if(m_pRecordset->State)
			m_pRecordset->Close();

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;

			//����ľ����
			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			//��䱸ע
			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestFill.AddTail(TempData);
								//��Ϊ�����������
			m_pRecordset->MoveNext();
			nTemp++;
		}

//����Ĵ���
		strSQL.Format("select * from modify;");
		if(m_pRecordset->State)
			m_pRecordset->Close();
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;


			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestModify.AddTail(TempData);
								//��Ϊ�����������
			m_pRecordset->MoveNext();
			nTemp++;
		}

//���������
		strSQL.Format("select * from design;");
		if(m_pRecordset->State)
			m_pRecordset->Close();

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;


			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestDesign.AddTail(TempData);
								//��Ϊ�����������
			m_pRecordset->MoveNext();
			nTemp++;
		}


		if(m_pRecordset->State)
			m_pRecordset->Close();
	}

	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	//�ر����ݿ�
	CloseSQL();
	return TRUE;
}
/*
����ѧ�����ѧ����Ϣ����
*/
BOOL CMyDataBase::LoadStudent()
{
	CString strSQL;
	strSQL.Format("select * from student;");
	int n = 0;					//����arrStu����������
    char* czTemp;
	
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		
		
		if(m_pRecordset->State)
			m_pRecordset->Close();
		
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0)
		{
			arrStu[n] = new CStuInfor;
			if(m_pRecordset->GetCollect("snum").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("snum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("snum"));
				arrStu[n]->strNum = czTemp;
			}				
			else
				arrStu[n]->strNum = NULL;
			
			
			if(m_pRecordset->GetCollect("sname").vt != VT_NULL)
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("sname"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("sname"));
				arrStu[n]->strName = czTemp;
				
			}
			else 
				arrStu[n]->strName = NULL;
			
		 		n++;
														//������һ
			if(n >= MAXNUM)
				break;
									//������MAXNUMʱ�˳���ѭ�������ѧ�����飩 
			m_pRecordset->MoveNext();
		}

		nStudent = n;//�����ж��ٸ�ѧ��

		while(n < MAXNUM)           //���û�е�MAXNUM�������ʣ���ѧ������
		{
			arrStu[n] = NULL;
			n++;
		}
		if(m_pRecordset->State)
			m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return nStudent;
		
}

BOOL CMyDataBase::LoadStudentExcel()
{
	CString strSQL;
	strSQL.Format("select * from [Sheet1$];");//[Sheet1$],
	int n = 0;					//����number��name����������
	int i,j;//��ʱѭ������
    char* czTemp;

	//��������ָ������ Ϊ���ݴ�ѧ�ź����� 
	//�Ȱ�ѧ�ź����������� ����ѧ�����ظ�����ʾȻ��ɾ��new���Ļ����������ش���
	//��������ѧ���ظ�����ʱ�Ϳ��Բ�����arrStu��������
	char* number[MAXNUM];
	char* name[MAXNUM];
	//��ʼ��Ϊ��
	//memset(number,NULL,MAXNUM);
	//memset(name,NULL,MAXNUM);
	for(i=0;i<MAXNUM;i++)
	{
		number[i] = NULL;
		name[i]   = NULL;
	}

	
	try
	{
		
		if(m_pRecordset->State)
			m_pRecordset->Close();
		//ִ�м�¼���Ĵ򿪲���
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		while(m_pRecordset->adoEOF == 0)
		{
			//���뿼��ѧ�� 
			if(m_pRecordset->GetCollect("number").vt != VT_NULL)//����Ƿ�� ����������쳣
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("number"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("number"));
				number[n] = czTemp;
				//���ѧ���Ƿ����ظ� 
				for(j=0;j<MAXNUM;j++)
				{
					if(n != j)
					{
						//�뵱ǰѧ����Ȳ��Ҳ���ͬһ������λ�� ��ѧ�����ظ�
						if(strcmp(number[n],number[j])==0)
						{
							CString strShow;
							strShow.Format("%s �������ظ� ���޸ĺ��ټ��أ�",number[n]);
							AfxMessageBox(strShow);
							//�ͷŻ�����
							for(i =0;i<MAXNUM;i++)
							{
								delete[] number[i];
								delete[] name[i];
							}
							return FALSE;
						}
					}
					else
						break;
					//���ѧ��ָ�����鵱ǰ��������ѭ������ ����Ķ�Ϊ�� ������ ����ѭ��
				}
			}				
			else
			{
				//�ͷŻ�����
				for(i =0;i<MAXNUM;i++)
				{
					delete[] number[i];
					delete[] name[i];
				}
				AfxMessageBox("����ѧ�Ų���Ϊ�գ����޸ĺ���������");
				return FALSE;
			}
			
			//���뿼������
			if(m_pRecordset->GetCollect("name").vt != VT_NULL)
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("name"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("name"));
				name[n] = czTemp;
				
			}
			else
			{
				for(i =0;i<MAXNUM;i++)
				{
					delete[] number[i];
					delete[] name[i];
				}
				AfxMessageBox("������������Ϊ�գ����޸ĺ���������");
				return FALSE;
			}
			//������һ
			n++;
			if(n >= MAXNUM)
				break;
				//������MAXNUMʱ�˳���ѭ�� 
			m_pRecordset->MoveNext();
		}

		nStudent = n;//�����ж��ٸ�ѧ��

		//����ջ�е�ѧ�� ���� ָ������ ���뵽arrStu������
		for(i = 0; i<MAXNUM; i++)
		{
			if(number[i] != NULL)
			{
				//������ �������ѧ�ź�����
				arrStu[i] = new CStuInfor();
				arrStu[i]->strNum  = number[i];
				arrStu[i]->strName = name[i];
			}
			else
				break;
			    //��numberѭ������ʱ˵��������Ϣ���� ����ѭ��ֹͣ����CStuInfor��
		}
		//��ʱ����
        //strSQL.Format("insert into [Sheet1$] values('0610014188','�¹�')");
		
		//�رռ�¼������
		if(m_pRecordset->State)
			m_pRecordset->Close();

	//	strSQL.Format("alter table student add  remark int;");//[Sheet1$]
	//	strSQL.Format("create table ttt(aa char(3),bb char(3));");
	//	m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}

	catch(_com_error e)
	{
		AfxMessageBox("Excel���ݲ����ϱ�׼");
		return FALSE;
	}

	return nStudent;
		
}

/*
�ر������ݿ������
*/
BOOL CMyDataBase::CloseDataBase()
{
	try
	{
		if(m_pConnection->State)
			m_pConnection->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;

}


/*���������excel*/
BOOL CMyDataBase::OutExcel(CString strPathName)
{
	//����Excel
	if(ConnectExcel(strPathName) ==FALSE)
	{
		return FALSE;
	}

	//�������
	CString strSQL;
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			//��ʽ��Ҫִ�е�SQL���
			strSQL.Format(
				"insert into [Sheet1$] values('%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d' ,'%d')",
				arrStu[n]->strNum,arrStu[n]->strName,
				arrStu[n]->StuCorrectFill[0],arrStu[n]->StuCorrectFill[1],arrStu[n]->StuCorrectFill[2],
				arrStu[n]->StuCorrectModify[0],arrStu[n]->StuCorrectModify[1],arrStu[n]->StuCorrectModify[2],
				arrStu[n]->StuCorrectDesign[0],arrStu[n]->StuCorrectDesign[1],arrStu[n]->StuCorrectDesign[2],
				arrStu[n]->nAllPoint);
			try
			{
				m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText); //ִ�����Ԫ�����
			}
			catch(_com_error e)
			{
				return FALSE;
			}
		}
		
		
	}

	CloseSQL(); //�ر����ݿ�
	return TRUE;
}