/////////////////////////////////////////////////////////////////////
//������CMainWindow
//˵����������������
//���ܣ��������������� ��Ӧ�����ڵ������¼�
//      ��Ӧ�˵� ������Ϣ ����ĺ�����        
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////
#ifndef MAINWND_H_
#define MAINWND_H_

class CMainWindow : public CWnd
{
public:
	CMainWindow();
				  //�����ڴ��ھ�� ����Ϊ��̬����Ϊ�����߳�Ҫ��
				  //��������ʱ��
   static int     nFlag;
	             //��־λ
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcreatestruct);
	afx_msg void OnStart();
	afx_msg void OnPaint(); 
	afx_msg void OnClose();
	afx_msg void OnPerson();
	afx_msg BOOL OnSetTime();
	afx_msg void OnConCheck();
	afx_msg void OnConStuInfo();
	afx_msg void OnConForbid();
	afx_msg void OnConRestate();
	afx_msg void OnConSend();


	afx_msg void OnInforPaint(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReset();
	afx_msg void OnExitTest();
	afx_msg BOOL OnLoadStu();
	afx_msg void OnRePaint();
	afx_msg void OnForbid();
	afx_msg void OnSendInfor();
	afx_msg void OnCheckAll();
	afx_msg void OnCheckSave();
	afx_msg void OnCheckShow();
	afx_msg void OnHelpAbout();
	afx_msg void OnLock();
	afx_msg void OnOutExcel();
	afx_msg void OnToolData();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	BOOL  InitMySocket();
	void  DrawInfor(CDC* pDC);
	void  DrawClient(CDC* pDC);
//	BOOL  LoadStuInfor();
	BOOL  LoadTestFirst();
	void  SetStartTime();
	void  RandStu();
	void  ReStart();
protected:
	int				m_cxChar;						  //��������
	int				m_cyChar;			              //������߶�
	CRect			m_rcClient;                       // ����Ϣ�ͻ���
	CRect           m_rcInfor;                        //��ʾ��Ϣ�ͻ���
	CRect			m_rcPaint;                        //�����ػ�ͻ���
	SOCKET			m_LisSock;						  //�����׽���������
	CFont			m_fontMain;                       //������  
	CRect			Arect[80];						  //80������Ϣ���ľ�������
	CWinThread*     m_threadAccept;					  //���������̵߳ľ��
	CWinThread*     m_threadSelect;					  //Select�̵߳ľ��
	int             PassedRect;                       //��¼��һ����ǰ��

public:

	int             nRightDown;						  //��¼���Ҽ�����ʱ���ڵ�����
	CMyDataBase     m_DataBase;						  //���ݿ���
	int             nMuchTest[3];                     //��¼���ο���ÿ���������
	CString         Password;                         //�洢����Ӧ�ó��������





DECLARE_MESSAGE_MAP()
};

#endif