#include <string.h>
#include <iostream.h>
#include<fstream.h>

int AddNum();

int main()
{
   int nOut = 0;
   nOut = AddNum();
   ofstream fout("answer.txt");
   fout<<nOut;
   fout.close();
   cout<<nOut;
   return 1;

}



int AddNum()
{
    int Sum = 0;
    for(int i = 1;i<= 100;i++)
    {
        Sum = Sum + i;         
    }
return Sum;   
}

