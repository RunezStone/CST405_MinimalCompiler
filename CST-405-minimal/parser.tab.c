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
#line 1 "parser.y"

/* SYNTAX ANALYZER (PARSER)
 * This is the second phase of compilation - checking grammar rules
 * Bison generates a parser that builds an Abstract Syntax Tree (AST)
 * The parser uses tokens from the scanner to verify syntax is correct
 *
 * LANGUAGE STRUCTURE:
 *   1. Global variable declarations  (int x; int y;)
 *   2. Function declarations         (func add(int a, int b) ... end result;)
 *   3. Program_Start block           (Program_Start() ... end null;)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* External declarations for lexer interface */
extern int yylex();      /* Get next token from scanner */
extern int yyparse();    /* Parse the entire input */
extern FILE* yyin;       /* Input file handle */
extern int yylineno;     /* Current line number from scanner */
extern char* yytext;     /* Current token text from scanner */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */

#line 98 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FNUM = 4,                       /* FNUM  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_FUNC = 9,                       /* FUNC  */
  YYSYMBOL_PROGRAM_START = 10,             /* PROGRAM_START  */
  YYSYMBOL_END = 11,                       /* END  */
  YYSYMBOL_NULLTOK = 12,                   /* NULLTOK  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_CONTINUE = 14,                  /* CONTINUE  */
  YYSYMBOL_RELOP = 15,                     /* RELOP  */
  YYSYMBOL_16_ = 16,                       /* '+'  */
  YYSYMBOL_17_ = 17,                       /* '-'  */
  YYSYMBOL_18_ = 18,                       /* '*'  */
  YYSYMBOL_19_ = 19,                       /* '/'  */
  YYSYMBOL_UMINUS = 20,                    /* UMINUS  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* '['  */
  YYSYMBOL_26_ = 26,                       /* ']'  */
  YYSYMBOL_27_ = 27,                       /* '='  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_program = 29,                   /* program  */
  YYSYMBOL_global_list = 30,               /* global_list  */
  YYSYMBOL_func_decl_list = 31,            /* func_decl_list  */
  YYSYMBOL_func_decl = 32,                 /* func_decl  */
  YYSYMBOL_param_list = 33,                /* param_list  */
  YYSYMBOL_param_item = 34,                /* param_item  */
  YYSYMBOL_end_clause = 35,                /* end_clause  */
  YYSYMBOL_program_start = 36,             /* program_start  */
  YYSYMBOL_stmt_list = 37,                 /* stmt_list  */
  YYSYMBOL_stmt = 38,                      /* stmt  */
  YYSYMBOL_id_list = 39,                   /* id_list  */
  YYSYMBOL_decl = 40,                      /* decl  */
  YYSYMBOL_assign = 41,                    /* assign  */
  YYSYMBOL_func_call = 42,                 /* func_call  */
  YYSYMBOL_arg_list = 43,                  /* arg_list  */
  YYSYMBOL_expr = 44,                      /* expr  */
  YYSYMBOL_print_stmt = 45,                /* print_stmt  */
  YYSYMBOL_while_stmt = 46,                /* while_stmt  */
  YYSYMBOL_assign_init = 47,               /* assign_init  */
  YYSYMBOL_condition = 48                  /* condition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   271


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
      21,    22,    18,    16,    23,    17,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
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
      15,    20
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    80,    92,    95,   106,   110,   123,   128,
     133,   138,   143,   158,   163,   167,   178,   182,   186,   203,
     207,   212,   219,   227,   247,   251,   255,   270,   274,   282,
     283,   284,   285,   295,   300,   305,   320,   323,   326,   330,
     334,   341,   357,   361,   366,   373,   381,   389,   397,   414,
     418,   423,   431,   447,   451,   455,   470,   474,   478,   483,
     486,   489,   492,   495,   498,   502,   514,   517,   524,   531,
     538,   554,   557,   560,   573,   581
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FNUM", "ID",
  "INT", "FLOAT", "PRINT", "FUNC", "PROGRAM_START", "END", "NULLTOK",
  "WHILE", "CONTINUE", "RELOP", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "'('", "')'", "','", "';'", "'['", "']'", "'='", "$accept", "program",
  "global_list", "func_decl_list", "func_decl", "param_list", "param_item",
  "end_clause", "program_start", "stmt_list", "stmt", "id_list", "decl",
  "assign", "func_call", "arg_list", "expr", "print_stmt", "while_stmt",
  "assign_init", "condition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -60,    12,   101,   -60,   119,    22,   132,     7,     9,   -60,
     -60,   -60,   -60,    28,    10,    36,    55,   -60,    71,   -60,
     103,   -60,   -60,   111,   -60,   191,   -60,   128,   -60,    63,
     153,   106,   -60,   -60,   112,   146,   160,   171,   153,    67,
     -60,     4,    50,    93,    62,   -60,   153,   -60,   -60,   -60,
     -60,   -60,   154,   161,   -60,   -60,   -60,   -60,   153,   153,
       8,   -60,   113,    83,   -60,    92,   -60,     6,    15,   -60,
     118,   -60,   -60,   -60,   -60,   -60,   -60,   153,   146,   -60,
     -60,   -60,   152,   113,   113,   110,   -60,   173,    16,    19,
     -60,    58,   -60,   -60,   -60,   -60,    35,   172,   169,   175,
     -60,   113,   -60,   164,   113,   113,   113,   113,   157,    51,
     -60,   -60,   -60,   -60,   -60,    25,   113,   113,   113,   162,
     124,   -60,   130,   130,   -60,   -60,   113,   -60,   -60,    43,
     183,   -60,   -60,   183,   183,   179,   139,   -60,   155,   -60,
     -60,    98,   190,   180,   -60,   -60,   183,   178,   184,   -60,
     162,   149,   185,   -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     0,     0,     6,
       3,     5,    41,    33,     0,    33,     0,    12,     0,    26,
       0,     7,     2,     0,    40,     0,    36,     0,    37,     0,
       0,     0,    35,    34,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,    25,     0,    27,    29,    30,
      31,    32,     0,     0,    18,    16,    17,    11,     0,     0,
       0,    48,     0,     0,    70,     0,    23,     0,     0,    73,
       0,    24,    28,    38,    39,     9,    10,     0,    15,    14,
      56,    57,    58,     0,     0,     0,    47,    58,     0,     0,
      69,     0,    22,    20,    21,    19,    58,     0,     0,     0,
       8,     0,    63,     0,     0,     0,     0,     0,     0,     0,
      46,    43,    45,    42,    68,     0,     0,     0,     0,     0,
       0,    64,    59,    60,    61,    62,     0,    52,    50,     0,
      53,    67,    66,    74,    75,     0,     0,    65,     0,    51,
      49,     0,     0,     0,    44,    55,    54,     0,     0,    71,
       0,     0,     0,    72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   -60,   199,   -60,   148,   -36,   202,   -38,
     -45,   206,   210,   -60,   -60,   -60,   -59,   -60,   -60,    72,
      95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    39,    40,    45,    10,    46,
      47,    14,    48,    49,    88,   129,    97,    50,    51,    98,
      99
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    72,    57,    85,    89,    61,    91,    92,    19,    78,
      71,    24,     3,    72,    36,    37,    94,   110,     6,     7,
     112,    77,    75,    76,   102,   103,   131,    15,    20,    62,
      93,    63,    72,    25,    26,   104,   105,   106,   107,    95,
     111,   100,   120,   113,   139,   122,   123,   124,   125,   132,
     130,    64,   127,    23,    80,    81,    82,   133,   134,   114,
     101,    27,   116,    69,    35,   140,   141,   138,    83,    36,
      37,    65,    84,   128,   104,   105,   106,   107,    25,    28,
     115,   136,   146,    70,    86,    38,    80,    81,    87,    59,
      60,    72,    29,    90,    66,    80,    81,    82,    67,   145,
      83,    80,    81,    82,    84,    68,    72,     4,     5,    83,
       6,     7,   151,    84,    31,    83,    80,    81,    82,    84,
      12,    80,    81,    96,    13,    30,   104,   105,   106,   107,
      83,    34,    52,    17,    84,    83,   108,    18,    53,    84,
     104,   105,   106,   107,    41,     4,     5,    42,   106,   107,
     137,    54,    44,   143,    41,     4,     5,    42,    41,     4,
       5,    42,    44,   152,    43,    55,    44,    41,     4,     5,
      42,   104,   105,   106,   107,    44,    56,   101,    73,   144,
     104,   105,   106,   107,   126,    74,   121,   117,   104,   105,
     106,   107,    32,   118,   109,   147,    33,   119,   101,   104,
     105,   106,   107,   142,   149,   116,   150,    21,    79,   153,
      22,    16,    11,   135,   148
};

static const yytype_uint8 yycheck[] =
{
      38,    46,    38,    62,    63,     1,    65,     1,     1,     1,
      46,     1,     0,    58,     6,     7,     1,     1,     9,    10,
       1,    59,    58,    59,    83,    84,     1,     5,    21,    25,
      24,    27,    77,    23,    24,    16,    17,    18,    19,    24,
      24,    77,   101,    24,     1,   104,   105,   106,   107,    24,
     109,     1,     1,    25,     3,     4,     5,   116,   117,     1,
      25,    25,    27,     1,     1,    22,    23,   126,    17,     6,
       7,    21,    21,    22,    16,    17,    18,    19,    23,    24,
      22,   119,   141,    21,     1,    22,     3,     4,     5,    22,
      23,   136,    21,     1,     1,     3,     4,     5,     5,     1,
      17,     3,     4,     5,    21,    12,   151,     6,     7,    17,
       9,    10,   150,    21,     3,    17,     3,     4,     5,    21,
       1,     3,     4,     5,     5,    22,    16,    17,    18,    19,
      17,     3,    26,     1,    21,    17,    26,     5,    26,    21,
      16,    17,    18,    19,     5,     6,     7,     8,    18,    19,
      26,     5,    13,    14,     5,     6,     7,     8,     5,     6,
       7,     8,    13,    14,    11,     5,    13,     5,     6,     7,
       8,    16,    17,    18,    19,    13,     5,    25,    24,    24,
      16,    17,    18,    19,    27,    24,    22,    15,    16,    17,
      18,    19,     1,    24,    21,     5,     5,    22,    25,    16,
      17,    18,    19,    24,    24,    27,    22,     8,    60,    24,
       8,     5,     2,   118,   142
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,     6,     7,     9,    10,    31,    32,
      36,    40,     1,     5,    39,     5,    39,     1,     5,     1,
      21,    32,    36,    25,     1,    23,    24,    25,    24,    21,
      22,     3,     1,     5,     3,     1,     6,     7,    22,    33,
      34,     5,     8,    11,    13,    35,    37,    38,    40,    41,
      45,    46,    26,    26,     5,     5,     5,    35,    37,    22,
      23,     1,    25,    27,     1,    21,     1,     5,    12,     1,
      21,    35,    38,    24,    24,    35,    35,    37,     1,    34,
       3,     4,     5,    17,    21,    44,     1,     5,    42,    44,
       1,    44,     1,    24,     1,    24,     5,    44,    47,    48,
      35,    25,    44,    44,    16,    17,    18,    19,    26,    21,
       1,    24,     1,    24,     1,    22,    27,    15,    24,    22,
      44,    22,    44,    44,    44,    44,    27,     1,    22,    43,
      44,     1,    24,    44,    44,    48,    37,    26,    44,     1,
      22,    23,    24,    14,    24,     1,    44,     5,    47,    24,
      22,    37,    14,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    31,    31,    32,    32,
      32,    32,    32,    33,    33,    33,    34,    34,    34,    35,
      35,    35,    35,    35,    36,    36,    36,    37,    37,    38,
      38,    38,    38,    39,    39,    39,    40,    40,    40,    40,
      40,    40,    41,    41,    41,    41,    41,    41,    41,    42,
      42,    42,    42,    43,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    45,    45,    45,    45,
      45,    46,    46,    46,    47,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     1,     2,     7,     6,
       6,     5,     2,     1,     3,     3,     2,     2,     2,     3,
       3,     3,     3,     2,     5,     4,     2,     1,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     6,     6,
       3,     2,     4,     4,     7,     4,     4,     3,     2,     4,
       3,     4,     3,     1,     3,     3,     1,     1,     1,     3,
       3,     3,     3,     2,     3,     4,     5,     5,     4,     3,
       2,     7,    11,     2,     3,     3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: global_list func_decl_list program_start  */
