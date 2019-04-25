#include <iostream.h>
#include <fstream.h>
bool narcissus(int n);
void main()
{
	bool nOut=narcissus(407);
	ofstream fout("answer.txt");
	fout<<nOut;
	fout.close();
}



bool narcissus(int n)
{
	int a=(int)n/100;
	int b=(int)(n-a*100)/10;
	int c=n%10;
	int sum=a*a*a+b*b*b+c*c*c;
	if(n==sum)
		return true;
	return false;
}
