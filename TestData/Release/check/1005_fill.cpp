#include <iostream>
#include <fstream.h>
#define Max_Size 10
class List
{
public:
	List(int d)
	{
		this->elem=d;
	}
	
	
	
~List()
{
}


	int elem;
};

void main()
{
	List L1();
	List L2;
	List L3(5);
	ofstream  out("answer.txt");
	out<<L3.elem;
}