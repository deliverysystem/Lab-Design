#include <iostream>
#include"controller.h"
#include"cartoon.h"
#include"tools.h"
#include <windows.h>
#include<stdio.h>
#include <process.h> 


int main(int argc, char** argv) {
	setinitmode(INIT_ANIMATION);//窗口初始化 
	initgraph(1100, 720);
	HANDLE hThread1,hThread2;//线程部分 
	hMutex=CreateMutex(NULL,FALSE,NULL);
   	hThread1=(HANDLE)_beginthreadex(NULL,0,getinput,NULL,0,NULL);   
	hThread2=(HANDLE)_beginthreadex(NULL,0,start,NULL,0,NULL);
    WaitForSingleObject(hThread1,INFINITE);	
	CloseHandle(hThread1);
    WaitForSingleObject(hThread2,INFINITE);	
	CloseHandle(hThread2);
	
	
	
	/*SetCursorPosition(40,0);
	if(money>=0)
	{
		SetColor(FOREGROUND_GREEN);
		printf("骑手已送完所有订单，程序结束运行\n");
	}
	else{
		SetColor(FOREGROUND_RED);
		printf("破产"); 
	}
	SetCursorPosition(45,0);
	SetColor(FOREGROUND_INTENSITY);*/
	closegraph();
	return 0;
}
