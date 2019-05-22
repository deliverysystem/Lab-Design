#include"rider.h"
#include"menu.h"
#include"controller.h"
#include<stdio.h>
#include<stdlib.h> 

struct menu* creatmenulist(){//初始化链表 
	struct menu *head;
	head=(struct menu*)malloc(sizeof(struct menu));
	if(head==NULL){
		printf("内存不够，应终止程序"); 
		return head;
	} 
	head->nextmenu=NULL;
	return head;
}

void addmenulist(int A,int object){//添加订单 
	struct menu *current=rider[A].waitlist;
	while(current->nextmenu!=NULL){//移动指针指向链表最后一个 
		current=current->nextmenu;
	}
	current->nextmenu=&Menu[object];//将订单加入链表
	rider[A].receive++;
	current=current->nextmenu;
	current->nextmenu=(struct menu*)malloc(sizeof(struct menu));//开创新的空间 
	current->nextmenu=NULL;
}

void buyrider(){//买骑手
	int i;
	while(money>=350){//大于400是为了留一段缓冲，防止买完骑手没钱导致破产 
		for(i=0;rider[i].exist==1;i++){};//判断哪些骑手存在
		rider[i].exist=1;
		rider[i+1].exist=0;
		if(i==1){//初始化,使nextmenuptr成为每个骑手订单链表的头指针 
			rider[0].waitlist=creatmenulist();
			rider[0].Path.init();
			rider[i].waitlist=creatmenulist();
			rider[1].Path.init();
			rider[i].receive =0;
			rider[i].achieve=0;
			rider[i].overtime=0;
			rider[i].x=15;
			rider[i].y=34;
		}
		else{ 
			rider[i].waitlist=creatmenulist();
			rider[i].Path.init();
			rider[i].receive =0;
			rider[i].achieve=0;
			rider[i].overtime=0;
			rider[i].x=15;
			rider[i].y=34;
		}
		money=money-300;
	}
}

void allocatemenu(int object){ //分配订单函数 
	int i,sumrider=0;
	for(i=0;rider[i].exist!=0;i++){//判断有多少骑手 
		sumrider++;
	}
	int time[sumrider];//每个骑手的时间 
	for(i=0;rider[i].exist!=0;i++){
		time[i]=rider[i].CalculatePath(&Menu[object]); 
	}
	int mintime,minrider;
	mintime=time[0];
	minrider=0;
	for(i=0;rider[i].exist!=0;i++){
		if(time[i]<mintime){
			mintime=time[i];
			minrider=i;
		}
	}
	Menu[object].p=&rider[minrider];//明确订单被分配到那个骑手 
	rider[minrider].Path=rider[minrider].OldPath;
	Menu[object].underline=minrider; 
	addmenulist(minrider,object);//加入到骑手订单列表中 
	rider[minrider].AddTOWaitlist(&Menu[object]);//加入到路径列表中 
}

void performance(){
	int i;
	for(i=0;rider[i].exist!=0;i++){
		printf("%d号骑手接单数%d 完成数%d 超时数%d\n",i,rider[i].receive,rider[i].achieve,rider[i].overtime);

	}
}

void deletelist(int menunum){//订单送到时删除该订单 
	struct menu *tmp,*current,*previous;
	current=rider[Menu[menunum].underline].waitlist; 
//	for(;*current!=menu[menunum];current=current->nextmenu){//寻找到要删除的订单 
//		previous=current;
//	}
	tmp=current;
	current=current->nextmenu;
	previous->nextmenu=current;
	free(tmp);
}

struct menu* The_ith(Rider *A,int i){////返回骑手订单列表第几个订单 
	struct menu *current=A->waitlist;
//	current=current->nextmenu;
	int num;
	for(num=1;current!=NULL&&num<=i;current=current->nextmenu,num++){}
	num -=1;
	if(num==i)
		return current;
	else if(i==0)
		return A->waitlist;
	else
		return NULL;
}

void destory(){//破产时调用？ 
	int i;
	struct menu *tmp,*current;
	for(;rider[i].exist!=0;i++){//释放骑手订单链表 
		current=rider[i].waitlist;
		while(current!=NULL){
			tmp=current;
			current=current->nextmenu;
			free(tmp);
		}
	}
}
