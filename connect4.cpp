// connect4.cpp

/**
* \file connect4.c
* \brief Definicje metod klasy Connect4, ktore odpowiadają za działanie gry. 
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "connect4.h"
 
 
/*!  \brief Konstruktor obiektu klasy Connect4
 *
 *  Wywoływany na początku programu, ustawia wartości pewnych parametrów gry :
 *  \param[in]  wrzucane_od_gory - zmienna typu bool, definiuje czy zetony będą wrzucane od góry tak jak w grze 
 *								   Connect4 oryginalnie ( wartość true). Jeśli chcemy definiować dokładnie gdzie 
 *								   dodajemy żeton ( który wiersz, która kolumna tak jak w kółko-krzyżyk), wówczas
 *								   ustawiamy ją na false.
 *
 * \param[in]  player - wartość 1 oznacza, że człowiek będzie miał żetony z numerem 1, a komputer z numerem 2. 
 *						Wartość 2 powoduje, że człowieka żetony będą miały wartość 2, a komputera wartość 1.
 *
 * \param[in]  mozna_wygrac - określa czy bieżąca rozgrywka ma szansę mieć rozstrzygnięcie na czyjąś korzyść ( wygraną).
 *							  W czasie gry jej stan może się zmienić na false, wówczas gra zostanie zatrzymana z odpowiednim
 *							  komunikatem na wyjściu.
 *
 * \param[in]  ilosc_ruchow - zmienna pełni rolę licznika, zlicza ilu dokonano ruchów w czasie gry ( ile żetonów jest na planszy)
 *
 *
 */
Connect4::Connect4(){


    srand (NULL);     
     
    // wartosc true spowoduje ze 'zetony' beda spadac pionowo, tak jak to jest 
	// w rzeczywistosci, zas false spowoduje wybor konkretnego pola w sensie wiersz oraz kolumna
    wrzucane_od_gory = true;
 
    player = 1;                 // jaki zeton bedzie miał człowiek ( z jaką cyfrą)
    mozna_wygrac = true;        // czy gre moze ktos wygrac, jesli juz nie to gra sie zakonczy
    ilosc_ruchow = 0;           // ilosc zapelnionych pol na planszy
}
 







/*! \brief Metoda wyświetla ekran powitalny na początku gry oraz pyta o parametry gry
 *
 * Dochodzi do interakcji z użytkownikiem, ustalane są wartości następujących zmiennych :
 *
 * \param[in]  rzad - określa zasadę rozgrywki, ile żetonów w rzędzie musi uzyskać gracz by ją wygrać
 *
 * \param[in] szer - określa szerokość planszy, czyli ilość jej kolumn
 *
 * \param[in] wys - określa wysokość planszy, czyli ilość jej weirszy
 *
 * Na koniec definiowana jest plansza w postaci wektora wektorów typu int, wszystkie pola są ustawiane na wartość 0.
 */
void Connect4::Witaj(){


    std::cout <<     "\n\n   ----- >   Witaj w grze  Connect 4 !! < ----- \n\n"<<std::endl;
	std::cout << " Ile w rzedzie by wygrac ? "<<std::endl;
	std::cin>>rzad;
	std::cout << " Podaj wymiary planszy ? Najpierw szerokosc ? " <<std::endl;
	std::cin>>szer;
	std::cout << " Teraz wysokosc ? "<<std::endl;
	std::cin>>wys;
		             
	 std::cout <<     "\n\n   ----- >   Witaj w grze  Connect 4 !! < ----- \n\n"
                      " Uzyskaj " << rzad << " takie same znaki w rzedzie by wygrac :) \n\n"
                    "Rozpoczynasz gre, jesli chcesz aby zaczal ja jednak komputer wcisnij 0 oraz ENTER\n\n"
                    " Powodzenia :) \n" << std::endl;


	ilosc_pol = szer * wys;   // ilosc miejsc na planszy 
 

    // Plansza w postaci wektora wektorow o odpowiednim rozmiarze, 
	// na poczatku wszystkie pola ustawimy na wartosc '0' 
    for (int x = 0; x < szer; x++)
    {
        plansza.push_back (std::vector<int>());
  
        for (int y = 0; y < wys; y++)
            plansza[x].push_back (0);
    }
}




	
/*! \brief Metoda wyświetla planszę na wyjściu
 *
 * W pewnej zwartej sekwencji na standardowym wyjściu wyświetlana jest aktualana zawartość wektora,
 * który reprezentuję planszę gry. Wszystko po to, by umożliwić graczowi podjęcie dalszej decyzji co do ruchu.
 *
 *
 */
