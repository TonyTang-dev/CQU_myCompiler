/* 全局变量 */
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

/* 
* 全局变量
 */
enum e_TokenCode{
    TK_PLUS,            //+0
    TK_MINUS,           //-1
    TK_STAR,            //*2
    TK_DIVIDE,            ///3
    TK_MOD,            //%4
    TK_EQ,            //==5
    TK_NEQ,            //!=6
    TK_LT,            //<7
    TK_LEQ,            //<=8
    TK_GT,            //>9
    TK_GEQ,            //>=10
    TK_ASSIGN,            //*=11
    TK_POINTSTO,            //->12
    TK_DOT,            //.13
    TK_AND,            //&14
    TK_OPENPA,            //(15
    TK_CLOSEPA,            //)16
    TK_OPENBR,            //[17
    TK_CLOSEBR,            //]
    TK_BEGIN,            //{
    TK_END,            //}
    TK_COLON,            //:
    TK_SEMICOLON,            //;
    TK_COMMA,            //,
    TK_ELLIPSIS,            //...
    TK_EOF,            //EOF
    
    /* CONST */
    TK_CINT,            //const int
    TK_CCHAR,            //const char
    TK_CSTR,            //const string
    

    /* KEYWORD */
    KW_CHAR,            //char
    KW_SHORT,            //short
    KW_INT,            //int
    KW_VOID,            //void
    KW_STRUCT,            //struct
    KW_IF,            //if
    KW_ELSE,            //else
    KW_CONST,            //const
    KW_FOR,            //for
    KW_CONTINUE,            //continue
    KW_BREAK,            //break
    KW_RETURN,            //return
    KW_SIZEOF,            //sizeof
    KW_MAIN,            //main
    KW_SWITCH,            //switch
    KW_CASE,            //case
    KW_DEFAULT,            //default
    KW_WHILE,            //while
    KW_SCANF,            //scanf
    KW_PRINTF,            //printf
    KW_ALIGN,            //align
    KW_CDECL,            //declare
    KW_STDCALL,            //stadard caling

    /* IDENTIFIER */
    TK_IDENT            //identifier
};

/* token */
int token = -1;

/* 字符 */
char ch=' ';

/* 行号 */
int line_num = 0;

/* 源文件 */
FILE *fin;
FILE *fout;

/* 整数 */
int tkvalue=0;

/* 全局的IDENTIFIER类型 */
char IDENTIFIERBUF[30] = "IDENFR";


/* 词法状态枚举定义 */
enum e_LexState{
    LEX_NORMAL,
    LEX_SEP
};


/* 动态字符串定义 */
typedef struct DynString{
    int count;
    int capacity;
    char *data;
}DynString;
/* 动态数组定义 */
typedef struct DynArray{
    int count;  //元素个数
    int capacity;   //缓冲区长度
    void **data;    //指向数据指针数组
}DynArray;
/* 单词存储结构定义 */
struct TkWord2{
    int tkcode;                 //单词编码
    struct TkWord2 *next;       //指向哈希冲突的同义词
    char *spelling;             //单词字符串
    struct Symbol *sym_struct;  //指向单词所表示的结构定义
    struct Symbol *sym_identifier;  //指向单词所表示的标识符
    char *tkName;               //单词的类别码
};
typedef struct TkWord2 TkWord;

/* 在初始化单词表（标识符+关键字）时的存储类型与单词 */
struct charArray{
    char word[20];
    char type[50];
};


/* token字符串 */
DynString tkstr;
DynString sourcestr;

/* 全局变量 */
#define MAXKEY 1024             //哈希容量
TkWord *tk_hashtable[MAXKEY];   //哈希表
DynArray tktable;               //单词表

/* 写入文件的单词类型,如main的类型:MAINTK */
char *tkType = NULL;



/* 语法分析全局变量 */

/* 语法缩进功能 */
int syntax_state;   //语法状态
int syntax_level;   //缩进级别

/* external_declaration解析声明，为避免重复造轮子
    通过参数识别声明的变量类型（函数内部和外部）
*/
int SC_GLOBAL = 0;  //函数外部解析状态
int SC_LOCAL = 1;   //函数内部解析状态

int SC_MEMBER = 3;

/* 语法状态枚举值 */
enum e_SyntaxState{
    SNTX_NUL,   //空状态，没有缩进
    SNTX_SP,    //空格
    SNTX_LF_HT, //换行并缩进，每一个声明，函数定义，语句结束都要设置
    SNTX_DELAY  //延迟到取出下一个单词后确定输出格式
};

// 语法功能类型
char *grammarType;

/* 语法分析结果类型存储数组 */
struct charArray grammarTypeArray[50]={
    {"", "<无符号整数>\n<整数>"},         //0
    {"", "<整数>"},         //1
    {"", "<常量定义>"},         //2
    {"", "<常量说明>"},         //3
    {"", "<变量定义初始化>"},         //4
    {"", "<变量定义>"},         //5
    {"", "<声明头部>"},         //6
    {"", "<参数表>"},         //7
    {"", "<因子>"},         //8
    {"", "<项>"},         //9
    {"", "<表达式>"},         //10
    {"", "<赋值语句>"},         //11
    {"", "<语句>"},         //12
    {"", "<返回语句>"},         //13
    {"", "<语句列>"},         //14
    {"", "<复合语句>"},         //15
    {"", "<有返回值函数定义>"},         //16
    {"", "<字符串>"},         //17
    {"", "<写语句>"},         //18
    {"", "<有返回值函数调用语句>"},         //19
    {"", "<主函数>"},         //20
    {"", "<程序>"},         //21
    {"", "<有返回值函数调用语句>"},         //22
    {"", "<有返回值函数调用语句>"},         //23
    {"",""}                 //定义一个空字符，用于初始化
};

// 是否是常量定义
int isConstDef=0;   //1-是；0-不是



/*============================================
 全局方法 
 =============================================*/
/* 从源文件读取一个字符 */
void getch(){
    ch=getc(fin); 
}

// 调用前声明函数，避免报出未定义错误
void get_token();


/* 错误处理程序用的枚举定义
    错误级别
 */
enum e_ErrorLevel{
    LEVEL_WARNING,
    LEVEL_ERROR
};

/* 工作阶段 */
enum e_WorkStage{
    STAGE_COMPILE,
    STAGE_LINK
};
