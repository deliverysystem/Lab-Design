#ifndef MENU_H
#define  MENU_H


#include<stdio.h>
#include<stdlib.h>
#include"rider.h"
class Rider;
	struct menu{
			int x1;//���ֽӲ͵�ַ������
			int y1;//���ֽӲ͵�ַ������
			int x2;//�����Ͳ͵�ַ������
			int y2;//�����Ͳ͵�ַ������	
			int endtime;//��һ����ֹ��ʱ�� 
			Rider *p;//ָ�����ֵ�ָ��
			int underline;//ָ�����ֵ��±� 
			int get;//�ж������Ƿ�ȡ�� 
			int reach;//�ж������Ƿ��͵����� 
			struct menu *nextmenu;
		};
	
	void buyrider();//������
	void allocatemenu(int); //���䶩������ ,ʵ���Ǿ���Ķ��� 
	struct menu* creatmenulist();//��ʼ������ 
	void addmenulist(int,struct menu*);//��������������� ,ʵ���Ǿ������֣����嶩�� 
	void performance();//��ӡÿλ���ֵĽӵ��������������ʱ��
	void deletelist(int);//ɾ�����ֶ��� 
	void destory();//�ͷſռ�
	struct menu* The_ith(Rider*,int i);//�������ֶ����б�ڼ������� 
#endif 
