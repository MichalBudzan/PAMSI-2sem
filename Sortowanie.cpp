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
#include <fstream>


using namespace std;


template <typename T>
void Sortowanie_Przez_Wstawianie( std::vector<T> & dane  ){   // zlozonosc O(n^2)

    int temp, j;           // w zmiennej temp trzymamy wartosc 'ogladanej' karty ( elementu)
  
    for( int i = 1; i < dane.size(); i++ )    // petla iteracyjnie przechodzi przez wszystkie elementy od poczatku do konca 
    {
        temp = dane[i];                            
      
        for( j =( i - 1); j >= 0 && dane[j] > temp; j-- )   // wszystkie elementy, ktore sa po lewej stronie od 'wyjetej karty' 
            dane[ j + 1 ] = dane[ j ];                      // i sa od niej wieksze , chcemy przesuwac o 1 miejsce w prawo 
           
        dane[ j + 1 ] = temp;   // wyjeta karte wstawiamy o 1 pozycje w prawo w stosunku do jej pierwotnej pozycji
    }

}



template <typename T>
void Sortowanie_Szybkie(std::vector<T> & d, int lewy, int prawy){   // lewy - 0 , prawy - rozmiar -1 

  int i,j,piwot;

  piwot = d[prawy];                        // piwot to prawy element ( ostatni) 

  for(j = i = lewy; i < prawy; i++)
     if(d[i] < piwot)                        // wskaznik i szuka elementow mniejszych od piwotu     
	    {
         swap(d[i], d[j]);                    // jesli znalazl, zamienia z elementem na pozycji wskazywanej przez j, 
         j++;                                 // wskaznik j zostaje przesuniety na nastepna pozycje
         }

  d[prawy] = d[j];                          // piwot wskakuje na pozycje na ktorej zatrzymal sie wskaznik j                   
  d[j] = piwot;                             // wskaznik j wskazuje teraz pozycje pivotu
  if(lewy < j - 1)  Sortowanie_Szybkie(d,lewy, j - 1);    // jesli to mozliwe, wywolanie rekurencyjne dla partycji z lewej i z prawej strony
  if(j + 1 < prawy) Sortowanie_Szybkie(d,j + 1, prawy);   
}




template <typename T>
void MergeSort(std::vector<T> & d,int i_p, int i_k) // scalanie
{
  int i_s,i1,i2,i;
  
  int p[1000000];                   // tablica pomocnicza wykorzystywana przy scalaniu                         


  i_s = (i_p + i_k + 1) / 2;        // znajdujemy srodek tabeli 

  if(i_s - i_p > 1) MergeSort(d,i_p, i_s - 1);   // podzial na dwuelementowe tablice 
  if(i_k - i_s > 0) MergeSort(d,i_s, i_k);  

	i1 = i_p;            // i1,i2 to indeksy pomocnicze dla dwuelemenentowych tablic, ktore beda sortowane
	i2 = i_s;
  for(i = i_p; i <= i_k; i++)
    p[i] = ( (i1 == i_s) || ((i2 <= i_k) && (d[i1] > d[i2])) ) ? d[i2++] : d[i1++];  // sortowanie dwuelementowych tablic
  for(i = i_p; i <= i_k; i++) d[i] = p[i];   // przepisanie z tablicy pomocniczej do glownej posortowanych tablic 
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

	cout<"~~~"<<endl;
	int zm=1;
	zm= ( zm<<1) ;
	cout<"~~~"<<endl;
    cout<<zm<<endl;

    srand(unsigned(time(NULL)));
	 
	// 2^10   1024
	// 2^12   4096
	// 2^14   16384
	// 2^16   65536
	// 2^18   262144
	// 2^20   1048576
	
	fstream plik; 
	plik.open("sortowanie.txt"); 
    if( plik.good() == true )
    {
        cout<<"Otwarto plik do zapisu "<<endl;



  for(int i=0; i < 11 ; i++) {

      for( size_t i = 0; i <16384 ;i++ )
              dane.push_back(rand());

  

     StartCounter(); // rozpoczynamy pomiar

	 //Sortowanie_Przez_Wstawianie(dane);
        Sortowanie_Szybkie(dane,0,dane.size()-1);
		   //  MergeSort(dane,0,dane.size()-1);
	 
		double time=GetCounter();
  
     plik<<time <<  endl;   // koniec pomiaru

       dane.clear();

}

	    plik.close();
    }

	 for( size_t i = 0; i < 10;i++ )
           cout<<dane[i]<<endl;


getchar();
}
