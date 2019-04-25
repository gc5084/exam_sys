// TestManage.cpp: implementation of the CTestManage class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestClient.h"
#include "TestManage.h"
#include "MySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CTestClientApp theApp;
extern SOCKET Gsock;

CTestManage::CTestManage()
{
	//��ȡ��ǰ·��
	this->m_szAppPath = new char[100];
	::GetCurrentDirectory(100,m_szAppPath);

	//���������������
	Describe[0][0] = "DesFill0";
	Describe[0][1] = "DesFill1";
	Describe[0][2] = "DesFill2";

	Describe[1][0] = "DesModify0";
	Describe[1][1] = "DesModify1";
	Describe[1][2] = "DesModify2";

	Describe[2][0] = "DesDesign0";
	Describe[2][1] = "DesDesign1";
	Describe[2][2] = "DesDesign2";
/*
	//��ǰ·������һ���ļ���
	CString  strNewFolderPath = m_szAppPath;	
	strNewFolderPath = strNewFolderPath+"\\Test";
	::CreateDirectory(strNewFolderPath,NULL); //����NULL ָ������д��ļ��оͲ������ļ���
	*/
}

CTestManage::~CTestManage()
{
}

/*��ȡ���������ļ�*/
void CTestManage::ReadDescribeFile()
{
	int i;
	//���
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[0][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			theApp.fill[i] = new char[file.GetLength()+1];
			file.Read(theApp.fill[i],file.GetLength()*sizeof(char));
			theApp.fill[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.fill[i] = NULL;
		}
	}

	//�Ĵ�
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			theApp.modify[i] = new char[file.GetLength()+1];
			file.Read(theApp.modify[i],file.GetLength()*sizeof(char));
			theApp.modify[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.modify[i] = NULL;
		}
	}

	//���
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[2][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			theApp.design[i] = new char[file.GetLength()+1];
			file.Read(theApp.design[i],file.GetLength()*sizeof(char));
			theApp.design[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.design[i] = NULL;
		}
	}
	//��������
	CString strFileName;
	strFileName = _T("K:\\Index");
	
	CFile file;
	if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
	{
		char* buffer = new char[file.GetLength()+1];
		file.Read(buffer,file.GetLength()*sizeof(char));
		buffer[file.GetLength()] = 0;
		
		int PackIndex;
		PackIndex = buffer[0]; //
		//������������
		CMySocket mysock;
		mysock.MySend(Gsock,NULL,Mess_TestPackIndex,PackIndex);

	}
	else
	{
		AfxMessageBox("��ȡ������ų��������Ƴ�");
		exit(0);
	}




}



BOOL CTestManage::InputText(char* Buffer)
{
	if(Buffer==NULL)
		return FALSE;
	switch(Buffer[SOCKHEAD-2])
	{
	case 5:	
	case 6:
	case 7:									//5-7���������
        if(Buffer[SOCKHEAD-1] == 1)			//1������� ���Ƶ����� ��theApp�������Ӧָ��
		{
			theApp.fill[Buffer[SOCKHEAD-2]-5] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.fill[Buffer[SOCKHEAD-2]-5],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.fill[Buffer[SOCKHEAD-2]-5]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2������������ ������ļ�
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	case 8:	
	case 9:
	case 10:								//8-10����Ĵ���
		if(Buffer[SOCKHEAD-1] == 1)			//1������� ���Ƶ����� ��theApp�������Ӧָ��
		{
			theApp.modify[Buffer[SOCKHEAD-2]-8] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.modify[Buffer[SOCKHEAD-2]-8],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.modify[Buffer[SOCKHEAD-2]-8]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2������������ ������ļ�
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	case 11:
	case 12:
	case 13:								//11-13���������
		if(Buffer[SOCKHEAD-1] == 1)			//1������� ���Ƶ����� ��theApp�������Ӧָ��
		{
			theApp.design[Buffer[SOCKHEAD-2]-11] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.design[Buffer[SOCKHEAD-2]-11],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.design[Buffer[SOCKHEAD-2]-11]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2������������ ������ļ�
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	default:
		AfxMessageBox("��Ϣ��־�쳣��");
		return FALSE;


	}
}

BOOL CTestManage::InputFile(char* Buffer,int MajorFlag)
{
	//���ļ���·���������
	CString strFilePath = this->m_szAppPath;
	strFilePath = strFilePath + "\\Test"; //��ǰ����·�������ļ����� ����ļ���·��

	CString strFileName; //�ļ���
	if(MajorFlag == 5||MajorFlag == 6||MajorFlag == 7)
		strFileName.Format("\\Fill%d.cpp",MajorFlag-5);	
	else if(MajorFlag == 8||MajorFlag == 9||MajorFlag == 10)
		strFileName.Format("\\Modify%d.cpp",MajorFlag-8);		
	else if(MajorFlag == 11||MajorFlag == 12||MajorFlag == 13)
        strFileName.Format("\\Design%d.cpp",MajorFlag-11);											
	else
	{
		AfxMessageBox("�ļ���־�쳣��");
		return FALSE;
	}                            //���ݲ�ͬ�ı�־ ��ʽ���ļ���

	
	strFilePath = strFilePath + strFileName; //��������ļ���

	try
	{
		CFile outFile(strFilePath,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write(Buffer,strlen(Buffer));
		outFile.Close();
												//��������ɵļ���ַ���д���ļ�,�Դ������
	}
	catch(CFileException* e)
	{
		AfxMessageBox("д���ļ��쳣��");
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	return TRUE;
}