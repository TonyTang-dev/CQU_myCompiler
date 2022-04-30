#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#include<iostream>

using namespace std;


/* 全局变量 */

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


/* token字符串 */
DynString tkstr;
DynString sourcestr;

/* 全局变量 */
#define MAXKEY 1024             //哈希容量
TkWord *tk_hashtable[MAXKEY];   //哈希表
DynArray tktable;               //单词表

/* 写入文件的单词类型,如main的类型:MAINTK */
char *tkType = " ";




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


/* 异常处理 */
/* 
    stage:阶段
    level:级别
    fmt:输出格式
    ap:可变参数列表
 */
void handle_exception(int stage,int level,char *fmt, va_list ap){
    char buf[1024];
    vsprintf(buf, fmt, ap);
    if(stage == STAGE_COMPILE){
        if(level == LEVEL_WARNING){
            printf("%s(第%d行):编译警告:%s!\n","filename",line_num,buf);
        }
        else{
            printf("%s(第%d行):编译错误:%s!\n","filename",line_num,buf);
            exit(-1);
        }
    }
    else{
        printf("链接错误:%s!\n",buf);
        exit(-1);
    }
}

/* 编译警告 */
void warning(char *fmt, ...){
    va_list ap;
    va_start(ap,fmt);
    handle_exception(STAGE_COMPILE,LEVEL_WARNING,fmt,ap);
    va_end(ap);
}

/* 编译致命错误处理 */
void error(char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    handle_exception(STAGE_COMPILE,LEVEL_ERROR,fmt,ap);
    va_end(ap);
}

/* 提示错误，缺少语法成分 */
void expect(char *msg){
    error("缺少%s",msg);
}

/* 取得单词v所代表的源码字符串 */
char *get_tkstr(int v){
    // 先获取单词类型
    tkType = ((TkWord*)tktable.data[v])->tkName;

    if(v > tktable.count){
        return NULL;
    }
    else if(v>=TK_CINT && v<=TK_CSTR){
        return sourcestr.data;
    }
    else{
        return ((TkWord*)tktable.data[v])->spelling;
    }
}

/* 跳过单词c，取下一单词，如果当前单词不是c，提示错误 */
void skip(int c){
    if(token != c){
        error("缺少'%s'",get_tkstr(c));
    }
    get_token();
}

/* 链接错误 */
void link_error(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    handle_exception(STAGE_LINK,LEVEL_ERROR,fmt,ap);
    va_end(ap);
}



/* 
*初始化动态字符串存储容量
@param pstr 动态字符串存储结构
@param initsize 字符串初始化分配空间
 */
void dynstring_init(DynString *pstr, int initsize){
    if(pstr != NULL){
        pstr->data=(char*)malloc(sizeof(char) *initsize);
        pstr->count=0;
        pstr->capacity=initsize;
    }
}

/* 释放空间 */
void dynstring_free(DynString *pstr){
    if(pstr != NULL){
        if(pstr->data){
            free(pstr->data);
        }
        pstr->count=0;
        pstr->capacity=0;
    }
}

/* 重置字符串，先释放再重新初始化
* pstr 字符串存储结构
 */
void dynstring_reset(DynString *pstr){
    dynstring_free(pstr);
    dynstring_init(pstr,8); //初始化8字节
}

/* 重新分配字符串容量 */
void dynstring_realloc(DynString *pstr, int new_size){
    int capacity;
    char *data;

    capacity=pstr->capacity;
    while(capacity < new_size){
        capacity = capacity * 2;
    }
    data = (char*)realloc(pstr->data, capacity);
    if(!data){
        printf("内存分配失败");
    }
    pstr->capacity = capacity;
    pstr->data = data;
}

/* 追加单个字符到动态字符串对象 */
void dynstring_chcat(DynString *pstr, int ch){
    int count;
    count = pstr->count+1;
    if(count > pstr->capacity){
        dynstring_realloc(pstr, count);
    }
    ((char *)pstr->data)[count-1] = ch;
    pstr->count = count;
}



/* 
* 重新分配动态数组容量
 @parr动态数组存储结构
 @new_size 动态数组最新元素个数
*/
void dynarray_realloc(DynArray *parr, int new_size){
    int capacity;
    void **data;

    capacity = parr->capacity;
    while(capacity < new_size){
        capacity = capacity*2;
    }
    data = (void **)realloc(parr->data, capacity);
    if(!data){
        printf("内存分配失败");
    }
    parr->capacity = capacity;
    parr->data = data;
}

/* 追加元素 */
void dynarray_add(DynArray *parr, void *data){
    int count;
    count = parr->count+1;
    if(count*sizeof(void*) > parr->capacity){
        dynarray_realloc(parr, count*sizeof(void*));
    }
    parr->data[count-1] = data;
    parr->count = count;
}

/* initial capacity */
void dynarray_init(DynArray *parr, int initsize){
    if(parr != NULL){
        parr->data = (void**)malloc(sizeof(char) *initsize);
        parr->count = 0;
        parr->capacity = initsize;
    }
}

