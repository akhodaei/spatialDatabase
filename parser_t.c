#define YY_Parser_h_included

/*  A Bison++ parser, made from parser.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WINDOWS) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
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
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  
#define YY_Parser_LSP_NEEDED 
#define YY_Parser_CONSTRUCTOR_INIT  : hist(0), prompt(getenv("USER"))
#define YY_Parser_ERROR_BODY  =0
#define YY_Parser_LEX_BODY  =0

 #ifdef CONST
 #undef CONST
 #endif
 #include <iostream.h>
 #include <fstream.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include <sys/types.h>
 #include "string.h"

#ifndef ARG_TYPE_H
#define ARG_TYPE_H

 typedef struct ArgType
 {
   char *strVal ;
   float realVal ;
 } ArgType ;

#endif

#define YY_Parser_MEMBERS  \
        public: \
         void PutPrompt() { /*cout << prompt << "[" << ++hist << "] " ;*/\
							AfxMessageBox(prompt.GetText()); } \
        protected: \
         int hist ; \
         String prompt ;

typedef union 
{
  float realTok ;
  char* strTok ;
  ArgType arg ;
  char* relOp ;
  char* aggOp;
} yy_Parser_stype;
#define YY_Parser_STYPE yy_Parser_stype


#define YYDEBUG 1
#include "scanner.h"
#include "db.h"
 extern Scanner scanner;
 extern DB (*dataBase);
 extern bool m_EndFlag;
/* %{ and %header{ and %union, during decl */
#define YY_Parser_BISON 1
#ifndef YY_Parser_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_Parser_COMPATIBILITY 1
#else
#define  YY_Parser_COMPATIBILITY 0
#endif
#endif

#if YY_Parser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_Parser_LTYPE
#define YY_Parser_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_Parser_STYPE 
#define YY_Parser_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_Parser_DEBUG
#define  YY_Parser_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_Parser_STYPE
#ifndef yystype
#define yystype YY_Parser_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_Parser_USE_GOTO
#define YY_Parser_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_Parser_USE_GOTO
#define YY_Parser_USE_GOTO 0
#endif

#ifndef YY_Parser_PURE
/*  YY_Parser_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */
#define YY_Parser_PARSE parser.cppparse
#define YY_Parser_LEX parser.cpplex
#define YY_Parser_ERROR parser.cpperror
#define YY_Parser_LVAL parser.cpplval
#define YY_Parser_CHAR parser.cppchar
#define YY_Parser_DEBUG parser.cppdebug
/* prefix */
#ifndef YY_Parser_DEBUG
/* YY_Parser_DEBUG */
#endif


#ifndef YY_Parser_LSP_NEEDED
 /* YY_Parser_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_Parser_LSP_NEEDED
#ifndef YY_Parser_LTYPE
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

#define YY_Parser_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_Parser_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

#ifndef YY_Parser_STYPE
#define YY_Parser_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_Parser_PARSE
#define YY_Parser_PARSE yyparse
#endif
#ifndef YY_Parser_LEX
#define YY_Parser_LEX yylex
#endif
#ifndef YY_Parser_LVAL
#define YY_Parser_LVAL yylval
#endif
#ifndef YY_Parser_LLOC
#define YY_Parser_LLOC yylloc
#endif
#ifndef YY_Parser_CHAR
#define YY_Parser_CHAR yychar
#endif
#ifndef YY_Parser_NERRS
#define YY_Parser_NERRS yynerrs
#endif
#ifndef YY_Parser_DEBUG_FLAG
#define YY_Parser_DEBUG_FLAG yydebug
#endif
#ifndef YY_Parser_ERROR
#define YY_Parser_ERROR yyerror
#endif
#ifndef YY_Parser_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_Parser_PARSE_PARAM
#ifndef YY_Parser_PARSE_PARAM_DEF
#define YY_Parser_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_Parser_PARSE_PARAM
#define YY_Parser_PARSE_PARAM void
#endif
#endif
#if YY_Parser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_Parser_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_Parser_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_Parser_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_Parser_PURE
#ifndef YYPURE
#define YYPURE YY_Parser_PURE
#endif
#endif
#ifdef YY_Parser_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_Parser_DEBUG 
#endif
#endif
#ifndef YY_Parser_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_Parser_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_Parser_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_Parser_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */
#define	REL_OP	258
#define	STR_TOK	259
#define	QUOT_STR	260
#define	CONST	261
#define	AGG_OP	262
#define	L_PAREN	263
#define	R_PAREN	264
#define	PERIOD	265
#define	IF	266
#define	COMMA	267
#define	COLON	268
#define	QUESTION_MARK	269
#define	PERCENT	270
#define	PLUS	271
#define	MINUS	272
#define	CONSULT	273
#define	AREA	274
#define	DISPLAY	275
#define	INTO	276
#define	ONTO	277
#define	QUIT	278
#define	BEGIN_MOD	279
#define	END_MOD	280
#define	SHELL	281
#define	NOT_REL	282
#define	GROUP_BY	283
#define	CONVT_T	284
#define	CONVT_L	285
#define	DISPLAY_POINTS	286

 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_Parser_CLASS
