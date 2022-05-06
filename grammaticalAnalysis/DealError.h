/* 异常处理 */
#include<stdio.h>
#include<stdarg.h>

#include<iostream>

#include "memorizeMethod_init.h"

using namespace std;

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

