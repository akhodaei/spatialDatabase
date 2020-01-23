#ifndef GLOBALS_H
#define GLOBALS_H

#include<iostream.h>
#include<stdlib.h>
//#include<sys/time.h>

//enum bool {false = 0, true} ;
void FreeStoreException() ;

template <class Type> void Swap(Type&, Type&) ;

template <class Type> 
inline void Swap(Type &x, Type &y)
{
  Type temp = x ;
  x = y ;
  y = temp ;
}

#endif
