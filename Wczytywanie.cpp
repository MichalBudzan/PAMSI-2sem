
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdlib.h> 
#include <ctime>  
#include <cstdio>
#include <cmath>
#include <windows.h>
using namespace std;


/*!
 *\brief  Definicja klasy Liczby  
 * 
 * Obiekty tej klasy reprezentuj¹ wczytane liczby z pliku .txt.
 * Sk³adaj¹ siê z dwóch pól, zmiennej informuj¹cej o iloœci wczytywanych liczb oraz z tablicy, 
 * w której s¹ one przechowywane. 
 *                      
 * 
 */ 
class Liczby { 
	
	private:
	
	/*!
	 * Pole przechowuje informacjê o iloœci wczytanych liczb
	 */ 
	int ilosc;
	/*!
	 * Tablica zawiera wczytane liczby z pliku .txt
	 * Dyrektywa przeprocesora ROZMIAR, ogranicza maksymaln¹ iloœæ wczytanych liczb.
	 * Jej wartoœæ mo¿na zmieniaæ, w zale¿noœci od potrzeb. 
	 */ 
	int * tablica;
		
	public :
	
/*!
*\return Zwraca wartoœæ pola rozmiar klasy Liczby.
* 
*/ 
int IloscLiczb() { return ilosc; }
	
/*!
 * Modyfikuje wartoœæ pola rozmiar w klasie Liczby. 
 *
 */  	
void ZapiszIloscLiczb ( int ile ) { ilosc=ile; } 


/*!
 * Zwraca odpowiedni element tablicy tab_liczb. 
 * 
 */ 
int Tablica(int indeks) { return tablica[indeks]; }  


/*!
 * Metoda przypisuje wartoœæ odpowiedniemu elementowi tablicy tab_liczb.
 * U¿ywana podczas wczytywania liczb z pliku .txt
 * 
 */ 
void Tablica(const int index,int wartosc) {  
	if ( index > IloscLiczb() ){
	    cout<<" Przekroczono zakres tablicy ! "<<IloscLiczb()<<endl;  
	    return ; } 
	tablica[index]=wartosc; } 
	


/*!
 *\brief Konstruktor parametryczny
 * 
 * Tworzy obiekt klasy Liczby, alokujac pamiec na tablice dynamiczna o rozmiarze zadanym
 * jako parametr.
 */ 
Liczby(int rozmiar);



/*!
 *\brief  Wyœwietlanie liczb 
 * 
 * Zadaniem funkcji jest wyœwietlenie liczb na wyjœcie. S¹ zapisane w obiekcie klasy Liczby,
 * który jest parametrem jej wywo³ania.
 * 
 */ 
int WyswietlLiczby();



/*!
 *\brief Metoda dodaje do tablicy element o zadaniej wartosci
 * 
 * Wykorzystywana jest 'realokacja' tablicy, gdyz jej rozmiar ulega teraz zwiekszeniu.
 * W tym celu tworzona jest nowa, wieksza tablica dynamiczna, do ktorej 
 * przepisywane sa dane oraz dodawany element.
 * 
 */ 
int DodajElement(int wartosc);


/*!
 *\brief Metoda dodaje do tablicy elementy zapisane w innym obiekcie klasy Liczby 
 * 
 * Polega to na polaczeniu dwoch tablic, zawartych w obiektach klasy Liczby.
 * Tworzona jest nowa tablica dynamiczna o odpowiednim rozmiarze.
 * Dane zapisywane sa w tablicy obiektu na rzecz ktorego wywolana jest ta metoda.  
*/
int DodajElementy (Liczby & L2);



/*!
 *\brief Metoda zamienia miejscami elementy tablicy o indeksach i oraz j.
 * 
 * Wykorzystuje 2 zmienne pomocnicze, po zamianie miejsc wyswietla zawartosc tablicy. 
 */ 
int ZamienMiejscami ( int i , int j);



/*!
 *\brief  Wymna¿anie liczb 
 * 
 * Zadaniem funkcji jest wymno¿enie wczytanych liczb z pliku .txt przez stala przekazana
 * jako parametr wywolania funkcji.
 * Wyniki przechowywane s¹ w obiekcie klasy Liczby.
 */ 
int WymnozLiczby(int razy);



/*!
 *\brief Sprawdzenie wyników mno¿enia 
 * 
 * Uzyskane wyniki, s¹ porównywane z liczbami zawartymi w drugim pliku .txt.
 * Odpowiadaj¹ one poprawnym wynikom. Funkcja sprawdza czy wszystko siê zgadza, informuj¹c  
 * o rezultacie u¿ytkownika poprzez komunikat na wyjœciu.
 *
 * \return Zwraca 0, gdy wyniki uzyskane s¹ poprawne. W przeciwnym wypadku zwraca 1.
 *          Gdy ilosci danych w tablicach sa rozne, zwraca -1.
 * 
 */   
int SprawdzWyniki(Liczby & wyniki);



/*!
 *\brief Metoda odwraca kolejnosc liczb w tablicy
 * 
 * Wykorzystuje tablice pomocnicza. Po dokonaniu czynnosci, wyswietla
 * zawartosc tablicy.
 */ 
int OdwrocKolejnosc();



/*!
 *\brief Przeciazenie operatora == dla obiektow klasy Liczby
 * 
 * Metoda porownuje czy obiekty tej klasy sa identyczne, czyli czy 
 * tablice z danymi maja taka sama zawartosc. Informuje uzytkownika 
 * o rezultacie porownania.
 * 
 * \return Zwraca true, jesli obiekty sa identyczne. W przeciwnym wypadku zwraca false.
 */   
bool operator ==  ( Liczby & L2);

};



