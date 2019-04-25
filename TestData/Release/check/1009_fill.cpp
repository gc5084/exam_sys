
#include <string.h>
#include <iostream.h>
#include<fstream.h>




int Compare(char ch1,char ch2)
{
    if(ch1 == ch2)
        return 1;
    else
       return 0;
}


int main()
{
   char ch1 = 'c';
   char ch2 = 'c';
   int nOut;
   nOut = Compare(ch1,ch2);
   ofstream fout("answer.txt");
   fout<<nOut;
   fout.close();
   cout<<nOut;
   return 1;

}
