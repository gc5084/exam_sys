#include "stdAfx.h"
#include "SrvMyApp.h"
#include "SrvMainWnd.h"
#include "MySocket.h"
#include "StuInfor.h"


extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CCriticalSection g_list;
extern CList<SOCKET,SOCKET> listSock;
extern SendTestData g_sendTestData[MAXNUM];
	
CStuInfor::CStuInfor()
{
	strNum = NULL;
	strName = NULL;
	nState  = 0;//��ʼ��Ϊδ��¼
	sock  = NULL;
	passTime = 0;
	testPackIndex = -1;
	for(int n=0;n<3;n++)
	{
		StuAnswerFill[n]    = NULL; 
		StuAnswerModify[n]  = NULL;
		StuAnswerDesign[n]  = NULL;
		StuCorrectFill[n]   = 0;//0Ϊ������ 1��ȷ 2 ����
		StuCorrectModify[n] = 0;
		StuCorrectDesign[n] = 0;
		nAllPoint           = 0;
		
	}
}

void CStuInfor::ReState()
{
	//ɾ����Ӧ�׽�����������
	if(nState == 1)//״̬Ϊ���߲�ɾ�� ���ѽ���״̬ �Ѿ����׽�����������ɾ����
	{
		g_list.Lock();
	    listSock.RemoveAt(listSock.Find(sock));
	    g_list.Unlock();
	}
	sock  = NULL;

	for(int n=0;n<3;n++)
	{
		//ɾ��ѧ����������
		delete[] StuAnswerFill[n];
		StuAnswerFill[n]    = NULL; 

		delete[] StuAnswerModify[n];
		StuAnswerModify[n]    = NULL; 

		delete[] StuAnswerDesign[n];
		StuAnswerDesign[n]    = NULL; 

		//�ľ���ȫ����Ϊδ�ľ�
		StuCorrectFill[n]   = 0;//0Ϊ������ 1��ȷ 2 ����
		StuCorrectModify[n] = 0;
		StuCorrectDesign[n] = 0;
	}


	//��ʼ��Ϊδ��¼
	nState  = 0;
	//����ʱ����
	passTime = 0;
}

void CStuInfor::CheckAllAnswer()
{

	//��ȡ��ǰ·�����ڱ��濼��
	m_szPath = new char[100];
	::GetCurrentDirectory(100,m_szPath);
	//����һ��SrvCheck�ļ���
	CString  strDir = m_szPath;	
	strDir = strDir+"\\SrvCheck";
	::CreateDirectory(strDir,NULL); //�������ͬ���ļ��оͺ���ʧ�� 

	//ѭ���������
	for(int i = 0;i < 3;i++)
		for(int j =0;j<3;j++)
		{
			if((i==0)&&(g_sendTestData[testPackIndex].nRandFill[j] != -1))
				CheckOne(i,j);
			else if((i==1)&&(g_sendTestData[testPackIndex].nRandModify[j] != -1))
				CheckOne(i,j);
			else if((i==2)&&(g_sendTestData[testPackIndex].nRandDesign[j] != -1))
				CheckOne(i,j);

		}

	//�����ܷ�
	MakeAllPoint();

	delete[] m_szPath;//�ͷ��ļ���Դ
	m_szPath = NULL;

}


