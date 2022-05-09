/* 操作存储单词数据结构的方法+初始化操作（存入关键词等） */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<iostream>

using namespace std;

#include "Global.h"

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
        // printf("内存分配失败");
        printf("allocation memery failed!");
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
        // printf("内存分配失败");
        printf("allocation memery failed!");
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
        // printf("内存分配失败");
        printf("allocation memery failed!");
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

