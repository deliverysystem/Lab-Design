#ifndef CONTROLLER_H
#define CONTROLLER_H
#include"menu.h"
#include"rider.h"
extern int bankruptcy(int );//判断是否破产 
extern void start();
extern void printmove();//对骑手进行移动 

extern int sysclock;
extern int money;
extern struct menu Menu[301];
extern Rider rider[100];
extern int Graph[100][100];

#endif
