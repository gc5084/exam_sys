if EXISTS
(
   select * 
   from master.dbo.sysdatabases 
   where name = 'TestData'
)
begin
      use master; /*��ֹ����ʹ���޷�ɾ��*/
     
      drop database TestData
end
GO


/*�������ݿ�*/
Create Database TestData
ON (
  NAME = 'TestData_data',   --�������ļ����߼���
  FILENAME = 'F:\TestSystem\TestData_data.mdf' ,  --�������ļ���������
  SIZE = 10 MB,  --�������ļ���ʼ��С
  FILEGROWTH = 20%    --�������ļ���������
) 
LOG ON 
 (NAME = 'TestData_log', 
  FILENAME = 'F:\TestSystem\TestData_log.ldf' ,
  SIZE = 3MB, 
  MAXSIZE = 10MB,
  FILEGROWTH = 10%
)

Go
USE [TestData]
                       /*�������ݿ�TestData*/
GO

create table fill
(
  fnum     char(10) primary key,   /*������ ���� */
  ftitle   text,	           /*����˵��*/                
  fcontent text, 		   /*�������� Դ��*/
  fanswer  text,                   /*������ȷ��*/
  fcheck   text,                   /*����������� ������������Ե�һ��Դ��*/
  fout     text,                   /*������� ��Ϻú����ȷ���*/
  fremark  text                   /*���ⱸ��*/
);

GO

create table modify
(
  fnum     char(10) primary key,   /*������ ���� */
  ftitle   text,	           /*����˵��*/                
  fcontent text, 		   /*�������� Դ��*/
  fanswer  text,                   /*������ȷ��*/
  fcheck   text,                   /*����������� ������������Ե�һ��Դ��*/
  fout     text,                   /*������� ��Ϻú����ȷ���*/
  fremark  text                   /*���ⱸ��*/
);

GO

create table design
(
  fnum     char(10) primary key,   /*������ ���� */
  ftitle   text,	           /*����˵��*/                
  fcontent text, 		   /*�������� Դ��*/
  fanswer  text,                   /*������ȷ��*/
  fcheck   text,                   /*����������� ������������Ե�һ��Դ��*/
  fout     text,                   /*������� ��Ϻú����ȷ���*/
  fremark  text                   /*���ⱸ��*/
);