#include "Wezel.h"

using namespace std;

template<typename Type>
class Lista{

 public:
  Wezel<Type> * head;
  Wezel<Type> * tail;
  Wezel<Type> * iterator;

  Lista();
  //~Lista();
  
  int dodaj_wezel();     // zwraca indeks stworzonego węzła
  void usun_wezel(int indeks);
  int dlugosc_listy();
  
  Type        * zwracanie_obiektu(int indeks);
  Wezel<Type> * zwracanie_wezla(int indeks);
};

template <typename Type>
int Lista<Type>::dlugosc_listy(){  ////////////////// Zwraca dlugość listy za pomocą liczby elementów
  int dlugosc = 0;

  this->iterator = this->head;
  while(this->iterator){
    this->iterator = this->iterator->nast;
    dlugosc++;
  }
  return dlugosc;
}

template <typename Type>
int Lista<Type>::dodaj_wezel(){  /////////////////////////// Dodawanie węzła
  Wezel<Type> * nowyElem;
  nowyElem = new Wezel<Type>;
  
  if( this->head == nullptr && this->tail == nullptr){ // Gdy lista jest pusta
    this->iterator = nowyElem;
    this->head = nowyElem;
    this->tail = nowyElem;
    nowyElem->poprz = nullptr;
    nowyElem->nast = nullptr;
  }
  else
    nowyElem->poprz = this->tail; // Gdy już jest chociaż 1 element
  
  nowyElem->obiekt = nullptr;
  nowyElem->nast = nullptr ;
  if( nowyElem->poprz != nullptr ){ //Jesli stworzony element nie jest pierwszy
    this->tail->nast = nowyElem;
    this->tail = nowyElem;
  }
  this->iterator = this->head;
  int indeks=1;/////////////////////////////////////////////////////////
    while( this->iterator != this->tail ){
      this->iterator = this->iterator->nast;
      indeks++;
    }
    
  return indeks;
}

template <typename Type>
void Lista<Type>::usun_wezel( int indeks){//////  Usuwanie elementu z listy
  Wezel<Type> * tmp = new Wezel<Type>;

  this->iterator = this->head;
  for( int i=1 ; i<indeks ; i++)
    this->iterator = this->iterator->nast;

  tmp = this->iterator;

  if( tmp->nast != nullptr && tmp->poprz != nullptr ){//Gdy usuwam srodkowy element
    this->iterator->obiekt = nullptr;
    this->iterator = tmp->nast;
    tmp->poprz->nast =this->iterator;
    this->iterator->poprz = tmp->poprz;
  }
  else if( tmp->nast != nullptr && tmp->poprz == nullptr ){//Gdy usuwam pierwszy element
    this->iterator->obiekt = nullptr;
    this->iterator = tmp->nast;
    this->head = tmp->nast;
    this->iterator->poprz = nullptr;
  }
  else if( tmp->nast == nullptr && tmp->poprz != nullptr ){//Gdy usuwam ostatni element
    this->iterator->obiekt = nullptr;
    this->iterator = tmp->poprz;
    this->tail = tmp->poprz;
    this->iterator->nast = nullptr;
  }
  else if( this->head != nullptr){ //Gdy usuwam jedyny element
    this->iterator->obiekt = nullptr;
    this->iterator = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
  }
  else
    cout<<"Ta lista już jest pusta"<<endl;
  delete  tmp;
  this->iterator = this->head;
}


template <typename Type>
Type * Lista<Type>::zwracanie_obiektu(int indeks){
  
  this->iterator = this->head;
  
  for( int i=1 ; i<indeks ; i++)
    this->iterator = this->iterator->nast;
 
  return this->iterator->obiekt;
}

template <typename Type> 
Wezel<Type> * Lista<Type>::zwracanie_wezla(int indeks){
  
  this->iterator = this->head;
  
  for( int i=1 ; i<indeks ; i++)
    this->iterator = this->iterator->nast;
 
  return this->iterator;
}

template<typename Type>  //////////////////////////  Konstruktor
Lista<Type>::Lista(){
  head = nullptr ;
  tail = nullptr ;
  iterator = nullptr;
}

/*
template<typename Type>  //////////////////////////  Destruktor
Lista<Type>::~Lista(){
  if ( head != nullptr )
    delete head;
  if(tail != nullptr )
    delete tail;
  if(iterator != nullptr)
    delete iterator;
}
*/
