// main.cpp
#include <iostream>
#include "connect4.h"
#include <Windows.h>
 
int main()
{
 
	bool czlowiek=true;     // zaczyna gre czlowiek 
    Connect4 Gra;
 
    Gra.Witaj();
    Gra.Rysuj_plansze();
 
    do
    {
		//Sleep(1000);
        Gra.Czyja_kolej();
         
        if (czlowiek){    // zaczyna czlowiek
            Gra.Ruch_czlowieka();
			czlowiek=false; }
        else{
            Gra.Ruch_komputera();
			czlowiek=true;}

		std::cout<<"koniec"<<std::endl;
 
        Gra.Rysuj_plansze();
    }
    while (!Gra.Znajdz_wygranego(true) && !Gra.Czy_plansza_pelna() && Gra.Czy_mozna_wygrac());
    
	getchar();
	getchar();
    return 0;
}
