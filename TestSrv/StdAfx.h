#include <afxwin.h>         // MFC ����ͷ�ļ�
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxcmn.h>         // MFC support for Windows Common Controls �н������ؼ�
#include <afxmt.h>			// MFC �ٽ��������ͷ�ļ�
#include <Afxsock.h>		// MFC �׽��ֿ�ͷ�ļ�
#include <Afxtempl.h>       // ģ��ͷ�ļ� ʹ��CList��ʱ����
#include "resource.h"       // ������Դͷ�ļ�


#import "msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

#include "MyDataBase.h"
#define ID_TIME       1     //timerʱ��ID ��Ϊ1
#define WM_INFORPAINT (WM_USER + 101)
							//�����ж���Ϣ ���������ڵ��ػ�

const int FLAG_TEST  = 1;    //���������Ƿ���ر�־
const int FLAG_STU   = 2;    //���������Ƿ����
const int FLAG_TIME  = 4;    //����ʱ���Ƿ�����
const int FLAG_START = 8;    //�����Ƿ�������
const int FLAG_OVER  = 16;   //�����Ƿ����
const int FLAG_SAVE  = 32;   //������Ϣ�Ƿ񱣴���
const int FLAG_MUCHNUM = 64; //���������ѳ�
const int FLAG_TIMEGO= 128;  //������ʼ��ʱ

const int MAXNUM    = 80;   //�������
const int LINEW     = 5;    //�����߿� ������ʾ��Ϣ�ͱ��֮��Ŀ��
const int ROWCOUNT  = 8;    //һ����8��
const int COLCOUNT  = 10;   //һ����10��
const int CELLWIDTH = 16;   //ÿһ�����������15���ַ� ����16���ַ����
const int CELLHIGH  = 5;    //ÿһ������������3���ַ�  ����5���ַ��߶�

const int SOCKHEAD = 4;     //socket����ͷ����
const int ADDBUFFER	= 4;	//��ֹ�ַ���Խ�� ����new���ַ���ͳһ���

///////////////////////////////////�������ͻ�����Ϣ����const
const int Mess_TestPackIndex = 20;
const int Mess_Time = 15;
const int Mess_ConfirmNumber = 2;
const int Mess_TestOver = 3;