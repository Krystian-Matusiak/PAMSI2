#include <iostream>

template <typename Type>
class Wezel{

 public:
  Wezel();
  //~Wezel();
  
  Wezel * poprz;
  Wezel * nast;
  Type * obiekt;

};

template<typename Type>
Wezel<Type>::Wezel(){
  /*
  this->poprz = new Wezel;  
  this->nast = new Wezel;
  this->obiekt = new Type;
  */
  
  this->poprz = nullptr;
  this->nast = nullptr;
  this->obiekt = nullptr;
}

/*
template<typename Type>
Wezel<Type>::~Wezel(){
  if( this->poprz !=nullptr )
    delete this->poprz;
  if( this->nast !=nullptr )
    delete this->nast;
  if( this->obiekt !=nullptr )
    delete this->obiekt;
}
*/
