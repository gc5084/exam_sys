/////////////////////////////////////////////////////////////////////
//������CStuInfor
//˵����������Ϣ��
//���ܣ����浥��������������Ϣ�Ͷ���Щ��Ϣ�Ĳ���     
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////
class CStuInfor
{
public:

	char*   strNum;//ѧ��
									
	char*   strName;//����
									
	int     nState;//״̬ ��0δ��¼ 1���� 2���� 3�쳣 4�ÿ�������Ϊ��ֹ����        
									
	SOCKET  sock;//ѧ����Ӧ�׽���  
										
//	int     nRandFill[3];//ѧ��������������������
									
//	int     nRandModify[3];//ѧ���������Ĵ���������
									
//	int     nRandDesign[3];//ѧ��������������������
	int		testPackIndex; //���������������

	int		passTime;   //����ʣ��ʱ��
									
	char*   StuAnswerFill[3];//ѧ���Ͻ���������

	char*   StuAnswerModify[3];//ѧ���Ͻ��ĸĴ����

	char*   StuAnswerDesign[3];//ѧ���Ͻ���������

	int     StuCorrectFill[3];//ѧ��������Ͻ����Ƿ���ȷ��־    1����ȷ 2�Ǵ��� 0��û������
    
	int     StuCorrectModify[3];//ѧ���Ĵ����Ͻ����Ƿ���ȷ��־

	int     StuCorrectDesign[3];//ѧ��������Ͻ����Ƿ���ȷ��־

	int     nAllPoint; //��¼ѧ�����ܷ�
protected:
	CString m_strTemp;//��ʱ�ַ��� ���ڴ�����ϵļ��� ��Խ��ͬ�ĺ���
	char*   m_szPath;  //���浱ǰ·��
public:
	CStuInfor();

	void ReState(); //����״̬

	void CheckAllAnswer();

	BOOL CheckOne(int nTestClass,int nTestNum);

	BOOL CheckOne(char* czAnswer,char* czCheck,char* czCheckOut);

	char* GetTestStr(int nTest,int nIndex,int Item);

	BOOL AnswerCorrect(char* czCheckOut);

	BOOL ReadTestFile();

	

protected:

    BOOL ComboAnswer(char* czAnswer,char* czCheck);
	void MakeAllPoint();
	


};