void Connect4::Rysuj_plansze(){
 
    std::cout << std::endl;
 
    for (int y = 0; y < wys + 1; y++)
	{
 
        
        for (int x = 0; x < szer + 1; x++)
        {
 
 
            if (x == 0)
            {
                if (y < 10)
                    std::cout << " " << y << " ";
                else
                    std::cout << " " << y;                   
            }else if (y == 0)
            {
                if (x < 10)
                    std::cout << " " << x << " ";
                else
                    std::cout << " " << x;                               
            }else{           
            // zamiast zer wyswietla puste pola          
            if (!plansza[x - 1][y - 1])
                std::cout << "   ";
            else
                std::cout << " " << plansza[x - 1][y - 1] << " ";
            }
 

            if (x < szer)
                std::cout << "|";
        }
 
        std::cout << std::endl; 

        std::cout << std::endl;   
	}

}






/*! \brief Metoda wyświetla informację dotyczącą tego, czyja kolej na ruch nastąpiła w danej chwili.
 *
 */
void Connect4::Czyja_kolej(){

	if(player==1) 
		  std::cout << " Twoj ruch czlowieku :   " ;
	else 
		std::cout << " Poczekaj, komputer mysli nad ruchem .... "; 
}
 





/*! \brief Metoda zmiena wartość zmiennej player, która określa czyja nastąpiła kolej na ruch
 * 
 * \param[in] ilosc_ruchow - wartość tej zmiennej jest inkrementowana, ponieważ poprzedni użytkownik zrobił ruch
 */
void Connect4::Przelacz_gracza(){

    ilosc_ruchow++;
 
    if (++player > 2)    
        player = 1;
}
 




 
/*! \brief  Metoda umożliwia dokonanie ruchu przez człowieka 
 *
 * \param[in] x -  zmienna określa numer kolumny, do której człowiek chce wrzucić żeton. Wybranie numeru 0,
 *				   spowoduje, że człowiek rezygnuje ze swojej kolejki na ruch, oddając ją komputerowi.
 * 
 * \param[in] y -   jeśli gra jest uruchomiona w trybie kółko-krzyżyk, wówczas podejmowana jest decyzja co do 
 *                  numeru wiersza, do którego człowiek chce wrzucić żeton
 *
 */
void Connect4::Ruch_czlowieka(){
 
    int x,y = 0;
 
    do{
        std::cout << "\n Podaj numer kolumny do ktorej wrzucasz :  ";
        std::cin >> x;
         
        // jesli wybrano 0, to zacznie komputer
        if (!x)  
            Ruch_komputera();
        else if (!wrzucane_od_gory)  // gdy wrzucamy od gory to nie wybieramy wiersza
        {    
            std::cout << "\nPodaj numert wiersza: ";
            std::cin >> y;
            --y;
        }
 
    }    
    while (x && !Wrzuc_zeton(--x, y));
}


 


/*! \brief Metoda wrzuca żeton w losowe miejsce na planszy.
 *
 */
void Connect4::Ruch_Losowy(){
 
    int x, y;
    
    do
    {
        x = rand() % szer;   // losuje pozycje do wrzucenia
        y = rand() % wys; 
    }
    while (!Wrzuc_zeton(x, y));   
 
}
 





/*! \brief Metoda wywoływana jest gry następuje kolej na ruch komputera.
 *
 * Wywoływna jest metoda Znajdz_wygranego z parametrem o wartości false, co oznacza, że szukamy
 * optymalnego ruchu dla komputera.
 */
void Connect4::Ruch_komputera(){
	
    Znajdz_wygranego(false);    // (0) = nie szuka zwyciescy, lecz symuluje ruchy dalsze 
}






