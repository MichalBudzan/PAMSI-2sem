// Sortowania.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <stddef.h>
#include <Windows.h>


using namespace std;


template <typename T>
void Sortowanie_Przez_Wstawianie( std::vector<T> & dane  ){   // zlozonosc O(n^2)

    int temp, j;
  
    for( int i = 1; i < dane.size(); i++ )
    {
        temp = dane[i];
      
        for( j =( i - 1); j >= 0 && dane[j] > temp; j-- )
            dane[ j + 1 ] = dane[ j ];
      
        dane[ j + 1 ] = temp;
    }

}



template <typename T>
void Sortowanie_Szybkie(std::vector<T> & d, int lewy, int prawy){   // lewy - 0 , prawy - rozmiar -1 

  int i,j,piwot;

  i = (lewy + prawy) / 2;
  piwot = d[i]; d[i] = d[prawy];
  for(j = i = lewy; i < prawy; i++)
  if(d[i] < piwot)
  {
    swap(d[i], d[j]);
    j++;
  }
  d[prawy] = d[j]; d[j] = piwot;
  if(lewy < j - 1)  Sortowanie_Szybkie(d,lewy, j - 1);
  if(j + 1 < prawy) Sortowanie_Szybkie(d,j + 1, prawy);
}



template <typename T>
void MergeSort(std::vector<T> & d,int i_p, int i_k)    // scalanie
{
  int i_s,i1,i2,i;
 int p[16384];


  i_s = (i_p + i_k + 1) / 2;
  if(i_s - i_p > 1) MergeSort(d,i_p, i_s - 1);
  if(i_k - i_s > 0) MergeSort(d,i_s, i_k);
  i1 = i_p; i2 = i_s;
  for(i = i_p; i <= i_k; i++)
    p[i] = ((i1 == i_s) || ((i2 <= i_k) && (d[i1] > d[i2]))) ? d[i2++] : d[i1++];
  for(i = i_p; i <= i_k; i++) d[i] = p[i];
}



///////////////
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

//////////////////


int main()
{



    std::vector<int> dane;

    srand(unsigned(time(NULL)));


	// 2^12   4096
	// 2^14   16384
	// 2^16   65536
	// 2^18   262144
	// 2^20   1048576



   for( size_t i = 0; i <  65536; i++ )
           dane.push_back(rand());

  

  //  for( size_t i = 0; i < dane.size(); i++ )
      //   cout<<dane[i]<<endl;
  


StartCounter(); // rozpoczynamy pomiar

	//Sortowanie_Przez_Wstawianie(dane);
     	// Sortowanie_Szybkie(dane,0,dane.size()-1);
						MergeSort(dane,0,dane.size()-1);

   cout<<"~~~~~"<<endl;

  cout << GetCounter() << " microseconds "<< endl;   // koniec pomiaru


  /*
    for( size_t i = 0; i < 30; i++ )   
         cout<<dane[i]<<endl;*/
		
	

getchar();
}
