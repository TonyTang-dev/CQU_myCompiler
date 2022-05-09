#include<stdio.h>
#include<stdlib.h>

#include<iostream>

using namespace std;

#include "lexcialAnalysis.h"



/* 函数声明 */
void translation_unit();
void external_declaration(int l);
int type_specifier();
void struct_specifier();
void struct_declaration_list();
void struct_declaration();
void function_calling_convention(int *fc);
void struct_member_alignment();
void declarator();
void direct_declarator();
void direct_declarator_postfix();
void parameter_type_list(int func_call);
void funcbody();
void initializer();
void statement();
void compound_statement();
int is_type_specifier(int v);
void expression_statement();
void if_statement();
void for_statement();
void continue_statement();
void break_statement();
void return_statement();
void expression();
void assignment_expression();
void equality_expression();
void relational_expression();
void additive_expression();
void multiplicative_expression();
void unary_expression();
void postfix_expression();
void primary_expression();
void argument_expression_list();
void sizeof_expression();



/* 语法分析 ，从主函数已经获得第一个符号*/

/* =================================
外部定义
<translation_unit> ::= {<external_declaration>}<TK_EOF>
<translation_unit>
==================================== */
void translation_unit(){
    // 逐个分析单词
    while(token != TK_EOF){
        external_declaration(SC_GLOBAL);
    }

    // 语法分析结束
    // 暂时写入主函数结束和程序文法结束
    fprintf(fout, "%s\n%s\n",grammarTypeArray[20].type,grammarTypeArray[21].type);
}

