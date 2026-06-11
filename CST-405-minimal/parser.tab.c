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
  YYSYMBOL_STRUCT = 15,                    /* STRUCT  */
  YYSYMBOL_IS = 16,                        /* IS  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_RELOP = 19,                     /* RELOP  */
  YYSYMBOL_LOWER_THAN_ELSE = 20,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '*'  */
  YYSYMBOL_24_ = 24,                       /* '/'  */
  YYSYMBOL_UMINUS = 25,                    /* UMINUS  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* ';'  */
  YYSYMBOL_30_ = 30,                       /* '['  */
  YYSYMBOL_31_ = 31,                       /* ']'  */
  YYSYMBOL_32_ = 32,                       /* '='  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_program = 36,                   /* program  */
  YYSYMBOL_global_list = 37,               /* global_list  */
  YYSYMBOL_func_decl_list = 38,            /* func_decl_list  */
  YYSYMBOL_func_decl = 39,                 /* func_decl  */
  YYSYMBOL_param_list = 40,                /* param_list  */
  YYSYMBOL_param_item = 41,                /* param_item  */
  YYSYMBOL_end_clause = 42,                /* end_clause  */
  YYSYMBOL_program_start = 43,             /* program_start  */
  YYSYMBOL_stmt_list = 44,                 /* stmt_list  */
  YYSYMBOL_stmt = 45,                      /* stmt  */
  YYSYMBOL_id_list = 46,                   /* id_list  */
  YYSYMBOL_decl = 47,                      /* decl  */
  YYSYMBOL_assign = 48,                    /* assign  */
  YYSYMBOL_func_call = 49,                 /* func_call  */
  YYSYMBOL_arg_list = 50,                  /* arg_list  */
  YYSYMBOL_expr = 51,                      /* expr  */
  YYSYMBOL_struct_def = 52,                /* struct_def  */
  YYSYMBOL_field_body = 53,                /* field_body  */
  YYSYMBOL_field_item = 54,                /* field_item  */
  YYSYMBOL_print_stmt = 55,                /* print_stmt  */
  YYSYMBOL_if_stmt = 56,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 57,                /* while_stmt  */
  YYSYMBOL_assign_init = 58,               /* assign_init  */
  YYSYMBOL_condition = 59                  /* condition  */
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
#define YYLAST   448

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
      26,    27,    23,    21,    28,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
       2,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    88,   100,   103,   114,   118,   131,   136,
     141,   146,   151,   166,   171,   175,   186,   190,   194,   211,
     215,   220,   226,   233,   241,   261,   265,   269,   284,   288,
     296,   297,   298,   299,   300,   301,   311,   316,   321,   336,
     339,   342,   346,   350,   354,   360,   367,   383,   387,   392,
     399,   407,   415,   423,   431,   448,   452,   457,   465,   481,
     485,   489,   504,   508,   512,   517,   520,   523,   526,   529,
     532,   536,   540,   556,   563,   566,   572,   576,   580,   584,
     588,   601,   604,   611,   618,   625,   642,   645,   648,   651,
     654,   657,   660,   663,   666,   682,   685,   688,   701,   709
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
  "WHILE", "CONTINUE", "STRUCT", "IS", "IF", "ELSE", "RELOP",
  "LOWER_THAN_ELSE", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'('", "')'",
  "','", "';'", "'['", "']'", "'='", "'{'", "'}'", "$accept", "program",
  "global_list", "func_decl_list", "func_decl", "param_list", "param_item",
  "end_clause", "program_start", "stmt_list", "stmt", "id_list", "decl",
  "assign", "func_call", "arg_list", "expr", "struct_def", "field_body",
  "field_item", "print_stmt", "if_stmt", "while_stmt", "assign_init",
  "condition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-181)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-65)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -181,    17,   416,  -181,     6,    18,    27,   148,     9,    50,
     199,  -181,  -181,  -181,  -181,  -181,   131,  -181,    40,    11,
      46,   200,  -181,    53,  -181,    59,    75,  -181,  -181,   150,
    -181,    88,  -181,  -181,   107,  -181,   134,   356,   179,  -181,
    -181,    89,    92,   108,   125,   143,   356,   205,  -181,  -181,
    -181,   248,    28,   124,    71,    73,   177,   177,   142,   356,
    -181,  -181,  -181,   420,  -181,  -181,  -181,   122,   157,   165,
       0,  -181,   144,   168,  -181,  -181,  -181,   242,   356,   356,
     137,  -181,   177,    55,  -181,   272,  -181,   172,    12,    13,
    -181,   201,  -181,   177,   147,  -181,   393,   194,  -181,   174,
     177,   177,   177,   177,   177,   227,   236,  -181,  -181,  -181,
    -181,   281,   283,   356,   108,  -181,   363,  -181,   145,    14,
      66,  -181,    82,  -181,  -181,  -181,  -181,  -181,    64,   411,
     181,   191,   198,   177,   216,  -181,   202,   123,   123,   214,
     214,   279,  -181,   239,  -181,   244,   287,   213,   257,  -181,
    -181,  -181,  -181,  -181,    15,   177,   177,   177,   356,   221,
     367,  -181,   177,  -181,   232,   237,   177,  -181,  -181,    25,
     424,  -181,  -181,   424,   424,   245,  -181,   308,    58,  -181,
     379,   270,   275,   383,  -181,  -181,   284,   300,   278,   268,
     111,  -181,  -181,  -181,  -181,  -181,   424,   277,   290,  -181,
      -9,   302,   356,   161,  -181,     4,   332,  -181,   185,   209,
    -181,   289,  -181,  -181,   233,  -181,  -181
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     6,     3,     5,    43,    36,     0,    46,    36,     0,
      36,     0,    12,     0,    27,     0,     0,     7,     2,     0,
      44,     0,    45,    39,     0,    40,     0,     0,     0,    38,
      37,     0,     0,     0,     0,     0,     0,     0,    13,    62,
      63,     0,     0,     0,     0,     0,     0,     0,    35,     0,
      28,    30,    31,     0,    32,    34,    33,     0,     0,     0,
       0,    74,     0,     0,    18,    16,    17,    35,     0,     0,
       0,    54,     0,     0,    85,     0,    24,     0,     0,     0,
      97,     0,    94,     0,    64,    69,     0,    35,    29,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    75,    41,
      42,    35,    35,     0,    15,    14,     0,    53,    64,     0,
       0,    84,     0,    21,    23,    20,    22,    19,    64,     0,
       0,     0,     0,     0,     0,    70,    72,    65,    66,    67,
      68,     0,    76,     0,    77,     0,    35,    71,     0,    52,
      48,    51,    47,    83,     0,     0,     0,     0,     0,     0,
       0,    72,     0,    80,     0,     0,     0,    58,    56,     0,
      59,    82,    81,    98,    99,     0,    35,     0,     0,    71,
       0,     0,     0,     0,    57,    55,     0,     0,     0,    87,
       0,    50,    78,    79,    49,    61,    60,     0,     0,    95,
       0,    86,     0,     0,    93,     0,     0,    91,     0,     0,
      92,     0,    89,    90,     0,    96,    88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -181,  -181,  -181,  -181,   314,  -181,   246,   -28,   317,   -46,
     -56,   276,   326,  -181,  -181,  -181,   -55,  -181,  -181,   259,
    -181,  -180,  -181,   146,   -89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    10,    11,    47,    48,   176,    12,    59,
      60,    16,    61,    62,   119,   169,    63,    14,    70,    71,
      64,    65,    66,   130,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    95,    96,    98,   132,    67,    68,    69,    55,    58,
      24,    15,    32,   124,   126,   149,   171,     3,    77,    17,
     204,    55,    98,    18,   203,   210,   184,   116,   120,    84,
     122,    97,    20,   113,   107,    25,   129,   209,   129,    29,
      33,   125,   127,   150,   172,   137,   138,   139,   140,   141,
     111,   112,   185,   186,    85,    26,   117,    98,    49,    50,
     118,    49,    50,    51,     5,     6,    52,   151,   175,    53,
      31,    54,    90,     9,    92,    55,    34,    56,   160,    36,
      56,    57,   134,   153,    57,   146,    37,   100,   101,   102,
     103,    41,   189,   170,   133,   152,   155,    91,   134,    93,
     173,   174,   129,   100,   101,   102,   103,   180,    38,   154,
      42,   183,   177,    74,    49,    50,    51,     5,     6,    52,
      72,    98,    53,    73,    54,    86,     9,    87,    55,    88,
      75,   196,   190,    56,    98,    43,    89,    57,   114,   134,
      44,    45,   -26,    44,    45,   201,   102,   103,    76,    22,
      98,    39,    98,    23,   104,    40,   206,   208,    98,    29,
      30,    46,   105,   214,    49,    50,    51,     5,     6,    52,
     106,   148,    53,   109,    54,   133,     9,   133,    55,   136,
      49,    50,    94,    56,    67,    68,    69,    57,    49,    50,
      51,     5,     6,    52,   -25,   207,    53,   110,    54,    56,
       9,   123,    55,    57,    49,    50,   128,    56,     7,     8,
     157,    57,    49,    50,    51,     5,     6,    52,   158,   212,
      53,   161,    54,    56,     9,   159,    55,    57,    29,    35,
     134,    56,    79,    80,   162,    57,    49,    50,    51,     5,
       6,    52,   164,   213,    53,   166,    54,   165,     9,    81,
      55,   -11,   -11,    15,   178,    56,   142,   143,   167,    57,
      49,    50,    94,   181,   -64,   144,   145,   216,   182,   -64,
     -64,   -64,   -64,   121,   187,    49,    50,    94,    82,    56,
      83,    19,    21,    57,   168,   195,   200,    49,    50,    94,
      -9,    -9,   -10,   -10,    56,   134,    -8,    -8,    57,   192,
     100,   101,   102,   103,   193,   197,    56,   199,   163,   155,
      57,    49,    50,    51,     5,     6,    52,   202,   215,    53,
     205,    54,   188,     9,    27,    55,   115,    28,    13,   108,
      56,     0,     0,   198,    57,    49,    50,    51,     5,     6,
      52,     0,     0,    53,     0,    54,   211,     9,     0,    55,
       0,     0,     0,     0,    56,     0,     0,     0,    57,    49,
      50,    51,     5,     6,    52,     0,     0,    53,     0,    54,
       0,     9,     0,    55,     0,     0,     0,     0,    56,   134,
       0,     0,    57,   134,   100,   101,   102,   103,   100,   101,
     102,   103,     0,     0,   147,   134,     0,     0,   179,   134,
     100,   101,   102,   103,   100,   101,   102,   103,   191,   134,
       0,     0,   194,     0,   100,   101,   102,   103,     0,     0,
     135,     4,     5,     6,     0,     7,     8,   134,     0,     0,
     156,     9,   100,   101,   102,   103,    99,     0,     0,     0,
     134,   100,   101,   102,   103,   100,   101,   102,   103
};

