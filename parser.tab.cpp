/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp" /* yacc.c:339  */

   #include "attributes.hpp"
	#define YYERROR_VERBOSE 1
	#define YYDEBUG 1
	#include "hw3_output.hpp"
	#include "varsSymbolsTable.h"
	#include "enums.h"
	#include "statement.h"
	using namespace std;
	using namespace output;
	extern int yylineno;
	extern int yylex();
	int yyerror(const char * message);
	FuncSymbolsTable* FuncSymbolsTable_t;
	VarsSymbolsTable* VarsSymbolsTable_t;
	#define PPP printf("line number %d \n", __LINE__);

#line 84 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LBRACE = 258,
    RBRACE = 259,
    VOID = 260,
    INT = 261,
    BYTE = 262,
    B = 263,
    BOOL = 264,
    SET = 265,
    TRUE = 266,
    FALSE = 267,
    RETURN = 268,
    IF = 269,
    WHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    SC = 273,
    COMMA = 274,
    DOTS = 275,
    ID = 276,
    NUM = 277,
    STRING = 278,
    SPACE = 279,
    ERROR_CHAR = 280,
    ASSIGN = 281,
    OR = 282,
    AND = 283,
    RELOP_EQ_2L = 284,
    RELOP_GT_1N = 285,
    RELOP_IN = 286,
    BINOP_ADD_L2 = 287,
    BINOP_MUL_L1 = 288,
    NOT = 289,
    LPAREN = 290,
    RPAREN = 291,
    ELSE = 292,
    LBRACKET = 293,
    RBRACKET = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 175 "parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   103,   103,   105,   110,   116,   117,   119,   119,   124,
     125,   127,   128,   130,   131,   134,   136,   137,   139,   140,
     141,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     154,   156,   158,   160,   161,   163,   164,   167,   168,   169,
     170,   172,   174,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   191
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LBRACE", "RBRACE", "VOID", "INT",
  "BYTE", "B", "BOOL", "SET", "TRUE", "FALSE", "RETURN", "IF", "WHILE",
  "BREAK", "CONTINUE", "SC", "COMMA", "DOTS", "ID", "NUM", "STRING",
  "SPACE", "ERROR_CHAR", "ASSIGN", "OR", "AND", "RELOP_EQ_2L",
  "RELOP_GT_1N", "RELOP_IN", "BINOP_ADD_L2", "BINOP_MUL_L1", "NOT",
  "LPAREN", "RPAREN", "ELSE", "LBRACKET", "RBRACKET", "$accept", "Program",
  "Global", "CGlobal", "Funcs", "FuncDecl", "$@1", "RetType", "Formals",
  "FormalsList", "FormalDecl", "Statements", "Statement", "OWhile",
  "IfStart", "WhileStart", "Call", "ExpList", "Type", "OScope", "CScope",
  "Exp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -66,     7,   199,   -66,   -66,   -66,   -66,   -66,   -27,   -66,
     199,    -5,   -66,   -10,   -66,   -66,   -22,     9,    49,    -2,
      -1,   -66,     8,    13,    -3,    38,    49,   -66,   -66,   -66,
     -66,   129,   -66,    10,    14,    16,    30,    51,   -20,   113,
     -66,    31,    36,    55,    53,   129,   -66,   -66,   -66,    41,
      82,   -66,    80,    77,   -66,   130,    80,    80,   -66,   -66,
      80,    59,   -66,   -66,   -66,   -66,   -66,    -9,   129,   -66,
     -66,    60,   167,   -66,    80,    80,    80,    80,    80,    80,
      80,   145,   145,   137,   -66,    61,   160,   -66,   129,   -66,
     -66,    80,   106,    80,   -66,    76,   181,   121,   185,    -8,
      85,   -66,   -66,   -66,    80,   -66,   129,   153,   -66,   -66,
     -66,    84,   -66,   -66,   -66,   -66,   129,   -66,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     5,     1,    10,    37,    38,    39,     0,     4,
       5,     0,     9,     0,     2,     6,     0,     0,    11,     0,
       0,    12,    13,     0,     0,     0,     0,    15,    40,     7,
      14,     0,    41,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     0,     0,     0,     0,    51,    52,    23,    46,
      48,    50,     0,     0,    47,     0,     0,     0,    28,    29,
       0,     0,    42,    17,    41,    41,    22,     0,    42,    49,
      53,     0,     0,    24,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,     8,     0,    30,
      19,     0,     0,     0,    43,    55,    54,    58,    56,    57,
      45,    44,    21,    33,     0,    42,     0,     0,    18,    59,
      36,    25,    42,    20,    41,    27,     0,    42,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,   -66,   -66,   103,   -66,   -66,   -66,   -66,    98,
     -66,    86,   -38,   -66,   -66,   -66,   -31,    21,     0,   -60,
     -65,   -14
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    14,     9,    10,    31,    11,    20,    21,
      22,    39,    40,   106,    41,    42,    54,    85,    44,    45,
      87,    86
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      43,    63,    12,    92,    88,    89,    60,     3,    43,    90,
      12,    13,    17,    18,    43,    61,    16,    91,    23,    55,
      24,    46,    47,    -1,    79,    80,    23,    26,    48,    19,
      63,    49,    50,    51,    27,    25,    28,    43,    70,    72,
     111,    29,    81,    82,    52,    53,    83,   115,    58,    56,
     105,    57,   118,    71,   116,     5,     6,    43,     7,     8,
      95,    96,    97,    98,    99,   100,   101,    64,   112,    59,
      46,    47,    65,    66,    67,    43,    61,   107,   117,   109,
      49,    50,    51,     5,     6,    43,     7,     8,    46,    47,
      69,    46,    47,    52,    53,    84,    93,   103,    49,    50,
      51,    49,    50,    51,    75,    76,    77,    78,    79,    80,
     108,    52,    53,    15,    52,    53,    32,    62,    80,     5,
       6,   114,     7,     8,    30,   110,    33,    34,    35,    36,
      37,    68,    32,     0,    38,     5,     6,     0,     7,     8,
       0,     0,    33,    34,    35,    36,    37,     0,    73,     0,
      38,    77,    78,    79,    80,   102,     0,    74,    75,    76,
      77,    78,    79,    80,    74,    75,    76,    77,    78,    79,
      80,   113,    74,    75,    76,    77,    78,    79,    80,   104,
      74,    75,    76,    77,    78,    79,    80,    74,    75,    76,
      77,    78,    79,    80,    74,    75,    76,    77,    78,    79,
      80,     0,     0,    94,     4,     5,     6,     0,     7,     8,
      76,    77,    78,    79,    80,    -1,    78,    79,    80
};

