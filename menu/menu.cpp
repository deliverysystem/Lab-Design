#include"rider.h"
#include"menu.h"
//#include"message.h"
#include"controller.h"
#include<stdio.h>
#include<stdlib.h>
//�������ֽṹ������ ��controller�ж����� 
//���嶩���ṹ������ 

Menu* creatmenulist(){//��ʼ������ 
	Menu *head;
	head=(Menu*)malloc(sizeof(Menu));
	if(head==NULL){
		printf("�ڴ治����Ӧ��ֹ����"); 
		return head;
	} 
	head->waitlist=NULL;
	return head;
}

void addmenulist(int A,int object){//��Ӷ��� 
	Menu *current=Rider[A].nextmenuptr;
	while(current->nextmenu!=NULL){//�ƶ�ָ��ָ���������һ�� 
		current=current->waitlist;
	}
	current->waitlist=&Menu[object];//�������������� 
	current=current->waitlist;
	current->waitlist=NULL;
}

void buyrider(){//������
	int i;
	if(money>=400){
		for(i=0;rid[i].exist==1;i++){};//�ж���Щ���ִ���
		rid=(Rider*)realloc(rid,(i+2)*sizeof(Rider)); 
		rid[i].exist=1;
		rid[i+1].exist=0;
		if(i==1){//��ʼ��,ʹnextmenuptr��Ϊÿ�����ֶ��������ͷָ�� 
			rid[0].waitptr=creatmenulist();
			rid[i].waitptr=creatmenulist();
		}
		else{ 
			rid[i].waituptr=creatmenulist();
		}
		money=money-300;
	}
}

void allocatemenu(int object){ //���䶩������ 
	int i,mintime,minrider;
	//��·������ȷ��ʱ�� 
	mintime=rid[0].t1;//�˴�Ӧ��Ϊȷ����ʱ�䣬����������� 
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
		printf("%d�����ֽӵ���%d �����%d ��ʱ��%d\n",i,rid[i].receive,rid[i].achieve,rid[i].overtime);
		printf("\n");
	}
}
void destory(){
	int i;
	Menu *tmp,*current;
	for(;rid[i].exist!=0;i++){//�ͷ����ֶ������� 
		current=rid[i].waitptr;
		while(current!=NULL){
			tmp=current;
			current=current->waitlist;
			free(tmp);
		}
	}
}
