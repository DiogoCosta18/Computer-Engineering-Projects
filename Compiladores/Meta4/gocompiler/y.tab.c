/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "gocompiler.y"

#include "ast.h"

int yylex(void);
void yyerror(char *);


struct node *program;
//int yydebug=1;



#line 84 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    COMMA = 259,                   /* COMMA  */
    BLANKID = 260,                 /* BLANKID  */
    ASSIGN = 261,                  /* ASSIGN  */
    STAR = 262,                    /* STAR  */
    DIV = 263,                     /* DIV  */
    MINUS = 264,                   /* MINUS  */
    PLUS = 265,                    /* PLUS  */
    EQ = 266,                      /* EQ  */
    GE = 267,                      /* GE  */
    GT = 268,                      /* GT  */
    LBRACE = 269,                  /* LBRACE  */
    LE = 270,                      /* LE  */
    LPAR = 271,                    /* LPAR  */
    LSQ = 272,                     /* LSQ  */
    LT = 273,                      /* LT  */
    MOD = 274,                     /* MOD  */
    NE = 275,                      /* NE  */
    NOT = 276,                     /* NOT  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    RBRACE = 279,                  /* RBRACE  */
    RPAR = 280,                    /* RPAR  */
    RSQ = 281,                     /* RSQ  */
    PACKAGE = 282,                 /* PACKAGE  */
    RETURN = 283,                  /* RETURN  */
    ELSE = 284,                    /* ELSE  */
    FOR = 285,                     /* FOR  */
    IF = 286,                      /* IF  */
    VAR = 287,                     /* VAR  */
    INT = 288,                     /* INT  */
    FLOAT32 = 289,                 /* FLOAT32  */
    BOOL = 290,                    /* BOOL  */
    STRING = 291,                  /* STRING  */
    PRINT = 292,                   /* PRINT  */
    PARSEINT = 293,                /* PARSEINT  */
    FUNC = 294,                    /* FUNC  */
    CMDARGS = 295,                 /* CMDARGS  */
    RESERVED = 296,                /* RESERVED  */
    IDENTIFIER = 297,              /* IDENTIFIER  */
    NATURAL = 298,                 /* NATURAL  */
    DECIMAL = 299,                 /* DECIMAL  */
    STRLIT = 300,                  /* STRLIT  */
    MINUS_SOZINHO = 301,           /* MINUS_SOZINHO  */
    PLUS_SOZINHO = 302             /* PLUS_SOZINHO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
#define MINUS_SOZINHO 301
#define PLUS_SOZINHO 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 36 "gocompiler.y"

    char *lexeme;
    struct node *node;

#line 236 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_BLANKID = 5,                    /* BLANKID  */
  YYSYMBOL_ASSIGN = 6,                     /* ASSIGN  */
  YYSYMBOL_STAR = 7,                       /* STAR  */
  YYSYMBOL_DIV = 8,                        /* DIV  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_LPAR = 16,                      /* LPAR  */
  YYSYMBOL_LSQ = 17,                       /* LSQ  */
  YYSYMBOL_LT = 18,                        /* LT  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_RPAR = 25,                      /* RPAR  */
  YYSYMBOL_RSQ = 26,                       /* RSQ  */
  YYSYMBOL_PACKAGE = 27,                   /* PACKAGE  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_VAR = 32,                       /* VAR  */
  YYSYMBOL_INT = 33,                       /* INT  */
  YYSYMBOL_FLOAT32 = 34,                   /* FLOAT32  */
  YYSYMBOL_BOOL = 35,                      /* BOOL  */
  YYSYMBOL_STRING = 36,                    /* STRING  */
  YYSYMBOL_PRINT = 37,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 38,                  /* PARSEINT  */
  YYSYMBOL_FUNC = 39,                      /* FUNC  */
  YYSYMBOL_CMDARGS = 40,                   /* CMDARGS  */
  YYSYMBOL_RESERVED = 41,                  /* RESERVED  */
  YYSYMBOL_IDENTIFIER = 42,                /* IDENTIFIER  */
  YYSYMBOL_NATURAL = 43,                   /* NATURAL  */
  YYSYMBOL_DECIMAL = 44,                   /* DECIMAL  */
  YYSYMBOL_STRLIT = 45,                    /* STRLIT  */
  YYSYMBOL_MINUS_SOZINHO = 46,             /* MINUS_SOZINHO  */
  YYSYMBOL_PLUS_SOZINHO = 47,              /* PLUS_SOZINHO  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_declarations = 50,              /* declarations  */
  YYSYMBOL_vardeclaration = 51,            /* vardeclaration  */
  YYSYMBOL_varspec = 52,                   /* varspec  */
  YYSYMBOL_varspec2 = 53,                  /* varspec2  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_funcdeclaration = 55,           /* funcdeclaration  */
  YYSYMBOL_parameters = 56,                /* parameters  */
  YYSYMBOL_parameters2 = 57,               /* parameters2  */
  YYSYMBOL_funcbody = 58,                  /* funcbody  */
  YYSYMBOL_varsandstatements = 59,         /* varsandstatements  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_statement2 = 61,                /* statement2  */
  YYSYMBOL_parseargs = 62,                 /* parseargs  */
  YYSYMBOL_funcinvocation = 63,            /* funcinvocation  */
  YYSYMBOL_funcinvocation2 = 64,           /* funcinvocation2  */
  YYSYMBOL_expr = 65                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 42 "gocompiler.y"