#define YY_Parser_CLASS Parser
#endif
#ifndef YY_Parser_INHERIT
#define YY_Parser_INHERIT
#endif
#ifndef YY_Parser_MEMBERS
#define YY_Parser_MEMBERS 
#endif
#ifndef YY_Parser_LEX_BODY
#define YY_Parser_LEX_BODY  
#endif
#ifndef YY_Parser_ERROR_BODY
#define YY_Parser_ERROR_BODY  
#endif
#ifndef YY_Parser_CONSTRUCTOR_PARAM
#define YY_Parser_CONSTRUCTOR_PARAM
#endif
#ifndef YY_Parser_CONSTRUCTOR_CODE
#define YY_Parser_CONSTRUCTOR_CODE
#endif
#ifndef YY_Parser_CONSTRUCTOR_INIT
#define YY_Parser_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_Parser_USE_CONST_TOKEN
#define YY_Parser_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_Parser_USE_CONST_TOKEN != 0
#ifndef YY_Parser_ENUM_TOKEN
#define YY_Parser_ENUM_TOKEN yy_Parser_enum_token
#endif
#endif

class YY_Parser_CLASS YY_Parser_INHERIT
{
public: 
#if YY_Parser_USE_CONST_TOKEN != 0
/* static const int token ... */
static const int REL_OP;
static const int STR_TOK;
static const int QUOT_STR;
static const int CONST;
static const int AGG_OP;
static const int L_PAREN;
static const int R_PAREN;
static const int PERIOD;
static const int IF;
static const int COMMA;
static const int COLON;
static const int QUESTION_MARK;
static const int PERCENT;
static const int PLUS;
static const int MINUS;
static const int CONSULT;
static const int AREA;
static const int DISPLAY;
static const int INTO;
static const int ONTO;
static const int QUIT;
static const int BEGIN_MOD;
static const int END_MOD;
static const int SHELL;
static const int NOT_REL;
static const int GROUP_BY;
static const int CONVT_T;
static const int CONVT_L;
static const int DISPLAY_POINTS;

