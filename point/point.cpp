#include "point.h" 
#include "tools.h" 
#include <cstdio> 
#include <iostream>
#include <graphics.h>
using namespace std;
void point::clear(){
	SetCursorPosition(x,y);
	std::cout<<" "; 
};

void point::PrintRider(){
	

	SetCursorPosition(x,y);
	std::cout<<"*";
};

void point::Printmap(){
	if(x==0&&y==0){
		PIMAGE img=newimage();
		PIMAGE img1=newimage(); 
		// 随机数初始化，如果需要使用随机数的话
		getimage(img,"C:/Users/ASUS/Desktop/map.jpg"); 
		int pwidth = 720, pheight = 720;
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
		
		getimage(img1,"C:/Users/ASUS/Desktop/2.jpg");//骑手 
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
		putimage(328,287,img1,MERGEPAINT);
		delimage(img);
		delimage(img1);
	}
   		   
	SetCursorPosition(x,y);
	std::cout<<"-----"<<endl;
	SetCursorPosition(x+1,y);
	std::cout<<"|   |"<<endl;
	SetCursorPosition(x+2,y);
	std::cout<<"-----";
	SetCursorPosition(x,y);
}
