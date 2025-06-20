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
#line 5 "compiler.y"

    #include "compiler_common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    #define MAX_SYMBOLS 256
    #define MAX_SCOPE 10

    typedef struct {
        char name[64];
        char type[16];
        int addr;
        int lineno;
        int mut;
        char func_sig[32];
    } Symbol;

    typedef struct {
        Symbol symbols[MAX_SYMBOLS];
        int count;
        int level;
    } Scope;

    static Scope scope_stack[MAX_SCOPE];
    static int scope_top = -1;
    static int addr_counter = 0;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void init_symbol();
    static int insert_symbol(const char *name, const char *type, int addr, int lineno, const char *sig);
    static int lookup_symbol(const char *name);
    static void dump_symbol();
    static int next_addr();
    static int get_scope_level();
    static const char* get_symbol_type(const char *name);

    /* Global variables */
    bool g_has_error = false;
    FILE *fout = NULL;
    int g_indent_cnt = 0;
    bool HAS_ERROR = false;
    static int label_id = 0;
    int last_if_id;

    int is_mutable(const char* name) {
        for (int i = scope_top; i >= 0; --i) {
            for (int j = 0; j < scope_stack[i].count; ++j) {
                if (strcmp(scope_stack[i].symbols[j].name, name) == 0) {
                    return scope_stack[i].symbols[j].mut;
                }
            }
        }
        return 0;
    }

#line 154 "y.tab.c"

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
# define YYDEBUG 0
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
    LET = 258,                     /* LET  */
    MUT = 259,                     /* MUT  */
    NEWLINE = 260,                 /* NEWLINE  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    BOOL = 263,                    /* BOOL  */
    STR = 264,                     /* STR  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    GEQ = 267,                     /* GEQ  */
    LEQ = 268,                     /* LEQ  */
    EQL = 269,                     /* EQL  */
    NEQ = 270,                     /* NEQ  */
    LOR = 271,                     /* LOR  */
    LAND = 272,                    /* LAND  */
    ADD_ASSIGN = 273,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 274,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 275,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 276,              /* DIV_ASSIGN  */
    REM_ASSIGN = 277,              /* REM_ASSIGN  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    FOR = 280,                     /* FOR  */
    WHILE = 281,                   /* WHILE  */
    LOOP = 282,                    /* LOOP  */
    PRINT = 283,                   /* PRINT  */
    PRINTLN = 284,                 /* PRINTLN  */
    FUNC = 285,                    /* FUNC  */
    RETURN = 286,                  /* RETURN  */
    BREAK = 287,                   /* BREAK  */
    ARROW = 288,                   /* ARROW  */
    AS = 289,                      /* AS  */
    IN = 290,                      /* IN  */
    DOTDOT = 291,                  /* DOTDOT  */
    RSHIFT = 292,                  /* RSHIFT  */
    LSHIFT = 293,                  /* LSHIFT  */
    INT_LIT = 294,                 /* INT_LIT  */
    FLOAT_LIT = 295,               /* FLOAT_LIT  */
    STRING_LIT = 296,              /* STRING_LIT  */
    IDENT = 297,                   /* IDENT  */
    ID = 298,                      /* ID  */
    LOWER_THAN_ASSIGN = 299,       /* LOWER_THAN_ASSIGN  */
    LOWER_THAN_ELSE = 300,         /* LOWER_THAN_ELSE  */
    IFX = 301                      /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 94 "compiler.y"

    int i_val;
    float f_val;
    char *s_val;
    char* type; /* i32, f32, str, bool */

