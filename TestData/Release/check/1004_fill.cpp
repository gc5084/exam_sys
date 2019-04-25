#include<iostream.h>
#include<fstream.h>
int calcdays(int y,int m);
void main()
{
	int nOut;
	ofstream fout("answer.txt");
	nOut=calcdays(400,2);
	fout<<nOut;
	nOut=calcdays(2000,1);
	fout<<nOut;
	fout.close();
}



int calcdays(int y,int m)
{
	int days;
	bool leap=false;
	switch(m)
	{
	case 1:
	case 3:
	case 5:											
	case 7:
	case 8:
	case 10:
	case 12:
		days=31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		days=30;
		break;
	case 2:
		if(y%400==0)
			leap=1;
		else if(y%4==0&&y%100!=0)
			leap=1;
		else
			leap=0;
		if(leap)
			days=29;
		else
			days=28;
	}
	return days;
}
