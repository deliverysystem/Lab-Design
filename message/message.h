#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct message
{
	int messagemoney;    //��ǰǮ�� 
 	int sum;	  //�ӵ��� 
 	int accomplish;//����� 
 	int overtime;//��ʱ�� 
}Message;

extern void printmessage(Message ,Rider []);

#endif
