#include <graphics.h>
#include <process.h> 
#include<stdio.h>
#include<stdlib.h>

#include"controller.h"
#include"menu.h"
#include"cartoon.h"
#include"rider.h"
#include"point.h"
#include"message.h"
mouse_msg msg={0};
void printcartoonmessage(struct message a){
	xyprintf(900,100,"%d",sysclock);
	xyprintf(900,600,"%d",money);
	xyprintf(900,290,"%d/%d",a.accomplish,a.sum);
	xyprintf(900,450,"%d",a.totalovertime);
}
void initimg(int i){//对骑手的IMG初始化 
	rider[i].Riderimg =newimage();
}
void release(){//程序结束时释放骑手的IMG 
	int i;
	for(i=0;rider[i].exist ==1;i++){
		delimage(rider[i].Riderimg);
	}
}
void clearrider(int x,int y,int i){//清除骑手上一个位置的图像，有问题，在一些点会有残影 ,还会把骑手也清掉，使骑手无法显示 
	setfillcolor(BLACK);			//用矩形达到清除的目的 
	if(((y-2)/4*41)%2==0){
		bar((y-2)/4*41,(x-1)/2*41+17,(y-2)/4*41+57,(x-1)/2*41+17+23);
	}
	else{
		bar((y-2)/4*41+17,(x-1)/2*41,(y-2)/4*41+17+23,(x-1)/2*41+57);
	}
	cleardevice(rider[i].Riderimg);
}
void carprint(int x,int y,int i){
	//打印骑手 
	if(((y-2)/4*41)%2==0){				//如果骑手在横轴上 
		//cleardevice(rider[i].Riderimg);
		getimage(rider[i].Riderimg,"C:/Users/linln/Desktop/lab/Lab-Design-cartoon/pic/9.jpg");
		
		//2.打印骑手 */
		putimage((y-2)/4*41,(x-1)/2*41+17,rider[i].Riderimg);
		//putimage(720,200+50*i,rider[i].Riderimg); 
		xyprintf((y-2)/4*41,(x-1)/2*41+17,"%d",i);
	}
	else{
		getimage(rider[i].Riderimg,"C:/Users/linln/Desktop/lab/Lab-Design-cartoon/pic/7.jpg");
		
		putimage((y-2)/4*41+17,(x-1)/2*41,rider[i].Riderimg);
		//putimage(720,200+50*i,rider[i].Riderimg); 
		xyprintf((y-2)/4*41,(x-1)/2*41+17,"%d",i);
	}
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
			clearrider(a.x,a.y,i);							//清除骑手当前位置的图像 
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
		//SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
		a.changeposi(rider[i].x,rider[i].y);
		//a.PrintRider();
		carprint(a.x,a.y,i);
		//SetColor(FOREGROUND_INTENSITY);
	}
}

void printorder(){
	int i;
	PIMAGE img;
	img = newimage();
	getimage(img,"C:/Users/linln/Desktop/lab/Lab-Design-cartoon/pic/12.jpg"); 
		
	for(i=0;Menu[i].x1!=0;i++){
		if(Menu[i].trueget==0){//没取 
			putimage((Menu[i].y1-2)/4*41,(Menu[i].x1-1)/2*41,img);
			xyprintf((Menu[i].y1-2)/4*41,(Menu[i].x1-1)/2*41,"%d A",i);//后期可以改为贴图 
		}
		if(Menu[i].truereach==0&&Menu[i].mouseup==1){//没到 
			putimage((Menu[i].y2-2)/4*41,(Menu[i].x2-1)/2*41,img);
			xyprintf((Menu[i].y2-2)/4*41,(Menu[i].x2-1)/2*41,"%d B",i);//后期可以改为贴图 
		}
	}
} 
unsigned __stdcall getinput(void* pArguments){
	WaitForSingleObject(hMutex,INFINITE);
	int flag1=0,flag2=0,i=0,j=0;//flag1,2,是用来判断订单输入的 
	int oldflag1=0,oldflag2=0;
	int initflag=1;
	/*setcolor(RED);
	setfont(-30, 0,"宋体");*/
		
	//限定骑手起始位置,将初始化移到这，解决了下面buyrider的问题，说明不同线程之间变量不能共用 
	rider[0].receive =0;
	rider[0].achieve=0;
	rider[0].overtime=0;
	rider[0].x=15;									
	rider[0].y=34;
	rider[0].exist=1;
	rider[1].exist=0;		//x,y具体待补充 ,rider[i].A.changeposi(x,y);
	for(;is_run();delay_fps(80)){
		
		//2.买骑手
		buyrider();	
		
		//1.订单输入 
		while (mousemsg())
		{
			msg = getmouse();
		}
		
		flag1=(int)msg.is_down();
		
		if(flag1!=oldflag1&&flag1==1){//如果鼠标点下 且是房子 
			if(flag2%2==0){
				Menu[size].y1=(msg.x/27)/3*2;//动画的xy与控制台的相反 
				Menu[size].x1=msg.y/27/3*2;
				Menu[size].x1=2*Menu[size].x1+1;
				Menu[size].y1=4*Menu[size].y1+2;
			}
			else{
				Menu[size].p=NULL;
				Menu[size].get=0;
				Menu[size].reach=0;
				Menu[size].underline=0;
				Menu[size].truereach=0;
				Menu[size].trueget=0;
				Menu[size].trueovertime=0;
				Menu[size].mouseup=1;
				Menu[size].x2=msg.y/27/3*2;
				Menu[size].y2=msg.x/27/3*2;
				Menu[size].x2=2*Menu[size].x2+1;
				Menu[size].y2=4*Menu[size].y2+2;	
				Menu[size].endtime=sysclock+30;
				size++;
				Message.sum ++;
				allocatemenu(size-1);//size-1为此刻新接订单在订单数组中的下标 
			}
			flag2++;
		}
		oldflag1=flag1;
		
		Sleep(200);
		ReleaseMutex(hMutex);
	}
		
	release();
	_endthreadex(0);
	return 0;
}
