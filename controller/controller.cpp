#include<stdio.h>
#include"controller.h"
#include"point.h"
#include"tools.h"
#include"message.h"
#include"rider.h"
#include"map.h"
#include"Menu.h" 
#include<stdlib.h>
#include <windows.h>
//ȫ�ֱ����� 
int sysclock=1;
int money=1000;
Menu *menu=NULL;
menu=(Menu*)calloc(1,sizeof(Menu));			//������̬���� 
Rider *rider=NULL;
rider=(Rider*)calloc(2,sizeof(Rider));		//���ֶ�̬���� 
void start()
{
	SetWindowSize(78,51);
	//�޶�������ʼλ��
	rider[0].exist=1;
	rider[1].exist=0;
	rider[0].A.changeposi(22,38);			//x,y��������� 			rider[i].A.changeposi(x,y);
	int boolnumber=0;			//�ж��Ƿ��Ʋ�ʹ�� 
	int j=0;			
	int number=0;		//���ļ��е���� 
	int size=0;      //���ƶ�������Ĵ�С 
	int righttime=0;   //�ж��Ƿ񵽴�ӵ�ʱ�� 
	int value=1;
	Map a;
	a.init();		//���Ƶ�ͼ
	//��ʼ��message
	Message message;
	message.messagemoney=money;
	message.accomplish=0;		//����� 
	message.overtime=0;			//��ʱ�� 
	message.sum=0;				//�ӵ��� 
	FILE *fw=fopen("seles.txt","r"); //���ļ� 
	for(;value==1;sysclock++){	 			//��ѭ���������������� 

		//1���ж��Ƿ��Ʋ� 
		boolnumber=bankruptcy(money);	
		if(boolnumber==0)
			break;
		//2�������ֵĺ���
		buyrider();														
		//3�����ļ������䶩�� 
		for(;sysclock==righttime&&(!feof(fw));){			//�ж��Ƿ񵽴�ӵ�ʱ�����ļ�û�ж��� 
			if(sysclock==1){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);
			}
			if(size!=0){
				menu=(Menu*)realloc(menu,(size+1)*sizeof(Menu));	//����������Ĵ�С��һ 
				menu[size].x1=0;						//��ʼ�������ӵĶ��� 
				menu[size].y1=0;
				menu[size].x2=0;
				menu[size].y2=0;
				menu[size].p=NULL;
				menu[size].take=0;
				menu[size].finish=0;					
			}
			fscanf(fw,"%d",&menu[size].x1);
			fscanf(fw,"%d",&menu[size].y1);
			fscanf(fw,"%d",&menu[size].x2);
			fscanf(fw,"%d",&menu[size].y2);
			menu[size].endtime=righttime+30;				
			size++;											
			message.sum+=1;					//�ӵ���+1
			//4�����䶩�� 
			allocatemenu(size-1);		//size-1Ϊ�˿��½Ӷ����ڶ��������е��±� 
			if(feof(fw)==0){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);	
			}
			if(feof(fw)!=0)
				break;
		}								
		//5���ж��Ƿ񵽴��Ͳ͵㣬�ж��Ƿ�ʱ,���ñ��������ķ��� 
		for(j=0;j<size;j++){				
			if(menu[j].x1==(menu[j].p)->x&&menu[j].y1==(menu[j].p)->y&&menu[j].take==0){ //���ֵ���Ӳ͵� 
				menu[j].take=1;
			}
			if(menu[j].x2==(menu[j].p)->x&&menu[j].y2==(menu[j].p)->y&&menu[j].take==1){	//���ֵ����Ͳ͵� 
				if(sysclock-menu[j].endtime>=60){		//�Ʋ� 
					money=-100;
					boolnumber=bankruptcy();
					if(boolnumber==0)	
						break;
				}
				else if(sysclock-menu[j].endtime>=30){	//��ʱ����50,��ʱ��+1 
					money-=50;
					message.overtime+=1;
					menu[j].finish=1;
					menu[j].p->unfinishednum+=1;
			 		deletelist(menu[j].p);
				}
				else{						//�Ͳͳɹ���Ǯ����10,�����+1 
					money+=10;
					message.accomplish+=1;
					menu[j].finish=1;
					menu[j].p->finishednum+=1;
					deletelist(menu[j].p);
				} 	
			} 
		}
		if(boolnumber==0)
			break;
		//6�����㲢�޸Ľӵ����ֵ���ʻ·��
		for(j=0;rider[j].exist==1;j++)
			rider[j].CalculatePath();
		//7�������ֽ����ƶ�
		printmove();
		//8����ӡ��ǰ��Ϣ 
		printmessage(message);
		//9��������ж�����ɣ�����ѭ��
		for(j=0;j<size;j++){
			if(menu[j].finish==0)
			 	break;
		}
		if(j==size)
			break; //���������е����ж���������ˣ�����ѭ����	
		sleep(1000); 
	}
	fclose(fw);			//�ر��ļ�	
}
  
  
  
  
  
  
int bankruptcy(int money)   //�жϵ�ǰ�Ƿ��Ʋ� 
{
	int i;
	if(money<0){
		for(i=0;rider[i].exist==1;i++){
			rider[i].printstate();
			return 0;
		}
	}
	else
		return 1;
}
void printmove(){
	int i;
	int m;
	int n;
	point a; 
	for(i=0;rider[i].exist==1;i++){
		m=rider[i].Path->header->next->x;				//rider[i]����ʻ·���е��¸�һ�㣬������������ 
		n=rider[i].Path->header->next->y;
		ListNode* temp=rider[i].Path->header->next;					//ɾ����һ���ڵ� 
		rider[i].Path->header=rider[i].Path->header->next->next;
		rider[i].Path->header->pred=rider[i].Path->header;			
		free(temp);															
		a.changeposi(rider[i].x,rider[i].y);
		a.clear();         				//�������ԭλ�� 
		a.changeposi(m,n);
		a.PrintCanteen();  				//��ӡ����ͼ������
		rider[i].A.changeposi(m,n);
	}
}
��Ҫ���ǵ����⣺
�������ѭ�����ж����ֵĶ��������Ƿ�Ϊ�գ�����������ʣ�����ע��ÿ���һ��������ֶ��������ɾ���� 
����ϸ�ڣ�
�и����⣺

�����Ͳ͵��Ժ���Ҫ��������������
���������Ƿ���Ӹ��ö����Ƿ������״̬�� 
1���������鳤�ȵ����⡣ 
2�������нṹ��ӱ��������⡣ 
3�������Ǻű�������⡣ 



�������鳤�ȡ� 
rider.h�ļ����Ƿ��һ���ı�������x,y�ĺ����� 
