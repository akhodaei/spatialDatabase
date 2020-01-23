/***************************************************
 * Name:     arg.h
 * Author:   
 * Time:     April 6, 1997
 * Descript: define of class Arg
 *
 ***************************************************/

#ifndef ARG_H
#define ARG_H

//---------------------------------------------------------------------------
#include <iostream.h>
#include "string.h"
#include "slist.h"
#include "vector.h"

//--------------------------------------------------------------------------

class Arg
{
 public :
   // Arg Constructors
   Arg() : cFlag(1), floatVal(defFloatVal) 
      { strPtr = (String *) 0 ; }
    Arg(float i) 
      { floatVal = i ; strPtr = (String *) 0 ; 
        cFlag = 1 ; 
      }
  
     Arg(const String& s) 
      { floatVal = defFloatVal ; strPtr = new String(s) ; cFlag=0;}
     Arg(const char* s) 
      { floatVal = defFloatVal; 
        cFlag=0; 
        strPtr = new String(s) ; 
      }

   Arg(const Arg& a) : cFlag(a.cFlag), floatVal(a.floatVal)
      { strPtr = (!a.strPtr) ? 0 : new String(*(a.strPtr)) ; }

   // Arg Destructor
   ~Arg() { if (strPtr) delete strPtr ;  }
   
   // Arg Operators 
   Arg& operator = (const Arg& a) 
   { if (this != &a) 
     { cFlag =  a.cFlag ; floatVal =  a.floatVal ; 
       strPtr = (!a.strPtr) ? 0 : new String(*(a.strPtr)) ;  
     }
     return *this ; }

   bool operator == (const Arg& a) const 
      { 
        return ((cFlag != a.cFlag) ? false :
           ((cFlag==1) ? ((floatVal == a.floatVal) ? true : false) :
           ((*strPtr!=*(a.strPtr)) ? false : true) ));}
   bool operator != (const Arg& a) const 
      { return (*this == a) ? false : true ; }

   int Flag() const {return cFlag;}

   operator float() const { return floatVal ; }
   operator String() const { return strPtr ? *strPtr : String("null") ; }

 
 private :
   float floatVal ;
   String* strPtr ;
   int cFlag;  //cFlag=0, for string, cFlag=1, for constant  
   static const float defFloatVal;

   friend class DB;
   //friend class PredType;
   //friend class Predicate;
   //friend class SlistINT;
   /*
   friend ostream& operator << (ostream& os, const Arg& a) 
   { 
          switch(a.Flag())
     { 
       case 0 : if (a.strPtr) os << *(a.strPtr); break; 
       case 1 : os << a.intVal; break;
       case 2 : os << *(a.setPtr); break;
       case 3 : os << " Z "; break;
       case 4 : if (a.setPtr) os << *(a.setPtr) ; break;
       case 5 : if (a.strPtr) os << *(a.strPtr);
                if (a.setPtr) os << *(a.setPtr);
                break; 
       default : if (a.strPtr) os << *(a.strPtr); break;
     } 
     os <<"("<<a.Flag()<<", "<<a.IsZ()<<")"; 
     
     return os ;
     }
     */ 
   
} ;

#endif









