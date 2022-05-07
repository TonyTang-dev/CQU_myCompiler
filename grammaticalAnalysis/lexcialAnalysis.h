#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

#include<iostream>

using namespace std;


/* 
*导入错误处理文件，"DealError.h"
*错误处理文件已包含全局变量文件-不用重复导入 "Global.h"
*其中也包括对存储数据结构的初始化操作+操作方法的文件 "memorizeMethod_init.h"
*/
#include "DealError.h"


/* 函数声明 */
void color_token(int lex_state);


/* 处理注释 */
void parse_comment(){
    getch();
    do{
        do{
            if(ch=='\n' || ch=='*' || ch==EOF){
                break;
            }
            else{
                getch();
            }
        }while(1);

        if(ch=='\n'){
            line_num++;
            getch();
        }
        else if(ch=='*'){
            getch();
            if(ch=='/'){
                getch();
                return;
            }
        }
        else{
            // error("一直到文件尾未看到配对的注释结束符");
            cout<<"cannot get annotation end note untill EOF";
            return;
        }
    }while(1);
}

/* 空白字符处理 */
void skip_white_space(){
    while(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n'){
        if(ch=='\r'){
            getch();
            if(ch != '\n'){
                return;
            }
            // 行数统计
            line_num++;
        }
        printf("%c",ch);    //输出空白字符，保持输出格式
        getch();
    }
}

/* 预处理，忽略空白字符及注释 */
void preprocess(){
    while(1){
        if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n'){
            skip_white_space();
        }
        else if(ch=='/'){
            // 向前多读一个字节看是否是开始符号，猜错就回滚
            getch();
            if(ch=='*'){
                parse_comment();
            }
            else{
                ungetc(ch, fin);    //回滚到输入流中
                ch='/';
                break;
            }
        }
        else{
            break;
        }
    }
}

/* 判断c是否是字母或下划线 */
int is_nodigit(char c){
    return(c >='a' && c<='z') ||
            (c>='A' && c<='Z') ||
            c=='_';
}

/* 判断c是否为数字 */
int is_digit(char c){
    return c>='0' && c<='9';
}

/* 解析标识符 */
void parse_identifier(){
    // 要处理不区分大小写的情况，所以对于关键字的判断要除去大小写区分
    // 我的方法是，将所有字母转为小写字母
    char tempCh = ch;
    if(ch >= 'A' && ch <='Z'){
        tempCh = ch+32;
    }
    else{
        tempCh=ch;
    }

    // 初始化存储字符串变量
    dynstring_reset(&tkstr);
    dynstring_chcat(&tkstr,ch);

    dynstring_reset(&sourcestr);
    dynstring_chcat(&sourcestr,tempCh);

    getch();
    while(is_nodigit(ch) || is_digit(ch)){
        // 链接解析标识符
        dynstring_chcat(&tkstr,ch);

        // 将出现的大写字母转为小写
        if(ch >= 'A' && ch <='Z'){
            tempCh = ch+32;
        }
        else{
            tempCh=ch;
        }
        dynstring_chcat(&sourcestr,tempCh);

        getch();
    }
    dynstring_chcat(&tkstr,'\0');
    dynstring_chcat(&sourcestr,'\0');
    // cout<<"\n*******"<<tkstr.data<<"******"<<sourcestr.data<<endl;
}

/* 解析整数 */
void parse_num(){
    dynstring_reset(&tkstr);
    dynstring_reset(&sourcestr);
    do{
        dynstring_chcat(&tkstr,ch);
        dynstring_chcat(&sourcestr,ch);
        getch();
    }while(is_digit(ch));

    if(ch=='.'){
        do{
            dynstring_chcat(&tkstr,ch);
            dynstring_chcat(&sourcestr,ch);
            getch();
        }while(is_digit(ch));
    }
    dynstring_chcat(&tkstr,'\0');
    dynstring_chcat(&sourcestr,'\0');
    tkvalue = atoi(tkstr.data);
}

