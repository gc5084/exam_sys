/////////////////////////////////////////////////////////////////////
//������CMyApp
//˵����Ӧ�ó�����
//���ܣ�����Ӧ�ó��������         
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////
#ifndef MYAPP_H_
#define MYAPP_H_

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	WSADATA wsaData;

};

/////////////////////////////////////////////////////////////////////
//������MemoryData
//˵����������
//���ܣ�����������Ϣ        
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////

class MemoryData
{
public:
	MemoryData(){TestTitle = NULL;TestContent = NULL;}
	char* TestTitle;
									//�������ָ��
	char* TestContent;
									//��������ָ��
	char* Check;

	char* PrimaryKey;

	char* CorrectAnswer;

	char* CheckOut;

	char* Remark;
};

/////////////////////////////////////////////////////////////////////
//SendTestData
//˵��������������Ϣ��
//���ܣ���������������        
//���ߣ�����(gc5084@163.com)
//��֯��
//���ڣ�2010.05
//////////////////////////////////////////////////////////////////////
class SendTestData
{
public:
	SendTestData() //����������Ҫ -1����û�г��������
	{
		int n;
		for(n=0;n<3;n++)
		{
			nRandFill[n] = -1;
			nRandModify[n] = -1;
			nRandDesign[n] = -1;
		}
	};

	int nRandFill[3];
	int nRandModify[3];
	int nRandDesign[3];
};

#endif