#line 257 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LET = 3,                        /* LET  */
  YYSYMBOL_MUT = 4,                        /* MUT  */
  YYSYMBOL_NEWLINE = 5,                    /* NEWLINE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_STR = 9,                        /* STR  */
  YYSYMBOL_TRUE = 10,                      /* TRUE  */
  YYSYMBOL_FALSE = 11,                     /* FALSE  */
  YYSYMBOL_GEQ = 12,                       /* GEQ  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_EQL = 14,                       /* EQL  */
  YYSYMBOL_NEQ = 15,                       /* NEQ  */
  YYSYMBOL_LOR = 16,                       /* LOR  */
  YYSYMBOL_LAND = 17,                      /* LAND  */
  YYSYMBOL_ADD_ASSIGN = 18,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 19,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_REM_ASSIGN = 22,                /* REM_ASSIGN  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_LOOP = 27,                      /* LOOP  */
  YYSYMBOL_PRINT = 28,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 29,                   /* PRINTLN  */
  YYSYMBOL_FUNC = 30,                      /* FUNC  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_BREAK = 32,                     /* BREAK  */
  YYSYMBOL_ARROW = 33,                     /* ARROW  */
  YYSYMBOL_AS = 34,                        /* AS  */
  YYSYMBOL_IN = 35,                        /* IN  */
  YYSYMBOL_DOTDOT = 36,                    /* DOTDOT  */
  YYSYMBOL_RSHIFT = 37,                    /* RSHIFT  */
  YYSYMBOL_LSHIFT = 38,                    /* LSHIFT  */
  YYSYMBOL_39_ = 39,                       /* '"'  */
  YYSYMBOL_INT_LIT = 40,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 41,                 /* FLOAT_LIT  */
  YYSYMBOL_STRING_LIT = 42,                /* STRING_LIT  */
  YYSYMBOL_IDENT = 43,                     /* IDENT  */
  YYSYMBOL_ID = 44,                        /* ID  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_LOWER_THAN_ASSIGN = 46,         /* LOWER_THAN_ASSIGN  */
  YYSYMBOL_LOWER_THAN_ELSE = 47,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_IFX = 48,                       /* IFX  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* '&'  */
  YYSYMBOL_52_ = 52,                       /* '['  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ']'  */
  YYSYMBOL_55_ = 55,                       /* ':'  */
  YYSYMBOL_56_ = 56,                       /* '>'  */
  YYSYMBOL_57_ = 57,                       /* '<'  */
  YYSYMBOL_58_ = 58,                       /* '{'  */
  YYSYMBOL_59_ = 59,                       /* '}'  */
  YYSYMBOL_60_ = 60,                       /* ','  */
  YYSYMBOL_61_ = 61,                       /* '+'  */
  YYSYMBOL_62_ = 62,                       /* '-'  */
  YYSYMBOL_63_ = 63,                       /* '*'  */
  YYSYMBOL_64_ = 64,                       /* '/'  */
  YYSYMBOL_65_ = 65,                       /* '%'  */
  YYSYMBOL_66_ = 66,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_Program = 68,                   /* Program  */
  YYSYMBOL_GlobalStatementList = 69,       /* GlobalStatementList  */
  YYSYMBOL_GlobalStatement = 70,           /* GlobalStatement  */
  YYSYMBOL_FunctionDeclStmt = 71,          /* FunctionDeclStmt  */
  YYSYMBOL_72_1 = 72,                      /* $@1  */
  YYSYMBOL_StatementList = 73,             /* StatementList  */
  YYSYMBOL_Statement = 74,                 /* Statement  */
  YYSYMBOL_Type = 75,                      /* Type  */
  YYSYMBOL_VarDeclStmt = 76,               /* VarDeclStmt  */
  YYSYMBOL_AssignmentStmt = 77,            /* AssignmentStmt  */
  YYSYMBOL_IfStmt = 78,                    /* IfStmt  */
  YYSYMBOL_79_2 = 79,                      /* @2  */
  YYSYMBOL_OptElse = 80,                   /* OptElse  */
  YYSYMBOL_RelExprJump = 81,               /* RelExprJump  */
  YYSYMBOL_WhileStmt = 82,                 /* WhileStmt  */
  YYSYMBOL_83_3 = 83,                      /* @3  */
  YYSYMBOL_RelExprForWhileJump = 84,       /* RelExprForWhileJump  */
  YYSYMBOL_PrintStmt = 85,                 /* PrintStmt  */
  YYSYMBOL_PrintlnStmt = 86,               /* PrintlnStmt  */
  YYSYMBOL_Block = 87,                     /* Block  */
  YYSYMBOL_88_4 = 88,                      /* $@4  */
  YYSYMBOL_ExpressionList = 89,            /* ExpressionList  */
  YYSYMBOL_ExpressionStmt = 90,            /* ExpressionStmt  */
  YYSYMBOL_Expression = 91,                /* Expression  */
  YYSYMBOL_OrExpr = 92,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 93,                   /* AndExpr  */
  YYSYMBOL_RelExpr = 94,                   /* RelExpr  */
  YYSYMBOL_AddExpr = 95,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 96,                   /* MulExpr  */
  YYSYMBOL_AsExpr = 97,                    /* AsExpr  */
  YYSYMBOL_UnaryExpr = 98,                 /* UnaryExpr  */
  YYSYMBOL_Primary = 99,                   /* Primary  */
  YYSYMBOL_ArrayIndexExpr = 100            /* ArrayIndexExpr  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
       2,     2,     2,    66,    39,     2,     2,    65,    51,     2,
      49,    50,    63,    61,    60,    62,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    53,
      57,    45,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      35,    36,    37,    38,    40,    41,    42,    43,    44,    46,
      47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   144,   145,   149,   150,   154,   154,   176,
     177,   181,   182,   183,   184,   185,   186,   187,   188,   192,
     193,   194,   195,   196,   197,   201,   214,   227,   232,   246,
     252,   269,   288,   315,   342,   369,   396,   420,   420,   436,
     437,   441,   455,   469,   483,   497,   511,   528,   528,   540,
     553,   566,   579,   592,   605,   621,   656,   691,   691,   699,
     700,   704,   716,   720,   724,   728,   732,   736,   753,   770,
     787,   804,   812,   820,   824,   829,   834,   838,   843,   848,
     852,   856,   861,   865,   872,   887,   891,   892,   893,   894,
     895,   896,   897,   915,   916,   919,   923
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LET", "MUT",
  "NEWLINE", "INT", "FLOAT", "BOOL", "STR", "TRUE", "FALSE", "GEQ", "LEQ",
  "EQL", "NEQ", "LOR", "LAND", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "REM_ASSIGN", "IF", "ELSE", "FOR", "WHILE", "LOOP",
  "PRINT", "PRINTLN", "FUNC", "RETURN", "BREAK", "ARROW", "AS", "IN",
  "DOTDOT", "RSHIFT", "LSHIFT", "'\"'", "INT_LIT", "FLOAT_LIT",
  "STRING_LIT", "IDENT", "ID", "'='", "LOWER_THAN_ASSIGN",
  "LOWER_THAN_ELSE", "IFX", "'('", "')'", "'&'", "'['", "';'", "']'",
  "':'", "'>'", "'<'", "'{'", "'}'", "','", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "$accept", "Program", "GlobalStatementList",
  "GlobalStatement", "FunctionDeclStmt", "$@1", "StatementList",
  "Statement", "Type", "VarDeclStmt", "AssignmentStmt", "IfStmt", "@2",
  "OptElse", "RelExprJump", "WhileStmt", "@3", "RelExprForWhileJump",
  "PrintStmt", "PrintlnStmt", "Block", "$@4", "ExpressionList",
  "ExpressionStmt", "Expression", "OrExpr", "AndExpr", "RelExpr",
  "AddExpr", "MulExpr", "AsExpr", "UnaryExpr", "Primary", "ArrayIndexExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   -71,   -13,    38,    18,   -71,   -71,     0,   -71,   -71,
      10,   -71,   -19,   -71,   -71,   -71,    60,     9,   -71,   -71,
     129,   129,   129,   129,    23,   -71,   -71,    14,   129,   129,
     -71,   129,   129,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,    -3,    51,    52,   -71,   -10,    42,   -71,    40,
     -71,   -71,    37,   -31,    30,   -71,   115,   -71,    32,    34,
     -71,    59,   129,   129,   129,   129,   129,   129,    62,    53,
     -34,   -71,   -71,   -71,   -71,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,     3,   -30,
     129,     3,   -19,   129,   129,   129,   129,   129,   129,   129,
     -71,   -71,   -71,    55,    57,    61,    63,    64,    67,    69,
     -71,   -71,   129,    52,   -71,   -45,   -45,   -45,   -45,   -45,
     -45,    42,    42,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     104,     3,   -71,   129,     3,    68,   -23,    91,   -45,   -45,
     -45,   -45,   -45,   -45,   -19,   131,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,    71,    72,   -16,   -71,   129,
     -71,   -19,   -71,   -71,   129,   129,   129,   129,   129,   129,
      92,   -71,   129,   -71,    78,   -71,   -45,   -45,   -45,   -45,
     -45,   -45,    79,    81,   -71,   -71,   -71
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     0,     0,     2,     4,     5,     0,     1,     3,
       0,     7,     0,    57,     8,     9,     0,     0,    90,    91,
       0,     0,     0,     0,     0,    88,    89,    92,     0,     0,
      58,     0,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,    62,    64,    66,    73,    76,    80,    82,
      85,    93,     0,     0,    92,    37,     0,    47,     0,     0,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    83,    84,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    56,    86,     0,     0,     0,     0,     0,     0,     0,
      95,    94,     0,    63,    65,    69,    70,    72,    71,    67,
      68,    74,    75,    77,    78,    79,    19,    20,    23,    21,
       0,     0,    81,     0,     0,     0,     0,    40,    45,    46,
      43,    44,    41,    42,     0,     0,    32,    33,    34,    35,
      36,    31,    96,    60,    22,     0,     0,     0,    25,     0,
      27,     0,    38,    48,     0,     0,     0,     0,     0,     0,
       0,    30,     0,    29,     0,    39,    53,    54,    51,    52,
      49,    50,     0,     0,    26,    24,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   134,   -71,   -71,   -71,   -71,   -70,   -71,
     -71,   -71,   -71,   -71,   114,   -71,   -71,   -71,   -71,   -71,
      -8,   -71,   -71,   -71,   -22,   -71,    66,    73,    -2,   -11,
     -71,   -29,   -71,   -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    12,    16,    33,   132,    34,
      35,    36,    92,   162,    55,    37,    99,   144,    38,    39,
      14,    15,    70,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    59,    72,    73,    77,    78,    69,    71,    40,   126,
     127,   128,   129,    52,    90,   133,    83,    84,    56,    56,
     111,   136,   159,     1,    91,   134,   112,    79,    80,   172,
     160,     7,    62,    63,    64,    65,    66,   173,     8,    13,
     103,   104,   105,   106,   107,   108,    81,    82,     2,    10,
      74,    83,    84,    53,   130,   131,   123,   124,   125,    67,
      11,   155,    60,    17,   157,    61,    68,    75,   135,    76,
      18,    19,   121,   122,    88,   115,   116,   117,   118,   119,
     120,    89,    68,    20,   137,   100,    21,   101,    22,    23,
     153,   138,   139,   140,   141,   142,   143,   145,   102,    24,
      25,    26,   109,   110,    27,    85,    86,    87,   146,    28,
     147,   156,    29,   154,   148,   161,   149,   150,    13,    30,
     151,   158,    31,   152,   170,   171,    32,    93,    94,    95,
      96,   184,   182,   185,   186,    57,   163,   174,     9,    18,
      19,   113,     0,   164,   165,   166,   167,     0,     0,   114,
     183,     0,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,   176,   177,   178,   179,   180,   181,    24,    25,
      26,    97,    98,    54,     0,     0,    83,    84,    28,     0,
       0,    29,     0,     0,     0,     0,     0,   168,   169,     0,
       0,    31,    83,    84,     0,    32
};

static const yytype_int16 yycheck[] =
{
      22,    23,    31,    32,    14,    15,    28,    29,    16,     6,
       7,     8,     9,     4,    45,    45,    61,    62,    20,    21,
      54,    91,    45,     5,    55,    55,    60,    37,    38,    45,
      53,    44,    18,    19,    20,    21,    22,    53,     0,    58,
      62,    63,    64,    65,    66,    67,    56,    57,    30,    49,
      53,    61,    62,    44,    51,    52,    85,    86,    87,    45,
      50,   131,    39,     3,   134,    42,    52,    16,    90,    17,
      10,    11,    83,    84,    34,    77,    78,    79,    80,    81,
      82,    44,    52,    23,    92,    53,    26,    53,    28,    29,
     112,    93,    94,    95,    96,    97,    98,    99,    39,    39,
      40,    41,    40,    50,    44,    63,    64,    65,    53,    49,
      53,   133,    52,     9,    53,    24,    53,    53,    58,    59,
      53,    53,    62,    54,    53,    53,    66,    12,    13,    14,
      15,    53,    40,    54,    53,    21,   144,   159,     4,    10,
      11,    75,    -1,    12,    13,    14,    15,    -1,    -1,    76,
     172,    -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,   167,   168,   169,    39,    40,
      41,    56,    57,    44,    -1,    -1,    61,    62,    49,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,
      -1,    62,    61,    62,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    30,    68,    69,    70,    71,    44,     0,    70,
      49,    50,    72,    58,    87,    88,    73,     3,    10,    11,
      23,    26,    28,    29,    39,    40,    41,    44,    49,    52,
      59,    62,    66,    74,    76,    77,    78,    82,    85,    86,
      87,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     4,    44,    44,    81,    95,    81,    91,    91,
      39,    42,    18,    19,    20,    21,    22,    45,    52,    91,
      89,    91,    98,    98,    53,    16,    17,    14,    15,    37,
      38,    56,    57,    61,    62,    63,    64,    65,    34,    44,
      45,    55,    79,    12,    13,    14,    15,    56,    57,    83,
      53,    53,    39,    91,    91,    91,    91,    91,    91,    40,
      50,    54,    60,    93,    94,    95,    95,    95,    95,    95,
      95,    96,    96,    98,    98,    98,     6,     7,     8,     9,
      51,    52,    75,    45,    55,    91,    75,    87,    95,    95,
      95,    95,    95,    95,    84,    95,    53,    53,    53,    53,
      53,    53,    54,    91,     9,    75,    91,    75,    53,    45,
      53,    24,    80,    87,    12,    13,    14,    15,    56,    57,
      53,    53,    45,    53,    91,    87,    95,    95,    95,    95,
      95,    95,    40,    91,    53,    54,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    72,    71,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    79,    78,    80,
      80,    81,    81,    81,    81,    81,    81,    83,    82,    84,
      84,    84,    84,    84,    84,    85,    86,    88,    87,    89,
      89,    90,    91,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    96,    96,    96,
      96,    97,    97,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     5,     5,     7,     5,     8,     6,
       6,     4,     4,     4,     4,     4,     4,     0,     5,     2,
       0,     3,     3,     3,     3,     3,     3,     0,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       3,     2,     1,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     1,     2,     2,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     4
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 7: /* $@1: %empty  */
#line 154 "compiler.y"
                      {
        create_symbol();
        insert_symbol((yyvsp[-2].s_val), "func", -1, yylineno, "(V)V");

        // 如果是 main，產生帶參數的 main
        if (strcmp((yyvsp[-2].s_val), "main") == 0) {
            CODEGEN("\n.method public static main([Ljava/lang/String;)V\n");
        } else {
            CODEGEN("\n.method public static %s()V\n", (yyvsp[-2].s_val));
        }
        CODEGEN(".limit stack 100\n");
        CODEGEN(".limit locals 100\n");
        g_indent_cnt++;  // 進入 function 增加縮排
    }
