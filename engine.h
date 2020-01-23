#ifndef ENGINE_H
#define ENGINE_H

#include "parser.h"
#include "iostream.h"

class Compiler : public Parser
 {
  public:
	  Compiler() { /*prompt += "_LCS" ;  PutPrompt() ;*/};
   int yylex() ;
   void yyerror(char*) ;
 } ;

#endif