/*! \brief  Metoda wrzuca żeton na pole planszy podane w parametrze wywołania
 *
 * \param[in]  x - określa do której kolumny wrzucony będzie żeton 
 * \param[in]  y - określa do którego wiersza w podanej kolumnie będzie wrzucony żeton 
 *				   ( UWAGA - tylko w trybie kółko-krzyżyk ) 
 *
 * \return  Zwraca wartość logiczną false, gdy parametry podane w wywołaniu przekraczają zakres planszy,
 *			gdyż wówczas nie ma możliwości wrzucenia żetonu w to miejsce. Zwraca wartość true, gdy 
 *          poprawnie wrzucono żeton na planszę.
 */
bool Connect4::Wrzuc_zeton(int x, int y){


    if (x < 0 || x > szer - 1 || y < 0
        || y > wys - 1 || plansza[x][y])
        return false;    // wybor niemozliwy
     
 
      if (wrzucane_od_gory) // gdy wrzucamy od gory to ponizsza procedura to robi :
        for(y = 0; y < wys - 1 && !plansza[x][y + 1]; y++) {}
     
    // wkladamy zeton na dane miejsce
    plansza[x][y] = player;
     
    return true;        
}
 





/*! \brief  Ta funkcja umozliwia sprawdzenie czy ktos wygral gre, albo do symulacji ruchu komputera. ( sztuczna inteligencja)
 *
 *     Ta funkcja umozliwia sprawdzenie czy ktos wygral gre, albo do symulacji ruchu komputera ( ktory tez przeciez
 *	   musi sie zorientowac kto jest np blizej wygranej by zaatakowac lub w przeciwnym wypadku bronic sie blokujac zetonem
 *	   przeciwnika :
 *
 *
 *	  FLAGA JAKO PARAMETR WYWOŁANIA TEJ FUNKCJI : ( OKRESLA CEL DLA KTOREGO JA WYWOŁANO )
 *    
 *
 *   ZnajdzRuch = true
 *   Sprawdza czy ktos juz wygral rozgrywke
 *
 *   ZnajdzRuch = false
 *
 *	 Komputer stara sie wybrac taki ruch aby optymalnie wygrac za jednym ruchem, jesli
 *	 nie da sie za pierwszym, to szuka nastepnego najlepszego w kolejce, który umożliwi mu wygraną w 
 *	 1 dodatkowej rundzie. Jeśli również nie istnieje taka możliwość to szuka takiego, który da wygraną
 *	 w 2 dodatkowych rundach.... itd. 
 *
 *	Szukamy poprostu dla komputera takiej sekwencji wrzucania żetonow, by wygral przy najmniejszej
 *	ilości ruchów.
 *
 *
 *   IleBrakujeByWygrac - wartość zmiennej daje informacje o tym ile ruchow potrzeba JESZCZE by wygrac..
 *                      Czyli gdy ma wartosc 0, to juz mamy zwyciesce
 *						Gdy 1, to czas na decydujacy ruch by wygrac
 *						itd.... ( oczywiscie wszystko przy założeniu, że przeciwnik wcześniej nie zablokuje ruchu swoim żetonem)
 *   
 *
 * \return Metoda zwraca wartosc true, gdy ktos wygral rozgrywke w danej chwilii lub wartosc false, jesli nadal nie znalezlismy
 *		   rozstrzygnięcia trwajacej rozgrywki.
 */