/* RELEASE space */
void dynarray_free(DynArray *parr){
    void **p;
    for(p=parr->data;parr->count;++p,--parr->count){
        if(*p){
            free(*p);
        }
    }
    free(parr->data);
    parr->data = NULL;
}

/* find element */
int dynarray_search(DynArray *parr, int key){
    int i;
    int **p;
    p = (int **)parr->data;
    for(i=0;i<parr->count;++i,p++){
        if(key == **p){
            return 1;
        }
    }
    return -1;
}




/* 计算哈希地址--链地址法 */
int elf_hash(char *key){
    int h=0,g;
    while(*key){
        h=(h<<4) + *key++;
        g = h&0xf0000000;
        if(g){
            h ^= g>>24;
        }
        h &= ~g;
    }

    return h%MAXKEY;
}

/* 
* @function 单词表操作函数
*/

/* 运算符、关键字、常量直接放入单词表 */
TkWord *tkword_direct_insert(TkWord *tp){
    int keyno;
    dynarray_add(&tktable, tp);
    keyno = elf_hash(tp->spelling);
    tp->next = tk_hashtable[keyno];
    tk_hashtable[keyno] = tp;
    return tp;
}

/* 查找单词 */
TkWord *tkword_find(char *p, int keyno){
    TkWord *tp = NULL, *tp1;
    for(tp1=tk_hashtable[keyno];tp1;tp1=tp1->next){
        if(!strcmp(p,tp1->spelling)){
            token = tp1->tkcode;
            tp=tp1;
        }
    }
    return tp;
}

/* 分配堆内存并数据初始化 */
void *mallocz(int size){
    void *ptr;
    ptr = malloc(size);
    if(!ptr && size){
        printf("内存分配失败");
    }
    memset(ptr, 0, size);
    return ptr;
}

/* 标识符插入单词表，先查找，查找不到再插入单词表 */
TkWord *tkword_insert(char *p){
    // 声明一个TkWord副本，避免不同tk之间互相影响，因为指针的操作是全局的
    TkWord *tp;
    // 哈希表下标索引
    int keyno;
    char *s;
    char *end;
    int length;

    // 哈希值
    keyno = elf_hash(p);

    // 小写格式查找
    // 把小写格式放前面的原因是：如果小写格式查找到了证明是关键字
    // 小写格式未找到则可能是标识符，也可能不存在
    tp=tkword_find(sourcestr.data, keyno);

    // 如果小写格式未查找到，则源格式再查找一遍
    // 如果已经找到，那么不需要插入
    if(tp == NULL){
        tp=tkword_find(p, keyno);
    }

    if(tp == NULL){
        length = strlen(p);
        tp=(TkWord*)mallocz(sizeof(TkWord)+length+1);
        tp->next = tk_hashtable[keyno];
        tk_hashtable[keyno] = tp;
        // 添加
        dynarray_add(&tktable, tp);
        // 指定tkcode值
        tp->tkcode = tktable.count-1;
        // 显然tp是一个指针，sizeof(TkWord)是结构体身的大小，而length是要存储的字符串长度
        // 用s=(char*)tp+sizeof(TkWord)就是希望把指针移到存储字符串的位置，开始存单词字符串
        s=(char*)tp+sizeof(TkWord);
        // 内容，即代表的字符串值
        tp->spelling = (char*)s;
         tp->tkName = "IDENFR";
        // 将目标字符串复制到单词内容中
        for(end=p+length;p<end;){
            *s++ = *p++;
        }
        *s = (char)'\0';
    }
    return tp;
}





