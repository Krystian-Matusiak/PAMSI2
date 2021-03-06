#include "Graf.h"


class Lista_Sas{

  Lista< Krawedz > * lista_k;
  Lista< Wierzcholek > * lista_w;
  
 public:

  Wierzcholek * w_startowy;

  
  Lista_Sas();
  ~Lista_Sas();

  ////////////////////////////////////////////////////////////////////////////////////////
  /**********************
   * Funkcje pomocnicze *
   *********************/

  void inicjuj_w_startowy( Wierzcholek * start );
  Wierzcholek * w_start() {return w_startowy;};

  void przyporzadkuj_liste_w( Lista<Wierzcholek> * lista_wierz);
  void przyporzadkuj_liste_k( Lista<Krawedz> * lista_kraw);
  void oczysc_listy();
  
  int spr_poz_wierz_x(int wartosc); 

  Lista<Krawedz> * zwroc_liste_k() {return lista_k;};
  Lista<Wierzcholek> * zwroc_liste_w() {return lista_w;};
  /////////////////////////////////////////////////////////////////////////////////////////
  /*******************
   * Metody dostępu  *
   ******************/
  Wierzcholek ** tab_krancow_kraw( Krawedz * K);
  Wierzcholek * przeciwlegly( Wierzcholek * W , Krawedz * K);
  bool czy_sasiednie( Wierzcholek * W1 , Wierzcholek * W2 );
  void podmien_w( Wierzcholek * W , int info );
  void podmien_k( Krawedz * K , int info );

  ////////////////////////////////////////////////////////////////////////////////////////
  /*************************
   * Metody uaktualniające *
   ************************/
  void dodaj_wierzcholek( int info );
  void usun_wierzcholek( Wierzcholek * W );
  
  void dodaj_krawedz( Wierzcholek * wierz1 , Wierzcholek * wierz2 , int info );
  void usun_krawedz( Krawedz * K );

  ///////////////////////////////////////////////////////////////////////////////////////
  /*************************
   * Metody iterujące *
   ************************/

  // Wypisuje wszystkie krawędzie przylegające do wierzchołka W
  void kraw_przyl_do_w( Wierzcholek * W);
  void pokaz_krawedzie();
  void pokaz_wierzcholki();

};



void Lista_Sas::oczysc_listy(){
  lista_w=nullptr;
  lista_k=nullptr;
  }






////////////////////////////////////////////////////////////////////////////////////////
/**********************
 * Funkcje pomocnicze *
 *********************/

Lista_Sas::Lista_Sas(){
  lista_k = new Lista<Krawedz>;
  lista_w = new Lista<Wierzcholek>;
  w_startowy = new Wierzcholek;
}

Lista_Sas::~Lista_Sas(){
  //if( lista_k != nullptr )
    delete lista_k;
    //if( lista_w != nullptr )
    delete lista_w;
    //if( w_startowy != nullptr )
    delete w_startowy;
}

void Lista_Sas::inicjuj_w_startowy( Wierzcholek * start ){
  this->w_startowy = start;
}

void Lista_Sas::przyporzadkuj_liste_w( Lista<Wierzcholek> * lista_wierz){
  this->lista_w = lista_wierz;
}

void Lista_Sas::przyporzadkuj_liste_k( Lista<Krawedz> * lista_kraw){
  this->lista_k = lista_kraw;
}


/*
  Sprawdza pozycje wierzchołka o wartości x. Pomaga wykryć czy dany wierzchołek istnieje
*/
int Lista_Sas::spr_poz_wierz_x(int x){ 
  
  this->lista_w->iterator = this->lista_w->head;
  int numer=1;

  // Gdy lista jest pusta, funkcja zwraca zero
  if( this->lista_w->iterator == nullptr ) 
    return 0;

  while( this->lista_w->iterator->obiekt->nr != x ){
    
    // Gdy wierzchołeknie nie istnieje, funkcja zwraca zero
    if( this->lista_w->iterator->nast == nullptr ) 
      return 0;
    
    else{
      this->lista_w->iterator = this->lista_w->iterator->nast;
      numer++;
    }
  }
  return numer;
}









/////////////////////////////////////////////////////////////////////////////////////////
/*******************
 * Metody dostępu  *
 ******************/

Wierzcholek ** Lista_Sas::tab_krancow_kraw( Krawedz * K){
  Wierzcholek ** krance;
  krance = new Wierzcholek * [2];
  krance[0] = new Wierzcholek;
  krance[1] = new Wierzcholek;
    
  krance[0] = K->poczatek;
  krance[1] = K->koniec;

  return krance;
}


