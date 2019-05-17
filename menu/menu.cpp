#include"rider.h"
#include"menu.h"
#include"controller.h"
#include<stdio.h>
#include<stdlib.h> 

struct menu* creatmenulist(){//��ʼ������ 
	struct menu *head;
	head=(struct menu*)malloc(sizeof(struct menu));
	if(head==NULL){
		printf("�ڴ治����Ӧ��ֹ����"); 
		return head;
	} 
	head->nextmenu=NULL;
	return head;
}

void addmenulist(int A,int object){//��Ӷ��� 
	struct menu *current=rider[A].waitlist;
	while(current->nextmenu!=NULL){//�ƶ�ָ��ָ���������һ�� 
		current=current->nextmenu;
	}
	current->nextmenu=&Menu[object];//��������������
	current=current->nextmenu;
	current->nextmenu=(struct menu*)malloc(sizeof(struct menu));//�����µĿռ� 
	current->nextmenu=NULL;
}

void buyrider(){//������
	int i;
	while(money>=350){//����400��Ϊ����һ�λ��壬��ֹ��������ûǮ�����Ʋ� 
		for(i=0;rider[i].exist==1;i++){};//�ж���Щ���ִ���
		rider=(Rider*)realloc(rider,(i+2)*sizeof(Rider)); 
		rider[i].exist=1;
		rider[i+1].exist=0;
		if(i==1){//��ʼ��,ʹnextmenuptr��Ϊÿ�����ֶ��������ͷָ�� 
			rider[0].waitlist=creatmenulist();
			rider[i].waitlist=creatmenulist();
		}
		else{ 
			rider[i].waitlist=creatmenulist();
		}
		money=money-300;
	}
}

void allocatemenu(int object){ //���䶩������ 
	int i,sumrider=0;
	for(i=0;rider[i].exist!=0;i++){//�ж��ж������� 
		sumrider++;
	}
	int time[sumrider];//ÿ�����ֵ�ʱ�� 
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
	Menu[object].p=&rider[minrider];//��ȷ���������䵽�Ǹ����� 
	Menu[object].underline=minrider; 
	addmenulist(minrider,object);//���뵽���ֶ����б��� 
	rider[minrider].AddTOWaitlist(&Menu[object]);//���뵽·���б��� 
}

void performance(){
	int i;
	for(i=0;rider[i].exist!=0;i++){
		printf("%d�����ֽӵ���%d �����%d ��ʱ��%d\n",i,rider[i].receive,rider[i].achieve,rider[i].overtime);

	}
}

void deletelist(int menunum){//�����͵�ʱɾ���ö��� 
	struct menu *tmp,*current,*previous;
	current=rider[Menu[menunum].underline].waitlist; 
//	for(;*current!=menu[menunum];current=current->nextmenu){//Ѱ�ҵ�Ҫɾ���Ķ��� 
//		previous=current;
//	}
	tmp=current;
	current=current->nextmenu;
	previous->nextmenu=current;
	free(tmp);
}

struct menu* The_ith(Rider *A,int i){////�������ֶ����б�ڼ������� 
	struct menu *current=A->waitlist;
	current=current->nextmenu;
	int num;
	for(num=1;current!=NULL&&num<=i;current=current->nextmenu,num++){}
	if(num==i)
		return current;
	else
		return NULL;
}

void destory(){//�Ʋ�ʱ���ã� 
	int i;
	struct menu *tmp,*current;
	for(;rider[i].exist!=0;i++){//�ͷ����ֶ������� 
		current=rider[i].waitlist;
		while(current!=NULL){
			tmp=current;
			current=current->nextmenu;
			free(tmp);
		}
	}
}
