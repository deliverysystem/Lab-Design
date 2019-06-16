#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <graphics.h>
#include <process.h> 

#include"controller.h"
#include"point.h"
#include"tools.h"
#include"message.h"
#include"rider.h"
#include"map.h"
#include"menu.h" 
#include"cartoon.h"
//全局变量： 
HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
int sysclock=0;
int money=700;
struct menu Menu[301]={0};	//订单动态数组 
Rider rider[100];		//骑手动态数组 
int Graph[100][100];
int size=0;				//订单数量，新增的全局变量 
int oldsize=0;			//鼠标输入时要用的，判断是否新增订单 
struct stop{
			int ridern;
			int name;
			int x;
			int y;
			int flag;
			int iscan;
		};		
struct message Message={0};			//MESSAGE 初始化 
				//接单数
			
unsigned __stdcall start(void* pArguments)
{
	SetWindowSize(140,120);			//原图为78*51  
	Message.messagemoney=money;
	Message.accomplish=0;		//完成数 
	Message.totalovertime=0;	//超时数 
	Message.sum=0;
	int boolnumber=0;				//判断是否破产使用 
	int j=0;			
	int number=0;		//读文件中的序号 
	//int size=0;      //控制订单数组的大小 
	int righttime=0;   //判断是否到达接单时刻 
	int value=1;
	int state=0;	//记录是否接完了所有单 
	Map a;
	a.init();		//绘制地图。。。。。 动画的地图绘制在cartonn里 
	int p=0;
	int q=0;
	int o=0;
	int i=0;
	FILE *fw=fopen("3.txt","r"); //打开文件 
	FILE *fp=fopen("outputs.txt","w");      //输出文件 
	for(;is_run()&&value==1;delay_fps(80)){	 			//大循环，控制整个进程 
		WaitForSingleObject(hMutex,INFINITE);			//线程互斥语句 ，相当于上锁 
		
		
		int rightnowfinish[300]={0};
		int rightnowticket[300]={0};
		struct stop Stop[310]={0};
		Stop[0].ridern=-1;
		Stop[1].ridern=-1;
		p=0;
		q=0;
		o=0;
		i=0;
		
		//2.打印地图 ，地图只打印一次 
		PIMAGE img=newimage();
		getimage(img,"C:/Users/ASUS/Desktop/map2.jpg"); 
		
		/*int pwidth = 1100, pheight = 720;
		//Resize image to pwidth*pheight
		PIMAGE save=gettarget();
		//Get image size
		settarget(img); 
		int width,height;
		width=getwidth();
		height=getheight();
		settarget(save); 
		PIMAGE backproc=newimage(pwidth,pheight);
		//Resize
		putimage(backproc,0,0,pwidth,pheight,img,0,0,width,height); 
		getimage(img,backproc,0,0,pwidth,pheight);
		delimage(backproc);*/
		
		putimage(0,0,img);
		//3.打印骑手 ,等文件输入没问题后，删除文件输入的相关部分，再调用这个部分 
		if(size!=0)							
			printmove();                                       
		else{
			//SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
			point a(15,34);
			//a.PrintRider();
			carprint(a.x,a.y,0);
			//SetColor(FOREGROUND_INTENSITY);	
		}
		xyprintf(0,50,"SIZE = %d",size);
		char str[20];
		sprintf(str, "fps %.02f", getfps()); //调用getfps取得当前帧率
		setcolor(WHITE);
		outtextxy(0, 0, str);
		
		printorder();
		printcartoonmessage(Message);
		
		
        xyprintf(720, 0, "x = %10d  y = %10d",
                 msg.x, msg.y);
                 //第一行显示鼠标x,y位置.
        xyprintf(720, 20, "move  = %d down  = %d up    = %d",
                 (int)msg.is_move(),
                 (int)msg.is_down(),
                 (int)msg.is_up());
                 //第二行显示鼠标是否有动作,按键状态
        xyprintf(720, 40, "left  = %d mid   = %d right = %d",
                 (int)msg.is_left(),
                 (int)msg.is_mid(),
                 (int)msg.is_right());
                 //第三行显示鼠标被按下的按键(左,中,右)
        xyprintf(720, 60, "wheel = %d  wheel rotate = %d",
                 (int)msg.is_wheel(),
                 msg.wheel);
                 //第四行显示滚轮位置
        xyprintf(720, 80, " %d   %d",        
        		msg.x/27/3*2,
				msg.y/27/3*2);
				
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
		int cyc,qqq=0;
		for(j=0;rider[j].exist==1;j++){
			fprintf(fp,"骑手%d的位置: %d, %d; 停靠:",j+1,(rider[j].x-1)/2,(rider[j].y-2)/4);//2*rider[i].x+1,4*rider[i].y+2
			for(i=0;Stop[i].flag!=0;i++){
				if(Stop[i].ridern==j){
					if(Stop[i].name==1){
						for(cyc=i;Stop[cyc].flag==1;cyc++){
							if(Stop[cyc].name==2&&Stop[cyc].ridern==j){
								fprintf(fp,"餐客 ");
								qqq=1;
								Stop[cyc].name=3;
							}
						}
						if(qqq==0)
							fprintf(fp,"餐厅 ");
					}
					if(Stop[i].name==2){
						for(cyc=i;Stop[cyc].flag==1;cyc++){
							if(Stop[cyc].name==1&&Stop[cyc].ridern==j){
								fprintf(fp,"餐客 ");
								qqq=1;
								Stop[cyc].name=3;
							}
						}
						if(qqq==0)
							fprintf(fp,"食客 "); 
					}	
					if(Stop[i].name ==3)
						fprintf(fp,"餐客 "); 
					fprintf(fp,"%d %d ",(Stop[i].x-1)/2,(Stop[i].y-2)/4);
					qqq=0;
					}
				}
			fprintf(fp,";\n");
		} 
		
				
		
		//10、如果所有订单完成，跳出循环
		for(j=0;j<size;j++){
			if(Menu[j].truereach==0)
			 	break;
		}
		if(j==size&&state==1)
			break; 			//订单数组中的所有订单都完成了，跳出循环。	
		
		sysclock++;
		Sleep(500);
		ReleaseMutex(hMutex);		//解锁 
		
	}		
	fclose(fw);				//关闭文件
	fclose(fp);	//关闭文件
	_endthreadex(0);	
	return 0;
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
