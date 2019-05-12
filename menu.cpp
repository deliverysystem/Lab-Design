#include"rider.h"
#include"menu.h"
//#include"message.h"
#include"controller.h"
#include<stdio.h>
#include<stdlib.h>
//定义骑手结构体数组 在controller中定义了 
//定义订单结构体数组 

Menu* creatmenulist(){//初始化链表 
	Menu *head;
	head=(Menu*)malloc(sizeof(Menu));
	if(head==NULL){
		printf("内存不够，应终止程序"); 
		return head;
	} 
	head->nextmenu=NULL;
	return head;
}

void addmenulist(int A,int object){//添加订单 
	Menu *current=Rider[A].nextmenuptr;
	while(current->nextmenu!=NULL){//移动指针指向链表最后一个 
		current=current->nextmenu;
	}
	current->nextmenu=&Menu[object];//将订单加入链表 
	current=current->nextmenu;
	current->nextmenu=NULL;
}

void buyrider(){//买骑手
	int i;
	if(money>=400){
		for(i=0;rid[i].exist==1;i++){};//判断哪些骑手存在
		rid=(Rider*)realloc(rid,(i+2)*sizeof(Rider)); 
		rid[i].exist=1;
		rid[i+1].exist=0;
		if(i==1){//初始化,使nextmenuptr成为每个骑手订单链表的头指针 
			rid[0].nextmenuptr=creatmenulist();
			rid[i].nextmenuptr=creatmenulist();
		}
		else{ 
			rid[i].nextmenuptr=creatmenulist();
		}
		money=money-300;
	}
}

void allocatemenu(int object){ //分配订单函数 
	int i,mintime,minrider;
	//用路径函数确定时间 
	mintime=rid[0].t1;//此处应该为确定的时间，暂用这个代替 
	minrider=0;
	for(i=0;rid[i].exist!=0;i++){
		if(rid[i].t1<mintime){
		 	mintime=rid[i].t1;
		 	minrider=i;
		}
	}	
	addmenulist(minrider,object);
}

void performance(){
	int i;
	for(i=0;rid[i].exist!=0;i++){
		printf("%d号骑手接单数%d 完成数%d 超时数%d\n",i,rid[i].receive,rid[i].achieve,rid[i].overtime);
		printf("\n");
	}
}
void destory(){
	int i;
	Menu *tmp,*current;
	for(;rid[i].exist!=0;i++){//释放骑手订单链表 
		current=rid[i].nextmenuptr;
		while(current!=NULL){
			tmp=current;
			current=current->nextmenu;
			free(tmp);
		}
	}
}
