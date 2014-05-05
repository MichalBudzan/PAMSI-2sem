
// Kruskal_macierzowo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <stddef.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <Windows.h>

using namespace std;

class Krawedz{

	int u,v,waga;

public:
	
	void Zmien_u(int val){ u=val; } 
	void Zmien_v(int val) { v=val; } 
	void Zmien_wage(int val) { waga=val;}
	const int Zwroc_u() { return u;}
	const int Zwroc_v() { return v;}
    const int Zwroc_wage() { return waga;}
	void Wyswietl_Krawedz(){cout<< u << "-" <<v<<"  "<<waga<<endl;}

	Krawedz & operator = ( const Krawedz & K){

	this->u=K.u;
	this->v=K.v;
	this->waga=K.waga;

	return *this;
	}


};





template <typename Krawedz>
class Graf{

	int ** Macierz; // macierz sasiedztwa
	int rozmiar;    
	std::vector<int> kolory;   // wektor kolorow - zabezpieczenie przed cyklem

public :

	Graf(int n){
	this->rozmiar=n;
	Macierz = new int * [n];    
	for(int i=0;i<n;i++)
		Macierz[i]=new int [n];
	}


	
	~Graf(){
		for(int i = 0; i < this->Zwroc_Rozmiar(); i++) delete [] Macierz[i];
      delete [] Macierz;
	}

	
int Zwroc_Rozmiar(){ return rozmiar;}


bool Czy_Graf_Jest_Spojny(){

	std::vector<int> kolory(this->rozmiar,0);  // kolory odpowiedza na to pytanie
	int id_u,id_v;

	for(int i = 0; i < (this->rozmiar-1); i++)
		for(int j = (i+1); j < this->rozmiar; j++){
			if(Macierz[i][j]!=0){
				 id_u=kolory[i];
				 id_v=kolory[j];


			   if(id_u==0 && id_v==0){
				  if(i>j)
					 kolory[i]=kolory[j]=i;
				 else
					 kolory[i]=kolory[j]=j;
			   }

			  else if( id_u!=0 && id_v==0){

				 kolory[j]=kolory[i];
				 
			 }

			 else if( id_u==0 && id_v!=0){

				 kolory[i]=kolory[j];
			 }

			 else if( id_u!=0 && id_v!=0 && id_u!=id_v ){
				  
				for(int zm=0;zm<this->rozmiar;zm++){  
			        if(kolory[zm]==id_v)
						kolory[zm]=id_u;
				}
			 }
			}
		}

int wzor=kolory[0];
for(int a=0;a<this->rozmiar;a++)
	 if(kolory[a]!=wzor){
		 cout<<" Wygenerowany graf nie jest spojny, losowanie bedzie powtorzone "<<endl;
		 return false;}

	 return true;

			
}






bool Losuj_Graf(int gestosc, std::vector<Krawedz> & krawedzie,int & licznik){
	
	    
	   ++licznik;

	    Krawedz K;

		int n=this->Zwroc_Rozmiar();
		srand (time(NULL));

		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++){
				 if(i==j) { Macierz[i][j]=Macierz[j][i]=0; }

				 else{
						if(rand()%100 < gestosc ){   
						     Macierz[i][j]=Macierz[j][i]=(rand()%RAND_MAX );  // wagi 
							 K.Zmien_u(i);
							 K.Zmien_v(j);
							 K.Zmien_wage(Macierz[i][j]);
							 krawedzie.push_back(K);
					 }
					    else 
					 	   Macierz[i][j]=Macierz[j][i]=0;
				 }
			}

			if(Czy_Graf_Jest_Spojny()==false){
				if(licznik>100){
					cout<<"Najprawdopodobniej podana gestosc jest za mala by stworzyc spojny graf dla tylu wierzcholkow."<<endl;
					return false;
				}
				krawedzie.clear();  // zaczynamy od nowa losowanie grafu
				Losuj_Graf(gestosc,krawedzie,licznik);}
			else{
				std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
				std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
				return true;}
}






void Wyswietl_Macierz(){
		
		int n=this->Zwroc_Rozmiar();

		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++)
				cout << Macierz[i][j] << " ";
               cout << endl;
		}

}



