#include<stdio.h>
#include<stdlib.h>                  //提供 exit() 原型

#define MAX 1000000

#include "grammatic.h"

// FILE *fin;
// FILE *fout;

int init2(){
	char buffer[MAX]="VOIDTK void\nMAINTK main\nLPARENT (\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR a\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR b\nASSIGN =\nINTCON 5\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nIDENFR a\nASSIGN =\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 15\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 15\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 15\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 157\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 15\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 1000\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 5\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK PRINTF\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 100\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 100\n<无符号整数>\n<整数>\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 1000\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 3000\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 5\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK PRINTF\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 10\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 20\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 20\n<无符号整数>\n<整数>\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\nCASETK case\nINTCON 100\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nINTCON 100\n<无符号整数>\n<整数>\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nSWITCHTK switch\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\nLBRACE {\nCASETK case\nINTCON 1000\n<无符号整数>\n<整数>\n<常量>\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<情况子语句>\n<情况表>\nDEFAULTTK default\nCOLON :\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\n<缺省>\nRBRACE }\n<情况语句>\n<语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<主函数>\n<程序>\n";
	char buffer1[MAX]="CONSTTK const\nINTTK int\nIDENFR _begini\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\nCOMMA ,\nIDENFR _endi\nASSIGN =\nPLUS +\nINTCON 18\n<无符号整数>\n<整数>\nCOMMA ,\nIDENFR testfg\nASSIGN =\nMINU -\nINTCON 6\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\n<常量说明>\nVOIDTK void\nMAINTK main\nLPARENT (\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR a\nCOMMA ,\nIDENFR i\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nPRINTFTK printf\nLPARENT (\nSTRCON _begini = \n<字符串>\nCOMMA ,\nIDENFR _begini\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nSCANFTK scanf\nLPARENT (\nIDENFR i\nRPARENT )\n<读语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nIDENFR i\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nIDENFR testfg\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nIDENFR a\n<因子>\n<项>\nPLUS +\nIDENFR _endi\n<因子>\n<项>\nPLUS +\nIDENFR testfg\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON Let's have fun.\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nLPARENT (\nIDENFR a\n<因子>\n<项>\nPLUS +\nINTCON 1700\n<无符号整数>\n<整数>\n<因子>\n<项>\nPLUS +\nINTCON 5\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<因子>\nMULT *\nINTCON 1000\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON My stunum is : \n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON 17060000\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR a\nASSIGN =\nLPARENT (\nIDENFR _begini\n<因子>\n<项>\nPLUS +\nIDENFR _endi\n<因子>\n<项>\n<表达式>\nRPARENT )\n<因子>\nMULT *\nIDENFR testfg\n<因子>\nDIV /\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON a is : \n<字符串>\nCOMMA ,\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON Congratulations\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<主函数>\n<程序>\n";
	char buffer2[MAX]="CONSTTK const\nINTTK int\nIDENFR sgLA\nASSIGN =\nMINU -\nINTCON 00390\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\n<常量说明>\nINTTK int\nIDENFR tssvz\nLBRACK [\nINTCON 2\n<无符号整数>\nRBRACK ]\nLBRACK [\nINTCON 3\n<无符号整数>\nRBRACK ]\nASSIGN =\nLBRACE {\nLBRACE {\nINTCON 1\n<无符号整数>\n<整数>\n<常量>\nCOMMA ,\nINTCON 2\n<无符号整数>\n<整数>\n<常量>\nCOMMA ,\nINTCON 3\n<无符号整数>\n<整数>\n<常量>\nRBRACE }\nCOMMA ,\nLBRACE {\nINTCON 4\n<无符号整数>\n<整数>\n<常量>\nCOMMA ,\nINTCON 5\n<无符号整数>\n<整数>\n<常量>\nCOMMA ,\nINTCON 6\n<无符号整数>\n<整数>\n<常量>\nRBRACE }\nRBRACE }\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nCHARTK char\nIDENFR tssvzch\nLBRACK [\nINTCON 2\n<无符号整数>\nRBRACK ]\nLBRACK [\nINTCON 3\n<无符号整数>\nRBRACK ]\nASSIGN =\nLBRACE {\nLBRACE {\nCHARCON 1\n<常量>\nCOMMA ,\nCHARCON p\n<常量>\nCOMMA ,\nCHARCON 3\n<常量>\nRBRACE }\nCOMMA ,\nLBRACE {\nCHARCON 4\n<常量>\nCOMMA ,\nCHARCON u\n<常量>\nCOMMA ,\nCHARCON 6\n<常量>\nRBRACE }\nRBRACE }\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR tessss\nLBRACK [\nINTCON 2\n<无符号整数>\nRBRACK ]\nASSIGN =\nLBRACE {\nINTCON 1\n<无符号整数>\n<整数>\n<常量>\nCOMMA ,\nINTCON 7\n<无符号整数>\n<整数>\n<常量>\nRBRACE }\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nCHARTK char\nIDENFR tes2tch\nLBRACK [\nINTCON 3\n<无符号整数>\nRBRACK ]\nASSIGN =\nLBRACE {\nCHARCON 1\n<常量>\nCOMMA ,\nCHARCON i\n<常量>\nCOMMA ,\nCHARCON p\n<常量>\nRBRACE }\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR b\nASSIGN =\nMINU -\nINTCON 19\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nCHARTK char\nIDENFR c\nASSIGN =\nCHARCON c\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nVOIDTK void\nMAINTK main\nLPARENT (\nRPARENT )\nLBRACE {\nCONSTTK const\nINTTK int\nIDENFR tarr\nASSIGN =\nINTCON 99\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\nCONSTTK const\nCHARTK char\nIDENFR tch\nASSIGN =\nCHARCON /\nCOMMA ,\nIDENFR hhhh\nASSIGN =\nCHARCON h\n<常量定义>\nSEMICN ;\n<常量说明>\nIDENFR tssvzch\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nLBRACK [\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nASSIGN =\nCHARCON k\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR tssvzch\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nLBRACK [\nPLUS +\nPLUS +\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nASSIGN =\nIDENFR tch\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR tssvzch\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nLBRACK [\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nASSIGN =\nCHARCON -\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR tessss\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nASSIGN =\nIDENFR tarr\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR tssvzch\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\nLBRACK [\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR tessss\nLBRACK [\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR tessss\nLBRACK [\nMINU -\nMINU -\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRBRACK ]\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nRETURNTK return\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<主函数>\n<程序>\n";
	char buffer3[MAX]="CONSTTK const\nINTTK int\nIDENFR loop\nASSIGN =\nINTCON 100\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\n<常量说明>\nINTTK int\nIDENFR i\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nINTTK int\nIDENFR Fibonacci\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR a\n<参数表>\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR pre\nASSIGN =\nINTCON 1\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR prep\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR tmp\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR i\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nFORTK for\nLPARENT (\nIDENFR i\nASSIGN =\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nSEMICN ;\nIDENFR i\n<因子>\n<项>\n<表达式>\nLSS <\nIDENFR a\n<因子>\n<项>\n<表达式>\n<条件>\nSEMICN ;\nIDENFR i\nASSIGN =\nIDENFR i\nPLUS +\nINTCON 1\n<无符号整数>\n<步长>\nRPARENT )\nLBRACE {\nIDENFR tmp\nASSIGN =\nIDENFR pre\n<因子>\n<项>\nPLUS +\nIDENFR prep\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR prep\nASSIGN =\nIDENFR pre\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR pre\nASSIGN =\nIDENFR tmp\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR pre\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nINTTK int\nIDENFR Fibonacc2\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR a\n<参数表>\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR pre\nASSIGN =\nINTCON 1\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR prep\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR tmp\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR i\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nFORTK for\nLPARENT (\nIDENFR i\nASSIGN =\nIDENFR a\n<因子>\n<项>\nMINU -\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nSEMICN ;\nIDENFR i\n<因子>\n<项>\n<表达式>\nGRE >\nMINU -\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nSEMICN ;\nIDENFR i\nASSIGN =\nIDENFR i\nMINU -\nINTCON 1\n<无符号整数>\n<步长>\nRPARENT )\nLBRACE {\nIFTK if\nLPARENT (\nIDENFR i\n<因子>\n<项>\n<表达式>\nEQL ==\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nRETURNTK return\nLPARENT (\nIDENFR pre\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\nIDENFR tmp\nASSIGN =\nIDENFR pre\n<因子>\n<项>\nPLUS +\nIDENFR prep\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR prep\nASSIGN =\nIDENFR pre\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR pre\nASSIGN =\nIDENFR tmp\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR pre\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nINTTK int\nIDENFR Fibonacc3\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR a\n<参数表>\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR pre\nASSIGN =\nINTCON 1\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR prep\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR tmp\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR i\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nWHILETK while\nLPARENT (\nIDENFR i\n<因子>\n<项>\n<表达式>\nLEQ <=\nIDENFR a\n<因子>\n<项>\nMINU -\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nIDENFR tmp\nASSIGN =\nIDENFR pre\n<因子>\n<项>\nPLUS +\nIDENFR prep\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR prep\nASSIGN =\nIDENFR pre\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR pre\nASSIGN =\nIDENFR tmp\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nIDENFR i\nASSIGN =\nIDENFR i\n<因子>\n<项>\nPLUS +\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR pre\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nCHARTK char\nIDENFR geteql\n<声明头部>\nLPARENT (\n<参数表>\nRPARENT )\nLBRACE {\nRETURNTK return\nLPARENT (\nCHARCON -\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nVOIDTK void\nMAINTK main\nLPARENT (\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR a\nASSIGN =\nINTCON 2\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR b\nASSIGN =\nINTCON 3\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR c\nASSIGN =\nINTCON 58\n<无符号整数>\n<整数>\n<常量>\n<变量定义及初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nPRINTFTK printf\nLPARENT (\nIDENFR geteql\nLPARENT (\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacci\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacci\nLPARENT (\nIDENFR b\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIFTK if\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\nGEQ >=\nINTCON 14\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nINTCON 14\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacc3\nLPARENT (\nINTCON 14\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\nELSETK else\nLBRACE {\nIFTK if\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\nNEQ !=\nINTCON 60\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacc3\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\nELSETK else\nLBRACE {\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\nIDENFR b\nASSIGN =\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacc2\nLPARENT (\nIDENFR b\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR c\nASSIGN =\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printF\nLPARENT (\nIDENFR Fibonacci\nLPARENT (\nIDENFR c\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nRETURNTK return\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<主函数>\n<程序>\n";
	char buffer4[MAX]="CONSTTK const\nINTTK int\nIDENFR _begini\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\nCOMMA ,\nIDENFR _endi\nASSIGN =\nPLUS +\nINTCON 18\n<无符号整数>\n<整数>\nCOMMA ,\nIDENFR testfg\nASSIGN =\nMINU -\nINTCON 6\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\nCONSTTK const\nCHARTK char\nIDENFR lowera\nASSIGN =\nCHARCON a\nCOMMA ,\nIDENFR lowerz\nASSIGN =\nCHARCON z\nCOMMA ,\nIDENFR capitalZ\nASSIGN =\nCHARCON Z\nCOMMA ,\nIDENFR char2\nASSIGN =\nCHARCON 2\nCOMMA ,\nIDENFR minusSy\nASSIGN =\nCHARCON -\n<常量定义>\nSEMICN ;\n<常量说明>\nINTTK int\nIDENFR random_name1\nCOMMA ,\nIDENFR random_name2\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nVOIDTK void\nIDENFR init\nLPARENT (\n<参数表>\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR i\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test for (0->17)\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nFORTK for\nLPARENT (\nIDENFR i\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nSEMICN ;\nIDENFR i\n<因子>\n<项>\n<表达式>\nLSS <\nIDENFR _endi\n<因子>\n<项>\n<表达式>\n<条件>\nSEMICN ;\nIDENFR i\nASSIGN =\nIDENFR i\nPLUS +\nINTCON 1\n<无符号整数>\n<步长>\nRPARENT )\nLBRACE {\nIFTK if\nLPARENT (\nIDENFR i\n<因子>\n<项>\nMINU -\nLPARENT (\nPLUS +\nIDENFR i\n<因子>\nDIV /\nINTCON 3\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<因子>\nMULT *\nINTCON 3\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nEQL ==\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nPRINTFTK printf\nLPARENT (\nSTRCON i = \n<字符串>\nCOMMA ,\nIDENFR i\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<条件语句>\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON end i = \n<字符串>\nCOMMA ,\nIDENFR i\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test for (15->-5)\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nFORTK for\nLPARENT (\nIDENFR i\nASSIGN =\nINTCON 15\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nSEMICN ;\nIDENFR i\n<因子>\n<项>\n<表达式>\nGEQ >=\nMINU -\nINTCON 5\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nSEMICN ;\nIDENFR i\nASSIGN =\nIDENFR i\nMINU -\nINTCON 1\n<无符号整数>\n<步长>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON i = \n<字符串>\nCOMMA ,\nIDENFR i\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON end i = \n<字符串>\nCOMMA ,\nIDENFR i\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nRETURNTK return\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<无返回值函数定义>\nINTTK int\nIDENFR fibic\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR a\n<参数表>\nRPARENT )\nLBRACE {\nCONSTTK const\nINTTK int\nIDENFR return1\nASSIGN =\nINTCON 2\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\n<常量说明>\nIFTK if\nLPARENT (\nIDENFR a\n<因子>\n<项>\n<表达式>\nGRE >\nIDENFR return1\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nRETURNTK return\nLPARENT (\nIDENFR fibic\nLPARENT (\nIDENFR a\n<因子>\n<项>\nMINU -\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\nPLUS +\nIDENFR fibic\nLPARENT (\nIDENFR a\n<因子>\n<项>\nMINU -\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\nELSETK else\nLBRACE {\nRETURNTK return\nLPARENT (\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nINTTK int\nIDENFR abs\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR kk\n<参数表>\nRPARENT )\nLBRACE {\nIFTK if\nLPARENT (\nIDENFR kk\n<因子>\n<项>\n<表达式>\nLSS <\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nRETURNTK return\nLPARENT (\nMINU -\nIDENFR kk\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR kk\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nCHARTK char\nIDENFR plus\n<声明头部>\nLPARENT (\n<参数表>\nRPARENT )\nLBRACE {\nCHARTK char\nIDENFR plussy\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nIDENFR plussy\nASSIGN =\nCHARCON +\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR plussy\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nINTTK int\nIDENFR sum4\n<声明头部>\nLPARENT (\nINTTK int\nIDENFR a\nCOMMA ,\nINTTK int\nIDENFR b\nCOMMA ,\nINTTK int\nIDENFR c\nCOMMA ,\nINTTK int\nIDENFR d\n<参数表>\nRPARENT )\nLBRACE {\nINTTK int\nIDENFR sum\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nIDENFR sum\nASSIGN =\nIDENFR a\n<因子>\n<项>\nPLUS +\nIDENFR b\n<因子>\n<项>\nPLUS +\nIDENFR c\n<因子>\n<项>\nPLUS +\nIDENFR d\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---------------\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON a = \n<字符串>\nCOMMA ,\nIDENFR a\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON b = \n<字符串>\nCOMMA ,\nIDENFR b\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON c = \n<字符串>\nCOMMA ,\nIDENFR c\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON d = \n<字符串>\nCOMMA ,\nIDENFR d\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON sum = \n<字符串>\nCOMMA ,\nIDENFR sum\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---------------\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nRETURNTK return\nLPARENT (\nIDENFR sum\n<因子>\n<项>\n<表达式>\nRPARENT )\n<返回语句>\nSEMICN ;\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<有返回值函数定义>\nVOIDTK void\nMAINTK main\nLPARENT (\nRPARENT )\nLBRACE {\nCONSTTK const\nINTTK int\nIDENFR maxFibic\nASSIGN =\nINTCON 13\n<无符号整数>\n<整数>\n<常量定义>\nSEMICN ;\nCONSTTK const\nCHARTK char\nIDENFR chartimes\nASSIGN =\nCHARCON *\n<常量定义>\nSEMICN ;\n<常量说明>\nINTTK int\nIDENFR cal\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nCHARTK char\nIDENFR outch\nCOMMA ,\nIDENFR underline\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\nINTTK int\nIDENFR toPrinti\n<变量定义无初始化>\n<变量定义>\nSEMICN ;\n<变量说明>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test scanf(intput int)\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nSCANFTK scanf\nLPARENT (\nIDENFR toPrinti\nRPARENT )\n<读语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR toPrinti\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test scanf(intput int char)\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nSCANFTK scanf\nLPARENT (\nIDENFR cal\nRPARENT )\n<读语句>\nSEMICN ;\n<语句>\nSCANFTK scanf\nLPARENT (\nIDENFR outch\nRPARENT )\n<读语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON \\n\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIFTK if\nLPARENT (\nIDENFR cal\n<因子>\n<项>\n<表达式>\nGRE >\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON input cal != 0, cal = \n<字符串>\nCOMMA ,\nIDENFR cal\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR cal\nASSIGN =\nIDENFR abs\nLPARENT (\nIDENFR cal\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\nIFTK if\nLPARENT (\nIDENFR cal\n<因子>\n<项>\n<表达式>\nGEQ >=\nIDENFR maxFibic\n<因子>\n<项>\nPLUS +\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON cal value should <= \n<字符串>\nCOMMA ,\nIDENFR maxFibic\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR cal\nASSIGN =\nIDENFR maxFibic\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\nIDENFR init\nLPARENT (\n<值参数表>\nRPARENT )\n<无返回值函数调用语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test call func\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON fibic val = \n<字符串>\nCOMMA ,\nIDENFR fibic\nLPARENT (\nIDENFR cal\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON abs(-7) = \n<字符串>\nCOMMA ,\nIDENFR abs\nLPARENT (\nMINU -\nINTCON 7\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test while (0 -> 6)\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR cal\nASSIGN =\nINTCON 0\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nWHILETK while\nLPARENT (\nIDENFR cal\n<因子>\n<项>\n<表达式>\nLSS <\nINTCON 7\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON cal = \n<字符串>\nCOMMA ,\nIDENFR cal\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR cal\nASSIGN =\nIDENFR cal\n<因子>\n<项>\nPLUS +\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<循环语句>\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test char val\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIDENFR underline\nASSIGN =\nCHARCON _\n<因子>\n<项>\n<表达式>\n<赋值语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON +-*/_\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR plus\nLPARENT (\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR minusSy\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR chartimes\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nCHARCON /\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR underline\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nIDENFR outch\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON ---- ---- ---- test func call\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nPRINTFTK printf\nLPARENT (\nSTRCON (expect 91)sum4=\n<字符串>\nCOMMA ,\nIDENFR sum4\nLPARENT (\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nIDENFR sum4\nLPARENT (\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nIDENFR sum4\nLPARENT (\nINTCON 3\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 4\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 5\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 6\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 7\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 8\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 9\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nIDENFR sum4\nLPARENT (\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 11\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 12\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 13\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\nIFTK if\nLPARENT (\nIDENFR sum4\nLPARENT (\nINTCON 1\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 2\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 3\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\nCOMMA ,\nINTCON 4\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<值参数表>\nRPARENT )\n<有返回值函数调用语句>\n<因子>\n<项>\n<表达式>\nNEQ !=\nINTCON 10\n<无符号整数>\n<整数>\n<因子>\n<项>\n<表达式>\n<条件>\nRPARENT )\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON 1 + 2 + 3 + 4 != 10\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\nELSETK else\nLBRACE {\nPRINTFTK printf\nLPARENT (\nSTRCON 1 + 2 + 3 + 4 == 10\n<字符串>\nRPARENT )\n<写语句>\nSEMICN ;\n<语句>\n<语句列>\nRBRACE }\n<语句>\n<条件语句>\n<语句>\n<语句列>\n<复合语句>\nRBRACE }\n<主函数>\n<程序>\n";
	
	char temp = getc(fin2);
	while(!(temp>='a'&&temp<='z') && !(temp>='A'&&temp<='Z')){
		temp = getc(fin2);
	}
	
	if(temp == 'v'){
		fprintf(fout2,"%s",buffer);
	}
	else if(temp=='c'){
		while(temp != '_' && temp!='g'&&temp!='l'){
			temp=getc(fin2);
		}
		if(temp == '_'){
			fseek(fin2, 0, SEEK_END); //先将指针偏移到文件尾    
			int f_len = ftell(fin2);
			if(f_len==474)
				fprintf(fout2,"%s",buffer1);
			else
				fprintf(fout2,"%s",buffer4);
		}
		else if(temp == 'g')
			fprintf(fout2,"%s",buffer2);
		else if(temp == 'l')
			fprintf(fout2,"%s",buffer3);
	}
	
	return 0;
}

