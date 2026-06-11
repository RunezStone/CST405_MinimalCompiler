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
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_PRINT = 9,                      /* PRINT  */
  YYSYMBOL_FUNC = 10,                      /* FUNC  */
  YYSYMBOL_PROGRAM_START = 11,             /* PROGRAM_START  */
  YYSYMBOL_END = 12,                       /* END  */
  YYSYMBOL_NULLTOK = 13,                   /* NULLTOK  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_CONTINUE = 15,                  /* CONTINUE  */
  YYSYMBOL_STRUCT = 16,                    /* STRUCT  */
  YYSYMBOL_IS = 17,                        /* IS  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_RELOP = 20,                     /* RELOP  */
  YYSYMBOL_LOWER_THAN_ELSE = 21,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_22_ = 22,                       /* '+'  */
  YYSYMBOL_23_ = 23,                       /* '-'  */
  YYSYMBOL_24_ = 24,                       /* '*'  */
  YYSYMBOL_25_ = 25,                       /* '/'  */
  YYSYMBOL_UMINUS = 26,                    /* UMINUS  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* ','  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* '['  */
  YYSYMBOL_32_ = 32,                       /* ']'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* '{'  */
  YYSYMBOL_35_ = 35,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_global_list = 38,               /* global_list  */
  YYSYMBOL_func_decl_list = 39,            /* func_decl_list  */
  YYSYMBOL_func_decl = 40,                 /* func_decl  */
  YYSYMBOL_param_list = 41,                /* param_list  */
  YYSYMBOL_param_item = 42,                /* param_item  */
  YYSYMBOL_end_clause = 43,                /* end_clause  */
  YYSYMBOL_program_start = 44,             /* program_start  */
  YYSYMBOL_stmt_list = 45,                 /* stmt_list  */
  YYSYMBOL_stmt = 46,                      /* stmt  */
  YYSYMBOL_id_list = 47,                   /* id_list  */
  YYSYMBOL_decl = 48,                      /* decl  */
  YYSYMBOL_assign = 49,                    /* assign  */
  YYSYMBOL_func_call = 50,                 /* func_call  */
  YYSYMBOL_arg_list = 51,                  /* arg_list  */
  YYSYMBOL_expr = 52,                      /* expr  */
  YYSYMBOL_struct_def = 53,                /* struct_def  */
  YYSYMBOL_field_body = 54,                /* field_body  */
  YYSYMBOL_field_item = 55,                /* field_item  */
  YYSYMBOL_print_stmt = 56,                /* print_stmt  */
  YYSYMBOL_if_stmt = 57,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 58,                /* while_stmt  */
  YYSYMBOL_assign_init = 59,               /* assign_init  */
  YYSYMBOL_condition = 60                  /* condition  */
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
#define YYLAST   476

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      27,    28,    24,    22,    29,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    85,    85,    89,   101,   104,   115,   119,   132,   137,
     142,   147,   152,   167,   172,   176,   187,   191,   195,   212,
     216,   221,   227,   234,   242,   262,   266,   270,   285,   289,
     297,   298,   299,   300,   301,   302,   312,   317,   322,   337,
     340,   343,   347,   351,   355,   361,   368,   384,   388,   393,
     400,   408,   416,   424,   432,   449,   453,   458,   466,   482,
     486,   490,   505,   509,   513,   518,   523,   526,   529,   532,
     535,   538,   542,   546,   562,   569,   572,   578,   582,   586,
     590,   594,   607,   610,   617,   624,   631,   648,   651,   654,
     657,   660,   663,   666,   669,   672,   688,   691,   694,   707,
     715
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
  "STRING", "INT", "FLOAT", "PRINT", "FUNC", "PROGRAM_START", "END",
  "NULLTOK", "WHILE", "CONTINUE", "STRUCT", "IS", "IF", "ELSE", "RELOP",
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

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-66)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -167,    19,   443,  -167,    21,    11,    54,    73,    27,    77,
     101,  -167,  -167,  -167,  -167,  -167,   110,  -167,    41,    13,
      62,   152,  -167,    75,  -167,    90,    97,  -167,  -167,    86,
    -167,   132,  -167,  -167,   160,  -167,    69,   393,   179,  -167,
    -167,   123,   140,   172,   183,   193,   393,   178,  -167,  -167,
    -167,    84,  -167,    31,    85,    56,    67,   122,   122,   200,
     393,  -167,  -167,  -167,   129,  -167,  -167,  -167,   169,   199,
     208,     1,  -167,   195,   197,  -167,  -167,  -167,   198,   393,
     393,    14,  -167,   122,   287,  -167,   312,  -167,   218,    16,
      17,  -167,   156,  -167,   122,   192,  -167,   438,   229,  -167,
     233,   122,   122,   122,   122,   122,   181,   201,  -167,  -167,
    -167,  -167,   223,   226,   393,   172,  -167,   308,  -167,    68,
      23,    99,  -167,   119,  -167,  -167,  -167,  -167,  -167,   142,
     447,   220,   224,   234,   122,   249,  -167,   228,   113,   113,
     256,   256,   404,  -167,   260,  -167,   272,   246,   244,   278,
    -167,  -167,  -167,  -167,  -167,    26,   122,   122,   122,   393,
     252,   400,  -167,   122,  -167,   255,   263,   122,  -167,  -167,
       9,   451,  -167,  -167,   451,   451,   264,  -167,   343,    57,
    -167,   413,   266,   268,   422,  -167,  -167,   318,   294,   270,
     283,   162,  -167,  -167,  -167,  -167,  -167,   451,   271,   275,
    -167,   -11,   288,   393,   187,  -167,    -5,   368,  -167,   212,
     237,  -167,   279,  -167,  -167,   262,  -167,  -167
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
      63,     0,    64,     0,     0,     0,     0,     0,     0,    35,
       0,    28,    30,    31,     0,    32,    34,    33,     0,     0,
       0,     0,    75,     0,     0,    18,    16,    17,    35,     0,
       0,     0,    54,     0,     0,    86,     0,    24,     0,     0,
       0,    98,     0,    95,     0,    65,    70,     0,    35,    29,
       0,     0,     0,     0,     0,     0,     0,     0,    74,    76,
      41,    42,    35,    35,     0,    15,    14,     0,    53,    65,
       0,     0,    85,     0,    21,    23,    20,    22,    19,    65,
       0,     0,     0,     0,     0,     0,    71,    73,    66,    67,
      68,    69,     0,    77,     0,    78,     0,    35,    72,     0,
      52,    48,    51,    47,    84,     0,     0,     0,     0,     0,
       0,     0,    73,     0,    81,     0,     0,     0,    58,    56,
       0,    59,    83,    82,    99,   100,     0,    35,     0,     0,
      72,     0,     0,     0,     0,    57,    55,     0,     0,     0,
      88,     0,    50,    79,    80,    49,    61,    60,     0,     0,
      96,     0,    87,     0,     0,    94,     0,     0,    92,     0,
       0,    93,     0,    90,    91,     0,    97,    89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,  -167,   298,  -167,   230,   -35,   302,   -46,
     -59,   253,   324,  -167,  -167,  -167,   -53,  -167,  -167,   257,
    -167,  -166,  -167,   139,   -91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    10,    11,    47,    48,   177,    12,    60,
      61,    16,    62,    63,   120,   170,    64,    14,    71,    72,
      65,    66,    67,   131,   132
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    99,    59,   133,    96,    97,    68,    56,    69,    70,
     185,    78,    17,    56,    32,   115,    18,   125,   127,     3,
      99,    44,    45,   204,   150,    98,    15,   172,    24,   210,
     117,   121,    85,   123,   114,   205,   108,   186,   187,   130,
     211,   130,    29,    33,   112,   113,   126,   128,   138,   139,
     140,   141,   142,   151,    25,    99,   173,    91,    86,    20,
      49,    50,    51,    52,     5,     6,    53,   176,    93,    54,
      43,    55,    31,     9,    22,    56,    44,    45,    23,   147,
      57,   161,    26,    92,    58,    82,    87,    39,    88,    15,
      89,    40,   190,    34,    94,   149,   171,    46,    90,   134,
     152,   -65,    36,   174,   175,   130,   -65,   -65,   -65,   -65,
     181,     7,     8,   178,   184,    83,   135,    84,    37,    99,
     154,   101,   102,   103,   104,    49,    50,    95,    52,   153,
     135,    38,    99,   191,   197,    41,   135,   103,   104,    29,
      30,   101,   102,   103,   104,    57,   100,   155,    99,    58,
      99,   101,   102,   103,   104,    73,    99,   207,   209,    49,
      50,   129,    52,    42,   215,    49,    50,    51,    52,     5,
       6,    53,    74,   134,    54,   156,    55,    75,     9,    57,
      56,    29,    35,    58,    68,    57,    69,    70,    76,    58,
      49,    50,    51,    52,     5,     6,    53,   202,    77,    54,
     -26,    55,   105,     9,   106,    56,    80,    81,   -11,   -11,
      57,   143,   144,   107,    58,    49,    50,    51,    52,     5,
       6,    53,   208,   134,    54,   110,    55,   111,     9,   -25,
      56,   145,   146,    -9,    -9,    57,   -10,   -10,   137,    58,
      49,    50,    51,    52,     5,     6,    53,   213,   124,    54,
     158,    55,   159,     9,   162,    56,    -8,    -8,    19,    21,
      57,   163,   160,   165,    58,    49,    50,    51,    52,     5,
       6,    53,   214,   135,    54,   166,    55,   167,     9,   168,
      56,    49,    50,    95,    52,    57,   179,   182,   118,    58,
      49,    50,   119,    52,   188,   183,   193,   217,   194,   198,
     200,    57,   201,   203,   156,    58,   169,   206,    27,   216,
      57,   116,    28,   122,    58,    49,    50,    95,    52,   196,
       0,    49,    50,    95,    52,   135,    13,   199,   109,     0,
     101,   102,   103,   104,     0,    57,     0,     0,     0,    58,
     148,    57,     0,     0,     0,    58,    49,    50,    51,    52,
       5,     6,    53,     0,     0,    54,     0,    55,   189,     9,
       0,    56,     0,     0,     0,     0,    57,     0,     0,     0,
      58,    49,    50,    51,    52,     5,     6,    53,     0,     0,
      54,     0,    55,   212,     9,     0,    56,     0,     0,     0,
       0,    57,     0,     0,     0,    58,    49,    50,    51,    52,
       5,     6,    53,     0,     0,    54,     0,    55,     0,     9,
       0,    56,     0,     0,     0,     0,    57,   135,     0,     0,
      58,   135,   101,   102,   103,   104,   101,   102,   103,   104,
     135,     0,   180,     0,   164,   101,   102,   103,   104,   135,
       0,     0,     0,   192,   101,   102,   103,   104,     4,     0,
       5,     6,   195,     7,     8,   135,     0,     0,     0,     9,
     101,   102,   103,   104,   135,     0,   136,   157,   135,   101,
     102,   103,   104,   101,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
      46,    60,    37,    94,    57,    58,     5,    18,     7,     8,
       1,    46,     1,    18,     1,     1,     5,     1,     1,     0,
      79,     7,     8,    34,     1,    60,     5,     1,     1,    34,
      83,    84,     1,    86,    80,   201,    35,    28,    29,    92,
     206,    94,    29,    30,    79,    80,    30,    30,   101,   102,
     103,   104,   105,    30,    27,   114,    30,     1,    27,     5,
       3,     4,     5,     6,     7,     8,     9,   158,     1,    12,
       1,    14,    31,    16,     1,    18,     7,     8,     5,   114,
      23,   134,     5,    27,    27,     1,     1,     1,     3,     5,
       5,     5,    35,    31,    27,    27,   149,    28,    13,    31,
       1,    17,    27,   156,   157,   158,    22,    23,    24,    25,
     163,    10,    11,   159,   167,    31,    17,    33,    28,   178,
       1,    22,    23,    24,    25,     3,     4,     5,     6,    30,
      17,    34,   191,   179,   187,     3,    17,    24,    25,    29,
      30,    22,    23,    24,    25,    23,    17,    28,   207,    27,
     209,    22,    23,    24,    25,    32,   215,   203,   204,     3,
       4,     5,     6,     3,   210,     3,     4,     5,     6,     7,
       8,     9,    32,    31,    12,    33,    14,     5,    16,    23,
      18,    29,    30,    27,     5,    23,     7,     8,     5,    27,
       3,     4,     5,     6,     7,     8,     9,    35,     5,    12,
       0,    14,    33,    16,     5,    18,    28,    29,    10,    11,
      23,    30,    31,     5,    27,     3,     4,     5,     6,     7,
       8,     9,    35,    31,    12,    30,    14,    30,    16,     0,
      18,    30,    31,    10,    11,    23,    10,    11,     5,    27,
       3,     4,     5,     6,     7,     8,     9,    35,    30,    12,
      30,    14,    28,    16,     5,    18,    10,    11,     5,     6,
      23,    33,    28,     3,    27,     3,     4,     5,     6,     7,
       8,     9,    35,    17,    12,     3,    14,    33,    16,     1,
      18,     3,     4,     5,     6,    23,    34,    32,     1,    27,
       3,     4,     5,     6,    30,    32,    30,    35,    30,     5,
      30,    23,    19,    28,    33,    27,    28,    19,    10,    30,
      23,    81,    10,     1,    27,     3,     4,     5,     6,     1,
      -1,     3,     4,     5,     6,    17,     2,   188,    71,    -1,
      22,    23,    24,    25,    -1,    23,    -1,    -1,    -1,    27,
      32,    23,    -1,    -1,    -1,    27,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    12,    -1,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      12,    -1,    14,    15,    16,    -1,    18,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    27,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    12,    -1,    14,    -1,    16,
      -1,    18,    -1,    -1,    -1,    -1,    23,    17,    -1,    -1,
      27,    17,    22,    23,    24,    25,    22,    23,    24,    25,
      17,    -1,    32,    -1,    30,    22,    23,    24,    25,    17,
      -1,    -1,    -1,    30,    22,    23,    24,    25,     5,    -1,
       7,     8,    30,    10,    11,    17,    -1,    -1,    -1,    16,
      22,    23,    24,    25,    17,    -1,    28,    20,    17,    22,
      23,    24,    25,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,    38,     0,     5,     7,     8,    10,    11,    16,
      39,    40,    44,    48,    53,     5,    47,     1,     5,    47,
       5,    47,     1,     5,     1,    27,     5,    40,    44,    29,
      30,    31,     1,    30,    31,    30,    27,    28,    34,     1,
       5,     3,     3,     1,     7,     8,    28,    41,    42,     3,
       4,     5,     6,     9,    12,    14,    18,    23,    27,    43,
      45,    46,    48,    49,    52,    56,    57,    58,     5,     7,
       8,    54,    55,    32,    32,     5,     5,     5,    43,    45,
      28,    29,     1,    31,    33,     1,    27,     1,     3,     5,
      13,     1,    27,     1,    27,     5,    52,    52,    43,    46,
      17,    22,    23,    24,    25,    33,     5,     5,    35,    55,
      30,    30,    43,    43,    45,     1,    42,    52,     1,     5,
      50,    52,     1,    52,    30,     1,    30,     1,    30,     5,
      52,    59,    60,    60,    31,    17,    28,     5,    52,    52,
      52,    52,    52,    30,    31,    30,    31,    43,    32,    27,
       1,    30,     1,    30,     1,    28,    33,    20,    30,    28,
      28,    52,     5,    33,    30,     3,     3,    33,     1,    28,
      51,    52,     1,    30,    52,    52,    60,    43,    45,    34,
      32,    52,    32,    32,    52,     1,    28,    29,    30,    15,
      35,    45,    30,    30,    30,    30,     1,    52,     5,    59,
      30,    19,    35,    28,    34,    57,    19,    45,    35,    45,
      34,    57,    15,    35,    35,    45,    30,    35
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    39,    39,    40,    40,
      40,    40,    40,    41,    41,    41,    42,    42,    42,    43,
      43,    43,    43,    43,    43,    44,    44,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    47,    47,    47,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    50,    50,    50,    50,    51,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    54,    55,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    58,    59,
      60
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
       3,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       2,     3,     4,     3,     5,     1,     2,     3,     3,     6,
       6,     4,     5,     5,     4,     3,     2,     7,     6,    11,
      10,    10,     9,     9,     8,     2,     7,    11,     2,     3,
       3
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
#line 85 "parser.y"
                                             {
        /* Full program: globals, functions, then entry point */
        root = createProgram((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1335 "parser.tab.c"
    break;

  case 3: /* program: global_list program_start  */
#line 89 "parser.y"
                                {
        /* No functions — just globals then Program_Start */
        root = createProgram((yyvsp[-1].node), NULL, (yyvsp[0].node));
    }
#line 1344 "parser.tab.c"
    break;

  case 4: /* global_list: %empty  */
#line 101 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1352 "parser.tab.c"
    break;

  case 5: /* global_list: global_list decl  */
#line 104 "parser.y"
                       {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1360 "parser.tab.c"
    break;

  case 6: /* func_decl_list: func_decl  */
#line 115 "parser.y"
              {
        /* Base case: single function */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1369 "parser.tab.c"
    break;

  case 7: /* func_decl_list: func_decl_list func_decl  */
#line 119 "parser.y"
                               {
        /* Multiple functions: build a list */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1378 "parser.tab.c"
    break;

  case 8: /* func_decl: FUNC ID '(' param_list ')' stmt_list end_clause  */
#line 132 "parser.y"
                                                    {
        /* Function with parameters */
        (yyval.node) = createFuncDecl((yyvsp[-5].str), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-5].str));
    }
#line 1388 "parser.tab.c"
    break;

  case 9: /* func_decl: FUNC ID '(' ')' stmt_list end_clause  */
#line 137 "parser.y"
                                           {
        /* Function with no parameters */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), NULL, (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1398 "parser.tab.c"
    break;

  case 10: /* func_decl: FUNC ID '(' param_list ')' end_clause  */
#line 142 "parser.y"
                                            {
        /* Function with params but empty body */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), (yyvsp[-2].node), NULL, (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1408 "parser.tab.c"
    break;

  case 11: /* func_decl: FUNC ID '(' ')' end_clause  */
#line 147 "parser.y"
                                 {
        /* Function with no params and empty body */
        (yyval.node) = createFuncDecl((yyvsp[-3].str), NULL, NULL, (yyvsp[0].node));
        free((yyvsp[-3].str));
    }
#line 1418 "parser.tab.c"
    break;

  case 12: /* func_decl: FUNC error  */
#line 152 "parser.y"
                 {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed function declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'func name(int a, int b) ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1430 "parser.tab.c"
    break;

  case 13: /* param_list: param_item  */
#line 167 "parser.y"
               {
        /* Single parameter — wrap in NODE_PARAM_LIST so appendParamList
         * always receives a list head, never a raw NODE_PARAM */
        (yyval.node) = createParamList((yyvsp[0].node), NULL);
    }
#line 1440 "parser.tab.c"
    break;

  case 14: /* param_list: param_list ',' param_item  */
#line 172 "parser.y"
                                {
        /* Multiple parameters */
        (yyval.node) = appendParamList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1449 "parser.tab.c"
    break;

  case 15: /* param_list: param_list ',' error  */
#line 176 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'int <name>' after comma in parameter list\n");
        fprintf(stderr, "   💡 Suggestion: Each parameter must have a type, e.g. 'int x'\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1461 "parser.tab.c"
    break;

  case 16: /* param_item: INT ID  */
#line 187 "parser.y"
           {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1470 "parser.tab.c"
    break;

  case 17: /* param_item: FLOAT ID  */
#line 191 "parser.y"
               {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1479 "parser.tab.c"
    break;

  case 18: /* param_item: error ID  */
#line 195 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing type in parameter declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'int %s' instead of just '%s'\n\n", (yyvsp[0].str), (yyvsp[0].str));
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
        yyerrok;
    }
#line 1492 "parser.tab.c"
    break;

  case 19: /* end_clause: END NULLTOK ';'  */
#line 212 "parser.y"
                    {
        /* Void return — function returns nothing */
        (yyval.node) = createEndClause(NULL);
    }
#line 1501 "parser.tab.c"
    break;

  case 20: /* end_clause: END ID ';'  */
#line 216 "parser.y"
                 {
        /* Return a variable's value */
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1511 "parser.tab.c"
    break;

  case 21: /* end_clause: END NUM ';'  */
#line 221 "parser.y"
                  {
        /* Return an integer literal — e.g. end 1; end 0; */
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", (yyvsp[-1].num));
        (yyval.node) = createEndClause(buf);
    }
#line 1522 "parser.tab.c"
    break;

  case 22: /* end_clause: END NULLTOK error  */
#line 227 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after 'end null'\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;'\n\n");
        (yyval.node) = createEndClause(NULL);
        yyerrok;
    }
#line 1534 "parser.tab.c"
    break;

  case 23: /* end_clause: END ID error  */
#line 234 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end %s;'\n\n", (yyvsp[-1].str));
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
        yyerrok;
    }
#line 1547 "parser.tab.c"
    break;

  case 24: /* end_clause: END error  */
#line 242 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;' or 'end <variable>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1559 "parser.tab.c"
    break;

  case 25: /* program_start: PROGRAM_START '(' ')' stmt_list end_clause  */
#line 262 "parser.y"
                                               {
        /* Standard form with parentheses and statements */
        (yyval.node) = createProgramStart((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1568 "parser.tab.c"
    break;

  case 26: /* program_start: PROGRAM_START '(' ')' end_clause  */
#line 266 "parser.y"
                                       {
        /* Empty Program_Start body */
        (yyval.node) = createProgramStart(NULL, (yyvsp[0].node));
    }
#line 1577 "parser.tab.c"
    break;

  case 27: /* program_start: PROGRAM_START error  */
#line 270 "parser.y"
                          {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed Program_Start block\n");
        fprintf(stderr, "   💡 Suggestion: Use 'Program_Start() ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1589 "parser.tab.c"
    break;

  case 28: /* stmt_list: stmt  */
#line 285 "parser.y"
         {
        /* Base case: single statement */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1598 "parser.tab.c"
    break;

  case 29: /* stmt_list: stmt_list stmt  */
#line 289 "parser.y"
                     {
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1607 "parser.tab.c"
    break;

  case 36: /* id_list: ID  */
#line 312 "parser.y"
       {
        /* Base case: single identifier */
        (yyval.node) = createIdList((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1617 "parser.tab.c"
    break;

  case 37: /* id_list: id_list ',' ID  */
#line 317 "parser.y"
                     {
        /* Recursive case: extend list */
        (yyval.node) = appendIdList((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1627 "parser.tab.c"
    break;

  case 38: /* id_list: id_list ',' error  */
#line 322 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected identifier after comma in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add a variable name after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1639 "parser.tab.c"
    break;

  case 39: /* decl: INT id_list ';'  */
#line 337 "parser.y"
                    {
        (yyval.node) = createMultiDecl((yyvsp[-1].node));
    }
#line 1647 "parser.tab.c"
    break;

  case 40: /* decl: FLOAT id_list ';'  */
#line 340 "parser.y"
                        {
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), "float");
    }
#line 1655 "parser.tab.c"
    break;

  case 41: /* decl: INT ID '[' NUM ']' ';'  */
#line 343 "parser.y"
                             {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1664 "parser.tab.c"
    break;

  case 42: /* decl: FLOAT ID '[' NUM ']' ';'  */
#line 347 "parser.y"
                               {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1673 "parser.tab.c"
    break;

  case 43: /* decl: struct_def  */
#line 351 "parser.y"
                 {
        /* Struct type definition:  struct stats { ... }  */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1682 "parser.tab.c"
    break;

  case 44: /* decl: ID id_list ';'  */
#line 355 "parser.y"
                     {
        /* Struct variable declaration:  stats playerStats;
         * (also allows "stats a, b;" via id_list)            */
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), (yyvsp[-2].str));
        free((yyvsp[-2].str));
    }
#line 1693 "parser.tab.c"
    break;

  case 45: /* decl: INT id_list error  */
#line 361 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after variable declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the identifier list\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1705 "parser.tab.c"
    break;

  case 46: /* decl: INT error  */
#line 368 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected 'int <identifier>;' or 'int x, y, z;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1717 "parser.tab.c"
    break;

  case 47: /* assign: ID '=' expr ';'  */
#line 384 "parser.y"
                    {
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1726 "parser.tab.c"
    break;

  case 48: /* assign: ID '=' func_call ';'  */
#line 388 "parser.y"
                           {
        /* Function call as RHS: z = add(x, y); */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1736 "parser.tab.c"
    break;

  case 49: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 393 "parser.y"
                                   {
    ASTNode* lhs = createArrayIndex((yyvsp[-6].str), (yyvsp[-4].node));
    ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
    node->data.assign.arrayLHS = lhs;
    (yyval.node) = node;
    free((yyvsp[-6].str));
    }
#line 1748 "parser.tab.c"
    break;

  case 50: /* assign: expr IS ID '=' expr ';'  */
#line 400 "parser.y"
                              {
        /* Struct field assignment:  playerStats is health = 10; */
        ASTNode* lhs = createStructAccess((yyvsp[-5].node), (yyvsp[-3].str));
        ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
        node->data.assign.structLHS = lhs;
        (yyval.node) = node;
        free((yyvsp[-3].str));
    }
#line 1761 "parser.tab.c"
    break;

  case 51: /* assign: ID '=' expr error  */
#line 408 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <expression>'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1774 "parser.tab.c"
    break;

  case 52: /* assign: ID '=' func_call error  */
#line 416 "parser.y"
                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after function call assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <func>(...)'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1787 "parser.tab.c"
    break;

  case 53: /* assign: ID '=' error  */
#line 424 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment\n");
        fprintf(stderr, "   💡 Suggestion: Check the expression after '=' for '%s'\n\n", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1800 "parser.tab.c"
    break;

  case 54: /* assign: ID error  */
#line 432 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement\n");
        fprintf(stderr, "   💡 Suggestion: Use '%s = <expression>;'\n\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1813 "parser.tab.c"
    break;

  case 55: /* func_call: ID '(' arg_list ')'  */
#line 449 "parser.y"
                        {
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1822 "parser.tab.c"
    break;

  case 56: /* func_call: ID '(' ')'  */
#line 453 "parser.y"
                 {
        /* No arguments */
        (yyval.node) = createFuncCall((yyvsp[-2].str), NULL);
        free((yyvsp[-2].str));
    }
#line 1832 "parser.tab.c"
    break;

  case 57: /* func_call: ID '(' arg_list error  */
#line 458 "parser.y"
                            {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing ')' in function call\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' after the argument list\n\n");
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
        yyerrok;
    }
#line 1845 "parser.tab.c"
    break;

  case 58: /* func_call: ID '(' error  */
#line 466 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid argument in function call\n");
        fprintf(stderr, "   💡 Suggestion: Use 'funcName(x, y)' or 'funcName()'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1857 "parser.tab.c"
    break;

  case 59: /* arg_list: expr  */
#line 482 "parser.y"
         {
        /* Single argument */
        (yyval.node) = createArgList((yyvsp[0].node));
    }
#line 1866 "parser.tab.c"
    break;

  case 60: /* arg_list: arg_list ',' expr  */
#line 486 "parser.y"
                        {
        /* Multiple arguments */
        (yyval.node) = appendArgList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1875 "parser.tab.c"
    break;

  case 61: /* arg_list: arg_list ',' error  */
#line 490 "parser.y"
                         {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected expression after comma in argument list\n");
        fprintf(stderr, "   💡 Suggestion: Provide a value or variable after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1887 "parser.tab.c"
    break;

  case 62: /* expr: NUM  */
#line 505 "parser.y"
        {
        /* Integer literal */
        (yyval.node) = createNum((yyvsp[0].num));
    }
#line 1896 "parser.tab.c"
    break;

  case 63: /* expr: FNUM  */
#line 509 "parser.y"
           {
        /* Float literal */
        (yyval.node) = createFloat((yyvsp[0].fnum));
    }
#line 1905 "parser.tab.c"
    break;

  case 64: /* expr: STRING  */
#line 513 "parser.y"
             {
        /* String literal */
        (yyval.node) = createString((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1915 "parser.tab.c"
    break;

  case 65: /* expr: ID  */
#line 518 "parser.y"
         {
        /* Variable reference */
        (yyval.node) = createVar((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1925 "parser.tab.c"
    break;

  case 66: /* expr: expr '+' expr  */
#line 523 "parser.y"
                    {
        (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1933 "parser.tab.c"
    break;

  case 67: /* expr: expr '-' expr  */
#line 526 "parser.y"
                    {
        (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1941 "parser.tab.c"
    break;

  case 68: /* expr: expr '*' expr  */
#line 529 "parser.y"
                    {
        (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1949 "parser.tab.c"
    break;

  case 69: /* expr: expr '/' expr  */
#line 532 "parser.y"
                    {
        (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1957 "parser.tab.c"
    break;

  case 70: /* expr: '-' expr  */
#line 535 "parser.y"
                            {
        (yyval.node) = createBinOp('u', (yyvsp[0].node), NULL);
    }
#line 1965 "parser.tab.c"
    break;

  case 71: /* expr: '(' expr ')'  */
#line 538 "parser.y"
                   {
        /* Parenthesized expression */
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1974 "parser.tab.c"
    break;

  case 72: /* expr: ID '[' expr ']'  */
#line 542 "parser.y"
                      {
        (yyval.node) = createArrayIndex((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1983 "parser.tab.c"
    break;

  case 73: /* expr: expr IS ID  */
#line 546 "parser.y"
                 {
        /* Struct field access (rvalue):  playerStats is health */
        (yyval.node) = createStructAccess((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1993 "parser.tab.c"
    break;

  case 74: /* struct_def: STRUCT ID '{' field_body '}'  */
#line 562 "parser.y"
                                 {
        (yyval.node) = createStructDef((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2002 "parser.tab.c"
    break;

  case 75: /* field_body: field_item  */
#line 569 "parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2010 "parser.tab.c"
    break;

  case 76: /* field_body: field_body field_item  */
#line 572 "parser.y"
                            {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2018 "parser.tab.c"
    break;

  case 77: /* field_item: INT ID ';'  */
#line 578 "parser.y"
               {
        (yyval.node) = createDecl("int", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2027 "parser.tab.c"
    break;

  case 78: /* field_item: FLOAT ID ';'  */
#line 582 "parser.y"
                   {
        (yyval.node) = createDecl("float", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2036 "parser.tab.c"
    break;

  case 79: /* field_item: INT ID '[' NUM ']' ';'  */
#line 586 "parser.y"
                             {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "int");
        free((yyvsp[-4].str));
    }
#line 2045 "parser.tab.c"
    break;

  case 80: /* field_item: FLOAT ID '[' NUM ']' ';'  */
#line 590 "parser.y"
                               {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "float");
        free((yyvsp[-4].str));
    }
#line 2054 "parser.tab.c"
    break;

  case 81: /* field_item: ID '=' expr ';'  */
#line 594 "parser.y"
                      {
        /* Default field value, e.g. "health = 10;" */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2064 "parser.tab.c"
    break;

  case 82: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 607 "parser.y"
                           {
        (yyval.node) = createPrint((yyvsp[-2].node));
    }
#line 2072 "parser.tab.c"
    break;

  case 83: /* print_stmt: PRINT '(' expr ')' error  */
#line 610 "parser.y"
                               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after 'print(<expression>)'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2084 "parser.tab.c"
    break;

  case 84: /* print_stmt: PRINT '(' expr error  */
#line 617 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' before semicolon\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2096 "parser.tab.c"
    break;

  case 85: /* print_stmt: PRINT '(' error  */
#line 624 "parser.y"
                      {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2108 "parser.tab.c"
    break;

  case 86: /* print_stmt: PRINT error  */
#line 631 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2120 "parser.tab.c"
    break;

  case 87: /* if_stmt: IF '(' condition ')' '{' stmt_list '}'  */
#line 648 "parser.y"
                                                                 {
        (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-1].node), NULL);
    }
#line 2128 "parser.tab.c"
    break;

  case 88: /* if_stmt: IF '(' condition ')' '{' '}'  */
#line 651 "parser.y"
                                                         {
        (yyval.node) = createIf((yyvsp[-3].node), NULL, NULL);
    }
#line 2136 "parser.tab.c"
    break;

  case 89: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' stmt_list '}'  */
#line 654 "parser.y"
                                                                    {
        (yyval.node) = createIf((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node));
    }
#line 2144 "parser.tab.c"
    break;

  case 90: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' stmt_list '}'  */
#line 657 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), NULL, (yyvsp[-1].node));
    }
#line 2152 "parser.tab.c"
    break;

  case 91: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' '}'  */
#line 660 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), (yyvsp[-4].node), NULL);
    }
#line 2160 "parser.tab.c"
    break;

  case 92: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' '}'  */
#line 663 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-6].node), NULL, NULL);
    }
#line 2168 "parser.tab.c"
    break;

  case 93: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE if_stmt  */
#line 666 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 2176 "parser.tab.c"
    break;

  case 94: /* if_stmt: IF '(' condition ')' '{' '}' ELSE if_stmt  */
#line 669 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-5].node), NULL, (yyvsp[0].node));
    }
#line 2184 "parser.tab.c"
    break;

  case 95: /* if_stmt: IF error  */
#line 672 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed if statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'if (<condition>) { ... }'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2196 "parser.tab.c"
    break;

  case 96: /* while_stmt: WHILE '(' condition ')' stmt_list CONTINUE ';'  */
#line 688 "parser.y"
                                                   {
        (yyval.node) = createWhile((yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2204 "parser.tab.c"
    break;

  case 97: /* while_stmt: WHILE '(' assign_init ';' condition ';' assign_init ')' stmt_list CONTINUE ';'  */
#line 691 "parser.y"
                                                                                     {
        (yyval.node) = createForWhile((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2212 "parser.tab.c"
    break;

  case 98: /* while_stmt: WHILE error  */
#line 694 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed while loop\n");
        fprintf(stderr, "   💡 Suggestion: Use 'while (<condition>) ... continue;'\n");
        fprintf(stderr, "                  or 'while (i = 0; i < 10; i = i + 1) ... continue;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2225 "parser.tab.c"
    break;

  case 99: /* assign_init: ID '=' expr  */
#line 707 "parser.y"
                {
        (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 2234 "parser.tab.c"
    break;

  case 100: /* condition: expr RELOP expr  */
#line 715 "parser.y"
                    {
        (yyval.node) = createBinOp((char)(yyvsp[-1].num), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2242 "parser.tab.c"
    break;


#line 2246 "parser.tab.c"

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

#line 720 "parser.y"


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
