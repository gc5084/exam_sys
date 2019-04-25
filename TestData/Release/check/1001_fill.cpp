#include <string.h>
#include <iostream.h>
#include<fstream.h>

int main()
{
   int max(int arr[],int n);
   int arr[5] = {22,33,66,55,32};
   int nOut;
   nOut = max(arr,5);
   ofstream fout("answer.txt");
   fout<<nOut;
   fout.close();
   cout<<nOut;
   return 1;

}



int max(int arr[],int n)
{
  int nmax = arr[0];
 for(int i =0;i<5;i++)
    {
        if(arr[i] > nmax)
          nmax = arr[i];    
    }
return nmax;   
}

