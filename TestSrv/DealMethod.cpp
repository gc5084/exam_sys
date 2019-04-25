// DealMethod.cpp: implementation of the CDealMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DealMethod.h"
#include "SrvMainWnd.h"
#include "SrvMyApp.h"
#include "StuInfor.h"
#include "MySocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CStuInfor* arrStu[MAXNUM];
extern int GStartTime;
extern int GTestTime;	
extern SendTestData g_sendTestData[MAXNUM];

CDealMethod::CDealMethod()
{

}

CDealMethod::~CDealMethod()
{

}

/*���������߿�����������*/
BOOL CDealMethod::SendAllStuTest()
{
	
	//�������ļ���
	CString  strNewFolderPath = "C:\\AllTest";
	if(::CreateDirectory(strNewFolderPath,NULL) == 0)//����NULL ָ������д��ļ��оͲ������ļ���
	{
		//ɾ���ļ���
		::system("rd/s/q C:\\AllTest");

	}
	::CreateDirectory(strNewFolderPath,NULL);//���ɾ�����ʹ����ļ��� ûɾ����������Ҳ�޷�

	int NowStudentIndex;
	for(NowStudentIndex = 0;NowStudentIndex<MAXNUM;NowStudentIndex++)
	{
		
		m_CurrentFolder.Format("C:\\AllTest\\K%d\\",NowStudentIndex);
		::CreateDirectory(m_CurrentFolder,NULL); //����NULL ָ������д��ļ��оͲ������ļ���
		if(SendTest(NowStudentIndex) == FALSE)
			return FALSE;
		
	}
	return TRUE;
}

/*����2����Ϣ ����ȷ����Ϣ*/
BOOL CDealMethod::DealNumberSure(char* czRecvPage,SOCKET sock)
{

	//����ѧ���ҵ�����
	int NowStudentIndex;
	NowStudentIndex = SearchStuIndex(&czRecvPage[SOCKHEAD]);

/*
	//��������
	int nFlag = CMainWindow::nFlag;
	if(nFlag&FLAG_TIMEGO == 1)   //�����Ѿ���ʱ��ʼ �������� ���û��ʼ�ͽ�����ʱ��
	{
		if(SendTest(NowStudentIndex,sock) == FALSE)
		{
			return FALSE;
		}
	}
*/

	arrStu[NowStudentIndex]->nState = 1; //������״̬��Ϊ����
			
    arrStu[NowStudentIndex]->sock = sock;//������׽����ڿ�����Ϣ����
	//����ʱ��
	if(SendTime(sock) == FALSE)
		return FALSE;

	//���Ŀ���״̬
		

		
	return TRUE;

}

/*����3����Ϣ ����������Ϣ*/
BOOL CDealMethod::TestOver(SOCKET sock)
{
	//�ҵ��ÿ���
	int NowStudentIndex;
	NowStudentIndex = this->SearchStuIndex(sock);

	//������״̬��дΪ����
	if((NowStudentIndex>=0)&&(NowStudentIndex<MAXNUM)) //��֤������ȷ
	{
		arrStu[NowStudentIndex]->nState = 2; //״̬��дΪ����
	}

	//������������ļ����� �ڴ�
	arrStu[NowStudentIndex]->ReadTestFile();

	//���������ͽ���ɹ���Ϣ
	CMySocket mysock;
	if(mysock.MySend(sock,NULL,19,1) == FALSE)
	{
		arrStu[NowStudentIndex]->nState = 3; //״̬��дΪ�쳣
		return FALSE;
	}

	return TRUE;

}

/*����20����Ϣ ����������Ϣ*/
BOOL CDealMethod::DealRequestTest(SOCKET sock)
{
	/*
	//�����׽����ҵ�ѧ������
	int NowStudentIndex;
	NowStudentIndex = SearchStuIndex(sock);

	//��������
	if(SendTest(NowStudentIndex) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
	*/
	return TRUE;
}








BOOL CDealMethod::SendTime(SOCKET sock)
{
	char SendBuf[4];
	int NowStudentIndex = SearchStuIndex(sock);
	int passTime = arrStu[NowStudentIndex]->passTime;

	SendBuf[0] = passTime+1;
	//ʱ���1 �Է�ֹʱ��Ϊ0ʱ���ض��ַ���
	SendBuf[1] = GTestTime;  //������ʱ��
	
	int nFlag = CMainWindow::nFlag;
	if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO)
		SendBuf[2] = 1;
	else
		SendBuf[2] = 2;
	//����ʱ����Ϣ�а��� �����Ƿ��ʱ��ʼ��Ϣ
	SendBuf[3] = 0;//������
	
	CMySocket mysock;
	if(mysock.MySend(sock,SendBuf,15,1) == FALSE) //����ʱ����Ϣ
	{
		return FALSE;
	}
		
	return TRUE;
	
}

