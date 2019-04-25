#include <fstream>

std::ofstream cout("answer.txt");



class MyClass
{
public:
	~MyClass(){};
	MyClass(int i)
	{ 
	   cout<<"i="<<i;
	};

};
void main()
{ 
	MyClass obj(41);
	return;
}