#ifndef DLIST_H
#define DLIST_H

#include "globals.h"

template <class Type> class Dlist ;
template <class Type> class DFIter ;
template <class Type> class DRIter ;

//-------------------------------------------------------------------------

template <class Type> 
class Dnode
 {
 public :
   friend class Dlist<Type> ;
   friend class DFIter<Type> ;
   friend class DRIter<Type> ;
   friend ostream& operator << (ostream&, const Dlist<Type> &) ;
   friend istream& operator >> (istream&, Dlist<Type> &) ;
  private :
   Dnode(Type &t) { itemPtr = &t ; 
                          nextPtr = prevPtr = (Dnode<Type> *) 0 ; }
   ~Dnode() { 
		if(itemPtr ) 
			delete itemPtr;
	    nextPtr = prevPtr = (Dnode<Type> *) 0 ; 
   }
   Type *itemPtr ;
   Dnode<Type> *nextPtr ;
   Dnode<Type> *prevPtr ;
 } ;

//-------------------------------------------------------------------------

template <class Type> 
class Dlist
 {
  public :
   Dlist() { headPtr = tailPtr = curPtr = (Dnode<Type> *) 0 ; len = 0 ; }
   Dlist(const Dlist<Type>&) ;
   ~Dlist() { Reset() ; } 

   Dlist<Type>& operator = (const Dlist<Type> &) ;
   friend Dlist<Type> operator + (const Dlist<Type>&, const Dlist<Type>&) ;
   Dlist<Type>& operator += (const Dlist<Type>&) ;

   bool operator == (const Dlist<Type>&) const ;
   bool operator != (const Dlist<Type>& l) const {
                              return (*this == l) ? false : true ; }

   bool operator ! () const { return (len > 0) ? false : true ; }
   const Type* GotoHead() { curPtr = headPtr ;
                              return curPtr ? curPtr->itemPtr : (Type *) 0 ; }
   const Type* GotoTail() { curPtr = tailPtr ;
                              return curPtr ? curPtr->itemPtr : (Type *) 0 ; }
   const Type* Next() ;
   const Type* Prev() ;

   int AppendHere(Type&) ;
   int PrependHere(const Type&) ;

   const Type* Delete() ;
   const Type* Delete(const Type&) ;
   const Type* Search(const Type&) const ;

   void Reset() ;
   void DeepDestroy() ;

   int Size() const { return len ; }
   const Type* Cur() { return curPtr ?  curPtr->itemPtr : (Type *) 0 ; }

  private :
   Dnode<Type>* headPtr ;
   Dnode<Type>* tailPtr ;
   Dnode<Type>* curPtr ;
   int len ;

   friend ostream& operator << (ostream&, const Dlist<Type>&) ;
   friend class DFIter<Type> ;
   friend class DRIter<Type> ;
 } ;

//-------------------------------------------------------------------------

template <class Type>
class DFIter
 {
  public :
   DFIter() : iterPtr(0), cListPtr(0) {}
   DFIter(const Dlist<Type> &l) : iterPtr(l.headPtr), cListPtr(&l) {}

   Type *operator() () 
   {
     Type* retPtr = 0 ;
     if (iterPtr)
     {
       retPtr = iterPtr->itemPtr ;
       iterPtr = iterPtr->nextPtr ;
     }
     return retPtr ;
   }

   void Reset() { iterPtr = cListPtr->headPtr ; }
   void ReSeat(const Dlist<Type>& l) { iterPtr = l.headPtr ; cListPtr = &l ; }
  private : 
   const Dnode<Type>* iterPtr ;
   const Dlist<Type>* cListPtr ;
 } ;

//-------------------------------------------------------------------------

template <class Type>
class DRIter
{
  public :
   DRIter() : iterPtr(0), cListPtr(0) {}
   DRIter(const Dlist<Type> &l) : iterPtr(l.tailPtr), cListPtr(&l) {}

   Type *operator() () 
   {
     Type* retPtr = 0 ;
     if (iterPtr)
     {
       retPtr = iterPtr->itemPtr ;
       iterPtr = iterPtr->prevPtr ;
       return retPtr ;
     }
     return retPtr ;
   }

   void Reset() { iterPtr = cListPtr->tailPtr ; }
   void ReSeat(const Dlist<Type>& l) { iterPtr = l.tailPtr ; cListPtr = &l ; }
  private : 
   const Dnode<Type>* iterPtr ;
   const Dlist<Type>* cListPtr ;
 } ;

//-------------------------------------------------------------------------