#define LOCATE(node, line, column) { node->token_line = line; node->token_column = column; }

#line 345 "y.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "COMMA",
  "BLANKID", "ASSIGN", "STAR", "DIV", "MINUS", "PLUS", "EQ", "GE", "GT",
  "LBRACE", "LE", "LPAR", "LSQ", "LT", "MOD", "NE", "NOT", "AND", "OR",
  "RBRACE", "RPAR", "RSQ", "PACKAGE", "RETURN", "ELSE", "FOR", "IF", "VAR",
  "INT", "FLOAT32", "BOOL", "STRING", "PRINT", "PARSEINT", "FUNC",
  "CMDARGS", "RESERVED", "IDENTIFIER", "NATURAL", "DECIMAL", "STRLIT",
  "MINUS_SOZINHO", "PLUS_SOZINHO", "$accept", "program", "declarations",
  "vardeclaration", "varspec", "varspec2", "type", "funcdeclaration",
  "parameters", "parameters2", "funcbody", "varsandstatements",
  "statement", "statement2", "parseargs", "funcinvocation",
  "funcinvocation2", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,    92,   121,   -63,   -22,   -63,   -63,   -63,
      99,   -63,    98,   -62,   -63,   -38,   -63,   -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     9,    13,    18,    26,    10,    28,    33,
      36,    38,    75,    55,    52,    63,   127,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    51,    51,    52,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    57,
      57,    58,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     3,     0,     2,     5,     3,     3,
       0,     1,     1,     1,     1,     7,     6,     3,     0,     4,
       0,     3,     2,     3,     3,     0,     3,     3,     9,     5,
       5,     4,     2,     1,     1,     1,     4,     4,     1,     3,
       0,    11,     8,     5,     3,     4,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     1,     1,     1,     1,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PACKAGE IDENTIFIER SEMICOLON declarations  */
#line 50 "gocompiler.y"
                                                                {   
                                                                    (yyval.node)=program=newnode(Program,NULL);
                                                                    if((yyvsp[0].node)!=NULL){addchild((yyval.node),(yyvsp[0].node));}
                                                                }
#line 1557 "y.tab.c"
    break;

  case 3: /* declarations: declarations vardeclaration SEMICOLON  */
#line 57 "gocompiler.y"
                                                                { 
                                                                    if ((yyvsp[-2].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[-2].node);
                                                                    }
                                                                    struct node* vardeclaration = newnode(aux,NULL);
                                                                    addchild(vardeclaration,(yyvsp[-1].node));
                                                                    addchild((yyval.node),vardeclaration);
                                                                }
