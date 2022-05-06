#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>

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
    // error("缺少%s",msg);
    cout<<"缺少"<<msg;
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
        // error("缺少'%s'",get_tkstr(c));
        cout<<"缺少"<<get_tkstr(c);
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

    int curCapacity = (int)count*sizeof(void*);
    int lastCapacity = (int)parr->capacity;

    if(curCapacity > lastCapacity){
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
    // 由于不同的字符组是有不一样的哈希值的，所以对关键字的查找也要
    // 重新计算哈希值
    int hashKey = elf_hash(sourcestr.data);
    tp=tkword_find(sourcestr.data, hashKey);

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
        // 如果使用每次都声明一个buf数组，那么每次都会对此数组进行操作，可能会报错
        // 我的办法是，将该数组声明为全局变量，使用到的指针都指向它
        /* 因为重新声明的时候，系统重新分配的地址就变了，原先的指针就找不到它了 */
        // char buf3[30] = "IDENFR";
        tp->tkName = IDENTIFIERBUF;
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

    // 由于直接用字符串给字符数组指针复制会报警告，所以定义一个字符数组缓冲
    static struct charArray array[60] = {
        {"+","PLUS"},
        {"-","MINU"},
        {"*","MULT"},
        {"/","DIV"},
        {"%","MOD"},
        {"==","EQL"},
        {"!=","NEQ"},
        {"<","LSS"},
        {"<=","LEQ"},
        {">","GRE"},
        {">=","GEQ"},
        {"=","ASSIGN"},
        {"->","POINTER"},
        {".","DOT"},
        {"&","AND"},
        {"(","LPARENT"},
        {")","RPARENT"},
        {"[","LBRACK"},
        {"]","RBRACK"},
        {"{","LBRACE"},
        {"}","RBRACE"},
        {":","COLON"},
        {";","SEMICN"},
        {",","COMMA"},
        {"...","ELLIPSIS"},
        {"End_Of_File","EOF"},

        {"整型常量","INTCON"},
        {"字符常量","CHARCON"},
        {"字符串常量","STRCON"},

        {"char","CHARTK"},
        {"short","SHORTTK"},
        {"int","INTTK"},
        {"void","VOIDTK"},
        {"struct","STRUCTTK"},

        {"if","IFTK"},
        {"else","ELSETK"},
        {"const","CONSTTK"},
        {"for","FORTK"},
        {"continue","CONTINUETK"},
        {"break","BREAKTK"},
        {"return","RETURNTK"},
        {"sizeof","SIZEOFTK"},
        {"main","MAINTK"},
        {"switch","SWITCHTK"},
        {"case","CASETK"},
        {"default","DEFAULTTK"},
        {"while","WHILETK"},
        {"scanf","SCANFTK"},
        {"printf","PRINTFTK"},
        {"__align","ALIGN"},
        {"__cdecl","CDECL"},
        {"__stdcal","STDCAL"}
    };

    static TkWord keywords[]={
        {TK_PLUS, NULL, array[0].word, NULL, NULL,array[0].type},
        {TK_MINUS, NULL, array[1].word, NULL, NULL,array[1].type},
        {TK_STAR, NULL, array[2].word, NULL, NULL,array[2].type},
        {TK_DIVIDE, NULL, array[3].word, NULL, NULL,array[3].type},
        {TK_MOD, NULL, array[4].word, NULL, NULL,array[4].type},
        {TK_EQ, NULL, array[5].word, NULL, NULL,array[5].type},
        {TK_NEQ, NULL, array[6].word, NULL, NULL,array[6].type},
        {TK_LT, NULL, array[7].word, NULL, NULL,array[7].type},
        {TK_LEQ, NULL, array[8].word, NULL, NULL,array[8].type},
        {TK_GT, NULL, array[9].word, NULL, NULL,array[9].type},
        {TK_GEQ, NULL, array[10].word, NULL, NULL,array[10].type},
        {TK_ASSIGN, NULL, array[11].word, NULL, NULL,array[11].type},
        {TK_POINTSTO, NULL, array[12].word, NULL, NULL,array[12].type},
        {TK_DOT, NULL, array[13].word, NULL, NULL,array[13].type},
        {TK_AND, NULL, array[14].word, NULL, NULL,array[14].type},
        {TK_OPENPA, NULL, array[15].word, NULL, NULL,array[15].type},
        {TK_CLOSEPA, NULL, array[16].word, NULL, NULL,array[16].type},
        {TK_OPENBR, NULL, array[17].word, NULL, NULL,array[17].type},
        {TK_CLOSEBR, NULL, array[18].word, NULL, NULL,array[18].type},
        {TK_BEGIN, NULL, array[19].word, NULL, NULL,array[19].type},
        {TK_END, NULL, array[20].word, NULL, NULL,array[20].type},
        {TK_COLON, NULL, array[21].word, NULL, NULL,array[21].type},
        {TK_SEMICOLON, NULL, array[22].word, NULL, NULL,array[22].type},
        {TK_COMMA, NULL, array[23].word, NULL, NULL,array[23].type},
        {TK_ELLIPSIS, NULL, array[24].word, NULL, NULL,array[24].type},
        {TK_EOF, NULL, array[25].word, NULL, NULL,array[25].type},

        {TK_CINT, NULL, array[26].word, NULL, NULL,array[26].type},
        {TK_CCHAR, NULL, array[27].word, NULL, NULL,array[27].type},
        {TK_CSTR, NULL, array[28].word, NULL, NULL,array[28].type},

        {KW_CHAR, NULL, array[29].word, NULL, NULL,array[29].type},
        {KW_SHORT, NULL, array[30].word, NULL, NULL,array[30].type},
        {KW_INT, NULL, array[31].word, NULL, NULL,array[31].type},
        {KW_VOID, NULL, array[32].word, NULL, NULL,array[32].type},
        {KW_STRUCT, NULL, array[33].word, NULL, NULL,array[33].type},

        {KW_IF, NULL, array[34].word, NULL, NULL,array[34].type},
        {KW_ELSE, NULL, array[35].word, NULL, NULL,array[35].type},
        {KW_CONST, NULL, array[36].word, NULL, NULL,array[36].type},
        {KW_FOR, NULL, array[37].word, NULL, NULL,array[37].type},
        {KW_CONTINUE, NULL, array[38].word, NULL, NULL,array[38].type},
        {KW_BREAK, NULL, array[39].word, NULL, NULL,array[39].type},
        {KW_RETURN, NULL, array[40].word, NULL, NULL,array[40].type},
        {KW_SIZEOF, NULL, array[41].word, NULL, NULL,array[41].type},
        {KW_MAIN, NULL, array[42].word, NULL, NULL,array[42].type},
        {KW_SWITCH, NULL, array[43].word, NULL, NULL,array[43].type},
        {KW_CASE, NULL, array[44].word, NULL, NULL,array[44].type},
        {KW_DEFAULT, NULL, array[45].word, NULL, NULL,array[45].type},
        {KW_WHILE, NULL, array[46].word, NULL, NULL,array[46].type},
        {KW_SCANF, NULL, array[47].word, NULL, NULL,array[47].type},
        {KW_PRINTF, NULL, array[48].word, NULL, NULL,array[48].type},
        {KW_ALIGN, NULL, array[49].word, NULL, NULL,array[49].type},
        {KW_CDECL, NULL, array[50].word, NULL, NULL,array[50].type},
        {KW_STDCALL, NULL, array[51].word, NULL, NULL,array[51].type},
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
            // error("一直到文件尾未看到配对的注释结束符");
            cout<<"一直到文件尾未看到配对的注释结束符";
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
    char c;
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
                cout<<"暂不支持!操作";
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
                    cout<<"省略号拼写错误";
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
}

/* 词法着色 */
void color_token(int lex_state){
    // HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
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
                // SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
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
                // cout<<p;               //<<get_tkstr(token);
            }
            // >KW_CHAR<TK_IDENT的是关键字部分
            else if(token >= KW_CHAR){
                // SetConsoleTextAttribute(h,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                get_tkstr(token);   //调用一下get_tkstr()，让其返回字符串的同时设置全局类型变量
                p = tkstr.data;
                out2File = tkstr.data;
                // cout<<p;               //get_tkstr(token);
            }
            // >TK_CINT<TK_CSTR的是常量部分
            else if(token >= TK_CINT){
                // SetConsoleTextAttribute(h,FOREGROUND_RED|FOREGROUND_GREEN);
                p=get_tkstr(token);     //函数返回的是带引号的，为了照顾控制台输出的
                out2File = tkstr.data;  //tkstr是不带引号的内容
                // cout<<p;
            }
            // 其他的就是排在最前面的是运算符分隔符部分
            else{
                // SetConsoleTextAttribute(h,FOREGROUND_RED|FOREGROUND_INTENSITY);
                p=get_tkstr(token);
                out2File = p;
                // if(token != TK_EOF)
                    // printf("%s",p);
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
            // printf("%c",ch);
            break;
        }
    }
}