#line 1749 "y.tab.c"
    break;

  case 8: /* FunctionDeclStmt: FUNC ID '(' ')' $@1 Block  */
#line 167 "compiler.y"
            {
        g_indent_cnt--;
        CODEGEN("return\n");
        CODEGEN(".end method\n");
        free((yyvsp[-4].s_val));
    }
#line 1760 "y.tab.c"
    break;

  case 19: /* Type: INT  */
#line 192 "compiler.y"
              { (yyval.s_val) = "i32"; }
#line 1766 "y.tab.c"
    break;

  case 20: /* Type: FLOAT  */
#line 193 "compiler.y"
              { (yyval.s_val) = "f32"; }
#line 1772 "y.tab.c"
    break;

  case 21: /* Type: STR  */
#line 194 "compiler.y"
              { (yyval.s_val) = "str"; }
#line 1778 "y.tab.c"
    break;

  case 22: /* Type: '&' STR  */
#line 195 "compiler.y"
              { (yyval.s_val) = "str"; }
#line 1784 "y.tab.c"
    break;

  case 23: /* Type: BOOL  */
#line 196 "compiler.y"
              { (yyval.s_val) = "bool"; }
#line 1790 "y.tab.c"
    break;

  case 24: /* Type: '[' Type ';' INT_LIT ']'  */
