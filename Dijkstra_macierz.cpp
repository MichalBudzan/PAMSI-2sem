// ALGORYTM DIJKSTRY :)

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
#include <set>
#include <limits>
#include <Windows.h>

#undef max   // dla numeric limits

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
						     Macierz[i][j]=Macierz[j][i]=(rand()%9 +1 );  // wagi 
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



void Algorytm_Dijkstry(std::vector<int> & P ,int n,int pocz) {

	const int inf = std::numeric_limits<int>::max();

	set<int, cmp> kopiec;             // kopiec z wierzcholkow, posortowany wzgledem odleglosci bierzacej do zrodla

	int wierzcholek;

	
	kopiec.clear();

	for(int i=0;i<n;i++){
		D.push_back(inf);
		P.push_back(0);
	    kopiec.insert(i);
	}

	D[pocz]=0;  // zaczynamy od zerowego wierzcholka


	while(!kopiec.empty()){

		wierzcholek=*(kopiec.begin());
		kopiec.erase(kopiec.begin());


		 for(int i=0;i < n ;i++){
			 if(Macierz[wierzcholek][i]!=0){
			  if( (D[wierzcholek] + Macierz[wierzcholek][i] ) < D[i] ){
				   kopiec.erase(kopiec.find(i));
				   D[i]=(D[wierzcholek] + Macierz[wierzcholek][i] );
				   P[i]=wierzcholek;
				   kopiec.insert(i);
			  }
			 }
		 }


	}

	/*
	cout<<"Wyswietlam rezultaty dzialania algorytmu Dijkstry : "<<endl;
	for(int i=0;i<D.size();i++)
		cout<<D[i]<<"	"<<P[i]<<endl;*/


}


};


std::vector<int> D;  // wektor drog
 
struct cmp
{
    // czy a jest mniejsze od b
    bool operator() (const int &a, const int &b)
    {
        if (D[a] < D[b]) return true;
        if (D[a] > D[b]) return false;
        return a<b;
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

	cout<<"Program - Algorytm Dijkstry - macierz sasiedztwa \n"<<endl;

	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;


	for(int i=0 ; i<6 ;i++){

		D.clear();

	std::vector<int> P;               // lista poprzednikow na najkrotszej sciezce


	Graf<Krawedz> G(n);               // wylosowany graf
	std::vector<Krawedz> krawedzie;   // lista krawedzi tworzace graf
	
	     

	int licznik=0; // zabezpieczenie gdy uzytkownik chce losowac graf o gestosci typu 5 % , to nierealne by byl spojny
	if(G.Losuj_Graf(gestosc,krawedzie,licznik)==false){
		getchar();
		getchar();
		return 1;
	}
	/*
	G.Wyswietl_Macierz();

	
	cout<< " Wyswietlam liste wylosowanych krawedzi :"<<endl;   // dla lepszego wglądu danych
	for(int i=0;i<krawedzie.size();i++)
		krawedzie[i].Wyswietl_Krawedz();*/

	cout<<"~~~"<<endl;


	 
	StartCounter();   // START CZAS

	G.Algorytm_Dijkstry(P,n,0); // 0- zrodlo

	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	wyniki[i]=time;
	}

		fstream plik;
    plik.open("wyniki.txt");
    if( plik.good() == true )
        cout<<"Otwarto plik do zapisu "<<endl;

for(int zm=0;zm<6;zm++)
plik<<wyniki[zm]<<endl;


	getchar();
	getchar();
	return 0;

}
