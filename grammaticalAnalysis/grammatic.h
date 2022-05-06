#include<stdio.h>
#include<stdlib.h>

#include<iostream>

using namespace std;

#include "lexcialAnalysis.h"

/* 全局变量 */

/* 语法缩进功能 */
int syntax_state;   //语法状态
int syntax_level;   //缩进级别

/* external_declaration解析声明，为避免重复造轮子
    通过参数识别声明的变量类型（函数内部和外部）
*/
int SC_GLOBAL = 0;  //函数外部解析状态
int SC_LOCAL = 1;   //函数内部解析状态

/* 语法状态枚举值 */
enum e_SyntaxState{
    SNTX_NUL,   //空状态，没有缩进
    SNTX_SP,    //空格
    SNTX_LF_HT, //换行并缩进，每一个声明，函数定义，语句结束都要设置
    SNTX_DELAY  //延迟到取出下一个单词后确定输出格式
};



/* 函数声明 */
void translation_unit();
void external_declaration(int l);
int type_specifier();
void struct_specifier();
void struct_declaration_list();
void declarator();
void direct_declarator();


/* 语法分析 */

/* =================================
外部定义
<translation_unit> ::= {<external_declaration>}<TK_EOF>
<translation_unit>
==================================== */
void translation_unit(){
    while(token != TK_EOF){
        external_declaration(SC_GLOBAL);
    }
}

/* 
外部声明
 */
void external_declaration(int l){
    if(!type_specifier()){
        expect("<类型区分符>");
    }

    if(token == TK_SEMICOLON){
        get_token();
        return;
    }

    while(1){
        declarator();
        if(token == TK_BEGIN){
            if(l == SC_LOCAL){
                char bufError[30] = "不支持函数嵌套定义";
                error(bufError);
            }
            funcbody();
            break;
        }
        else{
            if(token == TK_ASSIGN){
                get_token();
                initializer();
            }
            if(token == TK_COMMA){
                get_token();
            }
            else{
                syntax_state = SNTX_LF_HT;
                skip(TK_SEMICOLON);
                break;
            }
        }
    }
}

/*========================
 类型区分符号 
 <type_specifier> ::=
    <KW_INT>|<KW_CHAR>|<KW_SHORT>|<KW_VOID>|<strcut_specifier>
 ==========================*/
 int type_specifier(){
     int type_found = 0;
     switch(token){
         case KW_CHAR:
            type_found = 1;
            syntax_state = SNTX_SP;
            get_token();
            break;
        case KW_SHORT:
            type_found = 1;
            syntax_state = SNTX_SP;
            get_token();
            break;
        case KW_VOID:
            type_found = 1;
            syntax_state = SNTX_SP;
            get_token();
            break;
        case KW_INT:
            syntax_state = SNTX_SP;
            type_found = 1;
            get_token();
            break;
        case KW_STRUCT:
            syntax_state = SNTX_SP;
            struct_specifier();
            type_found = 1;
            break;
        default:
            break;
     }
     return type_found;
 }


/* =======================================
结构区分符号
<strcut_specifier> ::=
<KW_STRUCT><IDENTIFIER><TK_BEGIN><struct_declaration_list><TK_END>
    |<KW_STRUCT><IDENTIFIER>
========================================== */
void struct_specifier(){
    int v;
    get_token();
    v=token;

    syntax_state = SNTX_DELAY;  //延迟到取出下一个单词后确定输出格式

    get_token();

    if(token == TK_BEGIN){          //结构体定义
        syntax_state = SNTX_LF_HT;
    }
    else if(token == TK_CLOSEPA){
        syntax_state = SNTX_NUL;    //sizeof(struct struct_name)
    }
    else{
        syntax_state = SNTX_SP;     //结构体变量声明
    }

    syntax_indent();

    if(v < TK_IDENT){       //关键字不能作为结构体名称
        expect("结构体名");
    }

    if(token == TK_BEGIN){
        struct_declaration_list();
    }
}


/*==================================
 结构声明符表 
 <struct_declaration_list> ::=
    <struct_declatation>{<struct_declatation>}
 ===================================*/