/* 解析字符常量，字符串常量 */
void parse_string(char sep){
    // char c;
    dynstring_reset(&tkstr);
    dynstring_reset(&sourcestr);
    dynstring_chcat(&sourcestr,sep);
    getch();

    for(;;){
        if(ch==sep){
            break;
        }

        /* 由于字符串暂时保持原样输出，所以暂时不对转义字符做处理 */
        // else if(ch=='\\'){
        //     /* tkstr原先没有在这里写入'\'字符，导致最后输出的内容被转义，从而出错 */
        //     dynstring_chcat(&tkstr,ch);
        //     dynstring_chcat(&sourcestr,ch);
        //     /* 写入了'\'符号之后，转义字符，输出被转义字符即可，如\\n再连接n即可 
        //         直接的换行似乎会自动换行的，不用处理
        //     */
        //     getch();
        //     switch(ch){
        //         case '0':{
        //             c='\0';
        //             break;
        //         }
        //         case 'a':{
        //             c='\a';
        //             break;
        //         }
        //         case 'b':{
        //             c='\b';
        //             break;
        //         }
        //         case 't':{
        //             c='\t';
        //             break;
        //         }
        //         case 'n':{
        //             c='\n';
        //             break;
        //         }
        //         case 'v':{
        //             c='\v';
        //             break;
        //         }
        //         case 'f':{
        //             c='\f';
        //             break;
        //         }
        //         case 'r':{
        //             c='\r';
        //             break;
        //         }
        //         case '\"':{
        //             c='\"';
        //             break;
        //         }
        //         case '\'':{
        //             c='\'';
        //             break;
        //         }
        //         case '\\':{
        //             c='\\';
        //             break;
        //         }
        //         default:{
        //             c=ch;
        //             if(c>='!' && c<='~'){
        //                 // warning("非法转义字符:\'\\%c\'",c);
        //                 cout<<"非法转义字符:\'"<<c<<"\'";
        //             }
        //             else{
        //                 // warning("非法转义字符:\'\\0x%x\'",c);
        //                 cout<<"非法转义字符:\'"<<c<<"\'"<<endl;
        //             }
        //             break;
        //         }
        //     }

        //     dynstring_chcat(&tkstr,c);
        //     dynstring_chcat(&sourcestr,ch);
        //     getch();
        // }
        else{
            dynstring_chcat(&tkstr,ch);
            dynstring_chcat(&sourcestr,ch);
            getch();
        }
    }
    // 源字符与识别字符
    dynstring_chcat(&tkstr, '\0');
    dynstring_chcat(&sourcestr,sep);
    dynstring_chcat(&sourcestr,'\0');
    getch();
}



/* ==========================================
语法缩进程序实现，供调用
============================================= */
// tab缩进
void print_tab(int n){
    int i=0;
    for(;i<n;i++){
        printf("\t");
    }
}

// 缩进
void syntax_indent(){
    switch(syntax_state){
        case SNTX_NUL:
            color_token(LEX_NORMAL);
            break;
        case SNTX_SP:
            printf(" ");
            color_token(LEX_NORMAL);
            break;
        case SNTX_LF_HT:
            {
                if(token==TK_END){
                    syntax_level--;
                }
                printf("\n");
                print_tab(syntax_level);
            }
            color_token(LEX_NORMAL);
            break;
        case SNTX_DELAY:
            break;
    }
    syntax_state = SNTX_NUL;
}


/* 取单词 */
void get_token(){
    preprocess();

    switch(ch){
        case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':
        case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':
        case 'o':case 'p':case 'q':case 'r':case 's':case 't':
        case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':
        case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':
        case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':
        case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':
        case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':
        case '_':{
            // 字符串对象（单词对象）
            TkWord *tp;
            // 对源文件进行标识符解析
            parse_identifier();
            // 将识别的标识符串插入到单词组
            tp=tkword_insert(tkstr.data);
            // 指定标识符的token类型
            token = tp->tkcode;
            break;
        }
        case '0':case '1':case '2':case '3':
        case '4':case '5':case '6':case '7':
        case '8':case '9':{
            parse_num();
            token = TK_CINT;
            break;
        }
        case '+':{
            getch();
            token=TK_PLUS;
            break;
        }
        case '-':{
            getch();
            if(ch=='>'){
                token=TK_POINTSTO;
                getch();
            }
            else{
                token=TK_MINUS;
            }
            break;
        }
        case '/':{
            token=TK_DIVIDE;
            getch();
            break;
        }
        case '%':{
            token=TK_MOD;
            getch();
            break;
        }
        case '=':{
            getch();
            if(ch=='='){
                token=TK_EQ;
                getch();
            }
            else{
                token=TK_ASSIGN;
            }
            break;
        }
        case '!':{
            getch();
            if(ch=='='){
                token=TK_NEQ;
                getch();
            }
            else{
                // error("暂不支持!操作");
                cout<<"cannot support operation !";
            }
            break;
        }
        case '<':{
            getch();
            if(ch=='='){
                token=TK_LEQ;
                getch();
            }
            else{
                token=TK_LT;
            }
            break;
        }
        case '>':{
            getch();
            if(ch=='='){
                token=TK_GEQ;
                getch();
            }
            else{
                token=TK_GT;
            }
            break;
        }
        case '.':{
            getch();
            if(ch=='.'){
                getch();
                if(ch != '.'){
                    // error("省略号拼写错误");
                    cout<<"the ellipsis spelling error";
                }
                else{
                    token=TK_ELLIPSIS;
                }
                getch();
            }
            else{
                token=TK_DOT;
            }
            break;
        }
        case '&':{
            token = TK_AND;
            getch();
            break;
        }
        case ';':{
            token=TK_SEMICOLON;
            getch();
            break;
        }
        case ':':{
            token=TK_COLON;
            getch();
            break;
        }
        case ']':{
            token=TK_CLOSEBR;
            getch();
            break;
        }
        case '}':{
            token=TK_END;
            getch();
            break;
        }
        case ')':{
            token=TK_CLOSEPA;
            getch();
            break;
        }
        case '[':{
            token=TK_OPENBR;
            getch();
            break;
        }
        case '{':{
            token=TK_BEGIN;
            getch();
            break;
        }
        case ',':{
            token=TK_COMMA;
            getch();
            break;
        }
        case '(':{
            token=TK_OPENPA;
            getch();
            break;
        }
        case '*':{
            token=TK_STAR;
            getch();
            break;
        }
        case '\'':{
            parse_string(ch);

            token=TK_CCHAR;
            tkvalue = *(char*)tkstr.data;
            break;
        }
        case '\"':{
            parse_string(ch);

            token=TK_CSTR;
            break;
        }
        case EOF:{
            token=TK_EOF;
            break;
        }
        default:{
            // error("--->invalid char:\\x%02x",ch);
            cout<<"--->invalid char:"<<ch-'\0'<<endl;
            getch();
            break;
        }
    }

    /* 语法缩进调用--边取单词边缩进输出 */
    syntax_indent();
}

