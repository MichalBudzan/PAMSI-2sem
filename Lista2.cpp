



// lista2.cpp : Defines the entry point for the console application.
//    MICHAŁ BUDZAN    200294       LISTA 2      ZADANIA LABORATORIUM PAMSI 

#include "stdafx.h"
#include <iostream>
#include <stddef.h>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;
 
template<class T>         // Szablon klasy Lista opakowuje liste dwukierunkowa
class Lista {

	size_t rozmiar;       // Pole przechowuje informacje o ilosci elementow listy

    ///////  PUNKT 1 /////// 

public : 
	class Node{         // szablon klasy wezel z polami : wartosc elementu, wskaznik na kolejny wezel oraz na poprzedni

		public:

			T val;           
			Node * next;    // ostatni będzie wskazywał na samego siebie  
			Node * prev;    // pierwszy będzie wskazywał na samego siebie 

	   Node(T wartosc=0){     // konstruktor wezla
		val=wartosc;
		this->next=NULL;
		this->prev=NULL;
	}


	  };


	///////// PUNKT 2 //////// 
	
	
	class Iterator {      // szablon klasy Iterator  

	        public :
			Node * wsk;
			Iterator Next(Iterator it);       // metoda umozliwia przejscie do nastepnego wezla
			Iterator Prev(Iterator it);       // metoda umozliwia przejscie do poprzedniego wezla
		};

	Iterator poczatek_listy;                // Obiekty klasy Iterator wskazuja na poczatek oraz koniec listy
	Iterator koniec_listy;

	
	Iterator Prev(Iterator it){
		it.wsk=it.wsk->prev;
		return it;
	}

	Iterator Next(Iterator it){
		it.wsk=it.wsk->next;
		return it;
	}


	T & Zwroc_Referencje( Iterator it){          // metoda zwraca referencje do wartosci przechowywanej w wskazywanym wezle

		return it.wsk->val;
	}


	bool Compare_Iterators(Iterator it1, Iterator it2){    // porownanie miedzy iteratorami, weryfikuje czy wskazuja na ten sam wezel

		if(it1.wsk==it2.wsk){
			cout<<"Iteratory wskazuja na ten sam wezel."<<endl;
			return true; }

		cout<<"Iteratory wskazują na różne węzły. "<<endl;
		return false;
	}


	//////// PUNKT 3 //////////////


	bool Czy_Wezel_Rozlaczony(Node * wezel){      // metoda sprawdza, czy wezel jest rozlaczony 
		
			if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}


		if(wezel->next==wezel && wezel->prev==wezel){
			cout<<" Wezel jest rozlaczony"<<endl;
			return true;
		}
		return false;
	}
	 


	bool Czy_Wezel_Prawidlowo_Polaczony(Node * wezel){    // metoda sprawdza czy wezel jest prawidlowo podlaczony
		
			if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return false;
         	}


		if(wezel==poczatek_listy.wsk){   // jezeli to pierwszy wezel w liscie
			if(wezel->prev==wezel && wezel->next!=wezel && wezel->next!=NULL){
				return true;
			}
			return false;
		}
		
		if(wezel==koniec_listy.wsk){      // jezeli to ostatni wezel w liscie
			if(wezel->next==wezel && wezel->prev!=wezel && wezel->prev!=NULL){
				return true;
			}
			 return false;
		}

		if(wezel->next!=wezel && wezel->next!=NULL &&  wezel->prev!=NULL && wezel->prev!=wezel)
			return true;

		return false;

	}



  // metoda wstawia wezel za ostatnim, ktory jest podany jako parametr wywolania
  void  Wstaw_Wezel_Za_Ostatnim ( Node * ostatni, Node * nowy){  

	  	if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}

	  ostatni->next=nowy;
	  nowy->prev=ostatni;
	  nowy->next=nowy;
	  koniec_listy.wsk=nowy;

	  rozmiar++;    

}


  // Metoda wstawia wezel przed pierwszym, podanym jako parametr jej wywolania
  void Wstaw_Wezel_Przed_Pierwszym ( Node * pierwszy, Node * nowy){

	  	if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}

	pierwszy->prev=nowy;
	nowy->next=pierwszy;
	nowy->prev=nowy;
	poczatek_listy.wsk=nowy;

	rozmiar++;

}


  // Metodaw wstawia wezel przed pozycje wskazywana przez iterator, podany jako parametr jej wywolania
  void Wstaw_Przed_Pozycje ( Iterator pozycja, Node * nowy){    

	  	if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}

	if(pozycja.wsk==poczatek_listy.wsk){                   // zabezpieczenie gdy wstawiamy przed pierwszym
		Wstaw_Wezel_Przed_Pierwszym ( pozycja.wsk,nowy);
		return ;}

	Iterator poprzedni=Prev(pozycja);
	
	nowy->next=pozycja.wsk;
	nowy->prev=poprzedni.wsk;
	pozycja.wsk->prev=nowy;
    poprzedni.wsk->next=nowy;
	
	rozmiar++;
}


  // Metoda odlacza od listy wezel, wskazywany przez iterator
  void Odlacz_Wezel ( Iterator iter){    
	 
	  	if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}

	Iterator poprzedni = Prev(iter);
	Iterator nastepny = Next(iter);

	iter.wsk->prev=NULL;
    iter.wsk->next=NULL;
    rozmiar--;

	if(poczatek_listy.wsk==iter.wsk){      // gdy odlaczany jest pierwszy wezel 
		 nastepny.wsk->prev=nastepny.wsk;
		 poczatek_listy.wsk=nastepny.wsk;
		 return;
	}


	if(koniec_listy.wsk==iter.wsk){       // gdy odlaczany jest ostatni wezel
		   poprzedni.wsk->next=poprzedni.wsk;
		   koniec_listy.wsk=poprzedni.wsk;
		   return;
	} 

    poprzedni.wsk->next=nastepny.wsk;
	nastepny.wsk->prev=poprzedni.wsk;

	return;
}