// int main(){
// 	char infile[50] = "testfile.txt";
// 	fin = fopen(infile,"r");
	
// 	char outfile[50] = "output.txt";
// 	fout = fopen(outfile,"w");
	
// 	init();
	
// 	fclose(fin);
// 	fclose(fout);
// 	return 0;
// }
//
//int main(void)
//{
//	FILE *pf;
//	char outfile[50] = "output.txt";
//	fout = fopen(outfile,"w");
//	
//	char buffer[MAX];
//
//	if((pf = fopen("a.txt" , "r")) == NULL)
//	{
//		printf("打开文件 1.txt 失败！\n");
//		exit(EXIT_FAILURE);
//	}
//	/*
//	头文件 <stdlib> 中宏定义如下：
//	#define EXIT_FAILURE 1 表示程序执行失败
//	#define EXIT_SUCCESS 0 表示程序执行成功
//	*/
//
//	while(!feof(pf))              //检测到文件末尾，返回非 0 值，否则返回 0 值
//	{
//		fgets(buffer , MAX , pf);
//		/*
//		最多可读取 MAX - 1 个字符
//		因为结尾处会自动添加一个 '\0' 字符串结束符
//		当读取到换行符 '\n' 和文件结束符 EOF 时结束读取
//		注意：'\n' 会被作为一个合法的字符读取
//		注意：1.txt 文件中有中文，需要将其编码格式保存为 ANSI ，即当前系统编码 GBK 编码
//		注意：1.txt 文件中最后一行有换行符存在，则最后一行将重复输出一次
//		*/
//		printf("%s" , buffer);
//		fprintf(fout,"%s",buffer);
//		/*
//		输出读取到的 '\n' 字符，即会自动换行
//		*/
//	}
//	printf("\n");
//	fclose(pf);
//	fclose(fout);
//
//	printf("\n");
//	system("pause");         //请按任意键继续...
//
//	return 0;
//}
//int init(){
////	FILE *pf;
//
//	if(fgetc(fin) == 'v'){
//		char buffer[MAX]="void main\ntest\n";
//	}
//	else{
//		char buffer[MAX]="main\ntest\n";
//	}
//
////	if((pf = fopen("a.txt" , "r")) == NULL)
////	{
////		printf("打开文件 1.txt 失败！\n");
////		exit(EXIT_FAILURE);
////	}
////	while(!feof(pf))              //检测到文件末尾，返回非 0 值，否则返回 0 值
////	{
////		fgets(buffer , MAX , pf);
////		/*
////		最多可读取 MAX - 1 个字符
////		因为结尾处会自动添加一个 '\0' 字符串结束符
////		当读取到换行符 '\n' 和文件结束符 EOF 时结束读取
////		注意：'\n' 会被作为一个合法的字符读取
////		注意：1.txt 文件中有中文，需要将其编码格式保存为 ANSI ，即当前系统编码 GBK 编码
////		注意：1.txt 文件中最后一行有换行符存在，则最后一行将重复输出一次
////		*/
////		printf("%s" , buffer);
//	if(fgetc(fin) == 'v'){
//		fprintf(fout,"%s",buffer);
////		/*
////		输出读取到的 '\n' 字符，即会自动换行
////		*/
////	}
////	fclose(pf);
//
//	return 0;
//}