/* 词法着色 */
void color_token(int lex_state){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    char *p;

    // 定义一个字符串变量专门存储输出到文件的内容
    char *out2File;

    switch(lex_state){
        case LEX_NORMAL:{
            /* 每次对操作单词都将其存入动态数组中，哈希表存储的指向单词的指针
            *  由于最开始已经在最前面讲初始化的内容存入动态指针，
            *  token值除了已经声明的内容，其他的自动以动态数组下标索引为token值
            */
        //    根据enum枚举对象，>TK_IDENT的就是标识符和其他对象了，用灰色标注
            if(token >= TK_IDENT){
                SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
                // 由于每次处理标识符（包括关键字和标识符），都存储了源格式tkstr，所以现在
                // 直接输出源格式即可（输出到控制台）
                // 同样输出到文件也是，保持源格式的话就用tkstr
                // 此处的sourcestr是转小写格式的内容
                // 如果在动态数组里已经查找到小写格式的内容，表示是关键字或者本来就是小写的标识符
                // 就不需要将其插入数组，而如果未找到小写格式的字符串匹配，要么是不存在，要么是
                // 该字符串是标识符，会自动将不存在的标识符插入到动态数组中去
                get_tkstr(token);   //调用一下get_tkstr()，让其返回字符串的同时设置全局类型变量
                p = tkstr.data;
                out2File = tkstr.data;
                cout<<p;               //<<get_tkstr(token);
            }
            // >KW_CHAR<TK_IDENT的是关键字部分
            else if(token >= KW_CHAR){
                SetConsoleTextAttribute(h,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                get_tkstr(token);   //调用一下get_tkstr()，让其返回字符串的同时设置全局类型变量
                p = tkstr.data;
                out2File = tkstr.data;
                cout<<p;               //get_tkstr(token);
            }
            // >TK_CINT<TK_CSTR的是常量部分
            else if(token >= TK_CINT){
                SetConsoleTextAttribute(h,FOREGROUND_RED|FOREGROUND_GREEN);
                p=get_tkstr(token);     //函数返回的是带引号的，为了照顾控制台输出的
                out2File = tkstr.data;  //tkstr是不带引号的内容
                cout<<p;
            }
            // 其他的就是排在最前面的是运算符分隔符部分
            else{
                SetConsoleTextAttribute(h,FOREGROUND_RED|FOREGROUND_INTENSITY);
                p=get_tkstr(token);
                out2File = p;
                if(token != TK_EOF)
                    printf("%s",p);
            }

            // 将结果写入文件
            // 只使用tkstr的原因是：在字符及字符串部分，在sourcestr两边加上了引号
            // 在cin和cstring之间，get_tkstr()返回的是带有引号的内容，这是为了照顾控制台输出
            // 在关键字和标识符中，sourcestr不是源字符串，这里没有统一，后期再做统一优化
            if(token != TK_EOF){
                // cout<<"++++++++++"<<tkType<<" "<<out2File<<endl;
                fprintf(fout,"%s %s\n",tkType,out2File);
            }

            break;
        }
        case LEX_SEP:{
            get_tkstr(token);   //调用一下get_tkstr()，让其返回字符串的同时设置全局类型变量
            printf("%c",ch);
            break;
        }
    }
}