BOOL CDealMethod::SendTime(int NowStudentIndex)
{
	return TRUE;
}

BOOL CDealMethod::TestPackIndex(int pack,SOCKET sock)
{
	int stuIndex =  SearchStuIndex(sock);
	int packIndex = pack - 1; //�ڷ�����д���ļ�ʱ��1��
	if(packIndex>=0 && packIndex<MAXNUM)
	{
		arrStu[stuIndex]->testPackIndex = packIndex;
	}
	else
	{
		AfxMessageBox("���ܵ��������Ų��ٷ�Χ��");
		return FALSE;
	}
	return TRUE;
	
}

/*���¿���ʱ�亯��*/
BOOL CDealMethod::TiemUpdata(int time,SOCKET sock)
{
	int stuIndex =  SearchStuIndex(sock);

	arrStu[stuIndex]->passTime = time;

	return TRUE;

}



////////////////////////////////////////////////////////////////////////////////]
//�������� 

/*����ѧ���ҵ�ѧ����������*/
int CDealMethod::SearchStuIndex(char* czStuNumber)
{
	int NowStudentIndex = 0; //������0 
	while(NowStudentIndex<MAXNUM)
	{
		if(arrStu[NowStudentIndex] != NULL)
		{
			if(strcmp(czStuNumber,arrStu[NowStudentIndex]->strNum)== 0)
				break; //�ҵ���������ѭ��
		}
		NowStudentIndex++;
	}
	if(NowStudentIndex > MAXNUM)  //��ѭ������Ϊ�ۼӱ������������� ��δ�ҵ�����
	{
		return -1; //ֱ��return �Ͳ��������׽��ָֻ������� �������쳣 
	}

	return NowStudentIndex;
}



/*�����׽����ҵ�ѧ����������*/
int CDealMethod::SearchStuIndex(SOCKET sock)
{
	int NowStudentIndex = 0; //������0 
	while(NowStudentIndex<MAXNUM)
	{
		if(arrStu[NowStudentIndex] != NULL)
		{
			if(arrStu[NowStudentIndex]->sock == sock)
				break; //�ҵ���������ѭ��
		}
		NowStudentIndex++;
	}
	if(NowStudentIndex > MAXNUM)  //��ѭ������Ϊ�ۼӱ������������� ��δ�ҵ�����
	{
		return -1; //ֱ��return �Ͳ��������׽��ָֻ������� �������쳣 
	}

	return NowStudentIndex;
}




/*��������Ӧѧ����������*/
BOOL CDealMethod::SendTest(int NowStudentIndex)
{
	//����������
	if((NowStudentIndex>MAXNUM)||(NowStudentIndex<0))
	{
		return FALSE;
	}
	//��䴢���������������Ķ�ά����
	int TestRand[3][3];  //����һ����ά����
	
	for(int i=0;i<3;i++)
	{
		TestRand[0][i] = g_sendTestData[NowStudentIndex].nRandFill[i];
		TestRand[1][i] = g_sendTestData[NowStudentIndex].nRandModify[i];
		TestRand[2][i] = g_sendTestData[NowStudentIndex].nRandDesign[i];
	}
	
	//�������������ļ������⣩
	int type,order;
	MemoryData TempData;
	CString Desfilename;
	CString filename;

	for(type=0; type<3; type++)
		for(order=0; order<3; order++)
		{
			if(TestRand[type][order] != -1) //�ÿ����и����� ����
			{

				//����Ӧ������ȡ��������� TempData ��д���ļ�
				switch(type)
				{
				case 0:
					TempData = listTestFill.GetAt(
						listTestFill.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesFill%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Fill%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				case 1:
					TempData = listTestModify.GetAt(
						listTestModify.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesModify%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Modify%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				case 2:
					TempData = listTestDesign.GetAt(
						listTestDesign.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesDesign%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Design%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				}
				
			}
			
		}
		//д��Index�ļ�
		char content[2];
		content[0] = NowStudentIndex+1 ;content[1] = 0;

		filename = "Index";
		filename = m_CurrentFolder + filename;
		this->CreateTestFile(filename,content);

		return TRUE;
		
}

/*��ָ���ļ���������д���ļ���*/
BOOL CDealMethod::CreateTestFile(CString fileName,char* fileContent)
{

	try
	{
		CFile outFile(fileName,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write(fileContent,strlen(fileContent));
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

