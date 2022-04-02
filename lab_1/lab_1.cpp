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

        void lexicalAnalyse(FILE *fpin, FILE *fout);

    private:
		string KEYWORD[15]={
			"const","int","char","void","main","if","else","switch","case",
			"default","while","for","scanf","printf","return"
		};
		string keyName[15]={
			"CONSTTK","INTTK","CHARTK","VOIDTK","MAINTK","IFTK","ELSETK","SWITCHTK",
			"CASETK","DEFAULTTK","WHILETK","FORTK","SCANFTK","PRINTFTK","RETURNTK"
		};
        char SEPARATER[8]={';',',','{','}','[',']','(',')'};    //分隔符
        string separaterName[8]={"SEMICN","COMMA","LBRACE","RBRACE","LBRACK","RBRACK",
					"LPARENT","RPARENT"
		};
        char OPERATOR[8]={'+','-','*','/','>','<','=','!'};     //运算符
		string operatorName[8]={
			"PLUS","MINU","MULT","DIV","GSS","LSS","ASSIGN","NOT"
		};
        const int IDENTIFIER=100;         //标识符值
        const int CONSTANT=101;           //常数值
        const int FILTER_VALUE=102;       //过滤字符值
};

bool lexicalAnalysis::isKeyword(string word){
    for(int i=0;i<15;i++){
        if(KEYWORD[i] == word){
        	cout<<keyName[i];
            return true;
        }
    }

    return false;
}

bool lexicalAnalysis::isSeparater(char ch){
    for(int i=0;i<8;i++){
        if(SEPARATER[i] == ch){
        	cout<<separaterName[i];
            return true;
        }
    }
    return false;
}

bool lexicalAnalysis::isOperator(char ch){
    for(int i=0;i<8;i++){
        if(OPERATOR[i] == ch){
        	cout<<operatorName[i];
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

void lexicalAnalysis::lexicalAnalyse(FILE *fpin, FILE *fout){
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
                cout<<" "<<arr<<endl;
            }
            else{
                cout<<"IDENFR "<<arr<<endl;
            }
        }
        else if(isDigit(ch)){
            while(isDigit(ch) || (ch=='.' && isDigit(fgetc(fpin)))){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

            cout<<"INTCON "<<arr<<endl;
        }
        else if(isUpletter(ch) || isLowletter(ch) || ch == '_'){
            while(isUpletter(ch) || isLowletter(ch) || ch == '_' ||isDigit(ch)){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

            cout<<"IDENFR "<<arr<<endl;
        }
        else{
        	for(int j=0;j<8;j++){
        		if(ch == SEPARATER[j]){
        			cout<<separaterName[j]<<" "<<ch<<endl;
					continue;
				}
			}
			for(int k=0;k<8;k++){
				if(ch == OPERATOR[k]){
        			cout<<operatorName[k]<<" "<<ch<<endl;
					continue;
				}
			}
//            switch(ch){
//                case '+':
//                case '-':
//                case '*':
//                case '/':
//                case '>':
//                case '<':
//                case '=':
//                case '!':{
//                    arr += ch;
//                    cout<<"运算符："<<arr<<endl;
//                    break;
//                }
//
//                case ';':
//                case ',':
//                case '(':
//                case ')':
//                case '[':
//                case ']':
//                case '{':
//                case '}':{
//                    arr += ch;
//                    cout<<"分隔符："<<arr<<endl;
//                    break;
//                }
//
//                default:{
//                    cout<<"无法识别"<<endl;
//                    break;
//                }
//            }
        }
    }
}


int main(){
    char inFile[40]= "testfile.txt";
    char outFile[40]= "output.txt";
    
    FILE *fpin;
    FILE *fout;
    
    fout = fopen(outFile, "w");
    
    while(true){
        if((fpin = fopen(inFile, "r")) != NULL){
            break;
        }
        else{
            cout<<"文件不存在，请再次输入：";
        }
    }

    lexicalAnalysis ins;

    ins.lexicalAnalyse(fpin, fout);
    
    fprintf(fout, "%s\n", "hjsdjhjf");
	fprintf(fout, "%s\n", "hjsdjhjf");

	fclose(fpin);
	fclose(fout);
    system("pause");
    return 0;
}