#line 1572 "y.tab.c"
    break;

  case 4: /* declarations: declarations funcdeclaration SEMICOLON  */
#line 67 "gocompiler.y"
                                                                {                      
                                                                    if ((yyvsp[-2].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[-2].node);
                                                                    }
                                                                    if ((yyvsp[-1].node) != NULL) {
                                                                        addchild((yyval.node), (yyvsp[-1].node));
                                                                    }
                                                                }
#line 1587 "y.tab.c"
    break;

  case 5: /* declarations: %empty  */
#line 77 "gocompiler.y"
                                                                {(yyval.node)=NULL;}
#line 1593 "y.tab.c"
    break;

  case 6: /* vardeclaration: VAR varspec  */
#line 81 "gocompiler.y"
                                                                {(yyval.node)=(yyvsp[0].node);}
#line 1599 "y.tab.c"
    break;

  case 7: /* vardeclaration: VAR LPAR varspec SEMICOLON RPAR  */
#line 82 "gocompiler.y"
                                                                {(yyval.node)=(yyvsp[-2].node);}
#line 1605 "y.tab.c"
    break;

  case 8: /* varspec: IDENTIFIER varspec2 type  */
#line 85 "gocompiler.y"
                                                                {
                                                                    (yyval.node)=newnode(aux,NULL);
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl,(yyvsp[0].node));
                                                                    addchild(vardecl,newnode(Identifier,(yyvsp[-2].lexeme)));
                                                                    addchild((yyval.node),vardecl);
                                                                    if((yyvsp[-1].node)!=NULL){
                                                                        addchild((yyval.node),(yyvsp[-1].node));
                                                                        addType((yyvsp[-1].node),(yyvsp[0].node));
                                                                    }
                                                                    LOCATE(getchild(vardecl, 1), (yylsp[-2]).first_line, (yylsp[-2]).first_column); 
                                                                }
#line 1622 "y.tab.c"
    break;

  case 9: /* varspec2: varspec2 COMMA IDENTIFIER  */
#line 99 "gocompiler.y"
                                                                {   
                                                                    if ((yyvsp[-2].node) == NULL) {
                                                                        (yyval.node) = newnode(aux, NULL);
                                                                    } else {
                                                                        (yyval.node) = (yyvsp[-2].node);
                                                                    }
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl, newnode(Identifier, (yyvsp[0].lexeme)));
                                                                    addchild((yyval.node),vardecl);
                                                                    LOCATE(getchild(vardecl, 0), (yylsp[0]).first_line, (yylsp[0]).first_column);

                                                                }
#line 1639 "y.tab.c"
    break;

  case 10: /* varspec2: %empty  */
#line 111 "gocompiler.y"
                                                                {(yyval.node)=NULL;}
#line 1645 "y.tab.c"
    break;

  case 11: /* type: INT  */
#line 114 "gocompiler.y"
                                                                {(yyval.node)=newnode(Int,NULL);;}
#line 1651 "y.tab.c"
    break;

  case 12: /* type: FLOAT32  */
#line 115 "gocompiler.y"
                                                                {(yyval.node)=newnode(Float32,NULL);}
#line 1657 "y.tab.c"
    break;

  case 13: /* type: BOOL  */
#line 116 "gocompiler.y"
                                                                {(yyval.node)=newnode(Bool,NULL);}
#line 1663 "y.tab.c"
    break;

  case 14: /* type: STRING  */
#line 117 "gocompiler.y"
                                                                {(yyval.node)=newnode(String,NULL);}
#line 1669 "y.tab.c"
    break;

  case 15: /* funcdeclaration: FUNC IDENTIFIER LPAR parameters RPAR type funcbody  */
#line 121 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,(yyvsp[-5].lexeme)));
                                                                                    addchild(funcHeader,(yyvsp[-1].node));
                                                                                    addchild(funcHeader,(yyvsp[-3].node));

                                                                                    addchild((yyval.node),funcHeader);
                                                                                    addchild((yyval.node),(yyvsp[0].node));
                                                                                    LOCATE(getchild(funcHeader, 0), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
                                                                                }
