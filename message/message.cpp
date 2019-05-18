#include<stdio.h>
#include"point.h"
#include"tools.h"
#include"message.h"
#include"controller.h" 
void printmessage(struct message a){
	SetCursorPosition(17,74);
	printf("当前时刻：%d",sysclock);
	printf("当前钱数：%d\n",a.messagemoney);
	printf("接单数：%d\n",a.sum);
	printf("完成数：%d\n",a.accomplish);
	printf("超时数：%d\n",a.totalovertime);
}

