#ifndef RIDER_H
#define RIDER_H

#include "tools.h"
#include "point.h"
#include "menu.h"
#include "list.h"

class Rider{
  public:
    int x,y;
    //point A(int a,int b):x(a),y(b) {
    void changeposi(int fx,int fy){
		x=fx,y=fy;
	};
    List Path,OldPath;
    int receive;//���ֵĽӵ���
    int achieve;//���ֵ������
    int overtime;//���ֳ�ʱ��
    Rider() {}
    Rider(int x,int y):x(x),y(y) {}
    int exist;
    struct menu* waitlist;
    int CalculatePath(struct menu* newmenu);//�����������һ����ʱ��
    int Manhatten(point* x,point* y);
    void GeneratePath(point* A,struct menu*,int t);
    void AddTOWaitlist(struct menu* newmenu);//���µĶ�����ӽ�waitlist
    ~Rider() {}
    //friend class Menu;
    friend class point;
    friend class List;
};

#endif
