#include<stdio.h>
#include"point.h"
#include"tools.h"
#include"message.h"
#include"controller.h" 
void printmessage(struct message a){
	int i;
	int j;
	for(i=28;i<=32;i++){
		int j=76; 
		SetCursorPosition(i,j);
		printf("                                        ");
	}
	SetCursorPosition(27,76);
	printf("————————————");
	SetCursorPosition(33,76);
	printf("————————————");
	SetCursorPosition(28,76);
	printf("|");
	SetCursorPosition(29,76);
	printf("|");
	SetCursorPosition(30,76);
	printf("|");
	SetCursorPosition(31,76);
	printf("|");
	SetCursorPosition(32,76);
	printf("|");
	SetCursorPosition(28,99);
	printf("|");
	SetCursorPosition(29,99);
	printf("|");
	SetCursorPosition(30,99);
	printf("|");
	SetCursorPosition(31,99);
	printf("|");
	SetCursorPosition(32,99);
	printf("|");
	SetCursorPosition(28,78);
	printf("当前时刻：%d	",sysclock);
	SetCursorPosition(29,78);
	printf("当前钱数：%d\n",money);
	SetCursorPosition(30,78);
	printf("接单数：%d\n",a.sum);
	SetCursorPosition(31,78);
	printf("完成数：%d\n",a.accomplish);
	SetCursorPosition(32,78);
	printf("超时数：%d\n",a.totalovertime);
	SetCursorPosition(26,87);
}
