#include "stdafx.h"
#include "engine.h"
#include "scanner.h"

extern Scanner scanner ;

/*==============================================================================
==============================================================================*/

int Compiler::yylex()
 {
   yylloc.first_line = scanner.line ;
   yylloc.first_column = scanner.column ;
   
   int token = scanner.yylex(&yylval) ;
   yylloc.last_line = scanner.line ;
   yylloc.last_column = scanner.column ;
   yylloc.text = (char *) scanner.yytext ;
  return token ;
 }

/*==============================================================================
==============================================================================*/

void Compiler::yyerror(char *m)
 { 
	CString strOut;
	static char errBuf[257] ;

   m[0] = toupper(m[0]) ;
   if (scanner.yyin_points_to(&cin))
		sprintf(errBuf, "MLPQ: %s, token '%s' unexpected", 
                                               m, (char *) yylloc.text) ;
   else
		sprintf(errBuf, "MLPQ: %s on line %d, token '%s' unexpected\n", 
                      m, (int) yylloc.first_line, (char *) yylloc.text) ;
     
	strOut = errBuf;
   if (scanner.line > 1)
   {
     strOut += scanner.lineBuf;
	 strOut += "\n";
     sprintf(errBuf, "%*s", yylloc.first_column, "^") ;
	 strOut += errBuf;
    }
	AfxMessageBox(strOut);
 }

/*==============================================================================
==============================================================================*/
