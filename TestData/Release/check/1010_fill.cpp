#include <string.h>
#include <iostream.h>
#include<fstream.h>

void mySort(int arr[],int n);
int main()
{
   int arr[5] = {7,6,3,4,1};
   mySort(arr,5);
   int n = 5;

   ofstream fout("answer.txt");
   while (n--)
   {
        cout<<arr[n]<<endl;
        fout<<arr[n];     
   }    
   fout.close();   
   return 1;

}




void mySort(int arr[],int n)
{
  for(int i = 0;i<n;i++)
     for(int j = 0;j<n-i;j++)
     {
	if(arr[j+1] < arr[j])
	{
	     int temp;
	     temp = arr[j];
	     arr[j] = arr[j+1];
	     arr[j+1] = temp;
	}
      }
}