 /* decl const */
#else
enum YY_Parser_ENUM_TOKEN { YY_Parser_NULL_TOKEN=0
	,REL_OP=258
	,STR_TOK=259
	,QUOT_STR=260
	,CONST=261
	,AGG_OP=262
	,L_PAREN=263
	,R_PAREN=264
	,PERIOD=265
	,IF=266
	,COMMA=267
	,COLON=268
	,QUESTION_MARK=269
	,PERCENT=270
	,PLUS=271
	,MINUS=272
	,CONSULT=273
	,AREA=274
	,DISPLAY=275
	,INTO=276
	,ONTO=277
	,QUIT=278
	,BEGIN_MOD=279
	,END_MOD=280
	,SHELL=281
	,NOT_REL=282
	,GROUP_BY=283
	,CONVT_T=284
	,CONVT_L=285
	,DISPLAY_POINTS=286

 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_Parser_PARSE (YY_Parser_PARSE_PARAM);
 virtual void YY_Parser_ERROR(char *msg) YY_Parser_ERROR_BODY;
#ifdef YY_Parser_PURE
#ifdef YY_Parser_LSP_NEEDED
 virtual int  YY_Parser_LEX (YY_Parser_STYPE *YY_Parser_LVAL,YY_Parser_LTYPE *YY_Parser_LLOC) YY_Parser_LEX_BODY;
#else
 virtual int  YY_Parser_LEX (YY_Parser_STYPE *YY_Parser_LVAL) YY_Parser_LEX_BODY;
#endif
#else
 virtual int YY_Parser_LEX() YY_Parser_LEX_BODY;
 YY_Parser_STYPE YY_Parser_LVAL;
#ifdef YY_Parser_LSP_NEEDED
 YY_Parser_LTYPE YY_Parser_LLOC;
#endif
 int   YY_Parser_NERRS;
 int    YY_Parser_CHAR;
#endif
#if YY_Parser_DEBUG != 0
 int YY_Parser_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_Parser_CLASS(YY_Parser_CONSTRUCTOR_PARAM);
public:
 YY_Parser_MEMBERS 
};
/* other declare folow */
#if YY_Parser_USE_CONST_TOKEN != 0
const int YY_Parser_CLASS::REL_OP=258;
const int YY_Parser_CLASS::STR_TOK=259;
const int YY_Parser_CLASS::QUOT_STR=260;
const int YY_Parser_CLASS::CONST=261;
const int YY_Parser_CLASS::AGG_OP=262;
const int YY_Parser_CLASS::L_PAREN=263;
const int YY_Parser_CLASS::R_PAREN=264;
const int YY_Parser_CLASS::PERIOD=265;
const int YY_Parser_CLASS::IF=266;
const int YY_Parser_CLASS::COMMA=267;
const int YY_Parser_CLASS::COLON=268;
const int YY_Parser_CLASS::QUESTION_MARK=269;
const int YY_Parser_CLASS::PERCENT=270;
const int YY_Parser_CLASS::PLUS=271;
const int YY_Parser_CLASS::MINUS=272;
const int YY_Parser_CLASS::CONSULT=273;
const int YY_Parser_CLASS::AREA=274;
const int YY_Parser_CLASS::DISPLAY=275;
const int YY_Parser_CLASS::INTO=276;
const int YY_Parser_CLASS::ONTO=277;
const int YY_Parser_CLASS::QUIT=278;
const int YY_Parser_CLASS::BEGIN_MOD=279;
const int YY_Parser_CLASS::END_MOD=280;
const int YY_Parser_CLASS::SHELL=281;
const int YY_Parser_CLASS::NOT_REL=282;
const int YY_Parser_CLASS::GROUP_BY=283;
const int YY_Parser_CLASS::CONVT_T=284;
const int YY_Parser_CLASS::CONVT_L=285;
const int YY_Parser_CLASS::DISPLAY_POINTS=286;

 /* const YY_Parser_CLASS::token */
#endif
/*apres const  */
YY_Parser_CLASS::YY_Parser_CLASS(YY_Parser_CONSTRUCTOR_PARAM) YY_Parser_CONSTRUCTOR_INIT
{
#if YY_Parser_DEBUG != 0
YY_Parser_DEBUG_FLAG=0;
#endif
YY_Parser_CONSTRUCTOR_CODE;
};
#endif


#define	YYFINAL		133
#define	YYFLAG		-32768
#define	YYNTBASE	32

#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 49)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31
};

#if YY_Parser_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,     9,    11,    14,    17,    20,    25,
    30,    34,    40,    46,    50,    56,    62,    66,    77,    95,
    99,   103,   107,   117,   119,   122,   127,   132,   134,   136,
   140,   145,   152,   154,   156,   158,   162,   167,   173,   177,
   182,   187,   190,   192,   196,   199,   203,   206,   209,   211,
   213,   215,   217
};

static const short yyrhs[] = {    33,
     0,    32,    33,     0,    34,     0,    35,     0,    10,     0,
     1,    10,     0,    23,    10,     0,    20,    10,     0,    20,
    21,     5,    10,     0,    20,    22,     5,    10,     0,    20,
     5,    10,     0,    20,     5,    21,     5,    10,     0,    20,
     5,    22,     5,    10,     0,    31,     5,    10,     0,    31,
     5,    21,     5,    10,     0,    20,     5,    22,     5,    10,
     0,    26,     5,    10,     0,    19,     4,     8,     6,    13,
     6,    12,     6,     9,    10,     0,    19,     4,     8,     6,
    13,     6,    12,     6,     9,     8,     6,    13,     6,    12,
     6,     9,    10,     0,    18,     5,    10,     0,    29,     5,
    10,     0,    30,     5,    10,     0,    24,    15,     4,    15,
    36,    25,    15,     4,    15,     0,    37,     0,    36,    37,
     0,    38,    11,    42,    10,     0,     4,     8,    39,     9,
     0,    40,     0,    47,     0,    39,    12,    39,     0,    41,
     8,    45,     9,     0,    41,     8,    45,    28,     4,     9,
     0,     7,     0,    43,     0,    44,     0,    42,    12,    42,
     0,     4,     8,    48,     9,     0,    27,     4,     8,    48,
     9,     0,    45,     3,     6,     0,    45,     3,    16,     6,
     0,    45,     3,    17,     6,     0,    45,    46,     0,    46,
     0,    16,     6,     4,     0,    16,     4,     0,    17,     6,
     4,     0,    17,     4,     0,     6,     4,     0,     4,     0,
     4,     0,     6,     0,    47,     0,    48,    12,    47,     0
};

