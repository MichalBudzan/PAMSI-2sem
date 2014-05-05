// KRUSKAL - LISTA SASIEDZTWA

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <stddef.h>
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
	std::vector<int> kolory;

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
		 //cout<<" Wygenerowany graf nie jest spojny, losowanie bedzie powtorzone "<<endl;
		 return false;}

	 return true;
}





void Zainicjuj_Graf(int gestosc,int n){
	 
	Lista_S.clear(); // na wypadek gdy ponowny raz losujemy niespojny graf

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
					K.Zmien_wage(rand()%9);  // decyzja o PRZEDZIALE WAG  
					//cout<<"wylosowalem :";
					//K.Wyswietl_Krawedz();
					Lista_S[i].push_back(K); 
					
				}

		if(Czy_Graf_Jest_Spojny(n)==false)
				Zainicjuj_Graf(gestosc,n);
		else
				return;
}





void Wyswietl_Liste_Sasiedztwa(){
		
		int n=this->Zwroc_Rozmiar();

		for(int i=0; i<n; i++)
			for( std::list<Krawedz>::iterator it=Lista_S[i].L_K.begin() ; it!=Lista_S[i].L_K.end(); ++it){
			     it->Wyswietl_Krawedz(); 
		}

}



template <typename Krawedz>
int Zainicjuj_Liste_Polaczen(std::vector<Krawedz> & krawedzie){

		int n=this->Zwroc_Rozmiar();
		int m=0;
		
		Krawedz K;

		for(int i=0; i<n; i++)
			for( std::list<Krawedz>::iterator it=Lista_S[i].L_K.begin() ; it!=Lista_S[i].L_K.end(); ++it){
			       K.Zmien_u(it->Zwroc_u());
				   K.Zmien_v(it->Zwroc_v());
				   K.Zmien_wage(it->Zwroc_wage());
				   krawedzie.push_back(K);
	               ++m;
				   }


            std::make_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
			std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
			cout<<" Mamy w grafie "<< m << " polaczen "<<endl;
			return m;
}


void Stworz_MST(std::vector<Krawedz> & krawedzie,int m){



		for(int i=0;i<this->rozmiar;i++)  // zeruje tablice kolorow
			kolory.push_back(0);

	Lista_Krawedzi<Krawedz> L;
	for(int i=0 ; i<this->rozmiar;i++)
		Lista_S.push_back(L);

		 Krawedz K;
		 
		 cout<< "MAM "<< m <<" krawedzi "<<endl;
		 
		 for(int i=1; i<=m ;i++){

			  K=krawedzie[0];
             std::pop_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );
			  krawedzie.pop_back();
			std::sort_heap(krawedzie.begin(),krawedzie.end(), Compare<Krawedz>() );


			
			cout<<"Wyswietlam zdjeta krawedz z kopca : "<<endl;
			 K.Wyswietl_Krawedz();
			 


			 int u=K.Zwroc_u();
		     int v=K.Zwroc_v();

			 int id_u=kolory[K.Zwroc_u()];
			 int id_v=kolory[K.Zwroc_v()];

			 if(id_u==0 && id_v==0){
				 if(u>v)
					 kolory[u]=kolory[v]=u;
				 else
					 kolory[u]=kolory[v]=v;

				  Lista_S[u].push_back(K);
				//  Lista_S[v].push_back(K);
			 }

			 else if( id_u!=0 && id_v==0){

				  kolory[v]=kolory[u];
				  Lista_S[u].push_back(K);
				 // Lista_S[v].push_back(K);
			 }

			 else if( id_u==0 && id_v!=0){

				 kolory[u]=kolory[v];
				 Lista_S[u].push_back(K);
				// Lista_S[v].push_back(K);
			 }

			 else if( id_u!=0 && id_v!=0 && id_u!=id_v ){
				  
				for(int i=0;i<this->rozmiar;i++){  
			        if(kolory[i]==id_v)
						kolory[i]=id_u;
				}

				 Lista_S[u].push_back(K);
				 //Lista_S[v].push_back(K);
			 }

			if(Czy_Graf_Jest_Spojny(this->rozmiar)==true){
				cout<<"mam juz drzewo"<<endl;
				 break;
			 }



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

	int n,m,gestosc;


	
	cout<<"Podaj ilosc wierzcholkow grafu ktory mam wylosowac :"<<endl;
	cin>>n;
	cout<<"Podaj gestosc grafu w % : "<<endl;
	cin>>gestosc;


	


	Graf<Krawedz> G(n);  
	std::vector<Krawedz> krawedzie; // na tym obudujemy kopiec

	G.Zainicjuj_Graf(gestosc,n);
	G.Wyswietl_Liste_Sasiedztwa(); // pokazuje wylosowany graf
	
	
	m=G.Zainicjuj_Liste_Polaczen(krawedzie);  // sortuje kopiec 

	/*
	for(int i=0;i<krawedzie.size();i++)
		krawedzie[i].Wyswietl_Krawedz();*/

	
	Graf<Krawedz> Drzewo(n);

	StartCounter();   // START CZAS

	Drzewo.Stworz_MST(krawedzie,m);

	double time=GetCounter();   // STOP CZAS

	cout<<" Czas : "<<time<< "microseconds "<<endl;
	
	
	cout<<"Tak wyglada drzewo MST w postaci listy sasiedztwa : "<<endl;
	Drzewo.Wyswietl_Liste_Sasiedztwa();
	
	

	

	getchar();
	getchar();
	return 0;
}