#line 76 "parser.y"
                                             {
        /* Full program: globals, functions, then entry point */
        root = createProgram((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1242 "parser.tab.c"
    break;

  case 3: /* program: global_list program_start  */
#line 80 "parser.y"
                                {
        /* No functions — just globals then Program_Start */
        root = createProgram((yyvsp[-1].node), NULL, (yyvsp[0].node));
    }
#line 1251 "parser.tab.c"
    break;

  case 4: /* global_list: %empty  */
#line 92 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1259 "parser.tab.c"
    break;

  case 5: /* global_list: global_list decl  */
#line 95 "parser.y"
                       {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1267 "parser.tab.c"
    break;

  case 6: /* func_decl_list: func_decl  */
#line 106 "parser.y"
              {
        /* Base case: single function */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1276 "parser.tab.c"
    break;

  case 7: /* func_decl_list: func_decl_list func_decl  */
#line 110 "parser.y"
                               {
        /* Multiple functions: build a list */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1285 "parser.tab.c"
    break;

  case 8: /* func_decl: FUNC ID '(' param_list ')' stmt_list end_clause  */
#line 123 "parser.y"
                                                    {
        /* Function with parameters */
        (yyval.node) = createFuncDecl((yyvsp[-5].str), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-5].str));
    }
#line 1295 "parser.tab.c"
    break;

  case 9: /* func_decl: FUNC ID '(' ')' stmt_list end_clause  */
#line 128 "parser.y"
                                           {
        /* Function with no parameters */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), NULL, (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1305 "parser.tab.c"
    break;

  case 10: /* func_decl: FUNC ID '(' param_list ')' end_clause  */
#line 133 "parser.y"
                                            {
        /* Function with params but empty body */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), (yyvsp[-2].node), NULL, (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1315 "parser.tab.c"
    break;

  case 11: /* func_decl: FUNC ID '(' ')' end_clause  */
#line 138 "parser.y"
                                 {
        /* Function with no params and empty body */
        (yyval.node) = createFuncDecl((yyvsp[-3].str), NULL, NULL, (yyvsp[0].node));
        free((yyvsp[-3].str));
    }
#line 1325 "parser.tab.c"
    break;

  case 12: /* func_decl: FUNC error  */
#line 143 "parser.y"
                 {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed function declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'func name(int a, int b) ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1337 "parser.tab.c"
    break;

  case 13: /* param_list: param_item  */
#line 158 "parser.y"
               {
        /* Single parameter — wrap in NODE_PARAM_LIST so appendParamList
         * always receives a list head, never a raw NODE_PARAM */
        (yyval.node) = createParamList((yyvsp[0].node), NULL);
    }
#line 1347 "parser.tab.c"
    break;

  case 14: /* param_list: param_list ',' param_item  */
#line 163 "parser.y"
                                {
        /* Multiple parameters */
        (yyval.node) = appendParamList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1356 "parser.tab.c"
    break;

  case 15: /* param_list: param_list ',' error  */
#line 167 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'int <name>' after comma in parameter list\n");
        fprintf(stderr, "   💡 Suggestion: Each parameter must have a type, e.g. 'int x'\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1368 "parser.tab.c"
    break;

  case 16: /* param_item: INT ID  */
#line 178 "parser.y"
           {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1377 "parser.tab.c"
    break;

  case 17: /* param_item: FLOAT ID  */
#line 182 "parser.y"
               {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1386 "parser.tab.c"
    break;

  case 18: /* param_item: error ID  */
#line 186 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing type in parameter declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'int %s' instead of just '%s'\n\n", (yyvsp[0].str), (yyvsp[0].str));
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
        yyerrok;
    }
#line 1399 "parser.tab.c"
    break;

  case 19: /* end_clause: END NULLTOK ';'  */
#line 203 "parser.y"
                    {
        /* Void return — function returns nothing */
        (yyval.node) = createEndClause(NULL);
    }
#line 1408 "parser.tab.c"
    break;

  case 20: /* end_clause: END ID ';'  */
#line 207 "parser.y"
                 {
        /* Return a variable's value */
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1418 "parser.tab.c"
    break;

  case 21: /* end_clause: END NULLTOK error  */
#line 212 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after 'end null'\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;'\n\n");
        (yyval.node) = createEndClause(NULL);
        yyerrok;
    }
#line 1430 "parser.tab.c"
    break;

  case 22: /* end_clause: END ID error  */
#line 219 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end %s;'\n\n", (yyvsp[-1].str));
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
        yyerrok;
    }
#line 1443 "parser.tab.c"
    break;

  case 23: /* end_clause: END error  */
#line 227 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;' or 'end <variable>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1455 "parser.tab.c"
    break;

  case 24: /* program_start: PROGRAM_START '(' ')' stmt_list end_clause  */
#line 247 "parser.y"
                                               {
        /* Standard form with parentheses and statements */
        (yyval.node) = createProgramStart((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1464 "parser.tab.c"
    break;

  case 25: /* program_start: PROGRAM_START '(' ')' end_clause  */
#line 251 "parser.y"
                                       {
        /* Empty Program_Start body */
        (yyval.node) = createProgramStart(NULL, (yyvsp[0].node));
    }
#line 1473 "parser.tab.c"
    break;

  case 26: /* program_start: PROGRAM_START error  */
#line 255 "parser.y"
                          {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed Program_Start block\n");
        fprintf(stderr, "   💡 Suggestion: Use 'Program_Start() ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1485 "parser.tab.c"
    break;

  case 27: /* stmt_list: stmt  */
#line 270 "parser.y"
         {
        /* Base case: single statement */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1494 "parser.tab.c"
    break;

  case 28: /* stmt_list: stmt_list stmt  */
#line 274 "parser.y"
                     {
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1503 "parser.tab.c"
    break;

  case 33: /* id_list: ID  */
#line 295 "parser.y"
       {
        /* Base case: single identifier */
        (yyval.node) = createIdList((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1513 "parser.tab.c"
    break;

  case 34: /* id_list: id_list ',' ID  */
#line 300 "parser.y"
                     {
        /* Recursive case: extend list */
        (yyval.node) = appendIdList((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1523 "parser.tab.c"
    break;

  case 35: /* id_list: id_list ',' error  */
#line 305 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected identifier after comma in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add a variable name after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1535 "parser.tab.c"
    break;

  case 36: /* decl: INT id_list ';'  */
#line 320 "parser.y"
                    {
        (yyval.node) = createMultiDecl((yyvsp[-1].node));
    }
#line 1543 "parser.tab.c"
    break;

  case 37: /* decl: FLOAT id_list ';'  */
#line 323 "parser.y"
                        {
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), "float");
    }
#line 1551 "parser.tab.c"
    break;

  case 38: /* decl: INT ID '[' NUM ']' ';'  */
#line 326 "parser.y"
                             {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1560 "parser.tab.c"
    break;

  case 39: /* decl: FLOAT ID '[' NUM ']' ';'  */
#line 330 "parser.y"
                               {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1569 "parser.tab.c"
    break;

  case 40: /* decl: INT id_list error  */
#line 334 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after variable declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the identifier list\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1581 "parser.tab.c"
    break;

  case 41: /* decl: INT error  */
#line 341 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected 'int <identifier>;' or 'int x, y, z;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1593 "parser.tab.c"
    break;

  case 42: /* assign: ID '=' expr ';'  */
#line 357 "parser.y"
                    {
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1602 "parser.tab.c"
    break;

  case 43: /* assign: ID '=' func_call ';'  */
#line 361 "parser.y"
                           {
        /* Function call as RHS: z = add(x, y); */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1612 "parser.tab.c"
    break;

  case 44: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 366 "parser.y"
                                   {
    ASTNode* lhs = createArrayIndex((yyvsp[-6].str), (yyvsp[-4].node));
    ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
    node->data.assign.arrayLHS = lhs;
    (yyval.node) = node;
    free((yyvsp[-6].str));
    }
#line 1624 "parser.tab.c"
    break;

  case 45: /* assign: ID '=' expr error  */
#line 373 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <expression>'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1637 "parser.tab.c"
    break;

  case 46: /* assign: ID '=' func_call error  */
#line 381 "parser.y"
                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after function call assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <func>(...)'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1650 "parser.tab.c"
    break;

  case 47: /* assign: ID '=' error  */
#line 389 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment\n");
        fprintf(stderr, "   💡 Suggestion: Check the expression after '=' for '%s'\n\n", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1663 "parser.tab.c"
    break;

  case 48: /* assign: ID error  */
#line 397 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement\n");
        fprintf(stderr, "   💡 Suggestion: Use '%s = <expression>;'\n\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1676 "parser.tab.c"
    break;

  case 49: /* func_call: ID '(' arg_list ')'  */
#line 414 "parser.y"
                        {
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1685 "parser.tab.c"
    break;

  case 50: /* func_call: ID '(' ')'  */
#line 418 "parser.y"
                 {
        /* No arguments */
        (yyval.node) = createFuncCall((yyvsp[-2].str), NULL);
        free((yyvsp[-2].str));
    }
#line 1695 "parser.tab.c"
    break;

  case 51: /* func_call: ID '(' arg_list error  */
#line 423 "parser.y"
                            {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing ')' in function call\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' after the argument list\n\n");
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
        yyerrok;
    }
#line 1708 "parser.tab.c"
    break;

  case 52: /* func_call: ID '(' error  */
#line 431 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid argument in function call\n");
        fprintf(stderr, "   💡 Suggestion: Use 'funcName(x, y)' or 'funcName()'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1720 "parser.tab.c"
    break;

  case 53: /* arg_list: expr  */
#line 447 "parser.y"
         {
        /* Single argument */
        (yyval.node) = createArgList((yyvsp[0].node));
    }
#line 1729 "parser.tab.c"
    break;

  case 54: /* arg_list: arg_list ',' expr  */
#line 451 "parser.y"
                        {
        /* Multiple arguments */
        (yyval.node) = appendArgList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1738 "parser.tab.c"
    break;

  case 55: /* arg_list: arg_list ',' error  */
#line 455 "parser.y"
                         {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected expression after comma in argument list\n");
        fprintf(stderr, "   💡 Suggestion: Provide a value or variable after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1750 "parser.tab.c"
    break;

  case 56: /* expr: NUM  */
#line 470 "parser.y"
        {
        /* Integer literal */
        (yyval.node) = createNum((yyvsp[0].num));
    }
#line 1759 "parser.tab.c"
    break;

  case 57: /* expr: FNUM  */
#line 474 "parser.y"
           {
        /* Float literal */
        (yyval.node) = createFloat((yyvsp[0].fnum));
    }
#line 1768 "parser.tab.c"
    break;

  case 58: /* expr: ID  */
#line 478 "parser.y"
         {
        /* Variable reference */
        (yyval.node) = createVar((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1778 "parser.tab.c"
    break;

  case 59: /* expr: expr '+' expr  */
#line 483 "parser.y"
                    {
        (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1786 "parser.tab.c"
    break;

  case 60: /* expr: expr '-' expr  */
#line 486 "parser.y"
                    {
        (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1794 "parser.tab.c"
    break;

  case 61: /* expr: expr '*' expr  */
#line 489 "parser.y"
                    {
        (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1802 "parser.tab.c"
    break;

  case 62: /* expr: expr '/' expr  */
#line 492 "parser.y"
                    {
        (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1810 "parser.tab.c"
    break;

  case 63: /* expr: '-' expr  */
#line 495 "parser.y"
                            {
        (yyval.node) = createBinOp('u', (yyvsp[0].node), NULL);
    }
#line 1818 "parser.tab.c"
    break;

  case 64: /* expr: '(' expr ')'  */
#line 498 "parser.y"
                   {
        /* Parenthesized expression */
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1827 "parser.tab.c"
    break;

  case 65: /* expr: ID '[' expr ']'  */
#line 502 "parser.y"
                      {   
        (yyval.node) = createArrayIndex((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str)); 
    }
#line 1836 "parser.tab.c"
    break;

  case 66: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 514 "parser.y"
                           {
        (yyval.node) = createPrint((yyvsp[-2].node));
    }
#line 1844 "parser.tab.c"
    break;

  case 67: /* print_stmt: PRINT '(' expr ')' error  */
#line 517 "parser.y"
                               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after 'print(<expression>)'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1856 "parser.tab.c"
    break;

  case 68: /* print_stmt: PRINT '(' expr error  */
#line 524 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' before semicolon\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1868 "parser.tab.c"
    break;

  case 69: /* print_stmt: PRINT '(' error  */
#line 531 "parser.y"
                      {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1880 "parser.tab.c"
    break;

  case 70: /* print_stmt: PRINT error  */
#line 538 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1892 "parser.tab.c"
    break;

  case 71: /* while_stmt: WHILE '(' condition ')' stmt_list CONTINUE ';'  */
#line 554 "parser.y"
                                                   {
        (yyval.node) = createWhile((yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 1900 "parser.tab.c"
    break;

  case 72: /* while_stmt: WHILE '(' assign_init ';' condition ';' assign_init ')' stmt_list CONTINUE ';'  */
#line 557 "parser.y"
                                                                                     {
        (yyval.node) = createForWhile((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 1908 "parser.tab.c"
    break;

  case 73: /* while_stmt: WHILE error  */
#line 560 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed while loop\n");
        fprintf(stderr, "   💡 Suggestion: Use 'while (<condition>) ... continue;'\n");
        fprintf(stderr, "                  or 'while (i = 0; i < 10; i = i + 1) ... continue;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1921 "parser.tab.c"
    break;

  case 74: /* assign_init: ID '=' expr  */
#line 573 "parser.y"
                {
        (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 1930 "parser.tab.c"
    break;

  case 75: /* condition: expr RELOP expr  */
#line 581 "parser.y"
                    {
        (yyval.node) = createBinOp((char)(yyvsp[-1].num), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1938 "parser.tab.c"
    break;


#line 1942 "parser.tab.c"

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 586 "parser.y"


/* ERROR HANDLING - Called by Bison when a syntax error is detected */
void yyerror(const char* s) {
    fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
    fprintf(stderr, "   %s", s);

    if (yytext && yytext[0] != '\0') {
        fprintf(stderr, " (near token: '%s')\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "   💡 Common fixes:\n");
    fprintf(stderr, "      • Check for missing semicolons\n");
    fprintf(stderr, "      • Verify parentheses and brackets are balanced\n");
    fprintf(stderr, "      • Ensure variables are declared before use\n");
    fprintf(stderr, "      • Check for typos in keywords (int, print, func, end, null)\n");
    fprintf(stderr, "      • Global declarations must come before func declarations\n");
    fprintf(stderr, "      • Program_Start() must be last\n\n");
}
