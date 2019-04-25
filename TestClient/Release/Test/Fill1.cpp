#include <iostream.h>

class MyData
{
public:
	MyData(int i)
	{
/***found***/
     
         m_i = ____;
		
/***end***/
	}
	void print()
	{
		cout<<--m_i<<',';
	}
public:
	int m_i;
};

int main()
{

	int i = 0;

	MyData obj(5);

	while(i<5)
	{
		
		i++;

		obj.print(); 
	}
	cout<<endl;

	return 0;
}