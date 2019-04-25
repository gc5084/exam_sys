#include <iostream.h>
#include <fstream.h>
#include <math.h>
bool complete(int n);
void main()
{
	bool re=complete(496);
	ofstream fout("answer.txt");
	fout<<re;
	fout.close();
}



bool complete(int n)
{
	int sum=1;
	for(int i=2;i<=sqrt(n);i++)
	{
		if(n%i==0)
		{
			sum+=i+(n/i);
		}
	}
	if(n==sum)
		return true;
	return false;
}