Wierzcholek * Lista_Sas::przeciwlegly( Wierzcholek * W , Krawedz * K){
  int dl_listy;
  
  dl_listy = W->wskazniki_na_kraw->dlugosc_listy();

  while( dl_listy ){
    if( W->wskazniki_na_kraw->zwracanie_obiektu(dl_listy) == K ){
      
      if( K->poczatek == W )
	return K->koniec;
      
      else if( K->koniec == W )
	return K->poczatek;
      
    }
    else
      dl_listy--;  
  }

}

bool Lista_Sas::czy_sasiednie( Wierzcholek * W1 , Wierzcholek * W2 ){
  
  int dlugosc;
  dlugosc = W1->wskazniki_na_kraw->dlugosc_listy();
  
  for( int i=1 ; i<= dlugosc ; i++){
    if( W1->wskazniki_na_kraw->zwracanie_obiektu(i)->poczatek == W1 ){
      if( W1->wskazniki_na_kraw->zwracanie_obiektu(i)->koniec == W2 )
	return 1;
    }
    else if( W1->wskazniki_na_kraw->zwracanie_obiektu(i)->koniec == W1 )
      if( W1->wskazniki_na_kraw->zwracanie_obiektu(i)->poczatek == W2 )
	return 1;
  }

  return 0;
}

void Lista_Sas::podmien_w( Wierzcholek * W , int info ){
  W->nr = info;
}

void Lista_Sas::podmien_k( Krawedz * K , int info ){
  K->waga = info;
}




////////////////////////////////////////////////////////////////////////////////////////
/*************************
 * Metody uaktualniające *
 ************************/

void Lista_Sas::dodaj_krawedz( Wierzcholek * wierz1 , Wierzcholek * wierz2 , int info ){ //////////////////////  Dodawanie krawędzi do listy

  Krawedz * kraw;
  kraw = new Krawedz;
  
  int indeks;
  int id_lk_w1; // Indeks listy krawedzi dla wierzchołka kolejno 1 i 2
  int id_lk_w2;
  
  indeks = lista_k->dodaj_wezel();
  id_lk_w1 = wierz1->wskazniki_na_kraw->dodaj_wezel();
  id_lk_w2 = wierz2->wskazniki_na_kraw->dodaj_wezel();
  
  wierz1->wskazniki_na_kraw->iterator = wierz1->wskazniki_na_kraw->head;
  wierz2->wskazniki_na_kraw->iterator = wierz2->wskazniki_na_kraw->head;
  lista_k->iterator = lista_k->head;

  ////////////////////////////////////////////////////////////////////////////////////
  /*************************************************
   * Znalezienie stworzonego miejsca na krawędź    *
   * na liscie wskazników na krawedzie dla danego  *
   * wierzchołka 1 i 2 oraz ich wspisanie na liste *
   *************************************************/
  for( int i=1 ; i<id_lk_w1 ; i++)  
    wierz1->wskazniki_na_kraw->iterator = wierz1->wskazniki_na_kraw->iterator->nast;
  for( int i=1 ; i<id_lk_w2 ; i++)
    wierz2->wskazniki_na_kraw->iterator = wierz2->wskazniki_na_kraw->iterator->nast;

  wierz1->wskazniki_na_kraw->iterator->obiekt = kraw;
  wierz2->wskazniki_na_kraw->iterator->obiekt = kraw;

  /////////////////////////////////////////////////////////////////////////////////////
  for( int i=1 ; i<indeks ; i++)
    lista_k->iterator = lista_k->iterator->nast;
  //cout<<endl<<indeks<<endl;

  this->lista_k->iterator->obiekt = kraw;
  lista_k->zwracanie_obiektu(indeks)->waga = info;
  
  lista_k->zwracanie_obiektu(indeks)->poczatek = wierz1;
  lista_k->zwracanie_obiektu(indeks)->koniec = wierz2;
  
  lista_k->zwracanie_obiektu(indeks)->wsk_wierz1 = wierz1->wskazniki_na_kraw->zwracanie_wezla(id_lk_w1);
  lista_k->zwracanie_obiektu(indeks)->wsk_wierz2 = wierz2->wskazniki_na_kraw->zwracanie_wezla(id_lk_w2);
  
  lista_k->zwracanie_obiektu(indeks)->wsk_pozycja = lista_k->zwracanie_wezla(indeks);
}