#endif

#if YY_Parser_DEBUG != 0
static const short yyrline[] = { 0,
    82,    83,    86,    88,    91,    93,    99,   103,   105,   112,
   118,   120,   126,   132,   134,   140,   146,   148,   154,   160,
   167,   169,   173,   179,   181,   184,   188,   192,   194,   196,
   200,   202,   206,   210,   212,   214,   218,   221,   226,   229,
   232,   237,   239,   243,   246,   249,   252,   255,   258,   262,
   266,   270,   272
};

static const char * const yytname[] = {   "$","error","$illegal.","REL_OP","STR_TOK",
"QUOT_STR","CONST","AGG_OP","L_PAREN","R_PAREN","PERIOD","IF","COMMA","COLON",
"QUESTION_MARK","PERCENT","PLUS","MINUS","CONSULT","AREA","DISPLAY","INTO","ONTO",
"QUIT","BEGIN_MOD","END_MOD","SHELL","NOT_REL","GROUP_BY","CONVT_T","CONVT_L",
"DISPLAY_POINTS","program","progLine","command","module","clauseList","clause",
"headpredicate","headparam","aggregate","aggtype","body","predicate","expression",
"term","item","arg","argList",""
};
#endif

static const short yyr1[] = {     0,
    32,    32,    33,    33,    33,    33,    34,    34,    34,    34,
    34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
    34,    34,    35,    36,    36,    37,    38,    39,    39,    39,
    40,    40,    41,    42,    42,    42,    43,    43,    44,    44,
    44,    45,    45,    46,    46,    46,    46,    46,    46,    47,
    47,    48,    48
};

static const short yyr2[] = {     0,
     1,     2,     1,     1,     1,     2,     2,     2,     4,     4,
     3,     5,     5,     3,     5,     5,     3,    10,    17,     3,
     3,     3,     9,     1,     2,     4,     4,     1,     1,     3,
     4,     6,     1,     1,     1,     3,     4,     5,     3,     4,
     4,     2,     1,     3,     2,     3,     2,     2,     1,     1,
     1,     1,     3
};

static const short yydefact[] = {     0,
     0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     1,     3,     4,     6,     0,     0,     0,     8,
     0,     0,     7,     0,     0,     0,     0,     0,     2,    20,
     0,    11,     0,     0,     0,     0,     0,    17,    21,    22,
    14,     0,     0,     0,     0,     9,    10,     0,     0,     0,
    12,    13,     0,     0,    24,     0,    15,     0,     0,     0,
    25,     0,     0,    50,    51,    33,     0,    28,     0,    29,
     0,    49,     0,     0,     0,     0,     0,    34,    35,     0,
    43,     0,    27,     0,     0,     0,     0,    48,    45,     0,
    47,     0,     0,    26,     0,     0,    49,    42,     0,    30,
     0,    23,    52,     0,    44,    46,     0,    36,    39,     0,
     0,     0,    18,    31,     0,    37,     0,     0,    40,    41,
     0,     0,    53,    38,     0,    32,     0,     0,     0,     0,
    19,     0,     0
};

static const short yydefgoto[] = {    12,
    13,    14,    15,    54,    55,    56,    67,    68,    69,    77,
    78,    79,    80,    81,    70,   104
};

