
/* Please feel free to modify any content */

/* Definition section */
%{
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
%}

%define parse.error verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 *  - you can add new fields if needed.
 */
%union {
    int i_val;
    float f_val;
    char *s_val;
    char* type; /* i32, f32, str, bool */
}

/* Token without return */
%token LET MUT NEWLINE
%token INT FLOAT BOOL STR
%token TRUE FALSE
%token GEQ LEQ EQL NEQ LOR LAND
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN
%token IF ELSE FOR WHILE LOOP
%token PRINT PRINTLN
%token FUNC RETURN BREAK
%token ARROW AS IN DOTDOT RSHIFT LSHIFT
%token '"'

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT
%token <s_val> IDENT
%token <s_val> ID

/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type
%type <i_val> RelExprJump IfStmt OptElse WhileStmt
%type <type> VarDeclStmt PrintStmt PrintlnStmt
%type <type> Expression OrExpr AndExpr RelExpr AddExpr MulExpr AsExpr UnaryExpr Primary
%type <type> ExpressionList ArrayIndexExpr

%left '=' ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN
%left LOWER_THAN_ASSIGN
%nonassoc LOWER_THAN_ELSE
%nonassoc IFX
%nonassoc ELSE

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : GlobalStatementList
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;

GlobalStatement
    : FunctionDeclStmt
    | NEWLINE
;

FunctionDeclStmt
    : FUNC ID '(' ')' {
        create_symbol();
        insert_symbol($2, "func", -1, yylineno, "(V)V");

        // 如果是 main，產生帶參數的 main
        if (strcmp($2, "main") == 0) {
            CODEGEN("\n.method public static main([Ljava/lang/String;)V\n");
        } else {
            CODEGEN("\n.method public static %s()V\n", $2);
        }
        CODEGEN(".limit stack 100\n");
        CODEGEN(".limit locals 100\n");
        g_indent_cnt++;  // 進入 function 增加縮排
    } Block {
        g_indent_cnt--;
        CODEGEN("return\n");
        CODEGEN(".end method\n");
        free($2);
    }
;

StatementList
    : /* empty */
    | StatementList Statement
;

Statement
    : VarDeclStmt
    | AssignmentStmt
    | IfStmt
    | WhileStmt
    | PrintStmt
    | PrintlnStmt
    | Block
    | ExpressionStmt
;

Type
    : INT     { $$ = "i32"; }
    | FLOAT   { $$ = "f32"; }
    | STR     { $$ = "str"; }
    | '&' STR { $$ = "str"; }
    | BOOL    { $$ = "bool"; }
    | '[' Type ';' INT_LIT ']' { printf("INT_LIT %d\n", $4); $$ = "array"; }
;