////////// PUNKT 4  ///////////////



 // Konstruktor bezparametryczny 
	Lista(){
	this->rozmiar=0;
	} 
	

	bool Lista_Is_Empty(){
		if(rozmiar==0)
			return true;
		else
			return false;
	}



	Lista(T wartosc) {   // konstruktor parametryczny 
	Node * nowy = new Node;
	nowy->next = nowy;
	nowy->prev = nowy;
	nowy->val=wartosc;
	poczatek_listy.wsk=nowy;
	koniec_listy.wsk=nowy;
	this->rozmiar=1;
	}

	

	// Konstruktor kopiujacy klasy Lista 
	// Przepisuje elementy wezel po wezle, warunek to ten sam rozmiar dwoch list.

	Lista(Lista & L){             



	  this->rozmiar=L.rozmiar;

	  Iterator iter= L.poczatek_listy;
	  Iterator koniec= L.koniec_listy;  

	         Node * nowy = new Node;
			 nowy->next = nowy;
			 nowy->prev = nowy;
			 nowy->val=iter.wsk->val;
			 this->poczatek_listy.wsk=nowy;
			 this->koniec_listy.wsk=nowy;

	while(iter.wsk!=koniec.wsk){

		     iter=Next(iter);
			 Node * kolejny = new Node;
			 kolejny->val=iter.wsk->val;
			 Przekopiuj_Wezel(koniec_listy.wsk,kolejny);
		}
		
	}


// Dodatkowa przydatna metoda, wykorzystywana jest w konstruktorze kopiujacym.
// Sluzy do dodawania kolejnym wezlow podczas kopiowania listy.
void  Przekopiuj_Wezel ( Node * ostatni, Node * nowy){   

	  

	  ostatni->next=nowy;
	  nowy->prev=ostatni;
	  nowy->next=nowy;
	  koniec_listy.wsk=nowy;

}


// Przypisanie L-wartosci 
// Iteratory obiektu klasy Lista stojacego po lewej stronie znaku '=', wskazuja teraz 
// na te same miejsca w pamieci, co Iteratory obiektu stojacego po prawej stronie znaku.

Lista & operator = ( const Lista & L){    

		rozmiar=L.rozmiar;

		
		this->poczatek_listy=L.poczatek_listy;
		this->koniec_listy=L.koniec_listy;

		return *this;

	}


// Destruktor obiektu klasy Lista.
// Do wskaznikow na kolejne wezly przypisywana jest wartosc NULL.
	
	~Lista() {        

		Iterator i1=poczatek_listy;
		Iterator i2=koniec_listy;
		Iterator i;

		while(i1.wsk!=i2.wsk){
			i=i1;
			i1=Next(i1);
			delete i.wsk;
	}

  }


// Metoda wstawia element o podanej w parametrze jej wywolania wartosci na poczatek listy
void push_front( T const &  wartosc){



	Node * pierwszy = poczatek_listy.wsk; 
	Node * nowy = new Node;
	nowy->val=wartosc; 
	pierwszy->prev=nowy;
	nowy->next=pierwszy;
	nowy->prev=nowy;
	poczatek_listy.wsk=nowy;

	rozmiar++;

}


// Metoda wstawia element o podanej w parametrze jej wywolania wartosci na koniec listy
void push_back( T const &  wartosc){

	Node * ostatni=koniec_listy.wsk;
	Node * nowy= new Node;
	nowy->val=wartosc;
	ostatni->next=nowy;
	nowy->prev=ostatni;
	nowy->next=nowy;
	koniec_listy.wsk=nowy; 

	rozmiar++;
}


// Metoda usuwa pierwszy element listy
void pop_front (){

		if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}

	Iterator iter=poczatek_listy;
	poczatek_listy=Next(poczatek_listy);
	delete iter.wsk;
	rozmiar--;

}


// Metoda usuwa ostatni element listy
void pop_back(){

		if(Lista_Is_Empty()){
         cout<<"Lista jest pusta !"<<endl;
		 return;
	}  

	Iterator iter=koniec_listy;
	koniec_listy=Prev(koniec_listy);
	delete iter.wsk;
	rozmiar--;
}


