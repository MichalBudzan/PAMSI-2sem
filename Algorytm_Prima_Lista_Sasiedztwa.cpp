// ALG PRIMA - LISTA SASIEDZTWA

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <stddef.h>
#include <algorithm>
#include <fstream>
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
    int Zwroc_wage() { return waga;}
	void Wyswietl_Krawedz(){cout<< u << "-" <<v<<"  "<<waga<<endl;}

	Krawedz & operator = ( const Krawedz & K){

	this->u=K.u;
	this->v=K.v;
	this->waga=K.waga;

	return *this;
	}

	Krawedz & Zwroc_Krawedz (){ return *this; }

};

////////////////////////////////

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
//////////////////////////////






template <typename Krawedz>
class Graf{

	std::vector<  Lista_Krawedzi<Krawedz> >  Lista_S; // lista sasiedztwa
	int rozmiar;
	

public :
	
	Graf(int n){
		this->rozmiar=n;
	}

	
int Zwroc_Rozmiar(){ return rozmiar;}



bool Czy_Graf_Jest_Spojny(int n){

	std::vector<int> kolory(this->rozmiar,0);  // kolory odpowiedza na to pytanie
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
					K.Zmien_wage(rand()%9+1);  // decyzja o PRZEDZIALE WAG   1-9
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



void Stworz_MST(Graf & G,std::vector<Krawedz> & krawedzie,int m){

	int ilosc_wierzcholkow=0;

	std::vector<int> wektor_flag(this->rozmiar,0);  // 0 - gdy wierzcholek poza drzewem, 1 -gdy juz jest w drzewie


	Lista_Krawedzi<Krawedz> L;
	for(int i=0 ; i<this->rozmiar;i++)
		 this->Lista_S.push_back(L);       // tutaj powstanie drzewo

		 Krawedz K;
		 
		 cout<< "MAM "<< m <<" krawedzi "<<endl;
		 cout<<" ROZMIAR FLAG "<<wektor_flag.size()<<endl;

		 int a=0;

		 wektor_flag[a]=1;   // zaczynamy od 0 wierzcholka
		 ++ilosc_wierzcholkow;

	 for( std::list<Krawedz>::iterator it=G.Lista_S[a].L_K.begin() ; it!=G.Lista_S[a].L_K.end(); ++it)
		      krawedzie.push_back(it->Zwroc_Krawedz());

	    
            std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );  // wprowadzam sasiadow wierzcholka 0 na kopiec
			std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );

		

	 while(ilosc_wierzcholkow!=this->rozmiar){

		 

		 	 K=krawedzie[0];

			  //cout<<"Wyswietlam zdjeta krawedz z kOPCA : "<<endl;
		     // K.Wyswietl_Krawedz();


             std::pop_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
			  krawedzie.pop_back();
			 std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
		
		
		 //cout<<wektor_flag[K.Zwroc_u()]<<" oraz " <<wektor_flag[K.Zwroc_v()]<<endl;

		 if(wektor_flag[K.Zwroc_u()]!=1 || wektor_flag[K.Zwroc_v()]!=1) {

        

		//   procedura dodania krawedzi do listy sasiedztwa
		 int u,v;
		 u=K.Zwroc_u();
		 v=K.Zwroc_v();

		 Lista_S[u].push_back(K);
		 K.Zmien_u(v);
		 K.Zmien_v(u);
		 Lista_S[v].push_back(K);
		 //


		 ++ilosc_wierzcholkow;
		 wektor_flag[K.Zwroc_u()]=wektor_flag[K.Zwroc_v()]=1;   // wierzcholki sa juz uzyte

		 // dodajemy sasiadow : 

		 for( std::list<Krawedz>::iterator it=G.Lista_S[K.Zwroc_u()].L_K.begin() ; it!=G.Lista_S[K.Zwroc_u()].L_K.end(); ++it){
			   if(wektor_flag[it->Zwroc_u()]==0 || wektor_flag[it->Zwroc_v()]==0 )
		         krawedzie.push_back(it->Zwroc_Krawedz());
		 }
		 
            std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );  
			std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );

		
		 for( std::list<Krawedz>::iterator it=G.Lista_S[K.Zwroc_v()].L_K.begin() ; it!=G.Lista_S[K.Zwroc_v()].L_K.end(); ++it)
			  if(wektor_flag[it->Zwroc_u()]==0 || wektor_flag[it->Zwroc_v()]==0 ){
				  krawedzie.push_back(it->Zwroc_Krawedz());
			  }

		    std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );  
			std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
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

	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;

	for(int i=0;i<8;i++){

	std::vector<Krawedz> krawedzie;
	Graf<Krawedz> G(n);  

	G.Losuj_Graf(gestosc,n);
	m=G.Wyswietl_Liste_Sasiedztwa(); // pokazuje wylosowany graf
	
	
	Graf<Krawedz> Drzewo(n);

	StartCounter();   // START CZAS

	Drzewo.Stworz_MST(G,krawedzie,m);

	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	wyniki[i]=time;
	//cout<<"Tak wyglada drzewo MST w postaci listy sasiedztwa : "<<endl;
	//Drzewo.Wyswietl_Liste_Sasiedztwa();
	
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