#line 1686 "y.tab.c"
    break;

  case 16: /* funcdeclaration: FUNC IDENTIFIER LPAR parameters RPAR funcbody  */
#line 133 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,(yyvsp[-4].lexeme)));
                                                                                    addchild(funcHeader,(yyvsp[-2].node));

                                                                                    addchild((yyval.node),funcHeader);
                                                                                    addchild((yyval.node),(yyvsp[0].node));
                                                                                    LOCATE(getchild(funcHeader, 0), (yylsp[-4]).first_line, (yylsp[-4]).first_column);
                                                                                }
#line 1702 "y.tab.c"
    break;

  case 17: /* parameters: IDENTIFIER type parameters2  */
#line 146 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(FuncParams,NULL);

                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,(yyvsp[-1].node));
                                                                                    addchild(paramDecl,newnode(Identifier,(yyvsp[-2].lexeme)));

                                                                                    addchild((yyval.node),paramDecl);

                                                                                    if((yyvsp[0].node)!=NULL){
                                                                                        addchild((yyval.node),(yyvsp[0].node));
                                                                                    }
                                                                                    LOCATE(getchild(paramDecl, 1), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
                                                                                }
#line 1721 "y.tab.c"
    break;

  case 18: /* parameters: %empty  */
#line 161 "gocompiler.y"
                                                                                {(yyval.node)=newnode(FuncParams,NULL);}
#line 1727 "y.tab.c"
    break;

  case 19: /* parameters2: parameters2 COMMA IDENTIFIER type  */
#line 164 "gocompiler.y"
                                                                                {
                                                                                    if ((yyvsp[-3].node) == NULL) {
                                                                                        (yyval.node) = newnode(aux, NULL);
                                                                                    } else {
                                                                                        (yyval.node) = (yyvsp[-3].node);
                                                                                    }
                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,(yyvsp[0].node));
                                                                                    addchild(paramDecl,newnode(Identifier,(yyvsp[-1].lexeme)));
                                                                                    addchild((yyval.node),paramDecl);
                                                                                    LOCATE(getchild(paramDecl, 1), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                }
#line 1744 "y.tab.c"
    break;

  case 20: /* parameters2: %empty  */
#line 176 "gocompiler.y"
                                                                                {(yyval.node)=NULL;}
#line 1750 "y.tab.c"
    break;

  case 21: /* funcbody: LBRACE varsandstatements RBRACE  */
#line 179 "gocompiler.y"
                                                                                {
                                                                                    if((yyvsp[-1].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[-1].node);
                                                                                    }
                                                                                }
#line 1762 "y.tab.c"
    break;

  case 22: /* varsandstatements: varsandstatements SEMICOLON  */
#line 189 "gocompiler.y"
                                                                                {(yyval.node)=(yyvsp[-1].node);}
#line 1768 "y.tab.c"
    break;

  case 23: /* varsandstatements: varsandstatements vardeclaration SEMICOLON  */
#line 190 "gocompiler.y"
                                                                                {
                                                                                    if((yyvsp[-2].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[-2].node);
                                                                                    }
                                                                                    addchild((yyval.node),(yyvsp[-1].node));
                                                                                }
#line 1781 "y.tab.c"
    break;

  case 24: /* varsandstatements: varsandstatements statement SEMICOLON  */
#line 198 "gocompiler.y"
                                                                                {
                                                                                    if((yyvsp[-2].node)==NULL){
                                                                                        (yyval.node)=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        (yyval.node)=(yyvsp[-2].node);
                                                                                    }
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        addchild((yyval.node),(yyvsp[-1].node));
                                                                                    }
                                                                                }
#line 1796 "y.tab.c"
    break;

  case 25: /* varsandstatements: %empty  */
#line 208 "gocompiler.y"
                                                                                {(yyval.node)=NULL;}
