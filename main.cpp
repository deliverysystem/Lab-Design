#include <iostream>
#include"controller.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	start();
	SetCursorPosition(50,0);
	if(money>=0)
		printf("骑手已送完所有订单，程序结束运行\n");
	else
		printf("破产"); 
	SetCursorPosition(55,0);
	return 0;
}