/* =================================
外部声明，变量+函数+初始化
==================================== */
void external_declaration(int l){
    // 判断是否是否是规定的类型符号
    // 这里判断的过程中，已经读取字符到类型符下一位置
    if(!type_specifier()){
        char bufExpect[50] = "<type_specifier> ";
        expect(bufExpect);
    }

    // 遇见分号表示语句结束
    if(token == TK_SEMICOLON){
        get_token();
        return;
    }

    // 逐个分析声明或者函数定义
    while(1){
        // 声明（指针声明+函数调用+结构体生命+直接声明）
        // 直接声明包括标识符，数组和后缀（函数）
        // 包括函数调用和声明
        // 结构体声明和创建
        // 直接声明：函数声明+结构体声明+数组访问+函数调用
        // 例如第一句const int a =100;
        /* 通过识别，const->int->a,调用函数调用过程，如果
        不是函数，则调用结构体构造过程，如果不是结构体，就调用
        直接声明过程，如果是标识符，就取下一符号，就是下面的事了
        这里的结果都是基于词法分析的结果 */
        declarator();

        //如果是函数，就构建函数体{}
        if(token == TK_BEGIN){
            if(l == SC_LOCAL){
                char bufError[40] = "cannot support nest definition!";//"不支持函数嵌套定义";
                error(bufError);
            }

            // 函数体，即一个符合语句{}
            // 先确定函数返回值类型is_type_specifier(int v),v是当前token
            // 探寻函数内部的声明，不支持嵌套函数等，一行一个
            // 紧接着识别语句，直到'}'出现，函数识别结束
            // <compound_statement>::=<TK_BEGIN>{<declaration>}{<statement>}<TK_END>
            // 语句包括复合语句、if、return、break、continue、for循环等
            // 以if为例：<if_statement>::=<KW_IF><TK_OPENPA><expression>
            //      <TK_CLOSEPA><statement>[<KW_ELSE><statement>]
            // 就是先识别括号中的条件语句
            // 而后再去识别if中的表达式（递归）expression
            // 如果有else，就要识别else语句
            // 如果不是这些语句，那么就是表达式语句expression_statement()
            // 识别表达式语句就是在分号之前的语句expression()
            // <expression>::=<assignment_expression>{<TK_COMMA><assignment_expression>}
            // 语言中的表达式，都是基于赋值语句的
            funcbody();

            // 如果是有返回值函数则输出
            // 且默认把是否有返回值写为无返回值类型
            if(isReturn){
                fprintf(fout,"%s\n",grammarTypeArray[16].type);
                isReturn = 0;
            }
            break;
        }
        // 赋值
        else{
            if(token == TK_ASSIGN){
                // 获取下以单词
                get_token();

                // 初值操作，赋值语句
                // 包括布尔运算|单目运算赋值操作
                // 判断赋值等号右侧都有哪些，如a= b*a&c+a-b;这样的
                // 所以就一直递归下去探寻
                // 包括赋值为{}对象
                // 句点访问符号
                // 指针访问类型
                // 函数调用（）包含实参
                initializer();
            }
            // 逗号，完成一个声明
            if(token == TK_COMMA){
                // if(grammarType != grammarTypeArray[24].type){
                //     fprintf(fout, "%s\n",grammarType);
                // }
                get_token();
            }
            // 考虑了所有情况，最后就是分号结尾的结束了
            else{
                syntax_state = SNTX_LF_HT;

                // 不论是谁，只要到达分号，说明该语句结束，
                // 把变量状态置为非常量，同时要输出常量定义标识
                // 这对程序影响较大，暂时先这样写
                // if(isConstDef == 1){
                //     isConstDef=0;
                //     fprintf(fout, "%s\n",grammarTypeArray[2].type);
                // }
                // else if(grammarType != grammarTypeArray[24].type ){
                //     fprintf(fout, "%s\n",grammarType);
                // }

                // 将状态置空
                grammarType = grammarTypeArray[24].type;

                skip(TK_SEMICOLON);

                // 判断是否是需要做出声明的地方，需要判断下一字符
                if(token != KW_CONST){
                    // 常量状态置为0
                    // 暂时理解为不是常量说明就是变量说明，均通过isConstDef定义
                    if(isConstDef == 1){
                        isConstDef=0;
                        fprintf(fout, "%s\n",grammarTypeArray[3].type);
                    }
                    else{
                        if(!is_type_specifier(token)){
                            fprintf(fout, "%s\n",grammarTypeArray[25].type);
                        }
                    }
                }

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

    //  状态默认不是常量定义,只有到达分号自动重置为非常量
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

        // 添加const常量声明,const的后面还要跟着类型
        case KW_CONST:
            type_found = 1;
            syntax_state = SNTX_SP;
            // 设置状态为常量定义
            isConstDef = 1;
            get_token();
            // 自调用判断类型
            type_specifier();
            break;

        case KW_INT:
            syntax_state = SNTX_SP;
            type_found = 1;
            get_token();
            break;
        case KW_STRUCT:
            syntax_state = SNTX_SP;
            // 发现结构体时，直接调用结构体识别文法
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
        char bufExpect[50] = "struct name! ";
        expect(bufExpect);
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
    // int maxalign, offset;

    syntax_state = SNTX_LF_HT;  //第一个结构体成员与'{'不写在一行
    syntax_level++;             //结构体成员变量声明，缩进加一级

    get_token();
    while(token != TK_END){
        struct_declaration();//&maxalign, &offset
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
            // expect("整数常量");
            char bufExpect[50] = "Integer constant needed!";
            expect(bufExpect);
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
    else if(token == KW_MAIN){
        get_token();
    }
    else{
        // expect("标识符");
        char bufExpect[50] = "identifier needed!";
        expect(bufExpect);
    }

    direct_declarator_postfix();
}

/* ========================================
直接声明符后缀 
===========================================*/
void direct_declarator_postfix(){
    int n=0;
    if(token == TK_OPENPA){
        // 函数声明
        // 在此输出函数定义标识
        fprintf(fout, "%s\n",grammarTypeArray[6].type);

        parameter_type_list(n);
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
    // 不是函数不是结构体，那暂时就先判断分号即就是语句声明
    else if(token==TK_SEMICOLON){
        // 将状态置空
        grammarType = grammarTypeArray[4].type;
        // 常量状态置为0
        if(isConstDef == 1){
            fprintf(fout, "%s\n",grammarTypeArray[2].type);
        }
        else{
            fprintf(fout, "%s\n",grammarType);
            fprintf(fout, "%s\n",grammarTypeArray[5].type);
        }
    }
}

/* ========================================
形参类型表
===========================================*/
void parameter_type_list(int func_call){
    get_token();
    while(token != TK_CLOSEPA){
        if(!type_specifier()){
            char bufParam[30] = "invalid identifier type";//"无效类型标识符";
            error(bufParam);
        }

        declarator();

        if(token == TK_CLOSEPA){
            fprintf(fout,"%s\n",grammarTypeArray[7].type);
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
    fprintf(fout,"%s\n",grammarTypeArray[15].type);
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
void statement(){//int *bsym, int *csym
    switch(token){
        case TK_BEGIN:
            compound_statement();//bsym, csym
            break;
        case KW_IF:
            if_statement();//bsym, csym
            break;
        case KW_RETURN:
            return_statement();
            break;
        case KW_BREAK:
            break_statement();//bstm
            break;
        case KW_CONTINUE:
            continue_statement();//csym
            break;
        case KW_FOR:
            for_statement();//bsym, csym
            break;
        case KW_PRINTF:
            get_token();
            expression_statement();

            // 写语句获取
            fprintf(fout,"%s\n",grammarTypeArray[18].type);
            break;
        default:
            expression_statement();
            break;
    }

    // 语句获取
    fprintf(fout,"%s\n",grammarTypeArray[12].type);
    // 暂时获取语句就是语句列
    fprintf(fout,"%s\n",grammarTypeArray[14].type);
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

    // 复合语句获取
    fprintf(fout,"%s\n",grammarTypeArray[15].type);

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
        case KW_CONST:
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
        // 暂时设置为第一个标识符不是因子
        isItem = 0;
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

    // 返回语句获取
    fprintf(fout,"%s\n",grammarTypeArray[13].type);
    // 标记是有返回值函数
    isReturn = 1;

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
            fprintf(fout,"%s\n",grammarTypeArray[10].type);
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
        // 得到一个赋值语句
        fprintf(fout,"%s\n",grammarTypeArray[11].type);

        get_token();
        assignment_expression();
    }
}


/* ==========================================
相等类表达式
============================================= */
void equality_expression(){
    relational_expression();
    while(token == TK_EQ || token == TK_NEQ){
        get_token();
        relational_expression();
    }
}

/* ==========================================
关系表达式
============================================= */
void relational_expression(){
    additive_expression();
    while((token==TK_LT || token == TK_LEQ) ||
        token == TK_GT || token == TK_GEQ){
            get_token();
            additive_expression();
        }
}

/* ==========================================
加减类表达式
============================================= */
void additive_expression(){
    multiplicative_expression();
    while(token == TK_PLUS || token == TK_MINUS){
        get_token();
        multiplicative_expression();
    }
}

/* ==========================================
乘除类表达式
============================================= */
void multiplicative_expression(){
    unary_expression();
    while(token==TK_STAR || token==TK_DIVIDE || token==TK_MOD){
        get_token();
        unary_expression();
    }
}

/* ==========================================
一元表达式
============================================= */
void unary_expression(){
    switch(token){
        case TK_AND:
            get_token();
            unary_expression();
            break;
        case TK_STAR:
            get_token();
            unary_expression();
            break;
        case TK_PLUS:
            get_token();
            unary_expression();
            break;
        case TK_MINUS:
            get_token();
            unary_expression();
            break;
        case KW_SIZEOF:
            sizeof_expression();
            break;
        default:
            postfix_expression();
            break;
    }
}

/* ==========================================
sizeof表达式
============================================= */
void sizeof_expression(){
    get_token();
    skip(TK_OPENPA);
    type_specifier();
    skip(TK_CLOSEPA);
}


/* ==========================================
后缀表达式
============================================= */
void postfix_expression(){
    primary_expression();
    while(1){
        if(token == TK_DOT || token==TK_POINTSTO){
            get_token();

            /* 这个东西有点奇怪 */
            token |= SC_MEMBER;
            
            
            get_token();
        }
        else if(token==TK_OPENBR){
            get_token();
            expression();
            skip(TK_CLOSEBR);
        }
        else if(token == TK_OPENPA){
            argument_expression_list();
        }
        else{
            break;
        }
    }
}

/* ==========================================
初值表达式
============================================= */
void primary_expression(){
    int t;
    switch(token){
        case TK_CINT:
            // 写入值的类型
            grammarType = grammarTypeArray[0].type;
            fprintf(fout, "%s\n",grammarType);
            // if(isConstDef == 1){
            //     // 不直接将是否为常量置为0是因为可能是逗号而不是结尾
            //     // isConstDef=0;
            //     fprintf(fout, "%s\n",grammarTypeArray[2].type);
            //     // isConstDef=0;
            //     // fprintf(fout, "%s\n",grammarTypeArray[3].type);
            // }
            get_token();
            break;
        case TK_CCHAR:
            // 写入值的类型,char默认是变量定义
            // 只有在const状态下输出的常量定义
            // 所以默认定义为”变量定义“
            grammarType = grammarTypeArray[5].type;
            // fprintf(fout, "%s\n",grammarType);
            // 暂时注释，并到get_token()里写入文件--->因为要兼容逗号
            // if(isConstDef == 1){
            //     fprintf(fout, "%s\n",grammarTypeArray[2].type);
            //     // isConstDef=0;
            //     // fprintf(fout, "%s\n",grammarTypeArray[3].type);
            // }
            // else{
            //     fprintf(fout, "%s\n",grammarType);
            // }
            get_token();
            break;
        case TK_CSTR:
            // 写入值的类型
            grammarType = grammarTypeArray[17].type;
            fprintf(fout, "%s\n",grammarType);
            get_token();
            break;
        case TK_OPENPA:
            get_token();
            expression();
            skip(TK_CLOSEPA);
            break;
        default:
            t = token;
            if(t<TK_IDENT){
                // expect("标识符或常量");
                char bufExpect[50] = "identifier or constant needed!";
                expect(bufExpect);
            }
            else{
                // 写入值的类型
                // 这里的状态包括符合语句表达式，复合语句的第一个标识符不是因子
                // 用isItem表示是否是因子，1-是；0-不是
                if(isItem){
                    grammarType = grammarTypeArray[8].type;
                    fprintf(fout, "%s\n",grammarType);
                    grammarType = grammarTypeArray[9].type;
                    fprintf(fout, "%s\n",grammarType);
                }
                else{
                    // 暂不作处理
                    isItem = 1;
                }
            }

            get_token();
            break;
    }
}

/* ==========================================
实参表达式
============================================= */
void argument_expression_list(){
    get_token();
    if(token != TK_CLOSEPA){
        for(;;){
            assignment_expression();
            if(token == TK_CLOSEPA){
                break;
            }
            skip(TK_COMMA);
        }
    }
    skip(TK_CLOSEPA);
}