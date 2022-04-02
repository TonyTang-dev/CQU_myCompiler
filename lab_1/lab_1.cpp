#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;


class lexicalAnalysis{
    public:
        bool isKeyword(string word);
        bool isSeparater(char ch);
        bool isOperator(char ch);
        bool isUpletter(char ch);
        bool isLowletter(char ch);
        bool isDigit(char ch);

        void lexicalAnalyse(FILE *fpin);

    private:
        string KEYWORD[15]={"if","else","void","return","while","then","for","do",      //关键字
                    "int","char","double","float","case","cin","cout"};
        char SEPARATER[8]={';',',','{','}','[',']','(',')'};    //分隔符
        char OPERATOR[8]={'+','-','*','/','>','<','=','!'};     //运算符
        char FILTER[4]={' ','\t','\r','\n'};                    //过滤符
        const int IDENTIFIER=100;         //标识符值
        const int CONSTANT=101;           //常数值
        const int FILTER_VALUE=102;       //过滤字符值
};

bool lexicalAnalysis::isKeyword(string word){
    for(int i=0;i<15;i++){
        if(KEYWORD[i] == word){
            return true;
        }
    }

    return false;
}

bool lexicalAnalysis::isSeparater(char ch){
    for(int i=0;i<8;i++){
        if(SEPARATER[i] == ch){
            return true;
        }
    }
    return false;
}

bool lexicalAnalysis::isOperator(char ch){
    for(int i=0;i<8;i++){
        if(OPERATOR[i] == ch){
            return true;
        }
    }
    return false;
}

bool lexicalAnalysis::isUpletter(char ch){
    if(ch >= 'A' && ch <= 'Z'){
        return true;
    }

    return false;
}

bool lexicalAnalysis::isLowletter(char ch){
    if(ch >= 'a' && ch <= 'z'){
        return true;
    }

    return false;
}

bool lexicalAnalysis::isDigit(char ch){
    if(ch >= '0' && ch <= '9'){
        return true;
    }

    return false;
}

void lexicalAnalysis::lexicalAnalyse(FILE *fpin){
    char ch = ' ';
    string arr = "";

    while ((ch=fgetc(fpin)) != EOF){
        arr = "";

        if(isLowletter(ch)){
            while(isLowletter(ch)){
                arr += ch;
                ch = fgetc(fpin);
            }

            // 关键字判断
            if(isKeyword(arr)){
                cout<<"关键字："<<arr<<endl;
            }
            else{
                cout<<"标识符："<<arr<<endl;
            }
        }
        else if(isDigit(ch)){
            while(isDigit(ch) || (ch=='.' && isDigit(fgetc(fpin)))){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

            cout<<"整形数："<<arr<<endl;
        }
        else if(isUpletter(ch) || isLowletter(ch) || ch == '_'){
            while(isUpletter(ch) || isLowletter(ch) || ch == '_' ||isDigit(ch)){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

            cout<<"标识符："<<arr<<endl;
        }
        else{
            switch(ch){
                case '+':
                case '-':
                case '*':
                case '/':
                case '>':
                case '<':
                case '=':
                case '!':{
                    arr += ch;
                    cout<<"运算符："<<arr<<endl;
                    break;
                }

                case ';':
                case ',':
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':{
                    arr += ch;
                    cout<<"分隔符："<<arr<<endl;
                    break;
                }

                default:{
                    cout<<"无法识别"<<endl;
                    break;
                }
            }
        }
    }
}


int main(){
    char inFile[40];
    FILE *fpin;
    cout<<"请选择源文件：";

    while(true){
        cin>>inFile;

        if((fpin = fopen(inFile, "r")) != NULL){
            break;
        }
        else{
            cout<<"文件不存在，请再次输入：";
        }
    }

    cout<<"===============分析结果==============="<<endl;

    lexicalAnalysis ins;

    ins.lexicalAnalyse(fpin);


    system("pause");
    return 0;
}