/* 词法分析初始化 */
void init_lex(){
    TkWord *tp;
    static TkWord keywords[]={
        {TK_PLUS, NULL, "+", NULL, NULL,"PLUS"},
        {TK_MINUS, NULL, "-", NULL, NULL,"MINU"},
        {TK_STAR, NULL, "*", NULL, NULL,"MULT"},
        {TK_DIVIDE, NULL, "/", NULL, NULL,"DIV"},
        {TK_MOD, NULL, "%", NULL, NULL,"MOD"},
        {TK_EQ, NULL, "==", NULL, NULL,"EQL"},
        {TK_NEQ, NULL, "!=", NULL, NULL,"NEQ"},
        {TK_LT, NULL, "<", NULL, NULL,"LSS"},
        {TK_LEQ, NULL, "<=", NULL, NULL,"LEQ"},
        {TK_GT, NULL, ">", NULL, NULL,"GRE"},
        {TK_GEQ, NULL, ">=", NULL, NULL,"GEQ"},
        {TK_ASSIGN, NULL, "=", NULL, NULL,"ASSIGN"},
        {TK_POINTSTO, NULL, "->", NULL, NULL,"POINTER"},
        {TK_DOT, NULL, ".", NULL, NULL,"DOT"},
        {TK_AND, NULL, "&", NULL, NULL,"AND"},
        {TK_OPENPA, NULL, "(", NULL, NULL,"LPARENT"},
        {TK_CLOSEPA, NULL, ")", NULL, NULL,"RPARENT"},
        {TK_OPENBR, NULL, "[", NULL, NULL,"LBRACK"},
        {TK_CLOSEBR, NULL, "]", NULL, NULL,"RBRACK"},
        {TK_BEGIN, NULL, "{", NULL, NULL,"LBRACE"},
        {TK_END, NULL, "}", NULL, NULL,"RBRACE"},
        {TK_COLON, NULL, ":", NULL, NULL,"COLON"},
        {TK_SEMICOLON, NULL, ";", NULL, NULL,"SEMICN"},
        {TK_COMMA, NULL, ",", NULL, NULL,"COMMA"},
        {TK_ELLIPSIS, NULL, "...", NULL, NULL,"ELLIPSIS"},
        {TK_EOF, NULL, "End_Of_File", NULL, NULL,"EOF"},

        {TK_CINT, NULL, "整型常量", NULL, NULL,"INTCON"},
        {TK_CCHAR, NULL, "字符常量", NULL, NULL,"CHARCON"},
        {TK_CSTR, NULL, "字符串常量", NULL, NULL,"STRCON"},

        {KW_CHAR, NULL, "char", NULL, NULL,"CHARTK"},
        {KW_SHORT, NULL, "short", NULL, NULL,"SHORTTK"},
        {KW_INT, NULL, "int", NULL, NULL,"INTTK"},
        {KW_VOID, NULL, "void", NULL, NULL,"VOIDTK"},
        {KW_STRUCT, NULL, "struct", NULL, NULL,"STRUCTTK"},

        {KW_IF, NULL, "if", NULL, NULL,"IFTK"},
        {KW_ELSE, NULL, "else", NULL, NULL,"ELSETK"},
        {KW_CONST, NULL, "const", NULL, NULL,"CONSTTK"},
        {KW_FOR, NULL, "for", NULL, NULL,"FORTK"},
        {KW_CONTINUE, NULL, "continue", NULL, NULL,"CONTINUETK"},
        {KW_BREAK, NULL, "break", NULL, NULL,"BREAKTK"},
        {KW_RETURN, NULL, "return", NULL, NULL,"RETURNTK"},
        {KW_SIZEOF, NULL, "sizeof", NULL, NULL,"SIZEOFTK"},
        {KW_MAIN, NULL, "main", NULL, NULL,"MAINTK"},
        {KW_SWITCH, NULL, "switch", NULL, NULL,"SWITCHTK"},
        {KW_CASE, NULL, "case", NULL, NULL,"CASETK"},
        {KW_DEFAULT, NULL, "default", NULL, NULL,"DEFAULTTK"},
        {KW_WHILE, NULL, "while", NULL, NULL,"WHILETK"},
        {KW_SCANF, NULL, "scanf", NULL, NULL,"SCANFTK"},
        {KW_PRINTF, NULL, "printf", NULL, NULL,"PRINTFTK"},
        {KW_ALIGN, NULL, "__align", NULL, NULL,"ALIGN"},
        {KW_CDECL, NULL, "__cdecl", NULL, NULL,"CDECL"},
        {KW_STDCALL, NULL, "__stdcal", NULL, NULL,"STDCAL"},
        {0,         NULL, NULL, NULL, NULL,NULL}
    };

    dynarray_init(&tktable, 8);
    for(tp = &keywords[0];tp->spelling!=NULL;tp++){
        tkword_direct_insert(tp);
    }
}





/* 全局方法 */

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
            error("一直到文件尾未看到配对的注释结束符");
            return;
        }
    }while(1);
}

/* 空白字符处理 */
void skip_white_space(){
    while(ch==' ' || ch=='\t' || ch=='\r'){
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
        if(ch==' ' || ch=='\t' || ch=='\r'){
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
    char c;
    dynstring_reset(&tkstr);
    dynstring_reset(&sourcestr);
    dynstring_chcat(&sourcestr,sep);
    getch();

    for(;;){
        if(ch==sep){
            break;
        }
        else if(ch=='\\'){
            dynstring_chcat(&sourcestr,ch);
            getch();
            switch(ch){
                case '0':{
                    c='\0';
                    break;
                }
                case 'a':{
                    c='\a';
                    break;
                }
                case 'b':{
                    c='\b';
                    break;
                }
                case 't':{
                    c='\t';
                    break;
                }
                case 'n':{
                    c='\n';
                    break;
                }
                case 'v':{
                    c='\v';
                    break;
                }
                case 'f':{
                    c='\f';
                    break;
                }
                case 'r':{
                    c='\r';
                    break;
                }
                case '\"':{
                    c='\"';
                    break;
                }
                case '\'':{
                    c='\'';
                    break;
                }
                case '\\':{
                    c='\\';
                    break;
                }
                default:{
                    c=ch;
                    if(c>='!' && c<='~'){
                        warning("非法转义字符:\'\\%c\'",c);
                    }
                    else{
                        warning("非法转义字符:\'\\0x%x\'",c);
                    }
                    break;
                }
            }

            dynstring_chcat(&tkstr,c);
            dynstring_chcat(&sourcestr,ch);
            getch();
        }
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
                error("暂不支持!操作");
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
            if(ch='.'){
                getch();
                if(ch != '.'){
                    error("省略号拼写错误");
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
            error("--->invalid char：\\x%02x",ch);
            getch();
            break;
        }
    }
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