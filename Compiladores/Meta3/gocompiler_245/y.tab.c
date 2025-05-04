/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SEMICOLON = 258,
     COMMA = 259,
     BLANKID = 260,
     ASSIGN = 261,
     STAR = 262,
     DIV = 263,
     MINUS = 264,
     PLUS = 265,
     EQ = 266,
     GE = 267,
     GT = 268,
     LBRACE = 269,
     LE = 270,
     LPAR = 271,
     LSQ = 272,
     LT = 273,
     MOD = 274,
     NE = 275,
     NOT = 276,
     AND = 277,
     OR = 278,
     RBRACE = 279,
     RPAR = 280,
     RSQ = 281,
     PACKAGE = 282,
     RETURN = 283,
     ELSE = 284,
     FOR = 285,
     IF = 286,
     VAR = 287,
     INT = 288,
     FLOAT32 = 289,
     BOOL = 290,
     STRING = 291,
     PRINT = 292,
     PARSEINT = 293,
     FUNC = 294,
     CMDARGS = 295,
     RESERVED = 296,
     IDENTIFIER = 297,
     NATURAL = 298,
     DECIMAL = 299,
     STRLIT = 300,
     PLUS_SOZINHO = 301,
     MINUS_SOZINHO = 302
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COMMA 259
#define BLANKID 260
#define ASSIGN 261
#define STAR 262
#define DIV 263
#define MINUS 264
#define PLUS 265
#define EQ 266
#define GE 267
#define GT 268
#define LBRACE 269
#define LE 270
#define LPAR 271
#define LSQ 272
#define LT 273
#define MOD 274
#define NE 275
#define NOT 276
#define AND 277
#define OR 278
#define RBRACE 279
#define RPAR 280
#define RSQ 281
#define PACKAGE 282
#define RETURN 283
#define ELSE 284
#define FOR 285
#define IF 286
#define VAR 287
#define INT 288
#define FLOAT32 289
#define BOOL 290
#define STRING 291
#define PRINT 292
#define PARSEINT 293
#define FUNC 294
#define CMDARGS 295
#define RESERVED 296
#define IDENTIFIER 297
#define NATURAL 298
#define DECIMAL 299
#define STRLIT 300
#define PLUS_SOZINHO 301
#define MINUS_SOZINHO 302




/* Copy the first part of user declarations.  */
#line 3 "gocompiler.y"

#include "ast.h"

int yylex(void);
void yyerror(char *);


struct node *program;
//int yydebug=1;




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "gocompiler.y"
{
    char *lexeme;
    struct node *node;
}
/* Line 193 of yacc.c.  */
#line 208 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */
#line 42 "gocompiler.y"

#define LOCATE(node, line, column) { node->token_line = line; node->token_column = column; }