static const yytype_int8 yycheck[] =
{
      31,    39,     2,    68,    64,    65,    26,     0,    39,    18,
      10,    38,    22,    35,    45,    35,    21,    26,    18,    33,
      22,    11,    12,    31,    32,    33,    26,    19,    18,    20,
      68,    21,    22,    23,    21,    36,    39,    68,    52,    53,
     105,     3,    56,    57,    34,    35,    60,   112,    18,    35,
      88,    35,   117,    53,   114,     6,     7,    88,     9,    10,
      74,    75,    76,    77,    78,    79,    80,    36,   106,    18,
      11,    12,    36,    18,    21,   106,    35,    91,   116,    93,
      21,    22,    23,     6,     7,   116,     9,    10,    11,    12,
       8,    11,    12,    34,    35,    36,    36,    36,    21,    22,
      23,    21,    22,    23,    28,    29,    30,    31,    32,    33,
       4,    34,    35,    10,    34,    35,     3,     4,    33,     6,
       7,    37,     9,    10,    26,   104,    13,    14,    15,    16,
      17,    45,     3,    -1,    21,     6,     7,    -1,     9,    10,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    18,    -1,
      21,    30,    31,    32,    33,    18,    -1,    27,    28,    29,
      30,    31,    32,    33,    27,    28,    29,    30,    31,    32,
      33,    18,    27,    28,    29,    30,    31,    32,    33,    19,
      27,    28,    29,    30,    31,    32,    33,    27,    28,    29,
      30,    31,    32,    33,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    36,     5,     6,     7,    -1,     9,    10,
      29,    30,    31,    32,    33,    30,    31,    32,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    42,     0,     5,     6,     7,     9,    10,    44,
      45,    47,    58,    38,    43,    44,    21,    22,    35,    20,
      48,    49,    50,    58,    22,    36,    19,    21,    39,     3,
      49,    46,     3,    13,    14,    15,    16,    17,    21,    51,
      52,    54,    55,    56,    58,    59,    11,    12,    18,    21,
      22,    23,    34,    35,    56,    61,    35,    35,    18,    18,
      26,    35,     4,    52,    36,    36,    18,    21,    51,     8,
      61,    58,    61,    18,    27,    28,    29,    30,    31,    32,
      33,    61,    61,    61,    36,    57,    61,    60,    59,    59,
      18,    26,    60,    36,    36,    61,    61,    61,    61,    61,
      61,    61,    18,    36,    19,    52,    53,    61,     4,    61,
      57,    60,    52,    18,    37,    60,    59,    52,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    43,    44,    44,    46,    45,    47,
      47,    48,    48,    49,    49,    50,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    54,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    59,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     0,     0,     2,     0,    10,     1,
       1,     0,     1,     1,     3,     2,     1,     2,     5,     3,
       5,     4,     2,     2,     3,     5,     9,     6,     2,     2,
       0,     3,     3,     4,     3,     1,     3,     1,     1,     1,
       6,     0,     0,     3,     3,     3,     1,     1,     1,     2,
       1,     1,     1,     2,     3,     3,     3,     3,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 103 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1349 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 105 "parser.ypp" /* yacc.c:1646  */
    {FuncSymbolsTable_t = new FuncSymbolsTable();
																										VarsSymbolsTable_t = new VarsSymbolsTable();
																										VarsSymbolsTable_t->setFuncsTable(FuncSymbolsTable_t);
																										VarsSymbolsTable_t->addFirstScope();}
#line 1358 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 110 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->deleteScope(true);
																										delete VarsSymbolsTable_t;
																										delete FuncSymbolsTable_t;
}
#line 1367 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 116 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1373 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 117 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1379 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 119 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->addScopeFromFunc(*((yyvsp[-4])->str), (yyvsp[-2])->varsVec, (yyvsp[-5])->type);
                                                                            FuncSymbolsTable_t->addFunc(*((yyvsp[-4])->str), (yyvsp[-2])->varsVec, (yyvsp[-5])->type, VarsSymbolsTable_t);}