void Lista_Sas::usun_krawedz( Krawedz * K){
  int dlugosc = lista_k->dlugosc_listy();
  
  K->poczatek = nullptr;
  K->koniec = nullptr;
  K->wsk_wierz1 = nullptr;
  K->wsk_wierz2 = nullptr;
  K->wsk_pozycja = nullptr;

  lista_k->iterator = lista_k->head;
  
  for( int i=1 ; i<=dlugosc ; i++)
    if( lista_k->zwracanie_obiektu(i) == K ){
      lista_k->usun_wezel(i);
      i=dlugosc;
    }
}


void Lista_Sas::dodaj_wierzcholek( int info ){///////Dodawanie wierzchołka do listy

  Wierzcholek * wierzch;
  wierzch = new Wierzcholek;

  int indeks;
  indeks = lista_w->dodaj_wezel();

  this->lista_w->iterator = this->lista_w->head;
  for( int i=1 ; i<indeks ; i++)
    this->lista_w->iterator = this->lista_w->iterator->nast;
   
  lista_w->iterator->obiekt = wierzch;
  lista_w->zwracanie_obiektu(indeks)->nr = info;
  lista_w->zwracanie_obiektu(indeks)->wsk_pozycja = lista_w->zwracanie_wezla(indeks);
  //
}


void Lista_Sas::usun_wierzcholek( Wierzcholek * W ){//////  Usuwanie wierzchołka z listy

  int dlugosc;
  int ilosc_krawedzi;
  int ilosc_usun_kraw=0; // ilosc usunietych krawędzi
  
  dlugosc = W->wskazniki_na_kraw->dlugosc_listy(); //zwraca ilosc krawedzi dochodzących do wierzcholka
  ilosc_krawedzi = lista_k->dlugosc_listy();   // zwraca ilość wszystkich krawedzi

  
  while(dlugosc){ // W tej pętli usuwane są wszystkie krawędzie dochodzące do danego wierzchołka

    for( int i=0 ; i<(ilosc_krawedzi-ilosc_usun_kraw) ; i++){  // Ta pętla odpowiada za wyszukanie odpowiedniej krawedzi z listy krawędzi, aby tę krawędź usunąć

      /****************************************************************************************
       *Warunek sprawdzający czy dana krawedz z listy jest tą krawędzią, która ma być usunięta*
       ****************************************************************************************/
      if( W->wskazniki_na_kraw->zwracanie_obiektu(dlugosc)->wsk_pozycja == lista_k->zwracanie_wezla(i) ){
	this->usun_krawedz( lista_k->zwracanie_obiektu(i) );
	ilosc_usun_kraw++;
      }
      
    }
    dlugosc--;
  }
  int indeks;
  for( int i=1 ; i<=lista_w->dlugosc_listy() ; i++)
    if( lista_w->zwracanie_obiektu(i) == W ){
      indeks = i;
      i=lista_w->dlugosc_listy();
    }

  W->wskazniki_na_kraw = nullptr;
  W->wsk_pozycja = nullptr;
  lista_w->usun_wezel(indeks);
}

///////////////////////////////////////////////////////////////////////////////////////
/*************************
 * Metody iterujące *
 ************************/

void Lista_Sas::kraw_przyl_do_w( Wierzcholek * W){
  int dlugosc;
  dlugosc = W->wskazniki_na_kraw->dlugosc_listy();
  
  for( int i=1 ; i<=dlugosc ; i++){
    cout << W->wskazniki_na_kraw->zwracanie_obiektu(i)->waga << "   ";
  }
  cout << endl;
}


void Lista_Sas::pokaz_krawedzie(){/////////////// Pokazuje wszystkie krawędzie

  lista_k->iterator = lista_k->head;
 
  cout<<"\nKrawedzie:\n";
  while( lista_k->iterator->nast != NULL){
    cout << "(" << lista_k->iterator->obiekt->poczatek->nr <<" , ";
    cout << lista_k->iterator->obiekt->koniec->nr <<") ";
    cout << lista_k->iterator->obiekt->waga << endl;
    lista_k->iterator = lista_k->iterator->nast;
  }
  cout << "(" << lista_k->iterator->obiekt->poczatek->nr <<" , ";
  cout << lista_k->iterator->obiekt->koniec->nr <<") ";
  cout << lista_k->iterator->obiekt->waga << endl;

  lista_k->iterator = lista_k->head;
}


void Lista_Sas::pokaz_wierzcholki(){  //////////////// Pokazuje wszystkie wierzcholki
  lista_w->iterator = lista_w->head;

  cout<<"\nWierzcholki:\n";
  while( lista_w->iterator->nast != NULL){
    cout << lista_w->iterator->obiekt->nr <<", ";
    lista_w->iterator = lista_w->iterator->nast;
  }
  cout << lista_w->iterator->obiekt->nr<<"\n";
  
  lista_w->iterator = lista_w->head;
}

