#include "stdafx.h"
#include "globals.h"

//extern char* progName ;

/*==============================================================================
==============================================================================*/

void FreeStoreException()
 {
	 ASSERT(FALSE);
  cout << "progName" << ": FATAL, Free store exhausted!!!!\n" ;
  exit (2) ;
 }

/*==============================================================================
==============================================================================*/