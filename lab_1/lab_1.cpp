#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;


class lexicalAnalysis{
    public:
        bool isKeyword(string word, FILE* fout);
        bool isSeparater(char ch, FILE* fout);
        bool isOperator(char ch, FILE* fout);
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
        char SEPARATER[9]={';',',',':','{','}','[',']','(',')'};    //�ָ���
        string separaterName[9]={"SEMICN","COMMA","COLON","LBRACE","RBRACE","LBRACK","RBRACK",
					"LPARENT","RPARENT"
		};
        char OPERATOR[8]={'+','-','*','/','<','>','=','!'};     //�����
		string operatorName[8]={
			"PLUS","MINU","MULT","DIV","LSS","GRE","ASSIGN","NOT"
		};
		string operatorNameK[4]={
			"LEQ","GEQ","EQL","NEQ"
		};
        const int IDENTIFIER=100;         //��ʶ��ֵ
        const int CONSTANT=101;           //����ֵ
        const int FILTER_VALUE=102;       //�����ַ�ֵ
};

bool lexicalAnalysis::isKeyword(string word, FILE *fout){
//	string tempArr = "";
	
	for(int k=0;k<word.length();k++){
		char tempChar = word[k];
		if(tempChar>=65 && tempChar<=90){
//			tempArr = tempArr + (tempChar+32);
			word[k] = tempChar+32;
		}
	}
	
    for(int i=0;i<15;i++){
        if(KEYWORD[i] == word){
//        	cout<<keyName[i];
        	fprintf(fout, "%s ", keyName[i].c_str());
            return true;
        }
    }

    return false;
}

bool lexicalAnalysis::isSeparater(char ch, FILE *fout){
    for(int i=0;i<9;i++){
        if(SEPARATER[i] == ch){
//        	cout<<separaterName[i];
			fprintf(fout, "%s ", separaterName[i].c_str());
            return true;
        }
    }
    return false;
}

bool lexicalAnalysis::isOperator(char ch, FILE *fout){
    for(int i=0;i<8;i++){
        if(OPERATOR[i] == ch){
//        	cout<<operatorName[i];
        	fprintf(fout, "%s ", operatorName[i].c_str());
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

        if(ch=='_' || isLowletter(ch) || isUpletter(ch)){
            while(isLowletter(ch) || isUpletter(ch) || ch=='_' || isDigit(ch)){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

            // �ؼ����ж�
            if(isKeyword(arr, fout)){
//                cout<<" "<<arr<<endl;
                fprintf(fout, "%s\n", arr.c_str());
            }
            else{
//                cout<<"IDENFR "<<arr<<endl;
                fprintf(fout, "IDENFR %s\n", arr.c_str());
            }
        }
        
        else if(ch == '\''){
        	ch = fgetc(fpin);
        	while(ch != '\''){
                arr += ch;
                ch = fgetc(fpin);
            }

			if (arr != ""){
//				cout<<"CHARCON "<<arr<<endl;
				fprintf(fout, "CHARCON %s\n", arr.c_str());
			}
		}
		
		else if(ch == '\"'){
        	ch = fgetc(fpin);
        	while(ch != '\"'){
                arr += ch;
                ch = fgetc(fpin);
            }

			if (arr != ""){
//				cout<<"STRCON "<<arr<<endl;
				fprintf(fout, "STRCON %s\n", arr.c_str());
			}
		}
        
        else if(isDigit(ch)){
            while(isDigit(ch) || (ch=='.' && isDigit(fgetc(fpin)))){
                arr += ch;
                ch = fgetc(fpin);
            }

            fseek(fpin, -1L, SEEK_CUR);

//            cout<<"INTCON "<<arr<<endl;
            fprintf(fout, "INTCON %s\n", arr.c_str());
        }
        else{
        	for(int j=0;j<9;j++){
        		if(ch == SEPARATER[j]){
//        			cout<<separaterName[j]<<" "<<ch<<endl;
        			fprintf(fout, "%s %c\n", separaterName[j].c_str(),ch);
					break;
				}
			}
			for(int k=0;k<8;k++){
				if(ch == OPERATOR[k]){
//        			cout<<operatorName[k]<<" "<<ch<<endl;
					char tempChar = fgetc(fpin);
					if (tempChar == '='){
						fprintf(fout, "%s %c=\n", operatorNameK[k%4].c_str(),ch);
						break;
					}

					fseek(fpin, -1L, SEEK_CUR);
					
					fprintf(fout, "%s %c\n", operatorName[k].c_str(),ch);
					break;
				}
			}
        }
    }
}


int main(){
    char inFile[40]= "lab_1/testfile.txt";
    char outFile[40]= "lab_1/output.txt";

    FILE *fpin;
    FILE *fout;

    fout = fopen(outFile, "w");
//	fout.open(outFile, ios::out | ios::app);

    while(true){
        if((fpin = fopen(inFile, "r")) != NULL){
            break;
        }
        else{
            cout<<"file not exist";
        }
    }

    lexicalAnalysis ins;

    ins.lexicalAnalyse(fpin, fout);

	fclose(fpin);
	fclose(fout);
    system("pause");
    return 0;
}