void struct_declaration_list(){
    int maxalign, offset;

    syntax_state = SNTX_LF_HT;  //第一个结构体成员与'{'不写在一行
    syntax_level++;             //结构体成员变量声明，缩进加一级

    get_token();
    while(token != TK_END){
        struct_declaration(&maxalign, &offset);
    }

    skip(TK_END);

    syntax_state = SNTX_LF_HT;
}

/* =========================================
结构声明
<struct_declaration> ::=
    <type_specifier><struct_declarator_list><TK_SEMICOLON>*
<strcut_declarator_list>::=
    <declarator>{<TK_COMMA><declarator>}

等价转换后
<struct_declaration> ::=
    <type_specifirr><declarator>{<TK_COMMA><declarator>}
    <TK_SEMICOLON>
============================================ */
void struct_declaration(){
    type_specifier();
    while(1){
        declarator();

        if(token == TK_SEMICOLON){
            break;
        }
        skip(TK_COMMA);
    }

    syntax_state = SNTX_LF_HT;
    skip(TK_SEMICOLON);
}


/* ======================================
函数调用约定
<function_calling_convention>::=<KW_CDECL>|<KW_STDCALL>
========================================= */
void function_calling_convention(int *fc){
    *fc = KW_CDECL;

    if(token == KW_CDECL || token == KW_STDCALL){
        *fc = token;
        syntax_state = SNTX_SP;
        get_token();
    }
}


/* =======================================
结构成员对齐
<struct_member_alignment>::=<KW_ALIGN><TK_OPENPA><TK_CINT><TK_CLOSEPA>
========================================== */
void struct_member_alignment(){
    if(token == KW_ALIGN){
        get_token();
        skip(TK_OPENPA);
        if(token == TK_CINT){
            get_token();
        }
        else{
            expect("整数常量");
        }
        skip(TK_CLOSEPA);
    }
}

/* =======================================
声明符
<declarator> ::= {<pointer>}[<function_calling_convention>]
    [<struct_member_alignment>]<ditect_declarator>
<pointer>::=<TK_STAR>
转换
<declarator>::={<TK_STAR>}[<function_calling_convention>]
    [<struct_member_alignment>]<direct_declarator>
========================================== */
void declarator(){
    int fc;
    while(token == TK_STAR){
        get_token();
    }
    function_calling_convention(&fc);
    struct_member_alignment();
    direct_declarator();
}

/* ========================================
直接声明符
<direct_declarator> ::= <IDENTIFIER><direct_declarator_postfix>
=========================================== */
void direct_declarator(){
    if(token >= TK_IDENT){
        get_token();
    }
    else{
        expect("标识符");
    }

    direct_declarator_postfix();
}

/* ========================================
直接声明符后缀 
===========================================*/
void direct_declarator_postfix(){
    int n;
    if(token == TK_OPENPA){
        parameter_type_list();
    }
    else if(token == TK_OPENBR){
        get_token();
        if(token == TK_CINT){
            get_token();
            n = tkvalue;
        }
        skip(TK_CLOSEBR);
        direct_declarator_postfix();
    }
}

/* ========================================
形参类型表
===========================================*/
void parameter_type_list(int func_call){
    get_token();
    while(token != TK_CLOSEPA){
        if(!type_specifier()){
            char bufParam[30] = "无效类型标识符";
            error(bufParam);
        }

        declarator();

        if(token == TK_CLOSEPA){
            break;
        }

        skip(TK_COMMA);
        if(token == TK_ELLIPSIS){
            func_call = KW_CDECL;
            get_token();
            break;
        }
    }

    syntax_state = SNTX_DELAY;
    skip(TK_CLOSEPA);

    if(token == TK_BEGIN){  //函数定义
        syntax_state = SNTX_LF_HT;
    }
    else   {                //函数声明
        syntax_state = SNTX_NUL;
    }

    syntax_indent();
}

/* ========================================
函数体

调用compound_statement()，没有把程序单独放到这里的原因是
单看语法分析，直接放代码是正确的
但现在才语法分析，后面还有语义分析等，我希望先定义架构，后期
尽可能的少做结构性调整
===========================================*/
void funcbody(){
    compound_statement();
}