/* Line 216 of yacc.c.  */
#line 236 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    16,    17,    20,    26,    30,
      34,    35,    37,    39,    41,    43,    51,    58,    62,    63,
      68,    69,    73,    76,    80,    84,    85,    89,    93,   103,
     109,   115,   120,   123,   125,   127,   129,   134,   139,   141,
     145,   146,   158,   167,   173,   177,   182,   186,   187,   191,
     195,   199,   203,   207,   211,   215,   219,   223,   227,   231,
     235,   239,   242,   245,   248,   250,   252,   254,   256,   260
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    27,    42,     3,    50,    -1,    50,    51,
       3,    -1,    50,    55,     3,    -1,    -1,    32,    52,    -1,
      32,    16,    52,     3,    25,    -1,    42,    53,    54,    -1,
      53,     4,    42,    -1,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    39,    42,    16,    56,    25,    54,    58,
      -1,    39,    42,    16,    56,    25,    58,    -1,    42,    54,
      57,    -1,    -1,    57,     4,    42,    54,    -1,    -1,    14,
      59,    24,    -1,    59,     3,    -1,    59,    51,     3,    -1,
      59,    60,     3,    -1,    -1,    42,     6,    65,    -1,    14,
      61,    24,    -1,    31,    65,    14,    61,    24,    29,    14,
      61,    24,    -1,    31,    65,    14,    61,    24,    -1,    30,
      65,    14,    61,    24,    -1,    30,    14,    61,    24,    -1,
      28,    65,    -1,    28,    -1,    63,    -1,    62,    -1,    37,
      16,    65,    25,    -1,    37,    16,    45,    25,    -1,     1,
      -1,    61,    60,     3,    -1,    -1,    42,     4,     5,     6,
      38,    16,    40,    17,    65,    26,    25,    -1,    42,     4,
       5,     6,    38,    16,     1,    25,    -1,    42,    16,    65,
      64,    25,    -1,    42,    16,    25,    -1,    42,    16,     1,
      25,    -1,    64,     4,    65,    -1,    -1,    65,    23,    65,
      -1,    65,    22,    65,    -1,    65,    18,    65,    -1,    65,
      13,    65,    -1,    65,    11,    65,    -1,    65,    20,    65,
      -1,    65,    15,    65,    -1,    65,    12,    65,    -1,    65,
      10,    65,    -1,    65,     9,    65,    -1,    65,     7,    65,
      -1,    65,     8,    65,    -1,    65,    19,    65,    -1,    21,
      65,    -1,     9,    65,    -1,    10,    65,    -1,    43,    -1,
      44,    -1,    42,    -1,    63,    -1,    16,    65,    25,    -1,
      16,     1,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    57,    67,    77,    81,    82,    85,    99,
     111,   114,   115,   116,   117,   121,   133,   146,   161,   164,
     176,   179,   189,   190,   198,   208,   212,   219,   231,   245,
     255,   265,   273,   279,   283,   284,   285,   289,   293,   295,
     303,   310,   316,   319,   328,   333,   336,   343,   346,   352,
     357,   362,   367,   372,   377,   382,   387,   392,   397,   402,
     407,   412,   416,   420,   424,   426,   428,   430,   432,   433
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "BLANKID",
  "ASSIGN", "STAR", "DIV", "MINUS", "PLUS", "EQ", "GE", "GT", "LBRACE",
  "LE", "LPAR", "LSQ", "LT", "MOD", "NE", "NOT", "AND", "OR", "RBRACE",
  "RPAR", "RSQ", "PACKAGE", "RETURN", "ELSE", "FOR", "IF", "VAR", "INT",
  "FLOAT32", "BOOL", "STRING", "PRINT", "PARSEINT", "FUNC", "CMDARGS",
  "RESERVED", "IDENTIFIER", "NATURAL", "DECIMAL", "STRLIT", "PLUS_SOZINHO",
  "MINUS_SOZINHO", "$accept", "program", "declarations", "vardeclaration",
  "varspec", "varspec2", "type", "funcdeclaration", "parameters",
  "parameters2", "funcbody", "varsandstatements", "statement",
  "statement2", "parseargs", "funcinvocation", "funcinvocation2", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    51,    51,    52,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    57,
      57,    58,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     3,     0,     2,     5,     3,     3,
       0,     1,     1,     1,     1,     7,     6,     3,     0,     4,
       0,     3,     2,     3,     3,     0,     3,     3,     9,     5,
       5,     4,     2,     1,     1,     1,     4,     4,     1,     3,
       0,    11,     8,     5,     3,     4,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     1,     1,     1,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     2,     0,     0,     0,
       0,     0,    10,     6,     0,     3,     4,     0,     0,    18,
       0,     0,    11,    12,    13,    14,     8,     0,     0,     7,
       9,    20,     0,    17,    25,     0,    16,     0,     0,    15,
       0,    38,    22,    40,    21,    33,     0,     0,     0,     0,
       0,     0,    35,    34,    19,     0,     0,     0,     0,     0,
      66,    64,    65,    67,    32,    40,     0,     0,     0,     0,
       0,     0,    23,    24,    27,     0,    62,    63,     0,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    40,     0,     0,     0,
      26,     0,    44,    47,    39,    69,    68,    58,    59,    57,
      56,    52,    55,    51,    54,    50,    60,    53,    49,    48,
      31,     0,     0,    37,    36,     0,    45,     0,    30,    29,
       0,     0,    43,     0,     0,    46,    40,     0,     0,     0,
      42,     0,    28,     0,     0,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     6,     9,    13,    18,    26,    10,    28,    33,
      36,    38,    75,    55,    52,    63,   127,    64
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const yytype_int16 yypact[] =
{
     -20,   -34,    24,    25,   -63,   -63,   -23,   -12,   -13,    29,
      32,    13,   -63,   -63,    43,   -63,   -63,    59,    46,    23,
      41,    26,   -63,   -63,   -63,   -63,   -63,   182,    45,   -63,
     -63,   -63,   177,    67,   -63,    62,   -63,    36,    74,   -63,
     182,   -63,   -63,   -63,   -63,   198,   188,   198,    69,    47,
      84,    86,   -63,   -63,   -63,    96,   198,   198,    51,   198,
      83,   -63,   -63,   -63,   328,   -63,   294,   311,   141,    95,
     198,    48,   -63,   -63,   -63,   106,   -63,   -63,    78,   256,
     -63,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   111,   -63,   -63,    88,   275,   108,
     328,    90,   -63,   328,   -63,   -63,   -63,   -63,   -63,   100,
     100,    12,    12,    12,    12,    12,   -63,    12,   361,   345,
     -63,   130,   145,   -63,   -63,    79,   -63,     2,   -63,    89,
     105,   198,   -63,   109,    14,   328,   -63,    97,   112,   164,
     -63,   198,   -63,   236,   103,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,    92,   121,   -63,   -22,   -63,   -63,   -63,
      99,   -63,    98,   -62,   -63,   -38,   -63,   -45
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      53,    66,    67,    94,    11,    31,   131,     1,     3,     7,
      35,    76,    77,    79,    80,   137,     8,    53,    54,    81,
      82,    83,    84,    98,     4,   100,   103,   132,     5,    14,
      12,    90,    15,   121,   122,    16,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   101,
      21,    69,    78,    70,   138,    12,    53,    56,    57,    19,
      56,    57,    20,    71,    58,    27,    29,    58,    30,    59,
      32,    37,    59,   102,   139,    41,    34,    42,    40,    22,
      23,    24,    25,    53,    53,    68,   135,    72,    43,    73,
      60,    61,    62,    60,    61,    62,   143,    41,    44,    71,
      99,    53,    45,   105,    46,    47,     7,    81,    82,   104,
      43,    48,    41,   123,   125,   126,    49,   130,   133,    90,
      74,   134,   140,   136,    45,    43,    46,    47,   145,   141,
      50,    41,    17,    48,    39,   120,    51,     0,    49,    45,
       0,    46,    47,     0,    43,     0,    41,     0,    48,     0,
      56,    57,     0,    49,   128,     0,     0,    58,    45,    43,
      46,    47,    59,     0,     0,    41,     0,    48,     0,   129,
       0,     0,    49,    45,     0,    46,    47,     0,    43,     0,
       0,     0,    48,    60,    61,    62,    97,    49,   142,     0,
       0,    34,    45,     0,    46,    47,     0,    56,    57,     0,
       0,    48,    65,     0,    58,     0,    49,    56,    57,    59,
      22,    23,    24,    25,    58,    22,    23,    24,    25,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    81,    82,    83,    84,    85,    86,    87,
       0,    88,     0,     0,    89,    90,    91,     0,    92,    93,
       0,     0,   144,    81,    82,    83,    84,    85,    86,    87,
       0,    88,     0,     0,    89,    90,    91,     0,    92,    93,
       0,   106,    81,    82,    83,    84,    85,    86,    87,     0,
      88,     0,     0,    89,    90,    91,     0,    92,    93,     0,
     124,    81,    82,    83,    84,    85,    86,    87,    95,    88,
       0,     0,    89,    90,    91,     0,    92,    93,    81,    82,
      83,    84,    85,    86,    87,    96,    88,     0,     0,    89,
      90,    91,     0,    92,    93,    81,    82,    83,    84,    85,
      86,    87,     0,    88,     0,     0,    89,    90,    91,     0,
      92,    93,    81,    82,    83,    84,    85,    86,    87,     0,
      88,     0,     0,    89,    90,    91,     0,    92,    81,    82,
      83,    84,    85,    86,    87,     0,    88,     0,     0,    89,
      90,    91
};