BOOL CStuInfor::CheckOne(int nTestClass,int nTestNum)
{
	char* czAnswer;
	char* czCheck;
	char* czCheckOut;

	switch(nTestClass)
	{
	case 0://�����
		switch(nTestNum)
		{
		case 0://��һ��
			czAnswer    = StuAnswerFill[0];
			if(g_sendTestData[testPackIndex].nRandFill[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[0],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[0],3);
			break;
		case 1://�ڶ���
			czAnswer = StuAnswerFill[1];
			if(g_sendTestData[testPackIndex].nRandFill[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[1],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[1],3);
			break;
		case 2://������
			czAnswer = StuAnswerFill[2];
			if(g_sendTestData[testPackIndex].nRandFill[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[2],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[2],3);
			break;
		}
        //����Բ���ֵ ������switch�� �������Ϳ���switch���� �ڼ�������nTestNum
		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectFill[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectFill[nTestNum] = 2;
			return FALSE;
		}
		
		break;


	case 1://�Ĵ���
		switch(nTestNum)
		{
		case 0://��һ��
			czAnswer = StuAnswerModify[0];
			if(g_sendTestData[testPackIndex].nRandModify[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[0],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[0],3);
			break;
		case 1://�ڶ���
			czAnswer = StuAnswerModify[1];
			if(g_sendTestData[testPackIndex].nRandModify[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[1],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[1],3);
			break;
		case 2://������
			czAnswer = StuAnswerModify[2];
			if(g_sendTestData[testPackIndex].nRandModify[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[2],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[2],3);
			break;
		}

		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectModify[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectModify[nTestNum] = 2;
			return FALSE;
		}
		break;


	case 2://�����
		switch(nTestNum)
		{
		case 0://��һ��
			czAnswer = StuAnswerDesign[0];
			if(g_sendTestData[testPackIndex].nRandDesign[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[0],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[0],3);
			break;
		case 1://�ڶ���
			czAnswer = StuAnswerDesign[1];
			if(g_sendTestData[testPackIndex].nRandDesign[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[1],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[1],3);
			break;
		case 2://������
			czAnswer = StuAnswerDesign[2];
			if(g_sendTestData[testPackIndex].nRandDesign[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[2],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[2],3);
			break;
		}

//		AfxMessageBox(czAnswer);
//		AfxMessageBox(czCheck);
//		AfxMessageBox(czCheckOut);
		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectDesign[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectDesign[nTestNum] = 2;
			return FALSE;
		}
		break;

	default:
			return FALSE;
	}
	
}

BOOL CStuInfor::CheckOne(char* czAnswer,char* czCheck,char* czCheckOut)
{
	//��ϳ������ַ���
	CString strCombo;
	if(ComboAnswer(czAnswer,czCheck) == FALSE)
		return FALSE;
	strCombo = m_strTemp;
//	AfxMessageBox(strCombo);

	
	//�������ַ���д�뵽ָ���ļ�
	CString strFileName = m_szPath;
	strFileName = strFileName + "\\SrvCheck";

	CString strCppPath = strFileName + "\\Test.cpp";//�ļ�����·���ַ���											
	try
	{
		CFile outFile(strCppPath,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write((LPCTSTR)strCombo,sizeof(char)*strCombo.GetLength());
		outFile.Close();
												//��������ɵļ���ַ���д���ļ�,�Դ������
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	//����������
	CString strBat;
     strBat.Format("cd SrvCheck \r\n call VCVARS32.BAT \r\n  cl Test.cpp \r\n link Test.obj \r\n Test.exe");

	 CString strBatPath = strFileName + "\\Check.bat"; //����������·��
    try
	{

		CFile fillBat(strBatPath,CFile::modeReadWrite|CFile::modeCreate);//SrvCheck
		fillBat.Write(strBat,sizeof(char)*strBat.GetLength());
		fillBat.Close();
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
        return FALSE;
	}
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	GetStartupInfo(&si);
	si.dwFlags    =STARTF_USESHOWWINDOW; //���Ӵ˾� �������ݷ�ʽִ��ʱ�������ؽ���
	si.wShowWindow=SW_HIDE;

	
	char *szBatPath = new char[strFileName.GetLength() + 11 +ADDBUFFER];
	szBatPath = strBatPath.GetBuffer(0);
	//AfxMessageBox(szBatPath);

	CreateProcess( NULL, // No module name (use command line). 
        szBatPath, // Command line. SrvCheck
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0, // No creation flags.CREATE_NO_WINDOW 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi );              // Pointer to PROCESS_INFORMATION structure.
	WaitForSingleObject(pi.hProcess,INFINITE);



	//�����ȷ��񲢷�����Ϣ
	if(AnswerCorrect(czCheckOut) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}




	return TRUE;
}

char* CStuInfor::GetTestStr(int nTest,int nIndex,int nItem)
{
	//�������� nTest��������  nIndex��������� nItem���ʲô����1�������2�ľ�����...
	POSITION pos;
	int n;

	switch(nTest)
	{
	case 0:
		pos = listTestFill.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestFill.GetNext(pos);
		}

		if(nItem == 1)//�����������
		{
			return listTestFill.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//�����ľ�����
		{
			return listTestFill.GetNext(pos).Check;
		}
		else if(nItem == 3)//�����ľ����
		{
			return listTestFill.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
		

	case 1:
		pos = listTestModify.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestModify.GetNext(pos);
		}
		
		if(nItem == 1)//�����������
		{
			return listTestModify.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//�����ľ�����
		{
			return listTestModify.GetNext(pos).Check;
		}
		else if(nItem == 3)//�����ľ����
		{
			return listTestModify.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
	case 2:
		pos = listTestDesign.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestDesign.GetNext(pos);
		}

		if(nItem == 1)//�����������
		{
			return listTestDesign.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//�����ľ�����
		{
			return listTestDesign.GetNext(pos).Check;
		}
		else if(nItem == 3)//�����ľ����
		{
			return listTestDesign.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
		break;
	default:
		return NULL;

	}
}


BOOL CStuInfor::ComboAnswer(char* czAnswer,char* czCheck)
{
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
	CString strAnswer = czAnswer;
	CString strCheck  = czCheck;
	CString temp;

	while(strAnswer.Find("/***found***/")!=-1)
	{
        nAsBegin = strAnswer.Find("/***found***/");
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return FALSE;
		//���ַ�������һ��/***found***/ ����һ��/***end***/ ����ͳ���Ҫ����
		if( (nCKBegin = strCheck.Find("/***found***/")) == -1)
			return FALSE;
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return FALSE;
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
			return FALSE;
												//�ַ�����ɾ�� λ�������Ѱ��
		strAnswer.Delete(nAsEnd,11);
												//ɾ�����ַ������ѽ�ȡ����/***end***/���

		strCheck.Delete(nCKBegin,13);
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return FALSE;
		strCheck.Delete(nCKEnd,11);
		                                        //����ɾ���ļ�����еı�Ǳ��	
	}
	m_strTemp = strCheck;
	return TRUE;
}

///��鿼������������ļ������Ƿ���ȷ
BOOL CStuInfor::AnswerCorrect(char* czCheckOut)
{
	CString strCorrect = czCheckOut;

    CString str;
	CFile value;
	CFileException e;
	if(value.Open("SrvCheck\\answer.txt",CFile::modeRead,&e))	//���ļ��е����ݶ����ַ�����
	{
		char* buffur = new char[value.GetLength()+1];
		value.Read(buffur,value.GetLength()*sizeof(char));
		buffur[value.GetLength()] = 0;							
		str = buffur;
		delete []buffur;
		
	}
	else
		return FALSE;


	if(str.Compare(strCorrect)==0)
		return TRUE;
	else
		return FALSE;


}



///�����ܷ�
void CStuInfor::MakeAllPoint()
{
	int nQuestion = 0;      //��¼����һ���м�����
	int nCorrectQue = 0;    //��¼����˼�����

	//ͳ��һ�����˼�����ʹ�Եĸ���
	for(int n=0;n<3;n++)
	{
		//�����
		if(g_sendTestData[testPackIndex].nRandFill[n] != -1) //�����Ų�Ϊ-1˵���������
		{
			nQuestion++; 
			if(StuCorrectFill[n] == 1)//��Ӧ������ȷ����ȷ����1
			{
				nCorrectQue++;
			}
		}
		//�Ĵ���
		if(g_sendTestData[testPackIndex].nRandModify[n] != -1) //�����Ų�Ϊ-1˵���������
		{
			nQuestion++; 
			if(StuCorrectModify[n] == 1)//��Ӧ������ȷ����ȷ����1
			{
				nCorrectQue++;
			}
		}
		//�Ĵ��� 
		if(g_sendTestData[testPackIndex].nRandDesign[n] != -1) //�����Ų�Ϊ-1˵���������
		{
			nQuestion++; 
			if(StuCorrectDesign[n] == 1)//��Ӧ������ȷ����ȷ����1
			{
				nCorrectQue++;
			}
		}
	}

	//���
	if(nCorrectQue == 0)   //û��һ���Ե�Ϊ0��
	{
		this->nAllPoint = 0;
	}
	else
	{
		int nPoint;
		nPoint = (int)( ((100.00/(float)nQuestion)*nCorrectQue)+1 ); //�ܷ�һ�� ��1Ϊ���ٳ�ǿת��int�Ĳ���ȷ
		                                 
		if(nPoint >= 100) //��Ϊ��1�˿��ܴ���100
			this->nAllPoint = 100;
		else
			this->nAllPoint = nPoint;
	}
}


/*��ȡ�������ļ����е�����*/
BOOL CStuInfor::ReadTestFile()
{
	CString folderPath;
	folderPath.Format("C:\\AllTest\\k%d\\",testPackIndex);


	char* Describe[3][3];
	//��ʼ���ļ���
	Describe[0][0] = "Fill0.cpp";
	Describe[0][1] = "Fill1.cpp";
	Describe[0][2] = "Fill2.cpp";

	Describe[1][0] = "Modify0.cpp";
	Describe[1][1] = "Modify1.cpp";
	Describe[1][2] = "Modify2.cpp";

	Describe[2][0] = "Design0.cpp";
	Describe[2][1] = "Design1.cpp";
	Describe[2][2] = "Design2.cpp";

	int i;
	//���
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[0][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			StuAnswerFill[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerFill[i],file.GetLength()*sizeof(char));
			StuAnswerFill[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerFill[i] = NULL;
		}
	}

	//�Ĵ�
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			StuAnswerModify[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerModify[i],file.GetLength()*sizeof(char));
			StuAnswerModify[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerModify[i] = NULL;
		}
	}

	//���
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //�򿪸������ļ�
		{
			StuAnswerDesign[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerDesign[i],file.GetLength()*sizeof(char));
			StuAnswerDesign[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerDesign[i] = NULL;
		}
	}

	return TRUE;
}