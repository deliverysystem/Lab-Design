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
	xyprintf(900,160,"%d",sysclock);
	xyprintf(945,610,"%d",money);
	xyprintf(920,290,"%d/%d",a.accomplish,a.sum);
	xyprintf(850,440,"%d",a.totalovertime);
}
void initimg(){//对骑手的IMG初始化 
	int i;
	for(i=0;rider[i].exist ==1;i++){
		rider[i].Riderimg =newimage();
	}
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
		getimage(rider[i].Riderimg,"C:/Users/ASUS/Desktop/9.jpg");
		int pwidth1 =57,pheight1=23;
		//1.照片缩放 
		PIMAGE save1=gettarget();
		//Get image size
		settarget(rider[i].Riderimg); 
		int width1,height1;
		width1=getwidth();
		height1=getheight();
		settarget(save1); 
		PIMAGE backproc1=newimage(pwidth1,pheight1);
		//Resize
		putimage(backproc1,0,0,pwidth1,pheight1,rider[i].Riderimg,0,0,width1,height1); 
		getimage(rider[i].Riderimg,backproc1,0,0,pwidth1,pheight1);
		delimage(backproc1);
		//2.打印骑手 
		putimage((y-2)/4*41,(x-1)/2*41+17,rider[i].Riderimg);
	}
	else{
		getimage(rider[i].Riderimg,"C:/Users/ASUS/Desktop/8.jpg");
		int pwidth1 =23,pheight1=57;
		
		PIMAGE save1=gettarget();
		//Get image size
		settarget(rider[i].Riderimg); 
		int width1,height1;
		width1=getwidth();
		height1=getheight();
		settarget(save1); 
		PIMAGE backproc1=newimage(pwidth1,pheight1);
		//Resize
		putimage(backproc1,0,0,pwidth1,pheight1,rider[i].Riderimg,0,0,width1,height1); 
		getimage(rider[i].Riderimg,backproc1,0,0,pwidth1,pheight1);
		delimage(backproc1);
		
		putimage((y-2)/4*41+17,(x-1)/2*41,rider[i].Riderimg);
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
			//clearrider(a.x,a.y,i);							//清除骑手当前位置的图像 
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
		carprint(a.x,a.y,i);
		SetColor(FOREGROUND_INTENSITY);
	}
}
unsigned __stdcall getinput(void* pArguments){
	WaitForSingleObject(hMutex,INFINITE);
	int flag1,flag2,i=0,j=0;//flag1,2,是用来判断订单输入的 
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
	for(;is_run();delay_fps(60)){
		
		
		/*static PIMAGE page = NULL;//绘图层2，用于刷新画面,好像没用 
		if (page == NULL) {
		page = newimage(1100, 720);
		setbkcolor(WHITE);
		}
		cleardevice(page);
		settarget(page);
		setbkcolor(0xFCFCFC);
		settarget(NULL);*/
		//2.买骑手，不知道为啥就只买了一个骑手，但只剩100块钱,在调用buyrider前钱数为700，调用完为100，说明买了但骑手不知为何只有1。。。 
		 
		buyrider();	
		/*j=0;        //测试现在有多少骑手 
		for(i=0;rider[i].exist ==1;i++){
			j++;
		} 
		xyprintf(720,50,"钱数=%d",money);
		xyprintf(720,100,"骑手数量=%d",j);*/
		
		if(initflag==1){//只初始化一次 
			initimg();
			initflag=0;
		}
		
		//1.订单输入 
		while (mousemsg())
		{
			msg = getmouse();
		}
		
		flag1=(int)msg.is_down();
		flag2=(int)msg.is_up();
		if(flag1!=oldflag1&&flag1==1&&(msg.y/27/3)%2==0&&(msg.x/27/3)%2==0){//如果鼠标点下 且是房子 
			Menu[size].y1=msg.x/27/3;//动画的xy与控制台的相反 
			Menu[size].x1=msg.y/27/3;
			Menu[size].x1=4*Menu[size].x1+2;
			Menu[size].y1=2*Menu[size].y1+1;	
			outtextxy((msg.x/27/3*2+msg.x/27/3)*27,(msg.y/27/3*2+msg.y/27/3)*27,"下单");//后期可以改为贴图 
		}
		oldflag1=flag1;
		if(flag2==1&&flag2!=oldflag2&&(msg.y/27/3)%2==0&&(msg.x/27/3)%2==0){//与上面相同 
			Menu[size].p=NULL;
			Menu[size].get=0;
			Menu[size].reach=0;
			Menu[size].underline=0;
			Menu[size].truereach=0;
			Menu[size].trueget=0;
			Menu[size].trueovertime=0;
			Menu[size].x2=msg.y/27/3;
			Menu[size].y2=msg.x/27/3;
			Menu[size].x2=4*Menu[size].x2+2;
			Menu[size].y2=2*Menu[size].y2+1;	
			Menu[size].endtime=sysclock+30;
			size++;
			allocatemenu(size-1);//size-1为此刻新接订单在订单数组中的下标 
			outtextxy((msg.x/27/3*2+msg.x/27/3)*27,(msg.y/27/3*2+msg.y/27/3)*27,"下单");
		}
		oldflag2=flag2;
		
		
	
		//2.打印地图 ，地图只打印一次 
		PIMAGE img=newimage();
		getimage(img,"C:/Users/ASUS/Desktop/map2.jpg"); 
		
		int pwidth = 1100, pheight = 720;
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
		delimage(backproc);
		
		putimage(0,0,img);
		//3.打印骑手 ,等文件输入没问题后，删除文件输入的相关部分，再调用这个部分 
		if(size!=0)							
			printmove();                                       
		else{
			SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
			point a(15,34);
			a.PrintRider();
			carprint(a.x,a.y,0);
			SetColor(FOREGROUND_INTENSITY);	
		}
		
		xyprintf(0,50,"SIZE = %d",size);
		char str[20];
		sprintf(str, "fps %.02f", getfps()); //调用getfps取得当前帧率
		setcolor(WHITE);
		outtextxy(0, 0, str);
		
		printcartoonmessage(Message);
		Sleep(1000);
		ReleaseMutex(hMutex);
	}
	release();
	_endthreadex(0);
	return 0;
}
