#ifdef CONST
#undef CONST
#endif
#include "stdafx.h"
#include "scanner.h"
#include "engine.h"
#include "db.h"

//Compiler compiler;
//Scanner scanner;
//DB* dataBase;

//int nCurRelation=0;	// extern in CIdbView.cpp

int main(int argc, char ** argv)
{

   system("clear"); 
   while(compiler.yyparse());
   
   return 0;
}


/* =============================================================================
==============================================================================*/












