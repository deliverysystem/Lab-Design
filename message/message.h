#ifndef MESSAGE_H
#define MESSAGE_H

struct message
{
	int messagemoney;    //当前钱数 
 	int sum;	  //接单数 
 	int accomplish;//完成数 
 	int totalovertime;//超时数 
};

extern void printmessage(struct message);

#endif
