#include <iostream>
#include"controller.h"
#include"tools.h"
#include <windows.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	start();
	SetCursorPosition(40,0);
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
	SetColor(FOREGROUND_INTENSITY);
	return 0;
}
