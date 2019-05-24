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
int money=700;
struct menu Menu[301]={0};	//订单动态数组 
Rider rider[100];		//骑手动态数组 
int Graph[100][100];
struct stop{
			int ridern;
			int name;
			int x;
			int y;
			int flag;
			int iscan;
		};
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
	int p=0;
	int q=0;
	int o=0;
	int i=0;
	//初始化message
	SetCursorPosition(9,82);
	SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED);
	printf("KFC：餐厅");
	SetCursorPosition(14,82); 
	SetColor(FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	printf("BYR：食客"); 
	SetColor(FOREGROUND_INTENSITY);
	struct message Message;
	Message.messagemoney=money;
	Message.accomplish=0;		//完成数 
	Message.totalovertime=0;			//超时数 
	Message.sum=0;				//接单数
	FILE *fp=fopen("outputs.txt","w");						//输出文件 
	FILE *fw=fopen("seles.txt","r"); //打开文件 
	for(;value==1;sysclock++){	 			//大循环，控制整个进程 
		int rightnowfinish[300]={0};
		int rightnowticket[300]={0};
		struct stop Stop[310]={0};
		Stop[0].ridern=-1;
		Stop[1].ridern=-1;
		p=0;
		q=0;
		o=0;
		for(j=0;j<size;j++){
			if(Menu[j].truereach!=1&&sysclock-Menu[j].endtime>=30){		//破产 
				money=-100;
				if(money<0)					
					break;
			}
			else if(Menu[j].trueovertime==0&&Menu[j].truereach!=1&&sysclock-Menu[j].endtime>=0){	//超时罚款50,超时数+1 
					money-=50;
					Message.totalovertime+=1;
					Menu[j].p->overtime+=1;
					Menu[j].trueovertime=1;
					rightnowticket[q]=j+1;
					q++;
			}
		}
		//1、判断是否破产 
		boolnumber=bankruptcy(money);	
		if(boolnumber==0)
			break;
		//2、买骑手的函数
		buyrider();														
		//3、读文件并分配订单 
		for(;sysclock==(righttime+1)&&(!feof(fw));){			//判断是否到达接单时刻且文件没有读完 
			if(sysclock==1){
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
				Menu[size].truereach=0;
				Menu[size].trueget=0;
				Menu[size].trueovertime=0;					
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
			SetCursorPosition(Menu[size].x1,Menu[size].y1-1);
			SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED);
			printf("KFC");
			SetCursorPosition(Menu[size].x2,Menu[size].y2-1); 
			SetColor(FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			printf("BYR");
			SetColor(FOREGROUND_INTENSITY);			
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
			if((((Menu[j].x1-2)==(Menu[j].p)->x&&Menu[j].y1==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1+4)==(Menu[j].p)->y)||(Menu[j].x1==(Menu[j].p)->x&&(Menu[j].y1-4)==(Menu[j].p)->y)||((Menu[j].x1+2)==(Menu[j].p)->x&&(Menu[j].y1)==(Menu[j].p)->y))&&(Menu[j].trueget==0)){ //骑手到达接餐地 
				Menu[j].trueget=1;
				Stop[o].flag=1; 
				Stop[o].x=Menu[j].x1;
				Stop[o].y=Menu[j].y1;
				Stop[o].name=1; //1是餐馆 
				Stop[o].ridern = Menu[j].underline;
				Stop[o].iscan =1;
				o++; 
				SetCursorPosition(Menu[j].x1,Menu[j].y1-1);
				printf("   ");
			}
			if((((Menu[j].x2-2)==(Menu[j].p)->x&&Menu[j].y2==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2+4)==(Menu[j].p)->y)||(Menu[j].x2==(Menu[j].p)->x&&(Menu[j].y2-4)==(Menu[j].p)->y)||((Menu[j].x2+2)==(Menu[j].p)->x&&(Menu[j].y2)==(Menu[j].p)->y))&&(Menu[j].trueget==1)&&(Menu[j].truereach!=1))	//骑手到达送餐地 
			{						//送餐成功，钱数加10,完成数+1 
				if(Menu[j].trueovertime==0){
					
					money+=10;
				}
				if(o>=1){
						if(Stop[o-1].x==Stop[o].x&&Stop[o-1].y==Stop[o].y)//如果stop中前一个的坐标与餐馆坐标相等，则是餐客 
							Stop[o-1].name=3; //3是餐客
						else{
							Stop[o].ridern = Menu[j].underline;
							Stop[o].flag = 1;
							Stop[o].x=Menu[j].x2;
							Stop[o].y=Menu[j].y2;
							Stop[o].name=2; //2是食客
							o++;
						} 
				}
				else{
					Stop[o].ridern = Menu[j].underline;
					Stop[o].flag = 1;
					Stop[o].x=Menu[j].x2;
					Stop[o].y=Menu[j].y2;
					Stop[o].name=2; //2是食客
					o++;
				} 
				SetCursorPosition(Menu[j].x2,Menu[j].y2-1);
				printf("   ");
				Message.accomplish+=1;
				Menu[j].truereach=1;
				Menu[j].p->achieve+=1;
				rightnowfinish[p]=j+1;
				p++;
				deletelist(j);
			} 
		}
		//6、防止消除其他单的餐客
		for(j=0;j<size;j++)
		{
			if(Menu[j].trueget!=1){
				SetCursorPosition(Menu[j].x1,Menu[j].y1-1);
				SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED);
				printf("KFC");
			}
			if(Menu[j].truereach!=1){
				SetCursorPosition(Menu[j].x2,Menu[j].y2-1);
				SetColor(FOREGROUND_INTENSITY|FOREGROUND_BLUE);
				printf("BYR");
			}
		} 
		SetColor(FOREGROUND_INTENSITY);
		//7、将信息输入到文件中
		fprintf(fp,"时间：%d\n",sysclock);
		fprintf(fp,"钱：%d\n",money);
		fprintf(fp,"接单数：%d\n",Message.sum);
		fprintf(fp,"完成数：%d;结单：",Message.accomplish);
		for(i=0;rightnowfinish[i]!=0;i++){
			if(rightnowfinish[i+1]==0){
				fprintf(fp,"%d ",rightnowfinish[i]);
				fprintf(fp," ");
			}
			else{
				fprintf(fp,"%d ",rightnowfinish[i]);
				fprintf(fp," ");
			}
		}
		fprintf(fp,";\n");
		fprintf(fp,"超时数：%d;罚单: ",Message.totalovertime);
		for(i=0;rightnowticket[i]!=0;i++){
			if(rightnowticket[i+1]==0){
				fprintf(fp,"%d",rightnowticket[i]);
				fprintf(fp," ");
			}
			else{
				fprintf(fp,"%d ",rightnowticket[i]);
				fprintf(fp," ");
			}
		}
		fprintf(fp,";\n");
		for(j=0;rider[j].exist==1;j++){
			fprintf(fp,"骑手%d的位置: %d, %d; 停靠:",j+1,(rider[j].x-1)/2,(rider[j].y-2)/4);//2*rider[i].x+1,4*rider[i].y+2
		for(i=0;Stop[i].flag!=0;i++){
			if(Stop[i].ridern==j){
				if(Stop[i].name==1)
				fprintf(fp,"餐馆 "); 
			else if(Stop[i].name==2)
				fprintf(fp,"食客 "); 
			else
				fprintf(fp,"餐客 ");
			fprintf(fp,"%d %d ",(Stop[i].x-1)/2,(Stop[i].y-2)/4);
				}
			}
			fprintf(fp,";\n");
		} 	
		//8、对骑手进行移动 
		if(size!=0)								//此处改动 
			printmove();
		else{
			SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
			point a(15,34);
			a.PrintRider();
			SetColor(FOREGROUND_INTENSITY);
		} 
		//9、打印当前信息 
		printmessage(Message);
		//10、如果所有订单完成，跳出循环
		for(j=0;j<size;j++){
			if(Menu[j].truereach==0)
			 	break;
		}
		if(j==size&&state==1)
			break; 			//订单数组中的所有订单都完成了，跳出循环。	
		Sleep(1000); 
	}
	fclose(fw);				//关闭文件
	fclose(fp);
	SetCursorPosition(40,0);	
}
  
int bankruptcy(int money)   //判断当前是否破产 
{
	int i;
	if(money<0){
		SetCursorPosition(34,0);
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
			a.changeposi(rider[i].x,rider[i].y);
			a.clear();
			m=rider[i].Path.header->next->x;				//rider[i]的行驶路线中的下个一点，读出它的坐标 
			n=rider[i].Path.header->next->y;
			ListNode* temp=rider[i].Path.header->next;					//删除第一个节点 
			rider[i].Path.header->next=rider[i].Path.header->next->next;
			rider[i].Path.header->next->pred=rider[i].Path.header;		
			rider[i].Path._size--;	
			free(temp);
			rider[i].changeposi(m,n);
		}
	}
	for(i=0;rider[i].exist==1;i++)
	{
		SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
		a.changeposi(rider[i].x,rider[i].y);
		a.PrintRider();
		SetColor(FOREGROUND_INTENSITY);
	}
}
