#include "tools.h"
#include <windows.h>
#include <stdio.h>
void SetWindowSize(int cols, int lines)//���ô��ڴ�С
{
    system("title �����ɵ�ģ��ϵͳ");//���ô��ڱ���
    char cmd[30];
    sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
    system(cmd);//���ô��ڿ�Ⱥ͸߶�
}
void SetCursorPosition(const int x, const int y)//���ù��λ��
{
    COORD position;
	position.X = x;	 
   	position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void SetColor(int colorID)//�����ı���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}


