#ifndef MENU_H
#define  MENU_H

#include"rider.h"
#include<stdio.h>
#include<stdlib.h>
	typedef struct menu{
			int x1;//骑手接餐地址横坐标
			int y1;//骑手接餐地址纵坐标
			int x2;//骑手送餐地址横坐标
			int y2;//骑手送餐地址纵坐标	
			int endtime;//这一单截止的时间 
			int *p;//指向骑手的指针
			int take;//判断骑手是否取餐 
			int finish;//判断骑手是否送到订餐 
			struct menu *waitlist;
		}Menu;
	
	void buyrider();//买骑手
	void allocatemenu(Menu*); //分配订单函数 ,实参是具体的订单 
	Menu* creatmenulist();//初始化链表 
	void addmenulist(int,Menu*);//往链表里添加内容 ,实参是具体骑手，具体订单 
	//骑手行驶路径的算法函数
	void performance();//打印每位骑手的接单数、完成数、超时数
	
	extern Menu *menu;//声明订单结构体数组 
	extern Rider *rid;//声明骑手结构体数组 
#endif 
