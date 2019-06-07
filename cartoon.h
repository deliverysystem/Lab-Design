#ifndef CARTOON_H
#define CARTOON_H
#include <graphics.h>
unsigned __stdcall getinput(void* pArguments);
extern mouse_msg msg ;
void carprint(int ,int,int);
extern void printmove();//对骑手进行移动 
void initimg();//对骑手的IMG初始化 
void clearrider(int ,int ,int );//清除骑手上一个位置的图像，有问题，在一些点会有残影 
void release(); //程序结束时释放骑手的IMG 
#endif