VarDeclStmt
    : LET ID '=' Expression ';' {
        int addr = next_addr();
        insert_symbol($2, $4, addr, yylineno, "-");

        if (strcmp($4, "i32") == 0) {
            CODEGEN("istore %d\n", addr);  // 把 stack top 儲存到 local addr
        } else if (strcmp($4, "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp($4, "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        free($2);
    }
    | LET ID ':' Type '=' Expression ';' {
        int addr = next_addr();
        insert_symbol($2, $4, addr, yylineno, "-");

        if (strcmp($4, "i32") == 0) {
            CODEGEN("istore %d\n", addr); 
        } else if (strcmp($4, "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp($4, "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        free($2);
    }
    | LET ID ':' Type ';' {
        int addr = next_addr();
        insert_symbol($2, $4, addr, yylineno, "-");
        free($2);
    }    
    | LET MUT ID ':' Type '=' Expression ';' {
        int addr = next_addr();
        insert_symbol($3, $5, addr, yylineno, "-");

        if (strcmp($5, "i32") == 0) {
            CODEGEN("istore %d\n", addr);
        } else if (strcmp($5, "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp($5, "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free($3);
    }
    | LET MUT ID ':' Type ';' {
        int addr = next_addr();
        insert_symbol($3, $5, addr, yylineno, "-");
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free($3);
    }
    | LET MUT ID '=' Expression ';' {
        int addr = next_addr();
        insert_symbol($3, $5, addr, yylineno, "-");

        if (strcmp($5, "i32") == 0) {
            CODEGEN("istore %d\n", addr);
        } else if (strcmp($5, "f32") == 0) {
            CODEGEN("fstore %d\n", addr);
        } else if (strcmp($5, "str") == 0) {
            CODEGEN("astore %d\n", addr);
        }
        scope_stack[scope_top].symbols[scope_stack[scope_top].count - 1].mut = 1;
        free($3);
    }
;

AssignmentStmt
    : ID '=' Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
                if (strcmp(type, "i32") == 0)
                    CODEGEN("istore %d\n", addr);
                else if (strcmp(type, "f32") == 0)
                    CODEGEN("fstore %d\n", addr);
                else if (strcmp(type, "str") == 0)
                    CODEGEN("astore %d\n", addr);
            }
        }
        free($1);
    }
    | ID ADD_ASSIGN Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
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
        free($1);
    }
    | ID SUB_ASSIGN Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
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
        free($1);
    }
    | ID MUL_ASSIGN Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
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
        free($1);
    }
    | ID DIV_ASSIGN Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
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
        free($1);
    }
    | ID REM_ASSIGN Expression ';' {
        int addr = lookup_symbol($1);
        if (addr == -1) {
            printf("error:%d: undefined: %s\n", yylineno, $1);
        } else {
            if (!is_mutable($1)) {
                printf("error:%d: cannot borrow immutable borrowed content `%s` as mutable\n", yylineno, $1);
            } else {
                const char* type = get_symbol_type($1);
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
        free($1);
    }
;

IfStmt
    : IF RelExprJump {
        int id = $2;
        $<i_val>$ = id;  // 為 midrule 指定型別
        CODEGEN("L_if_%d:\n", id);
    } Block OptElse {
        int id = $<i_val>3;  // 取得 midrule 的 id（原本是 $2，現在在 $3）
        if ($5 != -1)
            CODEGEN("goto L_end_%d\n", id);  // 有 else，跳過 else 區塊
        CODEGEN("L_else_%d:\n", id);         // else 區塊開始 or 無 else 就結束
        if ($5 != -1)
            ; 
        CODEGEN("L_end_%d:\n", id); 
    }
;

OptElse
    : ELSE Block { $$ = 1; }
    | /* empty */ { $$ = -1; }
;

RelExprJump
    : AddExpr '>' AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpgt L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
    | AddExpr '<' AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmplt L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
    | AddExpr EQL AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpeq L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
    | AddExpr NEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpne L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
    | AddExpr GEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `>=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpge L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifge L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
    | AddExpr LEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `<=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmple L_if_%d\n", id);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifle L_if_%d\n", id);
        }
        // CODEGEN("goto L_else_%d\n", id);
        // CODEGEN("L_if_%d:\n", id);
    }
;

WhileStmt
    : WHILE RelExprJump {
        int id = label_id++;
        $<i_val>$ = id;
        CODEGEN("L_loop_%d:\n", id);
    } RelExprForWhileJump Block {
        int id = $<i_val>3;
        CODEGEN("goto L_loop_%d\n", id);
        CODEGEN("L_end_%d:\n", id);
    }
;

RelExprForWhileJump
    : AddExpr '>' AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmple L_end_%d\n", id);  // <= 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifle L_end_%d\n", id);       // <= 就跳出
        }
    }
    | AddExpr '<' AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpge L_end_%d\n", id);  // >= 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifge L_end_%d\n", id);       // >= 就跳出
        }
    }
    | AddExpr EQL AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpne L_end_%d\n", id);  // != 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_end_%d\n", id);       // != 就跳出
        }
    }
    | AddExpr NEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpeq L_end_%d\n", id);  // == 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_end_%d\n", id);       // == 就跳出
        }
    }
    | AddExpr GEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `>=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmplt L_end_%d\n", id);  // < 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_end_%d\n", id);       // < 就跳出
        }
    }
    | AddExpr LEQ AddExpr {
        int id = label_id++;
        $<i_val>$ = id;

        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `<=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpgt L_end_%d\n", id);  // > 就跳出
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_end_%d\n", id);       // > 就跳出
        }
    }
