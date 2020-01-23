#ifndef YY_parse_h_included
#define YY_parse_h_included
/* before anything */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#endif
#include <stdio.h>
 /* %{ and %header{ and %union, during decl */
#ifndef YY_parse_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_parse_COMPATIBILITY 1
#else
#define  YY_parse_COMPATIBILITY 0
#endif
#endif

#if YY_parse_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_parse_LTYPE
#define YY_parse_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_parse_STYPE 
#define YY_parse_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_parse_DEBUG
#define  YY_parse_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
#endif
#endif
#ifdef YY_parse_STYPE
#ifndef yystype
#define yystype YY_parse_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_parse_USE_GOTO
#define YY_parse_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_parse_USE_GOTO
#define YY_parse_USE_GOTO 0
#endif

#ifndef YY_parse_PURE
/* YY_parse_PURE */
#endif
/* prefix */
#ifndef YY_parse_DEBUG
/* YY_parse_DEBUG */
#endif
#ifndef YY_parse_LSP_NEEDED
 /* YY_parse_LSP_NEEDED*/
#endif
/* DEFAULT LTYPE*/
#ifdef YY_parse_LSP_NEEDED
#ifndef YY_parse_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_parse_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
#ifndef YY_parse_STYPE
#define YY_parse_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_parse_PARSE
#define YY_parse_PARSE yyparse
#endif
#ifndef YY_parse_LEX
#define YY_parse_LEX yylex
#endif
#ifndef YY_parse_LVAL
#define YY_parse_LVAL yylval
#endif
#ifndef YY_parse_LLOC
#define YY_parse_LLOC yylloc
#endif
#ifndef YY_parse_CHAR
#define YY_parse_CHAR yychar
#endif
#ifndef YY_parse_NERRS
#define YY_parse_NERRS yynerrs
#endif
#ifndef YY_parse_DEBUG_FLAG
#define YY_parse_DEBUG_FLAG yydebug
#endif
#ifndef YY_parse_ERROR
#define YY_parse_ERROR yyerror
#endif

#ifndef YY_parse_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_parse_PARSE_PARAM
#ifndef YY_parse_PARSE_PARAM_DEF
#define YY_parse_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_parse_PARSE_PARAM
#define YY_parse_PARSE_PARAM void
#endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_parse_PURE
extern YY_parse_STYPE YY_parse_LVAL;
#endif

#define	VAR	258
#define	CONS	259
#define	SIGN	260
#define	AR_M_OP	261
#define	RE_OP	262
#define	END_C	263
#define	COMMA	264
#define	COLON	265
#define	MINIMISE	266
#define	MAXIMISE	267

 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
#ifndef YY_parse_CLASS
#define YY_parse_CLASS parse
#endif

#ifndef YY_parse_INHERIT
#define YY_parse_INHERIT
#endif
#ifndef YY_parse_MEMBERS
#define YY_parse_MEMBERS 
#endif
#ifndef YY_parse_LEX_BODY
#define YY_parse_LEX_BODY  
#endif
#ifndef YY_parse_ERROR_BODY
#define YY_parse_ERROR_BODY  
#endif
#ifndef YY_parse_CONSTRUCTOR_PARAM
#define YY_parse_CONSTRUCTOR_PARAM
#endif
/* choose between enum and const */
#ifndef YY_parse_USE_CONST_TOKEN
#define YY_parse_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_parse_USE_CONST_TOKEN != 0
#ifndef YY_parse_ENUM_TOKEN
#define YY_parse_ENUM_TOKEN yy_parse_enum_token
#endif
#endif

class YY_parse_CLASS YY_parse_INHERIT
{
public: 
#if YY_parse_USE_CONST_TOKEN != 0
/* static const int token ... */
static const int VAR;
static const int CONS;
static const int SIGN;
static const int AR_M_OP;
static const int RE_OP;
static const int END_C;
static const int COMMA;
static const int COLON;
static const int MINIMISE;
static const int MAXIMISE;

 /* decl const */
#else
enum YY_parse_ENUM_TOKEN { YY_parse_NULL_TOKEN=0
	,VAR=258
	,CONS=259
	,SIGN=260
	,AR_M_OP=261
	,RE_OP=262
	,END_C=263
	,COMMA=264
	,COLON=265
	,MINIMISE=266
	,MAXIMISE=267

 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_parse_PARSE(YY_parse_PARSE_PARAM);
 virtual void YY_parse_ERROR(char *msg) YY_parse_ERROR_BODY;
#ifdef YY_parse_PURE
#ifdef YY_parse_LSP_NEEDED
 virtual int  YY_parse_LEX(YY_parse_STYPE *YY_parse_LVAL,YY_parse_LTYPE *YY_parse_LLOC) YY_parse_LEX_BODY;
#else
 virtual int  YY_parse_LEX(YY_parse_STYPE *YY_parse_LVAL) YY_parse_LEX_BODY;
#endif
#else
 virtual int YY_parse_LEX() YY_parse_LEX_BODY;
 YY_parse_STYPE YY_parse_LVAL;
#ifdef YY_parse_LSP_NEEDED
 YY_parse_LTYPE YY_parse_LLOC;
#endif
 int YY_parse_NERRS;
 int YY_parse_CHAR;
#endif
#if YY_parse_DEBUG != 0
public:
 int YY_parse_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_parse_CLASS(YY_parse_CONSTRUCTOR_PARAM);
public:
 YY_parse_MEMBERS 
};
/* other declare folow */
#endif


#if YY_parse_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_parse_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_parse_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_parse_DEBUG 
#define YYDEBUG YY_parse_DEBUG
#endif
#endif

#endif
/* END */
#endif