static const short yypact[] = {    15,
    -6,-32768,     8,    13,    45,    11,    21,    37,    52,    57,
    60,     0,-32768,-32768,-32768,-32768,    67,    68,    -7,-32768,
    75,    76,-32768,    80,    85,    86,    88,    27,-32768,-32768,
    91,-32768,    94,    95,    92,    93,    89,-32768,-32768,-32768,
-32768,    96,    97,    98,    99,-32768,-32768,   101,   102,   100,
-32768,-32768,   103,     2,-32768,   104,-32768,   105,     5,   106,
-32768,    47,   107,-32768,-32768,-32768,    -4,-32768,   108,-32768,
   110,   111,   114,    50,    83,   116,    78,-32768,-32768,    66,
-32768,   113,-32768,     5,    69,   109,    87,-32768,-32768,   119,
-32768,   121,   118,-32768,    47,    62,-32768,-32768,    84,-32768,
    43,-32768,-32768,    31,-32768,-32768,    87,-32768,-32768,   122,
   123,   124,-32768,-32768,   127,-32768,    87,    49,-32768,-32768,
   120,   125,-32768,-32768,   126,-32768,   115,   129,   128,   130,
-32768,   136,-32768
};

static const short yypgoto[] = {-32768,
   131,-32768,-32768,-32768,    53,-32768,    54,-32768,-32768,    44,
-32768,-32768,    56,   -73,   -85,    35
};


#define	YYLAST		143


static const short yytable[] = {   132,
     1,   103,    32,    16,    83,    53,    98,    84,    64,     2,
    65,    66,    17,    33,    34,     1,    18,     3,     4,     5,
    23,   103,     6,     7,     2,     8,    60,    98,     9,    10,
    11,   123,     3,     4,     5,    24,    41,     6,     7,   116,
     8,    25,   117,     9,    10,    11,    97,    42,    73,    19,
    72,   114,    73,    89,    20,    90,    26,   124,    74,    75,
   117,    27,    74,    75,    28,    21,    22,   109,    96,    97,
   115,    73,    97,    76,    73,    31,    30,   110,   111,    35,
    36,    74,    75,    37,    74,    75,    91,    94,    92,    95,
    64,   112,    65,   113,    38,    39,    43,    40,    44,    45,
    49,    46,    47,    48,    53,    58,    61,    51,    52,    50,
    59,    57,    82,    86,    62,    85,    63,    88,    87,    93,
    71,    99,   105,   102,   106,   107,   128,   119,   120,   121,
   122,   127,   125,   126,   129,   133,   130,   100,   108,   131,
   101,   118,    29
};

