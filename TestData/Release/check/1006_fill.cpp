#include <string.h>
#include <iostream.h>
#include<fstream.h>

int main()
{
   int min(int arr[],int n);
   int arr[5] = {22,33,66,55,32};
   int nOut;
   nOut = min(arr,5);
   ofstream fout("answer.txt");
   fout<<nOut;
   fout.close();
   cout<<nOut;
   return 1;
}



int min(int arr[],int n)
{
  int nmin = arr[0];
  for(int i =0;i<5;i++)
    {
        if(arr[i] < nmin)
          nmin = arr[i];    
    }
return nmin;   
}

