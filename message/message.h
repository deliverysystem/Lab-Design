#ifndef MESSAGE_H
#define MESSAGE_H

struct message
{
	int messagemoney;    //��ǰǮ�� 
 	int sum;	  //�ӵ��� 
 	int accomplish;//����� 
 	int totalovertime;//��ʱ�� 
};

extern void printmessage(struct message);

#endif