#line 1386 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 122 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1392 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 124 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->type = (yyvsp[0])->type;}
#line 1398 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 125 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Types_enum::VOID_TYPE);}
#line 1404 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 127 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(std::vector<Var>());}
#line 1410 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 128 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->varsVec = (yyvsp[0])->varsVec;}
#line 1416 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 130 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->varsVec = (yyvsp[0])->varsVec;}
#line 1422 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 131 "parser.ypp" /* yacc.c:1646  */
    {(yyvsp[0])->varsVec.push_back((yyvsp[-2])->varsVec.at(0));
																										(yyval)->varsVec = (yyvsp[0])->varsVec;}
#line 1429 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 134 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->varsVec = std::vector<Var>(1, Var(*((yyvsp[0])->str), (yyvsp[-1])->type));}
#line 1435 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1441 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 137 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1447 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 139 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1453 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->addVar(*((yyvsp[-1])->str), (yyvsp[-2])->type);}
#line 1459 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 141 "parser.ypp" /* yacc.c:1646  */
    {(yyvsp[-1])->exp.typeCheck((yyvsp[-4])->type);
                                                                            VarsSymbolsTable_t->addVar(*((yyvsp[-3])->str), (yyvsp[-4])->type);}
#line 1466 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 144 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->typeCheck(*((yyvsp[-3])->str), (yyvsp[-1])->exp.type);}
#line 1472 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 145 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1478 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 146 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->checkRetType(Types(Types_enum::VOID_TYPE));}
#line 1484 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 147 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->checkRetType((yyvsp[-1])->exp.type);}
#line 1490 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 148 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1496 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 149 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1502 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 150 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1508 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 151 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->checkWhile(*((yyvsp[-1])->str));}
#line 1514 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 152 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->checkWhile(*((yyvsp[-1])->str));}
#line 1520 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 154 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->setWhile();}
#line 1526 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 156 "parser.ypp" /* yacc.c:1646  */
    {Statement::checkExp((yyvsp[0])->exp);}