static const yytype_int16 yycheck[] =
{
      38,    46,    47,    65,    16,    27,     4,    27,    42,    32,
      32,    56,    57,    58,    59,     1,    39,    55,    40,     7,
       8,     9,    10,    68,     0,    70,    71,    25,     3,    42,
      42,    19,     3,    95,    96,     3,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,     1,
       4,     4,     1,     6,    40,    42,    94,     9,    10,    16,
       9,    10,     3,    16,    16,    42,    25,    16,    42,    21,
      25,     4,    21,    25,   136,     1,    14,     3,    42,    33,
      34,    35,    36,   121,   122,    16,   131,     3,    14,     3,
      42,    43,    44,    42,    43,    44,   141,     1,    24,    16,
       5,   139,    28,    25,    30,    31,    32,     7,     8,     3,
      14,    37,     1,    25,     6,    25,    42,    38,    29,    19,
      24,    16,    25,    14,    28,    14,    30,    31,    25,    17,
      38,     1,    11,    37,    35,    24,    38,    -1,    42,    28,
      -1,    30,    31,    -1,    14,    -1,     1,    -1,    37,    -1,
       9,    10,    -1,    42,    24,    -1,    -1,    16,    28,    14,
      30,    31,    21,    -1,    -1,     1,    -1,    37,    -1,    24,
      -1,    -1,    42,    28,    -1,    30,    31,    -1,    14,    -1,
      -1,    -1,    37,    42,    43,    44,    45,    42,    24,    -1,
      -1,    14,    28,    -1,    30,    31,    -1,     9,    10,    -1,
      -1,    37,    14,    -1,    16,    -1,    42,     9,    10,    21,
      33,    34,    35,    36,    16,    33,    34,    35,    36,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    26,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    25,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    -1,    18,    19,    20,    -1,    22,    23,    -1,
      25,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    20,    -1,    22,    23,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    18,
      19,    20,    -1,    22,    23,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    -1,    18,    19,    20,    -1,
      22,    23,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    -1,    18,    19,    20,    -1,    22,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    -1,    18,
      19,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    49,    42,     0,     3,    50,    32,    39,    51,
      55,    16,    42,    52,    42,     3,     3,    52,    53,    16,
       3,     4,    33,    34,    35,    36,    54,    42,    56,    25,
      42,    54,    25,    57,    14,    54,    58,     4,    59,    58,
      42,     1,     3,    14,    24,    28,    30,    31,    37,    42,
      51,    60,    62,    63,    54,    61,     9,    10,    16,    21,
      42,    43,    44,    63,    65,    14,    65,    65,    16,     4,
       6,    16,     3,     3,    24,    60,    65,    65,     1,    65,
      65,     7,     8,     9,    10,    11,    12,    13,    15,    18,
      19,    20,    22,    23,    61,    14,    14,    45,    65,     5,
      65,     1,    25,    65,     3,    25,    25,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      24,    61,    61,    25,    25,     6,    25,    64,    24,    24,
      38,     4,    25,    29,    16,    65,    14,     1,    40,    61,
      25,    17,    24,    65,    26,    25
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 50 "gocompiler.y"
    {   
                                                                    (yyval.node)=program=newnode(Program,NULL);
                                                                    if((yyvsp[(4) - (4)].node)!=NULL){addchild((yyval.node),(yyvsp[(4) - (4)].node));}
                                                                }
    break;

  case 3:
#line 57 "gocompiler.y"
    { 
                                                                    if ((yyvsp[(1) - (3)].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[(1) - (3)].node);
                                                                    }
                                                                    struct node* vardeclaration = newnode(aux,NULL);
                                                                    addchild(vardeclaration,(yyvsp[(2) - (3)].node));
                                                                    addchild((yyval.node),vardeclaration);
                                                                }
    break;

  case 4:
#line 67 "gocompiler.y"
    {                      
                                                                    if ((yyvsp[(1) - (3)].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[(1) - (3)].node);
                                                                    }
                                                                    if ((yyvsp[(2) - (3)].node) != NULL) {
                                                                        addchild((yyval.node), (yyvsp[(2) - (3)].node));
                                                                    }
                                                                }
    break;

  case 5:
#line 77 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 6:
#line 81 "gocompiler.y"
    {(yyval.node)=(yyvsp[(2) - (2)].node);}
    break;

  case 7:
#line 82 "gocompiler.y"
    {(yyval.node)=(yyvsp[(3) - (5)].node);}
    break;

  case 8:
#line 85 "gocompiler.y"
    {
                                                                    (yyval.node)=newnode(aux,NULL);
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl,(yyvsp[(3) - (3)].node));
                                                                    addchild(vardecl,newnode(Identifier,(yyvsp[(1) - (3)].lexeme)));
                                                                    addchild((yyval.node),vardecl);
                                                                    if((yyvsp[(2) - (3)].node)!=NULL){
                                                                        addchild((yyval.node),(yyvsp[(2) - (3)].node));
                                                                        addType((yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));
                                                                    }
                                                                    LOCATE(getchild(vardecl, 1), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column); 
                                                                }
    break;

  case 9:
#line 99 "gocompiler.y"
    {   
                                                                    if ((yyvsp[(1) - (3)].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[(1) - (3)].node);
                                                                    }
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl, newnode(Identifier, (yyvsp[(3) - (3)].lexeme)));
                                                                    addchild((yyval.node),vardecl);
                                                                    LOCATE(getchild(vardecl, 0), (yylsp[(3) - (3)]).first_line, (yylsp[(3) - (3)]).first_column);

                                                                }
    break;

  case 10:
#line 111 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 11:
#line 114 "gocompiler.y"
    {(yyval.node)=newnode(Int,NULL);;}
    break;

  case 12:
#line 115 "gocompiler.y"
    {(yyval.node)=newnode(Float32,NULL);}
    break;

  case 13:
#line 116 "gocompiler.y"
    {(yyval.node)=newnode(Bool,NULL);}
    break;

  case 14:
#line 117 "gocompiler.y"
    {(yyval.node)=newnode(String,NULL);}
    break;

  case 15:
#line 121 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,(yyvsp[(2) - (7)].lexeme)));
                                                                                    addchild(funcHeader,(yyvsp[(6) - (7)].node));
                                                                                    addchild(funcHeader,(yyvsp[(4) - (7)].node));

                                                                                    addchild((yyval.node),funcHeader);
                                                                                    addchild((yyval.node),(yyvsp[(7) - (7)].node));
                                                                                    LOCATE(getchild(funcHeader, 0), (yylsp[(2) - (7)]).first_line, (yylsp[(2) - (7)]).first_column);
                                                                                }
    break;

  case 16:
#line 133 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,(yyvsp[(2) - (6)].lexeme)));
                                                                                    addchild(funcHeader,(yyvsp[(4) - (6)].node));

                                                                                    addchild((yyval.node),funcHeader);
                                                                                    addchild((yyval.node),(yyvsp[(6) - (6)].node));
                                                                                    LOCATE(getchild(funcHeader, 0), (yylsp[(2) - (6)]).first_line, (yylsp[(2) - (6)]).first_column);
                                                                                }
    break;

  case 17:
#line 146 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(FuncParams,NULL);

                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,(yyvsp[(2) - (3)].node));
                                                                                    addchild(paramDecl,newnode(Identifier,(yyvsp[(1) - (3)].lexeme)));

                                                                                    addchild((yyval.node),paramDecl);

                                                                                    if((yyvsp[(3) - (3)].node)!=NULL){
                                                                                        addchild((yyval.node),(yyvsp[(3) - (3)].node));
                                                                                    }
                                                                                    LOCATE(getchild(paramDecl, 1), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column);
                                                                                }
    break;

  case 18:
#line 161 "gocompiler.y"
    {(yyval.node)=newnode(FuncParams,NULL);}
    break;

  case 19:
#line 164 "gocompiler.y"
    {
                                                                                    if ((yyvsp[(1) - (4)].node) == NULL) {
                                                                                        (yyval.node) = newnode(aux, NULL);
                                                                                    } else {
                                                                                        (yyval.node) = (yyvsp[(1) - (4)].node);
                                                                                    }
                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,(yyvsp[(4) - (4)].node));
                                                                                    addchild(paramDecl,newnode(Identifier,(yyvsp[(3) - (4)].lexeme)));
                                                                                    addchild((yyval.node),paramDecl);
                                                                                    LOCATE(getchild(paramDecl, 1), (yylsp[(3) - (4)]).first_line, (yylsp[(3) - (4)]).first_column);
                                                                                }
    break;

  case 20:
#line 176 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 21:
#line 179 "gocompiler.y"
    {
                                                                                    if((yyvsp[(2) - (3)].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[(2) - (3)].node);
                                                                                    }
                                                                                }
    break;

  case 22:
#line 189 "gocompiler.y"
    {(yyval.node)=(yyvsp[(1) - (2)].node);}
    break;

  case 23:
#line 190 "gocompiler.y"
    {
                                                                                    if((yyvsp[(1) - (3)].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[(1) - (3)].node);
                                                                                    }
                                                                                    addchild((yyval.node),(yyvsp[(2) - (3)].node));
                                                                                }
    break;

  case 24:
#line 198 "gocompiler.y"
    {
                                                                                    if((yyvsp[(1) - (3)].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[(1) - (3)].node);
                                                                                    }
                                                                                    if((yyvsp[(2) - (3)].node)!=NULL){
                                                                                        addchild((yyval.node),(yyvsp[(2) - (3)].node));
                                                                                    }
                                                                                }
    break;

  case 25:
#line 208 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 26:
#line 212 "gocompiler.y"
    {   
                                                                                    (yyval.node)=newnode(Assign,NULL);
                                                                                    addchild((yyval.node),newnode(Identifier,(yyvsp[(1) - (3)].lexeme)));
                                                                                    addchild((yyval.node),(yyvsp[(3) - (3)].node));
                                                                                    LOCATE(getchild((yyval.node), 0), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column);
                                                                                    LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                }
    break;

  case 27:
#line 219 "gocompiler.y"
    {
                                                                                    if((yyvsp[(2) - (3)].node)!=NULL){
                                                                                        if (countblocks((yyvsp[(2) - (3)].node)) > 1){
                                                                                            (yyval.node)=newnode(Block,NULL);
                                                                                            addchild((yyval.node),(yyvsp[(2) - (3)].node));
                                                                                        }else{
                                                                                            (yyval.node)=(yyvsp[(2) - (3)].node);
                                                                                        }
                                                                                    }else{
                                                                                        (yyval.node)=NULL;
                                                                                    }
                                                                                }
    break;

  case 28:
#line 231 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(If,NULL);
                                                                                    addchild((yyval.node),(yyvsp[(2) - (9)].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[(4) - (9)].node)!=NULL){
                                                                                        addchild(block,(yyvsp[(4) - (9)].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                    struct node *block2 = newnode(Block, NULL);
                                                                                    if((yyvsp[(8) - (9)].node)!=NULL){
                                                                                        addchild(block2,(yyvsp[(8) - (9)].node));
                                                                                    }
                                                                                    addchild((yyval.node),block2);
                                                                                }
    break;

  case 29:
#line 245 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(If,NULL);
                                                                                    addchild((yyval.node),(yyvsp[(2) - (5)].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[(4) - (5)].node)!=NULL){
                                                                                        addchild(block,(yyvsp[(4) - (5)].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                    addchild((yyval.node),newnode(Block,NULL));
                                                                                }
    break;

  case 30:
#line 255 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(For,NULL);
                                                                                    addchild((yyval.node),(yyvsp[(2) - (5)].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[(4) - (5)].node)!=NULL){
                                                                                        addchild(block,(yyvsp[(4) - (5)].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                }
    break;

  case 31:
#line 265 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(For,NULL);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[(3) - (4)].node)!=NULL){
                                                                                        addchild(block,(yyvsp[(3) - (4)].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                }
    break;

  case 32:
#line 273 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(Return,NULL);
                                                                                    addchild((yyval.node),(yyvsp[(2) - (2)].node));
                                                                                    LOCATE((yyval.node), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column);
                                                                                }
    break;

  case 33:
#line 279 "gocompiler.y"
    {   (yyval.node)=newnode(Return,NULL);
                                                                                    LOCATE((yyval.node), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column);
                                                                                }
    break;

  case 34:
#line 283 "gocompiler.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 35:
#line 284 "gocompiler.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 36:
#line 285 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(Print,NULL);
                                                                                    addchild((yyval.node),(yyvsp[(3) - (4)].node));
                                                                                }
    break;

  case 37:
#line 289 "gocompiler.y"
    {
                                                                                    (yyval.node)=newnode(Print,NULL);
                                                                                    addchild((yyval.node),newnode(StrLit,(yyvsp[(3) - (4)].lexeme)));
                                                                                }
    break;

  case 38:
#line 293 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 39:
#line 295 "gocompiler.y"
    {
                                                                                    if ((yyvsp[(1) - (3)].node) == NULL) {
                                                                                        (yyval.node) = newnode(aux, NULL); 
                                                                                    } else {
                                                                                        (yyval.node) = (yyvsp[(1) - (3)].node); 
                                                                                    }
                                                                                    if((yyvsp[(2) - (3)].node)!=NULL){addchild((yyval.node), (yyvsp[(2) - (3)].node));} 
                                                                                }
    break;

  case 40:
#line 303 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 41:
#line 310 "gocompiler.y"
    {
                                                                                            (yyval.node)=newnode(ParseArgs,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[(1) - (11)].lexeme)));
                                                                                            addchild((yyval.node),(yyvsp[(9) - (11)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(5) - (11)]).first_line, (yylsp[(5) - (11)]).first_column);
                                                                                        }
    break;

  case 42:
#line 316 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 43:
#line 319 "gocompiler.y"
    {
                                                                                            (yyval.node)=newnode(Call,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[(1) - (5)].lexeme)));
                                                                                            addchild((yyval.node),(yyvsp[(3) - (5)].node));
                                                                                            if((yyvsp[(4) - (5)].node)!=NULL){
                                                                                                addchild((yyval.node),(yyvsp[(4) - (5)].node));
                                                                                            }
                                                                                            LOCATE(getchild((yyval.node), 0), (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column);
                                                                                        }
    break;

  case 44:
#line 328 "gocompiler.y"
    {
                                                                                            (yyval.node)=newnode(Call,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[(1) - (3)].lexeme)));
                                                                                            LOCATE(getchild((yyval.node), 0), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column);
                                                                                        }
    break;

  case 45:
#line 333 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 46:
#line 336 "gocompiler.y"
    {
                                                                                            if ((yyvsp[(1) - (3)].node) == NULL) {
                                                                                                (yyval.node) = newnode(aux, NULL); 
                                                                                            } else {
                                                                                                (yyval.node) = (yyvsp[(1) - (3)].node); 
                                                                                            }addchild((yyval.node), (yyvsp[(3) - (3)].node));                                                     
                                                                                        }
    break;

  case 47:
#line 343 "gocompiler.y"
    {(yyval.node)=NULL;}
    break;

  case 48:
#line 346 "gocompiler.y"
    {
                                                                                            (yyval.node)=newnode(Or,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 49:
#line 352 "gocompiler.y"
    {    (yyval.node)=newnode(And,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 50:
#line 357 "gocompiler.y"
    {   (yyval.node)=newnode(Lt,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 51:
#line 362 "gocompiler.y"
    {   (yyval.node)=newnode(Gt,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 52:
#line 367 "gocompiler.y"
    {   (yyval.node)=newnode(Eq,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 53:
#line 372 "gocompiler.y"
    {   (yyval.node)=newnode(Ne,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 54:
#line 377 "gocompiler.y"
    {   (yyval.node)=newnode(Le,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 55:
#line 382 "gocompiler.y"
    {   (yyval.node)=newnode(Ge,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 56:
#line 387 "gocompiler.y"
    {   (yyval.node)=newnode(Add,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 57:
#line 392 "gocompiler.y"
    {   (yyval.node)=newnode(Sub,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 58:
#line 397 "gocompiler.y"
    {   (yyval.node)=newnode(Mul,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 59:
#line 402 "gocompiler.y"
    {   (yyval.node)=newnode(Div,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 60:
#line 407 "gocompiler.y"
    {   (yyval.node)=newnode(Mod,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                            addchild((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column);
                                                                                        }
    break;

  case 61:
#line 412 "gocompiler.y"
    {   (yyval.node)=newnode(Not,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column);
                                                                                        }
    break;

  case 62:
#line 416 "gocompiler.y"
    {   (yyval.node)=newnode(Minus,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column);
                                                                                        }
    break;

  case 63:
#line 420 "gocompiler.y"
    {   (yyval.node)=newnode(Plus,NULL);
                                                                                            addchild((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column);
                                                                                        }
    break;

  case 64:
#line 424 "gocompiler.y"
    {(yyval.node) = newnode(Natural, (yyvsp[(1) - (1)].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column);}
    break;

  case 65:
#line 426 "gocompiler.y"
    {(yyval.node) = newnode(Decimal, (yyvsp[(1) - (1)].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column);}
    break;

  case 66:
#line 428 "gocompiler.y"
    {(yyval.node) = newnode(Identifier, (yyvsp[(1) - (1)].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column);}
    break;

  case 67:
#line 430 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);
                                                                                            LOCATE((yyval.node), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column);}
    break;

  case 68:
#line 432 "gocompiler.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 69:
#line 433 "gocompiler.y"
    {(yyval.node) = NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 2238 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 439 "gocompiler.y"


/* START subroutines section */

// all needed functions are collected in the .l and ast.* files