#line 197 "compiler.y"
                               { printf("INT_LIT %d\n", (yyvsp[-1].i_val)); (yyval.s_val) = "array"; }
#line 1796 "y.tab.c"
    break;

  case 25: /* VarDeclStmt: LET ID '=' Expression ';'  */
#line 201 "compiler.y"
                                {
        int addr = next_addr();
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), addr, yylineno, "-");

        if (strcmp((yyvsp[-1].type), "i32") == 0) {
            CODEGEN("istore %d\n", addr);  // 把 stack top 儲存到 local addr
        } else if (strcmp((yyvsp[-1].type), "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp((yyvsp[-1].type), "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        free((yyvsp[-3].s_val));
    }
#line 1814 "y.tab.c"
    break;

  case 26: /* VarDeclStmt: LET ID ':' Type '=' Expression ';'  */
#line 214 "compiler.y"
                                         {
        int addr = next_addr();
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].s_val), addr, yylineno, "-");

        if (strcmp((yyvsp[-3].s_val), "i32") == 0) {
            CODEGEN("istore %d\n", addr); 
        } else if (strcmp((yyvsp[-3].s_val), "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp((yyvsp[-3].s_val), "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        free((yyvsp[-5].s_val));
    }
#line 1832 "y.tab.c"
    break;

  case 27: /* VarDeclStmt: LET ID ':' Type ';'  */
#line 227 "compiler.y"
                          {
        int addr = next_addr();
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].s_val), addr, yylineno, "-");
        free((yyvsp[-3].s_val));
    }
#line 1842 "y.tab.c"
    break;

  case 28: /* VarDeclStmt: LET MUT ID ':' Type '=' Expression ';'  */
#line 232 "compiler.y"
                                             {
        int addr = next_addr();
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].s_val), addr, yylineno, "-");

        if (strcmp((yyvsp[-3].s_val), "i32") == 0) {
            CODEGEN("istore %d\n", addr);
        } else if (strcmp((yyvsp[-3].s_val), "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp((yyvsp[-3].s_val), "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free((yyvsp[-5].s_val));
    }
#line 1861 "y.tab.c"
    break;

  case 29: /* VarDeclStmt: LET MUT ID ':' Type ';'  */
#line 246 "compiler.y"
                              {
        int addr = next_addr();
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].s_val), addr, yylineno, "-");
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free((yyvsp[-3].s_val));
    }
#line 1872 "y.tab.c"
    break;

  case 30: /* VarDeclStmt: LET MUT ID '=' Expression ';'  */