#line 1532 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 158 "parser.ypp" /* yacc.c:1646  */
    {Statement::checkExp((yyvsp[0])->exp);}
#line 1538 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 160 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->type = FuncSymbolsTable_t->checkFunc(*((yyvsp[-3])->str), (yyvsp[-1])->typesVec);}
#line 1544 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 161 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->type = FuncSymbolsTable_t->checkFunc(*((yyvsp[-2])->str), std::vector<Types>());}
#line 1550 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 163 "parser.ypp" /* yacc.c:1646  */
    {(yyval)->typesVec = std::vector<Types>(1, (yyvsp[0])->exp.type);}
#line 1556 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 164 "parser.ypp" /* yacc.c:1646  */
    {(yyvsp[0])->typesVec.push_back((yyvsp[-2])->exp.type);
																										(yyval)->typesVec = (yyvsp[0])->typesVec;}
#line 1563 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 167 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Types_enum::INT_TYPE);}
#line 1569 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 168 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Types_enum::BYTE_TYPE);}
#line 1575 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 169 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Types_enum::BOOL_TYPE);}
#line 1581 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 170 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(setCheck(yylineno, (yyvsp[-3])->num, (yyvsp[-1])->num));}
#line 1587 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 172 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->addScope();}
#line 1593 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 174 "parser.ypp" /* yacc.c:1646  */
    {VarsSymbolsTable_t->deleteScope();}
#line 1599 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 176 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype((yyvsp[-1])->exp);}
#line 1605 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 177 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.binopMulDiv((yyvsp[0])->exp)));}
#line 1611 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 178 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.binopAddSub((yyvsp[0])->exp)));}
#line 1617 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 179 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(VarsSymbolsTable_t->getExp(*((yyvsp[0])->str))));}
#line 1623 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 180 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[0])->type));}
#line 1629 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 181 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(Types_enum::INT_TYPE));}
#line 1635 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 182 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(Expression::byteCheck((yyvsp[-1])->num)));}
#line 1641 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 183 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(Types_enum::STRING_TYPE));}
#line 1647 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 184 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(Types_enum::BOOL_TYPE));}
#line 1653 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 185 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression(Types_enum::BOOL_TYPE));}
#line 1659 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 186 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[0])->exp.opNot()));}
#line 1665 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 187 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.opAnd((yyvsp[0])->exp)));}
#line 1671 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 188 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.opOr((yyvsp[0])->exp)));}
#line 1677 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 189 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.relop((yyvsp[0])->exp)));}
#line 1683 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 190 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.in((yyvsp[0])->exp)));}
#line 1689 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 191 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[-2])->exp.relop((yyvsp[0])->exp)));}
#line 1695 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 191 "parser.ypp" /* yacc.c:1646  */
    {(yyval) = new utype(Expression((yyvsp[0])->exp.cast((yyvsp[-2])->type)));}
#line 1701 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 1705 "parser.tab.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 193 "parser.ypp" /* yacc.c:1906  */


int main(){
   yyparse();
}

int yyerror(char const* s){
   output::errorSyn(yylineno);
   exit(1);
}


