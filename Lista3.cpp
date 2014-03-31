#include "stdafx.h"
#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>

using namespace std;


// SZABLON KLASY KOPIEC
// UWAGA !!! - ELEMENTY KOPCA SĄ INDEKSOWANE OD 1 DO ROZMIAR ( indeks 0 nie jest uzywany w programie)
template <typename T>
class Kopiec {


T * tab;
size_t rozmiar;  


	public:



// Zwraca informacje o rozmiarze kopca 
const size_t Rozmiar() const {
	return rozmiar;
}


// Konstruktor pustego kopca, bezparametryczny
Kopiec (){   

this->rozmiar=0; 
tab= new T[this->rozmiar];

}


// Konstruktor kopiujacy
Kopiec ( Kopiec & K){    

	this->rozmiar=K.rozmiar;
	this->tab=new T[rozmiar+1];

	for(unsigned int i=1;i<=this->rozmiar;i++)
		 this->tab[i]=K.tab[i];

}


// Operator przypisania L-wartosci
Kopiec & operator = ( const Kopiec & K){  

	this->rozmiar=K.rozmiar;
	this->tab=new T[rozmiar+1];

	for(unsigned int i=1;i<=this->rozmiar;i++)
		 this->tab[i]=K.tab[i];

	return *this;

} 


// Destruktor obiektu klasy Kopiec
~Kopiec () {
if(tab!=NULL) delete []tab;
}



// Przeciążenie operatora indeksujacego, pozwala pobrac element o podanym indeksie.
T & operator [] ( size_t i){    
return tab[i];
     }




// Wstawia na koniec kopca element, podany jako parametr wywołania funkcji. 
void insert(T const & element){

        rozmiar++;
        T * tmp=new T[rozmiar+1];

       for(unsigned int i=1; i<rozmiar;i++)
             tmp[i]=tab[i];

	   tmp[rozmiar]=element;
       tab=tmp;
  }



// Metoda umożliwia wyświetlenie zwartości kopca na standardowe wyjście w zwarty i estetyczny sposób.
void Wyswietl (){

	if(this->rozmiar==0) cout<<"Kopiec jest pusty"<<endl;

    int x = (rozmiar + 1) / 2; 
	int k = 2;
  for(unsigned int i = 1; i <= rozmiar; i++)
  {
    for(int j = 1; j <= x - 1; j++) cout << " ";
    cout <<" "<< tab[i];
    for(int j = 1; j <= x; j++) cout << "  ";
    if(i + 1 == k)
    {
      k += k; x /= 2; cout << endl;
    }
  }

}


// Metoda zwraca rodzica, dla dziecka spod podanego indeksu jako parametr wywołania funkcji.
// W przypadku, gdy wywołano dla indeksu 1 ( tj. korzenia), zwracany jest korzeń.
T Zwroc_Rodzica ( const int dziecko){

	if(dziecko==1) return tab[dziecko];   // jesli to korzen to zwraca sam siebie

int rodzic=dziecko/2;

return tab[rodzic];


}



// Metoda zwraca indeks lewego dziecka, dla elementu spod podanego indeksu.
// Jeśli nie ma lewego dziecka, zwracany jest indeks rodzica.
int Zwroc_Indeks_Lewego_Dziecka ( const unsigned int rodzic){

unsigned int dziecko_l=(rodzic*2);

if(dziecko_l>this->rozmiar){
    return rodzic;  }

return dziecko_l;
}



// Metoda zwraca indeks prawego dziecka, dla elementu spod podanego indeksu.
// Jeżeli nie ma prawego dziecka, zwracamy jest indeks rodzica.
int Zwroc_Indeks_Prawego_Dziecka ( const unsigned int rodzic){

unsigned int dziecko_p=(rodzic*2+1);

if(dziecko_p>this->rozmiar){
    return rodzic;
}

return dziecko_p;
}



// Metoda umożliwia zamiane miejscami dwóch elementów kopca o indeksach podanych jako parametr wywołania funkcji.
void Swap (const int ind1, const int ind2){   

T val;
val=tab[ind1];
tab[ind1]=tab[ind2];
tab[ind2]=val;

}


// Metoda przywraca częsciowo własność w doł od elementu spod danego indeksu.
// Jest wielokrotnie wywoływana podczas przywracania własności całego kopca w doł przez metode Przywroc_Cala_Wlasnosc_W_Dol.
void Przywroc_Wlasnosc_W_Dol( const int index){

	/*Wyswietl();
	cout<<"!!"<<endl;*/

int dziecko_l=this->Zwroc_Indeks_Lewego_Dziecka(index);
int dziecko_p=this->Zwroc_Indeks_Prawego_Dziecka(index);


if(tab[index]>tab[dziecko_l]){
	if(tab[dziecko_l]>=tab[dziecko_p]){
     Swap(index,dziecko_p); 
	 Przywroc_Wlasnosc_W_Dol(dziecko_p);
      }
     else {
      Swap(index,dziecko_l);   
	  Przywroc_Wlasnosc_W_Dol(dziecko_l);

	 }

}

else if ( tab[index]>tab[dziecko_p]){
	Swap(index,dziecko_p); 
	Przywroc_Wlasnosc_W_Dol(dziecko_p);
   }
	
}



// Metoda przywraca częściowo własność kopca w górę od elementu spod zadanego indeksu.
// Jest wielokrotnie wywoływana podczas przywracania własności całego kopca w górę przez metodę Przywroc_Cala_Wlasnosc_W_Gore.
void Przywroc_Wlasnosc_W_Gore ( const int index){

	/*Wyswietl();
	cout<<"!!"<<endl;*/

	int rodzic=(index/2);
	if(index==1) return;

	if(index==rodzic*2){    // to lewe dziecko 
		if(index<rozmiar){   // ma brata ( istnieje tez prawe dziecko ) 
		   if(tab[index]<tab[rodzic]){
			    if(tab[index]<=tab[index+1]){
					  Swap(index,rodzic);
					  Przywroc_Wlasnosc_W_Gore(rodzic);}
				else {
					Swap(index+1,rodzic);
					Przywroc_Wlasnosc_W_Gore(rodzic); }
		   }
		}
		

		else {     // nie ma brata 
		     Swap(index,rodzic);
		     Przywroc_Wlasnosc_W_Gore(rodzic); }
         
	}

	else if ( index==(rodzic*2+1) ) {   // to prawe dziecko 
		   if(tab[index]<tab[rodzic]){
			    if(tab[index]<tab[index-1]) {
					 Swap(index,rodzic);
					 Przywroc_Wlasnosc_W_Gore(rodzic);
				}
				else {
					Swap(index-1,rodzic);
					Przywroc_Wlasnosc_W_Gore(rodzic);
				}

		   }
	}

}



// Metoda sortuje elementy, tworząc kopiec typu min ( w korzeniu kopca jest najmniejsza wartość).
// Wykorzystuje do tego metodę przywracania własności kopca w dół, począwszy od węzła będącego indeksem 
// równym połowie rozmiaru całego kopca, a kończąć na korzeniu. Taka kolejność umożliwia w czasie liniowym
// O(n) stworzenie kopca typu min.
void Buduj_Kopiec() {


	for( int i=floor(double(rozmiar/2));i>=1;i--)   // liniowy czas O(n) 
		Przywroc_Wlasnosc_W_Dol(i);               // zrodlo : https://informatyka.wroc.pl/node/433?page=0,3


}




// Metoda przywraca całkowicie własność kopca w dół od węzła spod zadanego indeksu.
// Wywołuje iteracyjnie metodę Przywroc_Wlasnosc_W_Dol, tyle razy, do którego
// ,,poziomu'' kopca należy dany element licząc od dołu ( zaczynając od liścia na samym dole).
// Takie postępowanie zapewnia prawidłowy przebieg operacji. 
void Przywroc_Cala_Wlasnosc_W_Dol(const int index){


double wysokosc_calkowita = log(double(this->rozmiar+1))/log(2.00);
wysokosc_calkowita=ceil(wysokosc_calkowita);

double odl_od_korzenia = log(double(index+1))/log(2.00);
odl_od_korzenia =ceil(odl_od_korzenia );

int odl_od_dolu=int((wysokosc_calkowita-odl_od_korzenia)); // tyle razy trzeba wywolac funkcje Przywroc_Wlasnosc_W_Dol


for (int i=1;i<=odl_od_dolu;i++){
    Przywroc_Wlasnosc_W_Dol(index);
}

}


// Metoda przywraca całkowicie własność kopca w górę od węzła spod zadanego indeksu.
// Wywołuje iteracyjnie metodę Przywroc_Wlasnosc_W_Gore, o jeden raz mniej niż ,,wysokosc''
// na której znajduje się element spod danego indeksu ( licząc od korzenia w dół, korzeń to 1 poziom itd.)
// Takie postepowanie zapewnia całkowite przywrócenie własności kopca w góre od węzła spod danego indeksu.
void Przywroc_Cala_Wlasnosc_W_Gore(const int index){

 double wysokosc = log(double(index+1))/log(2.00);
 wysokosc=ceil(wysokosc);


    for (int i=1;i<wysokosc;i++){    // wystarczy wywolac o raz mniej niz wysokosc na ktorej jest dany wezel
        Przywroc_Wlasnosc_W_Gore(index);
       }

}



// Metoda zamienia zawartość dwóch kopców tego samego typu. 
void Zamien_Zawartosc_Dwoch_Kopcow ( Kopiec & K2){

	T * tab_pomocnicza=new T[this->rozmiar+1];

	for ( unsigned int i=1;i<=this->rozmiar;i++)
		tab_pomocnicza[i]=this->tab[i];

	for ( unsigned int i=1;i<=this->rozmiar;i++)
	       this->tab[i]=K2.tab[i];


	K2.tab=tab_pomocnicza;

}


// Pobieranie korzenia kopca. Metoda zwraca wartość elementu znajdującego się w korzeniu kopca. 
T top(){ 

	return tab[1];

}


// Metoda umożliwia usunięcie korzenia kopca. W jego miejscie wędruje ostatni element kopca, zatem jego rozmiar 
// zmniejsza się o 1. Po dokonaniu tej operacji kopiec automatycznie jest sortowany. W tym celu wystarczy przywrócić
// jego własność w dół od elementu wstawionego na miejscie usuniętego korzenia.
void pop(){  

        T * tmp=new T[rozmiar];

		tmp[1]=tab[rozmiar];  // w miejsce korzenia wedruje ostatni el kopca

       for(unsigned int i=2; i<rozmiar;i++)
             tmp[i]=tab[i];

	   this->rozmiar--;
       this->tab=tmp;

	   this->Przywroc_Cala_Wlasnosc_W_Dol(1);  // od korzenia w dol sergregacja
}



// Metoda usuwa element kopca o podanym indeksie. W jego miejsce jest wstawiany ostatni element. 
// Jeżeli usuwany jest ostatni element, wówczas tylko zmniejsza się jego rozmiar o 1.
void remove(size_t index){  // usuwa el o podanym indeksie, wstawia w jego miejsce ostatni el

	if(index==1) this->pop();

		T * tmp=new T[rozmiar];
		
        for(int i=1;i<index;i++)
			tmp[i]=tab[i];

		if(index<rozmiar) // gdy nie usuwamy ostatniego
		tmp[index]=tab[rozmiar];

		for(int i=(index+1);i<rozmiar;i++)
			tmp[i]=tab[i];


		this->rozmiar--;
		this->tab=tmp;
}


// Metoda przywraca własność kopca, jeżeli wiadomo, że element o podanym indeksie zmniejszył wartość. 
// Wykorzystuje do tego metodę przywracania całkowicie własności w górę, gdyż element, który zmniejszył wartośc
// na pewno może powędrować w górę kopca, nigdy w dół.
void decreased(size_t index){  
	this->Przywroc_Cala_Wlasnosc_W_Gore(index);

}



// Metoda przywraca własność kopca, jeżeli wiadomo, że element o podanym indeksie zwiększył wartość. 
// Wykorzystuje do tego metodę przywracania całkowicie własności w dół, gdyż element, który zwiększył wartość
// na pewno może powędrować w dół kopca, nigdy w górę. 
void increased(size_t index){

	this->Przywroc_Cala_Wlasnosc_W_Dol(index);

}


// Metoda przywraca własnośc kopca, jeżeli wiadomo, że element o podanym indeksie zmienił wartość.
// W tym celu najpierw przywracana jest cała własność kopca w górę, a następnie w dół, dla elementu spod zadanego indeksu.
void updated(size_t index){

    this->Przywroc_Cala_Wlasnosc_W_Gore(index);
	this->Przywroc_Cala_Wlasnosc_W_Dol(index);

}


// Metoda łączy dwa kopce tego samego typu w jeden, po czym przywraca własność całego kopca. 
void merge(Kopiec & K2){

	size_t rozmiar_1=this->rozmiar;
	this->rozmiar=(rozmiar+K2.rozmiar);
	T * tmp=new T[this->rozmiar+1];

	for(int i=1;i<=rozmiar_1;i++)
		tmp[i]=tab[i];

	for(int i=(rozmiar_1+1);i<=this->rozmiar;i++)
		 tmp[i]=K2.tab[i-rozmiar_1];

	this->tab=tmp;

	
  this->Buduj_Kopiec();
}



// Metoda TESTOWANIA KOPCA
// Sprawdza poprawność posortowania elementów kopca w kopiec typu min.
// Jako parametr wywołania przyjmuje indeks ostatniego elementu kopca.
// Wywoluje sie iteracyjnie, sprawdzajac czy dziecko jest większe od rodzica 
// lub równe rozpoczynając od ostatniego elementu kopca, kończąc na korzeniu. 
// Na wyjściu pojawia się informacja o rezultacie testu.
void Test_Kopca (int indeks){   
	
   if(indeks==0){
	   cout<<"Kopiec jest pusty "<<endl;
	   return;
   }

	if(indeks==1){
		cout<<"Kopiec posortowany prawidlowo"<<endl;
		return;
	}

	int rodzic=indeks/2;

	if(tab[indeks]>=tab[rodzic])
		Test_Kopca(indeks-1);

	else{
		cout<<" Blad. Kopiec posortowano nieprawidlowo ! "<<endl;
		return;
	}
}


};