bool Connect4::Znajdz_wygranego(bool ZnajdzRuch){ // true - sprawdza czy ktos juz wygral ; false - symuluje ruchy komputera, by wybrac najlepszy
     
      
 
 
    int ZetonGracza;   // informacja jaki symbol ma zeton aktualnie obslugiwanego gracza
    int IleDoKonca;     //  rola flagi
 

    if (ZnajdzRuch)
         IleDoKonca = 0;               // szukamy tylko czy ktoś już wygrał grę
    else if (ilosc_ruchow >= 2)
         IleDoKonca = rzad;			   // kazdy zrobil juz swoj ruch 
    else
         IleDoKonca = rzad - 1;        // to pierwszy ruch komputera, bedzie on losowy bo tak chcemy, wiec recznie ustawimy taka wartosc
         
 
    /*
	Tworzymy za pomocą prostej listy kolejność, którego gracza ruch symulujemy jako pierwszy.
	Oczywiście jest to bierzący, czyli komputer, bo teraz jego kolej.
	*/

    std::vector<int>::iterator it;
    kolejka.clear(); 
 
    for(int i = 1; i <= 2; i++){
        if (player == i) // bierzacy gracz na poczatku listy ( w symulacji AI to bedzie komputer)
            kolejka.insert(kolejka.begin(), player);
        else
            kolejka.push_back(i); // drugi na koncu
 
	}


	//////////////////////////////////     Algorytm AI ////////////////////////////////////


    for(int IleBrakujeByWygrac = 0; IleBrakujeByWygrac <=  IleDoKonca; IleBrakujeByWygrac++)
    {
 
        for(int i = 0; i < 2; i++)
		{
 
            ZetonGracza = kolejka[i]; // ktorego gracza ruch symulujemy w danej chwili


            for(int x = 0; x < szer; x ++)
			{
                   for(int y = 0; y < wys; y++)
                {   // Szukamy w ktora strone mozna by 'szukac szczescia' 
                    if (SzukajLinii(x, y, +0, +1, IleBrakujeByWygrac, ZetonGracza) ||   // pion
                        SzukajLinii(x, y, +1, +0, IleBrakujeByWygrac, ZetonGracza) ||   // poziom
                        SzukajLinii(x, y, +1, +1, IleBrakujeByWygrac, ZetonGracza) ||   // skos gora-prawo
                        SzukajLinii(x, y, -1, +1, IleBrakujeByWygrac, ZetonGracza))     // skos lewo- gora
					{   
 
                        // Czy wygrał ktoś ? 
                        if (IleBrakujeByWygrac == 0) 
                        {
                            Kto_wygral(player);
                            return true;
                        }else
                        {    // info jaka taktyke wybrano, wynikajaca z tego komu blizej do wygranej
                            if (ZetonGracza == player)    // szybciej wygra komputer to atakuje
                                std::cout << "\nRuch ofensywny - by wygrac!\n\n";
                            else						  // szybciej czlowiek , wiec trzeba obronic sie
                                std::cout << "\nRuch defensywny - by nie przegrac!\n\n";
 
                            return true;
                        }
     
                    }
                }
            }
		}
    }


	
   if(ZnajdzRuch==false){    // gdy nie znaleziono ruchu umozliwiajacego wygrac
         
        // nie byl to pierwszy ruch, wiec juz nie dojdzie do czyjejs wygranej
        if (ilosc_ruchow >= 2)       
            mozna_wygrac = false;
        else
        {
            std::cout << "\n Dokonuje losowego wyboru : ";
            Ruch_Losowy();
        }
	}           
 
    return false;
 
}
 




/*! \brief Metoda ma za zadanie sprawdzenie czy w danym kierunku przeszukiwania planszy da radę szybko stworzyć rząd żetonów
 *
 * 
 * \param[in] x_kier - określa w którą stronę poziomo szukamy wolnego pola na żeton
 * \param[in] y_kier - określa w którą stronę pionowo szukamy wolnego pola na żeton
 * \param[in] puste -  licznik pustych pól znajdujących się w danym rzędzie na planszy, który przeszukujemy 
 * \param[in] IleBrakujeByWygrac - zmienna określa dla ilu ruchów maksymalnie szukamy miejsca na utworzenie gotowego 
 *								   rzędu żetonów, który da wygraną.
 * \param[in] ZetonGracza - okresla ktorego gracz ruch symulujemy w danej chwilii. Jest to 1 dla czlowieka, 2 dla komputera
 *
 * \param[in] nowe_x - wspolrzedna 'x' miejsca w ktore wrzucimy zeton
 * \param[in] nowe_y - wspolrzedna 'y' miejsca w ktore wrzucimy zeton
 *
 *
 * \return Jezeli napotkamy w rozpatrywanym rzedzie żeton przeciwnika, to juz wiemy na pewno ze tutaj nie odniesiemy sukcesu
 *		    zwracamy false, musimy szukac gdzie indziej. Gdy zajdzie przeciwna sytuajca, wykonywana jest metoda WrzucZeton,  ktora
 *			doda zeton na wskazane miejsce, a zwracana jest wartość logiczna true.
 */