static const yytype_int16 yycheck[] =
{
      46,    56,    57,    59,    93,     5,     6,     7,    17,    37,
       1,     5,     1,     1,     1,     1,     1,     0,    46,     1,
     200,    17,    78,     5,    33,   205,     1,    82,    83,     1,
      85,    59,     5,    79,    34,    26,    91,    33,    93,    28,
      29,    29,    29,    29,    29,   100,   101,   102,   103,   104,
      78,    79,    27,    28,    26,     5,     1,   113,     3,     4,
       5,     3,     4,     5,     6,     7,     8,     1,   157,    11,
      30,    13,     1,    15,     1,    17,    30,    22,   133,    26,
      22,    26,    16,     1,    26,   113,    27,    21,    22,    23,
      24,     3,    34,   148,    30,    29,    32,    26,    16,    26,
     155,   156,   157,    21,    22,    23,    24,   162,    33,    27,
       3,   166,   158,     5,     3,     4,     5,     6,     7,     8,
      31,   177,    11,    31,    13,     1,    15,     3,    17,     5,
       5,   186,   178,    22,   190,     1,    12,    26,     1,    16,
       6,     7,     0,     6,     7,    34,    23,    24,     5,     1,
     206,     1,   208,     5,    32,     5,   202,   203,   214,    28,
      29,    27,     5,   209,     3,     4,     5,     6,     7,     8,
       5,    26,    11,    29,    13,    30,    15,    30,    17,     5,
       3,     4,     5,    22,     5,     6,     7,    26,     3,     4,
       5,     6,     7,     8,     0,    34,    11,    29,    13,    22,
      15,    29,    17,    26,     3,     4,     5,    22,     9,    10,
      29,    26,     3,     4,     5,     6,     7,     8,    27,    34,
      11,     5,    13,    22,    15,    27,    17,    26,    28,    29,
      16,    22,    27,    28,    32,    26,     3,     4,     5,     6,
       7,     8,     3,    34,    11,    32,    13,     3,    15,     1,
      17,     9,    10,     5,    33,    22,    29,    30,     1,    26,
       3,     4,     5,    31,    16,    29,    30,    34,    31,    21,
      22,    23,    24,     1,    29,     3,     4,     5,    30,    22,
      32,     5,     6,    26,    27,     1,    18,     3,     4,     5,
       9,    10,     9,    10,    22,    16,     9,    10,    26,    29,
      21,    22,    23,    24,    29,     5,    22,    29,    29,    32,
      26,     3,     4,     5,     6,     7,     8,    27,    29,    11,
      18,    13,    14,    15,    10,    17,    80,    10,     2,    70,
      22,    -1,    -1,   187,    26,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    13,    14,    15,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    26,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    13,
      -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,    16,
      -1,    -1,    26,    16,    21,    22,    23,    24,    21,    22,
      23,    24,    -1,    -1,    31,    16,    -1,    -1,    31,    16,
      21,    22,    23,    24,    21,    22,    23,    24,    29,    16,
      -1,    -1,    29,    -1,    21,    22,    23,    24,    -1,    -1,
      27,     5,     6,     7,    -1,     9,    10,    16,    -1,    -1,
      19,    15,    21,    22,    23,    24,    16,    -1,    -1,    -1,
      16,    21,    22,    23,    24,    21,    22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    37,     0,     5,     6,     7,     9,    10,    15,
      38,    39,    43,    47,    52,     5,    46,     1,     5,    46,
       5,    46,     1,     5,     1,    26,     5,    39,    43,    28,
      29,    30,     1,    29,    30,    29,    26,    27,    33,     1,
       5,     3,     3,     1,     6,     7,    27,    40,    41,     3,
       4,     5,     8,    11,    13,    17,    22,    26,    42,    44,
      45,    47,    48,    51,    55,    56,    57,     5,     6,     7,
      53,    54,    31,    31,     5,     5,     5,    42,    44,    27,
      28,     1,    30,    32,     1,    26,     1,     3,     5,    12,
       1,    26,     1,    26,     5,    51,    51,    42,    45,    16,
      21,    22,    23,    24,    32,     5,     5,    34,    54,    29,
      29,    42,    42,    44,     1,    41,    51,     1,     5,    49,
      51,     1,    51,    29,     1,    29,     1,    29,     5,    51,
      58,    59,    59,    30,    16,    27,     5,    51,    51,    51,
      51,    51,    29,    30,    29,    30,    42,    31,    26,     1,
      29,     1,    29,     1,    27,    32,    19,    29,    27,    27,
      51,     5,    32,    29,     3,     3,    32,     1,    27,    50,
      51,     1,    29,    51,    51,    59,    42,    44,    33,    31,
      51,    31,    31,    51,     1,    27,    28,    29,    14,    34,
      44,    29,    29,    29,    29,     1,    51,     5,    58,    29,
      18,    34,    27,    33,    56,    18,    44,    34,    44,    33,
      56,    14,    34,    34,    44,    29,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    36,    37,    37,    38,    38,    39,    39,
      39,    39,    39,    40,    40,    40,    41,    41,    41,    42,
      42,    42,    42,    42,    42,    43,    43,    43,    44,    44,
      45,    45,    45,    45,    45,    45,    46,    46,    46,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    49,    49,    50,
      50,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    53,    53,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    58,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     1,     2,     7,     6,
       6,     5,     2,     1,     3,     3,     2,     2,     2,     3,
       3,     3,     3,     3,     2,     5,     4,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     6,     6,     1,     3,     3,     2,     4,     4,     7,
       6,     4,     4,     3,     2,     4,     3,     4,     3,     1,
       3,     3,     1,     1,     1,     3,     3,     3,     3,     2,
       3,     4,     3,     5,     1,     2,     3,     3,     6,     6,
       4,     5,     5,     4,     3,     2,     7,     6,    11,    10,
      10,     9,     9,     8,     2,     7,    11,     2,     3,     3
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
#line 84 "parser.y"
                                             {
        /* Full program: globals, functions, then entry point */
        root = createProgram((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1325 "parser.tab.c"
    break;

  case 3: /* program: global_list program_start  */
#line 88 "parser.y"
                                {
        /* No functions — just globals then Program_Start */
        root = createProgram((yyvsp[-1].node), NULL, (yyvsp[0].node));
    }
#line 1334 "parser.tab.c"
    break;

  case 4: /* global_list: %empty  */
#line 100 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1342 "parser.tab.c"
    break;

  case 5: /* global_list: global_list decl  */
#line 103 "parser.y"
                       {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1350 "parser.tab.c"
    break;

  case 6: /* func_decl_list: func_decl  */
#line 114 "parser.y"
              {
        /* Base case: single function */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1359 "parser.tab.c"
    break;

  case 7: /* func_decl_list: func_decl_list func_decl  */
#line 118 "parser.y"
                               {
        /* Multiple functions: build a list */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1368 "parser.tab.c"
    break;

  case 8: /* func_decl: FUNC ID '(' param_list ')' stmt_list end_clause  */
#line 131 "parser.y"
                                                    {
        /* Function with parameters */
        (yyval.node) = createFuncDecl((yyvsp[-5].str), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-5].str));
    }
#line 1378 "parser.tab.c"
    break;

  case 9: /* func_decl: FUNC ID '(' ')' stmt_list end_clause  */
#line 136 "parser.y"
                                           {
        /* Function with no parameters */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), NULL, (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1388 "parser.tab.c"
    break;

  case 10: /* func_decl: FUNC ID '(' param_list ')' end_clause  */
#line 141 "parser.y"
                                            {
        /* Function with params but empty body */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), (yyvsp[-2].node), NULL, (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1398 "parser.tab.c"
    break;

  case 11: /* func_decl: FUNC ID '(' ')' end_clause  */
#line 146 "parser.y"
                                 {
        /* Function with no params and empty body */
        (yyval.node) = createFuncDecl((yyvsp[-3].str), NULL, NULL, (yyvsp[0].node));
        free((yyvsp[-3].str));
    }
#line 1408 "parser.tab.c"
    break;

  case 12: /* func_decl: FUNC error  */
#line 151 "parser.y"
                 {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed function declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'func name(int a, int b) ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1420 "parser.tab.c"
    break;

  case 13: /* param_list: param_item  */
#line 166 "parser.y"
               {
        /* Single parameter — wrap in NODE_PARAM_LIST so appendParamList
         * always receives a list head, never a raw NODE_PARAM */
        (yyval.node) = createParamList((yyvsp[0].node), NULL);
    }
#line 1430 "parser.tab.c"
    break;

  case 14: /* param_list: param_list ',' param_item  */
#line 171 "parser.y"
                                {
        /* Multiple parameters */
        (yyval.node) = appendParamList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1439 "parser.tab.c"
    break;

  case 15: /* param_list: param_list ',' error  */
#line 175 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'int <name>' after comma in parameter list\n");
        fprintf(stderr, "   💡 Suggestion: Each parameter must have a type, e.g. 'int x'\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1451 "parser.tab.c"
    break;

  case 16: /* param_item: INT ID  */
#line 186 "parser.y"
           {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1460 "parser.tab.c"
    break;

  case 17: /* param_item: FLOAT ID  */
#line 190 "parser.y"
               {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1469 "parser.tab.c"
    break;

  case 18: /* param_item: error ID  */
#line 194 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing type in parameter declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'int %s' instead of just '%s'\n\n", (yyvsp[0].str), (yyvsp[0].str));
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
        yyerrok;
    }
#line 1482 "parser.tab.c"
    break;

  case 19: /* end_clause: END NULLTOK ';'  */
#line 211 "parser.y"
                    {
        /* Void return — function returns nothing */
        (yyval.node) = createEndClause(NULL);
    }
#line 1491 "parser.tab.c"
    break;

  case 20: /* end_clause: END ID ';'  */
#line 215 "parser.y"
                 {
        /* Return a variable's value */
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1501 "parser.tab.c"
    break;

  case 21: /* end_clause: END NUM ';'  */
#line 220 "parser.y"
                  {
        /* Return an integer literal — e.g. end 1; end 0; */
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", (yyvsp[-1].num));
        (yyval.node) = createEndClause(buf);
    }
#line 1512 "parser.tab.c"
    break;

  case 22: /* end_clause: END NULLTOK error  */
#line 226 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after 'end null'\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;'\n\n");
        (yyval.node) = createEndClause(NULL);
        yyerrok;
    }
#line 1524 "parser.tab.c"
    break;

  case 23: /* end_clause: END ID error  */
#line 233 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end %s;'\n\n", (yyvsp[-1].str));
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
        yyerrok;
    }
#line 1537 "parser.tab.c"
    break;

  case 24: /* end_clause: END error  */
#line 241 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;' or 'end <variable>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1549 "parser.tab.c"
    break;

  case 25: /* program_start: PROGRAM_START '(' ')' stmt_list end_clause  */
#line 261 "parser.y"
                                               {
        /* Standard form with parentheses and statements */
        (yyval.node) = createProgramStart((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1558 "parser.tab.c"
    break;

  case 26: /* program_start: PROGRAM_START '(' ')' end_clause  */
#line 265 "parser.y"
                                       {
        /* Empty Program_Start body */
        (yyval.node) = createProgramStart(NULL, (yyvsp[0].node));
    }
#line 1567 "parser.tab.c"
    break;

  case 27: /* program_start: PROGRAM_START error  */
#line 269 "parser.y"
                          {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed Program_Start block\n");
        fprintf(stderr, "   💡 Suggestion: Use 'Program_Start() ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1579 "parser.tab.c"
    break;

  case 28: /* stmt_list: stmt  */
#line 284 "parser.y"
         {
        /* Base case: single statement */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1588 "parser.tab.c"
    break;

  case 29: /* stmt_list: stmt_list stmt  */
#line 288 "parser.y"
                     {
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1597 "parser.tab.c"
    break;

  case 36: /* id_list: ID  */
#line 311 "parser.y"
       {
        /* Base case: single identifier */
        (yyval.node) = createIdList((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1607 "parser.tab.c"
    break;

  case 37: /* id_list: id_list ',' ID  */
#line 316 "parser.y"
                     {
        /* Recursive case: extend list */
        (yyval.node) = appendIdList((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1617 "parser.tab.c"
    break;

  case 38: /* id_list: id_list ',' error  */
#line 321 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected identifier after comma in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add a variable name after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1629 "parser.tab.c"
    break;

  case 39: /* decl: INT id_list ';'  */
#line 336 "parser.y"
                    {
        (yyval.node) = createMultiDecl((yyvsp[-1].node));
    }
#line 1637 "parser.tab.c"
    break;

  case 40: /* decl: FLOAT id_list ';'  */
#line 339 "parser.y"
                        {
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), "float");
    }
#line 1645 "parser.tab.c"
    break;

  case 41: /* decl: INT ID '[' NUM ']' ';'  */
#line 342 "parser.y"
                             {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1654 "parser.tab.c"
    break;

  case 42: /* decl: FLOAT ID '[' NUM ']' ';'  */
#line 346 "parser.y"
                               {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1663 "parser.tab.c"
    break;

  case 43: /* decl: struct_def  */
#line 350 "parser.y"
                 {
        /* Struct type definition:  struct stats { ... }  */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1672 "parser.tab.c"
    break;

  case 44: /* decl: ID id_list ';'  */
#line 354 "parser.y"
                     {
        /* Struct variable declaration:  stats playerStats;
         * (also allows "stats a, b;" via id_list)            */
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), (yyvsp[-2].str));
        free((yyvsp[-2].str));
    }
#line 1683 "parser.tab.c"
    break;

  case 45: /* decl: INT id_list error  */
#line 360 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after variable declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the identifier list\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1695 "parser.tab.c"
    break;

  case 46: /* decl: INT error  */
#line 367 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected 'int <identifier>;' or 'int x, y, z;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1707 "parser.tab.c"
    break;

  case 47: /* assign: ID '=' expr ';'  */
#line 383 "parser.y"
                    {
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1716 "parser.tab.c"
    break;

  case 48: /* assign: ID '=' func_call ';'  */
#line 387 "parser.y"
                           {
        /* Function call as RHS: z = add(x, y); */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1726 "parser.tab.c"
    break;

  case 49: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 392 "parser.y"
                                   {
    ASTNode* lhs = createArrayIndex((yyvsp[-6].str), (yyvsp[-4].node));
    ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
    node->data.assign.arrayLHS = lhs;
    (yyval.node) = node;
    free((yyvsp[-6].str));
    }
#line 1738 "parser.tab.c"
    break;

  case 50: /* assign: expr IS ID '=' expr ';'  */
#line 399 "parser.y"
                              {
        /* Struct field assignment:  playerStats is health = 10; */
        ASTNode* lhs = createStructAccess((yyvsp[-5].node), (yyvsp[-3].str));
        ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
        node->data.assign.structLHS = lhs;
        (yyval.node) = node;
        free((yyvsp[-3].str));
    }
#line 1751 "parser.tab.c"
    break;

  case 51: /* assign: ID '=' expr error  */
#line 407 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <expression>'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1764 "parser.tab.c"
    break;

  case 52: /* assign: ID '=' func_call error  */
#line 415 "parser.y"
                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after function call assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <func>(...)'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1777 "parser.tab.c"
    break;

  case 53: /* assign: ID '=' error  */
#line 423 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment\n");
        fprintf(stderr, "   💡 Suggestion: Check the expression after '=' for '%s'\n\n", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1790 "parser.tab.c"
    break;

  case 54: /* assign: ID error  */
#line 431 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement\n");
        fprintf(stderr, "   💡 Suggestion: Use '%s = <expression>;'\n\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1803 "parser.tab.c"
    break;

  case 55: /* func_call: ID '(' arg_list ')'  */
#line 448 "parser.y"
                        {
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1812 "parser.tab.c"
    break;

  case 56: /* func_call: ID '(' ')'  */
#line 452 "parser.y"
                 {
        /* No arguments */
        (yyval.node) = createFuncCall((yyvsp[-2].str), NULL);
        free((yyvsp[-2].str));
    }
#line 1822 "parser.tab.c"
    break;

  case 57: /* func_call: ID '(' arg_list error  */
#line 457 "parser.y"
                            {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing ')' in function call\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' after the argument list\n\n");
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
        yyerrok;
    }
#line 1835 "parser.tab.c"
    break;

  case 58: /* func_call: ID '(' error  */
#line 465 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid argument in function call\n");
        fprintf(stderr, "   💡 Suggestion: Use 'funcName(x, y)' or 'funcName()'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1847 "parser.tab.c"
    break;

  case 59: /* arg_list: expr  */
#line 481 "parser.y"
         {
        /* Single argument */
        (yyval.node) = createArgList((yyvsp[0].node));
    }
#line 1856 "parser.tab.c"
    break;

  case 60: /* arg_list: arg_list ',' expr  */
#line 485 "parser.y"
                        {
        /* Multiple arguments */
        (yyval.node) = appendArgList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1865 "parser.tab.c"
    break;

  case 61: /* arg_list: arg_list ',' error  */
#line 489 "parser.y"
                         {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected expression after comma in argument list\n");
        fprintf(stderr, "   💡 Suggestion: Provide a value or variable after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1877 "parser.tab.c"
    break;

  case 62: /* expr: NUM  */
#line 504 "parser.y"
        {
        /* Integer literal */
        (yyval.node) = createNum((yyvsp[0].num));
    }
#line 1886 "parser.tab.c"
    break;

  case 63: /* expr: FNUM  */
#line 508 "parser.y"
           {
        /* Float literal */
        (yyval.node) = createFloat((yyvsp[0].fnum));
    }
#line 1895 "parser.tab.c"
    break;

  case 64: /* expr: ID  */
#line 512 "parser.y"
         {
        /* Variable reference */
        (yyval.node) = createVar((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1905 "parser.tab.c"
    break;

  case 65: /* expr: expr '+' expr  */
#line 517 "parser.y"
                    {
        (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1913 "parser.tab.c"
    break;

  case 66: /* expr: expr '-' expr  */
#line 520 "parser.y"
                    {
        (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1921 "parser.tab.c"
    break;

  case 67: /* expr: expr '*' expr  */
#line 523 "parser.y"
                    {
        (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1929 "parser.tab.c"
    break;

  case 68: /* expr: expr '/' expr  */
#line 526 "parser.y"
                    {
        (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1937 "parser.tab.c"
    break;

  case 69: /* expr: '-' expr  */
#line 529 "parser.y"
                            {
        (yyval.node) = createBinOp('u', (yyvsp[0].node), NULL);
    }
#line 1945 "parser.tab.c"
    break;

  case 70: /* expr: '(' expr ')'  */
#line 532 "parser.y"
                   {
        /* Parenthesized expression */
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1954 "parser.tab.c"
    break;

  case 71: /* expr: ID '[' expr ']'  */
#line 536 "parser.y"
                      {
        (yyval.node) = createArrayIndex((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1963 "parser.tab.c"
    break;

  case 72: /* expr: expr IS ID  */
#line 540 "parser.y"
                 {
        /* Struct field access (rvalue):  playerStats is health */
        (yyval.node) = createStructAccess((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1973 "parser.tab.c"
    break;

  case 73: /* struct_def: STRUCT ID '{' field_body '}'  */
#line 556 "parser.y"
                                 {
        (yyval.node) = createStructDef((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1982 "parser.tab.c"
    break;

  case 74: /* field_body: field_item  */
#line 563 "parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1990 "parser.tab.c"
    break;

  case 75: /* field_body: field_body field_item  */
#line 566 "parser.y"
                            {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1998 "parser.tab.c"
    break;

  case 76: /* field_item: INT ID ';'  */
#line 572 "parser.y"
               {
        (yyval.node) = createDecl("int", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2007 "parser.tab.c"
    break;

  case 77: /* field_item: FLOAT ID ';'  */
#line 576 "parser.y"
                   {
        (yyval.node) = createDecl("float", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2016 "parser.tab.c"
    break;

  case 78: /* field_item: INT ID '[' NUM ']' ';'  */
#line 580 "parser.y"
                             {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "int");
        free((yyvsp[-4].str));
    }
#line 2025 "parser.tab.c"
    break;

  case 79: /* field_item: FLOAT ID '[' NUM ']' ';'  */
#line 584 "parser.y"
                               {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "float");
        free((yyvsp[-4].str));
    }
#line 2034 "parser.tab.c"
    break;

  case 80: /* field_item: ID '=' expr ';'  */
#line 588 "parser.y"
                      {
        /* Default field value, e.g. "health = 10;" */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2044 "parser.tab.c"
    break;

  case 81: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 601 "parser.y"
                           {
        (yyval.node) = createPrint((yyvsp[-2].node));
    }
#line 2052 "parser.tab.c"
    break;

  case 82: /* print_stmt: PRINT '(' expr ')' error  */
#line 604 "parser.y"
                               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after 'print(<expression>)'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2064 "parser.tab.c"
    break;

  case 83: /* print_stmt: PRINT '(' expr error  */
#line 611 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' before semicolon\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2076 "parser.tab.c"
    break;

  case 84: /* print_stmt: PRINT '(' error  */
#line 618 "parser.y"
                      {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2088 "parser.tab.c"
    break;

  case 85: /* print_stmt: PRINT error  */
#line 625 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2100 "parser.tab.c"
    break;

  case 86: /* if_stmt: IF '(' condition ')' '{' stmt_list '}'  */
#line 642 "parser.y"
                                                                 {
        (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-1].node), NULL);
    }
#line 2108 "parser.tab.c"
    break;

  case 87: /* if_stmt: IF '(' condition ')' '{' '}'  */
#line 645 "parser.y"
                                                         {
        (yyval.node) = createIf((yyvsp[-3].node), NULL, NULL);
    }
#line 2116 "parser.tab.c"
    break;

  case 88: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' stmt_list '}'  */
#line 648 "parser.y"
                                                                    {
        (yyval.node) = createIf((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node));
    }
#line 2124 "parser.tab.c"
    break;

  case 89: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' stmt_list '}'  */
#line 651 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), NULL, (yyvsp[-1].node));
    }
#line 2132 "parser.tab.c"
    break;

  case 90: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' '}'  */
#line 654 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), (yyvsp[-4].node), NULL);
    }
#line 2140 "parser.tab.c"
    break;

  case 91: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' '}'  */
#line 657 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-6].node), NULL, NULL);
    }
#line 2148 "parser.tab.c"
    break;

  case 92: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE if_stmt  */
#line 660 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 2156 "parser.tab.c"
    break;

  case 93: /* if_stmt: IF '(' condition ')' '{' '}' ELSE if_stmt  */
#line 663 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-5].node), NULL, (yyvsp[0].node));
    }
#line 2164 "parser.tab.c"
    break;

  case 94: /* if_stmt: IF error  */
#line 666 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed if statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'if (<condition>) { ... }'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2176 "parser.tab.c"
    break;

  case 95: /* while_stmt: WHILE '(' condition ')' stmt_list CONTINUE ';'  */
#line 682 "parser.y"
                                                   {
        (yyval.node) = createWhile((yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2184 "parser.tab.c"
    break;

  case 96: /* while_stmt: WHILE '(' assign_init ';' condition ';' assign_init ')' stmt_list CONTINUE ';'  */
#line 685 "parser.y"
                                                                                     {
        (yyval.node) = createForWhile((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2192 "parser.tab.c"
    break;

  case 97: /* while_stmt: WHILE error  */
#line 688 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed while loop\n");
        fprintf(stderr, "   💡 Suggestion: Use 'while (<condition>) ... continue;'\n");
        fprintf(stderr, "                  or 'while (i = 0; i < 10; i = i + 1) ... continue;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2205 "parser.tab.c"
    break;

  case 98: /* assign_init: ID '=' expr  */
#line 701 "parser.y"
                {
        (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 2214 "parser.tab.c"
    break;

  case 99: /* condition: expr RELOP expr  */
#line 709 "parser.y"
                    {
        (yyval.node) = createBinOp((char)(yyvsp[-1].num), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2222 "parser.tab.c"
    break;


#line 2226 "parser.tab.c"

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

#line 714 "parser.y"


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