#line 1802 "y.tab.c"
    break;

  case 26: /* statement: IDENTIFIER ASSIGN expr  */
#line 212 "gocompiler.y"
                                                                                {   
                                                                                    (yyval.node)=newnode(Assign,NULL);
                                                                                    addchild((yyval.node),newnode(Identifier,(yyvsp[-2].lexeme)));
                                                                                    addchild((yyval.node),(yyvsp[0].node));
                                                                                    LOCATE(getchild((yyval.node), 0), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
                                                                                    LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                }
#line 1814 "y.tab.c"
    break;

  case 27: /* statement: LBRACE statement2 RBRACE  */
#line 219 "gocompiler.y"
                                                                                {
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        if (countblocks((yyvsp[-1].node)) > 1){
                                                                                            (yyval.node)=newnode(Block,NULL);
                                                                                            addchild((yyval.node),(yyvsp[-1].node));
                                                                                        }else{
                                                                                            (yyval.node)=(yyvsp[-1].node);
                                                                                        }
                                                                                    }else{
                                                                                        (yyval.node)=NULL;
                                                                                    }
                                                                                }
#line 1831 "y.tab.c"
    break;

  case 28: /* statement: IF expr LBRACE statement2 RBRACE ELSE LBRACE statement2 RBRACE  */
#line 231 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(If,NULL);
                                                                                    addchild((yyval.node),(yyvsp[-7].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[-5].node)!=NULL){
                                                                                        addchild(block,(yyvsp[-5].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                    struct node *block2 = newnode(Block, NULL);
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        addchild(block2,(yyvsp[-1].node));
                                                                                    }
                                                                                    addchild((yyval.node),block2);
                                                                                }
#line 1850 "y.tab.c"
    break;

  case 29: /* statement: IF expr LBRACE statement2 RBRACE  */
#line 245 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(If,NULL);
                                                                                    addchild((yyval.node),(yyvsp[-3].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        addchild(block,(yyvsp[-1].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                    addchild((yyval.node),newnode(Block,NULL));
                                                                                }
#line 1865 "y.tab.c"
    break;

  case 30: /* statement: FOR expr LBRACE statement2 RBRACE  */
#line 255 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(For,NULL);
                                                                                    addchild((yyval.node),(yyvsp[-3].node));
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        addchild(block,(yyvsp[-1].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                }
#line 1879 "y.tab.c"
    break;

  case 31: /* statement: FOR LBRACE statement2 RBRACE  */
#line 265 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(For,NULL);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if((yyvsp[-1].node)!=NULL){
                                                                                        addchild(block,(yyvsp[-1].node));
                                                                                    }
                                                                                    addchild((yyval.node),block);
                                                                                }
#line 1892 "y.tab.c"
    break;

  case 32: /* statement: RETURN expr  */
#line 273 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(Return,NULL);
                                                                                    addchild((yyval.node),(yyvsp[0].node));
                                                                                    LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                }
#line 1902 "y.tab.c"
    break;

  case 33: /* statement: RETURN  */
#line 279 "gocompiler.y"
                                                                                {   (yyval.node)=newnode(Return,NULL);
                                                                                    LOCATE((yyval.node), (yylsp[0]).first_line, (yylsp[0]).first_column);
                                                                                }
#line 1910 "y.tab.c"
    break;

  case 34: /* statement: funcinvocation  */
#line 283 "gocompiler.y"
                                                                                {(yyval.node)=(yyvsp[0].node);}
#line 1916 "y.tab.c"
    break;

  case 35: /* statement: parseargs  */
#line 284 "gocompiler.y"
                                                                                {(yyval.node)=(yyvsp[0].node);}
#line 1922 "y.tab.c"
    break;

  case 36: /* statement: PRINT LPAR expr RPAR  */
#line 285 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(Print,NULL);
                                                                                    addchild((yyval.node),(yyvsp[-1].node));
                                                                                }
#line 1931 "y.tab.c"
    break;

  case 37: /* statement: PRINT LPAR STRLIT RPAR  */
#line 289 "gocompiler.y"
                                                                                {
                                                                                    (yyval.node)=newnode(Print,NULL);
                                                                                    addchild((yyval.node),newnode(StrLit,(yyvsp[-1].lexeme)));
                                                                                }
#line 1940 "y.tab.c"
    break;

  case 38: /* statement: error  */
#line 293 "gocompiler.y"
                                                                                {(yyval.node)=NULL;}
#line 1946 "y.tab.c"
    break;

  case 39: /* statement2: statement2 statement SEMICOLON  */
#line 295 "gocompiler.y"
                                                                                {
                                                                                    if ((yyvsp[-2].node) == NULL) {
                                                                                        (yyval.node) = newnode(aux, NULL); 
                                                                                    } else {
                                                                                        (yyval.node) = (yyvsp[-2].node); 
                                                                                    }
                                                                                    if((yyvsp[-1].node)!=NULL){addchild((yyval.node), (yyvsp[-1].node));} 
                                                                                }
#line 1959 "y.tab.c"
    break;

  case 40: /* statement2: %empty  */
#line 303 "gocompiler.y"
                                                                                {(yyval.node)=NULL;}
#line 1965 "y.tab.c"
    break;

  case 41: /* parseargs: IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ expr RSQ RPAR  */
#line 310 "gocompiler.y"
                                                                                        {
                                                                                            (yyval.node)=newnode(ParseArgs,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[-10].lexeme)));
                                                                                            addchild((yyval.node),(yyvsp[-2].node));
                                                                                            LOCATE((yyval.node), (yylsp[-6]).first_line, (yylsp[-6]).first_column);
                                                                                        }