bool Connect4::SzukajLinii(int x, int y, int x_kier, int y_kier, int IleBrakujeByWygrac, int ZetonGracza){

     
    // czy nie przekroczymy zakresu planszy przy sprawdzaniu
    if (x + x_kier*(rzad-1) < 0 || x + x_kier*(rzad-1) >= szer
        || y + y_kier*(rzad-1) < 0 || y + y_kier*(rzad-1) >= wys){
        
        return false;
    }
     

    int puste = 0;    // ilosc wolnych miejsc w rozpatrywanym rzedzie
    int nowe_x = 0;    // wspolrzedne pustego miejsca na ktore mozna wrzucic zeton
    int nowe_y = 0;
 
    for (int i = 0; i < rzad; i++)    // ta petla wykona sie cala poprawnie wtedy i tylko wtedy gdy w rzedzie bedzie wygrana 
    {                                 // lub brakowac bedzie (rzad-IleBrakujeByWygrac) zetonow
         

		/* W tej petli wyszukuje sie nastepny mozliwy ruch gracza poprzez szukanie 
		  pustego miejsca na planszy obok kilku jego zetonow.
		  Jesli zmienna IleBrakujeByWygrac=0, wowczas sprawdzane
		  jest czy ktos juz wygral rozgrywke. */

    
 
        if (!plansza[x + i*x_kier][y + i*y_kier] && ++puste <= IleBrakujeByWygrac)   
        {
            // wspolrzedne pustego miejsca na planszy obok zetona/żetonów gracza
            nowe_x = x + i*x_kier;
            nowe_y = y + i*y_kier;
        }
		else if (plansza[x + i*x_kier][y + i*y_kier] != ZetonGracza)
        {
            // Jezeli napotkamy w rozpatrywanym rzedzie żeton przeciwnika, 
			// to juz wiemy na pewno ze tutaj nie odniesiemy sukcesu
			// zwracamy false, musimy szukac gdzie indziej

            return false;
        }
 
	}
 
 
    // Wrzucamy zeton gracza na znalezione miejsce w celu zwiekszenia rzędu jego żetonow, tj. przyblizenia go do wygranej
    Wrzuc_zeton(nowe_x, nowe_y);
 
    return true;
}





/*! \brief Metoda informuje kto wygrał rozgrywkę jeśli jest ona rozstrzygnięta
 *
 */
void Connect4::Kto_wygral(int player){

	if(player==1)
		std::cout << "WYGRAŁEŚ BRAWO !!"<<std::endl;
	else 
		std::cout << " NIESTETY, KOMPUTER OKAZAL SIE LEPSZY -> PRZEGRALES !!"<<std::endl;
	
}
 




/*! \brief Metoda sprawdza, czy bieżąca rozgrywka ma jeszcze szansę być rozstrzygnięta
 *
 * Jest to sprawdzane po oddaniu ruchu przez każdego z użytkowników. Definiuje to stan zmiennej
 * logiczne mozna_wygrac. Jeśli nie będzie już wygranej żadnego z użytkowników, wówczas 
 * na wyjściu pojawia się informacja o tym.
 * 
 * \return Zwraca false, gdy rozgrywka nie będzia już rozstrzygnięta. Zwraca true, gdy rozgrywka trwać będzie nadal.
 */
bool Connect4::Czy_mozna_wygrac()
{
    if (!mozna_wygrac)
    {
        std::cout << "\n Ta gra nie bedzie miala rozstrzygniecia, koncze gre !\n\n";
        return false;
    }
    return true;
}


/*! \brief Metoda sprawdza czy plansza gry jest zapełniona.
 *
 */

bool Connect4::Czy_plansza_pelna(){
   
    Przelacz_gracza();
 
    if (ilosc_ruchow >= ilosc_pol){
        std::cout << "\n MAMY REMIS !!!\n\n";
        return true;    
    }
 
    return false;    
}
