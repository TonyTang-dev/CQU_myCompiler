/* 全局变量 */
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

/* 
* 全局变量
 */
enum e_TokenCode{
    TK_PLUS,
    TK_MINUS,
    TK_STAR,
    TK_DIVIDE,
    TK_MOD,
    TK_EQ,
    TK_NEQ,
    TK_LT,
    TK_LEQ,
    TK_GT,
    TK_GEQ,
    TK_ASSIGN,
    TK_POINTSTO,
    TK_DOT,
    TK_AND,
    TK_OPENPA,
    TK_CLOSEPA,
    TK_OPENBR,
    TK_CLOSEBR,
    TK_BEGIN,
    TK_END,
    TK_COLON,
    TK_SEMICOLON,
    TK_COMMA,
    TK_ELLIPSIS,
    TK_EOF,
    
    /* CONST */
    TK_CINT,
    TK_CCHAR,
    TK_CSTR,
    

    /* KEYWORD */
    KW_CHAR,
    KW_SHORT,
    KW_INT,
    KW_VOID,
    KW_STRUCT,
    KW_IF,
    KW_ELSE,
    KW_CONST,
    KW_FOR,
    KW_CONTINUE,
    KW_BREAK,
    KW_RETURN,
    KW_SIZEOF,
    KW_MAIN,
    KW_SWITCH,
    KW_CASE,
    KW_DEFAULT,
    KW_WHILE,
    KW_SCANF,
    KW_PRINTF,
    KW_ALIGN,
    KW_CDECL,
    KW_STDCALL,

    /* IDENTIFIER */
    TK_IDENT
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
    char type[30];
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




/* 全局方法 */
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