void Stworz_MST(std::vector<Krawedz> & krawedzie,int m,int n){

		

	   int zm=0;
	   int ilosc_polaczen=(n-1);

		for(int i = 0; i < rozmiar; i++)
			for(int j = 0; j < rozmiar; j++)
				Macierz[i][j]=0;


		for(int i=0;i<this->rozmiar;i++)  // zeruje wektor kolorow
			kolory.push_back(0);

		 Krawedz K;
		 
		 cout<< "MAM "<< m <<" krawedzi w grafie "<<endl;
		 
		while(zm!=ilosc_polaczen){

			 std::pop_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>()); 
			 K =krawedzie[krawedzie.size()-1];

			 //cout<<"usuwam : ";
			 //K.Wyswietl_Krawedz();

			 krawedzie.pop_back();
			 std::sort_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>());

			 int u=K.Zwroc_u();
		     int v=K.Zwroc_v();

			 int id_u=kolory[K.Zwroc_u()];
			 int id_v=kolory[K.Zwroc_v()];

			 if(id_u==0 && id_v==0){
				 if(u>v)
					 kolory[u]=kolory[v]=u;
				 else
					 kolory[u]=kolory[v]=v;


				  Macierz[u][v]=Macierz[v][u]=K.Zwroc_wage();
				   ++zm;
			 }

			 else if( id_u!=0 && id_v==0){

				 kolory[v]=kolory[u];
				 Macierz[u][v]=Macierz[v][u]=K.Zwroc_wage();
				  ++zm;
			 }

			 else if( id_u==0 && id_v!=0){

				 kolory[u]=kolory[v];
				 Macierz[u][v]=Macierz[v][u]=K.Zwroc_wage();
				  ++zm;
			 }

			 else if( id_u!=0 && id_v!=0 && id_u!=id_v ){
				  
				for(int i=0;i<this->rozmiar;i++){  
			        if(kolory[i]==id_v)
						kolory[i]=id_u;
				}

				Macierz[u][v]=Macierz[v][u]=K.Zwroc_wage();
				 ++zm;
			 }
			 //else 
				// cout<<"Nie dodam jej, bo bedzie cykl"<<endl;
			

		}




}

};


template <typename Krawedz>
class Compare{
public:
  bool operator()(Krawedz &  K1, Krawedz & K2) const
  {
    return K1.Zwroc_wage() < K2.Zwroc_wage();
  } 
};



///////////////// POMIAR_CZASU ///////////////////////

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
/////////////////////////////////////////////////////////////



int _tmain(int argc, _TCHAR* argv[])
{
	long double wyniki[8];

	int n,m,gestosc;
cout<<"Program - Algorytm Kruskala - macierz sasiedztwa \n"<<endl;

	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;



	for(int i=0;i<8;i++){

	
	


	Graf<Krawedz> G(n);  

	std::vector<Krawedz> krawedzie;

	int licznik=0; // zabezpieczenie gdy uzytkownik chce losowac graf o gestosci typu 5 % , to nierealne by byl spojny
	if(G.Losuj_Graf(gestosc,krawedzie,licznik)==false){
		getchar();
		getchar();
		return 1;
	}

	//G.Wyswietl_Macierz();

/*
	cout<< " Wyswietlam liste wylosowanych krawedzi :"<<endl;   // dla lepszego wglądu danych
	for(int i=0;i<krawedzie.size();i++)
		krawedzie[i].Wyswietl_Krawedz();*/

	cout<<"~~~"<<endl;


	Graf<Krawedz> Drzewo(n);
	 
	StartCounter();   // START CZAS

	Drzewo.Stworz_MST(krawedzie,krawedzie.size(),n);

	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	wyniki[i]=time;

	//cout<<"Tak wyglada drzewo MST : "<<endl;
	//Drzewo.Wyswietl_Macierz();

	
	}


	fstream plik;
    plik.open("wyniki.txt");
    if( plik.good() == true )
        cout<<"Otwarto plik do zapisu "<<endl;

	for(int zm=0;zm<8;zm++)
	plik<<wyniki[zm]<<endl;

	getchar();
	getchar();
	return 0;
}