int _tmain(int argc, _TCHAR* argv[]){


Kopiec<int> K;  // tworzymy pusty kopiec


for(int i=10;i>=1;i--)   // dodajemy 10 elementow 
	K.insert(i); 

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 



 K.Buduj_Kopiec();  // budujemy z tych elementow kopiec typu min

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 


 K.Test_Kopca(10);  // Testujemy przeprowadzona operacje, rozpoczynając od ostatniego elementu

 K.insert(99); // dodajemy na koniec el 99 


 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 
 
 K.remove(K.Rozmiar());  // usuniemy teraz el 99 z kopca, czyli element ostatni

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

 cout<< " Korzen kopca ma wartosc : "<<K.top()<<endl;

 K.pop(); // usuwamy korzen kopca ( automatycznie jest sortowany)

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

K[2]=999;  // element 6 zwieksza znacznie wartosc na 999

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 


K.increased(2);    // wiemy ze ten element zwiekszyl wartosc, przywrocmy zatem wlasnosc kopca 

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

 K[9]=0;  // ostatni element zmnieszyl wartosc na 0 

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

 K.decreased(K.Rozmiar()); // przywrocmy wlasnosc kopca, wiedzac ze element ostatni zmniejszy wartosc
 
 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

 K[5]=1;       // 5-ty element zmienil wartosc 
 K.updated(5);

 K.Wyswietl();    // tak teraz wyglada kopiec 
 cout <<endl <<  " ~~~~~" <<endl; 

 Kopiec<int> K2;

 for(int i=5;i>=1;i--)   // tworzymy drugi kopiec, 5-elementowy o wartosciach 10,8,6,4,2
	K2.insert(i*2); 

 K.merge(K2);  // laczymy oba kopca, sa one automatycznie sortowane

 K.Wyswietl();  // efekt 
cout <<endl <<  " ~~~~~" <<endl; 


getchar();
return 0;
}