#line 252 "compiler.y"
                                    {
        int addr = next_addr();
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), addr, yylineno, "-");

        if (strcmp((yyvsp[-1].type), "i32") == 0) {
            CODEGEN("istore %d\n", addr);
        } else if (strcmp((yyvsp[-1].type), "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp((yyvsp[-1].type), "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free((yyvsp[-3].s_val));
    }
#line 1891 "y.tab.c"
    break;

  case 31: /* AssignmentStmt: ID '=' Expression ';'  */
#line 269 "compiler.y"
                            {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0)
                    CODEGEN("istore %d\n", addr);
                else if (strcmp(type, "f32") == 0)
                    CODEGEN("fstore %d\n", addr);
                else if (strcmp(type, "str") == 0)
                    CODEGEN("astore %d\n", addr);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 1915 "y.tab.c"
    break;

  case 32: /* AssignmentStmt: ID ADD_ASSIGN Expression ';'  */
#line 288 "compiler.y"
                                   {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0) {
                    CODEGEN("iload %d\n", addr);   // put x onto stack
                    CODEGEN("swap\n"); // x on the top
                    CODEGEN("iadd\n");
                    CODEGEN("istore %d\n", addr);
                }
                else if (strcmp(type, "f32") == 0){
                    CODEGEN("fload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("fadd\n");
                    CODEGEN("fstore %d\n", addr);
                }
                else if (strcmp(type, "str") == 0)
                    printf("error:%d: invalid operation: `+=` not supported for str\n", yylineno);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 1947 "y.tab.c"
    break;

  case 33: /* AssignmentStmt: ID SUB_ASSIGN Expression ';'  */
#line 315 "compiler.y"
                                   {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0) {
                    CODEGEN("iload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("isub\n");
                    CODEGEN("istore %d\n", addr);
                }
                else if (strcmp(type, "f32") == 0){
                    CODEGEN("fload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("fsub\n");
                    CODEGEN("fstore %d\n", addr);
                }
                else if (strcmp(type, "str") == 0)
                    printf("error:%d: invalid operation: `+=` not supported for str\n", yylineno);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 1979 "y.tab.c"
    break;

  case 34: /* AssignmentStmt: ID MUL_ASSIGN Expression ';'  */
#line 342 "compiler.y"
                                   {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0) {
                    CODEGEN("iload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("imul\n");
                    CODEGEN("istore %d\n", addr);
                }
                else if (strcmp(type, "f32") == 0){
                    CODEGEN("fload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("fmul\n");
                    CODEGEN("fstore %d\n", addr);
                }
                else if (strcmp(type, "str") == 0)
                    printf("error:%d: invalid operation: `+=` not supported for str\n", yylineno);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 2011 "y.tab.c"
    break;

  case 35: /* AssignmentStmt: ID DIV_ASSIGN Expression ';'  */
#line 369 "compiler.y"
                                   {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0) {
                    CODEGEN("iload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("idiv\n");
                    CODEGEN("istore %d\n", addr);
                }
                else if (strcmp(type, "f32") == 0){
                    CODEGEN("fload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("fdiv\n");
                    CODEGEN("fstore %d\n", addr);
                }
                else if (strcmp(type, "str") == 0)
                    printf("error:%d: invalid operation: `+=` not supported for str\n", yylineno);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 2043 "y.tab.c"
    break;

  case 36: /* AssignmentStmt: ID REM_ASSIGN Expression ';'  */
#line 396 "compiler.y"
                                   {
        int addr = lookup_symbol((yyvsp[-3].s_val));
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            if (!is_mutable((yyvsp[-3].s_val))) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, (yyvsp[-3].s_val));
            } else {
                const char* type = get_symbol_type((yyvsp[-3].s_val));
                if (strcmp(type, "i32") == 0) {
                    CODEGEN("iload %d\n", addr);
                    CODEGEN("swap\n");
                    CODEGEN("irem\n");
                    CODEGEN("istore %d\n", addr);
                }
                else if (strcmp(type, "str") == 0)
                    printf("error:%d: invalid operation: `+=` not supported for str\n", yylineno);
            }
        }
        free((yyvsp[-3].s_val));
    }
#line 2069 "y.tab.c"
    break;

  case 37: /* @2: %empty  */
#line 420 "compiler.y"
                     {
        int id = (yyvsp[0].i_val);
        (yyval.i_val) = id;  // 為 midrule 指定型別
        CODEGEN("L_if_%d:\n", id);
    }
#line 2079 "y.tab.c"
    break;

  case 38: /* IfStmt: IF RelExprJump @2 Block OptElse  */
#line 424 "compiler.y"
                    {
        int id = (yyvsp[-2].i_val);  // 取得 midrule 的 id（原本是 $2，現在在 $3）
        if ((yyvsp[0].i_val) != -1)
            CODEGEN("goto L_end_%d\n", id);  // 有 else，跳過 else 區塊
        CODEGEN("L_else_%d:\n", id);         // else 區塊開始 or 無 else 就結束
        if ((yyvsp[0].i_val) != -1)
            ; 
        CODEGEN("L_end_%d:\n", id); 
    }
#line 2093 "y.tab.c"
    break;

  case 39: /* OptElse: ELSE Block  */
#line 436 "compiler.y"
                 { (yyval.i_val) = 1; }
#line 2099 "y.tab.c"
    break;

  case 40: /* OptElse: %empty  */
#line 437 "compiler.y"
                  { (yyval.i_val) = -1; }
#line 2105 "y.tab.c"
    break;

  case 41: /* RelExprJump: AddExpr '>' AddExpr  */
#line 441 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpgt L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2124 "y.tab.c"
    break;

  case 42: /* RelExprJump: AddExpr '<' AddExpr  */
#line 455 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmplt L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2143 "y.tab.c"
    break;

  case 43: /* RelExprJump: AddExpr EQL AddExpr  */
#line 469 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpeq L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2162 "y.tab.c"
    break;

  case 44: /* RelExprJump: AddExpr NEQ AddExpr  */
#line 483 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpne L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2181 "y.tab.c"
    break;

  case 45: /* RelExprJump: AddExpr GEQ AddExpr  */
#line 497 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `>=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpge L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifge L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2200 "y.tab.c"
    break;

  case 46: /* RelExprJump: AddExpr LEQ AddExpr  */
#line 511 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `<=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmple L_if_%d\n", id);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifle L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
#line 2219 "y.tab.c"
    break;

  case 47: /* @3: %empty  */
#line 528 "compiler.y"
                        {
        int id = label_id++;
        (yyval.i_val) = id;
        CODEGEN("L_loop_%d:\n", id);
    }
#line 2229 "y.tab.c"
    break;

  case 48: /* WhileStmt: WHILE RelExprJump @3 RelExprForWhileJump Block  */
#line 532 "compiler.y"
                                {
        int id = (yyvsp[-2].i_val);
        CODEGEN("goto L_loop_%d\n", id);
        CODEGEN("L_end_%d:\n", id);
    }
#line 2239 "y.tab.c"
    break;

  case 49: /* RelExprForWhileJump: AddExpr '>' AddExpr  */
#line 540 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmple L_end_%d\n", id);  // <= 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifle L_end_%d\n", id);       // <= 就跳出
        }
    }
#line 2257 "y.tab.c"
    break;

  case 50: /* RelExprForWhileJump: AddExpr '<' AddExpr  */
#line 553 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpge L_end_%d\n", id);  // >= 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifge L_end_%d\n", id);       // >= 就跳出
        }
    }
#line 2275 "y.tab.c"
    break;

  case 51: /* RelExprForWhileJump: AddExpr EQL AddExpr  */
#line 566 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpne L_end_%d\n", id);  // != 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_end_%d\n", id);       // != 就跳出
        }
    }