// Zwraca iterator do poczatku listy
	Iterator Begin() { 
		return poczatek_listy;
	}


// Zwraca iterator do konca listy ( w zasadzie do elementu za koncem listy, ale ostatni->next wskazuje na samego siebie)
	Iterator End(){
		return koniec_listy;
	}


// Metoda zwraca dlugosc listy
const size_t size() const {
     return rozmiar;
}


// Metoda zamienia 2 listy, czyli wartosci pol rozmiar oraz odpowiednie iteratory
void ZamienListy ( Lista & L2) {

   size_t r1=this->rozmiar;
   this->rozmiar=L2.rozmiar;
   L2.rozmiar=r1;

	Iterator p1=this->poczatek_listy;
	Iterator k1=this->koniec_listy;

	this->poczatek_listy=L2.poczatek_listy;
	this->koniec_listy=L2.koniec_listy;

	L2.poczatek_listy=p1;
	L2.koniec_listy=k1;

}


 friend ostream & operator << <> ( ostream & StrmWy ,  Lista<T>  & L);
 friend istream & operator >> <> ( istream & StrmWe, Lista<T> & L);
};


//  Przeciazenie operatora strumieniowego << , umozliwia wyswietlanie elementow listy na wyjscie
template <typename T>
ostream & operator << ( ostream & StrmWy , Lista<T> & L ){

	Lista<T>::Iterator iter=L.poczatek_listy;

	for( int i=0;i<L.size();i++){
       StrmWy<<iter.wsk->val<<endl;
	   iter=L.Next(iter);
	}

return StrmWy;
}


//  Przeciazenie operatora strumieniowego >> , umozliwia wczytywanie elementow listy m.in z klawiatury
template <typename T>
istream & operator >> ( istream & StrmWe ,  Lista<T> & L ){

	cout<<" Ile elementow zostanie dodanych ? "<<endl;
	int ilosc;
	cin>>ilosc;

	T element;

	cout<<" Prosze wprowadzac elementy : "<<endl;

	for( int i=0; i< ilosc ; i++){
		cin>>element;
	    L.push_back(element);
	}

return StrmWe;
}







int _tmain(int argc, _TCHAR* argv[])
{

	// ZESTAW PRZYKŁADOWYCH WYWOŁAŃ WYMAGANYCH FUNKCJI 

	
	Lista<int> L(1);      // wywolanie kostruktora, pierwszy wezel ustawmy na wartosc 1 
	
	
	Lista<int>::Node * nowy = new Lista<int>::Node(2);   // dodaje na koniec
	L.Wstaw_Wezel_Za_Ostatnim(L.End().wsk,nowy);

	Lista<int>::Node * kolejny = new Lista<int>::Node(0);
	L.Wstaw_Wezel_Przed_Pierwszym(L.Begin().wsk,kolejny);   // dodaje na poczatek

	Lista<int>::Node * w3= new Lista<int>::Node(55);
	L.Wstaw_Przed_Pozycje(L.Next(L.Begin()),w3);    // dodaje przed drugi element 

	cout<<L<<endl;
	cout<<"~~~~"<<endl;

	int & zm = L.Zwroc_Referencje(L.Begin());   // zmieniamy wartosc pierwszego elementu listy
	zm=77;

	cout<<L<<endl;
	cout<<"~~~~"<<endl;

	L.Odlacz_Wezel(L.Prev(L.End()));    // usunmy przedostatni wezel

	cout<<L<<endl;
	cout<<"~~~~"<<endl;

	cin>>L; // umozliwia dodanie dowolnej ilosci elementow do listy 

	cout<<L<<endl;
	cout<<"~~~~"<<endl;

	
	Lista<int> L2=L;   // konstruktor kopiujacy

	cout<<L2<<endl;
	cout<<"~~~~"<<endl;

	L2.push_front(56);      // dodajemy wartosc 56 na poczatek listy L2

	cout<<L2<<endl;
	cout<<"~~~~"<<endl;

	L2.push_back(-90);    // dodajemy wartosc -90 na koniec listy L2

	cout<<L2<<endl;
    cout<<"~~~~"<<endl;


	L2.pop_back();     // zdejmujemy ostatni element listy L2

	cout<<L2<<endl;
	cout<<"~~~~"<<endl;

	L2.pop_front();    // zdejmujemy pierwszy element listy L2

	cout<<L2<<endl;
	cout<<"~~~~"<<endl;


	if(L2.Czy_Wezel_Prawidlowo_Polaczony(L2.Next(L2.Begin()).wsk))  // sprawdzmy czy wezel 2-gi listy L2 jest polaczony
		cout<<"Wezel polaczono prawidlowo "<<endl;          
	else 
		cout<<"Wezel nie jest polaczony prawidlowo"<<endl;


    cout<<"Koniec programu. Wcisnij ENTER"<<endl;
	
	getchar();
	getchar();
	return 0;
}
