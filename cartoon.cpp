#include <graphics.h>
#include <process.h> 
#include<stdio.h>

#include"controller.h"
#include"menu.h"
#include"cartoon.h"
#include"menu.h"
mouse_msg msg={0};
void carprint(int x,int y){
	PIMAGE img1=newimage();//打印骑手 
	getimage(img1,"C:/Users/ASUS/Desktop/2.jpg");
	int pwidth1 =70,pheight1=70;
	PIMAGE save1=gettarget();
	//Get image size
	settarget(img1); 
	int width1,height1;
	width1=getwidth();
	height1=getheight();
	settarget(save1); 
	PIMAGE backproc1=newimage(pwidth1,pheight1);
	//Resize
	putimage(backproc1,0,0,pwidth1,pheight1,img1,0,0,width1,height1); 
	getimage(img1,backproc1,0,0,pwidth1,pheight1);
	delimage(backproc1);
	setbkmode(TRANSPARENT);
	putimage((y-2)/4*41,(x-1)/2*41,img1,MERGEPAINT);
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
		carprint(a.x,a.y);
		SetColor(FOREGROUND_INTENSITY);
	}
}
unsigned __stdcall getinput(void* pArguments){
	WaitForSingleObject(hMutex,INFINITE);
	int flag1,flag2,i=0,j=0;
	int oldflag1=0,oldflag2=0;
	for(;is_run();delay_fps(60)){
		setcolor(RED);
		setfont(-28, 0,"宋体");
		
		static PIMAGE page = NULL;//绘图层2，用于刷新画面
		if (page == NULL) {
		page = newimage(1100, 720);
		setbkcolor(WHITE);
		}
		cleardevice(page);
		settarget(page);
		setbkcolor(0xFCFCFC);
		settarget(NULL);
		
		
		//1.订单输入 
		while (mousemsg())
		{
			msg = getmouse();
		}
		
		flag1=(int)msg.is_down();
		flag2=(int)msg.is_up();
		if(flag1!=oldflag1&&flag1==1){//如果鼠标点下 
			Menu[size].y1=msg.x/27/3;//动画的xy与控制台的相反 
			Menu[size].x1=msg.y/27/3;
			Menu[size].x1=4*Menu[size].x1+2;
			Menu[size].y1=2*Menu[size].y1+1;	
			outtextxy((msg.x/27/3*2+msg.x/27/3)*27,(msg.y/27/3*2+msg.y/27/3)*27,"下单");
		}
		oldflag1=flag1;
		if(flag2==1&&flag2!=oldflag2){//与上面相同 
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
		
		
		xyprintf(0,50,"SIZE = %d",size);
		{
			char str[20];
			sprintf(str, "fps %.02f", getfps()); //调用getfps取得当前帧率
			setcolor(WHITE);
			outtextxy(0, 0, str);
		}
		//2.打印地图 
		PIMAGE img=newimage();
		getimage(img,"C:/Users/ASUS/Desktop/map1.jpg"); 
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
		//3.打印骑手 
		if(size!=0)							
			printmove();                                       
		else{
			SetColor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
			point a(15,34);
			a.PrintRider();
			carprint(a.x,a.y);
			SetColor(FOREGROUND_INTENSITY);	
		}
		
		ReleaseMutex(hMutex);
		
	}
	
	_endthreadex(0);
	return 0;
}