Liczby::Liczby( int rozmiar){

	tablica=new int[rozmiar];
}




/*!
 *\brief  Wczytywanie liczb z pliku .txt
 * 
 * Funkcja wczytuje liczby z pliku .txt. Wykorzystywana zarówno przy wczytywaniu liczb do przemo¿enia
 *, jak i do wczytywania liczb z pliku z poprawnymi wynikami.
 * 
 */ 
Liczby WczytajLiczby() {
	
	
	cout<<"Podaj nazwe pliku : "<<endl;
	string nazwa;
	cin>>nazwa;
	
	fstream plik1;
    plik1.open( nazwa.c_str() , std::ios::in | std::ios::out );
  
  
     int ilosc;
     int wartosc;
   
    if( plik1.good() !=true ){
		cout << " B³¹d otwarcia pliku "<<endl;
		return 1;
	    }
	 
		plik1>>ilosc;

		Liczby wczytane(ilosc+1);   
		wczytane.ZapiszIloscLiczb(ilosc);
		wczytane.Tablica(0,ilosc);
		
	
        for( int i=1;i<=ilosc;i++){
			plik1>>wartosc;
			wczytane.Tablica(i,wartosc);
		}
		
		
		
return wczytane;
}




int Liczby::WyswietlLiczby(){
	

	for ( int i=0;i<=this->IloscLiczb();i++)
	    cout<<this->Tablica(i)<<endl;
	
	cout<<"~~~"<<endl;
	return 0;
	
}



int Liczby::WymnozLiczby(int razy){
	
	cout<<" Wymnazam : "<<endl;
	for ( int i=1;i<=this->IloscLiczb();i++)
		   this->Tablica(i,razy*(this->Tablica(i)));

	cout<<" Po wymozeniu przez : "<<razy<<endl;
	  this->WyswietlLiczby();
	
	return 0;
	
}



int Liczby::SprawdzWyniki(Liczby & wyniki){
	
	if(this->IloscLiczb()!=wyniki.IloscLiczb()){
		 cout<<" Rozmiary wczytanych plików s¹ ró¿ne !" <<endl;
		 return -1;
	}

	for ( int i=0;i<=this->IloscLiczb();i++)
	      if (this->Tablica(i)!=wyniki.Tablica(i)){
	           cout<<" B³ad ! Dotyczy liczby nr : " << i <<endl;
	            return 1; } 
	     
	    
	   cout << " Wyniki s¹ poprawne :) "<<endl;     
	           
	 return 0;          
	
}



int Liczby::ZamienMiejscami ( int i , int j){

	int wart1=this->Tablica(i);
	int wart2=this->Tablica(j);


	this->Tablica(i,wart2);
	this->Tablica(j,wart1);

	cout<<" Po zamianie miejscami : "<<endl;
    this->WyswietlLiczby();


	return 0 ;

}