#line 1976 "y.tab.c"
    break;

  case 42: /* parseargs: IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR  */
#line 316 "gocompiler.y"
                                                                                        {(yyval.node)=NULL;}
#line 1982 "y.tab.c"
    break;

  case 43: /* funcinvocation: IDENTIFIER LPAR expr funcinvocation2 RPAR  */
#line 319 "gocompiler.y"
                                                                                        {
                                                                                            (yyval.node)=newnode(Call,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[-4].lexeme)));
                                                                                            addchild((yyval.node),(yyvsp[-2].node));
                                                                                            if((yyvsp[-1].node)!=NULL){
                                                                                                addchild((yyval.node),(yyvsp[-1].node));
                                                                                            }
                                                                                            LOCATE(getchild((yyval.node), 0), (yylsp[-4]).first_line, (yylsp[-4]).first_column);
                                                                                        }
#line 1996 "y.tab.c"
    break;

  case 44: /* funcinvocation: IDENTIFIER LPAR RPAR  */
#line 328 "gocompiler.y"
                                                                                        {
                                                                                            (yyval.node)=newnode(Call,NULL);
                                                                                            addchild((yyval.node),newnode(Identifier,(yyvsp[-2].lexeme)));
                                                                                            LOCATE(getchild((yyval.node), 0), (yylsp[-2]).first_line, (yylsp[-2]).first_column);
                                                                                        }
#line 2006 "y.tab.c"
    break;

  case 45: /* funcinvocation: IDENTIFIER LPAR error RPAR  */
#line 333 "gocompiler.y"
                                                                                        {(yyval.node)=NULL;}
#line 2012 "y.tab.c"
    break;

  case 46: /* funcinvocation2: funcinvocation2 COMMA expr  */
#line 336 "gocompiler.y"
                                                                                        {
                                                                                            if ((yyvsp[-2].node) == NULL) {
                                                                                                (yyval.node) = newnode(aux, NULL); 
                                                                                            } else {
                                                                                                (yyval.node) = (yyvsp[-2].node); 
                                                                                            }addchild((yyval.node), (yyvsp[0].node));                                                     
                                                                                        }
#line 2024 "y.tab.c"
    break;

  case 47: /* funcinvocation2: %empty  */
