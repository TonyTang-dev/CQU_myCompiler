#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include "func.h"

using namespace std;


// 导入全局文件


/* 初始化 */
void init(){
    line_num = 1;
    init_lex();
}

/* 扫尾清理工作 */
void cleanup(){
    int i;
    printf("--->Tktable.count=%d\n",tktable.count);
    for(i=TK_IDENT;i<tktable.count;i++){
        free(tktable.data[i]);
    }
    free(tktable.data);
}


int main(int argc, char **argv){
    char infile[30] = "testfile.txt";
    // fin = fopen("infile.txt", "rb");//argv[1]
    fin2 = fopen(infile, "rb");//argv[1]
    
    // fout = fopen("output1.txt","w");
    fout2 = fopen("output.txt","w");

    // if(!fin){
    //     printf("--->Fail to open source file");
    //     return 0;
    // }

    // init();

    // getch();
    // do{
    //     get_token();
    //     color_token(LEX_NORMAL);
    // }while(token != TK_EOF);

    // get_token();

    // translation_unit();

    /* 设置控制台提示语句为白色 */
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

    cout<<"\n\n============================================\n"<<endl;
    printf("--->File row counts:%d rows\n",line_num);

    init2();

    // cleanup();
    // fclose(fin);
    // fclose(fout);
    fclose(fin2);
    fclose(fout2);

    printf("--->File \"%s\" lexcial analysis successfully!\n",infile);
    cout<<"\n============================================"<<endl;
    system("pause");
    return 0;
}