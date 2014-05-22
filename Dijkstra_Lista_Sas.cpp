// ALGORYTM DIJKSTRY - lista sas.

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

	Krawedz & Zwroc_Krawedz (){ return *this; }

};

//////////////////////////////////////

template <typename Krawedz>
class Lista_Krawedzi {

public :
std::list<Krawedz> L_K;

void push_back(Krawedz & K){
	L_K.push_back(K);
}


Lista_Krawedzi(){

	std::list<Krawedz> L_K;

}


};

///////////////////////////////////////////


template <typename Krawedz>
class Graf{

	std::vector< Lista_Krawedzi<Krawedz> > Lista_S; // lista sasiedztwa
	int rozmiar;    
	std::vector<int> kolory;   // wektor kolorow - zabezpieczenie przed cyklem

public :

	Graf(int n){
		this->rozmiar=n;
}


	
int Zwroc_Rozmiar(){ return rozmiar;}


bool Czy_Graf_Jest_Spojny(int n){

	std::vector<int> kolory(this->rozmiar,0); // kolory odpowiedza na to pytanie
	int id_u,id_v,i,j;


	for(i=0; i<n; i++)
		for( std::list<Krawedz>::iterator it=Lista_S[i].L_K.begin() ; it!=Lista_S[i].L_K.end(); ++it){
			i=it->Zwroc_u();
            j=it->Zwroc_v();
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

	int wzor=kolory[0];
		for(int a=0;a<this->rozmiar;a++)
				if(kolory[a]!=wzor){
						cout<<" Wygenerowany graf nie jest spojny, losowanie bedzie powtorzone "<<endl;
						return false;}

return true;
}



void Losuj_Graf(int gestosc,int n){

	Lista_S.clear();// na wypadek gdy ponowny raz losujemy niespojny graf

	Lista_Krawedzi<Krawedz> L;
	for(int i=0 ; i<n;i++)
			Lista_S.push_back(L);

	srand (time(NULL));

	Krawedz K;
        
	for(int i = 0; i < (n-1); i++)
	for(int j = (i+1); j < n; j++)
		if(rand()%100 < gestosc){
			K.Zmien_u(i);
			K.Zmien_v(j);
			K.Zmien_wage(rand()%9+1); // decyzja o PRZEDZIALE WAG 1-9
			//cout<<"wylosowalem :";
			//K.Wyswietl_Krawedz();
			Lista_S[i].push_back(K);
			K.Zmien_u(j);
			K.Zmien_v(i);
			Lista_S[j].push_back(K);
		}


	if(Czy_Graf_Jest_Spojny(n)==false)

		Losuj_Graf(gestosc,n);
	else
		return;

}


int Wyswietl_Liste_Sasiedztwa(){

	int n=this->Zwroc_Rozmiar();
	int m=0;

	for(int i=0; i<n; i++)
	for( std::list<Krawedz>::iterator it=Lista_S[i].L_K.begin() ; it!=Lista_S[i].L_K.end(); ++it){
			//it->Wyswietl_Krawedz();
			++m;
	}

return (m/2);

}



void Algorytm_Dijkstry(std::vector<Krawedz> & krawedzie,std::vector<int> & D,std::vector<int> & P,std::vector<int> & S,int n) {

	const int inf = std::numeric_limits<int>::max();
	int wierzcholek,odl,zm;
	int koniec=1;
	Krawedz K;

	for(int i=0;i<n;i++){
		D.push_back(inf);
		P.push_back(0);
		S.push_back(0);
	}


	wierzcholek=0;  // bierzemy zrodlo jako wierzcholek nr 0
	S[0]=1;  
	D[0]=0;
	


	while(koniec){

		odl=inf;
		zm=inf;
		for(int i=0;i<D.size();i++)
			if(D[i]<odl && S[i]==1){
			   if(D[i]<zm){
				 wierzcholek=i;
		         zm=D[i];
			   }
			}


		S[wierzcholek]=2;

		int i;

		for( std::list<Krawedz>::iterator it=Lista_S[wierzcholek].L_K.begin() ; it!=Lista_S[wierzcholek].L_K.end(); ++it){
			     K=it->Zwroc_Krawedz();
				 if(K.Zwroc_u()!=wierzcholek)
					i=K.Zwroc_u();
				 else
				    i=K.Zwroc_v();

			    if( S[i]!=2){  // kazdy sasiad wierzcholka ktorego nie ma w S
					 if( ( D[wierzcholek] + K.Zwroc_wage()) < D[i] ){  // znaleziono krotsza droge
							D[i]= ( D[wierzcholek] + K.Zwroc_wage());
							P[i]= wierzcholek;
							S[i]=1;
					 }
				}
		}

	
		koniec=0;
		for(int i=0;i<n;i++)
			if(S[i]==1){
				koniec=1;   // flaga sprawdza czy to koniec algorytmu
				//cout<<"to nie koniec"<<endl;
			}
	}

	cout<<"Wyswietlam rezultaty dzialania algorytmu Dijkstry : "<<endl;
		//for(int i=0;i<D.size();i++)
		//	cout<<D[i]<<"	"<<P[i]<<endl;


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

	int n,m,gestosc;
	long double wyniki[8];
	cout<<"Program - Algorytm Dijkstry - macierz sasiedztwa \n"<<endl;

	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;

	for(int i=0;i<5;i++){



	Graf<Krawedz> G(n);               // wylosowany graf
	std::vector<Krawedz> krawedzie;   // lista krawedzi tworzace graf
	std::vector<int> D;               // odleglosci zrodlo-wierzcholek
	std::vector<int> P;               // lista poprzednikow na najkrotszej sciezce
	std::vector<int> S;               // zbior wszystkich wierzcholkow o stanach  :  0 - jeszcze nie uzyty ; 1 - uzyty, lecz nie znaleziono drogi, 2 - uzyty i znaleziono


		G.Losuj_Graf(gestosc,n);
		m=G.Wyswietl_Liste_Sasiedztwa(); // pokazuje wylosowany graf
	
		cout<<"mam "<<m<<"krawedzi"<<endl;
	/*
	cout<< " Wyswietlam liste wylosowanych krawedzi :"<<endl;   // dla lepszego wglądu danych
	for(int i=0;i<krawedzie.size();i++)
		krawedzie[i].Wyswietl_Krawedz();*/

	cout<<"~~~"<<endl;


	 
	StartCounter();   // START CZAS

	G.Algorytm_Dijkstry(krawedzie,D,P,S,n);

	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	wyniki[i]=time;
	}


		fstream plik;
    plik.open("wyniki.txt");
    if( plik.good() == true )
        cout<<"Otwarto plik do zapisu "<<endl;

for(int zm=0;zm<5;zm++)
plik<<wyniki[zm]<<endl;





	getchar();
	getchar();
	return 0;

}
