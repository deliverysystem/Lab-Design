#include<stdio.h>
#include"point.h"
#include"tools.h"
#include"message.h"
void printmessage(struct message a){
	int i;
	SetCursorPosition(52,0);
	printf("��ǰǮ����%d\n",a.messagemoney);
	printf("�ӵ�����%d\n",a.sum);
	printf("�������%d\n",a.accomplish);
	printf("��ʱ����%d\n",a.totalovertime);
}