;

PrintStmt 
    : PRINT Expression ';' {
        if (strcmp($2, "i32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        } else if (strcmp($2, "f32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        } else if (strcmp($2, "bool") == 0) {
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
        } else if (strcmp($2, "str") == 0) {
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }

        $$ = "void";
    }
;

PrintlnStmt 
    : PRINTLN Expression ';' {
        if (strcmp($2, "i32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        } else if (strcmp($2, "f32") == 0) {
            CODEGEN("invokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        } else if (strcmp($2, "bool") == 0) {
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
        } else if (strcmp($2, "str") == 0) {
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        }

        $$ = "void";
    }
;

Block
    : '{' {
        create_symbol();    // 進入新scope時建立table
    } StatementList '}' {
        dump_symbol();      // 離開時丟出table
    }
;

ExpressionList
    : Expression { $$ = $1; }
    | ExpressionList ',' Expression { $$ = $1; }
;

ExpressionStmt
    : Expression ';' {
        if (strcmp($1, "bool") == 0) {
            // DO NOTHING!
            // 這是防止布林條件被評估兩次
        } else {
            CODEGEN("pop\n"); // 清除堆疊上的值
        }
    }
;


Expression
    : OrExpr { $$ = $1; }
;

OrExpr
    : OrExpr LOR AndExpr { 
        CODEGEN("ior\n"); 
        $$ = "bool"; 
    }
    | AndExpr { $$ = $1; }
;

AndExpr
    : AndExpr LAND RelExpr { 
        CODEGEN("iand\n"); 
        $$ = "bool"; 
    }
    | RelExpr { $$ = $1; }
;

RelExpr
    : AddExpr '>' AddExpr {
        int curr = label_id++;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `>`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpgt L_true_%d\n", curr);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifgt L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        $$ = "bool";
    }
    | AddExpr '<' AddExpr { 
        int curr = label_id++;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `<`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmplt L_true_%d\n", curr);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("iflt L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        $$ = "bool";
    }
    | AddExpr EQL AddExpr { 
        int curr = label_id++;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `==`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpeq L_true_%d\n", curr);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifeq L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        $$ = "bool";
    }
    | AddExpr NEQ AddExpr { 
        int curr = label_id++;
        if (strcmp($1, $3) != 0) {
            printf("error:%d: mismatched types in `!=`: %s and %s\n", yylineno, $1, $3);
        } else if (strcmp($1, "i32") == 0) {
            CODEGEN("if_icmpne L_true_%d\n", curr);
        } else if (strcmp($1, "f32") == 0) {
            CODEGEN("fcmpl\n");
            CODEGEN("ifne L_true_%d\n", curr);
        }
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end_%d\n", curr);
        CODEGEN("L_true_%d:\n", curr);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end_%d:\n", curr);
        $$ = "bool";
    }
    | AddExpr LSHIFT AddExpr {
        if (!(strcmp($1, "i32") == 0 && strcmp($3, "i32") == 0)) {
            printf("error:%d: invalid operation: LSHIFT (mismatched types %s and %s)\n", yylineno, $1, $3);
        } else {
            CODEGEN("ishl\n");
        }
        $$ = "i32";
    }
    | AddExpr RSHIFT AddExpr { 
        if (!(strcmp($1, "i32") == 0 && strcmp($3, "i32") == 0)) {
            printf("error:%d: invalid operation: RSHIFT (mismatched types %s and %s)\n", yylineno, $1, $3);
        } else {
            CODEGEN("iushr\n");
        }
        $$ = "i32";
    }
    | AddExpr { $$ = $1; }
;

AddExpr
    : AddExpr '+' MulExpr { 
        if (strcmp($1, "i32") == 0) CODEGEN("iadd\n");
        else if (strcmp($1, "f32") == 0) CODEGEN("fadd\n");
        $$ = $1;
    }
    | AddExpr '-' MulExpr { 
        if (strcmp($1, "i32") == 0) CODEGEN("isub\n");
        else if (strcmp($1, "f32") == 0) CODEGEN("fsub\n");
        $$ = $1;
    }
    | MulExpr { $$ = $1; }
;

MulExpr
    : MulExpr '*' UnaryExpr { 
        if (strcmp($1, "i32") == 0) CODEGEN("imul\n");
        else if (strcmp($1, "f32") == 0) CODEGEN("fmul\n");
        $$ = $1;
    }
    | MulExpr '/' UnaryExpr { 
        if (strcmp($1, "i32") == 0) CODEGEN("idiv\n");
        else if (strcmp($1, "f32") == 0) CODEGEN("fdiv\n");
        $$ = $1;
    }
    | MulExpr '%' UnaryExpr { 
        if (strcmp($1, "i32") == 0) CODEGEN("irem\n");
        $$ = $1; 
    }
    | AsExpr
;

AsExpr
    : UnaryExpr AS Type {
        if (strcmp($1, "f32") == 0 && strcmp($3, "i32") == 0) CODEGEN("f2i\n");
        else if (strcmp($1, "i32") == 0 && strcmp($3, "f32") == 0) CODEGEN("i2f\n");
        $$ = $3;
    }
    | UnaryExpr { $$ = $1; }
;

UnaryExpr
    : '-' UnaryExpr {
        if (strcmp($2, "i32") == 0)
            CODEGEN("ineg\n");
        else if (strcmp($2, "f32") == 0)
            CODEGEN("fneg\n");
        $$ = $2;
    }
    | '!' UnaryExpr {
        if (strcmp($2, "bool") != 0) {
            printf("error:%d: unary `!` can only be applied to bool, got %s\n", yylineno, $2);
            $$ = strdup("bool");  // 為防止錯誤後續 propagation，可回傳預設型別
        } else {
            int curr = label_id++;
            CODEGEN("ifeq L_true_%d\n", curr);
            CODEGEN("iconst_0\n");
            CODEGEN("goto L_end_%d\n", curr);
            CODEGEN("L_true_%d:\n", curr);
            CODEGEN("iconst_1\n");
            CODEGEN("L_end_%d:\n", curr);
            $$ = strdup("bool");
        }
    }
    | Primary
;

Primary
    : '"' STRING_LIT '"' { CODEGEN("ldc \"%s\"\n", $2); $$ = "str"; free($2); }
    | '"' '"' { CODEGEN("ldc \"\"\n"); $$ = "str"; }
    | INT_LIT    { CODEGEN("ldc %d\n", $1); $$ = "i32"; }
    | FLOAT_LIT  { CODEGEN("ldc %f\n", $1); $$ = "f32"; }
    | TRUE  { CODEGEN("iconst_1\n"); $$ = "bool"; }
    | FALSE { CODEGEN("iconst_0\n"); $$ = "bool"; }
    | ID {
        int ref = lookup_symbol($1);
        const char* type = get_symbol_type($1);
        if (ref == -1) {
            HAS_ERROR = true;
            printf("error:%d: undefined: %s\n", yylineno, $1);
            $$ = strdup("undefined");
        } else {
            if (strcmp(type, "i32") == 0)
                CODEGEN("iload %d\n", ref);
            else if (strcmp(type, "f32") == 0)
                CODEGEN("fload %d\n", ref);
            else if (strcmp(type, "str") == 0)
                CODEGEN("aload %d\n", ref);
            $$ = strdup(type);
        }
        free($1);
    }
    | ArrayIndexExpr { $$ = $1; }
    | '[' ExpressionList ']' {
        $$ = "array";
    }
    | '(' Expression ')' { $$ = $2; }
;

ArrayIndexExpr
    : ID '[' INT_LIT ']' {
        int ref = lookup_symbol($1);
        if (ref == -1) {
            HAS_ERROR = true;
            printf("error:%d: undefined variable %s\n", yylineno, $1);
        } else {
            // printf("IDENT (name=%s, address=%d)\n", $1, ref);
            // printf("INT_LIT %d\n", $3);
        }
        $$ = strdup("array");
        free($1);
    }
;

%%

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