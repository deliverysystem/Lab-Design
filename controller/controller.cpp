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
//全局变量： 
int sysclock=0;
int money=1000;
struct menu Menu[301]={0};	//订单动态数组 
Rider rider[100];		//骑手动态数组 
int Graph[100][100];
void start()
{
	SetWindowSize(140,120);			//原图为78*51 
	//限定骑手起始位置
	rider[0].receive =0;
	rider[0].achieve=0;
	rider[0].overtime=0;
	rider[0].x=15;
	rider[0].y=34;
	rider[0].exist=1;
	rider[1].exist=0;		//x,y具体待补充 ,rider[i].A.changeposi(x,y);
	int boolnumber=0;				//判断是否破产使用 
	int j=0;			
	int number=0;		//读文件中的序号 
	int size=0;      //控制订单数组的大小 
	int righttime=0;   //判断是否到达接单时刻 
	int value=1;
	int state=0;	//记录是否接完了所有单 
	Map a;
	a.init();		//绘制地图
	//初始化message
	SetCursorPosition(40,0); 
	struct message Message;
	Message.messagemoney=money;
	Message.accomplish=0;		//完成数 
	Message.totalovertime=0;			//超时数 
	Message.sum=0;				//接单数
	FILE *fp=fopen("outputs.txt","w");						//输出文件 
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
			if(sysclock==0){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);
				break;										//此处改动 
			} 
			if(size!=0){
				Menu[size].x1=0;						//初始化新增加的订单 
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
			//坐标变换
			Menu[size].x1=2*Menu[size].x1+1;
			Menu[size].y1=4*Menu[size].y1+2;
			Menu[size].x2=2*Menu[size].x2+1;
			Menu[size].y2=4*Menu[size].y2+2;				
			size++;											
			Message.sum+=1;					//接单数+1
			//4、分配订单 
			allocatemenu(size-1);		//size-1为此刻新接订单在订单数组中的下标 
			if(feof(fw)==0){
				fscanf(fw,"%d",&number);
				fscanf(fw,"%d",&righttime);	
			}
			if(feof(fw)!=0){
				state=1; 
				break;
			}
		}								
		//5、判断是否到达送餐点，判断是否超时,采用遍历订单的方法 
		for(j=0;j<size;j++){				
			if(((Menu[j].x1-2)==(Menu[j].p)->x&&Menu[j].y1==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1+4)==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1-4)==(Menu[j].p)->y)||((Menu[j].x1+2)==(Menu[j].p)->x&&(Menu[j].y1)==(Menu[j].p)->y)&&Menu[j].get==0){ //骑手到达接餐地 
				Menu[j].trueget=1;
			}
			if(((Menu[j].x2-2)==(Menu[j].p)->x&&Menu[j].y2==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2+4)==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2-4)==(Menu[j].p)->y)||((Menu[j].x2+2)==(Menu[j].p)->x&&(Menu[j].y2)==(Menu[j].p)->y)&&Menu[j].get==1){	//骑手到达送餐地 
				if(sysclock-Menu[j].endtime>=60){		//破产 
					money=-100;
					boolnumber=bankruptcy(money);
					if(boolnumber==0)	
						break;
				}
				else if(sysclock-Menu[j].endtime>=30){	//超时罚款50,超时数+1 
					money-=50;
					Message.totalovertime+=1;
					Menu[j].truereach=1;
					Menu[j].p->overtime+=1;
			 		deletelist(j);
				}
				else{						//送餐成功，钱数加10,完成数+1 
					money+=10;
					Message.accomplish+=1;
					Menu[j].truereach=1;
					Menu[j].p->achieve+=1;
					deletelist(j);
				} 	
			} 
		}
		if(boolnumber==0)
			break;
		//6、对骑手进行移动 
		if(size!=0)								//此处改动 
			printmove();
		else{
			point a(15,34);
			a.PrintRider();
		}	
		//7、打印当前信息 
		printmessage(Message);
		//8、将当前信息输入到文件中
		fprintf(fp,"当前时刻：%d\n",sysclock);
		for(j=0;rider[j].exist==1;j++){
			fprintf(fp,"骑手%d的位置:(%d,%d)\n",j+1,(rider[j].x-1)/2,(rider[j].y-2)/4);//2*rider[i].x+1,4*rider[i].y+2
		} 
		fprintf(fp,"接单数：%d\n",Message.sum);
		fprintf(fp,"完成数：%d\n",Message.accomplish);
		fprintf(fp,"超时数：%d\n",Message.totalovertime);
		//9、如果所有订单完成，跳出循环
		for(j=0;j<size;j++){
			if(Menu[j].reach==0)
			 	break;
		}
		if(j==size&&state==1)
			break; 			//订单数组中的所有订单都完成了，跳出循环。	
		Sleep(1200); 
	}
	fclose(fw);				//关闭文件
	fclose(fp);
	SetCursorPosition(40,0);	
}
  
int bankruptcy(int money)   //判断当前是否破产 
{
	int i;
	if(money<0){
		SetCursorPosition(40,0);
		performance();		
		return 0;
	}
	else
		return 1;
}


void printmove()
{
	int i;
	int m;
	int n;
	point a; 
	for(i=0;rider[i].exist==1;i++){
		if(rider[i].Path.header->next!=rider[i].Path.tailer){
			m=rider[i].Path.header->next->x;				//rider[i]的行驶路线中的下个一点，读出它的坐标 
			n=rider[i].Path.header->next->y;
			ListNode* temp=rider[i].Path.header->next;					//删除第一个节点 
			rider[i].Path.header->next=rider[i].Path.header->next->next;
			rider[i].Path.header->next->pred=rider[i].Path.header;			
			free(temp);															
			a.changeposi(rider[i].x,rider[i].y);
			a.clear();         				//清除骑手原位置 
			a.changeposi(m,n);
			a.PrintRider();  				//打印骑手图案函数
			rider[i].changeposi(m,n);
		}
		else{								//若骑手当前路径链表里只有一个节点 
			a.x=rider[i].x;
			a.y=rider[i].y;
			a.PrintRider();
		}
	}	
}
