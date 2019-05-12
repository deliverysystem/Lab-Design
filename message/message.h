#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct message
{
	int messagemoney;    //当前钱数 
 	int sum;	  //接单数 
 	int accomplish;//完成数 
 	int overtime;//超时数 
}Message;

extern void printmessage(Message ,Rider []);

#endif
