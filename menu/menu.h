#ifndef MENU_H
#define  MENU_H

#include"rider.h"
#include<stdio.h>
#include<stdlib.h>
	typedef struct menu{
			int x1;//���ֽӲ͵�ַ������
			int y1;//���ֽӲ͵�ַ������
			int x2;//�����Ͳ͵�ַ������
			int y2;//�����Ͳ͵�ַ������	
			int endtime;//��һ����ֹ��ʱ�� 
			int *p;//ָ�����ֵ�ָ��
			int take;//�ж������Ƿ�ȡ�� 
			int finish;//�ж������Ƿ��͵����� 
			struct menu *waitlist;
		}Menu;
	
	void buyrider();//������
	void allocatemenu(Menu*); //���䶩������ ,ʵ���Ǿ���Ķ��� 
	Menu* creatmenulist();//��ʼ������ 
	void addmenulist(int,Menu*);//��������������� ,ʵ���Ǿ������֣����嶩�� 
	//������ʻ·�����㷨����
	void performance();//��ӡÿλ���ֵĽӵ��������������ʱ��
	
	extern Menu *menu;//���������ṹ������ 
	extern Rider *rid;//�������ֽṹ������ 
#endif 
