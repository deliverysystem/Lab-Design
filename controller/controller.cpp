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
//全局变量： 
int sysclock=1;
int money=1000;
Menu *menu=NULL;
menu=(Menu*)calloc(1,sizeof(Menu));			//订单动态数组 
Rider *rider=NULL;
rider=(Rider*)calloc(2,sizeof(Rider));		//骑手动态数组 
void start()
{
	SetWindowSize(120,80);			//原图为78*51 
	//限定骑手起始位置
	rider[0].exist=1;
	rider[1].exist=0;
	rider[0].A.changeposi(22,38);		//x,y具体待补充 ,rider[i].A.changeposi(x,y);
	int boolnumber=0;				//判断是否破产使用 
	int j=0;			
	int number=0;		//读文件中的序号 
	int size=0;      //控制订单数组的大小 
	int righttime=0;   //判断是否到达接单时刻 
	int value=1;
	Map a;
	a.init();		//绘制地图
	//初始化message
	Message message;
	message.messagemoney=money;
	message.accomplish=0;		//完成数 
	message.overtime=0;			//超时数 
	message.sum=0;				//接单数 
	FILE *fw=fopen("seles.txt","r"); //打开文件 
	for(;value==1;sysclock++){	 			//大循环，控制整个进程 

		//1、判断是否破产 
		boolnumber=bankruptcy(money);	
		if(boolnumber==0)
			break;
		//2、买骑手的函数
		buyrider();														
		//3、读文件并分配订单 
		for(;sysclock==righttime&&(!feof(fw));){			//判断是否到达接单时刻且文件没有读完 
			if(sysclock==1){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);
			}
			if(size!=0){
				menu=(Menu*)realloc(menu,(size+1)*sizeof(Menu));	//将订单数组的大小加一 
				menu[size].x1=0;						//初始化新增加的订单 
				menu[size].y1=0;
				menu[size].x2=0;
				menu[size].y2=0;
				menu[size].p=NULL;
				menu[size].take=0;
				menu[size].finish=0;
				menu[size].underline=0;					
			}
			fscanf(fw,"%d",&menu[size].x1);
			fscanf(fw,"%d",&menu[size].y1);
			fscanf(fw,"%d",&menu[size].x2);
			fscanf(fw,"%d",&menu[size].y2);
			menu[size].endtime=righttime+30;
			//坐标变换
			menu[size].x1=3*menu[size].x1+1;
			menu[size].y1=4.5*menu[size].y1+2;
			menu[size].x2=3*menu[size].x2+1;
			menu[size].y2=4.5*menu[size].y2+2;				
			size++;											
			message.sum+=1;					//接单数+1
			//4、分配订单 
			allocatemenu(size-1);		//size-1为此刻新接订单在订单数组中的下标 
			if(feof(fw)==0){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);	
			}
			if(feof(fw)!=0)
				break;
		}								
		//5、判断是否到达送餐点，判断是否超时,采用遍历订单的方法 
		for(j=0;j<size;j++){				
			if(menu[j].x1==(menu[j].p)->x&&menu[j].y1==(menu[j].p)->y&&menu[j].take==0){ //骑手到达接餐地 
				menu[j].take=1;
			}
			if(menu[j].x2==(menu[j].p)->x&&menu[j].y2==(menu[j].p)->y&&menu[j].take==1){	//骑手到达送餐地 
				if(sysclock-menu[j].endtime>=60){		//破产 
					money=-100;
					boolnumber=bankruptcy();
					if(boolnumber==0)	
						break;
				}
				else if(sysclock-menu[j].endtime>=30){	//超时罚款50,超时数+1 
					money-=50;
					message.overtime+=1;
					menu[j].finish=1;
					menu[j].p->unfinishednum+=1;
			 		deletelist(j);
				}
				else{						//送餐成功，钱数加10,完成数+1 
					money+=10;
					message.accomplish+=1;
					menu[j].finish=1;
					menu[j].p->finishednum+=1;
					deletelist(j);
				} 	
			} 
		}
		if(boolnumber==0)
			break;
		//6、对骑手进行移动
		printmove();
		//7、打印当前信息 
		printmessage(message);
		//8、如果所有订单完成，跳出循环
		for(j=0;j<size;j++){
			if(menu[j].finish==0)
			 	break;
		}
		if(j==size)
			break; 			//订单数组中的所有订单都完成了，跳出循环。	
		sleep(1000); 
	}
	fclose(fw);			//关闭文件
	SetWindowSize(75,0);	
}
  
int bankruptcy(int money)   //判断当前是否破产 
{
	int i;
	if(money<0){
		SetCursorPosition(58,0);
		performance();		
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
		m=rider[i].Path->header->next->x;				//rider[i]的行驶路线中的下个一点，读出它的坐标 
		n=rider[i].Path->header->next->y;
	*	ListNode* temp=rider[i].Path->header->next;					//删除第一个节点 
		rider[i].Path->header=rider[i].Path->header->next->next;
		rider[i].Path->header->pred=rider[i].Path->header;			
		free(temp);															
		a.changeposi(rider[i].x,rider[i].y);
		a.clear();         				//清除骑手原位置 
		a.changeposi(m,n);
		a.PrintRider();  				//打印骑手图案函数
		rider[i].A.changeposi(m,n);
	}
}