#line 2293 "y.tab.c"
    break;

  case 52: /* RelExprForWhileJump: AddExpr NEQ AddExpr  */
#line 579 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpeq L_end_%d\n", id);  // == 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_end_%d\n", id);       // == 就跳出
        }
    }
#line 2311 "y.tab.c"
    break;

  case 53: /* RelExprForWhileJump: AddExpr GEQ AddExpr  */
#line 592 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `>=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmplt L_end_%d\n", id);  // < 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_end_%d\n", id);       // < 就跳出
        }
    }
#line 2329 "y.tab.c"
    break;

  case 54: /* RelExprForWhileJump: AddExpr LEQ AddExpr  */
#line 605 "compiler.y"
                          {
        int id = label_id++;
        (yyval.i_val) = id;

        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `<=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpgt L_end_%d\n", id);  // > 就跳出
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_end_%d\n", id);       // > 就跳出
        }
    }
#line 2347 "y.tab.c"
    break;

  case 55: /* PrintStmt: PRINT Expression ';'  */
#line 621 "compiler.y"
                           {
        if (strcmp((yyvsp[-1].type), "i32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "f32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "bool") == 0) {
            int curr = label_id++;
            // Stack top: boolean (int)
            CODEGEN("ifeq L_false_%d\n", curr);       // if 0 → false
            CODEGEN("ldc \"true\"\n");                // if != 0 → push "true"
            CODEGEN("goto L_end_%d\n", curr);
            CODEGEN("L_false_%d:\n", curr);
            CODEGEN("ldc \"false\"\n");
            CODEGEN("L_end_%d:\n", curr);
            // Stack top: "true" or "false"
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n"); // 把 PrintStream 放下面
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "str") == 0) {
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }

        (yyval.type) = "void";
    }
#line 2384 "y.tab.c"
    break;

  case 56: /* PrintlnStmt: PRINTLN Expression ';'  */
#line 656 "compiler.y"
                             {
        if (strcmp((yyvsp[-1].type), "i32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "f32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "bool") == 0) {
            int curr = label_id++;
            // Stack top: boolean (int)
            CODEGEN("ifeq L_false_%d\n", curr);       // if 0 → false
            CODEGEN("ldc \"true\"\n");                // if != 0 → push "true"
            CODEGEN("goto L_end_%d\n", curr);
            CODEGEN("L_false_%d:\n", curr);
            CODEGEN("ldc \"false\"\n");
            CODEGEN("L_end_%d:\n", curr);
            // Stack top: "true" or "false"
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n"); // 把 PrintStream 放下面
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        } else if (strcmp((yyvsp[-1].type), "str") == 0) {
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        }

        (yyval.type) = "void";
    }
#line 2421 "y.tab.c"
    break;

  case 57: /* $@4: %empty  */
#line 691 "compiler.y"
          {
        create_symbol();    // 進入新scope時建立table
    }
#line 2429 "y.tab.c"
    break;

  case 58: /* Block: '{' $@4 StatementList '}'  */
#line 693 "compiler.y"
                        {
        dump_symbol();      // 離開時丟出table
    }
#line 2437 "y.tab.c"
    break;

  case 59: /* ExpressionList: Expression  */
#line 699 "compiler.y"
                 { (yyval.type) = (yyvsp[0].type); }
#line 2443 "y.tab.c"
    break;

  case 60: /* ExpressionList: ExpressionList ',' Expression  */
#line 700 "compiler.y"
                                    { (yyval.type) = (yyvsp[-2].type); }
#line 2449 "y.tab.c"
    break;

  case 61: /* ExpressionStmt: Expression ';'  */
#line 704 "compiler.y"
                     {
        if (strcmp((yyvsp[-1].type), "bool") == 0) {
            // DO NOTHING!
            // 這是防止布林條件被評估兩次
        } else {
            CODEGEN("pop\n"); // 清除堆疊上的值
        }
    }
#line 2462 "y.tab.c"
    break;

  case 62: /* Expression: OrExpr  */
#line 716 "compiler.y"
             { (yyval.type) = (yyvsp[0].type); }
#line 2468 "y.tab.c"
    break;

  case 63: /* OrExpr: OrExpr LOR AndExpr  */
#line 720 "compiler.y"
                         { 
        CODEGEN("ior\n"); 
        (yyval.type) = "bool"; 
    }
#line 2477 "y.tab.c"
    break;

  case 64: /* OrExpr: AndExpr  */
#line 724 "compiler.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 2483 "y.tab.c"
    break;

  case 65: /* AndExpr: AndExpr LAND RelExpr  */
#line 728 "compiler.y"
                           { 
        CODEGEN("iand\n"); 
        (yyval.type) = "bool"; 
    }
#line 2492 "y.tab.c"
    break;

  case 66: /* AndExpr: RelExpr  */
#line 732 "compiler.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 2498 "y.tab.c"
    break;

  case 67: /* RelExpr: AddExpr '>' AddExpr  */
#line 736 "compiler.y"
                          {
        int curr = label_id++;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpgt L_true_%d\n", curr);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        (yyval.type) = "bool";
    }
#line 2520 "y.tab.c"
    break;

  case 68: /* RelExpr: AddExpr '<' AddExpr  */
#line 753 "compiler.y"
                          { 
        int curr = label_id++;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmplt L_true_%d\n", curr);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        (yyval.type) = "bool";
    }
#line 2542 "y.tab.c"
    break;

  case 69: /* RelExpr: AddExpr EQL AddExpr  */
#line 770 "compiler.y"
                          { 
        int curr = label_id++;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpeq L_true_%d\n", curr);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        (yyval.type) = "bool";
    }
#line 2564 "y.tab.c"
    break;

  case 70: /* RelExpr: AddExpr NEQ AddExpr  */
#line 787 "compiler.y"
                          { 
        int curr = label_id++;
        if (strcmp((yyvsp[-2].type), (yyvsp[0].type)) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else if (strcmp((yyvsp[-2].type), "i32") == 0) {
            CODEGEN("if_icmpne L_true_%d\n", curr);
        } else if (strcmp((yyvsp[-2].type), "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        (yyval.type) = "bool";
    }
#line 2586 "y.tab.c"
    break;

  case 71: /* RelExpr: AddExpr LSHIFT AddExpr  */
#line 804 "compiler.y"
                             {
        if (!(strcmp((yyvsp[-2].type), "i32") == 0 && strcmp((yyvsp[0].type), "i32") == 0)) {
            printf("error:%d: invalid operation: LSHIFT (mismatched types %s and %s)\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else {
            CODEGEN("ishl\n");
        }
        (yyval.type) = "i32";
    }
#line 2599 "y.tab.c"
    break;

  case 72: /* RelExpr: AddExpr RSHIFT AddExpr  */
#line 812 "compiler.y"
                             { 
        if (!(strcmp((yyvsp[-2].type), "i32") == 0 && strcmp((yyvsp[0].type), "i32") == 0)) {
            printf("error:%d: invalid operation: RSHIFT (mismatched types %s and %s)\n", yylineno, (yyvsp[-2].type), (yyvsp[0].type));
        } else {
            CODEGEN("iushr\n");
        }
        (yyval.type) = "i32";
    }
#line 2612 "y.tab.c"
    break;

  case 73: /* RelExpr: AddExpr  */
#line 820 "compiler.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 2618 "y.tab.c"
    break;

  case 74: /* AddExpr: AddExpr '+' MulExpr  */
#line 824 "compiler.y"
                          { 
        if (strcmp((yyvsp[-2].type), "i32") == 0) CODEGEN("iadd\n");
        else if (strcmp((yyvsp[-2].type), "f32") == 0) CODEGEN("fadd\n");
        (yyval.type) = (yyvsp[-2].type);
    }
#line 2628 "y.tab.c"
    break;

  case 75: /* AddExpr: AddExpr '-' MulExpr  */
#line 829 "compiler.y"
                          { 
        if (strcmp((yyvsp[-2].type), "i32") == 0) CODEGEN("isub\n");
        else if (strcmp((yyvsp[-2].type), "f32") == 0) CODEGEN("fsub\n");
        (yyval.type) = (yyvsp[-2].type);
    }
#line 2638 "y.tab.c"
    break;

  case 76: /* AddExpr: MulExpr  */
#line 834 "compiler.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 2644 "y.tab.c"
    break;

  case 77: /* MulExpr: MulExpr '*' UnaryExpr  */
#line 838 "compiler.y"
                            { 
        if (strcmp((yyvsp[-2].type), "i32") == 0) CODEGEN("imul\n");
        else if (strcmp((yyvsp[-2].type), "f32") == 0) CODEGEN("fmul\n");
        (yyval.type) = (yyvsp[-2].type);
    }
#line 2654 "y.tab.c"
    break;

  case 78: /* MulExpr: MulExpr '/' UnaryExpr  */
#line 843 "compiler.y"
                            { 
        if (strcmp((yyvsp[-2].type), "i32") == 0) CODEGEN("idiv\n");
        else if (strcmp((yyvsp[-2].type), "f32") == 0) CODEGEN("fdiv\n");
        (yyval.type) = (yyvsp[-2].type);
    }
#line 2664 "y.tab.c"
    break;

  case 79: /* MulExpr: MulExpr '%' UnaryExpr  */
#line 848 "compiler.y"
                            { 
        if (strcmp((yyvsp[-2].type), "i32") == 0) CODEGEN("irem\n");
        (yyval.type) = (yyvsp[-2].type); 
    }
#line 2673 "y.tab.c"
    break;

  case 81: /* AsExpr: UnaryExpr AS Type  */
#line 856 "compiler.y"
                        {
        if (strcmp((yyvsp[-2].type), "f32") == 0 && strcmp((yyvsp[0].s_val), "i32") == 0) CODEGEN("f2i\n");
        else if (strcmp((yyvsp[-2].type), "i32") == 0 && strcmp((yyvsp[0].s_val), "f32") == 0) CODEGEN("i2f\n");
        (yyval.type) = (yyvsp[0].s_val);
    }
#line 2683 "y.tab.c"
    break;

  case 82: /* AsExpr: UnaryExpr  */
#line 861 "compiler.y"
                { (yyval.type) = (yyvsp[0].type); }
#line 2689 "y.tab.c"
    break;

  case 83: /* UnaryExpr: '-' UnaryExpr  */
#line 865 "compiler.y"
                    {
        if (strcmp((yyvsp[0].type), "i32") == 0)
            CODEGEN("ineg\n");
        else if (strcmp((yyvsp[0].type), "f32") == 0)
            CODEGEN("fneg\n");
        (yyval.type) = (yyvsp[0].type);
    }
#line 2701 "y.tab.c"
    break;

  case 84: /* UnaryExpr: '!' UnaryExpr  */
#line 872 "compiler.y"
                    {
        if (strcmp((yyvsp[0].type), "bool") != 0) {
            printf("error:%d: unary `!` can only be applied to bool, got %s\n", yylineno, (yyvsp[0].type));
            (yyval.type) = strdup("bool");  // 為防止錯誤後續 propagation，可回傳預設型別
        } else {
            int curr = label_id++;
            CODEGEN("ifeq L_true_%d\n", curr);
            CODEGEN("iconst_0\n");
            CODEGEN("goto L_end_%d\n", curr);
            CODEGEN("L_true_%d:\n", curr);
            CODEGEN("iconst_1\n");
            CODEGEN("L_end_%d:\n", curr);
            (yyval.type) = strdup("bool");
        }
    }
#line 2721 "y.tab.c"
    break;

  case 86: /* Primary: '"' STRING_LIT '"'  */
#line 891 "compiler.y"
                         { CODEGEN("ldc \"%s\"\n", (yyvsp[-1].s_val)); (yyval.type) = "str"; free((yyvsp[-1].s_val)); }
#line 2727 "y.tab.c"
    break;

  case 87: /* Primary: '"' '"'  */
#line 892 "compiler.y"
              { CODEGEN("ldc \"\"\n"); (yyval.type) = "str"; }
#line 2733 "y.tab.c"
    break;

  case 88: /* Primary: INT_LIT  */
#line 893 "compiler.y"
                 { CODEGEN("ldc %d\n", (yyvsp[0].i_val)); (yyval.type) = "i32"; }
#line 2739 "y.tab.c"
    break;

  case 89: /* Primary: FLOAT_LIT  */
#line 894 "compiler.y"
                 { CODEGEN("ldc %f\n", (yyvsp[0].f_val)); (yyval.type) = "f32"; }
#line 2745 "y.tab.c"
    break;

  case 90: /* Primary: TRUE  */
#line 895 "compiler.y"
            { CODEGEN("iconst_1\n"); (yyval.type) = "bool"; }
#line 2751 "y.tab.c"
    break;

  case 91: /* Primary: FALSE  */
#line 896 "compiler.y"
            { CODEGEN("iconst_0\n"); (yyval.type) = "bool"; }
#line 2757 "y.tab.c"
    break;

  case 92: /* Primary: ID  */
#line 897 "compiler.y"
         {
        int ref = lookup_symbol((yyvsp[0].s_val));
        const char* type = get_symbol_type((yyvsp[0].s_val));
        if (ref == -1) {
            HAS_ERROR = true;
            printf("error:%d: undefined: %s\n", yylineno, (yyvsp[0].s_val));
            (yyval.type) = strdup("undefined");
        } else {
            if (strcmp(type, "i32") == 0)
                CODEGEN("iload %d\n", ref);
            else if (strcmp(type, "f32") == 0)
                CODEGEN("fload %d\n", ref);
            else if (strcmp(type, "str") == 0)
                CODEGEN("aload %d\n", ref);
            (yyval.type) = strdup(type);
        }
        free((yyvsp[0].s_val));
    }
#line 2780 "y.tab.c"
    break;

  case 93: /* Primary: ArrayIndexExpr  */
#line 915 "compiler.y"
                     { (yyval.type) = (yyvsp[0].type); }
#line 2786 "y.tab.c"
    break;

  case 94: /* Primary: '[' ExpressionList ']'  */
#line 916 "compiler.y"
                             {
        (yyval.type) = "array";
    }
#line 2794 "y.tab.c"
    break;

  case 95: /* Primary: '(' Expression ')'  */
#line 919 "compiler.y"
                         { (yyval.type) = (yyvsp[-1].type); }
#line 2800 "y.tab.c"
    break;

  case 96: /* ArrayIndexExpr: ID '[' INT_LIT ']'  */
#line 923 "compiler.y"
                         {
        int ref = lookup_symbol((yyvsp[-3].s_val));
        if (ref == -1) {
            HAS_ERROR = true;
            printf("error:%d: undefined variable %s\n", yylineno, (yyvsp[-3].s_val));
        } else {
            // printf("IDENT (name=%s, address=%d)\n", $1, ref);
            // printf("INT_LIT %d\n", $3);
        }
        (yyval.type) = strdup("array");
        free((yyvsp[-3].s_val));
    }
#line 2817 "y.tab.c"
    break;


#line 2821 "y.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 937 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");

    /* Symbol table init */
    // Add your code
    init_symbol();

    yylineno = 0;
    yyparse();

    /* Symbol table dump */
    // Add your code
    dump_symbol();

	printf("Total lines: %d\n", yylineno);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
    return 0;
}

static void create_symbol() {
    scope_top++;
    scope_stack[scope_top].count = 0;
    scope_stack[scope_top].level = scope_top;
    printf("> Create symbol table (scope level %d)\n", scope_top);
}

static void init_symbol() {
    scope_top = -1;
}

static int insert_symbol(const char *name, const char *type, int addr, int lineno, const char *sig) {
    Scope *current = &scope_stack[scope_top];
    Symbol *s = &current->symbols[current->count++];
    strcpy(s->name, name);
    strcpy(s->type, type);
    s->addr = addr;
    s->lineno = lineno;
    s->mut = 0;
    // 根據 type 判斷 mut 欄位值
    if (strcmp(type, "func") == 0) {
        s->mut = -1;
    } else {
        s->mut = 0;
    }
    strcpy(s->func_sig, sig);
    printf("> Insert `%s` (addr: %d) to scope level %d\n", name, addr, get_scope_level());
    return addr;
}

static int lookup_symbol(const char *name) {
    for (int i = scope_top; i >= 0; i--) {
        Scope *s = &scope_stack[i];
        for (int j = 0; j < s->count; j++) {
            if (strcmp(s->symbols[j].name, name) == 0) {
                return s->symbols[j].addr;
            }
        }
    }
    return -1;
}

static void dump_symbol() {
    Scope *current = &scope_stack[scope_top];
    printf("\n> Dump symbol table (scope level: %d)\n", current->level);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut", "Type", "Addr", "Lineno", "Func_sig");
    for (int i = 0; i < current->count; i++) {
        Symbol *s = &current->symbols[i];
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            i, s->name, s->mut, s->type, s->addr, s->lineno, s->func_sig);
    }
    scope_top--;
}

static const char* get_symbol_type(const char *name) {
    for (int i = scope_top; i >= 0; i--) {
        Scope *s = &scope_stack[i];
        for (int j = 0; j < s->count; j++) {
            if (strcmp(s->symbols[j].name, name) == 0) {
                return s->symbols[j].type;
            }
        }
    }
    return NULL;
}

static int next_addr() {
    return addr_counter++;
}

static int get_scope_level() {
    return scope_top;
}
