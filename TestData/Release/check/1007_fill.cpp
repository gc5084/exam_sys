#include <string.h>
#include <iostream.h>
#include<fstream.h>

void Swap(int& a,int& b);

int main()
{
   int nOut = 1;
   int temp = 2;
   Swap(nOut,temp);

   ofstream fout("answer.txt");
   fout<<nOut;
   fout.close();
   cout<<nOut;
   return 1;

}



void Swap(int& a,int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
