#include "tools.h"
#include <windows.h>
#include <stdio.h>
void SetWindowSize(int cols, int lines)//设置窗口大小
{
    system("title 外卖派单模拟系统");//设置窗口标题
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
    system(cmd);//设置窗口宽度和高度
}
void SetCursorPosition(const int x, const int y)//设置光标位置
{
    COORD position;
	position.X = x;	 
   	position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void SetColor(int colorID)//设置文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
