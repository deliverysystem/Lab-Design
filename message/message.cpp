#include<stdio.h>
#include"point.h"
#include"tools.h"
#include"message.h"
#include"controller.h" 
void printmessage(struct message a){
	int i;
	int j;
	for(i=17;i<=21;i++)
		for(j=74;j<=94;j++)
		{
			SetCursorPosition(i,j);
			printf(" ");
		}
	SetCursorPosition(17,74);
	printf("当前时刻：%d	",sysclock);
	SetCursorPosition(18,74);
	printf("当前钱数：%d\n",money);
	SetCursorPosition(19,74);
	printf("接单数：%d\n",a.sum);
	SetCursorPosition(20,74);
	printf("完成数：%d\n",a.accomplish);
	SetCursorPosition(21,74);
	printf("超时数：%d\n",a.totalovertime);
	SetCursorPosition(16,74);
}
