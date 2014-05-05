// ALGORYTM PRIMA - MAcierz
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
#include <Windows.h>
#include <cmath>

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






//////////////////////  GRAF /////////////////////////////// 



template <typename Krawedz>
class Graf{

	int ** Macierz; // macierz sasiedztwa
	int rozmiar;

public :

	Graf(int n){
	this->rozmiar=n;
	Macierz = new int * [n];    
	for(int i=0;i<n;i++)
		Macierz[i]=new int [n];
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



int Zainicjuj_Graf(int gestosc){

	    int m=0;
		int n=this->Zwroc_Rozmiar();
		srand (time(NULL));

		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++){
				 if(i==j) { Macierz[i][j]=Macierz[j][i]=0; }

				 else{
						if(rand()%100 < gestosc ){   
						     Macierz[i][j]=Macierz[j][i]=(rand()%9 + 1);  // narazie wagi od 1 do 9 
								++m;
	
					 }
					    else 
					 	   Macierz[i][j]=Macierz[j][i]=0;
				 }
			}

			if(Czy_Graf_Jest_Spojny()==false){  // zaczynamy od nowa
				Zainicjuj_Graf(gestosc);}
			else
				return (m);

}




void Wyswietl_Macierz(){
		
		int n=this->Zwroc_Rozmiar();

		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++)
				cout << Macierz[i][j] << " ";
               cout << endl;
		}

}



void Stworz_MST(Graf & G,std::vector<Krawedz> & krawedzie,int n,int m){

	   
	   std::vector<int> wektor_flag(this->rozmiar,0);

		for(int i = 0; i < rozmiar; i++)
			for(int j = 0; j < rozmiar; j++)
				Macierz[i][j]=0;

		int ilosc_wierzcholkow=0;
		Krawedz K;
		 
		 cout<< "MAM "<< m <<" krawedzi "<<endl;
		// cout<<" ROZMIAR wektora flag  "<<wektor_flag.size()<<endl;
		
		 int a=0;

		 wektor_flag[a]=1;   // zaczynamy od 0 wierzcholka
		 ++ilosc_wierzcholkow;

		 

    for(int i=0;i<rozmiar;i++)        // wrzucam sasiadow wierzcholka 0 na kopiec
		 if(G.Macierz[a][i]!=0){
			  K.Zmien_u(a);
			  K.Zmien_v(i);
			  K.Zmien_wage(G.Macierz[a][i]);
			  krawedzie.push_back(K);

		 }


		std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>());
		std::sort_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>());
		 
		 	 

	//cout<< " Wyswietlam sasiadow wierzcholka 0 :"<<endl;
	//for(int i=0;i<krawedzie.size();i++)
		//krawedzie[i].Wyswietl_Krawedz();

	


	 while(ilosc_wierzcholkow!=this->rozmiar){

		   K =krawedzie[0];
			/// cout<<"usuwam : ";
			// K.Wyswietl_Krawedz();

			 std::pop_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>()); 
			 krawedzie.pop_back();
			 std::sort_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>());

		
			//cout<<wektor_flag[K.Zwroc_u()]<<" oraz " <<wektor_flag[K.Zwroc_v()]<<endl;

		if(wektor_flag[K.Zwroc_u()]!=1 || wektor_flag[K.Zwroc_v()]!=1 ) {

		  //cout<<"Dodaje ja do drzewa "<<endl;

		//   procedura dodania krawedzi do macierzy sasiedztwa
		Macierz[K.Zwroc_u()][K.Zwroc_v()]=Macierz[K.Zwroc_v()][K.Zwroc_u()]=K.Zwroc_wage();
	   //


		 ++ilosc_wierzcholkow;
		 wektor_flag[K.Zwroc_u()]=wektor_flag[K.Zwroc_v()]=1;   // wierzcholki sa juz uzyte, ustawiamy flagi

		 // dodajemy sasiadow do kopca: 
		 Krawedz KS;
		 
	  for(int i=0;i<rozmiar;i++)        // wrzucam sasiadow wierzcholka u na kopiec
		 if(G.Macierz[K.Zwroc_u()][i]!=0  && wektor_flag[i]==0 ) {
			  KS.Zmien_u(K.Zwroc_u());
			  KS.Zmien_v(i);
			  KS.Zmien_wage(G.Macierz[K.Zwroc_u()][i]);
			  krawedzie.push_back(KS);
		 }

			  std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>());
			  std::sort_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>());
		 
	 for(int i=0;i<rozmiar;i++)        // wrzucam sasiadow wierzcholka v na kopiec
		 if( (G.Macierz[K.Zwroc_v()][i])!=0  && wektor_flag[i]==0) {
			  KS.Zmien_u(K.Zwroc_v());
			  KS.Zmien_v(i);
			  KS.Zmien_wage(G.Macierz[K.Zwroc_v()][i]);
			   krawedzie.push_back(KS);
			  
		 }
		 
		      std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>());
			  std::sort_heap(krawedzie.begin(),krawedzie.end(),Compare<Krawedz>());

		}

	 }

	 	cout<<"Stworzono drzewo MST "<<endl;

}


};


template <typename Krawedz>
class Compare{
public:
  bool operator()(Krawedz &  K1, Krawedz & K2) const
  {
    return K1.Zwroc_wage() <= K2.Zwroc_wage();
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
	

	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;

	for(int i=0;i<8;i++){

	
	Graf<Krawedz> G(n);  



	m=G.Zainicjuj_Graf(gestosc);
	//G.Wyswietl_Macierz();

	Graf<Krawedz> Drzewo(n);

	StartCounter();   // START CZAS

	std::vector<Krawedz>  krawedzie;   // na tym wektorze obudujemy kopiec

	
	Drzewo.Stworz_MST(G,krawedzie,n,m);

	cout<<"Tak wyglada drzewo MST : "<<endl;
	//Drzewo.Wyswietl_Macierz();

	
	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	wyniki[i]=time;
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