static const short yycheck[] = {     0,
     1,    87,    10,    10,     9,     4,    80,    12,     4,    10,
     6,     7,     5,    21,    22,     1,     4,    18,    19,    20,
    10,   107,    23,    24,    10,    26,    25,   101,    29,    30,
    31,   117,    18,    19,    20,    15,    10,    23,    24,     9,
    26,     5,    12,    29,    30,    31,     4,    21,     6,     5,
     4,     9,     6,     4,    10,     6,     5,     9,    16,    17,
    12,     5,    16,    17,     5,    21,    22,     6,     3,     4,
    28,     6,     4,    27,     6,     8,    10,    16,    17,     5,
     5,    16,    17,     4,    16,    17,     4,    10,     6,    12,
     4,     8,     6,    10,    10,    10,     6,    10,     5,     5,
     5,    10,    10,    15,     4,     6,    54,    10,    10,    13,
     8,    10,     6,     4,    11,     8,    12,     4,     8,     4,
    15,     9,     4,    15,     4,     8,    12,     6,     6,     6,
     4,     6,    13,     9,     6,     0,     9,    84,    95,    10,
    85,   107,    12
};
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_Parser_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_Parser_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_Parser_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_Parser_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_Parser_CHAR = (token), YY_Parser_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_Parser_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_Parser_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_Parser_PURE
/* UNPURE */
#define YYLEX           YY_Parser_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_Parser_CHAR;                      /*  the lookahead symbol        */
YY_Parser_STYPE      YY_Parser_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_Parser_NERRS;                 /*  number of parse errors so far */
#ifdef YY_Parser_LSP_NEEDED
YY_Parser_LTYPE YY_Parser_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_Parser_LSP_NEEDED
#define YYLEX           YY_Parser_LEX(&YY_Parser_LVAL, &YY_Parser_LLOC)
#else
#define YYLEX           YY_Parser_LEX(&YY_Parser_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_Parser_DEBUG != 0
int YY_Parser_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_Parser_CLASS::
#endif
     YY_Parser_PARSE(YY_Parser_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_Parser_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_Parser_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_Parser_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_Parser_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_Parser_LSP_NEEDED
  YY_Parser_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_Parser_LTYPE *yyls = yylsa;
  YY_Parser_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_Parser_PURE
  int YY_Parser_CHAR;
  YY_Parser_STYPE YY_Parser_LVAL;
  int YY_Parser_NERRS;
#ifdef YY_Parser_LSP_NEEDED
  YY_Parser_LTYPE YY_Parser_LLOC;
#endif
#endif

  YY_Parser_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_Parser_NERRS = 0;
  YY_Parser_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_Parser_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_Parser_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_Parser_LSP_NEEDED
      YY_Parser_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_Parser_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_Parser_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_Parser_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_Parser_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_Parser_LSP_NEEDED
      yyls = (YY_Parser_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_Parser_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_Parser_DEBUG != 0
      if (YY_Parser_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_Parser_CHAR == YYEMPTY)
    {
#if YY_Parser_DEBUG != 0
      if (YY_Parser_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_Parser_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_Parser_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_Parser_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_Parser_DEBUG != 0
      if (YY_Parser_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_Parser_CHAR);

#if YY_Parser_DEBUG != 0
      if (YY_Parser_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_Parser_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_Parser_CHAR, YY_Parser_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_Parser_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_Parser_CHAR != YYEOF)
    YY_Parser_CHAR = YYEMPTY;

  *++yyvsp = YY_Parser_LVAL;
#ifdef YY_Parser_LSP_NEEDED
  *++yylsp = YY_Parser_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
{ PutPrompt() ; ;
    break;}
case 4:
{  return -1;
                ;
    break;}
case 5:
{ PutPrompt() ; ;
    break;}
case 6:
{ yyerror("Syntax error") ; 
				  return -1;   
                ;
    break;}
case 7:
{ cout << "Quitting, goodbye!\n" ; 
                //  cout << "\nTotal Elapse Time : "<< (clock()/1000000.0)<<endl;
                   exit(0) ; ;
    break;}
case 8:
{ cout << (*dataBase) << endl ; ;
    break;}
case 9:
{ 
                  ofstream os(yyvsp[-1].strTok, ios::out) ;
                  if (!os)
                    cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for output\n" ;
                  else os << (*dataBase) << endl ;
                ;
    break;}
case 10:
{ ofstream os(yyvsp[-1].strTok, ios::app) ;
                  if (!os)
                   cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for output\n" ;
                  else os << (*dataBase) << endl ;
                ;
    break;}
case 11:
{ (*dataBase).Display(yyvsp[-1].strTok, cout); ;
    break;}
case 12:
{ ofstream os(yyvsp[-1].strTok, ios::out) ;
                  if (!os)
                    cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for output\n" ;
                  else (*dataBase).Display(yyvsp[-3].strTok, os);
                ;
    break;}
case 13:
{ ofstream os(yyvsp[-1].strTok, ios::app) ;
                  if (!os)
                    cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for append\n" ;
                  else (*dataBase).Display(yyvsp[-3].strTok, os);
                ;
    break;}
case 14:
{ (*dataBase).Display_points(yyvsp[-1].strTok, cout); ;
    break;}
case 15:
{ ofstream os(yyvsp[-1].strTok, ios::out) ;
                  if (!os)
                    cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for output\n" ;
                  else (*dataBase).Display_points(yyvsp[-3].strTok, os);
                ;
    break;}
case 16:
{ ofstream os(yyvsp[-1].strTok, ios::app) ;
                  if (!os)
                    cerr << "Couldn't open file \"" << yyvsp[-1].strTok << "\" for append\n" ;
                  else (*dataBase).Display_points(yyvsp[-3].strTok, os);
                ;
    break;}
case 17:
{ system(yyvsp[-1].strTok) ; ;
    break;}
case 18:
{ 
                  (*dataBase).AreaHandler(yyvsp[-8].strTok,yyvsp[-6].realTok,yyvsp[-4].realTok,yyvsp[-2].realTok); 
                  delete [] yyvsp[-8].strTok;
                ;
    break;}
case 19:
{ 
                  (*dataBase).AreaHandler2(yyvsp[-15].strTok,yyvsp[-13].realTok,yyvsp[-11].realTok,yyvsp[-9].realTok,yyvsp[-6].realTok,yyvsp[-4].realTok,yyvsp[-2].realTok); 
                  delete [] yyvsp[-15].strTok;
                ;
    break;}
case 20:
{
                  if (scanner.SwitchStream(yyvsp[-1].strTok))
                  { yylloc.first_line = yylloc.last_line = 0 ;
                    yylloc.first_column = yylloc.last_column = 0 ; }
                  else cerr << "Can't open file '" << yyvsp[-1].strTok << "'\n" ;
                ;
    break;}
case 21:
{ (*dataBase).Convt_t(yyvsp[-1].strTok); ;
    break;}
case 22:
{ (*dataBase).Convt_l(yyvsp[-1].strTok); ;
    break;}
case 23:
{ 
				   return -1;
				 ;
    break;}
case 24:
{ ;
    break;}
case 26:
{(*dataBase).ClauseHandler(); ;
    break;}
case 27:
{ (*dataBase).PredHandler(yyvsp[-3].strTok); 
                  delete [] yyvsp[-3].strTok ; ;
    break;}
case 28:
{ ;
    break;}
case 29:
{ ;
    break;}
case 30:
{ ;
    break;}
case 31:
{ (*dataBase).ObjectiveHandler();
    break;}
case 32:
{ (*dataBase).ObjectiveHandler(yyvsp[-1].strTok);
    break;}
case 33:
{ (*dataBase).AggregateHandler(yyvsp[0].aggOp);
	       delete[] yyvsp[0].aggOp; ;
    break;}
case 34:
{ ;
    break;}
case 35:
{ ;
    break;}
case 36:
{ ;
    break;}
case 37:
{ (*dataBase).PredHandler(yyvsp[-3].strTok); 
                  delete [] yyvsp[-3].strTok ; ;
    break;}
case 38:
{ (*dataBase).NegPredHandler(yyvsp[-3].strTok); 
                  delete [] yyvsp[-3].strTok ; ;
    break;}
case 39:
{ (*dataBase).ExpressionHandler(yyvsp[-1].relOp, yyvsp[0].realTok);
                  delete [] yyvsp[-1].relOp; ;
    break;}
case 40:
{ (*dataBase).ExpressionHandler(yyvsp[-2].relOp, yyvsp[0].realTok);
                    delete [] yyvsp[-2].relOp; ;
    break;}
case 41:
{ (*dataBase).ExpressionHandler(yyvsp[-2].relOp,- yyvsp[0].realTok);
                  delete [] yyvsp[-2].relOp; ;
    break;}
case 42:
{ ;
    break;}
case 43:
{ ;
    break;}
case 44:
{ (*dataBase).ItemHandler(yyvsp[-1].realTok,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 45:
{ (*dataBase).ItemHandler(1,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 46:
{ (*dataBase).ItemHandler(-yyvsp[-1].realTok,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 47:
{ (*dataBase).ItemHandler(-1,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 48:
{ (*dataBase).ItemHandler(yyvsp[-1].realTok,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 49:
{ (*dataBase).ItemHandler(1,yyvsp[0].strTok); 
                 delete [] yyvsp[0].strTok;  ;
    break;}
case 50:
{
		  (*dataBase).ArgHandler(yyvsp[0].strTok) ;
                  delete [] yyvsp[0].strTok ; ;
    break;}
case 51:
{ printf("(*dataBase).ArgHandler(%f)\n",yyvsp[0].realTok) ; ;
    break;}
case 52:
{ ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_Parser_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_Parser_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_Parser_LLOC.first_line;
      yylsp->first_column = YY_Parser_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_Parser_NERRS;

#ifdef YY_Parser_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_Parser_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_Parser_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_Parser_ERROR_VERBOSE */
	YY_Parser_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_Parser_CHAR == YYEOF)
	YYABORT;

#if YY_Parser_DEBUG != 0
      if (YY_Parser_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_Parser_CHAR, yytname[yychar1]);
#endif

      YY_Parser_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_Parser_LSP_NEEDED
  yylsp--;
#endif

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_Parser_DEBUG != 0
  if (YY_Parser_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_Parser_LVAL;
#ifdef YY_Parser_LSP_NEEDED
  *++yylsp = YY_Parser_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */


//----------------------------------------------------------------------