#line 343 "gocompiler.y"
                                                                                        {(yyval.node)=NULL;}
#line 2030 "y.tab.c"
    break;

  case 48: /* expr: expr OR expr  */
#line 346 "gocompiler.y"
                                                                                       {
                                                                                            (yyval.node)=newnode(Or,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2041 "y.tab.c"
    break;

  case 49: /* expr: expr AND expr  */
#line 352 "gocompiler.y"
                                                                                       {    (yyval.node)=newnode(And,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2051 "y.tab.c"
    break;

  case 50: /* expr: expr LT expr  */
#line 357 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Lt,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2061 "y.tab.c"
    break;

  case 51: /* expr: expr GT expr  */
#line 362 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Gt,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2071 "y.tab.c"
    break;

  case 52: /* expr: expr EQ expr  */
#line 367 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Eq,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2081 "y.tab.c"
    break;

  case 53: /* expr: expr NE expr  */
#line 372 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Ne,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2091 "y.tab.c"
    break;

  case 54: /* expr: expr LE expr  */
#line 377 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Le,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2101 "y.tab.c"
    break;

  case 55: /* expr: expr GE expr  */
#line 382 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Ge,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2111 "y.tab.c"
    break;

  case 56: /* expr: expr PLUS expr  */
#line 387 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Add,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2121 "y.tab.c"
    break;

  case 57: /* expr: expr MINUS expr  */
#line 392 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Sub,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2131 "y.tab.c"
    break;

  case 58: /* expr: expr STAR expr  */
#line 397 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Mul,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2141 "y.tab.c"
    break;

  case 59: /* expr: expr DIV expr  */
#line 402 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Div,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2151 "y.tab.c"
    break;

  case 60: /* expr: expr MOD expr  */
#line 407 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Mod,NULL);
                                                                                            addchild((yyval.node), (yyvsp[-2].node));
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2161 "y.tab.c"
    break;

  case 61: /* expr: NOT expr  */
#line 412 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Not,NULL);
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2170 "y.tab.c"
    break;

  case 62: /* expr: MINUS expr  */
#line 416 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Minus,NULL);
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2179 "y.tab.c"
    break;

  case 63: /* expr: PLUS expr  */
#line 420 "gocompiler.y"
                                                                                        {   (yyval.node)=newnode(Plus,NULL);
                                                                                            addchild((yyval.node), (yyvsp[0].node));
                                                                                            LOCATE((yyval.node), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                                                                        }
#line 2188 "y.tab.c"
    break;

  case 64: /* expr: NATURAL  */
#line 424 "gocompiler.y"
                                                                                        {(yyval.node) = newnode(Natural, (yyvsp[0].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 2195 "y.tab.c"
    break;

  case 65: /* expr: DECIMAL  */
#line 426 "gocompiler.y"
                                                                                        {(yyval.node) = newnode(Decimal, (yyvsp[0].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 2202 "y.tab.c"
    break;

  case 66: /* expr: IDENTIFIER  */
#line 428 "gocompiler.y"
                                                                                        {(yyval.node) = newnode(Identifier, (yyvsp[0].lexeme));
                                                                                            LOCATE((yyval.node), (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 2209 "y.tab.c"
    break;

  case 67: /* expr: funcinvocation  */
#line 430 "gocompiler.y"
                                                                                        {(yyval.node) = (yyvsp[0].node);
                                                                                            LOCATE((yyval.node), (yylsp[0]).first_line, (yylsp[0]).first_column);}
#line 2216 "y.tab.c"
    break;

  case 68: /* expr: LPAR expr RPAR  */
#line 432 "gocompiler.y"
                                                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2222 "y.tab.c"
    break;

  case 69: /* expr: LPAR error RPAR  */
#line 433 "gocompiler.y"
                                                                                        {(yyval.node) = NULL;}
#line 2228 "y.tab.c"
    break;


#line 2232 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 439 "gocompiler.y"


/* START subroutines section */

// all needed functions are collected in the .l and ast.* files
