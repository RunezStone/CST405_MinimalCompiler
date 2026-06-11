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
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_FUNC = 11,                      /* FUNC  */
  YYSYMBOL_PROGRAM_START = 12,             /* PROGRAM_START  */
  YYSYMBOL_END = 13,                       /* END  */
  YYSYMBOL_NULLTOK = 14,                   /* NULLTOK  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_STRUCT = 17,                    /* STRUCT  */
  YYSYMBOL_IS = 18,                        /* IS  */
  YYSYMBOL_IF = 19,                        /* IF  */
  YYSYMBOL_ELSE = 20,                      /* ELSE  */
  YYSYMBOL_SWITCH = 21,                    /* SWITCH  */
  YYSYMBOL_CASE = 22,                      /* CASE  */
  YYSYMBOL_DEFAULT = 23,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 24,                     /* BREAK  */
  YYSYMBOL_CLOSE = 25,                     /* CLOSE  */
  YYSYMBOL_CHAR_LIT = 26,                  /* CHAR_LIT  */
  YYSYMBOL_RELOP = 27,                     /* RELOP  */
  YYSYMBOL_LOWER_THAN_ELSE = 28,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_UMINUS = 33,                    /* UMINUS  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* ']'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_global_list = 46,               /* global_list  */
  YYSYMBOL_func_decl_list = 47,            /* func_decl_list  */
  YYSYMBOL_func_decl = 48,                 /* func_decl  */
  YYSYMBOL_param_list = 49,                /* param_list  */
  YYSYMBOL_param_item = 50,                /* param_item  */
  YYSYMBOL_end_clause = 51,                /* end_clause  */
  YYSYMBOL_program_start = 52,             /* program_start  */
  YYSYMBOL_stmt_list = 53,                 /* stmt_list  */
  YYSYMBOL_stmt = 54,                      /* stmt  */
  YYSYMBOL_id_list = 55,                   /* id_list  */
  YYSYMBOL_decl = 56,                      /* decl  */
  YYSYMBOL_assign = 57,                    /* assign  */
  YYSYMBOL_func_call = 58,                 /* func_call  */
  YYSYMBOL_arg_list = 59,                  /* arg_list  */
  YYSYMBOL_expr = 60,                      /* expr  */
  YYSYMBOL_struct_def = 61,                /* struct_def  */
  YYSYMBOL_field_body = 62,                /* field_body  */
  YYSYMBOL_field_item = 63,                /* field_item  */
  YYSYMBOL_print_stmt = 64,                /* print_stmt  */
  YYSYMBOL_if_stmt = 65,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 66,                /* while_stmt  */
  YYSYMBOL_assign_init = 67,               /* assign_init  */
  YYSYMBOL_condition = 68,                 /* condition  */
  YYSYMBOL_switch_stmt = 69,               /* switch_stmt  */
  YYSYMBOL_case_list = 70,                 /* case_list  */
  YYSYMBOL_case_arm = 71,                  /* case_arm  */
  YYSYMBOL_default_case = 72               /* default_case  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   682

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
      34,    35,    31,    29,    36,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    37,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      25,    26,    27,    28,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    88,    88,    92,   104,   107,   118,   122,   135,   140,
     145,   150,   155,   170,   175,   179,   190,   194,   198,   202,
     219,   223,   228,   234,   241,   249,   269,   273,   277,   292,
     296,   304,   305,   306,   307,   308,   309,   310,   320,   325,
     330,   345,   348,   351,   354,   361,   367,   373,   377,   381,
     385,   389,   395,   402,   418,   422,   427,   434,   442,   450,
     458,   466,   483,   487,   492,   500,   516,   520,   524,   539,
     543,   547,   552,   556,   561,   564,   567,   570,   573,   576,
     580,   584,   600,   607,   610,   616,   620,   624,   628,   632,
     645,   648,   655,   662,   669,   686,   689,   692,   695,   698,
     701,   704,   707,   710,   726,   729,   732,   745,   753,   768,
     774,   777,   783,   787,   791,   794,   800,   804
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
  "STRING", "INT", "FLOAT", "PRINT", "CHAR", "FUNC", "PROGRAM_START",
  "END", "NULLTOK", "WHILE", "CONTINUE", "STRUCT", "IS", "IF", "ELSE",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CLOSE", "CHAR_LIT", "RELOP",
  "LOWER_THAN_ELSE", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'('", "')'",
  "','", "';'", "'='", "'['", "']'", "'{'", "'}'", "':'", "$accept",
  "program", "global_list", "func_decl_list", "func_decl", "param_list",
  "param_item", "end_clause", "program_start", "stmt_list", "stmt",
  "id_list", "decl", "assign", "func_call", "arg_list", "expr",
  "struct_def", "field_body", "field_item", "print_stmt", "if_stmt",
  "while_stmt", "assign_init", "condition", "switch_stmt", "case_list",
  "case_arm", "default_case", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-74)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -192,    41,   659,  -192,    42,    27,    51,    89,   153,    11,
     102,   115,  -192,  -192,  -192,  -192,  -192,   180,  -192,   202,
       1,   222,   184,   242,   255,  -192,   -23,  -192,    66,    99,
    -192,  -192,   200,  -192,   564,   150,  -192,  -192,   564,   162,
    -192,   564,   164,  -192,   108,   545,   165,  -192,  -192,  -192,
    -192,   139,  -192,  -192,   564,   564,   555,   143,   583,   163,
     587,   167,   204,   213,   220,   225,   545,   265,  -192,    92,
      25,   154,    53,    68,   209,   247,   545,  -192,  -192,  -192,
     158,  -192,  -192,  -192,  -192,   218,   257,   260,    43,  -192,
     564,  -192,   627,   278,   564,   564,   564,   564,  -192,   233,
    -192,   248,  -192,   250,  -192,  -192,  -192,  -192,   320,   545,
     545,   244,  -192,   263,   564,  -192,   303,  -192,   259,     5,
       6,  -192,   577,  -192,   564,   564,   294,  -192,   293,   564,
      80,    96,  -192,  -192,   182,  -192,  -192,    82,    82,   284,
     284,  -192,  -192,  -192,   337,   365,   545,   204,  -192,  -192,
      21,     9,   107,   410,  -192,   131,  -192,  -192,  -192,  -192,
    -192,   282,   323,   268,   275,   288,   643,   287,   603,  -192,
     324,  -192,   331,  -192,   369,   223,  -192,  -192,  -192,  -192,
     298,  -192,    29,   564,   564,   564,   545,   297,   330,   564,
    -192,   300,   338,  -192,  -192,    70,   650,   564,  -192,  -192,
     650,   650,   345,  -192,   353,    10,   362,   607,   348,   349,
    -192,  -192,   341,   623,   391,   360,   379,    69,    32,   342,
    -192,  -192,  -192,  -192,  -192,   650,  -192,   363,   368,  -192,
      79,   387,   367,   370,   371,  -192,   380,   545,   189,  -192,
      93,   545,   545,   385,   375,   417,  -192,   229,   269,  -192,
     449,   481,   381,   513,  -192,   392,  -192,  -192,   309,   394,
     398,  -192,   400,  -192,  -192,  -192,  -192,  -192
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     3,     5,    50,    38,     0,    53,    38,
       0,    38,     0,    38,     0,    12,     0,    28,     0,     0,
       7,     2,     0,    51,     0,     0,    52,    41,     0,     0,
      42,     0,     0,    43,     0,     0,     0,    40,    39,    69,
      70,    73,    71,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,    37,     0,    29,    31,    32,
       0,    33,    35,    34,    36,     0,     0,     0,     0,    83,
       0,    78,     0,     0,     0,     0,     0,     0,    44,     0,
      45,     0,    46,     0,    19,    16,    17,    18,    37,     0,
       0,     0,    61,     0,     0,    94,     0,    25,     0,     0,
       0,   106,     0,   103,     0,     0,    37,    30,     0,     0,
       0,     0,    82,    84,     0,    79,    81,    74,    75,    76,
      77,    47,    48,    49,    37,    37,     0,    15,    14,    60,
      73,     0,     0,     0,    93,     0,    22,    24,    21,    23,
      20,    73,     0,     0,     0,     0,     0,    81,     0,    85,
       0,    86,     0,    80,    37,     0,    59,    55,    58,    54,
      80,    92,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,    65,    63,     0,    66,     0,    91,    90,
     107,   108,     0,    37,     0,     0,     0,     0,     0,     0,
      64,    62,     0,     0,     0,     0,    96,     0,     0,     0,
     110,    57,    87,    88,    68,    67,    56,     0,     0,   104,
       0,    95,     0,     0,     0,   111,     0,     0,     0,   102,
       0,   112,   114,     0,     0,     0,   100,     0,     0,   101,
       0,     0,     0,     0,   109,     0,    98,    99,     0,     0,
       0,   116,     0,   105,    97,   113,   115,   117
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,   397,  -192,   305,   -42,   406,   -57,
     -76,   140,   442,  -192,  -192,  -192,   -33,  -192,  -192,   357,
    -192,  -191,  -192,   232,  -120,  -192,  -192,   230,  -192
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    11,    12,    67,    68,   203,    13,    76,
      77,    17,    78,    79,   151,   195,    80,    15,    88,    89,
      81,    82,    83,   163,   164,    84,   219,   220,   236
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     127,    56,    36,    75,   165,    58,   157,   159,    60,   109,
     176,    44,    27,    49,    50,    69,    52,     5,     6,    70,
       7,    91,    92,    71,   108,    72,   115,    10,    18,    73,
     198,    74,    19,   127,   126,   232,    53,    32,    37,   239,
      54,     3,   158,   160,    55,    28,   177,    16,    85,   249,
      86,    87,   216,   146,   121,   175,    21,   134,   233,   116,
      90,   137,   138,   139,   140,   202,   199,   144,   145,   123,
     127,   210,    49,    50,    69,    52,     5,     6,    70,     7,
     152,   153,    71,   155,    72,   132,    10,   122,    73,   162,
      74,   162,   166,   112,    23,    53,   168,    16,    73,    54,
      93,    45,   124,    55,   174,   211,   212,    29,   178,    62,
     -73,   231,    73,    96,    97,    63,    64,   169,    65,   170,
     238,   -73,   -73,   -73,   -73,    93,     8,     9,   127,   204,
     113,   114,   181,   171,   248,   172,    94,    95,    96,    97,
      46,   127,   196,    66,   179,    20,    22,    24,   217,    93,
     200,   201,   162,    57,    25,   117,   207,   118,    26,   119,
      94,    95,    96,    97,   213,    59,   182,    61,   120,   127,
      85,   127,    86,    87,   127,   127,   128,   127,    90,   225,
     245,   247,   127,    99,   250,   251,   253,    94,    95,    96,
      97,   258,    49,    50,    69,    52,     5,     6,    70,     7,
      93,    47,    71,   101,    72,    48,    10,   103,    73,   104,
      74,    94,    95,    96,    97,    53,    32,    33,   105,    54,
      32,    40,   173,    55,   193,   106,    49,    50,    51,    52,
     107,   246,    49,    50,    69,    52,     5,     6,    70,     7,
      34,    35,    71,   125,    72,   147,    10,   -27,    73,    53,
      74,    63,    64,    54,    65,    53,   129,    55,   194,    54,
      38,    39,   130,    55,   149,   131,    49,    50,   150,    52,
     141,   256,    49,    50,    69,    52,     5,     6,    70,     7,
      41,    42,    71,   136,    72,   142,    10,   143,    73,    53,
      74,    32,    43,    54,   -26,    53,   156,    55,   167,    54,
     110,   111,    93,    55,   154,   185,    49,    50,    51,    52,
     186,   257,    49,    50,    69,    52,     5,     6,    70,     7,
     183,    90,    71,   187,    72,   189,    10,   191,    73,    53,
      74,   -11,   -11,    54,   192,    53,   197,    55,   205,    54,
     208,    93,   224,    55,    49,    50,    51,    52,    -9,    -9,
     184,   264,    94,    95,    96,    97,    49,    50,    69,    52,
       5,     6,    70,     7,   218,   234,    71,    53,    72,   215,
      10,    54,    73,   206,    74,    55,   -10,   -10,   209,    53,
      -8,    -8,   214,    54,   218,   222,   223,    55,    49,    50,
      69,    52,     5,     6,    70,     7,   227,   229,    71,   230,
      72,   183,    10,   237,    73,   244,    74,   240,    30,   252,
     241,    53,   254,   242,   243,    54,   148,    31,   261,    55,
      49,    50,    69,    52,     5,     6,    70,     7,    93,   263,
      71,   265,    72,   255,    10,   266,    73,   267,    74,    94,
      95,    96,    97,    53,    14,   133,   228,    54,     0,   235,
     180,    55,    49,    50,    69,    52,     5,     6,    70,     7,
       0,     0,    71,     0,    72,     0,    10,     0,    73,     0,
      74,     0,     0,   259,     0,    53,     0,     0,     0,    54,
       0,     0,     0,    55,    49,    50,    69,    52,     5,     6,
      70,     7,     0,     0,    71,     0,    72,     0,    10,     0,
      73,     0,    74,     0,     0,   260,     0,    53,     0,     0,
       0,    54,     0,     0,     0,    55,    49,    50,    69,    52,
       5,     6,    70,     7,     0,     0,    71,     0,    72,     0,
      10,     0,    73,     0,    74,     0,     0,   262,     0,    53,
       0,     0,     0,    54,     0,     0,     0,    55,    49,    50,
      69,    52,     5,     6,    70,     7,     0,     0,    71,     0,
      72,     0,    10,     0,    73,     0,    74,    49,    50,    51,
      52,    53,     0,    93,     0,    54,     0,     0,     0,    55,
      49,    50,   161,    52,    94,    95,    96,    97,     0,     0,
      53,     0,    98,     0,    54,     0,     0,     0,    55,     0,
       0,    93,     0,    53,     0,    93,     0,    54,     0,     0,
       0,    55,    94,    95,    96,    97,    94,    95,    96,    97,
     100,    93,     0,     0,   102,    93,     0,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    94,    95,    96,    97,
     190,    93,     0,     0,   221,    93,     0,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    94,    95,    96,    97,
     226,    93,   135,     0,     4,     0,     5,     6,    93,     7,
       8,     9,    94,    95,    96,    97,    10,     0,   188,    94,
      95,    96,    97
};

static const yytype_int16 yycheck[] =
{
      76,    34,     1,    45,   124,    38,     1,     1,    41,    66,
       1,    34,     1,     3,     4,     5,     6,     7,     8,     9,
      10,    54,    55,    13,    66,    15,     1,    17,     1,    19,
       1,    21,     5,   109,    76,     3,    26,    36,    37,   230,
      30,     0,    37,    37,    34,    34,    37,     5,     5,   240,
       7,     8,    42,   110,     1,    34,     5,    90,    26,    34,
      39,    94,    95,    96,    97,   185,    37,   109,   110,     1,
     146,     1,     3,     4,     5,     6,     7,     8,     9,    10,
     113,   114,    13,   116,    15,    42,    17,    34,    19,   122,
      21,   124,   125,     1,     5,    26,   129,     5,    19,    30,
      18,    35,    34,    34,   146,    35,    36,     5,     1,     1,
      18,    42,    19,    31,    32,     7,     8,    37,    10,    39,
      41,    29,    30,    31,    32,    18,    11,    12,   204,   186,
      38,    39,     1,    37,    41,    39,    29,    30,    31,    32,
      41,   217,   175,    35,    37,     5,     6,     7,   205,    18,
     183,   184,   185,     3,     1,     1,   189,     3,     5,     5,
      29,    30,    31,    32,   197,     3,    35,     3,    14,   245,
       5,   247,     7,     8,   250,   251,    18,   253,    39,   212,
     237,   238,   258,    40,   241,   242,   243,    29,    30,    31,
      32,   248,     3,     4,     5,     6,     7,     8,     9,    10,
      18,     1,    13,    40,    15,     5,    17,    40,    19,     5,
      21,    29,    30,    31,    32,    26,    36,    37,     5,    30,
      36,    37,    40,    34,     1,     5,     3,     4,     5,     6,
       5,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      38,    39,    13,    34,    15,     1,    17,     0,    19,    26,
      21,     7,     8,    30,    10,    26,    38,    34,    35,    30,
      38,    39,     5,    34,     1,     5,     3,     4,     5,     6,
      37,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      38,    39,    13,     5,    15,    37,    17,    37,    19,    26,
      21,    36,    37,    30,     0,    26,    37,    34,     5,    30,
      35,    36,    18,    34,     1,    37,     3,     4,     5,     6,
      35,    42,     3,     4,     5,     6,     7,     8,     9,    10,
      38,    39,    13,    35,    15,    38,    17,     3,    19,    26,
      21,    11,    12,    30,     3,    26,    38,    34,    41,    30,
      40,    18,     1,    34,     3,     4,     5,     6,    11,    12,
      27,    42,    29,    30,    31,    32,     3,     4,     5,     6,
       7,     8,     9,    10,    22,    23,    13,    26,    15,    16,
      17,    30,    19,    43,    21,    34,    11,    12,    40,    26,
      11,    12,    37,    30,    22,    37,    37,    34,     3,     4,
       5,     6,     7,     8,     9,    10,     5,    37,    13,    20,
      15,    38,    17,    35,    19,    25,    21,    20,    11,    24,
      43,    26,    37,    43,    43,    30,   111,    11,    37,    34,
       3,     4,     5,     6,     7,     8,     9,    10,    18,    37,
      13,    37,    15,    16,    17,    37,    19,    37,    21,    29,
      30,    31,    32,    26,     2,    88,   214,    30,    -1,   219,
      40,    34,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    -1,    15,    -1,    17,    -1,    19,    -1,
      21,    -1,    -1,    24,    -1,    26,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    34,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,
      19,    -1,    21,    -1,    -1,    24,    -1,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    -1,    15,    -1,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,    26,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    -1,
      15,    -1,    17,    -1,    19,    -1,    21,     3,     4,     5,
       6,    26,    -1,    18,    -1,    30,    -1,    -1,    -1,    34,
       3,     4,     5,     6,    29,    30,    31,    32,    -1,    -1,
      26,    -1,    37,    -1,    30,    -1,    -1,    -1,    34,    -1,
      -1,    18,    -1,    26,    -1,    18,    -1,    30,    -1,    -1,
      -1,    34,    29,    30,    31,    32,    29,    30,    31,    32,
      37,    18,    -1,    -1,    37,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    29,    30,    31,    32,
      37,    18,    -1,    -1,    37,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    29,    30,    31,    32,
      37,    18,    35,    -1,     5,    -1,     7,     8,    18,    10,
      11,    12,    29,    30,    31,    32,    17,    -1,    35,    29,
      30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,     0,     5,     7,     8,    10,    11,    12,
      17,    47,    48,    52,    56,    61,     5,    55,     1,     5,
      55,     5,    55,     5,    55,     1,     5,     1,    34,     5,
      48,    52,    36,    37,    38,    39,     1,    37,    38,    39,
      37,    38,    39,    37,    34,    35,    41,     1,     5,     3,
       4,     5,     6,    26,    30,    34,    60,     3,    60,     3,
      60,     3,     1,     7,     8,    10,    35,    49,    50,     5,
       9,    13,    15,    19,    21,    51,    53,    54,    56,    57,
      60,    64,    65,    66,    69,     5,     7,     8,    62,    63,
      39,    60,    60,    18,    29,    30,    31,    32,    37,    40,
      37,    40,    37,    40,     5,     5,     5,     5,    51,    53,
      35,    36,     1,    38,    39,     1,    34,     1,     3,     5,
      14,     1,    34,     1,    34,    34,    51,    54,    18,    38,
       5,     5,    42,    63,    60,    35,     5,    60,    60,    60,
      60,    37,    37,    37,    51,    51,    53,     1,    50,     1,
       5,    58,    60,    60,     1,    60,    37,     1,    37,     1,
      37,     5,    60,    67,    68,    68,    60,     5,    60,    37,
      39,    37,    39,    40,    51,    34,     1,    37,     1,    37,
      40,     1,    35,    38,    27,    37,    35,    35,    35,    38,
      37,     3,     3,     1,    35,    59,    60,    38,     1,    37,
      60,    60,    68,    51,    53,    41,    43,    60,    40,    40,
       1,    35,    36,    60,    37,    16,    42,    53,    22,    70,
      71,    37,    37,    37,     1,    60,    37,     5,    67,    37,
      20,    42,     3,    26,    23,    71,    72,    35,    41,    65,
      20,    43,    43,    43,    25,    53,    42,    53,    41,    65,
      53,    53,    24,    53,    37,    16,    42,    42,    53,    24,
      24,    37,    24,    37,    42,    37,    37,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      48,    48,    48,    49,    49,    49,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    51,    52,    52,    52,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66,    67,    68,    69,
      70,    70,    71,    71,    71,    71,    72,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     1,     2,     7,     6,
       6,     5,     2,     1,     3,     3,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     2,     5,     4,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     5,     5,     5,     6,     6,     6,
       1,     3,     3,     2,     4,     4,     7,     6,     4,     4,
       3,     2,     4,     3,     4,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     2,     3,
       4,     3,     5,     1,     2,     3,     3,     6,     6,     4,
       5,     5,     4,     3,     2,     7,     6,    11,    10,    10,
       9,     9,     8,     2,     7,    11,     2,     3,     3,     9,
       1,     2,     3,     6,     3,     6,     4,     5
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
#line 88 "parser.y"
                                             {
        /* Full program: globals, functions, then entry point */
        root = createProgram((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1410 "parser.tab.c"
    break;

  case 3: /* program: global_list program_start  */
#line 92 "parser.y"
                                {
        /* No functions — just globals then Program_Start */
        root = createProgram((yyvsp[-1].node), NULL, (yyvsp[0].node));
    }
#line 1419 "parser.tab.c"
    break;

  case 4: /* global_list: %empty  */
#line 104 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1427 "parser.tab.c"
    break;

  case 5: /* global_list: global_list decl  */
#line 107 "parser.y"
                       {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1435 "parser.tab.c"
    break;

  case 6: /* func_decl_list: func_decl  */
#line 118 "parser.y"
              {
        /* Base case: single function */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1444 "parser.tab.c"
    break;

  case 7: /* func_decl_list: func_decl_list func_decl  */
#line 122 "parser.y"
                               {
        /* Multiple functions: build a list */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1453 "parser.tab.c"
    break;

  case 8: /* func_decl: FUNC ID '(' param_list ')' stmt_list end_clause  */
#line 135 "parser.y"
                                                    {
        /* Function with parameters */
        (yyval.node) = createFuncDecl((yyvsp[-5].str), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-5].str));
    }
#line 1463 "parser.tab.c"
    break;

  case 9: /* func_decl: FUNC ID '(' ')' stmt_list end_clause  */
#line 140 "parser.y"
                                           {
        /* Function with no parameters */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), NULL, (yyvsp[-1].node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1473 "parser.tab.c"
    break;

  case 10: /* func_decl: FUNC ID '(' param_list ')' end_clause  */
#line 145 "parser.y"
                                            {
        /* Function with params but empty body */
        (yyval.node) = createFuncDecl((yyvsp[-4].str), (yyvsp[-2].node), NULL, (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1483 "parser.tab.c"
    break;

  case 11: /* func_decl: FUNC ID '(' ')' end_clause  */
#line 150 "parser.y"
                                 {
        /* Function with no params and empty body */
        (yyval.node) = createFuncDecl((yyvsp[-3].str), NULL, NULL, (yyvsp[0].node));
        free((yyvsp[-3].str));
    }
#line 1493 "parser.tab.c"
    break;

  case 12: /* func_decl: FUNC error  */
#line 155 "parser.y"
                 {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed function declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'func name(int a, int b) ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1505 "parser.tab.c"
    break;

  case 13: /* param_list: param_item  */
#line 170 "parser.y"
               {
        /* Single parameter — wrap in NODE_PARAM_LIST so appendParamList
         * always receives a list head, never a raw NODE_PARAM */
        (yyval.node) = createParamList((yyvsp[0].node), NULL);
    }
#line 1515 "parser.tab.c"
    break;

  case 14: /* param_list: param_list ',' param_item  */
#line 175 "parser.y"
                                {
        /* Multiple parameters */
        (yyval.node) = appendParamList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1524 "parser.tab.c"
    break;

  case 15: /* param_list: param_list ',' error  */
#line 179 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected 'int <name>' after comma in parameter list\n");
        fprintf(stderr, "   💡 Suggestion: Each parameter must have a type, e.g. 'int x'\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1536 "parser.tab.c"
    break;

  case 16: /* param_item: INT ID  */
#line 190 "parser.y"
           {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1545 "parser.tab.c"
    break;

  case 17: /* param_item: FLOAT ID  */
#line 194 "parser.y"
               {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1554 "parser.tab.c"
    break;

  case 18: /* param_item: CHAR ID  */
#line 198 "parser.y"
              {
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1563 "parser.tab.c"
    break;

  case 19: /* param_item: error ID  */
#line 202 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing type in parameter declaration\n");
        fprintf(stderr, "   💡 Suggestion: Use 'int %s' instead of just '%s'\n\n", (yyvsp[0].str), (yyvsp[0].str));
        (yyval.node) = createParam((yyvsp[0].str));
        free((yyvsp[0].str));
        yyerrok;
    }
#line 1576 "parser.tab.c"
    break;

  case 20: /* end_clause: END NULLTOK ';'  */
#line 219 "parser.y"
                    {
        /* Void return — function returns nothing */
        (yyval.node) = createEndClause(NULL);
    }
#line 1585 "parser.tab.c"
    break;

  case 21: /* end_clause: END ID ';'  */
#line 223 "parser.y"
                 {
        /* Return a variable's value */
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1595 "parser.tab.c"
    break;

  case 22: /* end_clause: END NUM ';'  */
#line 228 "parser.y"
                  {
        /* Return an integer literal — e.g. end 1; end 0; */
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", (yyvsp[-1].num));
        (yyval.node) = createEndClause(buf);
    }
#line 1606 "parser.tab.c"
    break;

  case 23: /* end_clause: END NULLTOK error  */
#line 234 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after 'end null'\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;'\n\n");
        (yyval.node) = createEndClause(NULL);
        yyerrok;
    }
#line 1618 "parser.tab.c"
    break;

  case 24: /* end_clause: END ID error  */
#line 241 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end %s;'\n\n", (yyvsp[-1].str));
        (yyval.node) = createEndClause((yyvsp[-1].str));
        free((yyvsp[-1].str));
        yyerrok;
    }
#line 1631 "parser.tab.c"
    break;

  case 25: /* end_clause: END error  */
#line 249 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid end clause\n");
        fprintf(stderr, "   💡 Suggestion: Use 'end null;' or 'end <variable>;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1643 "parser.tab.c"
    break;

  case 26: /* program_start: PROGRAM_START '(' ')' stmt_list end_clause  */
#line 269 "parser.y"
                                               {
        /* Standard form with parentheses and statements */
        (yyval.node) = createProgramStart((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1652 "parser.tab.c"
    break;

  case 27: /* program_start: PROGRAM_START '(' ')' end_clause  */
#line 273 "parser.y"
                                       {
        /* Empty Program_Start body */
        (yyval.node) = createProgramStart(NULL, (yyvsp[0].node));
    }
#line 1661 "parser.tab.c"
    break;

  case 28: /* program_start: PROGRAM_START error  */
#line 277 "parser.y"
                          {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed Program_Start block\n");
        fprintf(stderr, "   💡 Suggestion: Use 'Program_Start() ... end null;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1673 "parser.tab.c"
    break;

  case 29: /* stmt_list: stmt  */
#line 292 "parser.y"
         {
        /* Base case: single statement */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1682 "parser.tab.c"
    break;

  case 30: /* stmt_list: stmt_list stmt  */
#line 296 "parser.y"
                     {
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1691 "parser.tab.c"
    break;

  case 38: /* id_list: ID  */
#line 320 "parser.y"
       {
        /* Base case: single identifier */
        (yyval.node) = createIdList((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1701 "parser.tab.c"
    break;

  case 39: /* id_list: id_list ',' ID  */
#line 325 "parser.y"
                     {
        /* Recursive case: extend list */
        (yyval.node) = appendIdList((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 1711 "parser.tab.c"
    break;

  case 40: /* id_list: id_list ',' error  */
#line 330 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected identifier after comma in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add a variable name after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 1723 "parser.tab.c"
    break;

  case 41: /* decl: INT id_list ';'  */
#line 345 "parser.y"
                    {
        (yyval.node) = createMultiDecl((yyvsp[-1].node));
    }
#line 1731 "parser.tab.c"
    break;

  case 42: /* decl: FLOAT id_list ';'  */
#line 348 "parser.y"
                        {
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), "float");
    }
#line 1739 "parser.tab.c"
    break;

  case 43: /* decl: CHAR id_list ';'  */
#line 351 "parser.y"
                       {
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), "char");
    }
#line 1747 "parser.tab.c"
    break;

  case 44: /* decl: INT ID '=' expr ';'  */
#line 354 "parser.y"
                          {
        /* Inline init: int score = 85; → DECL + ASSIGN */
        ASTNode* d = createDecl("int", (yyvsp[-3].str));
        ASTNode* a = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        (yyval.node) = createStmtList(d, a);
        free((yyvsp[-3].str));
    }
#line 1759 "parser.tab.c"
    break;

  case 45: /* decl: FLOAT ID '=' expr ';'  */
#line 361 "parser.y"
                            {
        ASTNode* d = createDecl("float", (yyvsp[-3].str));
        ASTNode* a = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        (yyval.node) = createStmtList(d, a);
        free((yyvsp[-3].str));
    }
#line 1770 "parser.tab.c"
    break;

  case 46: /* decl: CHAR ID '=' expr ';'  */
#line 367 "parser.y"
                           {
        ASTNode* d = createDecl("char", (yyvsp[-3].str));
        ASTNode* a = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        (yyval.node) = createStmtList(d, a);
        free((yyvsp[-3].str));
    }
#line 1781 "parser.tab.c"
    break;

  case 47: /* decl: INT ID '[' NUM ']' ';'  */
#line 373 "parser.y"
                             {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1790 "parser.tab.c"
    break;

  case 48: /* decl: FLOAT ID '[' NUM ']' ';'  */
#line 377 "parser.y"
                               {
        (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
        free((yyvsp[-4].str));
    }
#line 1799 "parser.tab.c"
    break;

  case 49: /* decl: CHAR ID '[' NUM ']' ';'  */
#line 381 "parser.y"
                              {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "char");
        free((yyvsp[-4].str));
    }
#line 1808 "parser.tab.c"
    break;

  case 50: /* decl: struct_def  */
#line 385 "parser.y"
                 {
        /* Struct type definition:  struct stats { ... }  */
        (yyval.node) = (yyvsp[0].node);
    }
#line 1817 "parser.tab.c"
    break;

  case 51: /* decl: ID id_list ';'  */
#line 389 "parser.y"
                     {
        /* Struct variable declaration:  stats playerStats;
         * (also allows "stats a, b;" via id_list)            */
        (yyval.node) = createMultiDeclTyped((yyvsp[-1].node), (yyvsp[-2].str));
        free((yyvsp[-2].str));
    }
#line 1828 "parser.tab.c"
    break;

  case 52: /* decl: INT id_list error  */
#line 395 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after variable declaration\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after the identifier list\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1840 "parser.tab.c"
    break;

  case 53: /* decl: INT error  */
#line 402 "parser.y"
                {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid or missing identifier in declaration\n");
        fprintf(stderr, "   💡 Suggestion: Expected 'int <identifier>;' or 'int x, y, z;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1852 "parser.tab.c"
    break;

  case 54: /* assign: ID '=' expr ';'  */
#line 418 "parser.y"
                    {
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1861 "parser.tab.c"
    break;

  case 55: /* assign: ID '=' func_call ';'  */
#line 422 "parser.y"
                           {
        /* Function call as RHS: z = add(x, y); */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1871 "parser.tab.c"
    break;

  case 56: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 427 "parser.y"
                                   {
    ASTNode* lhs = createArrayIndex((yyvsp[-6].str), (yyvsp[-4].node));
    ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
    node->data.assign.arrayLHS = lhs;
    (yyval.node) = node;
    free((yyvsp[-6].str));
    }
#line 1883 "parser.tab.c"
    break;

  case 57: /* assign: expr IS ID '=' expr ';'  */
#line 434 "parser.y"
                              {
        /* Struct field assignment:  playerStats is health = 10; */
        ASTNode* lhs = createStructAccess((yyvsp[-5].node), (yyvsp[-3].str));
        ASTNode* node = createAssign(NULL, (yyvsp[-1].node));
        node->data.assign.structLHS = lhs;
        (yyval.node) = node;
        free((yyvsp[-3].str));
    }
#line 1896 "parser.tab.c"
    break;

  case 58: /* assign: ID '=' expr error  */
#line 442 "parser.y"
                        {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <expression>'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1909 "parser.tab.c"
    break;

  case 59: /* assign: ID '=' func_call error  */
#line 450 "parser.y"
                             {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after function call assignment\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after '%s = <func>(...)'\n\n", (yyvsp[-3].str));
        free((yyvsp[-3].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1922 "parser.tab.c"
    break;

  case 60: /* assign: ID '=' error  */
#line 458 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in assignment\n");
        fprintf(stderr, "   💡 Suggestion: Check the expression after '=' for '%s'\n\n", (yyvsp[-2].str));
        free((yyvsp[-2].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1935 "parser.tab.c"
    break;

  case 61: /* assign: ID error  */
#line 466 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing '=' in assignment statement\n");
        fprintf(stderr, "   💡 Suggestion: Use '%s = <expression>;'\n\n", (yyvsp[-1].str));
        free((yyvsp[-1].str));
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1948 "parser.tab.c"
    break;

  case 62: /* func_call: ID '(' arg_list ')'  */
#line 483 "parser.y"
                        {
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1957 "parser.tab.c"
    break;

  case 63: /* func_call: ID '(' ')'  */
#line 487 "parser.y"
                 {
        /* No arguments */
        (yyval.node) = createFuncCall((yyvsp[-2].str), NULL);
        free((yyvsp[-2].str));
    }
#line 1967 "parser.tab.c"
    break;

  case 64: /* func_call: ID '(' arg_list error  */
#line 492 "parser.y"
                            {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing ')' in function call\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' after the argument list\n\n");
        (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
        yyerrok;
    }
#line 1980 "parser.tab.c"
    break;

  case 65: /* func_call: ID '(' error  */
#line 500 "parser.y"
                   {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid argument in function call\n");
        fprintf(stderr, "   💡 Suggestion: Use 'funcName(x, y)' or 'funcName()'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 1992 "parser.tab.c"
    break;

  case 66: /* arg_list: expr  */
#line 516 "parser.y"
         {
        /* Single argument */
        (yyval.node) = createArgList((yyvsp[0].node));
    }
#line 2001 "parser.tab.c"
    break;

  case 67: /* arg_list: arg_list ',' expr  */
#line 520 "parser.y"
                        {
        /* Multiple arguments */
        (yyval.node) = appendArgList((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2010 "parser.tab.c"
    break;

  case 68: /* arg_list: arg_list ',' error  */
#line 524 "parser.y"
                         {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Expected expression after comma in argument list\n");
        fprintf(stderr, "   💡 Suggestion: Provide a value or variable after ','\n\n");
        (yyval.node) = (yyvsp[-2].node);
        yyerrok;
    }
#line 2022 "parser.tab.c"
    break;

  case 69: /* expr: NUM  */
#line 539 "parser.y"
        {
        /* Integer literal */
        (yyval.node) = createNum((yyvsp[0].num));
    }
#line 2031 "parser.tab.c"
    break;

  case 70: /* expr: FNUM  */
#line 543 "parser.y"
           {
        /* Float literal */
        (yyval.node) = createFloat((yyvsp[0].fnum));
    }
#line 2040 "parser.tab.c"
    break;

  case 71: /* expr: STRING  */
#line 547 "parser.y"
             {
        /* String literal */
        (yyval.node) = createString((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2050 "parser.tab.c"
    break;

  case 72: /* expr: CHAR_LIT  */
#line 552 "parser.y"
               {
        /* Character literal: 'A' → integer ASCII value */
        (yyval.node) = createNum((yyvsp[0].num));
    }
#line 2059 "parser.tab.c"
    break;

  case 73: /* expr: ID  */
#line 556 "parser.y"
         {
        /* Variable reference */
        (yyval.node) = createVar((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2069 "parser.tab.c"
    break;

  case 74: /* expr: expr '+' expr  */
#line 561 "parser.y"
                    {
        (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2077 "parser.tab.c"
    break;

  case 75: /* expr: expr '-' expr  */
#line 564 "parser.y"
                    {
        (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2085 "parser.tab.c"
    break;

  case 76: /* expr: expr '*' expr  */
#line 567 "parser.y"
                    {
        (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2093 "parser.tab.c"
    break;

  case 77: /* expr: expr '/' expr  */
#line 570 "parser.y"
                    {
        (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2101 "parser.tab.c"
    break;

  case 78: /* expr: '-' expr  */
#line 573 "parser.y"
                            {
        (yyval.node) = createBinOp('u', (yyvsp[0].node), NULL);
    }
#line 2109 "parser.tab.c"
    break;

  case 79: /* expr: '(' expr ')'  */
#line 576 "parser.y"
                   {
        /* Parenthesized expression */
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2118 "parser.tab.c"
    break;

  case 80: /* expr: ID '[' expr ']'  */
#line 580 "parser.y"
                      {
        (yyval.node) = createArrayIndex((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2127 "parser.tab.c"
    break;

  case 81: /* expr: expr IS ID  */
#line 584 "parser.y"
                 {
        /* Struct field access (rvalue):  playerStats is health */
        (yyval.node) = createStructAccess((yyvsp[-2].node), (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2137 "parser.tab.c"
    break;

  case 82: /* struct_def: STRUCT ID '{' field_body '}'  */
#line 600 "parser.y"
                                 {
        (yyval.node) = createStructDef((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2146 "parser.tab.c"
    break;

  case 83: /* field_body: field_item  */
#line 607 "parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2154 "parser.tab.c"
    break;

  case 84: /* field_body: field_body field_item  */
#line 610 "parser.y"
                            {
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2162 "parser.tab.c"
    break;

  case 85: /* field_item: INT ID ';'  */
#line 616 "parser.y"
               {
        (yyval.node) = createDecl("int", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2171 "parser.tab.c"
    break;

  case 86: /* field_item: FLOAT ID ';'  */
#line 620 "parser.y"
                   {
        (yyval.node) = createDecl("float", (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 2180 "parser.tab.c"
    break;

  case 87: /* field_item: INT ID '[' NUM ']' ';'  */
#line 624 "parser.y"
                             {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "int");
        free((yyvsp[-4].str));
    }
#line 2189 "parser.tab.c"
    break;

  case 88: /* field_item: FLOAT ID '[' NUM ']' ';'  */
#line 628 "parser.y"
                               {
        (yyval.node) = createArrayDeclTyped((yyvsp[-4].str), (yyvsp[-2].num), "float");
        free((yyvsp[-4].str));
    }
#line 2198 "parser.tab.c"
    break;

  case 89: /* field_item: ID '=' expr ';'  */
#line 632 "parser.y"
                      {
        /* Default field value, e.g. "health = 10;" */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2208 "parser.tab.c"
    break;

  case 90: /* print_stmt: PRINT '(' expr ')' ';'  */
#line 645 "parser.y"
                           {
        (yyval.node) = createPrint((yyvsp[-2].node));
    }
#line 2216 "parser.tab.c"
    break;

  case 91: /* print_stmt: PRINT '(' expr ')' error  */
#line 648 "parser.y"
                               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing semicolon after print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ';' after 'print(<expression>)'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2228 "parser.tab.c"
    break;

  case 92: /* print_stmt: PRINT '(' expr error  */
#line 655 "parser.y"
                           {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing closing parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Add ')' before semicolon\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2240 "parser.tab.c"
    break;

  case 93: /* print_stmt: PRINT '(' error  */
#line 662 "parser.y"
                      {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Invalid expression in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2252 "parser.tab.c"
    break;

  case 94: /* print_stmt: PRINT error  */
#line 669 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Missing opening parenthesis in print statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'print(<expression>);'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2264 "parser.tab.c"
    break;

  case 95: /* if_stmt: IF '(' condition ')' '{' stmt_list '}'  */
#line 686 "parser.y"
                                                                 {
        (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-1].node), NULL);
    }
#line 2272 "parser.tab.c"
    break;

  case 96: /* if_stmt: IF '(' condition ')' '{' '}'  */
#line 689 "parser.y"
                                                         {
        (yyval.node) = createIf((yyvsp[-3].node), NULL, NULL);
    }
#line 2280 "parser.tab.c"
    break;

  case 97: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' stmt_list '}'  */
#line 692 "parser.y"
                                                                    {
        (yyval.node) = createIf((yyvsp[-8].node), (yyvsp[-5].node), (yyvsp[-1].node));
    }
#line 2288 "parser.tab.c"
    break;

  case 98: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' stmt_list '}'  */
#line 695 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), NULL, (yyvsp[-1].node));
    }
#line 2296 "parser.tab.c"
    break;

  case 99: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE '{' '}'  */
#line 698 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-7].node), (yyvsp[-4].node), NULL);
    }
#line 2304 "parser.tab.c"
    break;

  case 100: /* if_stmt: IF '(' condition ')' '{' '}' ELSE '{' '}'  */
#line 701 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-6].node), NULL, NULL);
    }
#line 2312 "parser.tab.c"
    break;

  case 101: /* if_stmt: IF '(' condition ')' '{' stmt_list '}' ELSE if_stmt  */
#line 704 "parser.y"
                                                          {
        (yyval.node) = createIf((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 2320 "parser.tab.c"
    break;

  case 102: /* if_stmt: IF '(' condition ')' '{' '}' ELSE if_stmt  */
#line 707 "parser.y"
                                                {
        (yyval.node) = createIf((yyvsp[-5].node), NULL, (yyvsp[0].node));
    }
#line 2328 "parser.tab.c"
    break;

  case 103: /* if_stmt: IF error  */
#line 710 "parser.y"
               {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed if statement\n");
        fprintf(stderr, "   💡 Suggestion: Use 'if (<condition>) { ... }'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2340 "parser.tab.c"
    break;

  case 104: /* while_stmt: WHILE '(' condition ')' stmt_list CONTINUE ';'  */
#line 726 "parser.y"
                                                   {
        (yyval.node) = createWhile((yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2348 "parser.tab.c"
    break;

  case 105: /* while_stmt: WHILE '(' assign_init ';' condition ';' assign_init ')' stmt_list CONTINUE ';'  */
#line 729 "parser.y"
                                                                                     {
        (yyval.node) = createForWhile((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node));
    }
#line 2356 "parser.tab.c"
    break;

  case 106: /* while_stmt: WHILE error  */
#line 732 "parser.y"
                  {
        fprintf(stderr, "\n❌ Syntax Error at line %d:\n", yylineno);
        fprintf(stderr, "   Malformed while loop\n");
        fprintf(stderr, "   💡 Suggestion: Use 'while (<condition>) ... continue;'\n");
        fprintf(stderr, "                  or 'while (i = 0; i < 10; i = i + 1) ... continue;'\n\n");
        (yyval.node) = NULL;
        yyerrok;
    }
#line 2369 "parser.tab.c"
    break;

  case 107: /* assign_init: ID '=' expr  */
#line 745 "parser.y"
                {
        (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 2378 "parser.tab.c"
    break;

  case 108: /* condition: expr RELOP expr  */
#line 753 "parser.y"
                    {
        (yyval.node) = createBinOp((char)(yyvsp[-1].num), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2386 "parser.tab.c"
    break;

  case 109: /* switch_stmt: SWITCH '(' expr ')' ':' case_list default_case CLOSE ';'  */
#line 768 "parser.y"
                                                             {
        (yyval.node) = createSwitch((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-2].node));
    }
#line 2394 "parser.tab.c"
    break;

  case 110: /* case_list: case_arm  */
#line 774 "parser.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2402 "parser.tab.c"
    break;

  case 111: /* case_list: case_list case_arm  */
#line 777 "parser.y"
                         {
        (yyval.node) = appendCaseList((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2410 "parser.tab.c"
    break;

  case 112: /* case_arm: CASE NUM ':'  */
#line 783 "parser.y"
                 {
        /* Fall-through: no body, no break — execution falls to next case */
        (yyval.node) = createCase((yyvsp[-1].num), NULL);
    }
#line 2419 "parser.tab.c"
    break;

  case 113: /* case_arm: CASE NUM ':' stmt_list BREAK ';'  */
#line 787 "parser.y"
                                       {
        /* Append a NODE_BREAK so the TAC emits GOTO Lend */
        (yyval.node) = createCase((yyvsp[-4].num), createStmtList((yyvsp[-2].node), createBreak()));
    }
#line 2428 "parser.tab.c"
    break;

  case 114: /* case_arm: CASE CHAR_LIT ':'  */
#line 791 "parser.y"
                        {
        (yyval.node) = createCase((yyvsp[-1].num), NULL);
    }
#line 2436 "parser.tab.c"
    break;

  case 115: /* case_arm: CASE CHAR_LIT ':' stmt_list BREAK ';'  */
#line 794 "parser.y"
                                            {
        (yyval.node) = createCase((yyvsp[-4].num), createStmtList((yyvsp[-2].node), createBreak()));
    }
#line 2444 "parser.tab.c"
    break;

  case 116: /* default_case: DEFAULT ':' BREAK ';'  */
#line 800 "parser.y"
                          {
        /* Default with no body — just break */
        (yyval.node) = createDefault(createBreak());
    }
#line 2453 "parser.tab.c"
    break;

  case 117: /* default_case: DEFAULT ':' stmt_list BREAK ';'  */
#line 804 "parser.y"
                                      {
        (yyval.node) = createDefault(createStmtList((yyvsp[-2].node), createBreak()));
    }
#line 2461 "parser.tab.c"
    break;


#line 2465 "parser.tab.c"

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

#line 809 "parser.y"


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
