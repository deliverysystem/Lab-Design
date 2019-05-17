#include<stdio.h>
#include"point.h"
#include"tools.h"
#include"message.h"
void printmessage(struct message a){
	int i;
	SetCursorPosition(52,0);
	printf("当前钱数：%d\n",a.messagemoney);
	printf("接单数：%d\n",a.sum);
	printf("完成数：%d\n",a.accomplish);
	printf("超时数：%d\n",a.totalovertime);
}
