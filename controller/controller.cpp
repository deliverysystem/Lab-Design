#include<stdio.h>
#include"controller.h"
#include"point.h"
#include"tools.h"
#include"message.h"
#include"rider.h"
#include"map.h"
#include"menu.h" 
#include<stdlib.h>
#include <windows.h>
//ȫ�ֱ����� 
int sysclock=1;
int money=1000;
struct menu *Menu=(struct menu*)calloc(1,sizeof(struct menu));	//������̬���� 
Rider *rider=(Rider*)calloc(2,sizeof(Rider));	//���ֶ�̬���� 
void start()
{
	SetWindowSize(120,80);			//ԭͼΪ78*51 
	//�޶�������ʼλ��
	rider[0].exist=1;
	rider[1].exist=0;
	rider[0].changeposi(22,38);		//x,y��������� ,rider[i].A.changeposi(x,y);
	int boolnumber=0;				//�ж��Ƿ��Ʋ�ʹ�� 
	int j=0;			
	int number=0;		//���ļ��е���� 
	int size=0;      //���ƶ�������Ĵ�С 
	int righttime=0;   //�ж��Ƿ񵽴�ӵ�ʱ�� 
	int value=1;
	Map a;
	a.init();		//���Ƶ�ͼ
	//��ʼ��message
	struct message Message;
	Message.messagemoney=money;
	Message.accomplish=0;		//����� 
	Message.totalovertime=0;			//��ʱ�� 
	Message.sum=0;				//�ӵ��� 
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
				Menu=(struct menu*)realloc(Menu,(size+1)*sizeof(struct menu));	//����������Ĵ�С��һ 
				Menu[size].x1=0;						//��ʼ�������ӵĶ��� 
				Menu[size].y1=0;
				Menu[size].x2=0;
				Menu[size].y2=0;
				Menu[size].p=NULL;
				Menu[size].get=0;
				Menu[size].reach=0;
				Menu[size].underline=0;					
			}
			fscanf(fw,"%d",&Menu[size].x1);
			fscanf(fw,"%d",&Menu[size].y1);
			fscanf(fw,"%d",&Menu[size].x2);
			fscanf(fw,"%d",&Menu[size].y2);
			Menu[size].endtime=righttime+30;
			//����任
			Menu[size].x1=3*Menu[size].x1+1;
			Menu[size].y1=4.5*Menu[size].y1+2;
			Menu[size].x2=3*Menu[size].x2+1;
			Menu[size].y2=4.5*Menu[size].y2+2;				
			size++;											
			Message.sum+=1;					//�ӵ���+1
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
			if(((Menu[j].x1-3)==(Menu[j].p)->x&&Menu[j].y1==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1+5)==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1-4)==(Menu[j].p)->y)||((Menu[j].x1+3)==(Menu[j].p)->x&&(Menu[j].y1)==(Menu[j].p)->y)&&Menu[j].get==0){ //���ֵ���Ӳ͵� 
				Menu[j].get=1;
			}
			if(((Menu[j].x2-3)==(Menu[j].p)->x&&Menu[j].y2==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2+5)==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2-4)==(Menu[j].p)->y)||((Menu[j].x2+3)==(Menu[j].p)->x&&(Menu[j].y2)==(Menu[j].p)->y)&&Menu[j].get==1){	//���ֵ����Ͳ͵� 
				if(sysclock-Menu[j].endtime>=60){		//�Ʋ� 
					money=-100;
					boolnumber=bankruptcy(money);
					if(boolnumber==0)	
						break;
				}
				else if(sysclock-Menu[j].endtime>=30){	//��ʱ����50,��ʱ��+1 
					money-=50;
					Message.totalovertime+=1;
					Menu[j].reach=1;
					Menu[j].p->overtime+=1;
			 		deletelist(j);
				}
				else{						//�Ͳͳɹ���Ǯ����10,�����+1 
					money+=10;
					Message.accomplish+=1;
					Menu[j].reach=1;
					Menu[j].p->achieve+=1;
					deletelist(j);
				} 	
			} 
		}
		if(boolnumber==0)
			break;
		//6�������ֽ����ƶ�
		printmove();
		//7����ӡ��ǰ��Ϣ 
		printmessage(Message);
		//8��������ж�����ɣ�����ѭ��
		for(j=0;j<size;j++){
			if(Menu[j].reach==0)
			 	break;
		}
		if(j==size)
			break; 			//���������е����ж���������ˣ�����ѭ����	
		Sleep(1000); 
	}
	fclose(fw);			//�ر��ļ�
	SetWindowSize(75,0);	
}
  
int bankruptcy(int money)   //�жϵ�ǰ�Ƿ��Ʋ� 
{
	int i;
	if(money<0){
		SetCursorPosition(58,0);
		performance();		
		return 0;
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
		m=rider[i].Path.header->next->x;				//rider[i]����ʻ·���е��¸�һ�㣬������������ 
		n=rider[i].Path.header->next->y;
		ListNode* temp=rider[i].Path.header->next;					//ɾ����һ���ڵ� 
		rider[i].Path.header=rider[i].Path.header->next->next;
		rider[i].Path.header->pred=rider[i].Path.header;			
		free(temp);															
		a.changeposi(rider[i].x,rider[i].y);
		a.clear();         				//�������ԭλ�� 
		a.changeposi(m,n);
		a.PrintRider();  				//��ӡ����ͼ������
		rider[i].changeposi(m,n);
	}
}