/* ========================================
初值符
===========================================*/
void initializer(){
    assignment_expression();
}

/* ========================================
语句
===========================================*/
void statement(int *bsym, int *csym){
    switch(token){
        case TK_BEGIN:
            compound_statement(bsym, csym);
            break;
        case KW_IF:
            if_statement(bsym, csym);
            break;
        case KW_RETURN:
            return_statement();
            break;
        case KW_BREAK:
            break_statement(bstm);
            break;
        case KW_CONTINUE:
            continue_statement(csym);
            break;
        case KW_FOR:
            for_statement(bsym, csym);
            break;
        default:
            expression_statement();
            break;
    }
}

/* ========================================
符合语句
is_type_specifier()是根据取到的当前单词判断是否是声明的函数
===========================================*/
void compound_statement(){
    syntax_state = SNTX_LF_HT;
    syntax_level++;             //符合语句缩进增加一级

    get_token();
    while(is_type_specifier(token)){
        external_declaration(SC_LOCAL);
    }
    while(token != TK_END){
        statement();
    }

    syntax_state = SNTX_LF_HT;

    get_token();
}


/* ========================================
判断是否为类型区分符
is_type_specifier()是根据取到的当前单词判断是否是声明的函数
===========================================*/
int is_type_specifier(int v){
    switch(v){
        case KW_CHAR:
        case KW_SHORT:
        case KW_INT:
        case KW_VOID:
        case KW_STRUCT:
            return 1;

        default:
            break;
    }

    return 0;
}

/* ========================================
表达式语句
===========================================*/
void expression_statement(){
    if(token != TK_SEMICOLON){
        expression();
    }

    syntax_state = SNTX_LF_HT;
    skip(TK_SEMICOLON);
}


/* ========================================
选择语句
===========================================*/
void if_statement(){
    syntax_state = SNTX_SP;
    get_token();
    skip(TK_OPENPA);
    expression();
    syntax_state = SNTX_LF_HT;
    skip(TK_CLOSEPA);
    statement();

    if(token == KW_ELSE){
        syntax_state = SNTX_LF_HT;
        get_token();
        statement();
    }
}


/* ========================================
循环语句
===========================================*/
void for_statement(){
    get_token();
    skip(TK_OPENPA);
    if(token != TK_SEMICOLON){
        expression();
    }

    skip(TK_SEMICOLON);

    if(token != TK_SEMICOLON){
        expression();
    }

    skip(TK_SEMICOLON);

    if(token != TK_CLOSEPA){
        expression();
    }

    syntax_state = SNTX_LF_HT;
    skip(TK_CLOSEPA);
    statement();
}

/* ========================================
跳转语句
暂时没有对continue的位置进行限定
按理说，continue只能出现在循环中
此时，即使其出现在循环外也能编译通过
这将在语义分析部分进行限定
===========================================*/
void continue_statement(){
    get_token();
    syntax_state = SNTX_LF_HT;
    skip(TK_SEMICOLON);
}

/* ========================================
break语句
===========================================*/
void break_statement(){
    get_token();
    syntax_state = SNTX_LF_HT;
    skip(TK_SEMICOLON);
}

/* ========================================
return语句
===========================================*/
void return_statement(){
    syntax_state = SNTX_DELAY;
    get_token();
    if(token == TK_SEMICOLON){  //return
        syntax_state = SNTX_NUL;
    }
    else{                       //return <expression>
        syntax_state = SNTX_SP;
    }
    syntax_indent();

    if(token != TK_SEMICOLON){
        expression();
    }

    syntax_state = SNTX_LF_HT;
    skip(TK_SEMICOLON);
}

/* ========================================
表达式
===========================================*/
void expression(){
    while(1){
        assignment_expression();
        if(token != TK_COMMA){
            break;
        }

        get_token();
    }
}


/* ========================================
赋值表达式
===========================================*/
void assignment_expression(){
    equality_expression();

    if(token == TK_ASSIGN){
        get_token();
        assignment_expression();
    }
}