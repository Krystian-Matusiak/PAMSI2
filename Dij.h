#include "kolejka.h"
#include <chrono>


auto  Dij_macierz( Macierz_Sas * G , Wierzcholek * s , int * dystans , int * droga){
  auto M1 = chrono::high_resolution_clock::now() ;

  int dlugosc = G->zwroc_liste_w()->dlugosc_listy();
  Kolejka <Wierzcholek> * Q;
  Wierzcholek * U;
  int *d;
  int *sciezka;

  Q = new Kolejka <Wierzcholek>;
  U = new Wierzcholek;
  d = new int[ dlugosc ];
  sciezka = new int [dlugosc];


  for( int i=0 ; i<dlugosc ; i++){
    if( G->zwroc_liste_w()->zwracanie_obiektu(i+1) == s ){
      d[i] = 0 ;
      sciezka[ s->nr ] = -1;
    }
    else
      d[i] = 1000000;
  }
  
  for( int i=1 ; i<=dlugosc ; i++ )
    Q->dodaj( G->zwroc_liste_w()->zwracanie_obiektu(i) , d[i-1] );
    
  while( !Q->czy_pusta() ){ // Dopóki kolejka nie jest pusta
        
    U = Q->zwroc_usun_min(); // Zwracanie wierzchołka o najniższym priorytecie

    for( int j=0 ; j<dlugosc ; j++){
      if( G->macierz[ U->klucz ][j] != nullptr ){  // Jeżeli istnieje krąwędź między j-tym wierzchołkiem a wierzchołkiem wyciągniętym z kolejki


	int pozycjaU = G->spr_poz_wierz_x(U->nr)-1;
	int waga = G->macierz[U->klucz][j]->waga;
	int pozycja_przeciwleglego_U = G->spr_poz_wierz_x( G->przeciwlegly(U,G->macierz[U->klucz][j])->nr)-1;
	
	// d[ U ]  +  (waga krawędzi K pomiedzy U oraz jego sąsiadem)  <   d[ (przeciwległy wierzchołek U względem krawędzi K) ]
	if( d[ pozycjaU ] + waga  < d[ pozycja_przeciwleglego_U ] ){
	  d[ pozycja_przeciwleglego_U ] = d[ pozycjaU ] + waga;  // główny fragment relaksacji

	  sciezka[ G->przeciwlegly(U,G->macierz[U->klucz][j])->nr ] = U->nr;    // zapisywanie scieżki
	  
	  Q->zmien_klucz(  // podmiana klucza w kolejce
			 G->przeciwlegly( U , G->macierz[U->klucz][j] ) ,
			 d[ pozycjaU ] + waga
			 );
	}
      }
    }

  }
  auto M2 = chrono::high_resolution_clock::now() ;


  for( int g=0 ; g<dlugosc ; g++){  // przypisanie tablic do tablic z poza funkcji
    dystans[g] = d[g];
    droga[g] = sciezka[g];
  }

   // Odkomentować aby sprawdzić poprawność algorytmu
  cout<<"\n\nTablica dystansow:\n";
  for( int i=0 ;i<dlugosc ; i++)
    cout << "Wierzcholek " << G->zwroc_liste_w()->zwracanie_obiektu(i+1)->nr << ": " << d[i]<<endl;
 
  
  cout << "\nPokaz sciezke wierzcholka x:\n";
  int numer = 3;
      
  while( sciezka[numer] != -1 ){
    cout << "numer " << numer << endl;
    numer = sciezka[ numer ];
    if( sciezka[numer] == -1 )
      cout << "numer " << s->nr << endl; // wyswietlenie ostatniego
  }
  
  
  U=nullptr;
  delete [] sciezka;
  delete [] d;
  delete U;
  delete Q;

  return chrono::duration_cast<std::chrono::microseconds>( M2-M1 ).count();
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////






auto Dij_lista( Lista_Sas * G , Wierzcholek * s , int * dystans , int * droga){
  auto L1 = chrono::high_resolution_clock::now() ;

  int dlugosc = G->zwroc_liste_w()->dlugosc_listy();
  int ilosc_kraw;
  
  Kolejka <Wierzcholek> * Q;
  Wierzcholek * U;
  int *d;
  int *sciezka;

  Q = new Kolejka <Wierzcholek>;
  U = new Wierzcholek;
  d = new int[ dlugosc ];
  sciezka = new int [dlugosc];

  //dystans = d;
  //droga = sciezka;
  
  for( int i=0 ; i<dlugosc ; i++){
    if( G->zwroc_liste_w()->zwracanie_obiektu(i+1) == s ){
      d[i] = 0 ;
      sciezka[ s->nr ] = -1;
    }
    else
      d[i] = 1000000;
  }
  
  for( int i=1 ; i<=dlugosc ; i++ )
    Q->dodaj( G->zwroc_liste_w()->zwracanie_obiektu(i) , d[i-1] );

  while( !Q->czy_pusta() ){ // Dopóki kolejka nie jest pusta
    
    U = Q->zwroc_usun_min(); // Zwracanie wierzchołka o najniższym priorytecie
    
    ilosc_kraw = U->wskazniki_na_kraw->dlugosc_listy();
    
    for(int i=1 ; i<=ilosc_kraw ; i++){

      
      int pozycjaU = G->spr_poz_wierz_x( U->nr )-1;
      int waga_miedzy_sasiadami = U->wskazniki_na_kraw->zwracanie_obiektu(i)->waga;
      int pozycja_przeciwleglego_U = G->spr_poz_wierz_x(
							G->przeciwlegly( U ,
									 U->wskazniki_na_kraw->zwracanie_obiektu(i))->nr
							)-1 ;
      
      // d[U]  +  (waga krawędzi K pomiedzy U oraz jego sąsiadem)  <   d[ (przeciwległy wierzchołek U względem krawędzi K) ]
      if( d[pozycjaU] +  waga_miedzy_sasiadami  < d[pozycja_przeciwleglego_U] ){
	d[pozycja_przeciwleglego_U] =  d[pozycjaU] +  waga_miedzy_sasiadami ;

	sciezka[ G->przeciwlegly( U,U->wskazniki_na_kraw->zwracanie_obiektu(i))->nr ] = U->nr;
	
	Q->zmien_klucz(
		       G->przeciwlegly( U , U->wskazniki_na_kraw->zwracanie_obiektu(i) ) ,
		       d[pozycjaU] +  waga_miedzy_sasiadami
		       );
      }	
    }
  }
  auto L2 = chrono::high_resolution_clock::now() ;


  for( int g=0 ; g<dlugosc ; g++){
    dystans[g] = d[g];
    droga[g] = sciezka[g];
  }

    // Odkomentować aby sprawdzić poprawność algorytmu i sprawdza odleglosc wierzcholka o nr 5 od startowego
  cout<<"\n\nTablica dystansow:\n";
  for( int i=0 ;i<dlugosc ; i++)
    cout << "Wierzcholek " << G->zwroc_liste_w()->zwracanie_obiektu(i+1)->nr << ": " << d[i]<<endl;
 

  cout << "\nPokaz sciezke wierzcholka x:\n";
  int numer = 5;
      
  while( sciezka[numer] != -1 ){
    cout << "numer " << numer << endl;
    numer = sciezka[ numer ];
    if( sciezka[numer] == -1 )
      cout << "numer " << s->nr << endl; // wyswietlenie ostatniego
  }
  
  
  U=nullptr;
  delete [] sciezka;
  delete [] d;
  delete U;
  delete Q;

  return chrono::duration_cast<std::chrono::microseconds>( L2-L1 ).count();
}
