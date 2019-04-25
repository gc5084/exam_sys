if EXISTS
(
   select * 
   from master.dbo.sysdatabases 
   where name = 'TestData'
)
begin
      use master; /*防止正在使用无法删除*/
     
      drop database TestData
end
GO


/*创建数据库*/
Create Database TestData
ON (
  NAME = 'TestData_data',   --主数据文件的逻辑名
  FILENAME = 'F:\TestSystem\TestData_data.mdf' ,  --主数据文件的物理名
  SIZE = 10 MB,  --主数据文件初始大小
  FILEGROWTH = 20%    --主数据文件的增长率
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
                       /*创建数据库TestData*/
GO

create table fill
(
  fnum     char(10) primary key,   /*试题编号 主键 */
  ftitle   text,	           /*试题说明*/                
  fcontent text, 		   /*试题内容 源码*/
  fanswer  text,                   /*试题正确答案*/
  fcheck   text,                   /*试题的阅内容 与试题内容相对的一份源码*/
  fout     text,                   /*试题输出 组合好后的正确输出*/
  fremark  text                   /*试题备忘*/
);

GO

create table modify
(
  fnum     char(10) primary key,   /*试题编号 主键 */
  ftitle   text,	           /*试题说明*/                
  fcontent text, 		   /*试题内容 源码*/
  fanswer  text,                   /*试题正确答案*/
  fcheck   text,                   /*试题的阅内容 与试题内容相对的一份源码*/
  fout     text,                   /*试题输出 组合好后的正确输出*/
  fremark  text                   /*试题备忘*/
);

GO

create table design
(
  fnum     char(10) primary key,   /*试题编号 主键 */
  ftitle   text,	           /*试题说明*/                
  fcontent text, 		   /*试题内容 源码*/
  fanswer  text,                   /*试题正确答案*/
  fcheck   text,                   /*试题的阅内容 与试题内容相对的一份源码*/
  fout     text,                   /*试题输出 组合好后的正确输出*/
  fremark  text                   /*试题备忘*/
);