template <class Type>
Dlist<Type>::Dlist(const Dlist<Type>& s)
 {
  Type *itmPtr ;
  Dnode<Type>* xPtr = s.headPtr ;

   headPtr = tailPtr = curPtr = 0 ;
   len = 0 ;

   while(xPtr) 
    {
     itmPtr = new Type (*(xPtr->itemPtr)) ;
     AppendHere (*itmPtr) ;
     xPtr = xPtr->nextPtr ;
    }
   curPtr = headPtr ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
Dlist<Type>& Dlist<Type>::operator = (const Dlist<Type> &l)
 {
  if (this == &l)
   return *this ;

  Type *itmPtr ;
  Dnode<Type> *xPtr = headPtr, *yPtr = l.headPtr ; // DO NOT REMOVE !!!

   curPtr = headPtr ;
   while (xPtr && yPtr)
    {
     xPtr->itemPtr = new Type (*yPtr->itemPtr) ;
     xPtr = xPtr->nextPtr ;
     yPtr = yPtr->nextPtr ;
    }

   /* If this is longer than l, delete extra nodes and set end of list to 0 */
   if (xPtr && !yPtr)
    {
     tailPtr = xPtr->prevPtr ;
     tailPtr->nextPtr = (Dnode<Type>*) 0 ;
     for( ; xPtr->nextPtr ; )
      {
       xPtr = xPtr->nextPtr ;
       delete xPtr->prevPtr ;
      }
     delete xPtr ;
    }
   
   if (!xPtr && yPtr)
    {
     for (curPtr = tailPtr ; yPtr ; yPtr = yPtr->nextPtr)
      {
       itmPtr = new Type (*yPtr->itemPtr) ;
       AppendHere(*itmPtr) ;
      }
    }

   len = l.len ; 
   curPtr = headPtr ;
  return *this ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
Dlist<Type> operator + (const Dlist<Type>& first, const Dlist<Type>& second)
 {
  Dlist<Type> both(first) ;

  return (both += second) ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
Dlist<Type>& Dlist<Type>::operator += (const Dlist<Type> &list)
 {
  Type *addItmPtr ;
  Dnode<Type> *xPtr = list.headPtr, *tPtr = list.tailPtr ;

   curPtr = tailPtr ;
   while(xPtr && (xPtr != tPtr))
    {
     addItmPtr = new Type (*xPtr->itemPtr) ;
     AppendHere (*addItmPtr) ;
     xPtr = xPtr->nextPtr ;
    }
   if (xPtr)
    {
     addItmPtr = new Type (*xPtr->itemPtr) ;
     AppendHere (*addItmPtr) ;
    }
   curPtr = headPtr ;
  return *this ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
bool Dlist<Type>::operator == (const Dlist<Type>& list) const
 {
  if (len != list.len)
   return false ;

  Dnode<Type> *xPtr = headPtr, *yPtr = list.headPtr ;

   while(xPtr && yPtr)
    if (*(xPtr->itemPtr) != *(yPtr->itemPtr))
     return false ;
    else
     {
      xPtr = xPtr->nextPtr ;
      yPtr = yPtr->nextPtr ;
     }
  return true ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
ostream& operator << (ostream& os, const Dlist<Type>& list)
 {
  Dnode<Type>* nPtr = list.headPtr ;
  register int i = 0 ; //takes care of case when length of list == 0 ;

  while (i < list.len - 1)
   {
    os << *(nPtr->itemPtr) << ", " ;
    i++ ;
    nPtr = nPtr->nextPtr ;
   }

  if (nPtr)
   os << *(nPtr->itemPtr) ;
  return os ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
istream& operator >> (istream& is, Dlist<Type> &list)
 {
  Type item, *iPtr ;
register int count = 0 ;
   while (is >> item)
    {
     iPtr = new Type (item) ;
     list.AppendHere(*iPtr) ;
cout << *iPtr << endl ;
if (++count == 9) break ;
    }
  return is ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
const Type* Dlist<Type>::Next()
 {
  if (!curPtr || !(curPtr->nextPtr))
   return 0 ;
  curPtr = curPtr->nextPtr ;
  return curPtr->itemPtr ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
const Type* Dlist<Type>::Prev()
 {
  if (!curPtr || !(curPtr->nextPtr))
   return 0 ;

  curPtr = curPtr->prevPtr ;
  return curPtr->itemPtr ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
int Dlist<Type>::AppendHere(Type &val)
 {
  Dnode<Type> *newPtr = new Dnode<Type> (val) ;

   if (!len) // are we looking at an empty list ?
    curPtr = headPtr = tailPtr = newPtr ;
   else
   if (curPtr == tailPtr) // are we inserting at the end of the list ?
    {
     tailPtr->nextPtr = newPtr ;
     tailPtr = newPtr ;
     tailPtr->prevPtr = curPtr ;
     curPtr = tailPtr ;
    }
   else // we're inserting in between the list or after the head
    {
     newPtr->prevPtr = curPtr ;
     newPtr->nextPtr = curPtr->nextPtr ;
     curPtr->nextPtr = newPtr ;
     curPtr = newPtr ;
     curPtr->nextPtr->prevPtr = curPtr ;
    }
  return ++len ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
int Dlist<Type>::PrependHere(const Type &val)
 {
  Dnode<Type> *newPtr = new Dnode<Type> (val) ;

   if (!len) // are we looking at an empty list ?
    curPtr = headPtr = tailPtr = newPtr ;
   else
   if (curPtr == headPtr) // are we inserting at the head of the list ?
    {
     headPtr->prevPtr = newPtr ;
     headPtr = newPtr ;
     headPtr->nextPtr = curPtr ;
     curPtr = headPtr ;
    }
   else // we're inserting in between the list surely
    {
     newPtr->prevPtr = curPtr->prevPtr ;
     newPtr->nextPtr = curPtr ;
     curPtr->prevPtr->nextPtr = newPtr ;
     curPtr->prevPtr = newPtr ;
     curPtr = newPtr ;
    }
  return ++len ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
const Type* Dlist<Type>::Delete()
 {
  if (!len)
   return (Type *) 0 ;

  const Type* retPtr = curPtr->itemPtr ;

   if (len == 1)
    {
     Reset() ;
     return retPtr ;
    }

   if (curPtr == headPtr) // are we deleting the head of the list ?
    {
     headPtr = headPtr->nextPtr ;
     delete curPtr ;
     curPtr = headPtr ;
     curPtr->prevPtr = (Dnode<Type> *) 0 ;
    }
   else
   if (curPtr == tailPtr) // are we deleting the tail of the list ?
    {
     tailPtr = tailPtr->prevPtr ;
     delete curPtr ;
     curPtr = tailPtr ;
     curPtr->nextPtr = (Dnode<Type> *) 0 ;
    }
   else // we're surely deleting from in-between the list
    {
     Dnode<Type>* xPtr = curPtr ;
     curPtr->prevPtr->nextPtr = curPtr->nextPtr ;
     curPtr->nextPtr->prevPtr = curPtr->prevPtr ;
     curPtr = curPtr->nextPtr ;
     delete xPtr ;
    }
   len-- ;
  return retPtr ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
const Type* Dlist<Type>::Search(const Type& t) const
 {
  Dnode<Type>* nPtr = headPtr ;

   while(nPtr)
    if (*(nPtr->itemPtr) == t)
     return nPtr->itemPtr ;
    else
     nPtr = nPtr->nextPtr ;
  return (Type *) 0 ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
const Type* Dlist<Type>::Delete(const Type& t)
 {
  Dnode<Type>* nPtr = headPtr ;

   while(nPtr)
    if (*(nPtr->itemPtr) == t)
     {
      curPtr = nPtr ;
      return Delete() ;
     }
    else
     nPtr = nPtr->nextPtr ;
  return (Type *) 0 ;
 }

/*==============================================================================
==============================================================================*/

template <class Type>
void Dlist<Type>::Reset()
{
	curPtr = headPtr ;
	while(curPtr)
	{
		//if (curPtr->prevPtr)
		//	delete curPtr->prevPtr->itemPtr;
		delete curPtr->prevPtr ;
		curPtr = curPtr->nextPtr ;
	}
	delete tailPtr;
	headPtr = tailPtr = curPtr = (Dnode<Type> *) 0 ;
	len = 0 ;
}

/*==============================================================================
==============================================================================*/

template <class Type>
void Dlist<Type>::DeepDestroy()
 {
  curPtr = headPtr ;
  while(curPtr)
   {
    //if (curPtr->prevPtr)
    // delete (Type *) curPtr->prevPtr->itemPtr ;
    delete curPtr->prevPtr ;
    curPtr = curPtr->nextPtr ;
   }
  delete tailPtr;
  headPtr = tailPtr = curPtr = (Dnode<Type> *) 0 ;
  len = 0 ;
 }

/*==============================================================================
==============================================================================*/

#endif