int Liczby::OdwrocKolejnosc(){


	int * tab_pomocnicza=new int[this->IloscLiczb()+1];
	int zm=0;


	for ( int i=this->IloscLiczb() ; i >= 0 ; i--){
		tab_pomocnicza[i]=this->Tablica(zm++);
	}


	for (int j=0; j <= this->IloscLiczb() ; j++) {
		this->Tablica(j,tab_pomocnicza[j]);
	}

    cout<<" Po odwroceniu kolejnosci : "<<endl;
     this->WyswietlLiczby();


	delete [] tab_pomocnicza;
	return 0;

}




int Liczby::DodajElement(int wartosc) {


	int nowy_rozmiar=(this->IloscLiczb()+2);
    int * tmp= new int[nowy_rozmiar];
 
   for ( int i=0; i < (nowy_rozmiar-1); i++) 
	    tmp[i]=tablica[i];
 
			delete [] tablica;
   
			tablica = new int[nowy_rozmiar];
	
    for ( int i=0; i < (nowy_rozmiar-1); i++) 
	       tablica[i]=tmp[i];
			
			tablica[nowy_rozmiar-1]=wartosc;
			this->ZapiszIloscLiczb(nowy_rozmiar-1);

			delete [] tmp;
          
			this->WyswietlLiczby();


	return 0;
}


int Liczby::DodajElementy (Liczby & L2){


   int nowy_rozmiar=(this->IloscLiczb()+L2.IloscLiczb()+2);
   int * tmp= new int[nowy_rozmiar];

	for ( int i=0; i < (nowy_rozmiar-IloscLiczb()); i++) 
	    tmp[i]=tablica[i];
 
             delete [] tablica;
     
	         tablica = new int[nowy_rozmiar];
	
    for ( int i=0; i <= (this->IloscLiczb()); i++) 
	       tablica[i]=tmp[i];
	
	for ( int j=(this->IloscLiczb()+1); j < nowy_rozmiar ; j++)
	       tablica[j]=L2.Tablica(j-(this->IloscLiczb()+1)); 
	
	        this->ZapiszIloscLiczb(nowy_rozmiar-1);
	 
	        delete [] tmp;
          
            this->WyswietlLiczby();

	return 0; 
}




bool Liczby::operator ==  ( Liczby & L2) {
	 
	if(this->IloscLiczb()!=L2.IloscLiczb()){
		cout<<" Ilosc danych jest rozna ! "<<endl;
		return false;
	}
	
	for ( int i=0;i<=this->IloscLiczb();i++)
	      if (this->Tablica(i)!=L2.Tablica(i)){
	           cout<<" Blad ! Dotyczy indeksu nr : " << i <<endl;
	            return false; } 
	     
	    
	   cout << " Wyniki s¹ poprawne :) "<<endl;  
	 
	 return true;
}

LARGE_INTEGER startTimer()
{
LARGE_INTEGER start;
DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
QueryPerformanceCounter(&start);
SetThreadAffinityMask(GetCurrentThread(), oldmask);
return start;
}


LARGE_INTEGER endTimer(){
LARGE_INTEGER stop;
DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
QueryPerformanceCounter(&stop);
SetThreadAffinityMask(GetCurrentThread(), oldmask);
return stop;
}


int main()
{

LARGE_INTEGER performanceCountStart,performanceCountEnd;
performanceCountStart = startTimer(); //zapamietujemy czas poczatkowy

//tutaj funkcje, ktorych mierzymy wydajnosc :

Liczby wczytane=WczytajLiczby();
wczytane.WyswietlLiczby();


wczytane.WymnozLiczby(2);


cout<<"Wczytaj wyniki : "<<endl;  
Liczby wyniki=WczytajLiczby();
wyniki.WyswietlLiczby();  

wczytane.SprawdzWyniki(wyniki);


///// zamiana miejsc

int i;
int j;

cout<<" Ktore liczby chcesz zamienic miejscami ? Prosze podac indeksy ? "<<endl;
cin>>i;
cout<<" Oraz : "<<endl;
cin>>j;

wczytane.ZamienMiejscami(i,j);

//////


wczytane.OdwrocKolejnosc();

////

int val;
cout<<" Podaj wartosc elementu ktory chcesz dodac : "<<endl;
cin>>val;

wczytane.DodajElement(val);

////

wczytane.DodajElementy(wyniki);



performanceCountEnd = endTimer(); //zapamietujemy koniec czasu
double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
cout << endl << "Time:" <<tm <<endl;


	getchar();
	getchar();
    return 0;
}



