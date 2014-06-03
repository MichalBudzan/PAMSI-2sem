// connect4.h

/**
* \file connect4.h
* \brief Deklaracja klasy Connect4 stanowiącej silnik gry
*/

#ifndef CONNECT4_H
#define CONNECT4_H
#include <vector>
 



/**  \brief Klasa Connect4 stanowiąca silnik gry
 * 
 *  Szczegółowe opisy poszczególnych metod znajdują się w pliku connect4.cpp
 */
class Connect4{

private:    // atrybuty prywatne klasy silnika gry 

    bool wrzucane_od_gory;          //  true - beda wrzucane od gory ; false - wybor wierz i kolumna
    int szer;                      // szerokosc
    int wys;                      // wysokosc
    int rzad;                    // ilosc w rzedzie by wygrac 
    int player;                 // ktory player gra ? 1 - czlowiek ; 2 - komputer
    int ilosc_ruchow;          // ile ruchow dokonano do tej pory w grze (licznik)
    int ilosc_pol;            // ilosc pol na planszy
    bool mozna_wygrac;       // czy mozliwe jest rozstrzygniecie gry


    std::vector<int>kolejka;					// lista z kolejnoscia kto rozpoczyna symulacje ruchu w procesie min-max ( zaczyna ten kto 'atakuje')
    std::vector<std::vector<int> > plansza;    // plansza do gry

public:

    Connect4();
 
    void Witaj();			   // ekran powitalny
    void Czyja_kolej();       // czyja kolej na ruch 
 
    void Ruch_czlowieka();       // ruch czlowieka
    void Ruch_komputera();      // ruch komputera
    void Ruch_Losowy();        // ruch losowy ( komputer w poczatkowej fazie gry)
    void Rysuj_plansze();     // wyswietl plansze
 
    bool Czy_plansza_pelna();       // czy plansza jest zapelniona 
    void Przelacz_gracza();        // nastepny gracz ( przelaczanie z czlowieka na komp. i na odwrot)
    bool Czy_mozna_wygrac();      // jesli nie bedzie mozliwe by ktos wygral gre to koniec, nie kontynuujemy jej  
  
	
	bool Wrzuc_zeton(int x, int y);               // wrzuca zeton na plansze
    void Kto_wygral(int player);                 // informacja o zwyciescy


    bool Znajdz_wygranego(bool ZnajdzRuch);       // czy ktos wygral ? oraz wywolanie procesu symulacji sztucznej inteligencji
    bool SzukajLinii(int x, int y, int x_kier, int y_kier, int IleBrakujeByWygrac, int ZetonGracza); 
	 // sprawdza czy z danego pola panszy jest mozliwe, aby wygrac jadac w ktora strone gora, dol, skos ? 
};
#endif // CONNECT4_H
